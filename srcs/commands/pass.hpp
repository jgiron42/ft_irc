//
// Created by Joachim GIRON on 8/26/21.
//

#ifndef FT_IRC_PASS_HPP
#define FT_IRC_PASS_HPP
#include "command.hpp"

class pass_command : public command {
	pass_command(class client &c, class server &s) : command(c, s) {};
	void execute() {
		this->client.password = this->args["password"].front();
	}
private:
	name = "PASS";
	syntax = "<password>";
};

#endif //FT_IRC_PASS_HPP
