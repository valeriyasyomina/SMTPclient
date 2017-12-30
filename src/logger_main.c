#include <stdio.h>
#include "logger_process.h"

#define ARGS_NUMBER 3

#define INVALID_ARGS_NUMBER -1
#define INVALID_LOGGER_RESULT -2

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("Usage: ./logger <logger_queue_name> <logger_file_name>\n");
        return INVALID_ARGS_NUMBER;
    }
    int flags = (O_CREAT | O_RDONLY);
    mode_t mode = 0644;

    printf("Logger started\n");
    int logger_result = start_logger_process(argv[1], argv[2], flags, mode);

    if (logger_result < 0)
    {
        printf("Logger completed with error status %d\n", logger_result);
        return INVALID_LOGGER_RESULT;
    }
    return 0;
}
