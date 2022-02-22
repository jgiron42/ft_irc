#include "Server.hpp"
#include <signal.h>
#include "parse_conf.hpp"

bool running = true;
// TODO: c++98
void	stop(int)
{
	running = false;
	write(1, "\b\b", 2);
}

int main(int ac, char **av)
{
    (void)ac;
	try {
        in_addr addr;
        server s;
        if (ac == 2) {
            parse_conf(s, av[1]);
            //s.print_info();
        }
        else if (ac == 3){
            s.open_socket(INADDR_ANY, (short)atoi(av[1]));
            s.password = av[2];
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
