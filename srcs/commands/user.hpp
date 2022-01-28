//
// Created by Joachim GIRON on 8/25/21.
//

#ifndef FT_IRC_USER_HPP
#define FT_IRC_USER_HPP

#include "command.hpp"

class user_command : public command {
public:
	user_command(class client &c, class server &s) : command(c, s) {
		this->name = "USER";
		this->syntax = "<channel> { [ + | - ] | o | p | s | i | t | n | b | v } [ <limit> ] [ <user> ]";
		generate_token(std::string(syntax));
	};
	void execute() {
		if (!this->c.username.empty())
			this->reply_nbr(ERR_ALREADYREGISTRED);
		else
		{
			if (this->c.password == this->s.password)
			{
				this->c.username = this->args["username"].front();
				this->c.hostname = this->args["hostname"].front();
				this->c.servername = this->args["servername"].front();
				this->c.realname = this->args["realname"].front();
				// TODO: check syntax
				this->c.identified = true;
				this->reply_nbr(RPL_WELCOME);
			}
			else
				this->reply_nbr(ERR_PASSWDMISMATCH);
		}
	};
};

#endif //FT_IRC_USER_HPP
