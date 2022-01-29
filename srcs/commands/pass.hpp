//
// Created by Joachim GIRON on 8/26/21.
//

#ifndef FT_IRC_PASS_HPP
#define FT_IRC_PASS_HPP
#include "command.hpp"
#include "utils.hpp"

class pass_command : public command {
public:
	pass_command(class client &c, class server &s) : command(c, s) {
		name = "PASS";
		syntax = "<password>";
		generate_token(std::string(syntax));
	};
	void execute() { // TODO: masks
		if (this->c.identified)
			this->reply_nbr(ERR_ALREADYREGISTRED);
		else if (!this->args.count("password"))
			this->reply_nbr(ERR_NEEDMOREPARAMS);
		else
			//TODO: check if input is valid character
			this->c.password = this->args["password"].front();
	}
};

#endif //FT_IRC_PASS_HPP
