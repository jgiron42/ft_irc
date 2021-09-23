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