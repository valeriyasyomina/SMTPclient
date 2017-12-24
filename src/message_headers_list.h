#include "message_header.h"

struct message_headers_list 
{
	struct message_header* header;
	struct message_headers_list* next;
};

struct message_headers_list* create_empty_message_headers_list();
void free_message_headers_list(struct message_headers_list* message_headers_list);
struct message_headers_list* add_header_to_list(struct message_headers_list* list, struct message_header* header);