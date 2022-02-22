#ifndef FT_IRC_CLIENT_HPP
#define FT_IRC_CLIENT_HPP
#include <iostream>
#include <string>
#include <fcntl.h>
#include <cstring>
#include <ctime>
#include <deque>
#include <stack>
#include "channel.hpp"
#include "shell_colors.hpp"
#include "Server.hpp"
#include "utils.hpp"
#define ABS(n) ((n) > 0 ? (n) : -(n))

class channel;
class server;
class client {
public:
	client(server &s);
	client(int fd, server &s);
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
	bool	try_login();
	void	join_chan(channel &, bool as_op = false);
	void	leave_chan(channel &);
	bool	can_see(channel &);
	void	log(const std::string &);
	//private:
	server	&s;
	bool identified;
	std::map<std::string, channel *> channels;
	std::string password;
	std::string username;
	std::string nickname;


	std::string nickname_tmp;
	std::deque<std::string> nick_history;
	std::string hostname;
	std::string servername;
	std::string realname;
	std::string ip;
	std::string away_message;
	bool	away : 1;
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
    bool    alive;
	void	set_nick(std::string &);
};


#endif //FT_IRC_CLIENT_HPP
