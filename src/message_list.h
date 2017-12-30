#ifndef MESSAGE_LIST_H
#define MESSAGE_LIST_H

#include "message.h"
#include <stdlib.h>

struct message_list
{
    struct message* message;
    struct message_list* next;
};

struct message_list* create_message_list_item(struct message* message);
void free_message_list(struct message_list* list);
struct message_list* add_to_message_list(struct message_list* list, struct message_list* element);
struct message* get_message_by_header_key(struct message_list* list, char* header_key);
struct message* get_message_by_id(struct message_list* list, char* id);

#endif // MESSAGE_LIST_H

