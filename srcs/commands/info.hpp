//
// Created by frtalleu on 2/21/22.
//

#ifndef FT_IRC_INFO_HPP
#define FT_IRC_INFO_HPP
#include "command.hpp"

class info_command : public command {
public:
    info_command(class client &c, class server &s) : command(c, s) {
        name = "INFO";
        syntax = "[<server>]";
        generate_token(std::string(syntax));
    };
    void execute() {
        std::string server;
        this->get_arg("server", server);
        if (!server.empty() && this->s.hostname != server && this->s.users.find(server) != this->s.users.end()){
            this->args["server name"].push_back(server);
            this->reply_nbr(ERR_NOSUCHSERVER);
        }
        std::string str;
        str += "Host name = " + s.info.host_name + "\n";
        str += "Location = " + s.info.location + "\n";
        str += "Name location = " + s.info.name_location + "\n";
        str += "Mail = " + s.info.mail + "\n";
        str += "Network name" + s.info.network_name + "\n";
        str += "Other info = " + s.info.other_info + "\n";

        this->args["string"].push_back(str);
        this->reply_nbr(RPL_INFO);
        this->reply_nbr(RPL_ENDOFINFO);
    }
};

#endif //FT_IRC_INFO_HPP
