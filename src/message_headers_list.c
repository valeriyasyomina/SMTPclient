#include "message_headers_list.h"
#include <stdlib.h>

struct message_headers_list* create_empty_message_headers_list()
{
	struct message_headers_list* list = (struct message_headers_list*) malloc(sizeof(struct message_headers_list));	
	if (!list)
		return NULL;
	list->header = NULL;
	list->next = NULL;
	return list;
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

struct message_headers_list* add_header_to_list(struct message_headers_list* list, struct message_header* header)
{
	if (!list)
		return NULL;
	if (!header)
		return NULL;

	struct message_headers_list* element = create_empty_message_headers_list();
	if (!element)
		return NULL;
	element->header = header;
	element->next = list;

	return element;
}
