#include <exception>
//#include <error.h>
#include <cstring>
#include <string>
#include <cstring>
#include "utils.hpp"

const char *my_strerror(char *s1, int err)
{
	char *s2 = strerror(err);
	try {
		static std::string ret = std::string(s1) + std::string(s2);
		return ret.data();
	}
	catch (std::exception)
	{
		return s2;
	}
}

bool glob_include(char * glob, char * str)
{
	do {
		if (*glob == '*')
		{
			while (*glob == '*')
				++glob;
			if (!*glob)
				return true;
			while (*str) {
				if ((*glob == *str || *glob == '?') && glob_include(glob, str))
					return true;
				++str;
			}
			return false;
		}
		else if (*glob && (*glob == '?' || *glob == *str))
		{
			++str;
			++glob;
		}
	} while (*glob && (*str || *glob == '*'));
	return (*str == *glob);
}

bool	is_channel(const std::string &name)
{
	for (int i = 0; i < name.length() ; i++)
		if (name[i] ==  ' ' || name[i] == 7 || name[i] == ',')
			return (false);
	return ((name[0] == '&' || name[0] == '#') && name.length() <= CHAN_MAX_L);
}

bool	isspecial(const char c)
{
	return (c == '-' || c == '[' || c == ']' || c == '\\' || c == '\'' || c == '^' || c == '{' || c == '}');
}

bool	is_valid_nickname(const std::string &nick)
{
	if (!isalpha(nick[0]) || nick.size() > NICK_MAX_L)
		return (false);
	for (int i = 0; i < nick.length(); i++)
		if (!isalnum(nick[i]) && !isspecial(nick[i]))
			return (false);
	return (true);
}

void	log(const std::string &prefix, const std::string &str, log_type type)
{
	std::cout << prefix << log_color[type] << str << WHITE << std::endl;
}