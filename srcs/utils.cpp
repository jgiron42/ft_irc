//#include <exception>
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
	for (unsigned long i = 0; i < name.length() ; i++)
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
	if (!ft_isalpha(nick[0]) || nick.size() > NICK_MAX_L)
		return (false);
	for (unsigned long i = 0; i < nick.length(); i++)
		if (!ft_isalnum(nick[i]) && !isspecial(nick[i]))
			return (false);
	return (true);
}

void	log(const std::string &prefix, const std::string &str, log_type type)
{
	std::cout << prefix << log_color[type] << str << WHITE << std::endl;
}

void	ft_memcpy(char *dst, const char *src, size_t size)
{
	long int	*ldst;
	long int	*lsrc;

	while (size % sizeof(long int) && size > 0)
	{
		*dst = *src;
		dst++;
		src++;
		--size;
	}
	ldst = (long int *)dst;
	lsrc = (long int *)src;
	while (size > 0)
	{
		*ldst = *lsrc;
		ldst++;
		lsrc++;
		size -= 8;
	}
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

char	ft_toupper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c + ('A' - 'a'));
	if (c == '{')
		return ('[');
	if (c == '}')
		return (']');
	if (c == '|')
		return ('\\');
	return (c);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

bool	comp_nick::operator()(const std::string &n1, const std::string &n2) const {
	unsigned long int i;
	for (i = 0; i < n1.length() && i < n2.length(); i++)
	{
		if (ft_toupper(n1[i]) != ft_toupper(n2[i]))
			break;
	}
	return (ft_toupper(n1[i]) < ft_toupper(n2[i]));
}