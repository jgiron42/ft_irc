//
// Created by joachim on 2/5/22.
//

#ifndef FT_IRC_KILL_HPP
#define FT_IRC_KILL_HPP
#include "command.hpp"

class kill_command : public command {
public:
	kill_command(class client &c, class server &s) : command(c, s) {
		name = "KILL";
		syntax = "<nickname> <comment>";
		generate_token(std::string(syntax));
	};
	void execute() {
		std::string nick;
		std::string comment;
		if (!this->c.op)
			this->reply_nbr(ERR_NOPRIVILEGES);
		else if (this->args.size() < 2)
			this->reply_nbr(ERR_NEEDMOREPARAMS);
		else
		{
			nick = this->args["nickname"].front();
			if (!this->s.users.count(nick))
			{
				this->reply_nbr(ERR_NOSUCHNICK);
				return;
			}
			comment = this->args["comment"].front();
			this->send(this->c, "KILL", ":" + comment, *this->s.users[nick]);
			this->s.users[nick]->to_send.push_back("");
		}
	}
};

/*
 * Command: KILL
 Parameters: <nickname> <comment>
 The KILL message is used to cause a client-server connection to be
 closed by the server which has the actual connection. KILL is used
 by servers when they encounter a duplicate entry in the list of valid
 nicknames and is used to remove both entries. It is also available
 to operators.
 Clients which have automatic reconnect algorithms effectively make
 this command useless since the disconnection is only brief. It does
 however break the flow of data and can be used to stop large amounts
 of being abused, any user may elect to receive KILL messages
 generated for others to keep an ’eye’ on would be trouble spots.
 In an arena where nicknames are required to be globally unique at all
 times, KILL messages are sent whenever ’duplicates’ are detected
 (that is an attempt to register two users with the same nickname) in
 the hope that both of them will disappear and only 1 reappear.
 The comment given must reflect the actual reason for the KILL. For
 server-generated KILLs it usually is made up of details concerning
 the origins of the two conflicting nicknames. For users it is left
 up to them to provide an adequate reason to satisfy others who see
 it. To prevent/discourage fake KILLs from being generated to hide
 the identify of the KILLer, the comment also shows a ’kill-path’
 which is updated by each server it passes through, each prepending
 its name to the path.
 Numeric Replies:
 ERR_NOPRIVILEGES ERR_NEEDMOREPARAMS
 ERR_NOSUCHNICK ERR_CANTKILLSERVER
 KILL David (csd.bu.edu <- tolsun.oulu.fi)
 ; Nickname collision between csd.bu.edu
 and tolson.oulu.fi
 NOTE:
 It is recommended that only Operators be allowed to kill other users
 with KILL message. In an ideal world not even operators would need
 to do this and it would be left to servers to deal with.
 */

#endif //FT_IRC_KILL_HPP
