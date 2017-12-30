#include "string_list_test.h"

void test_create_string_list_item1()
{
    char* value = "value";
    struct string_list* item = create_string_list_item(value);
    CU_ASSERT_EQUAL(item->next, NULL);
    CU_ASSERT_STRING_EQUAL(item->value, value);
    free_string_list(item);
}

void test_create_string_list_item2()
{
    struct string_list* item = create_string_list_item(NULL);
    CU_ASSERT_EQUAL(item, NULL);
}

void test_create_string_list_item3()
{
    char* value = "value1";
    struct string_list* item = create_string_list_item(value);
    CU_ASSERT_EQUAL(item->next, NULL);
    CU_ASSERT_STRING_EQUAL(item->value, value);
    free_string_list(item);
}

void test_create_string_list_item4()
{
    char* value = "value2";
    struct string_list* item = create_string_list_item(value);
    CU_ASSERT_EQUAL(item->next, NULL);
    CU_ASSERT_STRING_EQUAL(item->value, value);
    free_string_list(item);
}

void test_create_string_list_item5()
{
    char* value = "value3";
    struct string_list* item = create_string_list_item(value);
    CU_ASSERT_EQUAL(item->next, NULL);
    CU_ASSERT_STRING_EQUAL(item->value, value);
    free_string_list(item);
}

void test_add_to_string_list1()
{
    char* value = "value";
    struct string_list* item = create_string_list_item(value);
    struct string_list* list = NULL;
    list = add_to_string_list(list, item);
    CU_ASSERT_EQUAL(list->value, item->value);
    CU_ASSERT_EQUAL(list->next, NULL);
    free_string_list(item);
}

void test_add_to_string_list2()
{
    struct string_list* list = NULL;
    list = add_to_string_list(list, NULL);
    CU_ASSERT_EQUAL(list, NULL);
}

void test_add_to_string_list3()
{
    char* value = "value";
    struct string_list* item = create_string_list_item(value);
    struct string_list* list = create_string_list_item(value);
    list = add_to_string_list(list, item);
    CU_ASSERT_STRING_EQUAL(list->value, value);
    CU_ASSERT_STRING_EQUAL(list->next->value, value);
    CU_ASSERT_EQUAL(list->next->next, NULL);
    free_string_list(item);
}

void test_add_to_string_list4()
{
    char* value = "value1";
    struct string_list* item = create_string_list_item(value);
    struct string_list* list = create_string_list_item(value);
    list = add_to_string_list(list, item);
    CU_ASSERT_STRING_EQUAL(list->value, value);
    CU_ASSERT_STRING_EQUAL(list->next->value, value);
    CU_ASSERT_EQUAL(list->next->next, NULL);
    free_string_list(item);
}


void test_add_to_string_list5()
{
    char* value = "value2";
    struct string_list* item = create_string_list_item(value);
    struct string_list* list = create_string_list_item(value);
    list = add_to_string_list(list, item);
    CU_ASSERT_STRING_EQUAL(list->value, value);
    CU_ASSERT_STRING_EQUAL(list->next->value, value);
    CU_ASSERT_EQUAL(list->next->next, NULL);
    free_string_list(item);
}
