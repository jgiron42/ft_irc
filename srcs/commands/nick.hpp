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
	};
	void execute() {
		//check collisions
		this->client.nickname = this->args["nickname"].front();
	}
};

#endif //FT_IRC_NICK_HPP
