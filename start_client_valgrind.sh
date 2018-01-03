#!/bin/bash

new_maildir_path="/home/lera/Desktop/maildir/new/"
cur_maildir_path="/home/lera/Desktop/maildir/cur/"
logger_queue_name="/test_queue"

valgrind --leak-check=full --show-leak-kinds=all ./src/client $new_maildir_path $cur_maildir_path $logger_queue_name

