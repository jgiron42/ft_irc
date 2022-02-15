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
        std::string channel;

        this->get_arg("channel", channel);
        if (channel.empty()) {
            this->reply_nbr(ERR_NEEDMOREPARAMS);
            return ;
        }
        while (!channel.empty()) {
            if (this->s.channels.find(channel) == this->s.channels.end()) {
                this->reply_nbr(ERR_NOSUCHCHANNEL);
                return ;
            }
            if (this->s.channels[channel].members.find(&this->c) == this->s.channels[channel].members.end()) {
                this->reply_nbr(ERR_NOTONCHANNEL);
                return ;
            }
            this->s.channels[channel].members.erase(this->s.channels[channel].members.find(&this->c));
            this->get_arg("channel", channel);
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
