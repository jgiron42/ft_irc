//
// Created by Joachim GIRON on 8/25/21.
//

#include <string>
#include <vector>
#include "numerics.hpp"

char replies[512][100] = {
//		[RPL_WELCOME] =	":Welcome to the Internet Relay Network <nickname>!<username>@<hostname>",
//		[RPL_YOURHOST] =	":Your host is <servername>, running version <version>",
//		[RPL_CREATED] =	":This server was created <date>",
//		[RPL_MYINFO] =	":<servername> <version> <available user modes> <available channel modes>",
//		[RPL_BOUNCE] =	":Try server <server name>, port <port number>",
		[ERR_NOSUCHNICK] = "<nickname> :No such nick/channel",
		[ERR_NOSUCHSERVER] = "<server name> :No such server",
		[ERR_NOSUCHCHANNEL] = "<channel name> :No such channel",
		[ERR_CANNOTSENDTOCHAN] = "<channel> :Cannot send to channel",
		[ERR_TOOMANYCHANNELS] = "<channel name> :You have joined too many  channels",
		[ERR_WASNOSUCHNICK] = "<nickname> :There was no such nickname",
		[ERR_TOOMANYTARGETS] = "<target> :Duplicate recipients. No message  delivered",
		[ERR_NOORIGIN] = ":No origin specified",
		[ERR_NORECIPIENT] = ":No recipient given (<command>)",
		[ERR_NOTEXTTOSEND] = ":No text to send",
		[ERR_NOTOPLEVEL] = "<mask> :No toplevel domain specified",
		[ERR_WILDTOPLEVEL] = "<mask> :Wildcard in toplevel domain",
		[ERR_UNKNOWNCOMMAND] = "<command> :Unknown command",
		[ERR_NOMOTD] = ":MOTD File is missing",
		[ERR_NOADMININFO] = "<server> :No administrative info available",
		[ERR_FILEERROR] = ":File error doing <file op> on <file>",
		[ERR_NONICKNAMEGIVEN] = ":No nickname given",
		[ERR_ERRONEUSNICKNAME] = "<nickname> :Erroneus nickname",
		[ERR_NICKNAMEINUSE] = "<nickname> :Nickname is already in use",
		[ERR_NICKCOLLISION] = "<nickname> :Nickname collision KILL",
		[ERR_USERNOTINCHANNEL] = "<nickname> <channel> :They aren't on that channel",
		[ERR_NOTONCHANNEL] = "<channel> :You're not on that channel",
		[ERR_USERONCHANNEL] = "<user> <channel> :is already on channel",
		[ERR_NOLOGIN] = "<user> :User not logged in",
		[ERR_SUMMONDISABLED] = ":SUMMON has been disabled",
		[ERR_USERSDISABLED] = ":USERS has been disabled",
		[ERR_NOTREGISTERED] = ":You have not registered",
		[ERR_NEEDMOREPARAMS] = "<command> :Not enough parameters",
		[ERR_ALREADYREGISTRED] = ":You may not reregister",
		[ERR_NOPERMFORHOST] = ":Your host isn't among the privileged",
		[ERR_PASSWDMISMATCH] = ":Password incorrect",
		[ERR_YOUREBANNEDCREEP] = ":You are banned from this server",
		[ERR_KEYSET] = "<channel> :Channel key already set",
		[ERR_CHANNELISFULL] = "<channel> :Cannot join channel (+l)",
		[ERR_UNKNOWNMODE] = "<char> :is unknown mode char to me",
		[ERR_INVITEONLYCHAN] = "<channel> :Cannot join channel (+i)",
		[ERR_BANNEDFROMCHAN] = "<channel> :Cannot join channel (+b)",
		[ERR_BADCHANNELKEY] = "<channel> :Cannot join channel (+k)",
		[ERR_NOPRIVILEGES] = ":Permission Denied- You're not an IRC operator",
		[ERR_CHANOPRIVSNEEDED] = "<channel> :You're not channel operator",
		[ERR_CANTKILLSERVER] = ":You cant kill a server!",
		[ERR_NOOPERHOST] = ":No O-lines for your host",
		[ERR_UMODEUNKNOWNFLAG] = ":Unknown MODE flag",
		[ERR_USERSDONTMATCH] = ":Cant change mode for other users",
		[RPL_NONE] = "",
		[RPL_USERHOST] = ":[<reply>{<space><reply>}]",
		[RPL_ISON] = ":[<nickname> {<space><nickname>}]",
		[RPL_AWAY] = "<nickname> :<message>",
		[RPL_UNAWAY] = ":You are no longer marked as being away",
		[RPL_NOWAWAY] = ":You have been marked as being away",
		[RPL_WHOISUSER] = "<nickname> <user> <host> * :<real name>",
		[RPL_WHOISSERVER] = "<nickname> <server> :<server info>",
		[RPL_WHOISOPERATOR] = "<nickname> :is an IRC operator",
		[RPL_WHOISIDLE] = "<nickname> <integer> :seconds idle",
		[RPL_ENDOFWHOIS] = "<nickname> :End of /WHOIS list",
		[RPL_WHOISCHANNELS] = "<nickname> :{[@|+]<channel><space>}",
		[RPL_WHOWASUSER] = "<nickname> <user> <host> * :<real name>",
		[RPL_ENDOFWHOWAS] = "<nickname> :End of WHOWAS",
		[RPL_LISTSTART] = "Channel :Users  Name",
		[RPL_LIST] = "<channel> <# visible> :<topic>",
		[RPL_LISTEND] = ":End of /LIST",
		[RPL_CHANNELMODEIS] = "<channel> <mode> <mode params>",
		[RPL_NOTOPIC] = "<channel> :No topic is set",
		[RPL_TOPIC] = "<channel> :<topic>",
		[RPL_INVITING] = "<channel> <nickname>",
		[RPL_SUMMONING] = "<user> :Summoning user to IRC",
		[RPL_VERSION] = "<version>.<debuglevel> <server> :<comments>",
		[RPL_WHOREPLY] = "<channel> <username> <host> <server> <nickname>  <H|G>[*][@|+] :<hopcount> <real name>",
		[RPL_ENDOFWHO] = "<name> :End of /WHO list",
		[RPL_NAMREPLY] = "<channel> :<user_list>",
		[RPL_ENDOFNAMES] = "<channel> :End of /NAMES list",
		[RPL_LINKS] = "<mask> <server> :<hopcount> <server info>",
		[RPL_ENDOFLINKS] = "<mask> :End of /LINKS list",
		[RPL_BANLIST] = "<channel> <banid>",
		[RPL_ENDOFBANLIST] = "<channel> :End of channel ban list",
		[RPL_INFO] = ":<string>",
		[RPL_ENDOFINFO] = ":End of /INFO list",
		[RPL_MOTDSTART] = ":- <servername> Message of the day - ",
		[RPL_MOTD] = ":- <text>",
		[RPL_ENDOFMOTD] = ":End of /MOTD command",
		[RPL_YOUREOPER] = ":You are now an IRC operator",
		[RPL_REHASHING] = "<config file> :Rehashing",
		[RPL_TIME] = "<server> :<time>",
		[RPL_USERSSTART] = ":UserID   Terminal  Host",
		[RPL_USERS] = ":%-8s %-9s %-8s",
		[RPL_ENDOFUSERS] = ":End of users",
		[RPL_NOUSERS] = ":Nobody logged in",
		[RPL_TRACELINK] = "Link <version & debug level> <destination>  <next server>",
		[RPL_TRACECONNECTING] = "Try. <class> <server>",
		[RPL_TRACEHANDSHAKE] = "H.S. <class> <server>",
		[RPL_TRACEUNKNOWN] = "???? <class> [<client IP address in dot form>]",
		[RPL_TRACEOPERATOR] = "Oper <class> <nickname>",
		[RPL_TRACEUSER] = "User <class> <nickname>",
		[RPL_TRACESERVER] = "Serv <class> <int>S <int>C <server>  <nick!user|*!*>@<host|server>",
		[RPL_TRACENEWTYPE] = "<newtype> 0 <client name>",
		[RPL_TRACELOG] = "File <logfile> <debug level>",
		[RPL_STATSLINKINFO] = "<linkname> <sendq> <sent messages>  <sent bytes> <received messages>  <received bytes> <time open>",
		[RPL_STATSCOMMANDS] = "<command> <count>",
		[RPL_STATSCLINE] = "C <host> * <name> <port> <class>",
		[RPL_STATSNLINE] = "N <host> * <name> <port> <class>",
		[RPL_STATSILINE] = "I <host> * <host> <port> <class>",
		[RPL_STATSKLINE] = "K <host> * <username> <port> <class>",
		[RPL_STATSYLINE] = "Y <class> <ping frequency> <connect  frequency> <max sendq>",
		[RPL_ENDOFSTATS] = "<stats letter> :End of /STATS report",
		[RPL_STATSLLINE] = "L <hostmask> * <servername> <maxdepth>",
		[RPL_STATSUPTIME] = ":Server Up %d days %d:%02d:%02d",
		[RPL_STATSOLINE] = "O <hostmask> * <name>",
		[RPL_STATSHLINE] = "H <hostmask> * <servername>",
		[RPL_UMODEIS] = "<user mode string>",
		[RPL_LUSERCLIENT] = ":There are <integer> users and <integer>  invisible on <integer> servers",
		[RPL_LUSEROP] = "<integer> :operator(s) online",
		[RPL_LUSERUNKNOWN] = "<integer> :unknown connection(s)",
		[RPL_LUSERCHANNELS] = "<integer> :channels formed",
		[RPL_LUSERME] = ":I have <integer> clients and <integer>   servers",
		[RPL_ADMINME] = "<server> :Administrative info",
		[RPL_ADMINLOC1] = ":<admin info>",
		[RPL_ADMINLOC2] = ":<admin info>",
		[RPL_ADMINEMAIL] = ":<admin info>"
};