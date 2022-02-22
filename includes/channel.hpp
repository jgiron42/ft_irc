#ifndef FT_IRC_CHANNEL_HPP
#define FT_IRC_CHANNEL_HPP
#include <string>
#include <vector>
#include <set>
#include <map>
#include "client.hpp"
#include "utils.hpp"
#define USER_PER_CHANNEL 25
class client;
class server;
class channel {
public:
	channel(void);
	channel(std::string id);
	channel(const channel &);
	channel(client);
	~channel();
	channel &operator=(const channel &);
	std::string	&getPass();
	void		setPass(std::string	&);
	void		addMember(client);
	void	log(const std::string &);
	std::string			id;
	std::string			topic;
	std::map<client *, bool>	members; // the bool indicate if the member is a chop
	std::set<std::string> invites;
	std::set<std::string> speakers;
	bool 				private_channel : 1;
	bool 				secret_channel : 1;
	bool 				invite_only : 1;
	bool 				topic_only_operator : 1;
	bool				server_clients_only : 1;
	bool				moderated : 1;
	int					user_limit;
	int 				ban_mask;
	std::string 		password;
};


#endif //FT_IRC_CHANNEL_HPP
