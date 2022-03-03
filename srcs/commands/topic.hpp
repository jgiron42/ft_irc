//
// Created by Joachim GIRON on 8/26/21.
//

#ifndef FT_IRC_TOPIC_HPP
#define FT_IRC_TOPIC_HPP

#include "command.hpp"


/*
    Petit probleme, topic str disparait FIX
*/


class topic_command : public command {
public:
	topic_command(class client &c, class server &s) : command(c, s) {
		name = "TOPIC";
		this->s.commands_count[this->name]++;
		syntax = "<channel> [ <topic> ]";
		generate_token();
	};
	void execute() {
        std::string channel;
        std::string topic;
        bool        is_topic;

        this->get_arg("channel", channel);
        is_topic = this->get_arg("topic", topic);
        if (channel.empty()) {
            this->reply_nbr(ERR_NEEDMOREPARAMS);
            return ;
        }
        else if (this->s.channels.find(channel) == this->s.channels.end()) {
                this->reply_nbr(ERR_NOSUCHCHANNEL);
                return ;
		}
        if (this->c.channels.find(channel) == this->c.channels.end())
            this->reply_nbr(ERR_NOTONCHANNEL);
        else if (!this->c.channels[channel]->members[&this->c] && this->c.channels[channel]->topic_only_operator)
            this->reply_nbr(ERR_CHANOPRIVSNEEDED);
        else if (topic.empty()) {
            if (this->c.channels[channel]->topic.empty() && !this->c.channels[channel]->topic_exist) {
                this->reply_nbr(RPL_NOTOPIC);
                return;
            }
            if (is_topic) {
                this->c.channels[channel]->topic = "";
                return ;
            }
            this->c.notice(*this->c.channels[channel], "TOPIC", channel + " : " + topic);
            this->args[topic].push_back(this->c.channels[channel]->topic);
            this->reply_nbr(RPL_TOPIC);
        } else {
            this->c.channels[channel]->topic = topic;
            this->c.channels[channel]->topic_exist = true;
            this->args[topic].push_back(this->c.channels[channel]->topic);
            this->reply_nbr(RPL_TOPIC);
            this->c.notice(*this->c.channels[channel], "TOPIC", channel+" : "+topic);
        }
	}
};

/*
 *       Command:Topic message

      Command: TOPIC
   Parameters: <channel> [<topic>]

   The TOPIC message is used to change or view the topic of a channel.
   The topic for channel <channel> is returned if there is no <topic>
   given.  If the <topic> parameter is present, the topic for that
   channel will be changed, if the channel modes permit this action.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
           RPL_NOTOPIC                     RPL_TOPIC
           ERR_CHANOPRIVSNEEDED

   Examples:

   :Wiz TOPIC #test :New topic     ;User Wiz setting the topic.

   TOPIC #test :another topic      ;set the topic on #test to "another
                                   topic".

   TOPIC #test                     ; check the topic for #test.
 */

#endif //FT_IRC_NICK_HPP
