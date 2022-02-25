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
		{
			for (std::map<std::string, channel *>::iterator i = this->c.channels.begin(); i != this->c.channels.end(); i++)
				for (std::map<client *, bool>::iterator j = i->second->members.begin(); j != i->second->members.end(); j++)
				{
					std::cout << j->first->nickname << std::endl;
					if (j->first != &this->c)
						j->first->send(this->c,"QUIT", ":" + message);
				}
		}
		this->c.to_send.push_back("");
	}
};

/*
 *       Command: QUIT
   Parameters: [<Quit message>]

   A client session is ended with a quit message.  The server must close
   the connection to a client which sends a QUIT message. If a "Quit
   Message" is given, this will be sent instead of the default message,
   the nickname.

   When netsplits (disconnecting of two servers) occur, the quit message
   is composed of the names of two servers involved, separated by a
   space.  The first name is that of the server which is still connected
   and the second name is that of the server that has become
   disconnected.

   If, for some other reason, a client connection is closed without  the
   client  issuing  a  QUIT  command  (e.g.  client  dies and EOF occurs
   on socket), the server is required to fill in the quit  message  with
   some sort  of  message  reflecting the nature of the event which
   caused it to happen.

   Numeric Replies:

           None.

   Examples:

   QUIT :Gone to have lunch        ; Preferred message format.

 */

#endif //FT_IRC_QUIT_HPP
