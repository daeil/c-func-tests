#include <stdio.h>

#pragma GCC push_options
#pragma GCC optimize ("O0")

#if 0
union value {
    float f;
    unsigned int i;
};
#endif

int main(int argc, char** argv) {
#if 0
    union value v, r;
    v.i = 0x3f557f2d;
    r.f = v.f * 180.f / 3.141592f;
    printf("%f(0x%08x)\n", r.f, r.i);
#endif

    unsigned int i = 0x3f557f2d; // 1062567725
    float f = *(float *) &i;
    printf("%f, f=%f\n", f, f * 180.f / 3.141592f);
    return 0;
}

#pragma GCC pop_options
