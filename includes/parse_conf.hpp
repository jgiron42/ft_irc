//
// Created by François-Louis Talleux on 04/02/2022.
//

#ifndef FT_IRC_PARSE_CONF_HPP
#define FT_IRC_PARSE_CONF_HPP

#include "string"

typedef struct s_client_authorization {
    std::string host_addr;
    std::string password;
    std::string host_name;
    short port;
    std::string classes;
    std::string flags;
} t_client_authorization;


void parse_conf (server &s, const std::string &file);

#endif //FT_IRC_PARSE_CONF_HPP
