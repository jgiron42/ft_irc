//
// Created by Leo JULIEN on 2/2/22
//

#ifndef FT_IRC_JOIN_HPP
#define FT_IRC_JOIN_HPP

#include "command.hpp"

class join_command : public command {
public:
	join_command(class client &c, class server &s) : command(c, s) {
		name = "JOIN";
		syntax = "<canal> { ',' <canal> } <key> { ',' <key> }";
		generate_token(std::string(syntax));
	};
	void execute() {
		std::string canal;
		std::string key;
		this->get_arg("canal", canal);
		this->get_arg("key", key);
		std::cout << "aaaarrgggss : " << canal << " | " << key << std::endl;
		/*
		std::string tmp;
		if (this->args.empty())
			this->reply_nbr(ERR_NONICKNAMEGIVEN);
		//TODO: check if input is valid character
		this->get_arg("nickname", tmp);
		//TODO: check collisions
		this->c.nickname = tmp;
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
		*/
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

 */

#endif //FT_IRC_NICK_HPP
