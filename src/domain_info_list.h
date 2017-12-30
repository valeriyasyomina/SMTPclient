#ifndef DOMAIN_INFO_LIST_H
#define DOMAIN_INFO_LIST_H

#include "domain_info.h"

struct domain_info_list
{
    struct domain_info* info;
    struct domain_info_list* next;
};

void free_domain_info_list(struct domain_info_list* list);
struct domain_info_list* create_empty_domain_info_list();
struct domain_info_list* create_domain_info_list_item(struct domain_info* info);
struct domain_info_list* get_domain_info_by_name(struct domain_info_list* list, char* domain_name);
struct domain_info_list* add_to_domain_info_list(struct domain_info_list* list, struct domain_info_list* item);
void free_domain_info_list(struct domain_info_list* list);
struct message* get_message_by_header_key_from_domain(struct domain_info_list* list, char* header_key);
struct message* get_message_by_id_from_domain(struct domain_info_list* list, char* message_id);

#endif // DOMAIN_INFO_LIST_H

