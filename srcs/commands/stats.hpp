//
// Created by lejulien on 2/25/22.
//

#ifndef FT_IRC_STATS_HPP
#define FT_IRC_STATS_HPP

#include "commands.hpp"
#include "Server.hpp"
#include <sstream>

class stats_command : public command {
public:
    stats_command(class client &c, class server &s) : command(c, s) {
        this->must_register = false;
        name = "STATS";
        syntax = "[ <query> [ <server> ] ]";
		generate_token();
    }

    void end_stats(std::string query) {
        this->args["stats letter"].push_back(query);
        this->reply_nbr(RPL_ENDOFSTATS);
    }

    void handle_stats(std::string &query) {
        std::ostringstream port;
        port << this->s.info.port;
        switch (query.at(0)) {
            case 'c':
                this->args["host"].push_back(this->s.hostname);
                this->args["port"].push_back(port.str());
                this->reply_nbr(RPL_STATSCLINE);
                break ;
            case 'h':
                this->args["servername"].push_back(SERVERNAME);
                this->reply_nbr(RPL_STATSHLINE);
                break ;
            case 'i':
                this->args["host"].push_back(this->s.hostname);
                this->args["port"].push_back(port.str());
                this->reply_nbr(RPL_STATSILINE);
                break ;
            case 'k':
                std::cout << "show all host banned" << std::endl;
                //Need to handle this later FIX
                break ;
            case 'l':
                this->args["servername"].push_back(SERVERNAME);
                this->args["maxdepth"].push_back("1");
                this->reply_nbr(RPL_STATSLLINE);
                break ;
            //case 'm':
            //    break ;
            //case 'o':
            //      break ;
            //case 'y':
            //      break ;
            //case 'v':
            //      break ;
            default :
                return ;
        }
        end_stats(query);
    }

    void execute() {
        std::string query;
        std::string server;
        this->get_arg("query", query);
        this->get_arg("server", server);

        if (query.empty())
            return ;
        else {
            if (!server.empty() && this->s.hostname.compare(server) != 0) {
                this->reply_nbr(ERR_NOSUCHSERVER);
                return ;
            }
            if (query.length() != 1)
                return ;
            if (server.empty()) {
                end_stats(query);
                return ;
            }
            handle_stats(query);
        }
    }
};

/*
 * Stats message

      Command: STATS
   Parameters: [<query> [<server>]]

   The stats message is used to query statistics of certain server.  If
   <server> parameter is omitted, only the end of stats reply is sent
   back.  The implementation of this command is highly dependent on the
   server which replies, although the server must be able to supply
   information as described by the queries below (or similar).

   A query may be given by any single letter which is only checked by
   the destination server (if given as the <server> parameter) and is
   otherwise passed on by intermediate servers, ignored and unaltered.
   The following queries are those found in the current IRC
   implementation and provide a large portion of the setup information
   for that server.  Although these may not be supported in the same way
   by other versions, all servers should be able to supply a valid reply
   to a STATS query which is consistent with the reply formats currently
   used and the purpose of the query.

   The currently supported queries are:

           c - returns a list of servers which the server may connect
               to or allow connections from;
           h - returns a list of servers which are either forced to be
               treated as leaves or allowed to act as hubs;
           i - returns a list of hosts which the server allows a client
               to connect from;
           k - returns a list of banned username/hostname combinations
               for that server;
           l - returns a list of the server's connections, showing how
               long each connection has been established and the traffic
               over that connection in bytes and messages for each
               direction;
           m - returns a list of commands supported by the server and
               the usage count for each if the usage count is non zero;
           o - returns a list of hosts from which normal clients may
               become operators;
           y - show Y (Class) lines from server's configuration file;
           u - returns a string showing how long the server has been up.

   Numeric Replies:

           ERR_NOSUCHSERVER ok
           RPL_STATSCLINE                  RPL_STATSNLINE
           RPL_STATSILINE                  RPL_STATSKLINE
           RPL_STATSQLINE                  RPL_STATSLLINE
           RPL_STATSLINKINFO               RPL_STATSUPTIME
           RPL_STATSCOMMANDS               RPL_STATSOLINE
           RPL_STATSHLINE                  RPL_ENDOFSTATS

   Examples:

STATS m                         ; check the command usage for the server
                                you are connected to

:Wiz STATS c eff.org            ; request by WiZ for C/N line
                                information from server eff.org

 * */

#endif //FT_IRC_STATS_HPP
