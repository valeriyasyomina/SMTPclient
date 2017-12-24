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

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include "message.h"
#include "string_list.h"
#include "file.h"

int start_smtp_client(char* new_directory_name, char* cur_directory_name);
int add_directory_watch(char* watch_directory_name, uint32_t mask, int* watch_directory, int* file_descriptor);
void smtp_client_main_loop(char* new_directory_name, char* cur_directory_name, int file_descriptor);
char* parse_events(char* new_directory_name, char* buffer, int length);
void signal_handler(int signum);
void free_resources(int watch_directory, int file_descriptor);

struct string_list* get_new_files_names(char* new_directory_name, char* cur_directory_name);

struct message* parse_message(char* file_name);
struct message* read_message(struct message* message, FILE* file);
struct message* reader_message_headers(struct message* message, FILE* file);
