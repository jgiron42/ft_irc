//
// Created by joachim on 1/29/22.
//

#ifndef FT_IRC_UTILS_HPP
#define FT_IRC_UTILS_HPP
#include <string>
#include <iostream>
#include <sstream>

#include "shell_colors.hpp"
#define CHAN_MAX_L 200
#define NICK_MAX_L 9
#define SSTR( x ) (static_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str())

typedef enum e_log_type     {MSG_OUT, MSG_IN, CHAN_EVENT, SRV_EVENT, USER_EVENT, ERROR} log_type;
static const	char *log_color[] = {GREEN,   BLUE,   YELLOW,     MAGENTA,   CYAN,       RED};

bool glob_include(char * glob, char * str);
const char *my_strerror(char *s1, int err);
bool	is_channel(const std::string &);
bool	is_valid_nickname(const std::string &nick);
void	log(const std::string &prefix, const std::string &str, log_type type);
void	ft_memcpy(char *dst, const char *src, size_t size);
void	ft_bzero(void *s, size_t n);
char	ft_toupper(char c);
int	ft_isdigit(int c);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
class	comp_nick{
public:
	comp_nick(){}
	comp_nick(const comp_nick &){}
	bool	operator()(const std::string &n1, const std::string &n2) const;
};

#endif //FT_IRC_UTILS_HPP
