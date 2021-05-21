#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#include <xmmintrin.h>

#define USE_SSE2
#include "sse_mathfun_extension.h"

#define BENCH_DURATION 1.0f //1 sec
#define MILLION (1000 * 1000)
#define COUNT (100 * MILLION)

static inline void unpack(__m128 p, float *x1, float *x2, float *x3, float *x4) {
    float x[4];
    _mm_store_ps(x, p);
    *x1 = x[0];
    *x2 = x[1];
    *x3 = x[2];
    *x4 = x[3];
}

#define pack(x1, x2, x3, x4) _mm_set_ps(x4, x3, x2, x1)

static inline unsigned long get_timestamp(void) {
    //struct timeval tv;
    //gettimeofday(&tv, NULL);
    //return tv.tv_sec * 1e6 + tv.tv_usec;
    return clock();
}

static inline float stupid_atan2f(float x) {
    return atan2f(x, x + 0.1f);
}

static inline __m128 stupid_atan2_ps(__m128 x) {
    __m128 y = _mm_add_ps(x, x);
    return atan2_ps(y, x);
}

static unsigned long int rand_elapsed;
static unsigned long int next = 1;
static float _randf(void) { // random float (0 - 120)
    next = next * 1103515245 + 12345;
    return ((next / 65536) % (unsigned int) (120 * 1e5)) * 1e-5;
}

static void _srand(unsigned int seed) {
    next = seed;
}

static void check_rand_elapsed_time(void) {
    long int niter = 0;
    unsigned long start = get_timestamp();
    float f;
    while (niter++ < COUNT) {
        f = _randf();
    }
    rand_elapsed = get_timestamp() - start;
    printf("rand() elapsed: %.3f sec. (ignore: %.3f)\n", rand_elapsed * 1e-6, f);
}

static void bench_mathlib_function(const char *name, float ( *fn )(float)) {
    long int niter = 0;
    unsigned long start = get_timestamp(), end;
    while (niter++ < COUNT) {
        fn(_randf());
    }
    end = get_timestamp();
    printf("%.3f seconds for %dM execution of %s()\n", (end - start - rand_elapsed) * 1e-6, COUNT / MILLION, name);
}

static void bench_sse_function(const char *name, __m128 ( *fn )(__m128)) {
    long int niter = 0;
    unsigned long start = get_timestamp(), end;
    while (niter++ < COUNT) {
        __m128 x = _mm_set_ps1(_randf());
        fn(x);
    }
    end = get_timestamp();
    printf("%.3f seconds for %dM execution of %s()\n", (end - start - rand_elapsed) * 1e-6, COUNT / MILLION, name);
}


#define BENCH_MATH_FUNC(fn) bench_mathlib_function(#fn, fn)
#define BENCH_SSE_FUNC(fn) bench_sse_function(#fn, fn)

static int sse_performance_check(void) {
    _srand(get_timestamp());
    check_rand_elapsed_time();

    printf("### Start Performance Test ###\n");
    BENCH_MATH_FUNC(sinf);
    BENCH_SSE_FUNC(sin_ps);

    BENCH_MATH_FUNC(cosf);
    BENCH_SSE_FUNC(cos_ps);

    BENCH_MATH_FUNC(tanf);
    BENCH_SSE_FUNC(tan_ps);

    BENCH_MATH_FUNC(atanf);
    BENCH_SSE_FUNC(atan_ps);

    BENCH_MATH_FUNC(stupid_atan2f);
    BENCH_SSE_FUNC(stupid_atan2_ps);
}


#define RESULT_FILE "sse_result.hex"

#define MIN_DEG -180.f
#define MAX_DEG 180.f
#define STEP    0.001f

static void print_f4(__m128 p) {
    static FILE *fp;
    if (fp == NULL) fp = fopen(RESULT_FILE, "w");
    float x[4];
    _mm_store_ps(x, p);
    for (int i = 0; i < 4; i++) {
        fprintf(fp, "0x%08x ", *((int *) &x[i]));
    }
    fprintf(fp, "\n");
}

static void sse_accuracy_check(void) {
    for (float f = MIN_DEG; f <= MAX_DEG; f += (STEP * 4)) {
        float r = f * (M_PI / 180);
        __m128 x = pack(r, r + STEP, r + (STEP * 2), r + (STEP * 3));
        print_f4(sin_ps(x));
        print_f4(cos_ps(x));
        print_f4(tan_ps(x));
        print_f4(stupid_atan2_ps(x));
    }
}


int
main(int argc, char *argv[])
{
    sse_performance_check();
    sse_accuracy_check();
    return EXIT_SUCCESS;
}
