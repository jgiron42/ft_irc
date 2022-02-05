#include "Server.hpp"
#include "command.hpp"
#include "commands.hpp"
#include "parse_struct.hpp"

message *parse_msg(std::string str);

server::server(void) :  clients(), fds(), history_size(0), hostname(SERVERNAME) { // syscall
	this->open_socket(INADDR_ANY, PORT);
	this->open_socket(INADDR_ANY, PORT + 1);
	std::cout << "server created" << std::endl;
}

void server::open_socket(long ip, short port) {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		throw syscall_failure(my_strerror((char *)"socket: ", errno));
	int enable = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) // syscall
		throw syscall_failure(my_strerror((char *)"setsockopt: ", errno));
	struct sockaddr_in sin = {};
	sin.sin_addr.s_addr = htonl(ip);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if(bind(sock, (sockaddr *) &sin, sizeof sin) == -1) // syscall
		throw syscall_failure(my_strerror((char *)"bind: ", errno));
	if(listen(sock, MAX_CLIENT) == -1) // syscall
		throw syscall_failure(my_strerror((char *)"listen: ", errno));
	this->fds.push_back((struct pollfd){.fd = sock, .events = POLLIN});
	this->sockets.insert(sock);
	if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1) // syscall
		throw syscall_failure(my_strerror((char *)"fcntl: ", errno));
}

server::server(const server &src) : clients(src.clients), fds(src.fds),password(src.password), history_size(src.history_size) {}

server::~server() {
	for (std::vector<struct pollfd>::iterator i = this->fds.begin(); i != this->fds.end(); i++)
		close(i->fd);
	std::cout << "server destroyed" << std::endl;
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


	ret = poll(this->fds.begin().operator->(), this->fds.size(), 100); // syscall
	if (ret == -1 && errno != EINTR)
		throw syscall_failure(my_strerror((char *)"poll: ", errno));
	if (ret == 0)
	{} // do something
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
		if ((tmp = accept(fd.fd, (sockaddr *) &csin, &sinsize)) >= 0) // syscall
		{
			if (this->fds.size() - this->sockets.size() > MAX_CLIENT)
			{
				std::cout << "client maximum reached!!!" << std::endl;
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
		if ((ret = recv(fd.fd, buf, 10, 0)) > 0) // syscall
		{
			current_cli->bufappend(buf, ret);
			current_cli->pong();
		}
		if (!ret) {
			this->disconnect(fd.fd);
			return;
		} else if (ret > 0)
			this->dispatch(*current_cli);
		else
			throw syscall_failure(my_strerror((char *) "recv: ", errno));
	}
	if (fd.revents & POLLOUT && !current_cli->to_send.empty()) {
		if (current_cli->to_send.front().empty())
		{
			this->disconnect(current_cli->sock);
			return;
		}
		if (send(fd.fd, current_cli->to_send.front().data(), current_cli->to_send.front().length(),
				 0) == -1)  //syscall
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

	while ((str = c.popLine()) != "\n" && !str.empty())
	{
		std::cout << "[" << c.nickname << "](" << c.getIP() << ") <= " << BLUE << str << WHITE << std::endl;
		message *parse = parse_msg(str);
#ifdef DEBUGPARSER
		std::cout << "command: |" << parse->command_str << "|" << std::endl;
#endif
		command *com = get_command(parse->command_str)(c, *this);
		com->name = parse->command_str;
		if (com->must_register && !c.identified)
			com->reply_nbr(ERR_NOTREGISTERED);
		else {
			com->parse(*parse);
			com->execute();
		}
		delete com;
		delete parse;
	}
}

void server::disconnect(int fd) {
	client &c = this->clients.find(fd)->second;
	std::cout << "[" << c.nickname << "](" << c.getIP() << ") " << RED << "DISCONNECTED" << WHITE << std::endl;
	for (std::map<std::string, channel *>::iterator i = c.channels.begin(); i != c.channels.end(); i++)
		i->second->members.erase(&c);
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
			// kill
			this->disconnect(c.sock);
			return (false);
		}
		if (!c.ping_send)
			send_ping(c);
	}
	return (true);
}

void server::send_ping(client &c) {
	c.send("PING " + this->hostname + "\n"); // multiserver
	c.ping_send = true;
}
