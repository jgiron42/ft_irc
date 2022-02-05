//
// Created by joachim on 2/5/22.
//

#ifndef FT_IRC_KILL_HPP
#define FT_IRC_KILL_HPP
#include "command.hpp"

class kill_command : public command {
public:
	kill_command(class client &c, class server &s) : command(c, s) {
		name = "KILL";
		syntax = "<nickname> <comment>";
		generate_token(std::string(syntax));
	};
	void execute() {
		std::string nick;
		std::string comment;
		if (!this->c.op)
			this->reply_nbr(ERR_NOPRIVILEGES);
		else if (this->args.size() < 2)
			this->reply_nbr(ERR_NEEDMOREPARAMS);
		else
		{
			nick = this->args["nickname"].front();
			if (!this->s.users.count(nick))
			{
				this->reply_nbr(ERR_NOSUCHNICK);
				return;
			}
			comment = this->args["comment"].front();
			this->send(this->c, "KILL", ":" + comment, *this->s.users[nick]);
			this->s.users[nick]->to_send.push_back("");
		}
	}
};
#endif //FT_IRC_KILL_HPP
