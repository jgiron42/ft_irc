//
// Created by frtalleu on 2/25/22.
//

#ifndef FT_IRC_WALLOPS_HPP
#define FT_IRC_WALLOPS_HPP
#include "command.hpp"
#include "utils.hpp"
#include "parse_conf.hpp"

class wallops_command : public command {
public:
    wallops_command(class client &c, class server &s) : command(c, s) {
        name = "WALLOPS";
		this->s.commands_count[this->name]++;
        syntax = "<param>";
        generate_token();
    };

    void execute() {
        std::string param;
        this->get_arg("param", param);
        if (param.empty()){
            this->args["command"].push_front("WALLOPS");
            this->reply_nbr(ERR_NEEDMOREPARAMS);
            return;
        }
        for (std::set<client *>::iterator i = c.s.operators.begin(); i != c.s.operators.end(); i++){
            (*i)->send(c, "WALLOPS", param);
        }

    };
};


/*
  Command: WALLOPS
   Parameters: Text to be sent to all operators currently online

   Sends  a  message  to  all   operators   currently   online.    After
   implementing  WALLOPS  as  a user command it was found that it was
   often and commonly abused as a means of sending a message to a lot
   of  people (much  similar to WALL).  Due to this it is recommended
   that the current implementation of  WALLOPS  be  used  as  an
   example  by  allowing  and recognising only servers as the senders of
   WALLOPS.

   Numeric Replies:

           ERR_NEEDMOREPARAMS = "<command> :Not enough parameters"

   Examples:

   :csd.bu.edu WALLOPS :Connect '*.uiuc.edu 6667' from Joshua; WALLOPS
                                   message from csd.bu.edu announcing a
                                   CONNECT message it received and acted
                                   upon from Joshua.
 */
#endif //FT_IRC_WALLOPS_HPP
