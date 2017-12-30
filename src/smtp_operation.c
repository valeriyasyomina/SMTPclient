#include "smtp_operation.h"


int send_messages(struct domain_info_list* domains, mqd_t mq)
{
    if (!domains)
    {
        send_log_message(mq, ERROR_LEVEL, "Null input domains");
        return NULL_DATA;
    }

    send_log_message(mq, DEBUG_LEVEL, "Start sending messages...");

    int result = 0;
    struct domain_info_list* cur = domains;
    while (cur && result >= 0)
    {        
        result = send_messages_one_domain(cur->info, mq);
        cur = cur->next;
    }
    if (result <= 0)
        send_log_message(mq, ERROR_LEVEL, "Send messages");
    else
        send_log_message(mq, DEBUG_LEVEL, "All messages successfully send");
    return result;
}

int send_messages_one_domain(struct domain_info* domain, mqd_t mq)
{
    int result = 0;
    if (!domain)
    {
        send_log_message(mq, ERROR_LEVEL, "Null input domain");
        return NULL_DATA;
    }

    char buffer[MAX_RESPONCE_BUFFER_SIZE];

    char log_message[MAX_LOGGER_MESSAGE_SIZE];
    snprintf(log_message, MAX_LOGGER_MESSAGE_SIZE, "Sending messages to domain %s", domain->domain_name);
    send_log_message(mq, DEBUG_LEVEL, log_message);

    send_log_message(mq, DEBUG_LEVEL, "Connecting to SMTP server...");
    int smtp_socket_descriptor = try_connect_to_smtp_server(domain->domain_name);
    if (!smtp_socket_descriptor)
    {
        send_log_message(mq, ERROR_LEVEL, "Fail connect to SMTP server");
        return SOCKET_ERROR;
    }
    send_log_message(mq, DEBUG_LEVEL, "Connection successufully established");
    send_log_message(mq, DEBUG_LEVEL, "Sending EHLO command");
    result = send_command_to_smtp_server(smtp_socket_descriptor, EHLO_COMMAND_NUMBER, MY_SERVER_NAME);
    if (result <= 0)
    {
        send_log_message(mq, ERROR_LEVEL, "Send EHLO command");
        return ERROR_SEND_DATA;
    }
    send_log_message(mq, DEBUG_LEVEL, "EHLO command successufully send");

   /* int responce_result = read(smtp_socket_descriptor, buffer, MAX_RESPONCE_BUFFER_SIZE);
    if (responce_result < 0)
        return ERROR_RECEIVE_DATA;
    printf("SMTP server hello = %s\n", buffer); */


    result = send_domain_messages_list(smtp_socket_descriptor, domain->messages, mq);
    if (result <= 0)
    {
        send_log_message(mq, ERROR_LEVEL, "Send messages for domain");
        return ERROR_SEND_DATA;
    }
    send_log_message(mq, DEBUG_LEVEL, "Domain's messages' successufully send");

    send_log_message(mq, DEBUG_LEVEL, "Sending QUIT command");
    result = send_command_to_smtp_server(smtp_socket_descriptor, QUIT_COMMAND_NUMBER, NULL);
    if (result <= 0)
    {
        send_log_message(mq, ERROR_LEVEL, "Send QUIT command");
        return ERROR_SEND_DATA;
    }
    send_log_message(mq, DEBUG_LEVEL, "QUIT command successufully send");


   // read(smtp_socket_descriptor, buffer, 1024);
   // printf("SMTP server quit = %s\n", buffer);

    return result;
}

int send_domain_messages_list(int smtp_socket_descriptor, struct message_list* messages, mqd_t mq)
{
    int result = 0;
    if (!messages)
        return NULL_DATA;

    struct message_list* cur = messages;
    while (cur && result >= 0)
    {
        result = send_domain_message(smtp_socket_descriptor, cur->message, mq);
        cur = cur->next;
    }
    return result;
}


int send_domain_message(int smtp_socket_descriptor, struct message* message, mqd_t mq)
{
    int result = 0;

    if (!message)
        return NULL_DATA;

    send_log_message(mq, DEBUG_LEVEL, "Sending message...");

    struct message_header* from_header = get_message_header_by_key(message, HEADER_FROM);

    send_log_message(mq, DEBUG_LEVEL, "Send MAIL FROM command");
    result = send_command_to_smtp_server(smtp_socket_descriptor, MAIL_FROM_COMMAND_NUMBER, from_header->value);
    if (result < 0)
    {
        send_log_message(mq, ERROR_LEVEL, "Send MAIL FROM command");
        return ERROR_SEND_DATA;
    }
    send_log_message(mq, DEBUG_LEVEL, "MAIL FROM command successufully send");

  /*  char buffer[MAX_RESPONCE_BUFFER_SIZE];

    int responce_result = read(smtp_socket_descriptor, buffer, MAX_RESPONCE_BUFFER_SIZE);
    if (responce_result < 0)
        return ERROR_RECEIVE_DATA;
    printf("SMTP server mail from = %s\n", buffer); */

    result = process_mail_to_headers(smtp_socket_descriptor, message->headers, mq);

    send_log_message(mq, DEBUG_LEVEL, "Send DATA command");
    result = send_command_to_smtp_server(smtp_socket_descriptor, DATA_COMMAND_NUMBER, NULL);
    if (result <= 0)
    {
        send_log_message(mq, ERROR_LEVEL, "Send DATA command");
        return ERROR_SEND_DATA;
    }
    send_log_message(mq, DEBUG_LEVEL, "DATA command successufully send");

    /* responce_result = read(smtp_socket_descriptor, buffer, MAX_RESPONCE_BUFFER_SIZE);
    if (responce_result < 0)
        return ERROR_RECEIVE_DATA;
    printf("SMTP server data com = %s\n", buffer); */

    send_log_message(mq, DEBUG_LEVEL, "Send message body");
    result = send_command_to_smtp_server(smtp_socket_descriptor, MESSAGE_BODY_COMMAND_NUMBER, message->data);
    if (result <= 0)
    {
        send_log_message(mq, ERROR_LEVEL, "Send message body");
        return ERROR_SEND_DATA;
    }
    send_log_message(mq, DEBUG_LEVEL, "Message successufully send");

   /* responce_result = read(smtp_socket_descriptor, buffer, MAX_RESPONCE_BUFFER_SIZE);
    if (responce_result < 0)
        return ERROR_RECEIVE_DATA;
    printf("SMTP server meessge = %s\n", buffer); */
    return result;
}

