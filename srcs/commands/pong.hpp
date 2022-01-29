//
// Created by joachim on 1/29/22.
//

#ifndef FT_IRC_PONG_HPP
#define FT_IRC_PONG_HPP
#include "command.hpp"
#include "utils.hpp"

class pong_command : public command {
public:
	pong_command(class client &c, class server &s) : command(c, s) {
		name = "PONG";
		syntax = "<server1> [ <server2> ]";
		generate_token(std::string(syntax));
	};
	void execute() { // TODO: masks
//		if (this->args.size() < 1)
//			this->reply_nbr(ERR_NOORIGIN);
		this->c.pong();
	}
};

#endif //FT_IRC_PONG_HPP
