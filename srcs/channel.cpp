#include <sys/syscall.h>
#include "channel.hpp"
#include <stdlib.h>

channel::channel(void) : id(), members(), chops(){}

channel::channel(std::string id) : id(id), members(), chops(){}

channel::channel(const channel &src): id(src.id), members(), chops() {
	*this = src;
}

channel::~channel() {}

channel &channel::operator=(const channel &src) {
	this->chops = src.chops;
	this->members = src.members;
	this->id = src.id;
	return (*this);
}

//void channel::send(const std::string &str) {
//	for (std::vector<client *>::iterator i = this->members.begin(); i != this->members.end(); i++)
//		(**i).send(str)
//}