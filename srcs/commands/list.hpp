//
// Created by Leo JULIEN on 2/20/22.
//

#ifndef FT_IRC_LIST_HPP
#define FT_IRC_LIST_HPP

#include "command.hpp"

class list_command : public command {
public:
	list_command(class client &c, class server &s) : command(c, s) {
		this->name = "LIST";
		this->syntax = "[ <canal> { ',' <canal> } [ <serveur> ] ]";
		generate_token();
	};

	void send_channel(const std::string &name, const std::string &topic) {
		if (name.empty())
			return ;
		this->args["channel"].push_front(name);
		this->args["topic"].push_front(topic);
		this->reply_nbr(RPL_LIST);
	}

	void print_canals() {
		std::map<std::string, channel>::iterator channels = this->s.channels.begin();

		while (channels != this->s.channels.end()) {
			if (channels->second.members.find(&this->c) != channels->second.members.end())
				send_channel(channels->first, channels->second.topic);
			else {
				if (!channels->second.private_channel && channels->second.secret_channel == false)
					send_channel(channels->first, channels->second.topic);
				else if (channels->second.private_channel && channels->second.secret_channel == false)
					send_channel(channels->first, "");
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
				send_channel(*channels, this->c.channels[*channels]->topic);
			else {
				if (this->s.channels.find(*channels) == this->s.channels.end()) {
					channels++;
					continue ;
				}
				tmp = this->s.channels.find(*channels)->second;
				if (!tmp.private_channel && tmp.secret_channel == false)
					send_channel(*channels, tmp.topic);
				else if (tmp.private_channel && tmp.secret_channel == false)
					send_channel(*channels, "");
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
