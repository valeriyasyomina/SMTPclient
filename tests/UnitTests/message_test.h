#ifndef MESSAGE_TEST_H
#define MESSAGE_TEST_H

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "../../src/message.h"

void test_create_message_with_data1();
void test_create_message_with_data2();

void test_create_empty_message1();

void test_set_message_data1();
void test_set_message_data2();
void test_set_message_data3();

void test_set_message_id1();
void test_set_message_id2();
void test_set_message_id3();

#endif // MESSAGE_TEST_H

