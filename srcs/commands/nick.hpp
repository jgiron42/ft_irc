//
// Created by Joachim GIRON on 8/26/21.
//

#ifndef FT_IRC_NICK_HPP
#define FT_IRC_NICK_HPP

#include "command.hpp"

class nick_command : public command {
public:
	nick_command(class client &c, class server &s) : command(c, s) {
		this->must_register = false;
		name = "NICK";
		syntax = "<nickname> [<hopcount>]";
		generate_token(std::string(syntax));
	};
	void execute() {
		std::string tmp;
		if (this->args.empty())
			this->reply_nbr(ERR_NONICKNAMEGIVEN);
		this->get_arg("nickname", tmp);
		if (!is_valid_nickname(tmp))
		{
			this->reply_nbr(ERR_ERRONEUSNICKNAME);
			return;
		}
		if (this->s.users.count(tmp))
		{
			this->reply_nbr(ERR_NICKNAMEINUSE);
			return;
		}
		this->c.set_nick(tmp);
		if (!this->c.identified && this->c.try_login()) {
			if (this->c.identified)
			{
				this->args["username"].push_front(this->c.username);
				this->args["hostname"].push_front(this->c.hostname);
				this->reply_nbr(RPL_WELCOME);
			}
			else
				this->reply_nbr(ERR_PASSWDMISMATCH);
		}
	}
};

/*
 *       Command: NICK
   Parameters: <nickname> [ <hopcount> ]

   NICK message is used to give user a nickname or change the previous
   one.  The <hopcount> parameter is only used by servers to indicate
   how far away a nick is from its home server.  A local connection has
   a hopcount of 0.  If supplied by a client, it must be ignored.

   If a NICK message arrives at a server which already knows about an
   identical nickname for another client, a nickname collision occurs.
   As a result of a nickname collision, all instances of the nickname
   are removed from the server's database, and a KILL command is issued
   to remove the nickname from all other server's database. If the NICK
   message causing the collision was a nickname change, then the
   original (old) nick must be removed as well.

   If the server recieves an identical NICK from a client which is
   directly connected, it may issue an ERR_NICKCOLLISION to the local
   client, drop the NICK command, and not generate any kills.

 Numeric Replies:
		ERR_NONICKNAMEGIVEN ERR_ERRONEUSNICKNAME
		ERR_NICKNAMEINUSE ERR_NICKCOLLISION
 Example:
	 NICK Wiz ; Introducing new nick "Wiz".
	 :WiZ NICK Kilroy ; WiZ changed his nickname to Kilroy.
 */

#endif //FT_IRC_NICK_HPP
