#!/bin/bash

make SystemTests

gnome-terminal -x ./start_logger.sh --disable-factory & pid_logger=$!
sleep 1
gnome-terminal -x ./start_client.sh --disable-factory & pid=$!

sleep 2
cp ./maildir/message.txt ./maildir/new/message.txt


