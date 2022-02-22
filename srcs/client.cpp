#include <unistd.h>
#include "client.hpp"

client::client(server &s) : nickname("*"), sock(-1), end(0), begin(0), channels(), identified(false), last_activity(std::time(NULL)), ping_send(false), s(s), nick_history(), alive(true){
	bzero(this->buf, 512);
}
client::client(int fd, server &s) : nickname("*"), sock(fd), end(0), begin(0), channels(), identified(false), last_activity(std::time(NULL)), ping_send(false), s(s), nick_history(), alive(true){
	bzero(this->buf, 512);
	fcntl(fd, F_SETFL, O_NONBLOCK);
	this->log("new client");
}

client::client(const client &src) : s(src.s){
	*this = src;
}

client::~client() {}

client &client::operator=(const client &src) {
	this->nickname = src.nickname;
	this->nickname_tmp = src.nickname_tmp;
	this->sock = src.sock;
	memcpy(this->buf, src.buf, 512);
	this->begin = src.begin;
	this->end = src.end;
	this->channels = src.channels;
	this->last_activity = src.last_activity;
	this->identified = src.identified;
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

	if (this->end == this->begin)
		return (ret);
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
	if (ret.find('\n') == std::string::npos ||
	ret.find('\n') > (ABS(this->end - this->begin)))
		return ("");
	ret = ret.substr(0, ret.find('\n'));
	this->begin += ret.length() + 1;
	this->begin %= 512;
	return (ret);
}

void client::send(const std::string &str) {
	::log("[" + this->nickname + "](" + this->getIP() + ") => ", str, MSG_OUT);
	this->to_send.push_back(str);
}

std::string client::getIP() const {
	return this->ip;
}

void client::setIP(const std::string &ip) {
	this->ip = ip;
}

void client::pong() {
	this->last_activity = std::time(NULL);
	this->ping_send = false;
}

bool client::try_login() {
	if ((this->password.empty() && !this->s.password.empty()) ||this->nickname_tmp.empty() || this->username.empty())
		return (false);
	else if (this->password == this->s.password)
	{
		this->set_nick(this->nickname_tmp);
		this->identified = true;
		return (true);
	}
	return (true);
}

void client::set_nick(std::string &str) {
	this->s.users.erase(this->nickname);
	this->nickname = str;
	this->nick_history.push_front(str);
	this->s.users[str] = this;
	if (this->nick_history.size() > this->s.history_size)
		this->nick_history.pop_back();
}

void client::join_chan(channel &chan, bool as_op) {
	this->channels[chan.id] = &chan;
	chan.members[this] = as_op;
}

void client::leave_chan(channel &chan) {
	this->channels.erase(chan.id);
	chan.members.erase(this);
}

bool	client::can_see(channel &chan) {
	return (((!chan.private_channel && !chan.secret_channel) || chan.members.count(this) || this->op));
}

void client::log(const std::string &str) {
	::log("[" + this->nickname + "@" + this->hostname + "] ", str, USER_EVENT);
}
