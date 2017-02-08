#include "heap.h"
#include "random.h"
#include "leak-checker.h"
#include "backtrace.h"
#include "fault.h"

void test2() {
    int *k = NULL;
    *k = 10;
}

void test1() {
    test2();
}

void test() {
    test1();
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
}
