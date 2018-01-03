#!/bin/bash

new_maildir_path="./maildir/new/"
cur_maildir_path="./maildir/cur/"
logger_queue_name="/test_queue"
attemps_number=3
attermps_delay=1

valgrind --leak-check=full --show-leak-kinds=all ./src/client $new_maildir_path $cur_maildir_path $logger_queue_name

