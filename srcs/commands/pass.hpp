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
		generate_token(std::string(syntax));
	};
	void execute() {
		this->c.password = this->args["password"].front();
	}
};

#endif //FT_IRC_PASS_HPP
