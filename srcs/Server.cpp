#include "Server.hpp"
#include "command.hpp"
#include "commands.hpp"
#include "parse_struct.hpp"
message *parse_msg(std::string str);

server::server(void) :  clients(), fds(), sock(socket(AF_INET, SOCK_STREAM, 0)){ // syscall
	if (this->sock == -1)
		throw syscall_failure(strerror(errno));
	std::cout << "server created" << std::endl;
	struct sockaddr_in sin = {};
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	if(bind(sock, (sockaddr *) &sin, sizeof sin) == -1) // syscall
		throw syscall_failure(strerror(errno));
	if(listen(sock, MAX_CLIENT) == -1) // syscall
		throw syscall_failure(strerror(errno));
	this->fds.clear();
	this->fds.push_back((struct pollfd){.fd = sock, .events = POLLIN});
	if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1) // syscall
		throw syscall_failure(strerror(errno));
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
	int tmp;
	struct sockaddr_in csin = {};
	socklen_t sinsize = sizeof csin;
	char buf[10];
	int ret;

	ret = poll(this->fds.begin().operator->(), this->fds.size(), -1); // syscall
	if (ret == -1)
		throw syscall_failure(strerror(errno));
	if (ret == 0)
	{} // do something
	for (size_t i = 0; i < this->fds.size(); i++)
	{
		if (this->fds[i].revents & POLLIN)

		{
			if (this->fds[i].fd != this->sock)
			{
				if((ret = recv(this->fds[i].fd, buf, 10, 0)) >  0) // syscall
					this->clients[this->fds[i].fd].bufappend(buf, ret);
				if (!ret)
				{
					std::cout << "client " << this->clients.at(this->fds[i].fd).getIP() << " disconnected" << std::endl;
					this->clients.erase(this->fds[i].fd);
					std::vector<struct pollfd>::iterator tmpit = this->fds.begin();
					for (int j = i; j > 0; j--)
						tmpit++;
					this->fds.erase(tmpit);
					break;
				}
				else if (ret > 0)
					this->dispatch(this->clients[this->fds[i].fd]);
				else
					throw syscall_failure(strerror(errno));
			}
			else
				if ((tmp = accept(sock, (sockaddr *)&csin, &sinsize)) >= 0) // syscall
				{
					this->clients.insert(std::make_pair(tmp, client(tmp)));
					this->fds.push_back((struct pollfd){.fd = tmp, .events = POLLIN});
					this->clients.at(tmp).setIP(std::string(inet_ntoa(csin.sin_addr)));
				}
				else
					throw syscall_failure(strerror(errno));
		}
		else if (this->fds[i].revents & POLLOUT && !this->clients[this->fds[i].fd].to_send.empty())
			{
				if (send(this->fds[i].fd, this->clients[this->fds[i].fd].to_send.front().data(), this->clients[this->fds[i].fd].to_send.front().length(), 0) == -1)  //syscall
					throw syscall_failure(strerror(errno));
				this->clients[this->fds[i].fd].to_send.pop_front();
			}
		else if (this->fds[i].revents & POLLHUP || this->fds[i].revents & POLLNVAL || this->fds[i].revents & POLLERR)
		{
//			this->fds[i]
//			this->clients.erase(this->fds[i].fd);
//			std::vector<struct pollfd>::iterator tmpit = this->fds.begin();
//			for (int j = 0; j <= i; i++, j++);
//			std::cout << this->fds.size() << std::endl;
//			this->fds.erase(tmpit);
//			std::cout << this->fds.size() << std::endl;
			std::cout << this->fds[i].fd << " error!!!" << std::endl;
			break;
		}
		this->fds[i].revents = 0;
		this->fds[i].events = (!this->clients[this->fds[i].fd].to_send.empty() * POLLOUT) | POLLIN;
	}
}

void server::dispatch(client &c) {
	std::string str;

	while ((str = c.popLine()) != "\n" && !str.empty())
	{
		std::cout << "From " << c.getIP() << " >> " << str;
		message *parse = parse_msg(str);
		std::cout << "command: " << parse->command_str << std::endl;
		command *com = get_command(parse->command_str)(c, *this);
		com->name = parse->command_str;
		com->parse(*parse);
		com->execute();
		delete com;
		delete parse;
	}
}
