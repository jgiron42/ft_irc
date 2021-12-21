
#include <command.hpp>
#include <sstream>
#include <cstdlib>
#include <stack>
#include "exceptions.hpp"

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
	command::add_elem_str(std::string str, std::list<block>::iterator it)
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


void command::parse_recurse (char *str)
{
//	std::list<block>::iterator it = this->token.begin();
	token_it<std::list<struct block> > tmp(this->token);
	std::stack<token_it<std::list<struct block> > > loop_begin;
	std::stack<enum scope, std::vector<bool> > current_scope;
	token_it<std::list<struct block> > next(this->token);
	bool delim[256];
	size_t pos;
	token_it<std::list<struct block> > it(this->token.begin(), this->token);

	while (it != it.end() && *str)
	{
		it.advance(*str);
		if (it->bloc_type == ELEM)
		{
			this->args[it->value].push_back("coucou");
			bzero(delim, 256);
			it.get_delim(delim);
			while (*str && !delim[*str])
				++str;
			it++;
		}
//		std::cout << it->value << std::endl;end
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
			parse_recurse(ft_string_dup(m.params));
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
