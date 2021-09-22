
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

std::vector<std::string> ft_split(std::string str, char c)
{
	std::vector<std::string> ret;
	std::string tmp;
	std::istringstream stream(str);

	while (std::getline(stream, tmp, c))
		ret.push_back(tmp);
	return (ret);
}

std::string get_name(char **syntax)
{
	char *begin = *syntax;

	while(**syntax && **syntax != '>')
		(*syntax)++;
	if (!**syntax)
		throw command::invalidSyntaxException();
	(*syntax)++;
	return (std::string(begin).substr(0, *syntax - begin - 1));
}

void command::parse_recurse (char **syntax, t_params *p, bool is_optional)
{
	static std::string key;
	static std::string value;
	if (!p)
	{
		if (is_optional)
			throw command::argumentMissing();
		return;
	}
	while (**syntax && p)
	{
		if (**syntax != ' ' && **syntax != '\n' && **syntax != p->str[0])
		{
			value.push_back(p->str[0]);
			p->str.erase(p->str.begin());
		}
		else
		{
			if (key.empty())
				throw syntaxError();
			this->args[key].push_back(value);
			key = "";
			value = "";
		}
		if (**syntax == p->str[0])
		{
			(*syntax)++;
			p->str.erase(p->str.begin());
		}
		else if (**syntax == ' ')
		{
			while(**syntax == ' ')
				(*syntax)++;
			p = p->next;
		}
		else if (**syntax == '}' || **syntax == ']')
			return;
		else if (**syntax == '<')
		{
			if (!p && !is_optional)
				throw command::syntaxError();
			else
				key = get_name(&(++(*syntax)));
		}
		else if (**syntax == '[')
		{
			(*syntax)++;
			try	{
				parse_recurse(syntax, p, true);
				if (**syntax != ']')
					throw command::invalidSyntaxException();
			}
			catch (argumentMissing s){}
			while (**syntax != ']')
				(*syntax)++;
		}
		else if (**syntax == '{')
		{
			(*syntax)++;
			char *stmp = *syntax;
			while (1)
			{
				try	{
					parse_recurse(syntax, p, true);
				}
				catch (argumentMissing s){
					break;
				}
				if (**syntax != '}')
					throw command::invalidSyntaxException();
				*syntax = stmp;
			}
			while (**syntax != '}')
				(*syntax)++;
		}
	}
	if (key.empty())
		throw syntaxError();
	this->args[key].push_back(value);
	key = "";
	value = "";
}

char *ft_string_dup(std::string str)
{
	const char *data = str.data();
	char *ret = (char*)malloc(str.length() + 1);

	for (int i = 0; i < str.length(); i++)
		ret[i] = data[i];
	ret[str.length()] = 0;
	return (ret);
}

void command::parse(message m) {
	char *str = ft_string_dup(this->syntax);
	try {
		this->args["command"].push_back(m.command_str);
		this->parse_recurse(&str, m.params, false);
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