#include <stdio.h>
#include <math.h>

#include <xmmintrin.h>
#include <immintrin.h>

#define LOOP_COUNT 1000 * 1000 * 100

double frand() { return rand() / (double)RAND_MAX; }

int main(int argc, char** argv) {


    for (int i=0; i<LOOP_COUNT; i++) {
#define NATIVE
#ifdef NATIVE
        float r = sqrt(frand());
        //printf("%.2f, %.2f\n", f, r);
#else
        __attribute__((aligned(16)))  float INPUT[4] = {frand(), frand(), frand(), frand()};
        __m128 m = _mm_load_ps(INPUT);
        //__m128 r = _mm_sin_ps(m);
        __m128 r = _mm_sqrt_ps(m);
        __attribute__((aligned(16))) float OUTPUT[4];
        _mm_store_ps(OUTPUT, r);
        //for (int j=0; j<4; j++) {
        //    printf("%.2f, %.2f\n", INPUT[j], OUTPUT[j]);
        //}
        i += 3;
#endif
    }
    return 0;
}
