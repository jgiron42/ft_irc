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
		this->args["version"].push_front(s.info.version);
		this->args["debug_level"].push_front(SSTR(s.info.debug_level));
		this->args["server"].push_back(this->s.hostname);
		this->args["comments"].push_back(this->s.info.version_comment);
		this->reply_nbr(RPL_VERSION);
	}
};

/*       Command: VERSION
   Parameters: [<server>]

   The VERSION message is used  to  query  the  version  of  the  server
   program.  An optional parameter <server> is used to query the version
   of the server program which a client is not directly connected to.

   Numeric Replies:

           ERR_NOSUCHSERVER                RPL_VERSION

   Examples:

   :Wiz VERSION *.se               ; message from Wiz to check the version
                                   of a server matching "*.se"

   VERSION tolsun.oulu.fi          ; check the version of server
                                   "tolsun.oulu.fi".
*/

#endif //FT_IRC_VERSION_HPP