int process_mail_to_headers(int smtp_socket_descriptor, struct message_headers_list* headers, mqd_t mq)
{
    int result = 0;

    if (!headers)
        return NULL_DATA;
    struct message_headers_list* cur = headers;

    while (cur && result >= 0)
    {
        if (compare_message_header_key(cur->header, HEADER_TO) == 0)
            result = send_mail_to_command(smtp_socket_descriptor, cur->header, mq);
        cur = cur->next;
    }
    return result;
}

int send_mail_to_command(int smtp_socket_descriptor, struct message_header* to_header, mqd_t mq)
{
    send_log_message(mq, DEBUG_LEVEL, "Send RCPT TO command");
    int result = send_command_to_smtp_server(smtp_socket_descriptor, RCPT_TO_COMMAND_NUMBER, to_header->value);
    if (result < 0)
    {
        send_log_message(mq, ERROR_LEVEL, "Send RCPT TO command");
        return ERROR_SEND_DATA;
    }
    send_log_message(mq, DEBUG_LEVEL, "RCPT TO command successufully send");

 /*   char buffer[MAX_RESPONCE_BUFFER_SIZE];

    int responce_result = read(smtp_socket_descriptor, buffer, MAX_RESPONCE_BUFFER_SIZE);
    if (responce_result < 0)
        return ERROR_RECEIVE_DATA;
    printf("SMTP server mail to = %s\n", buffer); */
    return result;
}

int send_command_to_smtp_server(int socket_descriptor, int command_type, char* command_payload)
{
    char command[MAX_COMMAND_BUFFER_SIZE];
    bzero(command, MAX_COMMAND_BUFFER_SIZE);

    if (command_type == EHLO_COMMAND_NUMBER)
    {
        strncpy(command, EHLO_COMMAND, strlen(EHLO_COMMAND));
        strcat(command, command_payload);
    }
    else if (command_type == MAIL_FROM_COMMAND_NUMBER || command_type == RCPT_TO_COMMAND_NUMBER)
    {
        command_type == MAIL_FROM_COMMAND_NUMBER ? strncpy(command, MAIL_FROM_COMMAND, strlen(MAIL_FROM_COMMAND))
                                                 : strncpy(command, RCPT_TO_COMMAND, strlen(RCPT_TO_COMMAND));
        strcat(command, OPEN_TRIANGLE_BRACKET);
        strcat(command, command_payload);
        strcat(command, CLOSE_TRIANGLE_BRACKET);
    }
    else if (command_type == MESSAGE_BODY_COMMAND_NUMBER)
    {
        strncpy(command, command_payload, strlen(command_payload));
    }
    else if (command_type == DATA_COMMAND_NUMBER || command_type == QUIT_COMMAND_NUMBER)
    {
        command_type == DATA_COMMAND_NUMBER ? strncpy(command, DATA_COMMAND, strlen(DATA_COMMAND))
                                            : strncpy(command, QUIT_COMMAND, strlen(QUIT_COMMAND));
    }
    strcat(command, "\r\n");
    return write(socket_descriptor, command, strlen(command));
}


int try_connect_to_smtp_server(char* domain_name)
{
    struct firedns_mxlist* xmlist = firedns_resolvemxlist_r(domain_name);
    int connection_stablished = 0;
    int smtp_socket = SOCKET_ERROR;
    while (xmlist && !connection_stablished)
    {
        printf("Server name %s\n", xmlist->name);
        smtp_socket = create_socket(xmlist->name, SMTP_SERVER_PORT);
        if (smtp_socket > 0)
            connection_stablished = 1;
        xmlist = xmlist->next;
    }
    return smtp_socket;
}

int create_socket(const char* host, int port)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int socket_found = 0;
    int result = SOCKET_ERROR;

    if ((he = gethostbyname(host )) == NULL)
        return SOCKET_ERROR;

    addr_list = (struct in_addr **) he->h_addr_list;

    for(int i = 0; addr_list[i] != NULL && !socket_found; i++)
    {
        struct sockaddr_in server;
        memset(&server, 0, sizeof(struct sockaddr_in));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(inet_ntoa(*addr_list[i]));
        server.sin_port = htons(SMTP_SERVER_PORT);

        int socket_descriptor = socket(AF_INET , SOCK_STREAM , 0);
        int connect_result = connect(socket_descriptor,(struct sockaddr *)&server, sizeof(server));
        if (connect_result == 0)
        {
            socket_found = 1;
            result = socket_descriptor;
        }
    }
    return result;
}
