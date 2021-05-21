#include <stdio.h>
#include <stdlib.h>
#include <math.h>

union value {
    float f;
    unsigned int i;
};

int main(int argc, char **argv)
{
    union value x, y, mid_result, result;
    x.i = 0x41aea739;
    y.i = 0x41bd285d;

    mid_result.f = atan2f(y.f, x.f);
    result.f = mid_result.f * 180.f / 3.141592f;

    printf("x=%f(0x%x), y=%f(0x%x), atan2f(y,x)=%f(0x%x), r=%f(0x%x)\n",
            x.f, x.i, y.f, y.i,mid_result.f, mid_result.i, result.f, result.i);

    return EXIT_SUCCESS;
}
