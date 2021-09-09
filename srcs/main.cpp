#include "Server.hpp"
#include <signal.h>

bool running = true;

void	stop(int)
{
	running = false;
}

int main(int , char **)
{
	 server s;

	 signal(SIGTERM, stop);
	 signal(SIGINT, stop);
	 while(running)
		 s.routine();
}
