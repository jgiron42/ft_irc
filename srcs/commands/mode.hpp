//
// Created by Leo JULIEN on 9/02/22.
//

#ifndef FT_IRC_MODE_HPP
#define FT_IRC_MODE_HPP

#include "command.hpp"
#include "channel.hpp"

class mode_command : public command {
public:
	mode_command(class client &c, class server &s) : command(c, s) {
		name = "mode";
		syntax = "<args> { <args> ' ' }";
		generate_token(std::string(syntax));
	};

    void sort_args(std::map<std::string, std::list< std::string > > &argument) {
        int         iter = 0;

        for (std::list<std::string>::iterator it = this->args["args"].begin(); it != this->args["args"].end(); it++) {

            if ((*it).empty()) {
                if (iter == 0)
                    this->reply_nbr(ERR_NEEDMOREPARAMS);
                return ;
            }
            switch (iter) {
                case 0:
                    if ((*it).at(0) == '#' || (*it).at(0) == '&')
                        argument["channel"].push_back(*it);
                    else
                        argument["user"].push_back(*it);
                    break ;
                case 1:
                    if ((*it).at(0) == '-' || (*it).at(0) == '+') {
                        argument["flags"].push_back(*it);
                        iter--;
                    }
                    else
                        argument["limits"].push_back(*it);
                    break ;
                case 2:
                    argument["user"].push_back(*it);
                    break ;
                case 3:
                    argument["banmask"].push_back(*it);
                default:
                    return ;
            } 
            iter++;
        }
    }

    void debug_args(std::map<std::string, std::list< std::string> > &arg) {
        std::cout << "ARGUMENT DEBUGING" << std::endl;
        if (!arg["channel"].empty())
        {
            std::cout << "  channel : " << std::endl;
            std::cout << "      - " << arg["channel"].front() << std::endl;
            if (!arg["limits"].empty())
            {
                std::cout << "  limits : " << std::endl;
                std::cout << "      - " << arg["limits"].front() << std::endl;
            }
            if (!arg["user"].empty())
            {
                std::cout << "  user : " << std::endl;
                std::cout << "      - " << arg["user"].front() << std::endl;
            }
            if (!arg["banmask"].empty())
            {
                std::cout << "  banmask : " << std::endl;
                std::cout << "      - " << arg["banmask"].front() << std::endl;
            }
        }
        else {
            if (!arg["user"].empty())
            {
                std::cout << "  user : " << std::endl;
                std::cout << "      - " << arg["user"].front() << std::endl;
            }
        }
        if (!arg["flags"].empty())
        {
            std::cout << "  flags : " << std::endl;
            for (std::list< std::string>::iterator it = arg["flags"].begin(); it != arg["flags"].end(); it++) {
                std::cout << "      - " << *it << std::endl;
            }
        };
    }

    bool is_member_channel(std::string &name, std::string &channel) {
        if (this->s.users[name]) {
            client *to_find = this->s.users[name];
            if (this->s.channels[channel].members.find(to_find) != this->s.channels[channel].members.end())
                return true;
        }
        return false;
    }

    bool is_member(std::string &name) {
        if (this->s.users[name]) {
            return true;
        }
        return false;
    }

    client *get_client(std::string &name) {
        return this->s.users[name];
    }

