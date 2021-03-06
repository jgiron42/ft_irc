#include <sys/syscall.h>
#include "channel.hpp"
#include <stdlib.h>

channel::channel(void) : id(),
						 topic(),
						 members(),
						 invites(),
						 speakers(),
						 private_channel(0),
						 secret_channel(0),
						 invite_only(0),
						 topic_only_operator(0),
						 no_messages_from_outside(0),
						 moderated(0),
						 user_limit(USER_PER_CHANNEL),
						 ban_mask(0),
						 password(),
						 topic_exist(0)
{}

channel::channel(std::string id) : id(id),
								   topic(),
								   members(),
								   invites(),
								   speakers(),
								   private_channel(0),
								   secret_channel(0),
								   invite_only(0),
								   topic_only_operator(0),
								   no_messages_from_outside(0),
								   moderated(0),
								   user_limit(USER_PER_CHANNEL),
								   ban_mask(0),
								   password(),
								   topic_exist(0)
{}
channel::channel(const channel &src) {
	*this = src;
}

channel::~channel() {}

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
	this->no_messages_from_outside = src.no_messages_from_outside;
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
