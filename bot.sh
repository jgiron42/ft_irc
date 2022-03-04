#!/bin/sh
HOST=localhost
PORT=1111
PASSWORD=lol
mkfifo .irc_fifo 2>/dev/null
(echo -n "NICK bc\r\nPASS $PASSWORD\r\nUSER bc bc bc bc\r\n" && cat .irc_fifo) | nc $HOST $PORT | while  read from command to message
do
	[ "$command" = "PRIVMSG" ] && (echo -n "PRIVMSG $(echo $from | tr -d \: | cut -d! -f 1) :" && echo -n "$message\n" | tr -d \: | tr -d '\r' | bc | tr -d '\n' ; echo '\r\n')
done  2>&1 | tee .irc_fifo
rm .irc_fifo
