#include "logger.h"

int create_logger(char* logger_name, int flags, mode_t mode, struct mq_attr *attr)
{
    int result = mq_open(logger_name, flags, mode, attr);
    if (result < 0)
        return ERROR_CREATE_LOGGER;   
    return result;
}


int send_log_message(mqd_t logger_descriptor, int logger_level, char* logger_data)
{
    if (logger_descriptor < 0)
        return ERROR_LOGGER_DESCRIPTOR;
    if (logger_level < 0)
        return ERROR_LOGGER_LEVEl;
    if (!logger_data)
        return NULL_LOGGER_DATA;

    char message[MAX_LOGGER_MESSAGE_SIZE];
    bzero(message, MAX_LOGGER_MESSAGE_SIZE);

    switch (logger_level)
    {
        case DEBUG_LEVEL:
            strncpy(message, DEBUG_LEVEL_CAPTION, strlen(DEBUG_LEVEL_CAPTION));
            break;
        case INFO_LEVEL:
            strncpy(message, INFO_LEVEL_CAPTION, strlen(INFO_LEVEL_CAPTION));
            break;
        case ERROR_LEVEL:
            strncpy(message, ERROR_LEVEL_CAPTION, strlen(ERROR_LEVEL_CAPTION));
            break;
        case CRITICAL_LEVEL:
            strncpy(message, CRITICAL_LEVEL_CAPTION, strlen(CRITICAL_LEVEL_CAPTION));
            break;
        default:
            break;
    }
    strcat(message, logger_data);
    strcat(message, "\n");

    int result = mq_send(logger_descriptor, message, strlen(message) + 1, logger_level);
    if (result < 0)
        return ERROR_SEND_MESSAGE;
    return result;
}

int receive_log_message(mqd_t logger_descriptor, char** buffer, int buffer_length)
{
    unsigned int message_prioritet = 0;
    int result = mq_receive(logger_descriptor, *buffer, buffer_length, &message_prioritet);
    if (result < 0)
        return ERROR_RECEIVE_MESSAGE;
    return result;
}


