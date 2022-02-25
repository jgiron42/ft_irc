//
// Created by Leo JULIEN on 2/15/22.
//

#ifndef FT_IRC_PART_HPP
#define FT_IRC_PART_HPP

#include "command.hpp"

class part_command : public command {
public:
	part_command(class client &c, class server &s) : command(c, s) {
		name = "PART";
		syntax = "<channel> { ',' <channel> }";
		generate_token(std::string(syntax));
	};
	void execute() {
        if (this->args.size() < 2) {
            this->reply_nbr(ERR_NEEDMOREPARAMS);
            return ;
        }
		std::list<std::string> &channels = this->args["channel"];
		std::string chan_name;
		while (!channels.empty())
		{
			channel chan;
			chan_name = channels.front();
			if (this->s.channels.find(chan_name) == this->s.channels.end()) {
                this->reply_nbr(ERR_NOSUCHCHANNEL);
            }
			else {
				chan = this->s.channels.find(chan_name)->second;
				if (chan.members.find(&this->c) == chan.members.end())
					this->reply_nbr(ERR_NOTONCHANNEL);
				else {
					this->c.notice(chan, "PART", chan.id + " :");
					this->c.leave_chan(chan);
				}
			}
			channels.pop_front();
        }
	}
};

/*
 *  Part message

      Command: PART
   Parameters: <channel>{,<channel>}

   The PART message causes the client sending the message to be removed
   from the list of active users for all given channels listed in the
   parameter string.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
           ERR_NOTONCHANNEL

   Examples:

   PART #twilight_zone             ; leave channel "#twilight_zone"

   PART #oz-ops,&group5            ; leave both channels "&group5" and
                                   "#oz-ops".
 */

#endif //FT_IRC_part_HPP
