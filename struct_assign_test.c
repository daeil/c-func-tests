#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int a;
    int b;
    int c;
} TEST;

int main (int argc, char** argv) {
    TEST a = {0, 1, 2};
    TEST b = {0, 0, 0};

    b = a;

    printf("a = {%d, %d, %d}\n", a.a, a.b, a.c);
    printf("b = {%d, %d, %d}\n", b.a, b.b, b.c);

    return 0;
}
