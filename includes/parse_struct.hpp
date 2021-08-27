//
// Created by joachim on 22/08/2021.
//

#ifndef FT_IRC_PARSE_STRUCT_HPP
#define FT_IRC_PARSE_STRUCT_HPP
#include "string"

typedef std::string t_host;

typedef struct s_params {
    std::string		str;
    struct s_params	*next;
}				t_params;

typedef struct s_prefix
{
    t_host	servername; // host = servername
    std::string	nick;
    std::string	user;
    t_host	host; // servername = host
} prefix;

typedef struct s_message{
	struct s_prefix	*prefix;//optional
	std::string	command_str;
	short int	command_nbr;
    std::string tmp_to_parse; // i need it to the parsing
    t_params	*params;
}				message;

#endif //FT_IRC_PARSE_STRUCT_HPP
