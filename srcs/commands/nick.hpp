//
// Created by Joachim GIRON on 8/26/21.
//

#ifndef FT_IRC_NICK_HPP
#define FT_IRC_NICK_HPP

#include "command.hpp"

class nick_command : public command {
public:
	nick_command(class client &c, class server &s) : command(c, s) {
		name = "NICK";
		syntax = "<nickname> [<hopcount>]";
		generate_token(std::string(syntax));
	};
	void execute() {
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
	}
};

#endif //FT_IRC_NICK_HPP
