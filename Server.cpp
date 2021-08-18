#include "Server.hpp"

Server::Server(void) : sock(socket(AF_INET, SOCK_STREAM, 0)), fds(), clients() {
	struct sockaddr_in sin = {
			.sin_addr.s_addr = htonl(INADDR_ANY),
			.sin_family = AF_INET,
			.sin_port = htons(PORT)
	};
	if(bind(sock, (sockaddr *) &sin, sizeof sin) == -1)
		throw std::exception();
	if(listen(sock, MAX_CLIENT) == -1)
		throw std::exception();
	this->fds.clear();
	this->fds.push_back((struct pollfd){.fd = sock, .events = POLLIN});
	fcntl(sock, F_SETFL, O_NONBLOCK);
}

Server::Server(const Server &src) : sock(src.sock), fds(src.fds), clients(src.clients) {}

Server::~Server() {
	close(this->sock);
}

Server &Server::operator=(const Server &src) {
	this->sock = src.sock;
	return (*this);
}

void Server::routine() {
	int tmp;
	struct sockaddr_in csin = { 0 };
	socklen_t sinsize = sizeof csin;
	char buf[10];
	int ret;


	poll(this->fds.begin().operator->(), this->fds.size(), -1);
	for (size_t i = 0; i < this->fds.size(); i++)
	{
		if (this->fds[i].revents & POLLIN)
		{
			if (this->fds[i].fd != this->sock)
			{
				while((ret = read(this->fds[i].fd, buf, 10)) >  0)
					this->clients[this->fds[i].fd].bufappend(buf, ret);
				this->clients[this->fds[i].fd].printBuf();
			}
			else
				while((tmp = accept(sock, (sockaddr *)&csin, &sinsize)) > 0)
				{
					this->clients.insert(std::make_pair(tmp, client(tmp)));
					this->fds.push_back((struct pollfd){.fd = tmp, .events = POLLIN});
				}
		}
		this->fds[i].revents = 0;
	}
}