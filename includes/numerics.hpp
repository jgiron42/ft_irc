//
// Created by Joachim GIRON on 8/21/21.
//

#ifndef FT_IRC_NUMERICS_HPP
#define FT_IRC_NUMERICS_HPP

#define     ERR_NOSUCHNICK 				401
#define     ERR_NOSUCHSERVER 			402
#define     ERR_NOSUCHCHANNEL 			403
#define     ERR_CANNOTSENDTOCHAN		404
#define     ERR_TOOMANYCHANNELS 		405
#define     ERR_WASNOSUCHNICK 			406
#define     ERR_TOOMANYTARGETS 			407
#define     ERR_NOORIGIN 				409
#define     ERR_NORECIPIENT 			411
#define     ERR_NOTEXTTOSEND 			412
#define     ERR_NOTOPLEVEL 				413
#define     ERR_WILDTOPLEVEL 			414
#define     ERR_UNKNOWNCOMMAND 			421
#define     ERR_NOMOTD 					422
#define     ERR_NOADMININFO 			423
#define     ERR_FILEERROR 				424
#define     ERR_NONICKNAMEGIVEN 		431
#define     ERR_ERRONEUSNICKNAME		432
#define     ERR_NICKNAMEINUSE 			433
#define     ERR_NICKCOLLISION 			436
#define     ERR_USERNOTINCHANNEL		441
#define     ERR_NOTONCHANNEL 			442
#define     ERR_USERONCHANNEL 			443
#define     ERR_NOLOGIN 				444
#define     ERR_SUMMONDISABLED 			445
#define     ERR_USERSDISABLED 			446
#define     ERR_NOTREGISTERED 			451
#define     ERR_NEEDMOREPARAMS 			461
#define     ERR_ALREADYREGISTRED		462
#define     ERR_NOPERMFORHOST 			463
#define     ERR_PASSWDMISMATCH 			464
#define     ERR_YOUREBANNEDCREEP		465
#define     ERR_KEYSET 					467
#define     ERR_CHANNELISFULL 			471
#define     ERR_UNKNOWNMODE 			472
#define     ERR_INVITEONLYCHAN 			473
#define     ERR_BANNEDFROMCHAN 			474
#define     ERR_BADCHANNELKEY 			475
#define     ERR_NOPRIVILEGES 			481
#define     ERR_CHANOPRIVSNEEDED		482
#define     ERR_CANTKILLSERVER 			483
#define     ERR_NOOPERHOST 				491
#define     ERR_UMODEUNKNOWNFLAG		501
#define     ERR_USERSDONTMATCH 			502

