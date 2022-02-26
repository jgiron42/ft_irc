#include "Server.hpp"
#include <signal.h>
#include "parse_conf.hpp"
#include "numerics.hpp"

bool running = true;
// TODO: c++98
void	stop(int)
{
    running = false;
    write(1, "\b\b", 2);
}

void usage(){
    std::cout << "Usage :" << std::endl;
    std::cout << "Not enough arguments" << std::endl;
    std::cout << "./ircserv <port> <password>" << std::endl;
    std::cout << "OR" << std::endl;
    std::cout << "./ircserv <conf file>" << std::endl;
    std::cout << "format of the expected conf file :" << std::endl;
    std::cout << "M:<Server NAME>:<YOUR Internet IP#>:<Geographic Location>:<Port>:<SID>:<Password>:" << std::endl;
    std::cout << "X:<motd_path>" << std::endl;
    std::cout << "A:<Your Name/Location>:<Your E-Mail Addr>:<other info>::<network name>:" << std::endl;
    std::cout << "I:<TARGET Host Addr>:<Password>:<TARGET Hosts NAME>:<Port>:<Class>:<Flags>:" << std::endl;
    std::cout << "O:<TARGET Host NAME>:<Password>:<Nickname>:<Port>:<Class>:<Flags>:" << std::endl;

}

int main(int ac, char **av)
{
    try {
		init_array();
        if (ac != 2 && ac != 3) {
            usage();
            return(1);
        }
        server s;
        if (ac == 2) {
            parse_conf(s, av[1]);
            //s.print_info();
        }
        else{
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
