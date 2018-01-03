#!/bin/bash

new_maildir_path="./maildir/new/"
cur_maildir_path="./maildir/cur/"
logger_queue_name="/test_queue"
attemts_number=3
attemts_delay=1

valgrind --log-file="./valgrind_SystemTests.txt" --leak-check=full --show-leak-kinds=all ./client $new_maildir_path $cur_maildir_path $logger_queue_name $attemts_number $attemts_delay

