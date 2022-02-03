
#include <command.hpp>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include "exceptions.hpp"
#include "t_token.hpp"
extern char replies[512][100];

template <typename T> std::string toStr(T tmp)
{
	std::ostringstream out;
	out << tmp;
	return out.str();
}
// Need to delete the below func later (DEBUG only)
std::string block_enum_printer(block b)
{
	if (b.bloc_type == ELEM)
		return ("ELEM");
	else if (b.bloc_type == OPT)
		return ("OPT");
	else if (b.bloc_type == OPTE)
		return ("OPTE");
	else if (b.bloc_type == REP)
		return ("REP");
	else if (b.bloc_type == REPE)
		return ("REPE");
	else if (b.bloc_type == STR)
		return ("STR");
	else if (b.bloc_type == CHAR)
		return ("CHAR");
	else if (b.bloc_type == OR)
		return ("OR");

	return ("unknown");
}

// END of debugging func


void command::token_displayer(std::list<struct block> token) {
    std::list<struct block> tmp = token;
    while (!tmp.empty()) {
        std::cout << "bt : " << block_enum_printer(tmp.front()) << " | " << token.front().value << std::endl;
        tmp.pop_front();
    }
}

void
        command::add_elem_str(std::string str, std::list<block>::iterator it)
{
        this->args[it->value].push_back(str);
}


void
	command::add_block(int bt, std::string val)
{
	block b;

	b.bloc_type = bt;
	b.value = val;
	this->token.push_back(b);
}

void
	command::add_elem(std::string str, std::list<block>::iterator it)
{
	this->args[it->value].push_back(str);
}

void
    command::add_list(std::string str, std::list<block>::iterator &it)
{
    it++;
    std::size_t sep_pos;
    std::list<block>::iterator tmp = it;
    std::string sep = tmp->value;
    std::string tmp_str;

    if ((sep_pos = str.find(sep)) == std::string::npos)
    {
        tmp++;
        add_elem_str(str, tmp);
        tmp++;
        std::cout << block_enum_printer(*tmp) << std::endl;
        it = tmp;
        return ;
    }
    while (!str.empty())
    {
        if (tmp->bloc_type == REPE)
            tmp = it;
        sep = tmp->value;
        tmp++;
        tmp++;
        if ((sep_pos = str.find(sep)) == std::string::npos) // end of the list
        {
            tmp--;
            add_elem_str(str, tmp);
            tmp++;
            it = tmp;
            return ;
        }
        tmp_str.assign(str);
        tmp--;
        add_elem_str(tmp_str.erase(sep_pos, std::string::npos), tmp);
        tmp++;
        str = str.substr(sep_pos + 1, std::string::npos);
    }
}


enum scope : bool {_OPT,_REP};

// advance (char)
// get_potential_delim

//need to split the string
//to handle this like before

void command::parse_recurse(std::string str)
{
	std::cout << "starting str " << str << std::endl;
    std::vector<std::string> p;
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    std::istringstream temp(str);
    std::string s;
	std::string s_tmp;
	int is_rep = 0;
	int is_opt = 0;
	int colon_pos;
	std::list<struct block>::iterator it = token.begin();
	std::list<struct block>::iterator tmp;

    while (std::getline(temp, s, ' ')) {
		if (s.at(0) == ':') {
			colon_pos = str.find(':', 0);
			p.push_back(str.substr(colon_pos + 1, str.length()));
			break;
		}
        p.push_back(s);
    }

	while (it != this->token.end())
    {
        if (it->bloc_type == OPT)
        {
            it++;
            is_opt = 1;
        }
        if (p.empty() && !is_opt && it != this->token.end())
            return ;
        if (p.empty() && is_opt)
            return ;
        if (is_rep)
            command::add_list(p.front(), it);
        if (it->bloc_type == ELEM && !p.empty())
        {
            tmp = it;
            tmp++;
            if (tmp != this->token.end() && tmp->bloc_type == REP)
            {
                it = tmp;
                command::add_list(p.front(), tmp);
				p.erase(p.begin());
				while (tmp->bloc_type != REPE)
					tmp++;
				it = tmp++;
            }
            else
                add_elem(p.front(), it);
        }
        if (it->bloc_type == ELEM)
            p.erase(p.begin());
        if (it->bloc_type == REPE)
            is_rep = 0;
        if (it->bloc_type == OPTE)
            is_opt = 0;
		it++;
    }
}


char *ft_string_dup(std::string str)
{
	const char *data = str.data();
	char *ret = (char*)malloc(str.length() + 1);

	for (unsigned long i = 0; i < str.length(); i++)
		ret[i] = data[i];
	ret[str.length()] = 0;
	return (ret);
}

void command::parse(message m) {
	try {
		this->args["command"].push_back(m.command_str);
		try
		{
            parse_recurse(m.params);
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
		std::cout << "printing args:" << std::endl;
		for (std::map<std::string, std::list<std::string> >::iterator i = this->args.begin(); i != this->args.end(); i++)
		{
			std::cout << "  " << i->first << std::endl;
			for (std::list<std::string>::iterator j = i->second.begin(); j != i->second.end(); j++)
				std::cout << "    " << *j << std::endl;
		}
	}
	catch (std::exception &e)
	{
		if (std::string(e.what()).compare("missing argument"))
			this->reply_nbr(ERR_NEEDMOREPARAMS);
		if (std::string(e.what()).compare("syntax is invalid"))
		{
			std::cerr << e.what()  << std::endl;
			return ;
		}
//		else if (std::string(e.what()) == "syntax error")
//				this->reply();
	}
}

bool command::get_arg(const std::string &key, std::string &dst) { // true if successfull
	std::map<std::string, std::list<std::string> >::iterator tmp =  this->args.find(key);
	if (tmp == this->args.end())
	{
		dst = "";
		return (false);
	}
	dst = tmp->second.front();
//	tmp->second.pop_front();
	return (true);
}

bool command::get_arg(const std::string &key, std::list<std::string> &dst) { // true if successfull
	std::map<std::string, std::list<std::string> >::iterator tmp =  this->args.find(key);
	if (tmp == this->args.end())
	{
		dst = std::list<std::string>();
		return (false);
	}
	dst = tmp->second;
	return (true);

}

void command::reply_nbr(int nbr) {
	this->send_numeric(nbr, this->c);
}

void command::reply(std::string command, std::string str) {
	if (!this->replied)
	{
		this->send(command, str, this->c);
		this->replied = true;
	}
}

void command::send_numeric(int n, client &c) {
	std::string format(replies[n]);
	std::string reply;
	std::map<std::string, std::list<std::string> >::iterator tmp;
	int j;
	for (int i = 0; i < format.size(); i++)
	{
		if (format[i] == '<')
		{
			for (j = i; format[j] != '>'; j++);
			tmp = this->args.find(format.substr(i + 1, j - i - 1));
			if (tmp != this->args.end())
				reply += tmp->second.front();
			i = j;
		}
		else
			reply += format[i];
	}
	this->send(toStr(n), reply, this->c);

}

void command::send(std::string command, std::string str, client &c) {
		c.send(":" + this->s.hostname + " " + command + " " + c.username + " " + str + "\n");
}