#define     RPL_NONE					300
#define     RPL_USERHOST				302
#define     RPL_ISON					303
#define     RPL_AWAY					301
#define     RPL_UNAWAY					305
#define     RPL_NOWAWAY					306
#define     RPL_WHOISUSER				311
#define     RPL_WHOISSERVER				312
#define     RPL_WHOISOPERATOR			313
#define     RPL_WHOISIDLE				317
#define     RPL_ENDOFWHOIS				318
#define     RPL_WHOISCHANNELS			319
#define     RPL_WHOWASUSER				314
#define     RPL_ENDOFWHOWAS				369
#define     RPL_LISTSTART				321
#define     RPL_LIST					322
#define     RPL_LISTEND					323
#define     RPL_CHANNELMODEIS			324
#define     RPL_NOTOPIC					331
#define     RPL_TOPIC					332
#define     RPL_INVITING				341
#define     RPL_SUMMONING				342
#define     RPL_VERSION					351
#define     RPL_WHOREPLY				352
#define     RPL_ENDOFWHO				315
#define     RPL_NAMREPLY				353
#define     RPL_ENDOFNAMES				366
#define     RPL_LINKS					364
#define     RPL_ENDOFLINKS				365
#define     RPL_BANLIST					367
#define     RPL_ENDOFBANLIST			368
#define     RPL_INFO					371
#define     RPL_ENDOFINFO				374
#define     RPL_MOTDSTART				375
#define     RPL_MOTD					372
#define     RPL_ENDOFMOTD				376
#define     RPL_YOUREOPER				381
#define     RPL_REHASHING				382
#define     RPL_TIME					391
#define     RPL_USERSSTART				392
#define     RPL_USERS					393
#define     RPL_ENDOFUSERS				394
#define     RPL_NOUSERS					395
#define     RPL_TRACELINK				200
#define     RPL_TRACECONNECTING			201
#define     RPL_TRACEHANDSHAKE			202
#define     RPL_TRACEUNKNOWN			203
#define     RPL_TRACEOPERATOR			204
#define     RPL_TRACEUSER				205
#define     RPL_TRACESERVER				206
#define     RPL_TRACENEWTYPE			208
#define     RPL_TRACELOG				261
#define     RPL_STATSLINKINFO			211
#define     RPL_STATSCOMMANDS			212
#define     RPL_STATSCLINE				213
#define     RPL_STATSNLINE				214
#define     RPL_STATSILINE				215
#define     RPL_STATSKLINE				216
#define     RPL_STATSYLINE				218
#define     RPL_ENDOFSTATS				219
#define     RPL_STATSLLINE				241
#define     RPL_STATSUPTIME				242
#define     RPL_STATSOLINE				243
#define     RPL_STATSHLINE				244
#define     RPL_UMODEIS					221
#define     RPL_LUSERCLIENT				251
#define     RPL_LUSEROP					252
#define     RPL_LUSERUNKNOWN			253
#define     RPL_LUSERCHANNELS			254
#define     RPL_LUSERME					255
#define     RPL_ADMINME					256
#define     RPL_ADMINLOC1				257
#define     RPL_ADMINLOC2				258
#define     RPL_ADMINEMAIL				259


