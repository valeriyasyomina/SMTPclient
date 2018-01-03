#include "smtp_client.h"

static int client_running = 1;
static int watch_directory = 0;
static int file_descriptor = 0;
static mqd_t mq;

void signal_handler(int signum)
{	
	client_running = 0;	
    free_resources(watch_directory, file_descriptor, mq);
}

int start_smtp_client(struct smtp_client_input_data input_data)
{
	signal(SIGINT, signal_handler);

    if (!input_data.new_directory_name)
		return ERROR_DIR_NAME;

    if (!input_data.cur_directory_name)
		return ERROR_DIR_NAME;

    int watch_result = add_directory_watch(input_data.new_directory_name, WATCH_FLAGS, &watch_directory, &file_descriptor);
	if (watch_result < 0)
	{
		if (watch_result == WATCH_DIR_RESCRIPTOR_ERROR)
			close(file_descriptor);
		return watch_result;
	}

    mq = mq_open(input_data.logger_fifo_name, input_data.logger_flags);
    CHECK((mqd_t)-1 != mq);

    int result = smtp_client_main_loop(input_data.new_directory_name, input_data.cur_directory_name, file_descriptor, mq,
                                       input_data.attempts_number, input_data.attempts_delay);

    free_resources(watch_directory, file_descriptor, mq);

    return result;
}

void free_resources(int watch_directory, int file_descriptor, mqd_t mq)
{
    send_log_message(mq, 0, "STOP");
    CHECK((mqd_t)-1 != mq_close(mq));
	inotify_rm_watch(file_descriptor, watch_directory);
	close(file_descriptor);
}

int smtp_client_main_loop(char* new_directory_name, char* cur_directory_name, int file_descriptor, mqd_t logger, int attempts_number, int attempts_delay)
{
    printf("SMTP client started\n");
    send_log_message(logger, DEBUG_LEVEL, "SMTP client started");
    send_log_message(logger, DEBUG_LEVEL, "Waitings for incoming letters...");
    while (client_running)
    {
        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(file_descriptor, &fdset);
        if (select(file_descriptor + 1, &fdset, NULL, NULL, NULL) == 1)
        {
           send_log_message(logger, DEBUG_LEVEL, "New letters appeared");
           struct string_list* new_files_names = get_new_files_names(file_descriptor, new_directory_name);
           if (!new_files_names)
           {
               send_log_message(logger, ERROR_LEVEL, "Get new letters names");
               return NULL_DATA;
           }
           send_log_message(logger, DEBUG_LEVEL, "New letters names received");

           struct string_list* cur_files_names = replace_files(new_files_names, new_directory_name, cur_directory_name);
           free_string_list(new_files_names);
           new_files_names = NULL;

           if (!cur_files_names)
           {
               send_log_message(logger, ERROR_LEVEL, "Replace files to cur directory");
               return NULL_DATA;
           }
           send_log_message(logger, DEBUG_LEVEL, "New letters replaced to cur directory");

           struct message_list* messages = parse_files(cur_files_names);
           free_string_list(cur_files_names);
           cur_files_names = NULL;

           if (!messages)
           {
               send_log_message(logger, ERROR_LEVEL, "Parse incoming letters");
               return NULL_DATA;
           }
           send_log_message(logger, DEBUG_LEVEL, "Incoming letters successfully parsed");

           struct domain_info_list* domains_list = create_domain_info_list(messages);
           free_message_list(messages);
           messages = NULL;

           if (!domains_list)
           {
               send_log_message(logger, ERROR_LEVEL, "Create domains list");
               return NULL_DATA;
           }
           send_log_message(logger, DEBUG_LEVEL, "Domains list successfully created");


           int send_messages_result = send_messages(domains_list, mq, attempts_number, attempts_delay);
           free_domain_info_list(domains_list);
           domains_list = NULL;

           clean_directory(cur_directory_name);

           if (send_messages_result < 0)
           {
               send_log_message(logger, ERROR_LEVEL, "Send messges");
               return ERROR_SEND_MESSAGES;
           }
        }
    }
    return 0;
}


