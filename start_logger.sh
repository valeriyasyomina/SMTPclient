#!/bin/bash

logger_file_name="./src/logger.txt"
logger_queue_name="/test_queue"

./src/logger $logger_queue_name $logger_file_name

