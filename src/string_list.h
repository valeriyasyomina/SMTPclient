#ifndef STRING_LIST_H
#define STRING_LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct string_list 
{
	char* value;
	struct string_list* next;
};

struct string_list* create_string_list_item(char* value);
void free_string_list(struct string_list* list);
struct string_list* add_to_string_list(struct string_list* list, struct string_list* element);
void print_string_list(struct string_list* list);

#endif
