#!/bin/bash

new_maildir_path="./maildir/new/"
cur_maildir_path="./maildir/cur/"
logger_queue_name="/test_queue"
attemps_number=3
attermps_delay=1

./src/client $new_maildir_path $cur_maildir_path $logger_queue_name $attemps_number $attermps_delay