void clean_directory(char* dir_name)
{
    struct dirent* ep = NULL;
    DIR* dp = opendir(dir_name);
    if (dp != NULL)
    {
        ep = readdir(dp);
        while (ep != NULL)
        {
            if (strcmp(ep->d_name, PARENT_DIRECTORY) != 0 && strcmp(ep->d_name, CURRENT_DIRECTORY) != 0)
            {
                char dest_file_path[MAX_BUFFER_SIZE];
                bzero(dest_file_path, MAX_BUFFER_SIZE);
                strncpy(dest_file_path, dir_name, strlen(dir_name));
                strcat(dest_file_path, ep->d_name);
                remove(dest_file_path);
            }
            ep = readdir(dp);
        }
    }
    closedir(dp);
}


struct domain_info_list* create_domain_info_list(struct message_list* messages)
{
    if (!messages)
        return NULL;
    struct domain_info_list* domains = NULL;
    struct message_list* cur = messages;
    while (cur)
    {
        domains = process_message(domains, cur->message);
        cur = cur->next;
    }
    return domains;
}

struct domain_info_list* process_message(struct domain_info_list* domains, struct message* message)
{
    if (!message)
        return NULL;
    struct message_headers_list* cur = message->headers;
    struct message_header* from_header = get_header_by_key(message->headers, HEADER_FROM);
    while (cur)
    {
        if (strcmp(cur->header->key, HEADER_FROM) != 0)
        {
            char* domain_name = get_domain_name(cur->header);
            struct domain_info_list* current_domain = get_domain_info_by_name(domains, domain_name);
            struct message* current_message = NULL;
            if (!current_domain)
            {
                struct domain_info* domain = create_domain_info_with_name(domain_name);            
                current_domain = create_domain_info_list_item(domain);
                domains = add_to_domain_info_list(domains, current_domain);
            }            
            current_message = get_message_by_id_from_domain(domains, message->id);
            if (!current_message)
            {
                struct message_header* new_from_header = create_header(from_header->key, from_header->value);
                current_message = create_empty_message();
                set_message_data(current_message, message->data);
                set_message_id(current_message, message->id);
                current_message = add_header_to_message(current_message, new_from_header);

                current_domain->info = add_message_to_domain_info(current_domain->info, current_message);
            }
            struct message_header* new_to_header = create_header(cur->header->key, cur->header->value);
            current_message = add_header_to_message(current_message, new_to_header);

            free(domain_name);
            domain_name = NULL;
        }
        cur = cur->next;
    }
    return domains;
}

struct message_list* parse_files(struct string_list* file_names)
{
    if (!file_names)
        return NULL;
    struct message_list* list = NULL;
    struct string_list* cur = file_names;
    while (cur)
    {
        struct message* message = convert_to_message(cur->value);
        struct message_list* item = create_message_list_item(message);
        list = add_to_message_list(list, item);
        cur = cur->next;
    }
    return list;
}

struct message* convert_to_message(char* file_name)
{
    FILE* file = open_file(file_name, "r");
    if (!file)
    {
        printf("error open file\n");
        return NULL;
    }
    struct message* message = create_empty_message();
    message->id = parse_message_id(file);
    struct message_headers_list* message_headers = parse_message_headers(file);
    message->headers = message_headers;
    char* message_data = read_message_data(file);
    message->data = message_data;

    close_file(file);
    return message;
}

char* parse_message_id(FILE* file)
{
    if (!file)
        return NULL;
    char buffer[MAX_BUFFER_SIZE];

    fgets(buffer, MAX_BUFFER_SIZE, file);
    return remove_new_line_from_buffer(buffer);
}

struct message_headers_list* parse_message_headers(FILE* file)
{
    if (!file)
        return NULL;

    struct message_headers_list* message_headers = NULL;

    char buffer[MAX_BUFFER_SIZE];

