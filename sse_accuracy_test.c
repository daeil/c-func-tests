#include <stdio.h>
#include <math.h>
#include <time.h>
#include <float.h>


#include <xmmintrin.h>
#include <immintrin.h>
#include <emmintrin.h>

#define USE_SSE2
#include "sse_mathfun_extension.h"

#define PI  3.14159265358979f

typedef float float32_t;


static inline void unpack(__m128 p, float *x1, float *x2, float *x3, float *x4) {
    float x[4];
    _mm_store_ps(x, p);
    *x1 = x[0];
    *x2 = x[1];
    *x3 = x[2];
    *x4 = x[3];
}
#define pack(x1, x2, x3, x4) _mm_set_ps(x4, x3, x2, x1)

static inline void mm_sin(const float32_t *radv, float32_t *sinv)
{
    v4sf f128_rads = _mm_load_ps(radv);
    v4sf f128_sin_r = sin_ps(f128_rads);
    _mm_store_ps(sinv, f128_sin_r);
}

static inline void mm_cos(const float32_t *radv, float32_t *sinv)
{
    v4sf f128_rads = _mm_load_ps(radv);
    v4sf f128_sin_r = cos_ps(f128_rads);
    _mm_store_ps(sinv, f128_sin_r);
}

static inline void mm_sincos(const float32_t *radv, float32_t *sinv, float32_t *cosv)
{
    v4sf f128_rads = _mm_load_ps(radv);
    v4sf f128_sin_r;
    v4sf f128_cos_r;
    sincos_ps(f128_rads, &f128_sin_r, &f128_cos_r);
    _mm_store_ps(sinv, f128_sin_r);
    _mm_store_ps(cosv, f128_cos_r);
}

static inline void mm_atan2(const float32_t *y, float32_t *x, float32_t *atanv)
{
    v4sf f128_x = _mm_load_ps(x);
    v4sf f128_y = _mm_load_ps(y);
    v4sf f128_v = atan2_ps(f128_y, f128_x);
    _mm_store_ps(atanv, f128_v);
}

float frand() {
    union {
        float f;
        unsigned int i;
    } tmp;
    tmp.i = (unsigned int) rand();
    return tmp.f;
}

void run_bench( const char *s, int ( *fn )() )
{
    printf( "benching %20s ..", s );
    fflush( stdout );
    double t0 = uclock_sec(), t1, tmax = 1.0;
    double niter = 0;
    do {
        niter += fn();
        t1 = uclock_sec();
    } while( t1 - t0 < tmax );
    printf("%s: %ld millions of iternation in (%ld)\n", s, niter, t1-t0);
}

#define NUM_OF_ITERATION 1000

#define DECL_NATIVE_FUNC(fn)                    \
static inline int bench_##fn()                  \
{                                               \
    float x = 0.5f, y = 0;                      \
    for(int i = 0; i < NUM_OF_ITERATION; i++) { \
        for(int j = 0; j < 4; j++) {            \
            x += 1e-6f;                         \
            y += fn( x + 5 * ( j & 1 ) );       \
        }                                       \
    }                                           \
    return i;                                   \
}


#define DECL_SSE_FUNC( fn )         \
static inline int bench_##fn()      \
{                                   \
    v4sf bmin = _mm_set_ps1( 0.5 ); \
    v4sf bmax = _mm_set_ps1( 1.0 ); \
    v4sf x = _mm_set_ps1( 0.75 );   \
    for(int i = 0; i < NUM_OF_ITERATION; i++) {\
        x = fn( x );                \
        x = _mm_min_ps( x, bmax );  \
        x = _mm_max_ps( x, bmin );  \
    }                               \
    return i;                       \
}




int main(int argc, char** argv) {
    float input[4];
    float sin_n[4], sin_s[4];
    float cos_n[4], cos_s[4];

    DECL_NATIVE_FUNC(sinf);
    DECL_NATIVE_FUNC(cosf);
    DECL_NATIVE_FUNC(tanf);
    DECL_NATIVE_FUNC(sinf);
    DECL_SCALAR_FN_BENCH( cosf);
    DECL_SCALAR_FN_BENCH( tanf);
    DECL_SCALAR_FN_BENCH( atanf);

    for (float f=-90.f; f<90.f; f+=0.0004f) {
        for (int i=0; i<4; i++) {
            input[i] = f * (M_PI / 180.0f);
            sin_n[i] = sinf(input[i]);
            cos_n[i] = cosf(input[i]);
        }
        mm_sincos(input, sin_s, cos_s);
        for (int i=0; i<4; i++) {
            if (sin_n[i] == sin_s[i]) {
                printf("same(sin): %.20f, %.20f, %.20f, %.20f\n", input[i], sin_n[i], sin_s[i], sin_n[i] - sin_s[i]);
            } else {
                printf("diff(sin): %.20f, %.20f, %.20f, %.20f\n", input[i], sin_n[i], sin_s[i], sin_n[i] - sin_s[i]);
            }

            if (cos_n[i] == cos_s[i]) {
                printf("same(cos): %.20f, %.20f, %.20f, %.20f\n", input[i], cos_n[i], cos_s[i], cos_n[i] - cos_s[i]);
            } else {
                printf("diff(cos): %.20f, %.20f, %.20f, %.20f\n", input[i], cos_n[i], cos_s[i], cos_n[i] - cos_s[i]);
            }
        }
    }
    return 0;
}
