//
// Created by Francois-louis TALLEUX on 8/23/21.
//

#include "../includes/parse_struct.hpp"
#include "string"
#include "iostream"
#include <cstdlib>
#include <cstring>

message *init_msg(void){
    message *res = new message;
    res->prefix = NULL;
    res->params = NULL;
    return res;
}

prefix *get_prefix(std::string str){
    prefix *res = new s_prefix;
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
        res->nick = pref.substr(0, i);
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

message *get_command(std::string str, message *res) {
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
    else
        cmd = str;
    while ( (i = cmd.find_first_of(" ", 0)) == 0)
        cmd = cmd.substr(i, cmd.length());

    if (i > cmd.length())
        i = cmd.length() - 1;
    if (i == std::string::npos)
        res->tmp_to_parse = "";
    else
        res->tmp_to_parse = cmd.substr(i + 1, cmd.length() );
    cmd = cmd.substr(0, i + 1);
    if (std::isdigit(cmd.at(0)) != 0){
        res->command_nbr = atoi(cmd.c_str());
        return res;
    }
    res->command_str = cmd;
	size_t end = cmd.find_last_not_of(" ");
	res->command_str = (end == std::string::npos) ? std::string("") : cmd.substr(0, end + 1);
	return res;
}

//t_params *get_param(std::string str){
//    if (str.length() == 0)
//        return (NULL);
//    t_params *res = new s_params;
//    res->next = NULL;
//    size_t i = str.find_first_of(" ", 0);
//    if (i == std::string::npos)
//        i = str.length();
//    while (i == 0){
//        str = str.substr(1, str.length());
//        i = str.find_first_of(" ", 0);
//    }
//    i = str.find_first_of(" ", 0);
//    if (i == std::string::npos)
//        i = str.length();
//    res->str = str.substr(0, i);
//    str = str.substr(i, str.length());
//    i = str.find_first_of(" ", 0);
//    while (i == 0){
//        str = str.substr(1, str.length());
//        i = str.find_first_of(" ", 0);
//    }
//    if (str.length() != 0 || !(str.empty()))
//        res->next = get_param(str);
//    return res;
//}

message *parse_msg(std::string str){
    message *res = init_msg();
    if (str.at(0) == ':')
        res->prefix = get_prefix(str);
    res = get_command(str, res);
    res->params = res->tmp_to_parse;//get_param(res->tmp_to_parse);
    return res;
}

void aff_parse(message *res){
    if (!(res->command_str.empty()))
        std::cout << "CMD STR " << res->command_str <<  std::endl;
    else
        std::cout << "CMD NBR " << res->command_nbr <<  std::endl;
    if (!res->params.empty()){
		std::cout << res->params << std::endl;
    }
    if (res->prefix){
        if (!(res->prefix->nick.empty())){
            std::cout << "OK" << std::endl;
            std::cout << "Host = " << res->prefix->host << std::endl;
            std::cout << "Nick = " << res->prefix->nick << std::endl;
            std::cout << "User = " << res->prefix->user << std::endl;
        }
        else if (!(res->prefix->servername.empty()))
            std::cout << "Servername = " << res->prefix->servername << std::endl;
    }
}

/*(int main()
{
    std::string tmp;
    message *m_tmp;

        //std::getline(std::cin, tmp);
        std::string ntm;
        ntm = ":irc.botspot.com 266 ccoe :Current Global Users: 1";
        std::cout << "==========================" << std::endl;
        std::cout << ntm << std::endl;
        m_tmp = parse_msg(ntm);
        aff_parse(m_tmp);
        ntm = "IRC Network ccoe!ccoe@192.168.1.59";
        std::cout << "==========================" << std::endl;
        std::cout << ntm << std::endl;
        m_tmp = parse_msg(ntm);
        aff_parse(m_tmp);
        ntm = ":irc.botspot.com 003 ccoe :This server was created";
        std::cout << "==========================" << std::endl;
        std::cout << ntm << std::endl;
        m_tmp = parse_msg(ntm);
        aff_parse(m_tmp);
        ntm = ":irc.botspot.com 004 ccoe irc.botspot.com";
        std::cout << "==========================" << std::endl;
        std::cout << ntm << std::endl;
        m_tmp = parse_msg(ntm);
        aff_parse(m_tmp);
        ntm = "Unreal3.2.3 iowghraAsORTVSxNCWqBzvdHtGp";
        std::cout << "==========================" << std::endl;
        std::cout << ntm << std::endl;
        m_tmp = parse_msg(ntm);
        aff_parse(m_tmp);
        ntm = ":irc.botspot.com 005 ccoe SAFELIST HCN";
        std::cout << "==========================" << std::endl;
        std::cout << ntm << std::endl;
        m_tmp = parse_msg(ntm);
        aff_parse(m_tmp);
        ntm = ":irc.botspot.com 251 ccoe :There are 1 users and";
        std::cout << "==========================" << std::endl;
        std::cout << ntm << std::endl;
        m_tmp = parse_msg(ntm);
        aff_parse(m_tmp);
        ntm = "NICK ok";
        std::cout << "==========================" << std::endl;
        std::cout << ntm << std::endl;
        m_tmp = parse_msg(ntm);
        aff_parse(m_tmp);
        ntm = "NICK";
        std::cout << "==========================" << std::endl;
        std::cout << ntm << std::endl;
        m_tmp = parse_msg(ntm);
        aff_parse(m_tmp);
}*/
