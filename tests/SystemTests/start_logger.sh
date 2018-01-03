#!/bin/bash

logger_file_name="./SystemTests.txt"
logger_queue_name="/test_queue"

./logger $logger_queue_name $logger_file_name

