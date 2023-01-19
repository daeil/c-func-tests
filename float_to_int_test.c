#include <stdio.h>

int main(int argc, char** argv) {
    float f = 1;
    int *a = (int *) &f;
    printf("%x\n", *a);
    printf("%x\n", *((int *) &f));

    for (float f=-100.f; f<100.f; f+= 0.5f) {
        short d = f * 100.f;
        printf("f=%.2f, d=%5d\n", f, d);
    }
    return 0;
}
