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
#include "command_not_found.hpp"


class zbeub_command : public command {
public:
	zbeub_command(class client &c, class server &s) : command(c, s) {
		name = "ZBEUB";
		syntax = "<arg1> {,<argn>}";
	};
	void execute() {
	}
};


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
		map["ZBEUB"] = &f<zbeub_command>;
	}
	try {
		return (map.at(name));
	}
	catch (std::out_of_range e)	{
		return (&f<command_not_found>);
	}
}

#endif //FT_IRC_COMMANDS_HPP
