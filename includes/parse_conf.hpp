//
// Created by François-Louis Talleux on 04/02/2022.
//

#ifndef FT_IRC_PARSE_CONF_HPP
#define FT_IRC_PARSE_CONF_HPP

#include "string"
#include "Server.hpp"
class server;
typedef struct s_client_authorization {
    std::string host_addr;
    std::string password;
    std::string host_name;
    short port;
    std::string classes;
    std::string flags;
} t_client_authorization;

typedef struct s_oper_auth {
    std::string nickname;
    std::string password;
    std::string host_name;
    short port;
    std::string classes;
    std::string flags;
} t_oper_auth;


void parse_conf (server &s, const std::string &file);

#endif //FT_IRC_PARSE_CONF_HPP
