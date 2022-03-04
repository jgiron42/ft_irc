#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP
#include <map>
#include <set>
#include <vector>
#include <cstring>
#include "client.hpp"
#include "channel.hpp"
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <cerrno>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <exception>
#include <poll.h>
#include "parse_conf.hpp"
#include <stdlib.h>
#include "utils.hpp"

#define LIVENESS_TIMEOUT	120
#define PING_TIMEOUT		10
#define MAX_CLIENT			1000
#define PORT				1111
#define VERSION				"1"
#define CRLF				"\r\n"
#define DEBUG_LVL			0
#define SERVERNAME			"ft_ic"

const char *my_strerror(char *s1, int err);

class client;
class channel;
class server {
private:
	std::map<int, client>		clients;
	std::set<int>				sockets;
	std::vector<struct pollfd>	fds;
public:
	server(void);
	server(const server &);
	~server();
	server	&operator=(const server &);
	void	open_socket(long, short);
	void 	open_socket(std::string const &path);
	void	routine();
	void	routine_sock(struct pollfd fd);
	void	routine_client(struct pollfd &fd, time_t now);
	void	dispatch(client &c);
	void	disconnect(int fd);
	bool	check_liveness(client &, time_t);
	void	send_ping(client &);
    void    print_info(void);
	void	log(const std::string &);
	channel	&create_chan(const std::string &name, std::string key);
	std::map<std::string, channel> channels;
	std::map<std::string, client *, comp_nick> users; // map nickname to user
	std::map<std::string, unsigned int> commands_count;
	std::set<client *> operators;
	std::string password;
	std::string hostname;
	int		history_size;
	typedef std::runtime_error syscall_failure;
	struct info {
	    long ip;
	    std::string version;
	    std::string version_comment;
	    std::string debug_level;
	    std::string location;
	    short port;
	    std::string sid;
	    std::string name_location;
	    std::string mail;
	    std::string other_info;
	    std::string network_name;
	    std::vector<t_client_authorization> authorization;
        std::vector<t_oper_auth> oper;
		std::string motd;
	} info;
};


#endif //FT_IRC_SERVER_HPP
