#include "Server.hpp"
#include "command.hpp"
#include "commands.hpp"
#include "parse_struct.hpp"

message *parse_msg(std::string str);

server::server(void) :  clients(), fds(), sock(socket(AF_INET, SOCK_STREAM, 0)){ // syscall
	if (this->sock == -1)
		throw syscall_failure(my_strerror((char *)"socket: ", errno));
	int enable = 1;
	if (setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) // syscall
		throw syscall_failure(my_strerror((char *)"setsockopt: ", errno));
	struct sockaddr_in sin = {};
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	if(bind(sock, (sockaddr *) &sin, sizeof sin) == -1) // syscall
		throw syscall_failure(my_strerror((char *)"bind: ", errno));
	if(listen(sock, MAX_CLIENT) == -1) // syscall
		throw syscall_failure(my_strerror((char *)"listen: ", errno));
	this->fds.clear();
	this->fds.push_back((struct pollfd){.fd = sock, .events = POLLIN});
	if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1) // syscall
		throw syscall_failure(my_strerror((char *)"fcntl: ", errno));
	std::cout << "server created" << std::endl;
}

server::server(const server &src) : clients(src.clients), fds(src.fds), sock(src.sock),password(src.password) {}

server::~server() {
	for (std::map<int, client>::iterator i = this->clients.begin(); i != this->clients.end(); i++)
		close(i->first); // syscall
	close(this->sock); // syscall
	std::cout << "server destroyed" << std::endl;
}

server &server::operator=(const server &src) {
	this->sock = src.sock;
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
		if (this->fds[i].fd != this->sock)
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
		if ((tmp = accept(sock, (sockaddr *) &csin, &sinsize)) >= 0) // syscall
		{
			this->clients[tmp] = client(tmp);
			this->fds.push_back((struct pollfd) {.fd = tmp, .events = POLLIN});
			this->clients.at(tmp).setIP(std::string(inet_ntoa(csin.sin_addr)));
		} else
			throw syscall_failure(my_strerror((char *) "accept: ", errno));
	}
	fd.revents = 0;
	fd.events = POLLIN;

}

void server::routine_client(struct pollfd fd, time_t now)
{
	ssize_t ret;
	char buf[10];
	client *current_cli = &this->clients[fd.fd];

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
	} else if (fd.revents & POLLOUT && !current_cli->to_send.empty()) {
		if (send(fd.fd, current_cli->to_send.front().data(), current_cli->to_send.front().length(),
				 0) == -1)  //syscall
			throw syscall_failure(my_strerror((char *) "send: ", errno));
		current_cli->to_send.pop_front();
	} else if (fd.revents & POLLHUP || fd.revents & POLLNVAL ||
			   fd.revents & POLLERR) {
		this->disconnect(fd.fd);
		std::cerr << " error!!!" << std::endl;
		return;
	}
	fd.revents = 0;
	fd.events = (short)((!current_cli->to_send.empty() * POLLOUT) | POLLIN);
}

void server::dispatch(client &c) {
	std::string str;

	while ((str = c.popLine()) != "\n" && !str.empty())
	{
		std::cout << "From " << c.getIP() << " >> " << str;
		message *parse = parse_msg(str);
		std::cout << "command: |" << parse->command_str << "|" << std::endl;
		command *com = get_command(parse->command_str)(c, *this);
		com->name = parse->command_str;
		com->parse(*parse);
		com->execute();
		delete com;
		delete parse;
	}
}

void server::disconnect(int fd) {
	std::string ip = this->clients[fd].getIP();
	this->clients.erase(fd);
	std::vector<struct pollfd>::iterator tmpit = this->fds.begin();
	while (tmpit != this->fds.end() && tmpit->fd != fd)
		tmpit++;
	if (tmpit->fd == fd)
		this->fds.erase(tmpit);
	close(fd);
	std::cout << "client " << ip << " disconnected" << std::endl;
}

bool server::check_liveness(client &c, time_t now) {
//	std::cout << now << std::endl;
//	std::cout << c.last_activity << std::endl;
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
	// send ping message
	std::cout << "PING" << std::endl;
	c.ping_send = true;
}
