#include "Server.hpp"

Server::Server(void) : sock(socket(AF_INET, SOCK_STREAM, 0)), fds(), clients() {
	struct sockaddr_in sin = {};
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
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
				if((ret = recv(this->fds[i].fd, buf, 10, 0)) >  0)
//				while((ret = recv(this->fds[i].fd, buf, 10, 0)) >  0)
					this->clients[this->fds[i].fd].bufappend(buf, ret);
				std::string stmp = this->clients[this->fds[i].fd].popLine();
				if (!ret)
				{
					this->clients.erase(this->fds[i].fd);
					std::vector<struct pollfd>::iterator tmpit = this->fds.begin();
					for (int j = i; j > 0; j--)
						tmpit++;
					this->fds.erase(tmpit);
					std::cout << "client disconnected" << std::endl;
					break;
				}
				else
					this->dispatch(this->clients[this->fds[i].fd]);
			}
			else
				if ((tmp = accept(sock, (sockaddr *)&csin, &sinsize)) > 0)
//				while((tmp = accept(sock, (sockaddr *)&csin, &sinsize)) > 0)
				{
					this->clients.insert(std::make_pair(tmp, client(tmp)));
					this->fds.push_back((struct pollfd){.fd = tmp, .events = POLLIN});
				}
		}
		else if (this->fds[i].revents & POLLOUT && !this->clients[this->fds[i].fd].to_send.empty())
//			 (!this->clients[this->fds[i].fd].to_send.empty())
			{
				send(this->fds[i].fd, this->clients[this->fds[i].fd].to_send.front().data(), this->clients[this->fds[i].fd].to_send.front().length(), 0);
				this->clients[this->fds[i].fd].to_send.pop_front();
			}
//		else if (this->fds[i].revents & POLLHUP || this->fds[i].revents & POLLNVAL || this->fds[i].revents & POLLERR)
//		{
//			this->clients.erase(this->fds[i].fd);
//			std::vector<struct pollfd>::iterator tmpit = this->fds.begin();
//			for (int j = 0; j <= i; i++, j++);
//			std::cout << this->fds.size() << std::endl;
//			this->fds.erase(tmpit);
//			std::cout << this->fds.size() << std::endl;
//			break;
//		}
		this->fds[i].revents = 0;
		this->fds[i].events = (!this->clients[this->fds[i].fd].to_send.empty() * POLLOUT) | POLLIN;
	}
}

void Server::dispatch(client &c) {
	std::string command;

	while ((command = c.popLine()) != "")
	{
		if (command == "zbeub\n")
			c.send("-> zboub\n");
		//parsing
	}
}