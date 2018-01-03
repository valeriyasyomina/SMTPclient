#include "message.h"
#include <stdlib.h>
#include <string.h>

struct message* create_empty_message()
{
	struct message* message = (struct message*) malloc(sizeof(struct message));
	if (!message)
		return NULL;
	message->data = NULL;
    message->id = NULL;
    message->headers = NULL;
    // message->headers = create_empty_message_headers_list();
	return message;
}

struct message* create_message_width_data(char* data)
{
    if (!data)
        return NULL;
    struct message* message = (struct message*) malloc(sizeof(struct message));
    if (!message)
        return NULL;
    int data_size = strlen(data);
    message->data = (char*) malloc(data_size + 1);
    strncpy(message->data, data, data_size);
    message->data[data_size] = '\0';
    message->headers = NULL;
    message->id = NULL;
    return message;
}

void set_message_data(struct message* message, char* data)
{
    if (message && data)
    {
        if (message->data)
        {
            free(message->data);
            message->data = NULL;
        }
        int data_size = strlen(data);
        message->data = (char*) malloc(data_size + 1);
        strncpy(message->data, data, data_size);
        message->data[data_size] = '\0';
    }
}

void set_message_id(struct message* message, char* id)
{
    if (message && id)
    {
        if (message->id)
        {
            free(message->id);
            message->id = NULL;
        }
        int id_size = strlen(id);
        message->id = (char*) malloc(id_size + 1);
        strncpy(message->id, id, id_size);
        message->id[id_size] = '\0';
    }
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
        if (message->id)
        {
            free(message->id);
            message->id = NULL;
        }
		free_message_headers_list(message->headers);
        message->headers = NULL;
        free(message);
	}
}

struct message* add_header_to_message(struct message* message, struct message_header* header)
{
    if (!message)
        return NULL;
    if (!header)
        return NULL;

    struct message_headers_list* header_item = create_message_headers_list_item(header);
    message->headers = add_to_message_headers_list(message->headers, header_item);
    return message;
}

int compare_message_id(struct message* message, char* id)
{
    if (!message || !message->id || !id)
        return NULL_DATA;
    return strcmp(message->id, id);
}

struct message_header* get_message_header_by_key(struct message* message, char* header_key)
{
    if (!header_key)
        return NULL;
    return get_header_by_key(message->headers, header_key);
}