    void handle_flags(bool op, std::string flags, bool user, std::map<std::string, std::list<std::string> > &arg) {
        for (int i = 0; i < flags.length(); i++)
        {
            if (!user) {
                switch (flags.at(i)) {
                    case 'o':
                        if (!arg["limits"].empty())
                        {
                            if (!is_member(arg["limits"].front())) {
                                this->reply_nbr(ERR_NOSUCHNICK);
                                return ;
                            }

                            if (is_member_channel(arg["limits"].front(), arg["channel"].front())) {
                                if (op)
                                    this->s.channels[arg["channel"].front()].members[get_client(arg["limits"].front())] = true;
                                else
                                    this->s.channels[arg["channel"].front()].members[get_client(arg["limits"].front())] = false;
                            }
                            else{
                                this->reply_nbr(ERR_NOTONCHANNEL);
                                return ;
                            }
                        }
                        break ;
                    case 'p':
                        if (op)
                            this->s.channels[arg["channel"].front()].private_channel = true;
                        else
                            this->s.channels[arg["channel"].front()].private_channel = false;
                        break ;
                    case 's':
                        if (op)
                            this->s.channels[arg["channel"].front()].secret_channel = true;
                        else
                            this->s.channels[args["channel"].front()].secret_channel = false;
                        break ;
                    case 'i':
                        if (op)
                            this->s.channels[args["channel"].front()].invite_only = true;
                        else
                            this->s.channels[args["channel"].front()].invite_only = false;
                        break ;
                    case 't':
                        if (op) {
                            this->s.channels[args["channel"].front()].topic_only_operator = 0;
                            this->s.channels[args["channel"].front()].topic = args["limits"].front();
                        }
                        else
                            this->s.channels[args["channel"].front()].topic_only_operator = 1;
                        break ;
                    case 'n':
                        if (op)
                            this->s.channels[args["channel"].front()].server_clients_only = true;
                        else
                            this->s.channels[args["channel"].front()].server_clients_only = false;
                        break ;
                    case 'm':
                        if (op)
                            this->s.channels[args["channel"].front()].moderated = true;
                        else
                            this->s.channels[args["channel"].front()].moderated = false;
                        break ;
                    case 'l':
                        if (op)
                            this->s.channels[args["channel"].front()].user_limit = std::atoi(args["limits"].front().c_str());
                        else
                            this->s.channels[args["channel"].front()].user_limit = 15;
                        break ;
                    case 'b':
                        if (op)
                            this->s.channels[args["channel"].front()].ban_mask = std::atoi(args["limits"].front().c_str());
                        else
                            this->s.channels[args["channel"].front()].moderated = -1;
                        break ;
                    case 'v':
                        // need to talk about it
                        break ;
                    case 'k':
                        if (op){
                            if (!args["limits"].empty()) {
                                this->s.channels[args["channel"].front()].password = args["limits"].front();
                                break ;
                            }
                        }
                        this->s.channels[args["channel"].front()].password = "";
                        break ;
                    default:
                        this->reply_nbr(ERR_UMODEUNKNOWNFLAG);
                        return ;
                }
            } else {
                switch (flags.at(i)) {
                    case 'i':
                        if (op)
                            this->s.users[args["user"].front()]->invisible = true;
                        else
                            this->s.users[args["user"].front()]->invisible = false;
                        break ;
                    case 's':
                        if (op)
                            this->s.users[args["user"].front()]->notices = true;
                        else
                            this->s.users[args["user"].front()]->notices = false;
                    case 'w':
                        if (op)
                            this->s.users[args["user"].front()]->can_see = true;
                        else
                            this->s.users[args["user"].front()]->can_see = false;
                    case 'o':
                        if (op)
                            this->s.users[args["user"].front()]->op = true;
                        else
                            this->s.users[args["user"].front()]->op = false;
                    default:
                        this->reply_nbr(ERR_UMODEUNKNOWNFLAG);
                        return ;
                }
            }
        }
    }

    void channel_mode(std::map<std::string, std::list<std::string> > &arguments) {
        std::list<std::string>::iterator it = arguments["channel"].begin();

        if (this->s.channels.find(*it) != this->s.channels.end()) {
            for (std::list<std::string>::iterator it = arguments["flags"].begin(); it != arguments["flags"].end(); it++) {
                if ((*it).c_str()[0] == '+')
                    handle_flags(true, std::string(&((*it).c_str()[1])), false, arguments);
                else
                    handle_flags(false, std::string(&((*it).c_str()[1])), false, arguments);
            }
        }
        else
            this->reply_nbr(ERR_NOSUCHCHANNEL);
    }

    void user_mode(std::map<std::string, std::list<std::string> > &arguments) {
        std::list<std::string>::iterator it = arguments["user"].begin();

        if (this->s.users.find(*it) != this->s.users.end()) {
            for (std::list<std::string>::iterator it = arguments["flags"].begin(); it != arguments["flags"].end(); it++) {
                if ((*it).c_str()[0] == '+')
                    handle_flags(true, std::string(&((*it).c_str()[1])), true, arguments);
                else
                    handle_flags(false, std::string(&((*it).c_str()[1])), true, arguments);
            }
        }
        else
            this->reply_nbr(ERR_NOSUCHNICK);
    }

