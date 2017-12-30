#include <stdio.h>
#include "smtp_client.h"

#define ARGS_NUMBER 4
#define ERROR_ARGS_NUMBER -1

int main(int argc, char** argv)
{
    // "/home/lera/Desktop/maildir/new/", "/home/lera/Desktop/maildir/cur/", "/test_queue"
    if (argc != ARGS_NUMBER)
    {
        printf("Usage: ./client <new_dir_path> <cur_dir_path> <logger_queue_name>");
        return ERROR_ARGS_NUMBER;
    }
    int logger_flags = O_WRONLY;
    int res = start_smtp_client(argv[1], argv[2], argv[3], logger_flags);
    printf("SMTP client terminated with code = %d\n", res);
    return res;
}
