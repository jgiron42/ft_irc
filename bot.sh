#!/bin/sh

HOST=localhost
PORT=1111
PASSWORD=

mkfifo .irc_fifo

(echo  "
NICK bc
USER a b c d
EOF
" && cat .irc_fifo) | nc $HOST $PORT | while read from command message
do
	if [ "$command" = "PRIVMSG" ]
	then
		echo -n "PRIVMSG $(echo $from | tr -d \: | cut -d! -f 1) :"
		echo "$message" | tr -d \:  | bc
	fi
done > .irc_fifo 2>&1

rm .irc_fifo
