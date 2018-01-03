#include <stdio.h>
#include "smtp_client.h"

#define ARGS_NUMBER 6
#define ERROR_ARGS_NUMBER -1

int main(int argc, char** argv)
{
    if (argc != ARGS_NUMBER)
    {
        printf("Usage: ./client <new_dir_path> <cur_dir_path> <logger_queue_name> <attempts_number> <attempts_delay_sec>");
        return ERROR_ARGS_NUMBER;
    }
    int logger_flags = O_WRONLY;
    struct smtp_client_input_data input_data;
    input_data.new_directory_name = argv[1];
    input_data.cur_directory_name = argv[2];
    input_data.logger_fifo_name = argv[3];
    input_data.attempts_number = atoi(argv[4]);
    input_data.attempts_delay = atoi(argv[5]);
    input_data.logger_flags = logger_flags;
    int res = start_smtp_client(input_data);
    printf("SMTP client terminated with code = %d\n", res);
    return res;
}
