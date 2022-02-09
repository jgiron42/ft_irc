//
// Created by Leo JULIEN on 9/02/22.
//

#ifndef FT_IRC_MODE_HPP
#define FT_IRC_MODE_HPP

#include "command.hpp"

class mode_command : public command {
public:
	mode_command(class client &c, class server &s) : command(c, s) {
		name = "mode";
		syntax = "<args> { <args> ' ' }";
		generate_token(std::string(syntax));
	};

    void sort_args(std::map<std::string, std::list< std::string > > &argument) {
        std::string temp;
        int         iter = 0;
        while (this->get_arg("args", temp)) {
            if (temp.empty())
                return ; //maybe throw not enough args
            switch (iter) {
                case 0:
                    if (temp[0] == '#' || temp[0] == '&')
                        argument["channel"].push_back(temp);
                    else
                        argument["user"].push_back(temp);
                    break ;
                case 1:
                    if (temp[0] == '-' || temp[0] == '+') {
                        argument["flags"].push_back(temp.substr(1, temp.length() - 1));
                        continue ;
                    }
                    else
                        argument["limits"].push_back(temp);
                    break ;
                case 2:
                    argument["user"].push_back(temp);
                    break ;
                case 3:
                    argument["banmask"].push_back(temp);
                default:
                    return ;
            }
            iter++;
        }
    }

	void execute() {
        std::map<std::string, std::list< std::string > > arguments;
        sort_args(arguments);
        if (!arguments["channel"].empty()) {
            std::cout << "channel mode " << std::endl;
        }
        else if (!arguments["user"].empty()) {
            std::cout << "user mode" << std::endl;
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

:Angel MODE Angel +i            ; Message from Angel to make themselves
                                invisible.

MODE WiZ -o                     ; WiZ 'deopping' (removing operator
                                status).  The plain reverse of this
                                command ("MODE WiZ +o") must not be
                                allowed from users since would bypass
                                the OPER command.

*/
#endif