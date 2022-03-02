//
// Created by leo JULIEN on 11/02/22.
//

#ifndef FT_IRC_KICK_HPP
#define FT_IRC_KICK_HPP

#include "command.hpp"

class kick_command : public command {
public:
	kick_command(class client &c, class server &s) : command(c, s) {
		name = "KICK";
		syntax = "<channel> <user> [ <comment> ]";
		generate_token();
	};
	void execute() {
        std::string channel;
        this->get_arg("channel", channel);
        std::string user;
        this->get_arg("user", user);
        std::string comment;
        this->get_arg("comment", comment);
        if (channel.empty() || user.empty()){
            this->args["command"].push_back("KICK");
            this->reply_nbr(ERR_NEEDMOREPARAMS);
            return;
        }
        if (s.channels.find(channel) == s.channels.end()){
            this->args["channel"].push_back(channel);
            this->reply_nbr(ERR_NOSUCHCHANNEL);
            return;
        }
        if (c.channels.find(channel) == c.channels.end()){
            this->args["channel"].push_back(channel);
            this->reply_nbr(ERR_NOTONCHANNEL);
            return;
        }
        class channel *chan = c.channels.find(channel)->second;
        if (chan->members.find(&this->c)->second == false) {
            this->args["channel"].push_back(channel);
            this->reply_nbr(ERR_CHANOPRIVSNEEDED);
            return;
        }
        class client *cli = s.users.find(user)->second;
        cli->leave_chan(*chan);
        this->c.notice(*chan, "KICK", chan->id + " :" + comment);

            /*
             if (this->args.size() <= 2)
                 this->reply_nbr(ERR_NEEDMOREPARAMS);
             std::string channel;
             this->get_arg("channel", channel);
             std::string user;
             this->get_arg("user", user);
             std::string comment;
             this->get_arg("comment", comment);
             class channel *chan = c.channels.find(channel)->second;
             if (!is_channel(channel)) {
                 this->reply_nbr(ERR_NOSUCHCHANNEL);
                 return ;
             }
             if (chan->members.find(&this->c)->second == false) {
                 this->reply_nbr(ERR_CHANOPRIVSNEEDED);
                 return ;
             }
             if (is_member(user)) {
                 if (!is_member_channel(user, channel)) {
                     this->reply_nbr(ERR_NOTONCHANNEL);
                     return ;
                 }
             }
             else
                 return ;
             this->s.channels[channel].members.erase(get_client(user));
             */
	}
};

/**   Kick command

      Command: KICK
   Parameters: <channel> <user> [<comment>]

   The KICK command can be  used  to  forcibly  remove  a  user  from  a
   channel.   It  'kicks  them  out'  of the channel (forced PART).
   Only a channel operator may kick another user out of a  channel.
   Each  server that  receives  a KICK message checks that it is valid
   (ie the sender is actually a  channel  operator)  before  removing
   the  victim  from  the channel.

   Numeric Replies:

           ERR_NEEDMOREPARAMS
           "<command> :Not enough parameters"
           ERR_NOSUCHCHANNEL
           "<channel> :No such channel"
           ERR_CHANOPRIVSNEEDED
           "<channel> :you're not channel operator"
           ERR_NOTONCHANNEL
           "<channel> :You're not on that channel"

   Examples:

KICK &Melbourne Matthew         ; Kick Matthew from &Melbourne

KICK #Finnish John :Speaking English
                                ; Kick John from #Finnish using
                                "Speaking English" as the reason
                                (comment).

:WiZ KICK #Finnish John         ; KICK message from WiZ to remove John
                                from channel #Finnish

NOTE:
     It is possible to extend the KICK command parameters to the
following:

<channel>{,<channel>} <user>{,<user>} [<comment>]
**/

#endif //FT_IRC_KICK_HPP
