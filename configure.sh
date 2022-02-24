#!/bin/bash

IP=$(hostname -i)
SERVNAME=$(hostname)

cp ircd.back ircd.conf

sed -i "s/YOUR_IP/$IP/g" ircd.conf
sed -i "s/YOUR_SERVNAME/$SERVNAME/g" ircd.conf

make re

echo "servname = $SERVNAME"
echo "IP = $IP"

./ircserv ircd.conf

make clean
