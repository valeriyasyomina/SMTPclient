#include "message_headers_list_test.h"

void test_create_empty_message_headers_list1()
{
    struct message_headers_list* list = create_empty_message_headers_list();
    CU_ASSERT_EQUAL(list->header, NULL);
    CU_ASSERT_EQUAL(list->next, NULL);
    free_message_headers_list(list);
}

void test_create_message_headers_list_item1()
{
    struct message_header* header = create_header("key", "value");
    struct message_headers_list* item = create_message_headers_list_item(header);
    CU_ASSERT_EQUAL(item->header, header);
    CU_ASSERT_EQUAL(item->next, NULL);
    free_message_headers_list(item);
}

void test_create_message_headers_list_item2()
{
    struct message_headers_list* item = create_message_headers_list_item(NULL);
    CU_ASSERT_EQUAL(item, NULL);
}

void test_create_message_headers_list_item3()
{
    struct message_header* header = create_header("key", "value");
    struct message_headers_list* item = create_message_headers_list_item(header);
    CU_ASSERT_EQUAL(item->header, header);
    CU_ASSERT_EQUAL(item->next, NULL);
    free_message_headers_list(item);
}

void test_create_message_headers_list_item4()
{
    struct message_header* header = create_header("key", "value");
    struct message_headers_list* item = create_message_headers_list_item(header);
    CU_ASSERT_EQUAL(item->header, header);
    CU_ASSERT_EQUAL(item->next, NULL);
    free_message_headers_list(item);
}

void test_create_message_headers_list_item5()
{
    struct message_header* header = create_header("key", "value");
    struct message_headers_list* item = create_message_headers_list_item(header);
    CU_ASSERT_EQUAL(item->header, header);
    CU_ASSERT_EQUAL(item->next, NULL);
    free_message_headers_list(item);
}
