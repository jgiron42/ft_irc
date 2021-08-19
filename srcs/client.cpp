#include <unistd.h>
#include "client.hpp"

client::client() : sock(-1), end(0), begin(0), channels(){};
client::client(int fd) : sock(fd), end(0), begin(0), channels(){
	fcntl(fd, F_SETFL, O_NONBLOCK);
	std::cout << "new client" << std::endl;
}

client::client(const client &src) : sock(src.sock), end(src.end), begin(src.begin), channels(src.channels) {
	memcpy(this->buf, src.buf, 512);
}

client::~client() {}

client &client::operator=(const client &src) {
	this->sock = src.sock;
	memcpy(this->buf, src.buf, 512);
	this->begin = src.begin;
	this->end = src.end;
	this->channels = src.channels;
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

std::string client::getBufStr() {
	std::string ret = "";

	if (this->end > this->begin)
		ret.append(this->buf + this->begin, this->end - this->begin);
	else
	{
		ret.append( this->buf + this->begin, 512 - this->begin);
		ret.append( this->buf, this->end);
	}
	return(ret);
}

std::string client::popLine() {
	std::string ret;

	ret = getBufStr();
	if (ret.find('\n') == std::string::npos || ret.find('\n') > (ABS(this->end - this->begin)))
		return ("");
	ret = ret.substr(0, ret.find('\n') + 1);
	this->begin += ret.length();
	this->begin %= 512;
	return (ret);
}

void client::send(std::string str) {
	this->to_send.push_back(str);
}