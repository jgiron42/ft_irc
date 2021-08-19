#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP
#include <map>
#include <vector>
#include "client.hpp"
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
#define MAX_CLIENT 1000
#define PORT	1111

class Server {
private:
	std::map<int, client>		clients;
	std::vector<struct pollfd>	fds;
	int	sock;
public:
	Server(void);
	Server(const Server &);
	~Server();
	Server &operator=(const Server &);
	void	routine();
	void	dispatch(client &c);
};


#endif //FT_IRC_SERVER_HPP