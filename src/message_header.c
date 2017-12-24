#include "message_header.h"
#include <stdlib.h>

struct message_header* create_header(char* key, char* value)
{
	if (!key)
		return NULL;
	if (!value)
		return NULL;

	struct message_header* header = (struct message_header*) malloc(sizeof(struct message_header));
	if (!header)
		return NULL;

	header->key = key;
	header->value = value;
	return header;
}

void free_message_header(struct message_header* message_header)
{
	if (message_header)
	{
		if (message_header->key)
		{
			free(message_header->key);
			message_header->key = NULL;
		}
		if (message_header->value)
		{
			free(message_header->value);
			message_header->value = NULL;
		}
		message_header = NULL;
	}
}