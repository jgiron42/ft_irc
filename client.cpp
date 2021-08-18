#include "client.hpp"

client::client(int fd) : sock(fd) {
	std::cout << "new client" << std::endl;
}

client::client(const client &src) : sock(src.sock) {}

client::~client() {}

client &client::operator=(const client &src) {
	this->sock = src.sock;
	return (*this);
}