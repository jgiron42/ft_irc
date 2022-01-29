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
		this->syntax = "<username> <hostname> <servername> <realname>";
		generate_token(std::string(syntax));
	};
	void execute() {
		if (this->args.size() < 4)
			this->reply_nbr(ERR_NEEDMOREPARAMS);
		else if (this->c.identified)
			this->reply_nbr(ERR_ALREADYREGISTRED);
		else
		{
			//TODO: check if input is valid character
			get_arg("username", this->c.username);
			get_arg("hostname", this->c.hostname);
			get_arg("servername", this->c.servername);
			get_arg("realname", this->c.realname);
			if (this->c.try_login()) {
				if (this->c.identified)
				{
					this->args["nickname"].push_front(this->c.nickname);
					this->reply_nbr(RPL_WELCOME);
				}
				else
					this->reply_nbr(ERR_PASSWDMISMATCH);
			}
		}
	};
};

#endif //FT_IRC_USER_HPP
