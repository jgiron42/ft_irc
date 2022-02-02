//
// Created by joachim on 1/29/22.
//

#ifndef FT_IRC_UTILS_HPP
#define FT_IRC_UTILS_HPP
#include <string>

bool glob_include(char * glob, char * str);
const char *my_strerror(char *s1, int err);
bool	is_channel(const std::string &);


#endif //FT_IRC_UTILS_HPP
