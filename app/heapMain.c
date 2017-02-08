#include "heap.h"
#include "random.h"
#include "leak-checker.h"
#include "backtrace.h"
#include "fault.h"
#include <stdio.h>
#include <stdlib.h>

void test2() {
    int *j = malloc(sizeof(int));
    int *k = NULL;
    *k = 10;
    *j /= 10;
}

void test1() {
    int *j = malloc(sizeof(int));
    test2();
    *j /= 10;
}

void test() {
    int *j = malloc(sizeof(int));
    test1();
    *j /= 10;
}

int main(int argc, char** argv)
{   
    register_fault_handlers();
    leak_checker_start("liwei.log");
    int* i = malloc(sizeof(int));
     i = malloc(sizeof(int));
     i = malloc(sizeof(int));
     i = malloc(sizeof(int));
     free(i);
     i = malloc(sizeof(int));
    leak_checker_stop();
    test();

    return 0;
}
