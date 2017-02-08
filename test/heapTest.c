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

#define ARRAY_SIZE 200000

#define LLOG_DATE_LEN  32

unsigned int data[ARRAY_SIZE] = { 0 };

static void generateData() {
    int i = 0;
    for (i; i < ARRAY_SIZE; i++) {
        data[i] = random_range(ARRAY_SIZE * 1000);
    }
}

static void showData(unsigned int *data, int n) {
    int i = 0;
    for (i; i < n; i++) {
        printf("%15u ", data[i]);
        if ((i+1) % 10 == 0 && i != 0)
            printf("\n");
    }
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

struct ArrayList *new = NULL;

int compare(void *a, void *b) {
    return a - b;
}

int cmp(void *a, void *b) {

    return *(unsigned int *)a - *(unsigned int *)b;
}

void test_array_list_create(void)
{
    new = arrayListCreate(1000, compare);
    TEST_ASSERT_NOT_NULL(new);
    TEST_ASSERT_EQUAL(new->size, 0);
    TEST_ASSERT_EQUAL(new->capability, 1000);
}

void test_array_list_destroy(void)
{
    arrayListDestroy(&new);
    TEST_ASSERT_NULL(new);
}

void test_array_list_insert(void)
{
    int i = 0;
    for (i; i < ARRAY_SIZE; i++)
    {
        arrayListInsert(new, data[i]);
        TEST_ASSERT_EQUAL(new->size, i+1);
        TEST_ASSERT_EQUAL(arrayListGetAt(new, i), data[i]);
    }

    TEST_ASSERT_EQUAL(256000, new->capability);
    TEST_ASSERT_EQUAL(ARRAY_SIZE, new->size);
    TEST_ASSERT_EQUAL(0, memcmp(new->data, data, new->size * sizeof (void *)));
}

void test_array_list_clear(void)
{
    arrayListClear(new);
    TEST_ASSERT_EQUAL(new->capability, 1000);
    TEST_ASSERT_EQUAL(new->size, 0);
}

void test_array_list_insert_one(void)
{
    arrayListInsert(new, 10);
    TEST_ASSERT_EQUAL(new->capability, 1000);
    TEST_ASSERT_EQUAL(new->size, 1);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 0), 10);
}

void test_array_list_insert_five(void)
{
    int i = 0;
    arrayListInsert(new, 10);
    arrayListInsert(new, 1);
    arrayListInsert(new, 3);
    arrayListInsert(new, 20);
    arrayListInsert(new, 300);
    TEST_ASSERT_EQUAL(new->capability, 1000);
    TEST_ASSERT_EQUAL(new->size, 5);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 0), 10);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 1), 1);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 2), 3);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 3), 20);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 4), 300);

    arrayListDeleteAt(new, 2);
#if 1
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 0), 10);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 1), 1);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 2), 20);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 3), 300);
    TEST_ASSERT_EQUAL(new->capability, 1000);
    TEST_ASSERT_EQUAL(new->size, 4);
#endif

    arrayListDeleteAt(new, 1);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 1), 20);
    TEST_ASSERT_EQUAL(new->capability, 1000);
    TEST_ASSERT_EQUAL(new->size, 3);

    arrayListDeleteAt(new, 2);
    TEST_ASSERT_EQUAL(new->capability, 1000);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 2), 0);
    TEST_ASSERT_EQUAL(new->size, 2);

    arrayListDeleteAt(new, 0);
    TEST_ASSERT_EQUAL(new->capability, 1000);
    TEST_ASSERT_EQUAL(new->size, 1);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 0), 20);

    arrayListDeleteAt(new, 0);
    TEST_ASSERT_EQUAL(new->capability, 1000);
    TEST_ASSERT_EQUAL(new->size, 0);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 0), 0);
}

void test_array_list_insert_sort(void) {
    int i = 0;
    for (i; i < ARRAY_SIZE; i++)
    {
        arrayListInsertSorted(new, data[i]);
        TEST_ASSERT_EQUAL(new->size, i+1);
    }
    showData(data, ARRAY_SIZE);
    printf("----------------qsort-------------------\n");
    qsort(data, ARRAY_SIZE, sizeof(unsigned int), cmp);
    showData(data, ARRAY_SIZE);
    printf("----------------qsort-------------------\n");
    showData(new->data, ARRAY_SIZE);
    TEST_ASSERT_EQUAL(0, memcmp(new->data, data, new->size * sizeof (void *)));
}

void test_arrary_list_delete(void) {
    arrayListInsert(new, 10);
    arrayListInsert(new, 1);
    arrayListInsert(new, 3);
    arrayListInsert(new, 20);
    arrayListInsert(new, 300);
    TEST_ASSERT_EQUAL(new->capability, 1000);
    TEST_ASSERT_EQUAL(new->size, 5);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 0), 10);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 1), 1);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 2), 3);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 3), 20);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 4), 300);
    arrayListDelete(new, 1);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 0), 10);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 1), 3);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 2), 20);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 3), 300);
    TEST_ASSERT_EQUAL(new->size, 4);

    arrayListDelete(new, 10);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 0), 3);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 1), 20);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 2), 300);
    TEST_ASSERT_EQUAL(new->size, 3);

    arrayListDelete(new, 300);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 0), 3);
    TEST_ASSERT_EQUAL(arrayListGetAt(new, 1), 20);
    TEST_ASSERT_EQUAL(new->size, 2);
}

int main(int argc, char** argv)
{
    generateData();
    llog(INFO, "%s sizeof(data): %d", "Start the test for Project tt!,", sizeof(data) / sizeof(int));
    UNITY_BEGIN();

    //showData(data, ARRAY_SIZE);
    RUN_TEST(test_array_list_create);
    RUN_TEST(test_array_list_insert);
    RUN_TEST(test_array_list_clear);
    RUN_TEST(test_array_list_insert_one);
    RUN_TEST(test_array_list_clear);
    RUN_TEST(test_array_list_insert_five);
    RUN_TEST(test_array_list_clear);
    RUN_TEST(test_array_list_insert_five);
    RUN_TEST(test_array_list_clear);
    RUN_TEST(test_arrary_list_delete);
    RUN_TEST(test_array_list_clear);
    RUN_TEST(test_array_list_insert_sort);
    RUN_TEST(test_array_list_destroy);

    UNITY_END();
    llog(INFO, "%s", "Test For Project tt is Finished!");
 }
