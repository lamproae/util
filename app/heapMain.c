#include "heap.h"
#include "random.h"
#include "leak-checker.h"
#include "backtrace.h"
#include "fault.h"

void test2() {
    do_log_backtrace();
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
    printf("%d\n", random_uint32());
    printf("%lu\n", random_uint64());
    leak_checker_start("liwei.log");
    int* i = malloc(sizeof(int));
    leak_checker_stop();
    test();
}
