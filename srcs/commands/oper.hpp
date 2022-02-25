//
// Created by frtalleu on 2/25/22.
//

#ifndef FT_IRC_OPER_HPP
#define FT_IRC_OPER_HPP

#include "command.hpp"
#include "utils.hpp"
#include "parse_conf.hpp"

class oper_command : public command {
public:
    oper_command(class client &c, class server &s) : command(c, s) {
        name = "OPER";
        syntax = "<name> <password>";
        generate_token(std::string(syntax));
    };

    void execute() {
        std::string name;
        std::string pass;
        this->get_arg("name", name);
        this->get_arg("password", pass);
        if (name.empty() || pass.empty()) {
            this->args["command"].push_front("OPER");
            this->reply_nbr(ERR_NEEDMOREPARAMS);
            return;
        }
        if (c.op){
            this->reply_nbr(RPL_YOUREOPER);
            return;
        }
        std::vector<t_oper_auth> oper = c.s.info.oper;
        bool ok = false;
        if (oper.empty()) {
            std::cout << "prout" << std::endl;
            this->reply_nbr(ERR_NOOPERHOST);
            return;
        }
        for (std::vector<t_oper_auth>::iterator i = oper.begin(); i != oper.end(); i++) {
            std::cout << "Hostname client = " << c.hostname << std::endl << "Target hostname = " << i->host_name << std::endl;
            if (c.hostname == i->host_name){
                ok = true;
                std::cout << "Nickname = " << i->nickname << std::endl << "Password = " << i->password << std::endl;
                if (name == i->nickname && pass == i->password){
                    c.op = true;
                    this->reply_nbr(RPL_YOUREOPER);
                    return;
                }
            }
        }
        if (ok)
            this->reply_nbr(ERR_PASSWDMISMATCH);
        else
            this->reply_nbr(ERR_NOOPERHOST);
    };
};


/*
    Command: OPER
            Parameters: <name> <password>

A normal user uses the OPER command to obtain operator privileges.
The combination of <name> and <password> are REQUIRED to gain
Operator privileges.  Upon success, the user will receive a MODE
message (see section 3.1.5) indicating the new user modes.

    Numeric Replies:

    ERR_NEEDMOREPARAMS  = "<command> :Not enough parameters"
    RPL_YOUREOPER       = ":You are now an IRC operator"
    ERR_NOOPERHOST      = ":No O-lines for your host"
    ERR_PASSWDMISMATCH  = ":Password incorrect"

    Example:

            OPER foo bar                    ; Attempt to register as an operator
                                            using a username of "foo" and "bar"
                                            as the password.
*/
#endif //FT_IRC_OPER_HPP
