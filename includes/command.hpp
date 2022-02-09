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
#include "utils.hpp"

#include "t_token.hpp"


//extern char **replies;
template <class C>
class token_it;

class command {
public:
	command(client &c, server &s) : replied(false), c(c), s(s), must_register(true) {};
	virtual ~command() {};
	virtual void		parse(message);
	virtual void		execute() {  };
	void reply(std::string command, std::string str);
	void reply_nbr(int nbr);
	void send(const std::string &prefix, const std::string &command, const std::string &str, client &dst);
	void send(const client &from, const std::string &command, const std::string &str, client &dst);
	void send(const std::string &command, const std::string &str, client &dst);
	void send(const client &from, const int command, const std::string &str, client &dst);
	void send(const std::string &prefix, const int command, const std::string &str, client &dst);
	void send(const int command, const std::string &str, client &dst);
	void send_numeric(const std::string &prefix, int n, client &dst);
	void send_numeric(const client &from, int n, client &dst);
	void send_numeric(int n, client &dst);
	std::map<std::string, std::list<std::string> > args;
	std::string name;
	bool must_register;
protected:
	std::list<struct block> token;
	bool replied;
	std::string syntax;
	client &c;
	server &s;
	bool		get_arg(const std::string &key, std::string &dst);
	bool		get_arg(const std::string &key, std::list<std::string> &dst);
	void parse_recurse (std::string str);
	void add_block(int bt, std::string value);
	void add_elem(std::string str, std::list<block>::iterator it);
	void add_elem_str(std::string, std::list<block>::iterator it);
	void add_list(std::string str, std::list<block>::iterator &it);
	void token_displayer(std::list<struct block> token);
	void generate_token(std::string syntax);
	void	send_names(channel &chan);

};

#include <map>



#endif //FT_IRC_COMMAND_HPP
