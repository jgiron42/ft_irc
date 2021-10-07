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

#ifndef TOKEN_UTILITY
#define TOKEN_UTILITY
#define ELEM 0
#define OPT  1
#define OPTE 2
#define REP  3
#define REPE 4
#define STR  5
#define CHAR 6
#define OR	 4
#endif

struct block {
	int bloc_type;
	std::string value;
};

//extern char **replies;

class command {
public:
	command(client &c, server &s) : replied(false), c(c), s(s) {};
	virtual ~command() {};
	virtual void		parse(message);
	virtual void		execute() {  };
	void reply(std::string command, std::string str);
	void reply_nbr(int nbr);
	class invalidSyntaxException :public std::exception {
		public:
			invalidSyntaxException() throw() {};
			virtual ~invalidSyntaxException() throw() {};
			const char * what() const  throw() {
				return ("syntax is invalid");
			}
	};
	class syntaxError : public std::exception {
		public:
			syntaxError() throw() {};
			virtual ~syntaxError() throw() {};
			const char * what() const  throw() {
				return ("syntax error");
			}
	};
	class argumentMissing : public std::exception {
		public:
			argumentMissing() throw() {};
			virtual ~argumentMissing() throw() {};
			const char * what() const  throw() {
				return ("missing argument");
			}
	};
	std::map<std::string, std::list<std::string> > args;
	std::string name;
protected:
	std::list<block> token;
	bool replied;
	std::string syntax;
	client &c;
	server &s;
	void parse_recurse (t_params *p);
	void add_block(int bt, std::string value);
	void add_elem(t_params *p, std::list<block>::iterator it);
	void add_elem_str(std::string, std::list<block>::iterator it);
	void add_list(std::string str, std::list<block>::iterator &it);
};

#include <map>



#endif //FT_IRC_COMMAND_HPP