	void execute() {
        std::map<std::string, std::list< std::string > > arguments;

        arguments.clear();
        sort_args(arguments);
        debug_args(arguments);
        if (!arguments["channel"].empty())
            channel_mode(arguments);
        else if (!arguments["user"].empty()) {
            user_mode(arguments);
            std::cout << "user mode" << std::endl;
            std::cout << "is_user : " << is_member(arguments["user"].front()) << std::endl;
        }
        else {
            this->reply_nbr(ERR_NEEDMOREPARAMS);
        }
	}
};

/*
4.2.3 Mode message

      Command: MODE

   The MODE command is a dual-purpose command in IRC.  It allows both
   usernames and channels to have their mode changed.  The rationale for
   this choice is that one day nicknames will be obsolete and the
   equivalent property will be the channel.

   When parsing MODE messages, it is recommended that the entire message
   be parsed first and then the changes which resulted then passed on.

4.2.3.1 Channel modes

   Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]
               [<ban mask>]

   The MODE command is provided so that channel operators may change the
   characteristics of `their' channel.  It is also required that servers
   be able to change channel modes so that channel operators may be
   created.

   The various modes available for channels are as follows:

           o - give/take channel operator privileges;
           p - private channel flag;
           s - secret channel flag;
           i - invite-only channel flag;
           t - topic settable by channel operator only flag;
           n - no messages to channel from clients on the outside;
           m - moderated channel;
           l - set the user limit to channel;
           b - set a ban mask to keep users out;
           v - give/take the ability to speak on a moderated channel;
           k - set a channel key (password).

   When using the 'o' and 'b' options, a restriction on a total of three
   per mode command has been imposed.  That is, any combination of 'o'
   and

4.2.3.2 User modes

   Parameters: <nickname> {[+|-]|i|w|s|o}

   The user MODEs are typically changes which affect either how the
   client is seen by others or what 'extra' messages the client is sent.
   A user MODE command may only be accepted if both the sender of the
   message and the nickname given as a parameter are both the same.

   The available modes are as follows:

           i - marks a users as invisible;
           s - marks a user for receipt of server notices;
           w - user receives wallops;
           o - operator flag.

   Additional modes may be available later on.

   If a user attempts to make themselves an operator using the "+o"
   flag, the attempt should be ignored.  There is no restriction,
   however, on anyone `deopping' themselves (using "-o").  Numeric
   Replies:

           ERR_NEEDMOREPARAMS              RPL_CHANNELMODEIS
           ERR_CHANOPRIVSNEEDED            ERR_NOSUCHNICK
           ERR_NOTONCHANNEL                ERR_KEYSET
           RPL_BANLIST                     RPL_ENDOFBANLIST
           ERR_UNKNOWNMODE                 ERR_NOSUCHCHANNEL

           ERR_USERSDONTMATCH              RPL_UMODEIS
           ERR_UMODEUNKNOWNFLAG

   Examples:

           Use of Channel Modes:

MODE #Finnish +im               ; Makes #Finnish channel moderated and
                                'invite-only'.

MODE #Finnish +o Kilroy         ; Gives 'chanop' privileges to Kilroy on
                                channel #Finnish.

MODE #Finnish +v Wiz            ; Allow WiZ to speak on #Finnish.

MODE #Fins -s                   ; Removes 'secret' flag from channel
                                #Fins.

MODE #42 +k oulu                ; Set the channel key to "oulu".

MODE #eu-opers +l 10            ; Set the limit for the number of users
                                on channel to 10.

MODE &oulu +b                   ; list ban masks set for channel.

MODE &oulu +b *!*@*             ; prevent all users from joining.

MODE &oulu +b *!*@*.edu         ; prevent any user from a hostname
                                matching *.edu from joining.

        Use of user Modes:

:MODE WiZ -w                    ; turns reception of WALLOPS messages
                                off for WiZ.

:MODE Angel +i            ; Message from Angel to make themselves
                                invisible.

MODE WiZ -o                     ; WiZ 'deopping' (removing operator
                                status).  The plain reverse of this
                                command ("MODE WiZ +o") must not be
                                allowed from users since would bypass
                                the OPER command.

*/
#endif