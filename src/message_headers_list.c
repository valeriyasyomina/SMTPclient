#include "message_headers_list.h"
#include <stdlib.h>
#include <string.h>

struct message_headers_list* create_empty_message_headers_list()
{
	struct message_headers_list* list = (struct message_headers_list*) malloc(sizeof(struct message_headers_list));	
	if (!list)
		return NULL;
	list->header = NULL;
	list->next = NULL;
	return list;
}

struct message_header* get_header_by_key(struct message_headers_list* list, char* key)
{
    if (!key)
        return NULL;
    if (!list)
        return NULL;
    struct message_headers_list* cur = list;
    struct message_header* result = NULL;
    int found = 0;
    while (cur && !found)
    {
        if (strcmp(cur->header->key, key) == 0)
        {
            found = 1;
            result = cur->header;
        }
        cur = cur->next;
    }
    return result;
}

struct message_headers_list* create_message_headers_list_item(struct message_header* header)
{
    if (!header)
        return NULL;
    struct message_headers_list* element = (struct message_headers_list*) malloc(sizeof(struct message_headers_list));
    if (!element)
        return NULL;
    element->header = header;
    element->next = NULL;
    return element;
}

void free_message_headers_list(struct message_headers_list* message_headers_list)
{
	if (message_headers_list)
	{
		struct message_headers_list* cur = message_headers_list;
		while (cur)
		{
			cur = message_headers_list->next;
            if (message_headers_list->header)
            {
                free_message_header(message_headers_list->header);
                message_headers_list->header = NULL;
            }
			free(message_headers_list);
			message_headers_list = cur;
		}
		message_headers_list = NULL;
	}
}

struct message_headers_list* add_to_message_headers_list(struct message_headers_list* list, struct message_headers_list* item)
{
    if (!item)
        return NULL;
    if (!list)
        return item;
    item->next = list;
    return item;
}

