#include "Server.hpp"

bool running = true;

void	stop(int sig)
{
	running = false;
}

int main(int argc, char **argv)
{
	 Server s;

	 signal(SIGINT, stop);
	 while(running)
		 s.routine();
}
