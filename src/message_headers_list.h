#ifndef MESSAGE_HEADER_LIST_H
#define MESSAGE_HEADER_LIST_H

#include "message_header.h"

struct message_headers_list 
{
	struct message_header* header;
	struct message_headers_list* next;
};

struct message_headers_list* create_empty_message_headers_list();
void free_message_headers_list(struct message_headers_list* message_headers_list);
struct message_headers_list* add_to_message_headers_list(struct message_headers_list* list, struct message_headers_list* item);
struct message_headers_list* create_message_headers_list_item(struct message_header* header);
struct message_header* get_header_by_key(struct message_headers_list* list, char* key);

#endif
