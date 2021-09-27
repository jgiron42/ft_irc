
#include <command.hpp>
#include <sstream>
#include <cstdlib>

extern char replies[512][100];

template <typename T> std::string toStr(T tmp)
{
	std::ostringstream out;
	out << tmp;
	return out.str();
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
	command::add_elem(t_params *p, std::list<block>::iterator it)
{
	this->args[it->value].push_back(p->str);
}

void command::parse_recurse (t_params *p)
{
	std::list<block>::iterator it = this->token.begin();

	while (it != this->token.end())
	{
		if (it->bloc_type == ELEM)
			add_elem(p, it);
		if (it != this->token.end() && p->next == NULL)
			throw command::argumentMissing();
		p = p->next;
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
		command::parse_recurse(m.params);
		std::cout << "printing args:" << std::endl;
		for (std::map<std::string, std::list<std::string> >::iterator i = this->args.begin(); i != this->args.end(); i++)
		{
			std::cout << "  " << i->first << std::endl;
			for (std::list<std::string>::iterator j = i->second.begin(); j != i->second.end(); j++)
				std::cout << "    " << *j << std::endl;
		}
	}
	catch (std::exception e)
	{
		if (std::string(e.what()) == "syntax is invalid")
		{
			std::cerr << e.what()  << std::endl;
			exit(1);
		}
//		else if (std::string(e.what()) == "syntax error")
//				this->reply();
		else if (std::string(e.what()) == "missing argument")
				this->reply_nbr(ERR_NEEDMOREPARAMS);
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
