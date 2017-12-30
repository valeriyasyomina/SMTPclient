#include "domain_info_list.h"

struct domain_info_list* create_empty_domain_info_list()
{
    struct domain_info_list* list = (struct domain_info_list*) malloc(sizeof(struct domain_info_list));
    if (!list)
        return NULL;
    list->info = NULL;
    list->next = NULL;
    return list;
}

void free_domain_info_list(struct domain_info_list* list)
{
    if (list)
    {
        struct domain_info_list* cur = NULL;
        for (; list; list = cur)
        {
            cur = list->next;
            if (list->info)
            {
                free_domain_info(list->info);
                list->info = NULL;
            }
            free(list);
            list = NULL;
        }
        list = NULL;

    }
}

struct domain_info_list* create_domain_info_list_item(struct domain_info* info)
{
    if (!info)
        return NULL;
    struct domain_info_list* list = (struct domain_info_list*) malloc(sizeof(struct domain_info_list));
    if (!list)
        return NULL;
    list->info = info;
    list->next = NULL;
    return list;
}

struct domain_info_list* get_domain_info_by_name(struct domain_info_list* list, char* domain_name)
{
    if (!list)
        return NULL;
    if (!domain_name)
        return NULL;

    struct domain_info_list* cur = list;
    struct domain_info_list* result = NULL;
    int found = 0;
    while (cur && !found)
    {
        if (cur->info && compare_domain_info_name(cur->info, domain_name) == 0)
        {
            result = cur;
            found = 1;
        }
        cur = cur->next;
    }
    return result;
}

struct message* get_message_by_id_from_domain(struct domain_info_list* list, char* message_id)
{
    if (!list || !list->info || !message_id)
        return NULL;
    return get_message_by_id_from_domain_info(list->info, message_id);
}

struct message* get_message_by_header_key_from_domain(struct domain_info_list* list, char* header_key)
{
    if (!list || !list->info || !header_key)
        return NULL;
    return NULL;
   // return get_message_by_header_key_from_domain_info(list->info, header_key);
}

struct domain_info_list* add_to_domain_info_list(struct domain_info_list* list, struct domain_info_list* item)
{
    if (!item)
        return NULL;
    if (!list)
        return item;
    item->next = list;
    return item;
}
