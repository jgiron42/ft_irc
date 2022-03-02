//
// Created by François-Louis Talleux on 02/02/2022.
//

#include "Server.hpp"
#include <string>
#include "fstream"
#include "exceptions.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include "parse_conf.hpp"
#include "stdlib.h"

#define NB_OPT 6

std::string get_value(size_t target, std::string to_parse) {
    std::string res;
    size_t i = 0;
    size_t j = 0;
    while (to_parse[i]) {
        if (to_parse[i] == ':') {
            j++;
            if (j == target) {
                res = to_parse.substr(i + 1, to_parse.find_first_of(":", i + 1) - (i + 1));
                return (res);
            }
        }
        i++;
    }
    throw ft_irc::conf_file_error();
}

static void set_server(std::string target, server &serv) {
    in_addr addr;

    serv.hostname = get_value(1, target);
    inet_aton(get_value(2, target).c_str(), &addr);
    serv.info.ip = addr.s_addr;
    serv.info.location = get_value(3, target);
    std:: string port_str = get_value(4, target);
    if (port_str.empty())
        serv.info.port = 6667;
    else
        serv.info.port = (short) atoi(port_str.c_str());
    serv.info.sid = get_value(5, target);
    serv.password = get_value(6, target);
    std::cout << "Password = " << serv.password << std::endl;
}

static void administrative_information(std::string target, server &serv) {
    serv.info.name_location = get_value(1, target);
    serv.info.mail = get_value(2, target);
    serv.info.other_info = get_value(3, target);
    serv.info.network_name = get_value(4, target);
}
//void    open_socket(long ip, short port);
//void    open_socket(std::string dir , short port);



static void allow_port(std::string target, server &serv) {
    in_addr addr;
    std::string ip = get_value(1, target);
    std::string port = get_value(4, target);
    if (inet_aton(ip.c_str(), &addr))
        serv.open_socket(addr.s_addr, (short)atoi(port.c_str()));
    else
        serv.open_socket(ip);
}

static void client_authorization(std::string target, server &serv) {
    t_client_authorization fill;

    fill.host_addr = get_value(1, target);
    fill.password = get_value(2, target);
    fill.host_name = get_value(3, target);
    std:: string port_str = get_value(4, target);
    fill.port = (short)atoi(port_str.c_str());
    fill.classes = get_value(5, target);
    fill.flags = get_value(6, target);
    serv.info.authorization.push_back(fill);
}

static void special(std::string target, server &serv){
    std::ifstream ifs;
    std::string read;
    ifs.open(get_value(1, target).data());
    if (!(ifs.is_open()))
        throw ft_irc::conf_file_name_error();
    while (getline(ifs, read)){
        serv.info.motd += read;
        serv.info.motd += "\n";
    }
    ifs.close();
}

static void oper_author(std::string target, server &serv){
    t_oper_auth fill;

    fill.host_name = get_value(1, target);
    fill.password = get_value(2, target);
    fill.nickname = get_value(3, target);
    std:: string port_str = get_value(4, target);
    fill.port = (short)atoi(port_str.c_str());
    fill.classes = get_value(5, target);
    fill.flags = get_value(6, target);
    serv.info.oper.push_back(fill);
}

void parse_conf (server &s, const std::string &file){
    std::ifstream ifs;
    ifs.open(file.data());

    if (!(ifs.is_open()))
        throw ft_irc::conf_file_name_error();

    std::string read;
    // TODO: ajouter un moyen de specifier un path pour le motd puis parser ce fichier -> le path est maitenant ranger dans la variable X, comment parser le fichier?
    typedef struct s_type{char c; void (*f)(std::string target, server &serv);} t_type;
    t_type lst_conf[NB_OPT] = {
            {'M', &set_server},
            {'A', &administrative_information},
            {'P', &allow_port},
            {'I', &client_authorization},
            {'X', &special},
            {'O', &oper_author}
    };
    int i;
    int line = 0;
    try {
        while (getline(ifs, read)) {
            line++;
            for (i = 0; i < NB_OPT; i++) {
                if (read[0] == lst_conf[i].c) {
                    lst_conf[i].f(read, s);
                    break;
                }
            }
            if (read[0] != '#' && i == NB_OPT && read.length() != 0) {
                throw ft_irc::conf_file_error();
            }
        }
    }
    catch (std::exception &a) {
        if ((std::string)a.what() == "invalid conf file")
            std::cout << "line " << line << " : invalid conf file" << std::endl;
        throw;
    }

    ifs.close();
}
