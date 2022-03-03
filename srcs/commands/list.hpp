//
// Created by Leo JULIEN on 2/20/22.
//

#ifndef FT_IRC_LIST_HPP
#define FT_IRC_LIST_HPP

#include "command.hpp"
#include <string>
#include <iostream>
#include <sstream>

class list_command : public command {
public:
	list_command(class client &c, class server &s) : command(c, s) {
		this->name = "LIST";
		this->syntax = "[ <canal> { ',' <canal> } [ <serveur> ] ]";
		generate_token();
	};

	void visible_channel(channel &chan) {
		unsigned int visible = 0;
		for (std::map<client *, bool>::iterator it = chan.members.begin(); it != chan.members.end(); it++) {
			if (it->first->invisible)
				visible++;
		}
		this->args["visible"].push_front(SSTR(visible));
	}

	void send_channel(channel &chan, std::string topic, std::string name) {
		if (chan.id.empty())
			return ;
		this->args["channel"].push_front(name);
		visible_channel(chan);
		this->args["topic"].push_front(topic);
		this->reply_nbr(RPL_LIST);
	}

	void print_canals() {
		std::map<std::string, channel>::iterator channels = this->s.channels.begin();

		while (channels != this->s.channels.end()) {
			if (channels->second.members.find(&this->c) != channels->second.members.end())
				send_channel(channels->second, channels->second.topic, channels->first);
			else {
				if (!channels->second.private_channel && channels->second.secret_channel == false)
					send_channel(channels->second, channels->second.topic, channels->first);
				else if (channels->second.private_channel && channels->second.secret_channel == false)
					send_channel(channels->second, "", channels->first);
			}
			channels++;
		}
	}

	void print_choosen_canals() {
		std::list<std::string> channel_list;
		this->get_arg("canal", channel_list);
		std::list<std::string>::iterator channels = channel_list.begin();
		channel tmp;

		while (channels != channel_list.end()) {
			if (is_member_channel(this->c.nickname, *channels))
				send_channel(*this->c.channels[*channels], this->c.channels[*channels]->topic, *channels);
			else {
				if (this->s.channels.find(*channels) == this->s.channels.end())
					return ;
				tmp = this->s.channels.find(*channels)->second;
				if (!tmp.private_channel && tmp.secret_channel == false)
					send_channel(tmp, tmp.topic, *channels);
				else if (tmp.private_channel && tmp.secret_channel == false)
					send_channel(tmp, "Prv", *channels);
			}
			channels++;
		}
	}

	void execute() {
		std::string canal;
		this->get_arg("canal", canal);
		this->reply_nbr(RPL_LISTSTART);
		if (canal.empty())
			print_canals();
		else
			print_choosen_canals();
		this->reply_nbr(RPL_LISTEND);
	};
};

/*
 *       Message LIST

Commande: LIST
Paramètres: [<canal>{,<canal>} [<serveur>]]

Le message LIST est utilisé pour lister les canaux et leur sujet. Si le paramètre <canal> est utilisé,
seul le statut de ces canaux est affiché. Les canaux privés sont listés (sans leur sujet) comme canal
"Prv" à moins que le client qui génère la requête soit effectivement sur le canal. De même, les canaux
secrets ne sont pas listés du tout, à moins que le client soit un membre du canal en question.

Réponses numériques :

           ERR_NOSUCHSERVER                RPL_LISTSTART
           RPL_LIST                        RPL_LISTEND

Exemples:

    LIST ; Liste tous les canaux.
    LIST #twilight_zone,#42 ; Liste les canaux #twilight_zone et #42 
 */

#endif //FT_IRC_USER_HPP
