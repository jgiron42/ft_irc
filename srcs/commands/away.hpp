//
// Created by joachim on 2/5/22.
//

#ifndef FT_IRC_AWAY_HPP
#define FT_IRC_AWAY_HPP
#include "command.hpp"

class away_command : public command {
public:
	away_command(class client &c, class server &s) : command(c, s) {
		name = "AWAY";
		this->s.commands_count[this->name]++;
		syntax = "[ <message> ]";
		generate_token();
	};
	void execute() {
		if (get_arg("message", this->c.away_message))
		{
			this->c.away = true;
			this->reply_nbr(RPL_NOWAWAY);
		}
		else
		{
			this->c.away = false;
			this->reply_nbr(RPL_UNAWAY);
		}
	}
};

/*
 * Command: AWAY
 Parameters: [message]

 With the AWAY message, clients can set an automatic reply string for
 any PRIVMSG commands directed at them (not to a channel they are on).
 The automatic reply is sent by the server to client sending the
 PRIVMSG command. The only replying server is the one to which the
 sending client is connected to.
 The AWAY message is used either with one parameter (to set an AWAY
 message) or with no parameters (to remove the AWAY message).
 Numeric Replies:
 RPL_UNAWAY RPL_NOWAWAY
 Examples:
 AWAY :Gone to lunch. Back in 5 ; set away message to "Gone to lunch.
 Back in 5".
 :WiZ AWAY ; unmark WiZ as being away.
 */
#endif //FT_IRC_AWAY_HPP
