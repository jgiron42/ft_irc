//
// Created by joachim on 2/5/22.
//

#ifndef FT_IRC_AWAY_HPP
#define FT_IRC_AWAY_HPP
#include "command.hpp"

class away_command : public command {
public:
	away_command(class client &c, class server &s) : command(c, s) {
		name = "AWAY";
		syntax = "[ <message> ]";
		generate_token(std::string(syntax));
	};
	void execute() {
		if (get_arg("message", this->c.away_message))
		{
			this->c.away = true;
			this->reply_nbr(RPL_NOWAWAY);
		}
		else
		{
			this->c.away = false;
			this->reply_nbr(RPL_UNAWAY);
		}
	}
};


#endif //FT_IRC_AWAY_HPP
