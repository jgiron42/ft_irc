#include "Server.hpp"
#include <signal.h>

bool running = true;

void	stop(int)
{
	running = false;
	write(1, "\b\b", 2);
}

int main(int , char **)
{
	try {
		server s;

		signal(SIGTERM, stop);
		signal(SIGINT,  stop);
		while(running)
			s.routine();
	}
	catch (std::exception &e)
	{
		std::cerr << "fatal error: " << e.what() << std::endl;
	}
}
