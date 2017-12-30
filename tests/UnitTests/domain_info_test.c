#include "domain_info_test.h"

void test_get_domain_name_from_header_value1()
{
    char* domain_name = "yandex.ru";
    struct message_header* header = create_header(HEADER_TO, "valeriya.syomina@yandex.ru");
    char* domain = get_domain_name(header);

    CU_ASSERT_STRING_EQUAL(domain_name, domain);
    free(domain);
    free_message_header(header);
}

void test_get_domain_name_from_header_value2()
{
    char* domain_name = "mail.ru";
    struct message_header* header = create_header(HEADER_TO, "valeriya.syomina@mail.ru");
    char* domain = get_domain_name(header);

    CU_ASSERT_STRING_EQUAL(domain_name, domain);
    free(domain);
    free_message_header(header);
}


void test_create_domain_info_with_name1()
{
    char* domain_name = "yandex.ru";
    struct domain_info* domain = create_domain_info_with_name(domain_name);   
    CU_ASSERT_STRING_EQUAL(domain->domain_name, domain_name);
    free_domain_info(domain);
}

void test_create_domain_info_with_name2()
{
    struct domain_info* domain = create_domain_info_with_name(NULL);
    CU_ASSERT_EQUAL(domain, NULL);
}

void test_create_domain_info_with_name3()
{
    char* domain_name = "mail.ru";
    struct domain_info* domain = create_domain_info_with_name(domain_name);
    CU_ASSERT_STRING_EQUAL(domain->domain_name, domain_name);
    free_domain_info(domain);
}

void test_create_domain_info_with_name4()
{
    char* domain_name = "gmail.com";
    struct domain_info* domain = create_domain_info_with_name(domain_name);
    CU_ASSERT_STRING_EQUAL(domain->domain_name, domain_name);
    free_domain_info(domain);
}

void test_create_domain_info_with_name5()
{
    char* domain_name = "mydomain.ru";
    struct domain_info* domain = create_domain_info_with_name(domain_name);
    CU_ASSERT_STRING_EQUAL(domain->domain_name, domain_name);
    free_domain_info(domain);
}
