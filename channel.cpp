#include "channel.hpp"

channel::channel(void) : members(), id(){}

channel::channel(std::string id) : members(), id(id){}

channel::channel(const channel &src) {
	*this = src;
}

channel::~channel() {}

channel &channel::operator=(const channel &src) {
	this->members = src.members;
	this->id = src.id;
	return (*this);
}