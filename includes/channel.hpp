#ifndef FT_IRC_CHANNEL_HPP
#define FT_IRC_CHANNEL_HPP
#include <string>
#include <vector>
#include "client.hpp"

class client;
class channel {
public:
	channel(void);
	channel(std::string id);
	channel(const channel &);
	~channel();
	channel &operator=(const channel &);
private:
	std::string			id;
	std::vector<client *>	members;
	std::vector<client *>	chops;
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