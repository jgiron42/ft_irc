//
// Created by Joachim GIRON on 8/23/21.
//

#ifndef FT_IRC_COMMAND_HPP
#define FT_IRC_COMMAND_HPP

#include <string>
#include <list>
#include <map>
#include <exception>
#include "numerics.hpp"
#include "client.hpp"
#include "Server.hpp"
#include "parse_struct.hpp"

//extern char **replies;

class command {
public:
	command(client &c, server &s) : replied(false), client(c), server(s) {};
	void		parse(message);
	virtual void		execute() {  };
	void		reply(int);
	class invalidSyntaxException : std::exception {
		const char * what() const  throw() {
			return ("syntax is invalid");
		}
	};
	class syntaxError : std::exception {
		const char * what() const  throw() {
			return ("syntax error");
		}
	};
	class argumentMissing : std::exception {
		const char * what() const  throw() {
			return ("missing argument");
		}
	};
	std::map<std::string, std::list<std::string> > args;
protected:
	bool replied;
	std::string name;
	std::string syntax;
	client &client;
	server &server;
	void parse_recurse (char **syntax, t_params *p, bool is_optional);
};

#include <map>



#endif //FT_IRC_COMMAND_HPP
