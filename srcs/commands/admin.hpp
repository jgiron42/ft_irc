//
// Created by frtalleu on 2/22/22.
//

#ifndef FT_IRC_ADMIN_HPP
#define FT_IRC_ADMIN_HPP
#include "command.hpp"
#include "string"

class admin_command : public command {
public:
    admin_command(class client &c, class server &s) : command(c, s) {
        this->name = "ADMIN";
		this->s.commands_count[this->name]++;
        this->syntax = "[ <server> ]";
		this->s.commands_count[this->name]++;
		generate_token();
    };

    void execute() {
        std::string server;
        this->get_arg("server", server);
        if (!server.empty() &&  this->s.hostname != server){
            this->args["server name"].push_back(server);
            this->reply_nbr(ERR_NOSUCHSERVER);
        }
        if (server.empty())
            server = this->s.hostname;
        this->args["server"].push_back(server);
        this->reply_nbr(RPL_ADMINME);
        this->args["admin info"].push_back("PARIS");
        this->reply_nbr(RPL_ADMINLOC1);
        this->args["admin info"].push_back("42");
        this->reply_nbr(RPL_ADMINLOC2);
        this->args["admin info"].push_back("42@42.fr");

    };
};
#endif //FT_IRC_ADMIN_HPP


/*
4.3.7 Commande ADMIN
Commande: ADMIN
Paramètres: [<serveur>]

Le message ADMIN est utilisé pour trouver le nom de l'administrateur d'un serveur donné, ou
 du serveur courant si le paramètre <serveur> est omis. Tout serveur doit posséder la possibilité
 de propager les messages ADMIN aux autres serveurs.

Réponses numériques :

           ERR_NOSUCHSERVER
           RPL_ADMINME                     RPL_ADMINLOC1
           RPL_ADMINLOC2                   RPL_ADMINEMAIL
Exemples:

ADMIN tolsun.oulu.fi ; requête ADMIN de tolsun.oulu.fi
:WiZ ADMIN *.edu ; requête ADMIN de WiZ pour le premier serveur trouvé qui correspond à *.edu.

ERR_NOSUCHSERVER
"<nom de serveur> :No such server"

RPL_ADMINME
"<serveur> :Administrative info"

RPL_ADMINLOC1
":<info admin>"

RPL_ADMINLOC2
":<info admin>"

RPL_ADMINEMAIL
":<info admin>"

 Lorsqu'il répond à un message ADMIN, un serveur doit renvoyer les réponses RLP_ADMINME à
 RPL_ADMINEMAIL et fournir un texte de message avec chacune. Pour RPL_ADMINLOC1, on attend
 une description de la ville et de l'état où se trouve le serveur, suivie des détails de
 l'université et du département (RPL_ADMINLOC2), et finalement le contact administratif pour
 ce serveur (avec obligatoirement une adresse email) dans RPL_ADMINEMAIL.
 */
