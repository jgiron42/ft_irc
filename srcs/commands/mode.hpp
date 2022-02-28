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
		generate_token();
	};

    void sort_args(std::map<std::string, std::list< std::string > > &argument) {
        int         iter = 0;

        for (std::list<std::string>::iterator it = this->args["args"].begin(); it != this->args["args"].end(); it++) {

            if ((*it).empty()) {
                if (iter == 0)
                    this->reply_nbr(ERR_NEEDMOREPARAMS);
                return ;
            }
            switch (iter) { // TODO: un enum serait le bienvenue
                case 0:
                    if (is_channel(*it))
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

    int is_allready_set(char c, bool op, std::string &channel, bool user) {
        if (user)
            return 0;
        switch(c) {
            case 'p':
                if (this->s.channels[channel].private_channel == op) {
                    this->args["channel"].push_back(channel);
                    this->reply_nbr(ERR_KEYSET);
                    return 1;
                }
                break ;
            case 's':
                if (this->s.channels[channel].secret_channel == op) {
                    this->args["channel"].push_back(channel);
                    this->reply_nbr(ERR_KEYSET);
                    return 1;
                }
                break ;
            case 'i':
                if (this->s.channels[channel].invite_only == op) {
                    this->args["channel"].push_back(channel);
                    this->reply_nbr(ERR_KEYSET);
                    return 1;
                }
                break ;
            case 'n':
                if (this->s.channels[channel].no_messages_from_outside == op) {
                    this->args["channel"].push_back(channel);
                    this->reply_nbr(ERR_KEYSET);
                    return 1;
                }
                break ;
            case 'm':
                if (this->s.channels[channel].moderated == op) {
                    this->args["channel"].push_back(channel);
                    this->reply_nbr(ERR_KEYSET);
                    return 1;
                }
                break ;
            default:
                break ;
        }
        return 0;
    }

    void handle_flags(bool op, std::string flags, bool user, std::map<std::string, std::list<std::string> > &arg) {
		std::string str_channel;
		std::string str_limits;

		if (arg.count("channel") && !arg["channel"].empty())
			str_channel = arg["channel"].front();
		if (arg.count("limits") && !arg["limits"].empty())
	        str_limits = arg["limits"].front();
        channel &p_chan = this->s.channels[str_channel];
        if (!user) {
            for(unsigned  long i = 0; i < flags.length(); i++) {
                if (is_allready_set(flags.at(i), op, str_channel, user))
                    continue ;
            }
        }
        for (unsigned long i = 0; i < flags.length(); i++) // TODO: pas beau
        {
            if (!user) {
                switch (flags.at(i)) {
                    case 'o':
                        if (!arg["limits"].empty())
                        {
                            if (!is_member(str_limits))
                                this->reply_nbr(ERR_NOSUCHNICK);
                            if (is_member_channel(str_limits, str_channel)) {
                                if (!op && p_chan.members[get_client(str_limits)] && this->c.nickname.compare(str_limits) == 0) {
                                    p_chan.members[get_client(str_limits)] = op;
                                }
                            }
                            else
                                this->reply_nbr(ERR_NOTONCHANNEL);
                        }
						else
                           this->reply_nbr(ERR_NEEDMOREPARAMS);
                        break ;
                    case 'p':
                        p_chan.private_channel = op;
                        break ;
                    case 's':
                        p_chan.secret_channel = op;
                        break ;
                    case 'i':
                        p_chan.invite_only = op;
                        break ;
                    case 't':
                        p_chan.topic_only_operator = op;
                        break ;
                    case 'n':
                        p_chan.no_messages_from_outside = op;
                        break ;
                    case 'm':
                        p_chan.moderated = op;
                        break ;
                    case 'l':
                        if (op)
                            p_chan.user_limit = std::atoi(str_limits.c_str());
                        else
                            p_chan.user_limit = 15;
                        break ;
                    case 'b':
                        if (op)
                            p_chan.ban_mask = std::atoi(str_limits.c_str());
                        else
                            p_chan.moderated = -1;
                        break ;
                    case 'v':
                        if (!arg["limits"].empty()) {
                            if (!is_member_channel(str_limits, str_channel)) {
                                this->reply_nbr(ERR_NOSUCHNICK);
                                return ;
                            }
                            client *cli = get_client(str_limits);
                            if (op && p_chan.speakers.find(cli->nickname) == p_chan.speakers.end())
                                p_chan.speakers.insert(cli->nickname);
                            if (!op)
                                p_chan.speakers.erase(cli->nickname);

                        }
                        else {
                            if (op && p_chan.speakers.find(this->c.nickname) == p_chan.speakers.end())
                                p_chan.speakers.insert(this->c.nickname);
                            if (!op)
                                p_chan.speakers.erase(this->c.nickname);
                        }
                        break ;
                    case 'k':
                        if (op){
                            if (!arg["limits"].empty()) {
                                p_chan.setPass(str_limits);
                                return ;
                            }
                        }
                        p_chan.password.clear();
                        break ;
                    default:
                        this->reply_nbr(ERR_UMODEUNKNOWNFLAG);
                        return ;
                }
            } else {
                switch (flags.at(i)) {
                    case 'i':
                        this->s.users[arg["user"].front()]->invisible = op;
                        break ;
                    case 's':
                        this->s.users[arg["user"].front()]->notices = op;
                        break ;
                    case 'w':
                        this->s.users[arg["user"].front()]->wallops = op;
                        break ;
                    case 'o':
                        if (this->c.nickname == arg["user"].front() && !op)
                            this->c.remove_oper_set();
                        break ;
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
            if (this->s.channels[*it].members.find(get_client(this->c.nickname)) == this->s.channels[*it].members.end()){
                this->reply_nbr(ERR_NOTONCHANNEL);
                return ;
            }
            if (this->s.channels[*it].members[get_client(this->c.nickname)] == false) {
                this->reply_nbr(ERR_CHANOPRIVSNEEDED);
                return ;
            }
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
        if (this->s.users.find(*it) != this->s.users.end()) { // TODO: c'est mieux d'utiliser map::count
            if (this->c.nickname.compare(arguments["user"].front()) != 0) {
                this->reply_nbr(ERR_USERSDONTMATCH);
                return ;
            }
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

    std::string get_modes(std::string &channel) {
        std::string ret = "+";
        if (this->s.channels[channel].private_channel)
            ret.append("p");
        if (this->s.channels[channel].secret_channel)
            ret.append("s");
        if (this->s.channels[channel].topic_only_operator)
            ret.append("t");
        if (this->s.channels[channel].no_messages_from_outside)
            ret.append("n");
        if (this->s.channels[channel].invite_only)
            ret.append("i");
        if (this->s.channels[channel].moderated)
            ret.append("m");
        return ret;
    }

	void execute() {
        std::map<std::string, std::list< std::string > > arguments;

        arguments.clear();
        sort_args(arguments);
//        debug_args(arguments);
        if (!arguments["channel"].empty() && arguments["flags"].empty()) {
            this->args["channel"].push_back(arguments["channel"].front());
            this->args["mode"].push_back(get_modes(arguments["channel"].front()));
            if (!arguments["limits"].empty())
                this->args["mode params"].push_back(arguments["limits"].front());
            this->reply_nbr(RPL_CHANNELMODEIS);
            return ;
        }
        if (!arguments["channel"].empty()){
            if (this->c.channels[arguments["channel"].front()])
                std::cout << "pass is " << this->c.channels[arguments["channel"].front()]->password << std::endl;
            channel_mode(arguments);}
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

           ERR_NEEDMOREPARAMS              TODO: RPL_CHANNELMODEIS
           ERR_CHANOPRIVSNEEDED            ERR_NOSUCHNICK
           ERR_NOTONCHANNEL                TODO: ERR_KEYSET
           TODO: RPL_BANLIST                     RPL_ENDOFBANLIST
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