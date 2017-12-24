#include "message_header.h"
#include <stdlib.h>
#include <string.h>

struct message_header* create_header(char* key, char* value)
{
	if (!key)
		return NULL;
	if (!value)
		return NULL;

	struct message_header* header = (struct message_header*) malloc(sizeof(struct message_header));
	if (!header)
		return NULL;

    int key_size = strlen(key);
    header->key = (char*) malloc(key_size + 1);
    if (!header->key)
        return NULL;
    strncpy(header->key, key, key_size);
    header->key[key_size] = '\0';

    int value_size = strlen(value);
    header->value = (char*) malloc(value_size + 1);
    if (!header->value)
        return NULL;
    strncpy(header->value, value, value_size);
    header->value[value_size] = '\0';
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
