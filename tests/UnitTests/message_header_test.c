#include "message_header_test.h"

void test_message_header_from_string1()
{
    char* header_key = "HEADER_KEY";
    char* header_value = "VALUE";

    struct message_header* header = message_header_from_string("HEADER_KEY: VALUE");
    CU_ASSERT_STRING_EQUAL(header_key, header->key);
    CU_ASSERT_STRING_EQUAL(header_value, header->value);

    free_message_header(header);
}

void test_message_header_from_string2()
{
    struct message_header* header = message_header_from_string(NULL);
    CU_ASSERT_EQUAL(header, NULL);
}

void test_create_header1()
{
    char* key = "KEY";
    char* value = "VALUE";

    struct message_header* header = create_header(key, value);
    CU_ASSERT_STRING_EQUAL(header->key, key);
    CU_ASSERT_STRING_EQUAL(header->value, value);
    free_message_header(header);
}

void test_create_header2()
{
    char* key = "KEY";

    struct message_header* header = create_header(key, NULL);
    CU_ASSERT_EQUAL(header, NULL);
}

void test_create_header3()
{
    char* value = "VALUE";

    struct message_header* header = create_header(NULL, value);
    CU_ASSERT_EQUAL(header, NULL);
}

void test_create_header4()
{
    struct message_header* header = create_header(NULL, NULL);
    CU_ASSERT_EQUAL(header, NULL);
}

void test_compare_message_header_key1()
{
    char* key = "KEY";
    char* value = "VALUE";

    struct message_header* header = create_header(key, value);
    int result = compare_message_header_key(header, key);
    CU_ASSERT_EQUAL(result, 0);
    free_message_header(header);
}

void test_compare_message_header_key2()
{
    char* key = "KEY";
    char* value = "VALUE";

    struct message_header* header = create_header(key, value);
    int result = compare_message_header_key(header, "Another_key");
    CU_ASSERT_NOT_EQUAL(result, 0);
    free_message_header(header);
}
