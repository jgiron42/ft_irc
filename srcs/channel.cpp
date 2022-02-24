#include <sys/syscall.h>
#include "channel.hpp"
#include <stdlib.h>

channel::channel(void) : user_limit(USER_PER_CHANNEL){}

channel::channel(std::string id) : id(id), members(), user_limit(USER_PER_CHANNEL){
	this->log("created");
}

channel::channel(const channel &src) {
	*this = src;
}

channel::channel(client creator) : id(), topic(), members(), user_limit(USER_PER_CHANNEL),  password(){
    (void)creator;
}

channel::~channel() {
	this->log("destroyed");
}

channel &channel::operator=(const channel &src) {
	this->id = src.id;
	this->topic = src.topic;
	this->members = src.members;
	this->invites = src.invites;
	this->speakers = src.speakers;
	this->private_channel = src.private_channel;
	this->secret_channel = src.secret_channel;
	this->invite_only = src.invite_only;
	this->topic_only_operator = src.topic_only_operator;
	this->server_clients_only = src.server_clients_only;
	this->moderated = src.moderated;
	this->user_limit = src.user_limit;
	this->ban_mask = src.ban_mask;
	this->password = src.password;
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
