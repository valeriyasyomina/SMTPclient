struct message_header
{
	char* key;
	char* value;	
};

struct message_header* create_header(char* key, char* value);
void free_message_header(struct message_header* message_header);

