#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP
#include <map>
#include <vector>
#include <cstring>
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

char *my_strerror(char *s1, int err);

class server {
private:
	std::map<int, client>		clients;
	std::vector<struct pollfd>	fds;
	int	sock;
public:
	server(void);
	server(const server &);
	~server();
	server &operator=(const server &);
	void	routine();
	void	dispatch(client &c);
	std::string password;
	std::string hostname;

	typedef std::runtime_error syscall_failure;
//	class syscall_failure : public std::exception {
//	private:
//		std::string error;
//	public:
//		syscall_failure() throw() : error(""){}
//		syscall_failure( const syscall_failure& other ) throw() : error(other.error) {}
//		explicit syscall_failure( const std::exception& other ) throw() : error("") {}
//		syscall_failure(std::string &error) throw() {
//			this->error = error;
//		}
//		virtual const char    *what() const throw() {
//			return (this->error.data());
//		}
//		~syscall_failure() throw();
//	};
};


#endif //FT_IRC_SERVER_HPP