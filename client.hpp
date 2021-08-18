#ifndef FT_IRC_CLIENT_HPP
#define FT_IRC_CLIENT_HPP
#include <iostream>
#include <fcntl.h>

class client {
public:
	client();
	client(int fd);
	client(const client &);
	~client();
	client &operator=(const client &);
	void	bufappend(const char *, size_t);
	void	printBuf();
private:
	char	buf[512];
	int		end;
	int		begin;
	int		sock;
};


#endif //FT_IRC_CLIENT_HPP