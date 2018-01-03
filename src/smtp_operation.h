#ifndef SMTP_OPERATION_H
#define SMTP_OPERATION_H

#define SMTP_SERVER_PORT 25

#define SOCKET_ERROR -1
#define ERROR_SEND_DATA -2
#define ERROR_RECEIVE_DATA -3

#define MY_SERVER_NAME "my_smtp_client"

#define EHLO_COMMAND "EHLO "
#define MAIL_FROM_COMMAND "MAIL FROM: "
#define RCPT_TO_COMMAND "RCPT TO: "
#define DATA_COMMAND "DATA"
#define QUIT_COMMAND "QUIT"

#define OPEN_TRIANGLE_BRACKET "<"
#define CLOSE_TRIANGLE_BRACKET ">"

#define EHLO_COMMAND_NUMBER 0
#define MAIL_FROM_COMMAND_NUMBER 1
#define RCPT_TO_COMMAND_NUMBER 2
#define DATA_COMMAND_NUMBER 3
#define MESSAGE_BODY_COMMAND_NUMBER 4
#define QUIT_COMMAND_NUMBER 5

#define MAX_COMMAND_BUFFER_SIZE 2048
#define MAX_RESPONCE_BUFFER_SIZE 1024

#define START_SEND_MSG_CODE 354
#define SUCCESS_EHLO_CODE 220
#define SUCCESS_QUIT_CODE 221
#define SUCCESS_OPERATION_CODE 250

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <firedns.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <mqueue.h>
#include "domain_info_list.h"
#include "logger.h"

int send_messages(struct domain_info_list* domains, mqd_t mq, int attempts_number, int attempts_delay);
int send_messages_one_domain(struct domain_info* domain, mqd_t mq, int attempts_number, int attempts_delay);
int send_domain_messages_list(int smtp_socket_descriptor, struct message_list* messages, mqd_t mq);
int send_domain_message(int smtp_socket_descriptor, struct message* message, mqd_t mq);
int create_socket(const char* host, int port, int attempts_number, int attempts_delay);
void get_host_ip_by_name(char* host_name);
int try_connect_to_smtp_server(char* domain_name, int attempts_number, int attempts_delay);
int send_mail_to_command(int smtp_socket_descriptor, struct message_header* to_header, mqd_t mq);
int process_mail_to_headers(int smtp_socket_descriptor, struct message_headers_list* headers, mqd_t mq);
int send_command_to_smtp_server(int socket_descriptor, int command_type, char* command_payload);

void free_xmlist(struct firedns_mxlist* xmlist);
void free_firedns_ip6list(struct firedns_ip6list* list);
void free_firedns_ip4list(struct firedns_ip4list* list);

int try_connect_to_socket(struct sockaddr_in server, int attempts_number, int attempts_delay);
#endif // SMTP_OPERATION_H

