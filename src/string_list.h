#include <stdlib.h>
#include <string.h>

struct string_list 
{
	char* value;
	struct string_list* next;
};

struct string_list* create_empty_string_list();
void free_string_list(struct string_list* list);
struct string_list* add_string_to_list(struct string_list* list, char* value);
