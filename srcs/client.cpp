#include <unistd.h>
#include "client.hpp"

client::client(server &s) : s(s),
							channels(),
							password(),
							username(),
							nickname("*"),
							nickname_tmp(),
							nick_history(),
							hostname(),
							realname(),
							ip(),
							away_message(),
							identified(false),
							away(0),
							invisible(0),
							notices(0),
							wallops(0),
							op(0),
							end(0),
							begin(0),
							sock(-1),
							last_activity(std::time(NULL)),
							ping_send(false)
{
	bzero(this->buf, 512);
}
client::client(int fd, server &s)  : s(s),
									 channels(),
									 password(),
									 username(),
									 nickname("*"),
									 nickname_tmp(),
									 nick_history(),
									 hostname(),
									 realname(),
									 ip(),
									 away_message(),
									 identified(false),
									 away(0),
									 invisible(0),
									 notices(0),
									 wallops(0),
									 op(0),
									 end(0),
									 begin(0),
									 sock(fd),
									 last_activity(std::time(NULL)),
									 ping_send(false)
{
	bzero(this->buf, 512);
#ifdef __OSX__
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) // syscall
		throw syscall_failure(my_strerror((char *)"fcntl: ", errno));
#endif

	this->log("new client");
}

client::client(const client &src) : s(src.s){
	*this = src;
}

client::~client() {}

client &client::operator=(const client &src) {
	this->channels = src.channels;
	this->password = src.password;
	this->username = src.username;
	this->nickname = src.nickname;
	this->nickname_tmp = src.nickname_tmp;
	this->nick_history = src.nick_history;
	this->hostname = src.hostname;
	this->realname = src.realname;
	this->ip = src.ip;
	this->away_message = src.away_message;
	this->identified = src.identified;
	this->away = src.away;
	this->invisible = src.invisible;
	this->notices = src.notices;
	this->wallops = src.wallops;
	this->op = src.op;
	memcpy(this->buf, src.buf, 512);
	this->end = src.end;
	this->begin = src.begin;
	this->sock = src.sock;
	this->last_activity = src.last_activity;
	this->ping_send = src.ping_send;
	return (*this);
}

void client::bufappend(const char *str, size_t size) {
	if (this->end + size > (unsigned long)(this->begin + ((this->end >= this->begin) * 512)))
		this->begin = (this->end + size + 1) % 512;
	for (size_t i = 0; i < size; i++)
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
	ret.find('\n') > (unsigned long)(ABS(this->end - this->begin)))
		return ("");
	ret = ret.substr(0, ret.find('\n'));
	this->begin += ret.length() + 1;
	this->begin %= 512;
	return (ret);
}


void client::send(const client &from, int command, const std::string &str) {
	std::string prefix = from.nickname;
	if (!from.username.empty())
		prefix.append("!" + from.username);
	if (!from.username.empty())
		prefix.append("@" + from.hostname);
	this->send(prefix, command, str);
}

void client::send(const client &from, const std::string & command, const std::string &str) {
	std::string prefix = from.nickname;
	if (!from.username.empty())
		prefix.append("!" + from.username);
	if (!from.username.empty())
		prefix.append("@" + from.hostname);
	this->send(prefix, command, str);
}

void client::send(int command, const std::string &str) {
	this->send(this->s.hostname, command, str);
}

void client::send(const std::string & command, const std::string &str) {
	this->send(this->s.hostname, command, str);
}

void client::send(const std::string &prefix, int command, const std::string &params) {
	this->send(":" + prefix + " " + SSTR(command) + " " + this->nickname + " " + params);
}

void client::send(const std::string &prefix, const std::string &command, const std::string &params) {
	this->send(":" + prefix + " " + SSTR(command) + " " + params);
}


void client::send(const std::string &str) {
	::log("[" + this->nickname + "](" + this->getIP() + ") => ", str, MSG_OUT);
	this->to_send.push_back(str + CRLF);
}

void client::notice(channel &c, const std::string &command, const std::string &str) {
	for (std::map<client *, bool>::iterator i = c.members.begin(); i != c.members.end(); i++)
		i->first->send(*this,command,str);
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
	if (this->nick_history.size() > (unsigned long)this->s.history_size)
		this->nick_history.pop_back();
}

void client::join_chan(channel &chan, bool as_op) {
	this->channels[chan.id] = &chan;
	chan.members[this] = as_op;
	chan.log(this->nickname + " joined");
}

void client::leave_chan(channel &chan) {
	this->channels.erase(chan.id);
	chan.members.erase(this);
	chan.log(this->nickname + " left");
	if (chan.members.empty())
	{
		chan.log("destroyed");
		this->s.channels.erase(chan.id);
	}
}

bool	client::can_see(channel &chan) {
	return (((!chan.secret_channel) || chan.members.count(this) || this->op));
}

void client::log(const std::string &str) {
	::log("[" + this->nickname + "@" + this->hostname + "] ", str, USER_EVENT);
}

void client::put_oper_set(){
    this->op = true;
    this->s.operators.insert(this);
}

void client::remove_oper_set(){
    this->op = false;
    this->s.operators.erase(this->s.operators.find(this));
}