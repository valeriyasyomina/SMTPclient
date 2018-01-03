#include "logger_process.h"

static mqd_t logger_descriptor;
static char logger_q_name[MAX_LOGGER_MESSAGE_SIZE];
static FILE* logger_file = NULL;

void signal_handler(int signum)
{
    free_resources();
}

int start_logger_process(char* logger_queue_name, char* logger_file_name, int flags, mode_t mode)
{
    signal(SIGINT, signal_handler);
    strncpy(logger_q_name, logger_queue_name, strlen(logger_queue_name));

    int must_stop = 0;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;
    attr.mq_curmsgs = 0;

    /* create the message queue */
    logger_descriptor = mq_open(logger_queue_name, flags, mode, &attr);
    CHECK((mqd_t)-1 != logger_descriptor);


    logger_file = open_file(logger_file_name, "w");
    if (!logger_file)
        return ERROR_CREATE_LOGGER_FILE;

    int logger_result = 0;

    do
    {
        char buffer[MAX_LOGGER_MESSAGE_SIZE];
        unsigned int message_prioritet = 0;
        logger_result = mq_receive(logger_descriptor, buffer, MAX_LOGGER_MESSAGE_SIZE, &message_prioritet);

       // CHECK(logger_result >= 0);

        if (!strncmp(buffer, STOP_LOGGING, strlen(STOP_LOGGING)))
            must_stop = 1;
        else
        {
            printf("%s\n", buffer);
            fprintf(logger_file, "%s", buffer);
        }
    }
    while (!must_stop);

    free_resources();

    return logger_result;
}

void free_resources()
{
    CHECK((mqd_t)-1 != mq_close(logger_descriptor));
    CHECK((mqd_t)-1 != mq_unlink(logger_q_name));

    close_file(logger_file);
}

