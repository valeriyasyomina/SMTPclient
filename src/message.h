#ifndef MESSAGE_H
#define MESSAGE_H

#include "message_headers_list.h"

#define MAX_DATA_SIZE 2048
#define NULL_DATA -1
#define HAS_HEADER 0
#define NOT_HAS_HEADER 1

struct message
{
	char* data;
    char* id;
	struct message_headers_list* headers;
};

struct message* create_empty_message();
struct message* create_message_width_data(char* data);
void set_message_data(struct message* message, char* data);
void set_message_id(struct message* message, char* id);
void free_message(struct message* message);
struct message* add_header_to_message(struct message* message, struct message_header* header);
int compare_message_id(struct message* message, char* id);
struct message_header* get_message_header_by_key(struct message* message, char* header_key);

#endif
