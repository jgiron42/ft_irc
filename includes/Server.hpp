#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP
#include <map>
#include <vector>
#include <cstring>
#include "client.hpp"
#include "channel.hpp"
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cerrno>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <exception>
#include <poll.h>
#define LIVENESS_TIMEOUT	120
#define PING_TIMEOUT		10
#define MAX_CLIENT			1000
#define PORT				1111
#define VERSION				"1"
#define DEBUG_LVL			0

const char *my_strerror(char *s1, int err);

class client;
class channel;
class server {
private:
	std::map<int, client>		clients;
	std::vector<struct pollfd>	fds;
	int	sock;
public:
	server(void);
	server(const server &);
	~server();
	server	&operator=(const server &);
	void	routine();
	void	routine_sock(struct pollfd fd);
	void	routine_client(struct pollfd &fd, time_t now);
	void	dispatch(client &c);
	void	disconnect(int fd);
	bool	check_liveness(client &, time_t);
	void	send_ping(client &);
	std::map<std::string, channel> channels;
	std::map<std::string, client *> users;
	std::string password;
	std::string hostname;
	typedef std::runtime_error syscall_failure;
};


#endif //FT_IRC_SERVER_HPP