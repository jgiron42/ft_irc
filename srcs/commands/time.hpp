//
// Created by joachim on 1/30/22.
//

#ifndef FT_IRC_TIME_HPP
#define FT_IRC_TIME_HPP

#include "command.hpp"

class time_command : public command {
public:
	time_command(class client &c, class server &s) : command(c, s) {
		name = "TIME";
		syntax = "[ <server> ]";
		generate_token(std::string(syntax));
	};
	void execute() {
		std::time_t t = std::time(0);   // get time now
		std::tm* now = std::localtime(&t);
		this->args["time"].push_front(SSTR(now->tm_mday << '-'
				<< (now->tm_mon + 1) << '-'
				<< (now->tm_year + 1900) << " "
				<< now->tm_hour << ":"
				<< now->tm_min << ":"
				<< now->tm_sec));
		this->args["server"].push_front(this->s.hostname);
		this->reply_nbr(RPL_TIME);
	}
};

#endif //FT_IRC_TIME_HPP
