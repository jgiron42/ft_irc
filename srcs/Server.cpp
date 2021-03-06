#include "Server.hpp"
#include "command.hpp"
#include "commands.hpp"
#include "parse_struct.hpp"

message *parse_msg(std::string str);

server::server(void) :  clients(), fds(), hostname(SERVERNAME), history_size(0){
	this->log("server created");
	commands_count["AWAY"] = 0;
	commands_count["INVITE"] = 0;
	commands_count["JOIN"] = 0;
	commands_count["KILL"] = 0;
	commands_count["NICK"] = 0;
	commands_count["NAMES"] = 0;
	commands_count["NOTICE"] = 0;
	commands_count["PASS"] = 0;
	commands_count["PONG"] = 0;
	commands_count["PRIVMSG"] = 0;
	commands_count["QUIT"] = 0;
	commands_count["TIME"] = 0;
	commands_count["USER"] = 0;
	commands_count["VERSION"] = 0;
	commands_count["MODE"] = 0;
	commands_count["KICK"] = 0;
	commands_count["PART"] = 0;
	commands_count["TOPIC"] = 0;
	commands_count["LIST"] = 0;
    commands_count["INFO"] = 0;
    commands_count["ADMIN"] = 0;
    commands_count["WHO"] = 0;
    commands_count["OPER"] = 0;
	commands_count["STATS"] = 0;
    commands_count["WALLOPS"] = 0;
}

void server::open_socket(long ip, short port) {
	char *ipstr = inet_ntoa(*(struct in_addr *)&ip);
	this->log(SSTR("opening socket on " << ipstr << " " << port));
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		throw syscall_failure(my_strerror((char *)"socket: ", errno));
	int enable = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
		throw syscall_failure(my_strerror((char *)"setsockopt: ", errno));
	struct sockaddr_in sin = {};
	sin.sin_addr.s_addr = ip;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if(bind(sock, (sockaddr *) &sin, sizeof sin) == -1)
		throw syscall_failure(my_strerror((char *)"bind: ", errno));
	if(listen(sock, MAX_CLIENT) == -1)
		throw syscall_failure(my_strerror((char *)"listen: ", errno));
	this->fds.push_back((struct pollfd){.fd = sock, .events = POLLIN});
	this->sockets.insert(sock);
#ifdef __OSX__
	if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1) // syscall
		throw syscall_failure(my_strerror((char *)"fcntl: ", errno));
#endif
}

void server::open_socket(std::string const &path) {
	this->log("opening unix socket on " + path);
	unlink(path.data());
	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock == -1)
		throw syscall_failure(my_strerror((char *)"socket: ", errno));
	int enable = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
		throw syscall_failure(my_strerror((char *)"setsockopt: ", errno));
	struct sockaddr_un sun = {};
	ft_memcpy((char *)sun.sun_path, (const char *)path.data(), path.length() + 1);
	sun.sun_family = AF_UNIX;
	if(bind(sock, (sockaddr *) &sun, sizeof sun) == -1)
		throw syscall_failure(my_strerror((char *)"bind: ", errno));
	if(listen(sock, MAX_CLIENT) == -1)
		throw syscall_failure(my_strerror((char *)"listen: ", errno));
	this->fds.push_back((struct pollfd){.fd = sock, .events = POLLIN});
	this->sockets.insert(sock);
#ifdef __OSX__
	if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
        throw syscall_failure(my_strerror((char *)"fcntl: ", errno));
#endif
}

server::server(const server &src) : clients(src.clients), fds(src.fds),password(src.password), history_size(src.history_size) {}

server::~server() {
	for (std::vector<struct pollfd>::iterator i = this->fds.begin(); i != this->fds.end(); i++)
		close(i->fd);
	this->log("server destroyed");
}

server &server::operator=(const server &src) {
	this->fds = src.fds;
	this->clients = src.clients;
	this->password = src.password;
	return (*this);
}

void server::routine() {
	int ret;
	time_t now = time(NULL);

	ret = poll(this->fds.begin().operator->(), this->fds.size(), 10);
	if (ret == -1 && errno != EINTR)
		throw syscall_failure(my_strerror((char *)"poll: ", errno));
	if (ret == 0)
	{} // do the flop
	for (size_t i = 0; i < this->fds.size(); i++)
		if (!this->sockets.count(this->fds[i].fd))
			this->routine_client(this->fds[i], now);
		else
			this->routine_sock(this->fds[i]);
}

void server::routine_sock(struct pollfd fd)
{
	int tmp;
	struct sockaddr_in csin = {};
	socklen_t sinsize = sizeof csin;

	if (fd.revents & POLLIN) {
		if ((tmp = accept(fd.fd, (sockaddr *) &csin, &sinsize)) >= 0)
		{
			if (this->fds.size() - this->sockets.size() > MAX_CLIENT)
			{
				this->log("client maximum reached!!!");
				close(tmp);
			}
			else {
				this->clients.insert(std::make_pair(tmp, client(tmp, *this)));
				this->fds.push_back((struct pollfd) {.fd = tmp, .events = POLLIN});
				this->clients.at(tmp).setIP(std::string(inet_ntoa(csin.sin_addr)));
			}
		} else
			throw syscall_failure(my_strerror((char *) "accept: ", errno));
	}
	fd.revents = 0;
	fd.events = POLLIN ;

}

