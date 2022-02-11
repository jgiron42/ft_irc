//
// Created by Joachim GIRON on 8/28/21.
//

#ifndef FT_IRC_COMMANDS_HPP
#define FT_IRC_COMMANDS_HPP

#include "away.hpp"
#include "invite.hpp"
#include "kill.hpp"
#include "command.hpp"
#include "Server.hpp"
#include "client.hpp"
#include "user.hpp"
#include "names.hpp"
#include "nick.hpp"
#include "notice.hpp"
#include "pass.hpp"
#include "join.hpp"
#include "pong.hpp"
#include "privmsg.hpp"
#include "kick.hpp"
#include "version.hpp"
#include "time.hpp"
#include "mode.hpp"
#include "quit.hpp"
#include "command_not_found.hpp"

typedef command *creator(client &, server &);

template <class U>
command *f(client &c, server &s)
{
	return (new U(c, s));
}

creator *get_command(std::string name)
{
	static std::map<std::string, creator*> map;

	if (map.empty())
	{
		map["AWAY"] = &f<away_command>;
		map["INVITE"] = &f<invite_command>;
		map["JOIN"] = &f<join_command>;
		map["KILL"] = &f<kill_command>;
		map["NICK"] = &f<nick_command>;
		map["NAMES"] = &f<names_command>;
		map["NOTICE"] = &f<notice_command>;
		map["PASS"] = &f<pass_command>;
		map["PONG"] = &f<pong_command>;
		map["PRIVMSG"] = &f<privmsg_command>;
		map["QUIT"] = &f<quit_command>;
		map["TIME"] = &f<time_command>;
		map["USER"] = &f<user_command>;
		map["VERSION"] = &f<version_command>;
		map["MODE"] = &f<mode_command>;
		map["KICK"] = &f<kick_command>;
	}
	try {
		return (map.at(name));
	}
	catch (std::out_of_range &e)	{
		return (&f<command_not_found>);
	}
}

#endif //FT_IRC_COMMANDS_HPP
