//
// Created by Joachim GIRON on 8/28/21.
//

#ifndef FT_IRC_COMMANDS_HPP
#define FT_IRC_COMMANDS_HPP

#include "command.hpp"
#include "Server.hpp"
#include "client.hpp"
#include "user.hpp"
#include "nick.hpp"
#include "pass.hpp"

typedef command *creator(client &, server &);

template <class U>
command *f(client &c, server &s)
{
	return (new U(c, s));
}

command *nullf(client &, server &) {
	return(NULL);
}

creator *get_command(std::string name)
{
	static std::map<std::string, creator*> map;
	if (map.empty())
	{
		map["USER"] = &f<user_command>;
		map["NICK"] = &f<nick_command>;
		map["PASS"] = &f<pass_command>;
	}
	try {
		return (map.at(name));
	}
	catch (std::out_of_range e)	{
		return (nullf);
	}
}

#endif //FT_IRC_COMMANDS_HPP
