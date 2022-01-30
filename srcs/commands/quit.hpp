//
// Created by joachim on 1/30/22.
//

#ifndef FT_IRC_QUIT_HPP
#define FT_IRC_QUIT_HPP

#include "command.hpp"

class quit_command : public command {
public:
	quit_command(class client &c, class server &s) : command(c, s) {
		name = "QUIT";
		syntax = "[ <quit message> ]";
		generate_token(std::string(syntax));
	};
	void execute() {
		std::string message;
		if (this->get_arg("quit message", message))
			;
		this->s.disconnect(this->c.sock);
	}
};

#endif //FT_IRC_QUIT_HPP
