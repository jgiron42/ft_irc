#include "Server.hpp"

Server::Server(void) : sock(socket(AF_INET, SOCK_STREAM, 0)) {
	struct sockaddr_in sin = {
			.sin_addr.s_addr = htonl(INADDR_ANY),
			.sin_family = AF_INET,
			.sin_port = htons(PORT)
	};
	if(bind(sock, (sockaddr *) &sin, sizeof sin) == -1)
		throw std::exception();
	if(listen(sock, MAX_CLIENT) == -1)
		throw std::exception();
}

Server::Server(const Server &src) : sock(src.sock) {}

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

	while((tmp = accept(sock, (sockaddr *)&csin, &sinsize)) > 0)
		this->clients.insert(std::make_pair(tmp, client(tmp)));
}