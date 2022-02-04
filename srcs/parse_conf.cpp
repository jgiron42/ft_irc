//
// Created by François-Louis Talleux on 02/02/2022.
//

#include "Server.hpp"
#include "string"
#include "fstream"
#include "exceptions.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include "parse_conf.hpp"

#define NB_OPT 4


static void set_server(std::string target, server &serv) {
    in_addr addr;
    size_t pos = 2;
    if (target[1] != ':') //check si le format est respecte
        throw ft_irc::conf_file_error();
    //host_name
    size_t pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    serv.info.host_name = target.substr(pos, pos_bis);
    //ip
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos || inet_aton(target.substr(pos, pos_bis).c_str(), &addr) == 0)
        throw ft_irc::conf_file_error();
    serv.info.ip = addr.s_addr;
    //location
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    serv.info.location = target.substr(pos, pos_bis);
    std::string port;
    //port
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    port = target.substr(pos, pos_bis);
    if (port.empty())
        serv.info.port = 6667;
    else
        serv.info.port = (short)std::stoi(port);
    //sid
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    serv.info.sid = target.substr(pos, pos_bis);
};

static void administrative_information(std::string target, server &serv) {
    size_t pos = 2;
    if (target[1] != ':') //check si le format est respecte
        throw ft_irc::conf_file_error();
    //name_location
    size_t pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    serv.info.name_location = target.substr(pos, pos_bis);
    //mail
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    serv.info.mail = target.substr(pos, pos_bis);
    //other info
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    serv.info.other_info = target.substr(pos, pos_bis);
    //network name
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    serv.info.network_name = target.substr(pos, pos_bis);
};
void    open_socket(long ip, short port);
void    open_socket(std::string dir , short port);

static void allow_port(std::string target, server &serv) {
    in_addr addr;
    size_t pos = 2;
    if (target[1] != ':') //check si le format est respecte
        throw ft_irc::conf_file_error();
    std::string ip_directory;
    std::string stuff1; //pas utilise
    std::string stuff2; //pas utilise
    short port;
    std::string port_tmp;
    std::string flags; //pas utilise
    //ip directory
    size_t pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    ip_directory = target.substr(pos, pos_bis);
    //stuff1
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    stuff1 = target.substr(pos, pos_bis);
    //stuff2
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    stuff2 = target.substr(pos, pos_bis);
    //port
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    port_tmp = target.substr(pos, pos_bis);
    if (port_tmp.empty())
        throw ft_irc::conf_file_error();
    else
        port = (short)std::stoi(port_tmp);
    //flags
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    flags = target.substr(pos, pos_bis);
    //connect
    if (!ip_directory.empty())
        throw ft_irc::conf_file_error();
    if (inet_aton(ip_directory.substr(pos, pos_bis).c_str(), &addr) == 0)
        open_socket(ip_directory, port);
    else
        open_socket(addr.s_addr, port);
    (void)stuff1;
    (void)stuff2;
    (void)flags;
    //do some stuff with stuff1, stuff2 and flags
};

static void client_authorization(std::string target, server &serv) {
    t_client_authorization fill;
    size_t pos = 2;
    if (target[1] != ':') //check si le format est respecte
        throw ft_irc::conf_file_error();
    //host_addr
    size_t pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    fill.host_addr = target.substr(pos, pos_bis);
    //password
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    fill.password = target.substr(pos, pos_bis);
    //host name
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    fill.host_name = target.substr(pos, pos_bis);
    //port
    std::string port;
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    port = target.substr(pos, pos_bis);
    fill.port = (short)std::stoi(port);
    //classes
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    fill.classes = target.substr(pos, pos_bis);
    //flags
    pos = pos_bis;
    pos_bis = target.find_first_of(target, pos);
    if (pos_bis == std::string::npos)
        throw ft_irc::conf_file_error();
    fill.flags = target.substr(pos, pos_bis);
    serv.info.authorization.push_back(fill);
};


void parse_conf (server &s, const std::string &file){
    std::ifstream ifs;
    ifs.open(file);
    std::string read;

    typedef struct s_type{char c; void (*f)(std::string target, server &serv);} t_type;
    t_type lst_conf[NB_OPT] = {
            {'M', &set_server},
            {'A', &administrative_information},
            {'P', &allow_port},
            {'I', &client_authorization}
    };
    while (getline(ifs, read)){
        int i;
        for (i = 0; i < NB_OPT; i++){
            if (read[0] == lst_conf[i].c){
                lst_conf[i].f(read, s);
                break;
            }
        }
        if (read[0] != '#' || i == NB_OPT){
            throw ft_irc::conf_file_error();
        }
    }
}
