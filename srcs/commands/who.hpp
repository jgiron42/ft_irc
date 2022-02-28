//
// Created by frtalleu on 2/22/22.
//

#ifndef FT_IRC_WHO_HPP
#define FT_IRC_WHO_HPP


#include "command.hpp"

class who_command : public command {
private:

    bool check_op_client(class client &cli, bool op)
    {
        bool op_or_not = cli.op;
        if (op && !op_or_not)
            return true;
        return false;
    }

    void who_reply(class channel &chan, client &cli, bool op){
        if (cli.invisible && check_op_client(cli, op))
            return;
        this->args["channel"].push_front(chan.id);
        this->args["username"].push_front(cli.username);
        this->args["host"].push_front(cli.hostname);
        this->args["server"].push_front(cli.s.hostname);
        this->args["nickname"].push_front(cli.nickname);
        this->args["hopcount"].push_front("1");
        this->args["H|G"].push_front("H");
        if (check_op_client(cli, true))
            this->args["[*][@|+]"].push_front("+");
        else
            this->args["[*][@|+]"].push_front("@");
        this->args["real name"].push_front(cli.realname);
        this->reply_nbr(RPL_WHOREPLY);
    }

    void who_chan(class channel *chan, bool op){
        for(std::map<client *, bool >::iterator i = chan->members.begin(); i != chan->members.end(); i++){
            this->who_reply(*chan, *i->first, op);
        }
    }

    bool match_send(class client &cli, std::string name){
        if (cli.realname == name || cli.nickname == name || cli.s.hostname == name
        || cli.hostname == name)
            return (true);
        return false;
    }

public:
    who_command(class client &c, class server &s) : command(c, s) {
        this->name = "WHO";
        this->syntax = "[ <name> [ <o> ] ]";
		generate_token();
    };

    void execute() {
        std::string name;
        std::string o;
        bool op = false;
        this->get_arg("name", name);
        this->get_arg("o", o);
        if (!o.empty() && o == "o")
            op = true;
        for (std::map<std::string, channel *>::iterator i = c.channels.begin(); i != c.channels.end(); i++){
            if (i->first == name){
                this->who_chan(i->second, op);
                this->args["name"].push_back(name);
                this->reply_nbr(RPL_ENDOFWHO);
                return;
            }
        }
        for (std::map<std::string, channel *>::iterator i = c.channels.begin(); i != c.channels.end(); i++) {
            for (std::map<client *, bool>::iterator j = i->second->members.begin(); j != i->second->members.end(); j++) {
                if (name == "*" || match_send(*j->first, name))
                    who_reply(*i->second, *j->first, op);
            }
        }
        this->args["name"].push_back(name);
        this->reply_nbr(RPL_ENDOFWHO);
    };
};
/*
Command: WHO
        Parameters: [<name> [<o>]]

The WHO message is used by a client to generate a query which returns
a list of information which 'matches' the <name> parameter given by
the client.  In the absence of the <name> parameter, all visible
(users who aren't invisible (user mode +i) and who don't have a
common channel with the requesting client) are listed.  The same
result can be achieved by using a <name> of "0" or any wildcard which
will end up matching every entry possible.

The <name> passed to WHO is matched against users' host, server, real
name and nickname if the channel <name> cannot be found.

If the "o" parameter is passed only operators are returned according
to the name mask supplied.

Numeric Replies:

        ERR_NOSUCHSERVER = "<server name> :No such server",
        RPL_WHOREPLY     = "<channel> <username> <host> <server> <nickname>  <H|G>[*][@|+] :<hopcount> <real name>"
        RPL_ENDOFWHO     = "<name> :End of /WHO list"

        Examples:

WHO *.fi                        ; List all users who match against
"*.fi".

WHO jto* o                      ; List all users with a match against
"jto*" if they are an operator.
*/

#endif //FT_IRC_WHO_HPP
