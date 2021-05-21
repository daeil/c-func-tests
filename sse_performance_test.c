#include <stdio.h>
#include <math.h>
#include <time.h>

#include <xmmintrin.h>

#define USE_SSE2

#include "sse_mathfun_extension.h"

static inline float stupid_atan2f(float x) {
    return atan2f(x, x + 0.1f);
}

static inline __m128 stupid_atan2_ps(__m128 x) {
    __m128 y = _mm_add_ps(x, x);
    return atan2_ps(y, x);
}

#define BENCH_DURATION 1.0f //1 sec
#define MILLION (1000 * 1000)
#define NUM_OF_ITERATION 1000

#define GET_CLOCK_SEC (clock() / (double) CLOCKS_PER_SEC)
#define RANDF (rand() / (double) RAND_MAX)

#define DECL_SCALAR_FN_BENCH(fn)        \
static inline void bench_##fn(void) {   \
    fn(RANDF);                          \
}

#define DECL_VECTOR_FN_BENCH(fn)        \
static inline void bench_##fn(void) {   \
    __m128 x = _mm_set_ps1(RANDF);      \
    fn(x);                              \
}

void run_bench(const char *s, void ( *fn )(void)) {
    double start = GET_CLOCK_SEC, end;
    double niter = 0;
    do {
        fn();
        niter++;
        end = GET_CLOCK_SEC;
    } while (end - start < BENCH_DURATION);
    printf("%10.3f millions of %s() executed in %.1f seconds\n", niter / MILLION, s, BENCH_DURATION);
}

DECL_SCALAR_FN_BENCH(sinf)
DECL_VECTOR_FN_BENCH(sin_ps)

DECL_SCALAR_FN_BENCH(cosf)
DECL_VECTOR_FN_BENCH(cos_ps)

DECL_SCALAR_FN_BENCH(tanf)
DECL_VECTOR_FN_BENCH(tan_ps)

DECL_SCALAR_FN_BENCH(atanf)
DECL_VECTOR_FN_BENCH(atan_ps)

DECL_SCALAR_FN_BENCH(stupid_atan2f)
DECL_VECTOR_FN_BENCH(stupid_atan2_ps)

int main(int argc, char **argv) {

    run_bench("sinf", bench_sinf);
    run_bench("sin_ps", bench_sin_ps);

    run_bench("cosf", bench_cosf);
    run_bench("cos_ps", bench_cos_ps);

    run_bench("tanf", bench_tanf);
    run_bench("tan_ps", bench_tan_ps);

    run_bench("atanf", bench_atanf);
    run_bench("atan_ps", bench_atan_ps);

    run_bench("atan2f", bench_stupid_atan2f);
    run_bench("atan2f_ps", bench_stupid_atan2_ps);
    return 0;
}
