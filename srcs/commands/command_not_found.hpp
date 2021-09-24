//
// Created by Joachim GIRON on 8/26/21.
//

#ifndef FT_IRC_COMMAND_NOT_FOUND_HPP
#define FT_IRC_COMMAND_NOT_FOUND_HPP

#include "command.hpp"

class command_not_found : public command {
public:
	command_not_found(class client &c, class server &s) : command(c, s) {
		name = "";
		syntax = "";
	};
	void	parse(message){};
	void	execute() {
		this->reply_nbr(ERR_UNKNOWNCOMMAND);
	}
};

#endif //FT_IRC_NICK_HPP
