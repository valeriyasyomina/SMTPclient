#include "message_list.h"

struct message_list* create_message_list_item(struct message* message)
{
    if (!message)
        return NULL;
    struct message_list* element = (struct message_list*) malloc(sizeof(struct message_list));
    if (!element)
        return NULL;
    element->message = message;
    element->next = NULL;
    return element;
}

void free_message_list(struct message_list* list)
{
    if (list)
    {
        struct message_list* cur = NULL;
        for (; list; list = cur)
        {
            cur = list->next;
            if (list->message)
            {
                free_message(list->message);
                list->message = NULL;
            }
            free(list);
            list = NULL;
        }
        list = NULL;
    }
}

struct message* get_message_by_id(struct message_list* list, char* id)
{
    if (!list || !id)
        return NULL;
    struct message_list* cur = list;
    struct message* result =  NULL;
    int message_found = 0;
    while (cur && !message_found)
    {
        if (compare_message_id(cur->message, id) == 0)
        {
            result = cur->message;
            message_found = 1;
        }
        cur = cur->next;
    }
    return result;
}

struct message_list* add_to_message_list(struct message_list* list, struct message_list* element)
{
    if (!element)
        return NULL;
    if (!list)
        return element;
    element->next = list;
    return element;
}

struct message* get_message_by_header_key(struct message_list* list, char* header_key)
{
    if (!list || !list->message || !header_key)
        return NULL;

}
