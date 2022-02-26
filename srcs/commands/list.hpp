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

	void send_channel(std::string name, std::string topic) {
		this->args["channel"].push_back(name);
		this->args["topic"].push_back(topic);
		this->reply_nbr(RPL_LIST);
	}

	void execute() {
		std::string canal;
		this->get_arg("canal", canal);
		std::map<std::string, channel>::iterator channels = this->s.channels.begin();

		this->reply_nbr(RPL_LISTSTART);
		if (canal.empty()) {
			while (channels != this->s.channels.end()) {
				if (channels->second.members.find(&this->c) != channels->second.members.end())
					send_channel(channels->first, channels->second.topic);
				else {
					if (channels->second.private_channel)
						send_channel(channels->first, "");
					else if (channels->second.secret_channel == false)
						send_channel(channels->first, channels->second.topic);
				}
				channels++;
			}
		}
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
