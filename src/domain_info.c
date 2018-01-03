#include "domain_info.h"

struct domain_info* create_domain_info_with_name(char* name)
{
    if (!name)
        return NULL;
    struct domain_info* info = (struct domain_info*) malloc(sizeof(struct domain_info));
    if (!info)
        return NULL;
    int name_size = strlen(name);
    info->domain_name = (char*) malloc(name_size + 1);
    strncpy(info->domain_name, name, name_size);
    info->domain_name[name_size] = '\0';
    info->messages = NULL;
    return info;
}

void free_domain_info(struct domain_info* info)
{
    if (info)
    {
        if (info->domain_name)
        {
            free(info->domain_name);
            info->domain_name = NULL;
        }
        if (info->messages)
        {
            free_message_list(info->messages);
            info->messages = NULL;
        }
        free(info);
    }
}

struct domain_info* add_message_to_domain_info(struct domain_info* info, struct message* message)
{
    if (!info)
        return NULL;
    if (!message)
        return NULL;

    struct message_list* item = create_message_list_item(message);
    info->messages = add_to_message_list(info->messages, item);
    return info;
}

struct message* get_message_by_id_from_domain_info(struct domain_info* info, char* message_id)
{
    if (!info || !message_id)
        return NULL;
    return get_message_by_id(info->messages, message_id);
}

struct message* get_message_by_header_key_from_domain_info(struct domain_info* info, char* header_key)
{
    if (!info || !info->messages || !header_key)
        return NULL;

    return get_message_by_header_key(info->messages, header_key);
}

int compare_domain_info_name(struct domain_info* info, char* name)
{
    if (!info || !info->domain_name)
        return NULL_DATA;
    if (!name)
        return NULL_DATA;
    return strcmp(info->domain_name, name);
}

