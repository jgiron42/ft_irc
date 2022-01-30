//
// Created by joachim on 1/30/22.
//

#ifndef FT_IRC_VERSION_HPP
#define FT_IRC_VERSION_HPP

#include "command.hpp"
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <sstream>
#define SSTR( x ) static_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()
#include <string.h>

class version_command : public command {
public:
	version_command(class client &c, class server &s) : command(c, s) {
		name = "VERSION";
		syntax = " [ <server> ]";
		generate_token(std::string(syntax));
	};
	void execute() {
		this->args["version"].push_front(VERSION);\
		this->args["debug_level"].push_front(SSTR(DEBUG_LVL));
		this->args["server"].push_front(this->s.hostname);
		this->reply_nbr(RPL_VERSION);
	}
};

#endif //FT_IRC_VERSION_HPP
