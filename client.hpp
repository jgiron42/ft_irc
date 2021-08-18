#ifndef FT_IRC_CLIENT_HPP
#define FT_IRC_CLIENT_HPP
#include <iostream>

class client {
public:
	client(int fd);
	client(const client &);
	~client();
	client &operator=(const client &);
private:
	int sock;
};


#endif //FT_IRC_CLIENT_HPP