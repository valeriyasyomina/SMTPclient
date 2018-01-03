#include "message_test.h"

void test_create_empty_message1()
{
    struct message* message = create_empty_message();
    CU_ASSERT_EQUAL(message->data, NULL);
    CU_ASSERT_EQUAL(message->id, NULL);
    CU_ASSERT_EQUAL(message->headers, NULL);
    free_message(message);
}

void test_set_message_data1()
{
    char* message_data = "Test_data";
    struct message* message = create_empty_message();
    set_message_data(message, message_data);
    CU_ASSERT_STRING_EQUAL(message->data, message_data);
    free_message(message);
}

void test_set_message_data2()
{
    struct message* message = create_empty_message();
    set_message_data(message, NULL);
    CU_ASSERT_EQUAL(message->id, NULL);
    free_message(message);
}

void test_set_message_data3()
{
    struct message* message = NULL;
    set_message_data(message, NULL);
    CU_ASSERT_EQUAL(message, NULL);
}

void test_set_message_id1()
{
    char* message_id = "Test_id";
    struct message* message = create_empty_message();
    set_message_id(message, message_id);
    CU_ASSERT_STRING_EQUAL(message->id, message_id);
    free_message(message);
}

void test_set_message_id2()
{
    struct message* message = create_empty_message();
    set_message_id(message, NULL);
    CU_ASSERT_EQUAL(message->id, NULL);
    free_message(message);
}

void test_set_message_id3()
{
    struct message* message = NULL;
    set_message_id(message, NULL);
    CU_ASSERT_EQUAL(message, NULL);
}

void test_create_message_with_data1()
{
    char* message_data = "Test_data";
    struct message* message = create_message_width_data(message_data);
    CU_ASSERT_STRING_EQUAL(message_data, message->data);
    free_message(message);
}

void test_create_message_with_data2()
{
    struct message* message = create_message_width_data(NULL);
    CU_ASSERT_EQUAL(message, NULL);
}






