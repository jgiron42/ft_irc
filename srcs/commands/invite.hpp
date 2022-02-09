//
// Created by joachim on 2/9/22.
//

#ifndef FT_IRC_INVITE_HPP
#define FT_IRC_INVITE_HPP
#include "command.hpp"
#include "utils.hpp"

class invite_command : public command {
public:
	invite_command(class client &c, class server &s) : command(c, s) {
		name = "INVITE";
		syntax = "<nickname> <channel>";
		generate_token(std::string(syntax));
	};
	void execute() {
		std::string nickname;
		std::string chan;
		if (this->args.size() < 3) {
			this->reply_nbr(ERR_NEEDMOREPARAMS);
			return;
		}
		this->get_arg("nickname", nickname);
		this->get_arg("channel", chan);
		std::map<std::string, channel *>::iterator chanit = this->c.channels.find(chan);
		std::map<std::string, client *>::iterator it = this->s.users.find(nickname);
		if (it == this->s.users.end())
			this->reply_nbr(ERR_NOSUCHNICK);
		else if (!this->s.channels.count(chan))
		{
			this->send(this->c, "INVITE", nickname + " :" + chan, *it->second);
			this->reply_nbr(RPL_INVITING);
		}
		else if (chanit == this->c.channels.end())
			this->reply_nbr(ERR_NOTONCHANNEL);
		else if (it->second->channels.count(chan))
			this->reply_nbr(ERR_USERONCHANNEL);
		else if (!chanit->second->members.find(&this->c)->second)
			this->reply_nbr(ERR_CHANOPRIVSNEEDED);
		else if (it->second->away)
		{
			this->args["away message"].push_back(it->second->away_message);
			this->reply_nbr(RPL_AWAY);
		}
		else
		{
			this->send(this->c, "INVITE", nickname + " :" + chan, *it->second);
			chanit->second->invites.insert(nickname);
			this->reply_nbr(RPL_INVITING);
		}
	}
};
#endif //FT_IRC_INVITE_HPP
