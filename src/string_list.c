#include "string_list.h"


struct string_list* create_string_list_item(char* value)
{
    if (!value)
        return NULL;
    struct string_list* item = (struct string_list*) malloc(sizeof(struct string_list));
    if (!item)
        return NULL;

    int value_size = strlen(value);
    item->value = (char*) malloc(value_size + 1);
    if (!item->value)
        return NULL;
    strncpy(item->value, value, value_size);
    item->value[value_size] = '\0';

    item->next = NULL;
    return item;
}

void free_string_list(struct string_list* list)
{
	if (list)
	{
        struct string_list* cur = NULL;
        for (; list; list = cur)
        {
            cur = list->next;
            if (list->value)
            {
                free(list->value);
                list->value = NULL;
            }
            free(list);
            list = NULL;
        }
        list = NULL;
	}
}

struct string_list* add_to_string_list(struct string_list* list, struct string_list* element)
{	
    if (!element)
		return NULL;
    if (!list)
        return element;
    element->next = list;
	return element;
}

void print_string_list(struct string_list* list)
{
    if (list)
    {
        struct string_list* cur = list;
        printf("String list:\n");
        while (cur)
        {
            if (cur->value)
                printf("%s\n", cur->value);
            cur = cur->next;
        }
        printf("\n\n");
    }
}
