//
// Created by Joachim GIRON on 8/26/21.
//

#ifndef FT_IRC_PASS_HPP
#define FT_IRC_PASS_HPP
#include "command.hpp"
#include "utils.hpp"

class pass_command : public command {
public:
	pass_command(class client &c, class server &s) : command(c, s) {
		name = "PASS";
		syntax = "<password>";
		generate_token(std::string(syntax));
	};
	void execute() { // TODO: masks
		if (this->c.identified)
			this->reply_nbr(ERR_ALREADYREGISTRED);
		else if (!this->args.count("password"))
			this->reply_nbr(ERR_NEEDMOREPARAMS);
		else
			//TODO: check if input is valid character
			this->c.password = this->args["password"].front();
	}
};

/*
 *       Command: PASS
   Parameters: <password>

   The PASS command is used to set a 'connection password'.  The
   password can and must be set before any attempt to register the
   connection is made.  Currently this requires that clients send a PASS
   command before sending the NICK/USER combination and servers *must*
   send a PASS command before any SERVER command.  The password supplied
   must match the one contained in the C/N lines (for servers) or I
   lines (for clients).  It is possible to send multiple PASS commands
   before registering but only the last one sent is used for
   verification and it may not be changed once registered.  Numeric
   Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Example:

           PASS secretpasswordhere

 */

#endif //FT_IRC_PASS_HPP