void server::routine_client(struct pollfd &fd, time_t now)
{
	ssize_t ret;
	char buf[10];
	client *current_cli = &this->clients.find(fd.fd)->second;

	if (!this->check_liveness(*current_cli, now))
		return;
	if (fd.revents & POLLIN) {
		if ((ret = recv(fd.fd, buf, 10, 0)) > 0)
		{
			current_cli->bufappend(buf, ret);
			current_cli->pong();
		}
		if (!ret) {
			this->disconnect(fd.fd);
			return;
		} else if (ret > 0)
			this->dispatch(*current_cli);
	}
	if (fd.revents & POLLOUT && !current_cli->to_send.empty()) {
		if (current_cli->to_send.front().empty())
		{
			this->disconnect(current_cli->sock);
			return;
		}
		if (send(fd.fd, current_cli->to_send.front().data(), current_cli->to_send.front().length(),
				 0) == -1)
			throw syscall_failure(my_strerror((char *) "send: ", errno));
		current_cli->to_send.pop_front();
	}
	if (fd.revents & POLLHUP || fd.revents & POLLNVAL ||
			   fd.revents & POLLERR) {
		this->disconnect(fd.fd);
		std::cerr << " error!!!" << std::endl; //TODO
		return;
	}
	fd.revents = 0;
	fd.events = (short)((!current_cli->to_send.empty() * POLLOUT) | POLLIN);
}

void server::dispatch(client &c) {
	std::string str;

    while ((str = c.popLine()) != CRLF && !str.empty())
	{
		::log("[" + c.nickname + "](" + c.getIP() + ") <= ", str, MSG_IN);
		message *parse = parse_msg(str);
#ifdef DEBUGPARSER
		std::cout << "command: |" << parse->command_str << "|" << std::endl;
#endif
		command *com = get_command(parse->command_str)(c, *this);
		try {
			com->name = parse->command_str;
			if (com->must_register && !c.identified)
				com->reply_nbr(ERR_NOTREGISTERED);
			else {
				com->parse(*parse);
				com->execute();
			}
		}
		catch (std::exception &e)
		{
			delete com;
			throw e;
		}
		delete com;
		delete parse;
	}
}

void server::disconnect(int fd) {
	client &c = this->clients.find(fd)->second;
	c.log("disconnected");
	while (!c.channels.empty())
		c.leave_chan(*c.channels.begin()->second);
	this->users.erase(c.nickname);
    this->operators.erase(&c);
	this->clients.erase(fd);
	std::vector<struct pollfd>::iterator tmpit = this->fds.begin();
	while (tmpit != this->fds.end() && tmpit->fd != fd)
		tmpit++;
	if (tmpit->fd == fd)
		this->fds.erase(tmpit);
	close(fd);
}

bool server::check_liveness(client &c, time_t now) {
	if (now - c.last_activity > LIVENESS_TIMEOUT)
	{
		if (now - c.last_activity > PING_TIMEOUT + LIVENESS_TIMEOUT)
		{
			this->disconnect(c.sock);
			return (false);
		}
		if (!c.ping_send)
			send_ping(c);
	}
	return (true);
}

void server::print_info() {
    std::cout << "IP > " << this->info.ip << std::endl;
    std::cout << "host_name > " << this->hostname << std::endl;
    std::cout << "location > " << this->info.location << std::endl;
    std::cout << "port > " << this->info.port << std::endl;
    std::cout << "sid > " << this->info.sid << std::endl;
    std::cout << "Name Location > " << this->info.name_location << std::endl;
    std::cout << "Mail > " << this->info.mail << std::endl;
    std::cout << "Other Info > " << this->info.other_info << std::endl;
    std::cout << "Network Name >" << this->info.network_name << std::endl;
    std::vector<t_client_authorization>::iterator  end(this->info.authorization.end());
    std::vector<t_client_authorization>::iterator  start(this->info.authorization.begin());
    int i = 1;
    while (end != start){
        std::cout << "AUTHORIZATION > " << i << std::endl;
        std::cout << "Host address > "<< start->host_addr << std::endl;
        std::cout << "Password > " << start->password << std::endl;
        std::cout << "Host name > " << start->host_name << std::endl;
        std::cout << "Port > " << start->port << std::endl;
        std::cout << "Classes > " << start->classes << std::endl;
        std::cout << "Host name > " << start->host_name << std::endl;
        std::cout << "Flags > " << start->flags << std::endl;
        start++;
        i++;
    }

}

channel	&server::create_chan(const std::string &name, std::string key = "") {
	this->channels[name] = channel(name);
	channel &chan = this->channels[name];
			chan.log("created");
	if (!key.empty())
		chan.setPass(key);
	return (chan);
}

void server::send_ping(client &c) {
	c.send("PING", this->hostname);
	c.ping_send = true;
}

void server::log(const std::string &str) {
	::log("[" + this->hostname + "] ", str, SRV_EVENT);
}
