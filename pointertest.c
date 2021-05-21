#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct {
    int header;
    char c;
    int footer;
} TEST_t;

static TEST_t static_test;



void test2(TEST_t test) {
    static_test = test;

    printf("%d: %c :%d\n", static_test.header, static_test.c, static_test.footer);
}



void test(TEST_t* test) {
    //static_test = *test;
    //printf("%d: %c :%d\n", static_test.header, static_test.c, static_test.footer);
    test2(*test);
}


int main () {
    TEST_t t;
    t.header = 100;
    t.c = 'D';
    t.footer = 200;

    test(&t);
}
