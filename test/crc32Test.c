#include <stdlib.h>
#include "heap.h"
#include <llog.h>
#include <time.h>
#include <unity.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include "unity_internals.h"
#include <arrayList.h>
#include <random.h>
#include <crc32c.h>

void test_crc32_test_char(void)
{
}

void test_crc32_test_int32(void)
{
}

void test_crc32_test_string(void)
{
}

int main() 
{
    UNITY_BEGIN();
    RUN_TEST(test_crc32_test_char);
    RUN_TEST(test_crc32_test_int32);
    RUN_TEST(test_crc32_test_string);
    UNITY_END();
}

