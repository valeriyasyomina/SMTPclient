#ifndef SMTP_CLIENT_H
#define SMTP_CLIENT_H

#define ERROR_DIR_NAME -1
#define FILE_DESCRIPTOR_ERROR -2
#define WATCH_DIR_RESCRIPTOR_ERROR -3

#define WATCH_FLAGS (IN_CREATE | IN_DELETE)

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUFFER_LENGTH     (16384 * ( EVENT_SIZE + 16 ))

#define MAX_BUFFER_SIZE 1024

#define MIN_ENTITIES_NUMBER 2
#define PARENT_DIRECTORY ".."
#define CURRENT_DIRECTORY "."

#define ERROR_SEND_MESSAGES -5
#define ERROR_CREATE_LOGGER -6

#define LOGGER_FIFO_MODE 0666

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include "message.h"
#include "message_list.h"
#include "string_list.h"
#include "domain_info_list.h"
#include "file.h"
#include "smtp_operation.h"
#include "logger.h"

int start_smtp_client(char* new_directory_name, char* cur_directory_name, char* logger_fifo_name, int logger_flags);
int add_directory_watch(char* watch_directory_name, uint32_t mask, int* watch_directory, int* file_descriptor);
int smtp_client_main_loop(char* new_directory_name, char* cur_directory_name, int file_descriptor, mqd_t logger);
void signal_handler(int signum);
void free_resources(int watch_directory, int file_descriptor, mqd_t mq);

struct string_list* get_new_files_names(int file_descriptor, char* new_directory_name);

struct message_list* parse_files(struct string_list* file_names);
struct message* convert_to_message(char* file_name);
struct message_headers_list* parse_message_headers(FILE* file);
char* parse_message_id(FILE* file);
char* read_message_data(FILE* file);

char* remove_new_line_from_buffer(char* buffer);
struct string_list* replace_files(struct string_list* files, char* src_dir, char* dest_dir);

struct domain_info_list* create_domain_info_list(struct message_list* messages);
struct domain_info_list* process_message(struct domain_info_list* domains, struct message* message);

int get_logger_descriptor(char* logger_name, mode_t mode);

#endif
