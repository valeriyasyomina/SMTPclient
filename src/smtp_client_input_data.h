#ifndef SMTP_CLIENT_INPUT_DATA
#define SMTP_CLIENT_INPUT_DATA

struct smtp_client_input_data
{
    char* new_directory_name;
    char* cur_directory_name;
    int attempts_number;
    int attempts_delay;
    char* logger_fifo_name;
    int logger_flags;
};

#endif // SMTP_CLIENT_INPUT_DATA

