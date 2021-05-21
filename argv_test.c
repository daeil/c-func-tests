#include <stdio.h>


struct Test {
    int i;
    float f;
    char c;
};

int foo(int argc, char **argv) {
    printf("%s, %d\n", __func__ , argc);
    struct Test *t = (struct Test *)argv;
    printf("t->i=%d\n", t->i);
}

int main(int argc, char** argv) {

    struct Test t;
    t.i = 100;
    t.f = 3.14;
    t.c = 'c';
    foo(0, (char**) &t);
    return 0;
}
