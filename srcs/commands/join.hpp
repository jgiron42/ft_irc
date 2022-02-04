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

  void connecting(class client &c, class server &s, std::string &canal) {
    this->s.channels[canal].addMember(this->c);
    if (!this->s.channels[canal].topic.empty())
    {
      std::cout << "tu est rentre ici connard" << std::endl;
      if (this->args["channel"].empty())
        this->args["channel"].push_front(std::string(canal));
      if (this->args["topic"].empty())
        this->args["topic"].push_front(this->s.channels[canal].topic);
      this->send_numeric(RPL_TOPIC, this->c);
    }
  }
  
	void execute() {
		std::string canal;
		std::string key;
		this->get_arg("canal", canal);
    if (canal.empty())
      this->reply_nbr(ERR_NEEDMOREPARAMS);
		this->get_arg("key", key);
		if (this->s.channels.find(canal) == this->s.channels.end() ) {
      std::cout << "channel successfully created." << std::endl;
      this->s.channels[canal] = channel(this->c);
      if (key.empty() == 0)
        this->s.channels[canal].setPass(key);
      connecting(this->c, this->s, canal);
    } else {
      if (this->s.channels[canal].getPass().empty())
        connecting(this->c, this->s, canal);
      else {
        if (key.compare(this->s.channels[canal].getPass()))
          this->reply_nbr(ERR_BADCHANNELKEY);
        else
          connecting(this->c, this->s, canal);
      }
    }
    this->get_arg("canal", canal);
		
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
