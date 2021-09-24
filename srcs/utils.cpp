#include <exception>
#include <string>


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
