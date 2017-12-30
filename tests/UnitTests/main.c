#include <stdio.h>
#include "domain_info_test.h"
#include "message_header_test.h"
#include "message_test.h"
#include "smtp_client_test.h"
#include "domain_info_list_test.h"
#include "message_headers_list_test.h"
#include "string_list_test.h"

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

int main()
{     
    if ( CUE_SUCCESS != CU_initialize_registry() )
       return CU_get_error();

    /* add a suite to the registry */
    CU_pSuite meesageHeaderSuite = CU_add_suite( "message_header_suite", init_suite, clean_suite );
    if (!meesageHeaderSuite)
    {
       CU_cleanup_registry();
       return CU_get_error();
    }

    CU_add_test(meesageHeaderSuite, "test_message_header_from_string1", test_message_header_from_string1);
    CU_add_test(meesageHeaderSuite, "test_message_header_from_string1", test_message_header_from_string1);
    CU_add_test(meesageHeaderSuite, "test_create_header1", test_create_header1);
    CU_add_test(meesageHeaderSuite, "test_create_header2", test_create_header2);
    CU_add_test(meesageHeaderSuite, "test_create_header3", test_create_header3);
    CU_add_test(meesageHeaderSuite, "test_create_header4", test_create_header4);
    CU_add_test(meesageHeaderSuite, "test_compare_message_header_key1", test_compare_message_header_key1);
    CU_add_test(meesageHeaderSuite, "test_compare_message_header_key2", test_compare_message_header_key2);

    CU_pSuite meesageHeaderListSuite = CU_add_suite( "message_header list_suite", init_suite, clean_suite );
    if (!meesageHeaderListSuite)
    {
       CU_cleanup_registry();
       return CU_get_error();
    }

    CU_add_test(meesageHeaderListSuite, "test_create_empty_message_headers_list1", test_create_empty_message_headers_list1);
    CU_add_test(meesageHeaderListSuite, "test_create_message_headers_list_item1", test_create_message_headers_list_item1);
    CU_add_test(meesageHeaderListSuite, "test_create_message_headers_list_item2", test_create_message_headers_list_item2);
    CU_add_test(meesageHeaderListSuite, "test_create_message_headers_list_item3", test_create_message_headers_list_item3);
    CU_add_test(meesageHeaderListSuite, "test_create_message_headers_list_item4", test_create_message_headers_list_item4);
    CU_add_test(meesageHeaderListSuite, "test_create_message_headers_list_item5", test_create_message_headers_list_item5);


    CU_pSuite messageSuite = CU_add_suite("message_suite", init_suite, clean_suite);
    if (!messageSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(messageSuite, "test_create_message_with_data1", test_create_message_with_data1);
    CU_add_test(messageSuite, "test_create_message_with_data2", test_create_message_with_data2);
    CU_add_test(messageSuite, "test_create_empty_message1", test_create_empty_message1);
    CU_add_test(messageSuite, "test_set_message_data1", test_set_message_data1);
    CU_add_test(messageSuite, "test_set_message_data2", test_set_message_data2);
    CU_add_test(messageSuite, "test_set_message_data3", test_set_message_data3);
    CU_add_test(messageSuite, "test_set_message_id1", test_set_message_id1);
    CU_add_test(messageSuite, "test_set_message_id2", test_set_message_id2);
    CU_add_test(messageSuite, "test_set_message_id3", test_set_message_id3);

    CU_pSuite domainInfoSuite = CU_add_suite("domain_info_suite", init_suite, clean_suite);
    if (!domainInfoSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(domainInfoSuite, "test_get_domain_name_from_header_value1", test_get_domain_name_from_header_value1);
    CU_add_test(domainInfoSuite, "test_get_domain_name_from_header_value2", test_get_domain_name_from_header_value2);
    CU_add_test(domainInfoSuite, "test_create_domain_info_with_name1", test_create_domain_info_with_name1);
    CU_add_test(domainInfoSuite, "test_create_domain_info_with_name2", test_create_domain_info_with_name2);
    CU_add_test(domainInfoSuite, "test_create_domain_info_with_name3", test_create_domain_info_with_name3);
    CU_add_test(domainInfoSuite, "test_create_domain_info_with_name4", test_create_domain_info_with_name4);
    CU_add_test(domainInfoSuite, "test_create_domain_info_with_name5", test_create_domain_info_with_name5);

    CU_pSuite domainInfoListSuite = CU_add_suite("domain_info_list suite", init_suite, clean_suite);
    if (!domainInfoListSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(domainInfoListSuite, "test_create_empty_domain_info_list1", test_create_empty_domain_info_list1);
    CU_add_test(domainInfoListSuite, "test_create_domain_info_list_item1", test_create_domain_info_list_item1);
    CU_add_test(domainInfoListSuite, "test_create_domain_info_list_item2", test_create_domain_info_list_item2);
    CU_add_test(domainInfoListSuite, "test_create_domain_info_list_item3", test_create_domain_info_list_item3);
    CU_add_test(domainInfoListSuite, "test_create_domain_info_list_item4", test_create_domain_info_list_item4);
    CU_add_test(domainInfoListSuite, "test_create_domain_info_list_item5", test_create_domain_info_list_item5);

    CU_pSuite stringSuite = CU_add_suite("string_suite", init_suite, clean_suite);
    if (!stringSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(stringSuite, "test_remove_new_line_from_buffer1", test_remove_new_line_from_buffer1);
    CU_add_test(stringSuite, "test_remove_new_line_from_buffer2", test_remove_new_line_from_buffer2);
    CU_add_test(stringSuite, "test_remove_new_line_from_buffer3", test_remove_new_line_from_buffer3);
    CU_add_test(stringSuite, "test_remove_new_line_from_buffer4", test_remove_new_line_from_buffer4);
    CU_add_test(stringSuite, "test_remove_new_line_from_buffer5", test_remove_new_line_from_buffer5);
    CU_add_test(stringSuite, "test_remove_new_line_from_buffer6", test_remove_new_line_from_buffer6);
    CU_add_test(stringSuite, "test_remove_new_line_from_buffer7", test_remove_new_line_from_buffer7);

    CU_pSuite stringListSuite = CU_add_suite("string list_suite", init_suite, clean_suite);
    if (!stringListSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(stringListSuite, "test_create_string_list_item1", test_create_string_list_item1);
    CU_add_test(stringListSuite, "test_create_string_list_item2", test_create_string_list_item2);
    CU_add_test(stringListSuite, "test_create_string_list_item3", test_create_string_list_item3);
    CU_add_test(stringListSuite, "test_create_string_list_item4", test_create_string_list_item4);
    CU_add_test(stringListSuite, "test_create_string_list_item5", test_create_string_list_item5);
    CU_add_test(stringListSuite, "test_add_to_string_list1", test_add_to_string_list1);
    CU_add_test(stringListSuite, "test_add_to_string_list2", test_add_to_string_list2);
    CU_add_test(stringListSuite, "test_add_to_string_list3", test_add_to_string_list3);
    CU_add_test(stringListSuite, "test_add_to_string_list4", test_add_to_string_list4);
    CU_add_test(stringListSuite, "test_add_to_string_list5", test_add_to_string_list5);


    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    CU_cleanup_registry();
    return CU_get_error();
}