    while (fgets(buffer, MAX_BUFFER_SIZE, file) && strlen(buffer) != 1)
    {
        char* buffer_without_nl = remove_new_line_from_buffer(buffer);
        struct message_header* header = message_header_from_string(buffer_without_nl);
        struct message_headers_list* item = create_message_headers_list_item(header);
        message_headers = add_to_message_headers_list(message_headers, item);
        free(buffer_without_nl);
        buffer_without_nl = NULL;
    }
    return message_headers;
}

char* remove_new_line_from_buffer(char* buffer)
{
    if (!buffer)
        return NULL;
    int buffer_length = strlen(buffer);
    if (buffer[buffer_length - 1] != '\n')
        return buffer;

    char* new_buffer = (char*) malloc(buffer_length);
    if (!new_buffer)
        return NULL;
    strncpy(new_buffer, buffer, buffer_length - 1);
    new_buffer[buffer_length - 1] = '\0';
    return new_buffer;
}

char* read_message_data(FILE* file)
{
    if (!file)
        return NULL;

    char* message_data = (char*) malloc(MAX_DATA_SIZE);
    if (!message_data)
        return NULL;

    char symbol;
    int index = 0;

    while ((symbol = fgetc(file)) != EOF)
    {
        message_data[index] = symbol;
        index++;
    }
    message_data[index] = '\0';
    return message_data;
}


struct string_list* replace_files(struct string_list* files, char* src_dir, char* dest_dir)
{
    if (!files || !src_dir || !dest_dir)
        return NULL;

    struct string_list* result_files_names = NULL;
    struct string_list* cur = files;
    int replace_correct = 0;
    while (cur && replace_correct >= 0)
    {
        char src_file_path[MAX_BUFFER_SIZE];
        bzero(src_file_path, MAX_BUFFER_SIZE);
        strncpy(src_file_path, src_dir, strlen(src_dir));
        strcat(src_file_path, cur->value);

        char dest_file_path[MAX_BUFFER_SIZE];
        bzero(dest_file_path, MAX_BUFFER_SIZE);
        strncpy(dest_file_path, dest_dir, strlen(dest_dir));
        strcat(dest_file_path, cur->value);

        replace_correct = rename(src_file_path, dest_file_path);
        if (replace_correct >= 0)
        {
            struct string_list* item = create_string_list_item(dest_file_path);
            result_files_names = add_to_string_list(result_files_names, item);
        }
        cur = cur->next;
    }
    return result_files_names;
}


struct string_list* get_new_files_names(int file_descriptor, char* new_directory_name)
{
    struct string_list* files_names_list = NULL;

    size_t length = 0;
    ioctl(file_descriptor, FIONREAD, &length);

    if (length > 0)
    {
        char buffer[BUFFER_LENGTH];
        bzero(buffer, BUFFER_LENGTH);
        if (read(file_descriptor, buffer, length))
        {
            for (size_t offset = 0; offset < length; )
            {
                struct inotify_event *event = (struct inotify_event *) &buffer[offset];

                if (event->len > 0)
                {
                    // we shall see just created files
                    if (event->mask & IN_CREATE)
                    {
                        printf("File created %s\n", event->name);                 
                        struct string_list* item = create_string_list_item(event->name);
                        files_names_list = add_to_string_list(files_names_list, item);
                    }
                    offset += sizeof(*event) + event->len;
                }
            }
        }
    }
    return files_names_list;
}


// adds watch to directory
// watch_directory_name: directory name
// mask: mask for watch events 
// watch_directory: watch_directory descriptor
// file_descriptor: fd of directory
// returns: error code
int add_directory_watch(char* watch_directory_name, uint32_t mask, int* watch_directory, int* file_descriptor)
{
	*file_descriptor = 0;
	*watch_directory = 0;

	if (!watch_directory_name)
		return ERROR_DIR_NAME;

	*file_descriptor = inotify_init();
	if (*file_descriptor < 0)
		return FILE_DESCRIPTOR_ERROR;

	*watch_directory = inotify_add_watch(*file_descriptor, watch_directory_name, mask);
	if (*watch_directory < 0)
		return WATCH_DIR_RESCRIPTOR_ERROR;

	return 0;
}
