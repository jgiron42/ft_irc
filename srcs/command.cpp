
#include <command.hpp>
#include <sstream>
#include <cstdlib>
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

void
	command::add_block(int bt, std::string val)
{
	block b;

	b.bloc_type = bt;
	b.value = val;
	this->token.push_back(b);
}

void
	command::add_elem(t_params *p, std::list<block>::iterator it)
{
	this->args[it->value].push_back(p->str);
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

void command::parse_recurse()
{
	int is_rep = 0;
	int is_opt = 0;
	std::list<struct block>::iterator tmp = token.begin();

	while (it != this->token.end())
    {
        if (it->bloc_type == OPT)
        {
            it++;
            is_opt = 1;
        }
        if (p == NULL && !is_opt && it != this->token.end())
            throw command::argumentMissing();
        if (p == NULL && is_opt)
            return ;
        if (is_rep)
            command::add_list(p->str, it);
        if (it->bloc_type == ELEM && p != NULL)
        {
            tmp = it;
            tmp++;
            if (tmp != this->token.end() && tmp->bloc_type == REP)
            {
                it = tmp;
                command::add_list(p->str, it);
            }
            else
                add_elem(p, it);
        }
        if (it->bloc_type == ELEM)
            p = p->next;
        it++;
        if (it->bloc_type == REPE)
        {
            is_rep = 0;
            it++;
        }
        if (it->bloc_type == OPTE)
        {
            is_opt = 0;
            it++;
        }
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
			parse_recurse();
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

void command::reply_nbr(int nbr) {
	this->replied = true;
	std::string reply(replies[nbr]);
	//some substitutions
	this->reply(toStr(nbr), reply);
}

void command::reply(std::string command, std::string str) {
	if (!this->replied)
	{
		this->c.send(":" + this->s.hostname + " " + command + " " + this->c.username + " " + str + "\n");
	}
}
