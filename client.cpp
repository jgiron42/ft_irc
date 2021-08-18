#include "client.hpp"

client::client() : sock(-1){};
client::client(int fd) : sock(fd) {
	fcntl(fd, F_SETFL, O_NONBLOCK);
	std::cout << "new client" << std::endl;
}

client::client(const client &src) : sock(src.sock) {}

client::~client() {}

client &client::operator=(const client &src) {
	this->sock = src.sock;
	return (*this);
}