char **singleton(){
	char (*array)[502];
	array[ERR_NOSUCHNICK] = "<nickname> :No such nick/channel";
	array[ERR_NOSUCHSERVER] = "<server name> :No such server";
	array[ERR_NOSUCHCHANNEL] = "<channel name> :No such channel";
	array[ERR_CANNOTSENDTOCHAN] = "<channel name> :Cannot send to channel";
	array[ERR_TOOMANYCHANNELS] = "<channel name> :You have joined too many  channels";
	array[ERR_WASNOSUCHNICK] = "<nickname> :There was no such nickname";
	array[ERR_TOOMANYTARGETS] = "<target> :Duplicate recipients. No message  delivered";
	array[ERR_NOORIGIN] = ":No origin specified";
	array[ERR_NORECIPIENT] = ":No recipient given (<command>)";
	array[ERR_NOTEXTTOSEND] = ":No text to send";
	array[ERR_NOTOPLEVEL] = "<mask> :No toplevel domain specified";
	array[ERR_WILDTOPLEVEL] = "<mask> :Wildcard in toplevel domain";
	array[ERR_UNKNOWNCOMMAND] = "<command> :Unknown command";
	array[ERR_NOMOTD] = ":MOTD File is missing";
	array[ERR_NOADMININFO] = "<server> :No administrative info available";
	array[ERR_FILEERROR] = ":File error doing <file op> on <file>";
	array[ERR_NONICKNAMEGIVEN] = ":No nickname given";
	array[ERR_ERRONEUSNICKNAME] = "<nick> :Erroneus nickname";
	array[ERR_NICKNAMEINUSE] = "<nick> :Nickname is already in use";
	array[ERR_NICKCOLLISION] = "<nick> :Nickname collision KILL";
	array[ERR_USERNOTINCHANNEL] = "<nick> <channel> :They aren't on that channel";
	array[ERR_NOTONCHANNEL] = "<channel> :You're not on that channel";
	array[ERR_USERONCHANNEL] = "<user> <channel> :is already on channel";
	array[ERR_NOLOGIN] = "<user> :User not logged in";
	array[ERR_SUMMONDISABLED] = ":SUMMON has been disabled";
	array[ERR_USERSDISABLED] = ":USERS has been disabled";
	array[ERR_NOTREGISTERED] = ":You have not registered";
	array[ERR_NEEDMOREPARAMS] = "<command> :Not enough parameters";
	array[ERR_ALREADYREGISTRED] = ":You may not reregister";
	array[ERR_NOPERMFORHOST] = ":Your host isn't among the privileged";
	array[ERR_PASSWDMISMATCH] = ":Password incorrect";
	array[ERR_YOUREBANNEDCREEP] = ":You are banned from this server";
	array[ERR_KEYSET] = "<channel> :Channel key already set";
	array[ERR_CHANNELISFULL] = "<channel> :Cannot join channel (+l)";
	array[ERR_UNKNOWNMODE] = "<char> :is unknown mode char to me";
	array[ERR_INVITEONLYCHAN] = "<channel> :Cannot join channel (+i)";
	array[ERR_BANNEDFROMCHAN] = "<channel> :Cannot join channel (+b)";
	array[ERR_BADCHANNELKEY] = "<channel> :Cannot join channel (+k)";
	array[ERR_NOPRIVILEGES] = ":Permission Denied- You're not an IRC operator";
	array[ERR_CHANOPRIVSNEEDED] = "<channel> :You're not channel operator";
	array[ERR_CANTKILLSERVER] = ":You cant kill a server!";
	array[ERR_NOOPERHOST] = ":No O-lines for your host";
	array[ERR_UMODEUNKNOWNFLAG] = ":Unknown MODE flag";
	array[ERR_USERSDONTMATCH] = ":Cant change mode for other users";
	array[RPL_NONE] = "";
	array[RPL_USERHOST] = ":[<reply>{<space><reply>}]";
	array[RPL_ISON] = ":[<nick> {<space><nick>}]";
	array[RPL_AWAY] = "<nick> :<away message>";
	array[RPL_UNAWAY] = ":You are no longer marked as being away";
	array[RPL_NOWAWAY] = ":You have been marked as being away";
	array[RPL_WHOISUSER] = "<nick> <user> <host> * :<real name>";
	array[RPL_WHOISSERVER] = "<nick> <server> :<server info>";
	array[RPL_WHOISOPERATOR] = "<nick> :is an IRC operator";
	array[RPL_WHOISIDLE] = "<nick> <integer> :seconds idle";
	array[RPL_ENDOFWHOIS] = "<nick> :End of /WHOIS list";
	array[RPL_WHOISCHANNELS] = "<nick> :{[@|+]<channel><space>}";
	array[RPL_WHOWASUSER] = "<nick> <user> <host> * :<real name>";
	array[RPL_ENDOFWHOWAS] = "<nick> :End of WHOWAS";
	array[RPL_LISTSTART] = "Channel :Users  Name";
	array[RPL_LIST] = "<channel> <# visible> :<topic>";
	array[RPL_LISTEND] = ":End of /LIST";
	array[RPL_CHANNELMODEIS] = "<channel> <mode> <mode params>";
	array[RPL_NOTOPIC] = "<channel> :No topic is set";
	array[RPL_TOPIC] = "<channel> :<topic>";
	array[RPL_INVITING] = "<channel> <nick>";
	array[RPL_SUMMONING] = "<user> :Summoning user to IRC";
	array[RPL_VERSION] = "<version>.<debuglevel> <server> :<comments>";
	array[RPL_WHOREPLY] = "<channel> <user> <host> <server> <nick>  <H|G>[*][@|+] :<hopcount> <real name>";
	array[RPL_ENDOFWHO] = "<name> :End of /WHO list";
	array[RPL_NAMREPLY] = "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]";
	array[RPL_ENDOFNAMES] = "<channel> :End of /NAMES list";
	array[RPL_LINKS] = "<mask> <server> :<hopcount> <server info>";
	array[RPL_ENDOFLINKS] = "<mask> :End of /LINKS list";
	array[RPL_BANLIST] = "<channel> <banid>";
	array[RPL_ENDOFBANLIST] = "<channel> :End of channel ban list";
	array[RPL_INFO] = ":<string>";
	array[RPL_ENDOFINFO] = ":End of /INFO list";
	array[RPL_MOTDSTART] = ":- <server> Message of the day - ";
	array[RPL_MOTD] = ":- <text>";
	array[RPL_ENDOFMOTD] = ":End of /MOTD command";
	array[RPL_YOUREOPER] = ":You are now an IRC operator";
	array[RPL_REHASHING] = "<config file> :Rehashing";
	array[RPL_TIME] = "<server> :<string showing server's local time>";
	array[RPL_USERSSTART] = ":UserID   Terminal  Host";
	array[RPL_USERS] = ":%-8s %-9s %-8s";
	array[RPL_ENDOFUSERS] = ":End of users";
	array[RPL_NOUSERS] = ":Nobody logged in";
	array[RPL_TRACELINK] = "Link <version & debug level> <destination>  <next server>";
	array[RPL_TRACECONNECTING] = "Try. <class> <server>";
	array[RPL_TRACEHANDSHAKE] = "H.S. <class> <server>";
	array[RPL_TRACEUNKNOWN] = "???? <class> [<client IP address in dot form>]";
	array[RPL_TRACEOPERATOR] = "Oper <class> <nick>";
	array[RPL_TRACEUSER] = "User <class> <nick>";
	array[RPL_TRACESERVER] = "Serv <class> <int>S <int>C <server>  <nick!user|*!*>@<host|server>";
	array[RPL_TRACENEWTYPE] = "<newtype> 0 <client name>";
	array[RPL_TRACELOG] = "File <logfile> <debug level>";
	array[RPL_STATSLINKINFO] = "<linkname> <sendq> <sent messages>  <sent bytes> <received messages>  <received bytes> <time open>";
	array[RPL_STATSCOMMANDS] = "<command> <count>";
	array[RPL_STATSCLINE] = "C <host> * <name> <port> <class>";
	array[RPL_STATSNLINE] = "N <host> * <name> <port> <class>";
	array[RPL_STATSILINE] = "I <host> * <host> <port> <class>";
	array[RPL_STATSKLINE] = "K <host> * <username> <port> <class>";
	array[RPL_STATSYLINE] = "Y <class> <ping frequency> <connect  frequency> <max sendq>";
	array[RPL_ENDOFSTATS] = "<stats letter> :End of /STATS report";
	array[RPL_STATSLLINE] = "L <hostmask> * <servername> <maxdepth>";
	array[RPL_STATSUPTIME] = ":Server Up %d days %d:%02d:%02d";
	array[RPL_STATSOLINE] = "O <hostmask> * <name>";
	array[RPL_STATSHLINE] = "H <hostmask> * <servername>";
	array[RPL_UMODEIS] = "<user mode string>";
	array[RPL_LUSERCLIENT] = ":There are <integer> users and <integer>  invisible on <integer> servers";
	array[RPL_LUSEROP] = "<integer> :operator(s) online";
	array[RPL_LUSERUNKNOWN] = "<integer> :unknown connection(s)";
	array[RPL_LUSERCHANNELS] = "<integer> :channels formed";
	array[RPL_LUSERME] = ":I have <integer> clients and <integer>   servers";
	array[RPL_ADMINME] = "<server> :Administrative info";
	array[RPL_ADMINLOC1] = ":<admin info>";
	array[RPL_ADMINLOC2] = ":<admin info>";
	array[RPL_ADMINEMAIL] = ":<admin info>";
	return(array);
}

#endif //FT_IRC_NUMERICS_HPP
