#include <stdio.h>


union {
    int i,j;
} a;

union {
    struct {
        int i,j;
    };
} b;

int main(int argc, char** argv) {

    a.i = 1;
    a.j = 2;
    b.i = 1;
    b.j = 2;
    printf("a size=%ld, i=%d, j=%d\n",sizeof(a), a.i, a.j);
    printf("b size=%ld, i=%d, j=%d\n",sizeof(b), b.i, b.j);
    return 0;
}
