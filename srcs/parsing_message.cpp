//
// Created by Francois-louis TALLEUX on 8/23/21.
//

#include "../includes/parse_struct.hpp"
#include "string"

message *init_msg(void){
    message *res = new message;
    res->prefix = NULL;
    res->params = NULL;
    res->command_str = NULL;
    return res;
}

prefix *get_prefix(std::string str){
    prefix *res = new t_prefix;
    std::string tmp;
    size_t i = str.find_first_of(" ", 0);
    std::string pref;
    pref = str.substr(1, i);
    if (pref.find_first_of(".", 0) != std::string::npos && pref.find_first_of("@", 0) == std::string::npos){
        res->servername = pref;
        return res;
    }
    i = pref.find_first_of("!", 0);
    size_t j = pref.find_first_of("@", 0);
    size_t min = std::min(i, j);
    if (min == std::string::npos)
        res->nick = pref;
    else if (i < j){
        tres->nick = pref.substr(0, i);
        if (j != std::string::npos){
            res->user = pref.substr(i + 1, j);
            res->host = pref.substr(j + 1, pref.length());
        }
        else
            res->user = pref.substr(i + 1, pref.length());
    }
    else if (j < i) {
        res->nick = pref.substr(0, j);
        res->host = pref.substr(j + 1, pref.length());
    }
    return res;
}

std::string get_command(std::string str) {
    std::string cmd;
    size_t i = str.find_first_of(" ", 0);
    if (str.at(0) == ':'){
        cmd = str.substr(i + 1, str.length());
        i = cmd.find_first_of(" ", 0);
        while (i == 0){
            cmd = cmd.substr(i + 1, cmd.length());
            i = cmd.find_first_of(" ", 0);
        }
    }
    i = 0;
    while (cmd.at(i) != ' ' && i < cmd.length())
        i++;
    return cmd.substr(0, i);
}

message parse_msg(std::string str){
    message *res;
    if (str.at(0) == ':')
        res->prefix = get_prefix(str);
    res->command_str = get_command(str);
    //need to bei finish to parse the params
}