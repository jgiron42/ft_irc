//
// Created by joachim on 1/22/22.
//

#ifndef FT_NOTICE_JOIN_HPP
#define FT_NOTICE_JOIN_HPP
#include "command.hpp"
#include "utils.hpp"

class notice_command : public command {
public:
	notice_command(class client &c, class server &s) : command(c, s) {
		name = "NOTICE";
		syntax = "<receiver> { ',' <receiver> } <text to be sent>";
		this->generate_token(this->syntax);
	};
	void execute() {
		channel *c;
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
				{
					if (this->c.channels.count(*r)) {
						c = &this->s.channels[*r];
						for (std::map<client *, bool>::iterator i = c->members.begin(); i != c->members.end(); i++) {
							if (i->first == &this->c)
								continue;
							if (!i->first->away)
								this->send(this->c, this->name, *r + " :" + text, *i->first);
						}
					}
				}
				else if (this->s.users.count(*r)) {
					if (!this->s.users[*r]->away)
						this->send(this->c, this->name, *r + " :" + text, *this->s.users[*r]);
				}
				// user@host
				// channel
				// nick
				// #mask
				// $mask
			}
	}
};

/*
 Command: NOTICE
 Parameters: <nickname> <text>
 The NOTICE message is used similarly to PRIVMSG. The difference
 between NOTICE and PRIVMSG is that automatic replies must never be
 sent in response to a NOTICE message. This rule applies to servers
 too - they must not send any error reply back to the client on
 receipt of a notice. The object of this rule is to avoid loops
 between a client automatically sending something in response to
 something it received. This is typically used by automatons (clients
 with either an AI or other interactive program controlling their
 actions) which are always seen to be replying lest they end up in a
 loop with another automaton.
 See PRIVMSG for more details on replies and examples.
 */

#endif
