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
	char	buf[512];
private:
	int		sock;
};


#endif //FT_IRC_CLIENT_HPP