#include "channel.hpp"

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