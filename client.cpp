#include <unistd.h>
#include "client.hpp"

client::client() : sock(-1), end(0), begin(0){};
client::client(int fd) : sock(fd), end(0), begin(0){
	fcntl(fd, F_SETFL, O_NONBLOCK);
	std::cout << "new client" << std::endl;
}

client::client(const client &src) : sock(src.sock), end(src.end), begin(src.begin) {
	memcpy(this->buf, src.buf, 512);
}

client::~client() {}

client &client::operator=(const client &src) {
	this->sock = src.sock;
	memcpy(this->buf, src.buf, 512);
	this->begin = src.begin;
	this->end = src.end;
	return (*this);
}

void client::bufappend(const char *str, size_t size) {
	if (this->end + size > this->begin + ((this->end >= this->begin) * 512))
		this->begin = (this->end + size + 1) % 512;
	for (int i = 0; i < size; i++)
	{
		this->buf[this->end] = str[i];
		this->end++;
		if (this->end >= 512)
			this->end = 0;
	}
}

void client::printBuf() {
	if (this->end > this->begin)
		write(1, this->buf + this->begin, this->end - this->begin);
	else
	{
		write(1, this->buf + this->begin, 512 - this->begin);
		write(1, this->buf, this->end);
	}
	std::cout << std::endl;
}