#include "message.h"
#include <stdlib.h>

struct message* create_empty_message()
{
	struct message* message = (struct message*) malloc(sizeof(struct message));
	if (!message)
		return NULL;
	message->data = NULL;
	message->headers = create_empty_message_headers_list();
	return message;
}

void free_message(struct message* message)
{
	if (message)
	{
		if (message->data)
		{
			free(message->data);
			message->data = NULL;
		}
		free_message_headers_list(message->headers);
	}
}

struct message* add_header(struct message* message, struct message_header* header)
{
	if (!message)
		return NULL;
	if (!header)
		return NULL;
	message->headers = add_header_to_list(message->headers, header);
	if (!message->headers)
		return NULL;
	return message;
}