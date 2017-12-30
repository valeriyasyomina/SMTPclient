#ifndef LOGGER_H
#define LOGGER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>

#define MAX_LOGGER_MESSAGE_SIZE 1024

#define ERROR_LOGGER_DESCRIPTOR -1
#define ERROR_LOGGER_LEVEl -2
#define NULL_LOGGER_DATA -3
#define ERROR_SEND_MESSAGE -4
#define ERROR_RECEIVE_MESSAGE -5

#define ERROR_CREATE_LOGGER -6

#define DEBUG_LEVEL 1
#define INFO_LEVEL 2
#define ERROR_LEVEL 3
#define CRITICAL_LEVEL 4

#define DEBUG_LEVEL_CAPTION "[DEBUG] >> "
#define INFO_LEVEL_CAPTION "[INFO] >> "
#define ERROR_LEVEL_CAPTION "[ERROR] >> "
#define CRITICAL_LEVEL_CAPTION "[CRITICAL] >> "

#define CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
            perror(#x); \
            exit(-1); \
        } \
    } while (0) \

int create_logger(char* logger_name, int flags, mode_t mode, struct mq_attr *attr);
int send_log_message(mqd_t logger_descriptor, int logger_level, char* logger_data);
int receive_log_message(mqd_t logger_descriptor, char** buffer, int buffer_length);

#endif // LOGGER_H

