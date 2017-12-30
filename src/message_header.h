#ifndef MESSAGE_HEADER_H
#define MESSAGE_HEADER_H

#define HEADER_DELIMITER ':'
#define DOMAIN_DELIMITER '@'
#define SPACE ' '

#define HEADER_FROM "BabarykinSyomina-SERVER_FROM"
#define HEADER_TO "BabarykinSyomina-SERVER_TO"
#define HEADER_MESSAGE_ID "BabarykinSyomina-SERVER_MESSAGE_ID"

struct message_header
{
	char* key;
	char* value;	
};

struct message_header* create_header(char* key, char* value);
void free_message_header(struct message_header* message_header);
struct message_header* message_header_from_string(char* str);

char* get_domain_name(struct message_header* header);
int compare_message_header_key(struct message_header* header, char* key);

#endif
