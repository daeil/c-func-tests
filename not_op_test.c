#include <stdio.h>

int main(int argc, char** argv) {

    int i = 0;
    printf("i=%d, ~i=%d, !i=%d\n", i, ~i, !i);
    i = 1;
    printf("i=%d, ~i=%d, !i=%d\n", i, ~i, !i);
    return 0;
}
