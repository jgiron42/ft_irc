//
// Created by joachim on 22/08/2021.
//

#ifndef FT_IRC_PARSE_STRUCT_HPP
#define FT_IRC_PARSE_STRUCT_HPP

typedef struct s_message{
	t_prefix	prefix;//optional
	char		*command_str;
	short int	command_nbr
	t_params	*params;
}				message;

typedef struct t_prefix
{
	t_host	*servername;
	char	*nick;
	char	*user;
	t_host	*host;
};

typedef char t_host;

typedef struct s_params {
	char		*str;
	t_params	*next;
}				t_params;

#endif //FT_IRC_PARSE_STRUCT_HPP
