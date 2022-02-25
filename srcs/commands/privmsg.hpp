//
// Created by joachim on 1/22/22.
//

#ifndef FT_PRIVMSG_JOIN_HPP
#define FT_PRIVMSG_JOIN_HPP
#include "command.hpp"
#include "utils.hpp"

class privmsg_command : public command {
public:
	privmsg_command(class client &c, class server &s) : command(c, s) {
		name = "PRIVMSG";
		syntax = "<receiver> { ',' <receiver> } <text to be sent>";
		this->generate_token(this->syntax);
	};

	void send_channel(const std::string &name, const std::string &text)
	{
		channel *c;
		if (!this->c.channels.count(name))
		{
			this->reply_nbr(ERR_CANNOTSENDTOCHAN);
			return;
		}
		c = &this->s.channels[name];
		if (c->moderated && !c->speakers.count(this->c.nickname))
		{
			this->reply_nbr(ERR_CANNOTSENDTOCHAN);
			return;
		}
		for (std::map<client *, bool>::iterator i = c->members.begin(); i != c->members.end(); i++) {
			if (i->first == &this->c)
				continue;
			else if (i->first->away){
				this->args["nickname"].push_front(name);
				this->args["message"].push_front(i->first->away_message);
				this->reply_nbr(RPL_AWAY);
				this->replied = false;
			}
			else
				i->first->send(this->c, this->name, name + " :" + text);
		}

	}

	void	send_user(const std::string &name, const std::string &text)
	{
		if (!this->s.users[name]->away)
			this->s.users[name]->send(this->c, this->name, name + " :" + text);
		else {
			this->args["nickname"].push_front(name);
			this->args["message"].push_front(this->s.users[name]->away_message);
			this->reply_nbr(RPL_AWAY);
			this->replied = false;
		}

	}

	void execute() {
		std::list<std::string> receivers;
		std::string text;
		if (!this->get_arg("receiver", receivers))
			this->reply_nbr(ERR_NORECIPIENT);
		else if (!this->get_arg("text to be sent", text))
			this->reply_nbr(ERR_NOTEXTTOSEND);
		else
			for (std::list<std::string>::iterator r = receivers.begin(); r != receivers.end(); r++)
			{
				if (is_channel(*r))
					this->send_channel(*r, text);
				else if (this->s.users.count(*r))
					this->send_user(*r, text);
				else
				{
					this->args["nickname"].push_front(*r);
					this->reply_nbr(ERR_NOSUCHNICK);
				} // TODO: masks
				// user@host
				// #mask
				// $mask
			}
	}
};

/*
 *       Command: PRIVMSG
   Parameters: <receiver>{,<receiver>} <text to be sent>

   PRIVMSG is used to send private messages between users.  <receiver>
   is the nickname of the receiver of the message.  <receiver> can also
   be a list of names or channels separated with commas.

   The <receiver> parameter may also me a host mask  (#mask)  or  server
   mask  ($mask).   In  both cases the server will only send the PRIVMSG
   to those who have a server or host matching the mask.  The mask  must
   have at  least  1  (one)  "."  in it and no wildcards following the
   last ".".  This requirement exists to prevent people sending messages
   to  "#*"  or "$*",  which  would  broadcast  to  all  users; from
   experience, this is abused more than used responsibly and properly.
   Wildcards are  the  '*' and  '?'   characters.   This  extension  to
   the PRIVMSG command is only available to Operators.

   Numeric Replies:

           ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
           ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
           ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
           ERR_NOSUCHNICK
           RPL_AWAY

   Examples:

:Angel PRIVMSG Wiz :Hello are you receiving this message ?
                                ; Message from Angel to Wiz.

PRIVMSG Angel :yes I'm receiving it !receiving it !'u>(768u+1n) .br ;
                                Message to Angel.

PRIVMSG jto@tolsun.oulu.fi :Hello !
                                ; Message to a client on server

 */

#endif
