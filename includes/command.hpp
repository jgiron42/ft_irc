//
// Created by Joachim GIRON on 8/23/21.
//

#ifndef FT_IRC_COMMAND_HPP
#define FT_IRC_COMMAND_HPP

#include <string>
#include <list>
#include <map>
#include <exception>
#include "client.hpp"
#include "Server.hpp"
#include "parse_struct.hpp"

class command {
public:
	command(client &c, server &s) : client(c), server(s) {};
	void		parse(t_command c);
	void		execute();
	class invalidSyntaxException : std::exception {
		const char * what() const noexcept override {
			return ("syntax is invalid");
		}
	};
	class syntaxError : std::exception {
		const char * what() const noexcept override {
			return ("syntax error");
		}
	};
	class argumentMissing : std::exception {
		const char * what() const noexcept override {
			return ("missing argument");
		}
	};
private:
	std::map<std::string, std::list<std::string> > args;
	std::string name;
	std::string syntax;
	client &client;
	server &server;
	void parse_recurse (char *syntax, t_params p);
};

#include <map>

std::map<std::string, command> a;


#endif //FT_IRC_COMMAND_HPP
