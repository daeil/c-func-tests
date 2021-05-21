#include <stdio.h>

int main(int argc, char** argv) {
    float f = 1;
    int *a = (int *) &f;
    printf("%x\n", *a);
    printf("%x\n", *((int *) &f));
    return 0;
}
