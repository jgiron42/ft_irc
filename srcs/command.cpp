
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
    command::add_list(std::string str, std::list<block>::iterator &it, std::vector<std::string> *p)
{
    it++;
    std::size_t sep_pos;
    std::list<block>::iterator tmp = it;
    std::string sep = tmp->value;
    std::string tmp_str;

    if ((sep_pos = str.find(sep)) == std::string::npos)
    {
		if (tmp->bloc_type != ELEM)
			tmp++;
		else {
			for (std::vector<std::string>::iterator ite = p->begin(); ite != p->end() ; ite++)
				add_elem_str(*ite, tmp);
			return ;
		}
        add_elem_str(str, tmp);
        tmp++;
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


enum scope {_OPT,_REP};

// advance (char)
// get_potential_delim

//need to split the string
//to handle this like before

void command::parse_recurse(std::string str)
{
    std::vector<std::string> p;
    std::istringstream temp(str);
    std::string s;
	std::string s_tmp;
	int is_rep = 0;
	int is_opt = 0;
	int colon_pos;
	std::list<struct block>::iterator it = token.begin();
	std::list<struct block>::iterator tmp;

    for (std::string s; temp >> s; ) {
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
            command::add_list(p.front(), it, &p);
        if (it->bloc_type == ELEM && !p.empty())
        {
            tmp = it;
            tmp++;
            if (tmp != this->token.end() && tmp->bloc_type == REP)
            {
				it = tmp;
                command::add_list(p.front(), tmp, &p);
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
#ifdef DEBUG_PARSER
		std::cout << "printing args:" << std::endl;
		for (std::map<std::string, std::list<std::string> >::iterator i = this->args.begin(); i != this->args.end(); i++)
		{
			std::cout << "  " << i->first << std::endl;
			for (std::list<std::string>::iterator j = i->second.begin(); j != i->second.end(); j++)
				std::cout << "    " << *j << std::endl;
		}
#endif
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
		this->c.send(this->s.hostname, command, str);
		this->replied = true;
	}
}

void command::send_numeric(const std::string &prefix, int n, client &dst) {
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
	this->c.send(prefix, n, reply);
}

void command::send_numeric(int n, client &dst) {
	this->send_numeric(this->s.hostname, n, dst);
}

void command::send_numeric(const client &from, int n, client &dst) {
	std::string prefix = from.nickname;
	if (!from.username.empty())
		prefix.append("!" + from.username);
	if (!from.username.empty())
		prefix.append("@" + from.getIP());
	this->send_numeric(prefix, n, dst);
}

void command::send_names(channel &chan) {
	std::string user_list;
	char flag;
	this->args["channel"].push_front(chan.id);
	int usable_length =
			512 - 1 - this->s.hostname.length() - 1 - 3 - 1 - this->c.nickname.length() - 1 - chan.id.length() - 2;
	//						 ':'  <hostname>                 ' ' <NUM> ' '  <nick>                     ' '  <chan_id>         ' :'
	for (std::map<class client *, bool>::iterator it = chan.members.begin();
		 it != chan.members.end(); it++) {
		if (it->second)
			flag = '@';
		else if (chan.moderated && chan.speakers.count(it->first->nickname))
			flag = '+';
		else
			flag = ' ';
		user_list += flag +  it->first->nickname; // 68 + this.s.hostname.length();
		if (user_list.length() + usable_length >= 499) {
			this->args["user_list"].push_front(user_list);
			this->send_numeric(RPL_NAMREPLY, this->c);
			user_list.clear();
		} else
			user_list.append(" ");
	}
	if (!user_list.empty()) {
		this->args["user_list"].push_front(user_list);
		this->send_numeric(RPL_NAMREPLY, this->c);
	}
	this->send_numeric(RPL_ENDOFNAMES, this->c);
}

void command::send_names(void) {
	bool is_visible;
	std::string user_list;
	this->args["channel"].push_front("*");
	int usable_length =
			512 - 1 - this->s.hostname.length() - 1 - 3 - 1 - this->c.nickname.length() - 1 - 1 - 2;
	//						 ':'  <hostname>                 ' ' <NUM> ' '  <nick>       ' '  '*' ' :'
	for (std::map<std::string, client *>::iterator it = s.users.begin(); it != s.users.end(); it++) {
		if (!it->second->invisible) {
			is_visible = false;
			for (std::map<std::string, channel *>::iterator j = it->second->channels.begin(); j != it->second->channels.end(); j++)
				is_visible |= c.can_see(*j->second);
			if (is_visible)
				continue;
			user_list += it->first; // 68 + this.s.hostname.length();
			if (user_list.length() + usable_length >= 499) {
				this->args["user_list"].push_front(user_list);
				this->send_numeric(RPL_NAMREPLY, this->c);
				user_list.clear();
			} else
				user_list.append(" ");
		}
	}
	if (!user_list.empty()) {
		this->args["user_list"].push_front(user_list);
		this->send_numeric(RPL_NAMREPLY, this->c);
	}
	this->send_numeric(RPL_ENDOFNAMES, this->c);

}

void command::send_names(const std::string &chan) {
	std::map<std::string, channel>::iterator i = this->s.channels.find(chan);
	if (chan == "*")
		this->send_names();
	else if (i != this->s.channels.end() && this->c.can_see(i->second))
		this->send_names(i->second);
	else
	{
		this->args["channel"].push_front(chan);
		this->send_numeric(RPL_ENDOFNAMES, this->c);
	}
}


bool command::is_member_channel(std::string &name, std::string &channel) {
    if (this->s.users[name]) {
        client *to_find = this->s.users[name];
        if (this->s.channels[channel].members.find(to_find) != this->s.channels[channel].members.end())
            return true;
    }
    return false;
}

bool command::is_member(std::string &name) {
    if (this->s.users[name]) {
        return true;
    }
    return false;
}

client *command::get_client(std::string &name) {
    return this->s.users[name];
}
