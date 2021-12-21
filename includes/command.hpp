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

#include "t_token.hpp"


//extern char **replies;
template <class C>
class token_it;

class command {
public:
	command(client &c, server &s) : replied(false), c(c), s(s) {};
	virtual ~command() {};
	virtual void		parse(message);
	virtual void		execute() {  };
	void reply(std::string command, std::string str);
	void reply_nbr(int nbr);
	std::map<std::string, std::list<std::string> > args;
	std::string name;
protected:
	std::list<struct block> token;
//	std::list<block> token;
	bool replied;
	std::string syntax;
	client &c;
	server &s;
	void parse_recurse (char * p);
	void add_block(int bt, std::string value);
	void add_elem(t_params *p, std::list<block>::iterator it);
	void add_elem_str(std::string, std::list<block>::iterator it);
	void add_list(std::string str, std::list<block>::iterator &it);
};

#include <map>



#endif //FT_IRC_COMMAND_HPP
