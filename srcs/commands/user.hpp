//
// Created by Joachim GIRON on 8/25/21.
//

#ifndef FT_IRC_USER_HPP
#define FT_IRC_USER_HPP

#include "command.hpp"

class user_command : public command {
public:
	user_command(class client &c, class server &s) : command(c, s) {
		this->must_register = false;
		this->name = "USER";
		this->syntax = "<username> <hostname> <servername> <realname>";
		generate_token(std::string(syntax));
	};
	void execute() {
		if (this->args.size() <= 4)
			this->reply_nbr(ERR_NEEDMOREPARAMS);
		else if (this->c.identified)
			this->reply_nbr(ERR_ALREADYREGISTRED);
		else
		{
			//TODO: check if input is valid character and length
			get_arg("username", this->c.username);
			get_arg("hostname", this->c.hostname);
			this->c.hostname = this->c.hostname.substr(0, 9);
			get_arg("servername", this->s.hostname);
			get_arg("realname", this->c.realname);
			if (this->c.try_login()) {
				if (this->c.identified)
				{
//					this->args["nickname"].push_front(this->c.nickname);
//					this->reply_nbr(RPL_WELCOME);

					this->args["servername"].push_front(this->s.hostname);
					this->reply_nbr(RPL_MOTDSTART);
					this->args["text"].push_front("");
					std::string &text = this->args["text"].front();
					for (unsigned long i = 0; i < this->s.info.motd.size(); i += 507)
					{
						text = this->s.info.motd.substr(i, 507);
						this->reply_nbr(RPL_MOTD);
					}
					this->reply_nbr(RPL_ENDOFMOTD);
				}
				else
					this->reply_nbr(ERR_PASSWDMISMATCH);
			}
		}
	};
};

/*
 *       Command: USER
   Parameters: <username> <hostname> <servername> <realname>

   The USER message is used at the beginning of connection to specify
   the username, hostname, servername and realname of s new user.  It is
   also used in communication between servers to indicate new user
   arriving on IRC, since only after both USER and NICK have been
   received from a client does a user become registered.

   Between servers USER must to be prefixed with client's NICKname.
   Note that hostname and servername are normally ignored by the IRC
   server when the USER command comes from a directly connected client
   (for security reasons), but they are used in server to server
   communication.  This means that a NICK must always be sent to a
   remote server when a new user is being introduced to the rest of the
   network before the accompanying USER is sent.

   It must be noted that realname parameter must be the last parameter,
   because it may contain space characters and must be prefixed with a
   colon (':') to make sure this is recognised as such.

   Since it is easy for a client to lie about its username by relying
   solely on the USER message, the use of an "Identity Server" is
   recommended.  If the host which a user connects from has such a
   server enabled the username is set to that as in the reply from the
   "Identity Server".

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Examples:


   USER guest tolmoon tolsun :Ronnie Reagan
                                   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan".


   :testnick USER guest tolmoon tolsun :Ronnie Reagan
                                   ; message between servers with the
                                   nickname for which the USER command
                                   belongs to


 */

#endif //FT_IRC_USER_HPP
