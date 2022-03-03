//
// Created by joachim on 2/9/22.
//

#ifndef FT_IRC_NAMES_HPP
#define FT_IRC_NAMES_HPP
#include "command.hpp"
#include "utils.hpp"

class names_command : public command {
public:
	names_command(class client &c, class server &s) : command(c, s) {
		name = "NAMES";
		this->s.commands_count[this->name]++;
		syntax = "[ <channel> { ',' <channel> } ]";
		generate_token();
	};
	void execute() {
		if (this->args.size() > 1)
		{
			std::list<std::string> &chans = this->args.find("channel")->second;
			for (std::list<std::string>::iterator i = chans.begin(); i != chans.end(); i++)
				this->send_names(*i);
		}
		else
		{
			for (std::map<std::string, channel >::iterator i = this->s.channels.begin(); i != this->s.channels.end(); i ++)
				this->send_names(i->second);
			this->send_names("*");
		}
        this->send_numeric(RPL_ENDOFNAMES, this->c);
	}
};

/*
 * Command: NAMES
 Parameters: [<channel>{,<channel>}]
 By using the NAMES command, a user can list all nicknames that are
 visible to them on any channel that they can see. Channel names
 which they can see are those which aren’t private (+p) or secret (+s)
 or those which they are actually on. The <channel> parameter
 specifies which channel(s) to return information about if valid.
 There is no error reply for bad channel names.
 If no <channel> parameter is given, a list of all channels and their
 occupants is returned. At the end of this list, a list of users who
 are visible but either not on any channel or not on a visible channel
 are listed as being on ‘channel’ "*".
 Numerics:
 RPL_NAMREPLY RPL_ENDOFNAMES
 Examples:
 NAMES #twilight_zone,#42 ; list visible users on #twilight_zone
 and #42 if the channels are visible to
 you.
 NAMES ; list all visible channels and users
 */

#endif //FT_IRC_NAMES_HPP
