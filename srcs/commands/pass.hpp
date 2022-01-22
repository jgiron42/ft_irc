//
// Created by Joachim GIRON on 8/26/21.
//

#ifndef FT_IRC_PASS_HPP
#define FT_IRC_PASS_HPP
#include "command.hpp"

class pass_command : public command {
public:
	pass_command(class client &c, class server &s) : command(c, s) {
		name = "PASS";
		syntax = "<password>";
	};
	void execute() {
		if (this->c.identified)
			this->reply_nbr(ERR_ALREADYREGISTRED);
		else if (!this->args.count("password"))
			this->reply_nbr(ERR_NEEDMOREPARAMS);
		else
			this->c.password = this->args["password"].front();
	}
};

#endif //FT_IRC_PASS_HPP
