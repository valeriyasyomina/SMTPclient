#ifndef LOGGER_PROCESS_H
#define LOGGER_PROCESS_H

#include "logger.h"
#include "file.h"
#include <signal.h>

#define ERROR_CREATE_LOGGER_FILE -1
#define MAX_QUEUE_SIZE 1024
#define STOP_LOGGING "STOP"

void signal_handler(int signum);
int start_logger_process(char* logger_file_name, char* logger_queue_name, int flags, mode_t mode);
void free_resources();

#endif // LOGGER_PROCESS_H

