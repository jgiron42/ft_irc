#include "Server.hpp"
#include <signal.h>
#include "parse_conf.hpp"

bool running = true;

void	stop(int)
{
	running = false;
	write(1, "\b\b", 2);
}

int main(int ac, char **av)
{
    (void)ac;
	try {
        server s;
        if (ac == 2) {
            parse_conf(s, av[1]);
            s.print_info();
        }
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
