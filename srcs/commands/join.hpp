//
// Created by Leo JULIEN on 2/2/22
//

#ifndef FT_IRC_JOIN_HPP
#define FT_IRC_JOIN_HPP

#include "command.hpp"
#include "channel.hpp"

class join_command : public command {
public:
	join_command(class client &c, class server &s) : command(c, s) {
		name = "JOIN";
		syntax = "<canal> { ',' <canal> } <key> { ',' <key> }";
		generate_token(std::string(syntax));
	};

	void connecting(class client &c, class server &s, std::string &canal, bool as_op = false) {
		channel &chan = this->s.channels[canal];

		c.join_chan(chan, as_op);
		this->args["channel"].push_front(std::string(canal));
		if (!chan.topic.empty())
		{
			this->args["topic"].push_front(chan.topic);
			this->send_numeric(RPL_TOPIC, this->c);
		}
		for (std::map<client *, bool>::iterator i = chan.members.begin(); i != chan.members.end(); i++)
			this->send(this->c, "JOIN", chan.id, *i->first);
		this->send_names(chan);
	}

	void execute() { // TODO: join on invite
		std::string canal;
		std::string key;

		if (!this->get_arg("canal", canal))
		{
			this->reply_nbr(ERR_NEEDMOREPARAMS);
			return;
		}
		else if (!is_channel(canal))
		{
			this->reply_nbr(ERR_NOSUCHCHANNEL);
			return;
		}
		std::map<std::string, channel>::iterator chanit = this->s.channels.find(canal);
		if (chanit == this->s.channels.end()) {
			this->s.create_chan(canal, this->c, key);
			connecting(this->c, this->s, canal, true);
		}
		else if (chanit->second.members.size() >= chanit->second.user_limit)
			this->reply_nbr(ERR_CHANNELISFULL);
		else if (!chanit->second.invite_only)
		{
			if (chanit->second.invites.count(this->c.nickname))
				connecting(this->c, this->s, canal);
			else
				this->reply_nbr(ERR_INVITEONLYCHAN);
		}
		else if (!chanit->second.getPass().empty())
		{
			if (key.compare(this->s.channels[canal].getPass()))
				this->reply_nbr(ERR_BADCHANNELKEY);
			else
				connecting(this->c, this->s, canal);
		}
		else
			connecting(this->c, this->s, canal);
	}
};

/*
 *       Command: JOIN
   Parameters: <channel>{,<channel>} [<key>{,<key>}]

   The JOIN command is used by client to start listening a specific
   channel. Whether or not a client is allowed to join a channel is
   checked only by the server the client is connected to; all other
   servers automatically add the user to the channel when it is received
   from other servers.  The conditions which affect this are as follows:

           1.  the user must be invited if the channel is invite-only;

           2.  the user's nick/username/hostname must not match any
               active bans;

           3.  the correct key (password) must be given if it is set.

   These are discussed in more detail under the MODE command (see
   section 4.2.3 for more details).

   Once a user has joined a channel, they receive notice about all
   commands their server receives which affect the channel.  This
   includes MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.  The
   JOIN command needs to be broadcast to all servers so that each server
   knows where to find the users who are on the channel.  This allows
   optimal delivery of PRIVMSG/NOTICE messages to the channel.

   If a JOIN is successful, the user is then sent the channel's topic
   (using RPL_TOPIC) and the list of users who are on the channel (using
   RPL_NAMREPLY), which must include the user joining.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
           ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
           ERR_CHANNELISFULL               ERR_BADCHANMASK
           ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
           RPL_TOPIC

   Examples:

   JOIN #foobar                    ; join channel #foobar.

   JOIN &foo fubar                 ; join channel &foo using key "fubar".

   JOIN #foo,&bar fubar            ; join channel #foo using key "fubar"
                                   and &bar using no key.

   JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar".
                                   and channel #bar using key "foobar".

   JOIN #foo,#bar                  ; join channels #foo and #bar.

   :WiZ JOIN #Twilight_zone        ; JOIN message from WiZ

 */

#endif //FT_IRC_NICK_HPP
