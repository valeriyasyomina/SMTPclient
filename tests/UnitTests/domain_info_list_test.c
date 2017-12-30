#include "domain_info_list_test.h"

void test_create_empty_domain_info_list1()
{
    struct domain_info_list* list = create_empty_domain_info_list();
    CU_ASSERT_EQUAL(list->info, NULL);
    CU_ASSERT_EQUAL(list->next, NULL);
    free_domain_info_list(list);
}

void test_create_domain_info_list_item1()
{
    struct domain_info_list* item = create_domain_info_list_item(NULL);
    CU_ASSERT_EQUAL(item, NULL);
}

void test_create_domain_info_list_item2()
{
    struct domain_info* info = create_domain_info_with_name("mail.ru");
    struct domain_info_list* item = create_domain_info_list_item(info);
    CU_ASSERT_EQUAL(item->info, info);
    free_domain_info_list(item);
}

void test_create_domain_info_list_item3()
{
    struct domain_info* info = create_domain_info_with_name("yandex.ru");
    struct domain_info_list* item = create_domain_info_list_item(info);
    CU_ASSERT_EQUAL(item->info, info);
    free_domain_info_list(item);
}

void test_create_domain_info_list_item4()
{
    struct domain_info* info = create_domain_info_with_name("gmail.com");
    struct domain_info_list* item = create_domain_info_list_item(info);
    CU_ASSERT_EQUAL(item->info, info);
    free_domain_info_list(item);
}

void test_create_domain_info_list_item5()
{
    struct domain_info* info = create_domain_info_with_name("aquivalabs");
    struct domain_info_list* item = create_domain_info_list_item(info);
    CU_ASSERT_EQUAL(item->info, info);
    free_domain_info_list(item);
}
