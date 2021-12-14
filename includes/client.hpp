#ifndef FT_IRC_CLIENT_HPP
#define FT_IRC_CLIENT_HPP
#include <iostream>
#include <string>
#include <fcntl.h>
#include <cstring>
#include <deque>
#include "channel.hpp"
#define ABS(n) ((n) > 0 ? (n) : -(n))

class channel;
class client {
public:
	client();
	client(int fd);
	client(const client &);
	~client();
	client &operator=(const client &);
	void	bufappend(const char *, size_t);
	void	printBuf();
	std::string getBufStr();
	std::string popLine();
	std::deque<std::string> to_send;
	void	send(const std::string &);
	std::string getIP() const;
	void	setIP(const std::string &);
	void	pong();
//private:
	bool identified;
	std::vector<channel *> channels;
	std::string password;
	std::string username;
	std::string nickname;
	std::string hostname;
	std::string servername;
	std::string realname;
	std::string ip;
	bool	invisible : 1;
	bool 	notices : 1;
	bool	wallops : 1;
	bool	op : 1;
	char	buf[512];
	int		end;
	int		begin;
	int		sock;
	time_t	last_activity;
	bool	ping_send;
};


#endif //FT_IRC_CLIENT_HPP
