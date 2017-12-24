#include "message_headers_list.h"

#define MAX_DATA_SIZE 2048

struct message
{
	char* data;
	struct message_headers_list* headers;
};

struct message* create_empty_message();
void free_message(struct message* message);
struct message* add_header(struct message* message, struct message_header* header);