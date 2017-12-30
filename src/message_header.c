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

struct message_header* message_header_from_string(char* str)
{
    if (!str)
        return NULL;
    char* tmp = str;
    while (*tmp != HEADER_DELIMITER)
        tmp++;
    int header_key_lenght = tmp - str;
    char* key = (char*) malloc(header_key_lenght + 1);
    strncpy(key, str, header_key_lenght);
    key[header_key_lenght] = '\0';

    tmp++;

    while (*tmp == SPACE)
        tmp++;

    int header_value_length = strlen(str) - (tmp - str);
    char* value = (char*) malloc(header_value_length + 1);
    strncpy(value, tmp, header_value_length);
    value[header_value_length] = '\0';

    struct message_header* message_header = create_header(key, value);
    free(key);
    key = NULL;
    free(value);
    value = NULL;

    return message_header;

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

char* get_domain_name(struct message_header* header)
{
    if (!header || !header->key || !header->value)
        return NULL;
    if (strcmp(header->key, HEADER_TO) != 0)
        return NULL;
    char* tmp = header->value;
    while (*(tmp++) != DOMAIN_DELIMITER)
        ;
    int domain_length = strlen(header->value) - (header->value - tmp);
    char* domain = (char*) malloc(domain_length + 1);
    strncpy(domain, tmp, domain_length);
    domain[domain_length] = '\0';
    return domain;
}

int compare_message_header_key(struct message_header* header, char* key)
{
    return strcmp(header->key, key);
}
