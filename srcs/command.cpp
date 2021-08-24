
#include <command.hpp>

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
	while (**syntax)
	{
		if (**syntax != ' ' && **syntax != p->str[0])
			value.push_back(**syntax);
		else
		{
			if (!key)
				throw syntaxError();
			this->args[key] = value;
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
				key = get_name(++syntax);
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
				*syntax = tmp;
			}
			while (**syntax != '}')
				(*syntax)++;
		}
	}
}

void command::parse(message m) {
	this->parse_recurse(this->syntax, m.params, false);
}
