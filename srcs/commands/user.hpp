//
// Created by Joachim GIRON on 8/25/21.
//

#ifndef FT_IRC_USER_HPP
#define FT_IRC_USER_HPP

#include "command.hpp"


class user_command : public command {
public:
	user_command(class client &c, class server &s) : command(c, s) {};
	void execute() {
		if (!this->client.username.empty())
			this->reply(ERR_ALREADYREGISTRED);
		else
		{
			if (this->client.password == this->server.password)
			{
				this->client.username = this->args["username"].front();
				this->client.hostname = this->args["hostname"].front();
				this->client.servername = this->args["servername"].front();
				this->client.realname = this->args["realname"].front();
				this->client.identified = true;
				this->reply(RPL_WELCOME);
			}
			else
				this->reply(ERR_PASSWDMISMATCH);
		}
	};
private:
	std::string name = "USER";
	std::string syntax = "<username> <hostname> <servername> <realname>";
};

#endif //FT_IRC_USER_HPP
