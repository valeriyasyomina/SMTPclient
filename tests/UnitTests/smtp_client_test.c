#include "smtp_client_test.h"


void test_remove_new_line_from_buffer1()
{
    char* buffer_with_new_line = "Hello\n";
    char* buffer_wo_new_line = "Hello";
    char* result = remove_new_line_from_buffer(buffer_with_new_line);
    CU_ASSERT_STRING_EQUAL(result, buffer_wo_new_line);
    free(result);
}

void test_remove_new_line_from_buffer2()
{
    char* buffer_with_new_line = "Hello";
    char* buffer_wo_new_line = "Hello";
    char* result = remove_new_line_from_buffer(buffer_with_new_line);
    CU_ASSERT_STRING_EQUAL(result, buffer_wo_new_line);  
}

void test_remove_new_line_from_buffer3()
{
    char* result = remove_new_line_from_buffer(NULL);
    CU_ASSERT_EQUAL(result, NULL);
}

void test_remove_new_line_from_buffer4()
{
    char* buffer_with_new_line = "Ololo";
    char* buffer_wo_new_line = "Ololo";
    char* result = remove_new_line_from_buffer(buffer_with_new_line);
    CU_ASSERT_STRING_EQUAL(result, buffer_wo_new_line);
}

void test_remove_new_line_from_buffer5()
{
    char* buffer_with_new_line = "111";
    char* buffer_wo_new_line = "111";
    char* result = remove_new_line_from_buffer(buffer_with_new_line);
    CU_ASSERT_STRING_EQUAL(result, buffer_wo_new_line);
}

void test_remove_new_line_from_buffer6()
{
    char* buffer_with_new_line = "1213";
    char* buffer_wo_new_line = "1213";
    char* result = remove_new_line_from_buffer(buffer_with_new_line);
    CU_ASSERT_STRING_EQUAL(result, buffer_wo_new_line);
}

void test_remove_new_line_from_buffer7()
{
    char* buffer_with_new_line = "str\n";
    char* buffer_wo_new_line = "str";
    char* result = remove_new_line_from_buffer(buffer_with_new_line);
    CU_ASSERT_STRING_EQUAL(result, buffer_wo_new_line);
    free(result);
}


