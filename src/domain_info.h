#ifndef DOMAIN_INFO_H
#define DOMAIN_INFO_H

#include <stdlib.h>
#include <string.h>
#include "message_list.h"

struct domain_info
{
    char* domain_name;
    struct message_list* messages;
};

struct domain_info* create_domain_info_with_name(char* name);
void free_domain_info(struct domain_info* info);
struct domain_info* add_message_to_domain_info(struct domain_info* info, struct message* message);
int compare_domain_info_name(struct domain_info* info, char* name);
struct message* get_message_by_header_key_from_domain_info(struct domain_info* info, char* header_key);

struct message* get_message_by_id_from_domain_info(struct domain_info* info, char* message_id);

#endif // DOMAIN_INFO_H

