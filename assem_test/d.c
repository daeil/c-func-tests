#include <stdio.h>

extern float mul(float, float);

int main(int argc, char *argv[]) {
    float a = 1.3f, b = 5.7f;
    float c = mul(a, b);
    printf("%f %x\n", c, *(int *)(&c));
    return 0;
}

