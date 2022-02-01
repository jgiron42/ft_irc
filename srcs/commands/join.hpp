//
// Created by Leo JULIEN on 1/02/22.
//

#ifndef FT_IRC_JOIN_HPP
#define FT_IRC_JOIN_HPP

#include "command.hpp"

class join_command : public command {
public:
	join_command(class client &c, class server &s) : command(c, s) {
		name = "JOIN";
		syntax = "<canal> { ',' <canal> } [ <cle> { ',' <cle> } ]";
		generate_token(std::string(syntax));
	};
	void execute() {
        std::cout << "is in execute" << std::endl;
		std::string tmp;
        std::string key;
		if (this->args.empty()) {
			std::cout << "none args" << std::endl;
        }
		//TODO: check if input is valid character
		this->get_arg("canal", tmp);
        this->get_arg("cle", key);
        std::cout << "THis is the arg taken : " << tmp << ", " << key << std::endl;
        /*
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

#endif //FT_IRC_JOIN_HPP
