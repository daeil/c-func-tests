#include <stdio.h>

#define sinf(r) getSinf(r)

#include <math.h>


float getSinf(float f) {
    printf("%s\n", __func__);
    return 0.1;
}

int main(int argc, char** argv) {


    printf("%f\n", sinf(M_PI / 4));
    return 0;
}
