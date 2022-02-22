#include <sys/syscall.h>
#include "channel.hpp"
#include <stdlib.h>

channel::channel(void) : id(), members(){}

channel::channel(std::string id) : id(id), members(){
	this->log("created");
}

channel::channel(const channel &src): id(src.id), members() {
	*this = src;
}

channel::channel(client creator) : id(), members(),  password(), topic() {
	int	user_limit = 25;
	int ban_mask = 0;
}

channel::~channel() {
	this->log("destroyed");
}

channel &channel::operator=(const channel &src) {
	this->members = src.members;
	this->id = src.id;
	return (*this);
}

std::string	&channel::getPass() {
	return this->password;
}

void		channel::setPass(std::string &pass) {
	this->password = pass;
}

void		channel::addMember(client c) {
	this->members[&c];
}

void channel::log(const std::string &str) {
	::log("[" + this->id + "] ", str, CHAN_EVENT);
}
