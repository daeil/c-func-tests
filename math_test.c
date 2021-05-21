#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

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
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1e6 + tv.tv_usec;
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

static float getAtan2f(float y, float x) {
    __m128 xx = _mm_set_ps1(x);
    __m128 xy = _mm_set_ps1(y);
    float r[4];
    _mm_store_ps1(r, atan2_ps(xy, xx));
    return r[0];
}

void test() {

#if 0
    double d;
    for (double d=0; d<10; d++) {
        printf("pow(%lf, 0.5)=%lf\n", d, pow(d, 0.5));
    }
    int RangeMap[1800][900] = { 0, };
    printf("size=%lu\n", sizeof(RangeMap));

    float azim = 60.f;
    float x,y;

    x = cosf(azim * M_PI / 180.f);
    y = sinf(azim * M_PI / 180.f);

    float azim2 = atan2f(y, x) * 180.f / M_PI;
    printf("azim=%f, x=%f, y=%f, azim2=%f\n", azim, x, y, azim2);


    //float PTx=7.957153, PTy=-0.654197;
    float PTy=7.957153, PTx=-0.654197;
    //float PTx=0, PTy=0;
    float a = ceil((atan2(PTx, PTy) * 180 / M_PI) * 10);
    printf("atan2f(%f, %f) = %f, a=%f\n", PTx, PTy, atan2f(PTx, PTy), a);

    float nan = atof("NaN");
    printf("NaN=%f\n", nan);
    printf("sinf(nan)=%f\n", sinf(nan));
    printf("cosf(nan)=%f\n", cosf(nan));
    printf("pow(0.1, 2.0)=%f\n", pow(0.1, 2.0));


    {
    float a = 10;
    float d = 100;
    float r = 4;

    float f1 = (a + r) / 180.f * M_PI;
    float f2 = (a) / 180.f * M_PI;

    printf("sinf(f1)=%f, sinf(f2)=%f\n", sinf(f1), sinf(f2));

    }

    {

    float x, y;
    float t, r, d;

    for (float f=0; f<360.f; f+=1.f) {
        r = f / 180.f * M_PI;
        x = sinf(r);
        y = cosf(r);
        t = atan2f(y, x);
        d = t * 180.f / M_PI;
        printf("azm=%f, theta_d:%f, theta_r:%f, x=%f, y=%f\n", f, d, t, x, y);
    }
    }


#endif
    float x=29.759726;
    float y=7.236212;

#define	RAD2DEG						57.2957795130824f /* 180/PI */

	float result = fabsf(atan2f(x, y) * RAD2DEG);
    printf("atanf(%f,%f)=%f\n", x, y, result);

}


int
main(int argc, char *argv[])
{
    //sse_performance_check();
    //sse_accuracy_check();
    //f32_XCur=21.831652(0x41aea739), f32_YCur=23.644709(0x41bd285d);
    //f32_XComp=21.833870(0x41aeabc4), f32_YComp=24.065104(0x41c08555);


    {
    float r = 180.f;
    float pi= 3.141592f;
    printf("r=%f(0x%x), pi=%f(0x%x)\n", r, *((int *) &r), pi,  *((int *) &pi));

    int x1 = 0x41aea739;
    int y1 = 0x41bd285d;
    float f32_XCur = *((float *) &x1);
    float f32_YCur = *((float *) &y1);

    int x2 = 0x41aeabc4;
    int y2 = 0x41c08555;
    float f32_XComp = *((float *) &x2);
    float f32_YComp = *((float *) &y2);

    float m1 = atan2f(f32_YCur, f32_XCur);
    float s1 = getAtan2f(f32_YCur, f32_XCur);
    float final_m1 = m1 * 180.f / 3.141592f;
    float final_s1 = s1 * 180.f / 3.141592f;

    printf("data set #1\n");

    printf("math atan2f(%.8f, %.8f)=%.8f (0x%08x)\n", f32_YCur, f32_XCur, m1, *((int *) &m1));
    printf("math %f(0x%x) * 180.f / 3.131592f = %f(0x%x)\n", m1, *((int *) &m1), final_m1,  *((int *) &final_m1));
    printf("sse  atan2f(%.8f, %.8f)=%.8f (0x%08x)\n", f32_YCur, f32_XCur, s1, *((int *) &s1));
    printf("sse  %f(0x%x) * 180.f / 3.131592f = %f(0x%x)\n", s1, *((int *) &s1), final_s1,  *((int *) &final_s1));


    float m2 = atan2f(f32_YComp, f32_XComp);
    float s2 = getAtan2f(f32_YComp, f32_XComp);
    float final_m2 = m2 * 180.f / 3.141592f;
    float final_s2 = s2 * 180.f / 3.141592f;
    printf("data set #2\n");
    printf("math atan2f(%.8f, %.8f)=%.8f (0x%08x)\n", f32_YComp, f32_XComp, m2, *((int *) &m2));
    printf("math %f(0x%x) * 180.f / 3.131592f = %f(0x%x)\n", m2, *((int *) &m2), final_m2,  *((int *) &final_m2));
    printf("sse  atan2f(%.8f, %.8f)=%.8f (0x%08x)\n", f32_YComp, f32_XComp, s2, *((int *) &s2));
    printf("sse  %f(0x%x) * 180.f / 3.131592f = %f(0x%x)\n", s2, *((int *) &s2), final_s2,  *((int *) &final_s2));
    }

    printf("%f\n", 0.12);
    return EXIT_SUCCESS;
}
