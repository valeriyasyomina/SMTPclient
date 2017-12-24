#include "string_list.h"

struct string_list* create_empty_string_list()
{
	struct string_list* list = (struct string_list*) malloc(sizeof(struct string_list));
	if (!list)
		return NULL;
	list->value = NULL;
	list->next = NULL;
	return list;
}

void free_string_list(struct string_list* list)
{
	if (list)
	{
		struct string_list* cur = list;
		while (cur)
		{
			cur = list->next;
            if (list->value)
            {
                free(list->value);
                list->value = NULL;
            }
			free(list);
			list = cur;
		}
		list = NULL;
	}
}

struct string_list* add_string_to_list(struct string_list* list, char* value)
{
	if (!list)
		return NULL;
	if (!value)
		return NULL;
	struct string_list* element = create_empty_string_list();
	if (!element)
		return NULL;

    int value_size = strlen(value);
    element->value = (char*) malloc(value_size + 1);
    if (!element->value)
        return NULL;
    strncpy(element->value, value, value_size);
    element->value[value_size] = '\0';
	element->next = list;
	return element;
}
