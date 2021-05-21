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
static inline __m128 pack(float x1, float x2, float x3, float x4) {
    return _mm_set_ps(x4, x3, x2, x1);
}

//#define pack(x1, x2, x3, x4) _mm_set_ps(x4, x3, x2, x1)


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

static void sincos_dean2(__m128 x, __m128 *s, __m128 *c) {
    float xf[4];
    float sf[4];
    float cf[4];
    unpack(x, &xf[0], &xf[1], &xf[2], &xf[3]);
    for (int i=0; i<4; i++) {
        sf[i] = sinf(xf[i]);
        printf("xf[i]=%f, sf[i]=%f\n", xf[i], sf[i]);
        cf[i] = cosf(xf[i]);
    }
    __m128 rs = pack(sf[0], sf[1], sf[2], sf[3]);
    __m128 rc = pack(cf[0], cf[1], cf[2], cf[3]);
    *s = rs;
    *c = rc;
}

static void sincos_dean(__m128 x, __m128 *s, __m128 *c) {
    float xf[4];
    float sf[4];
    float cf[4];
    unpack(x, &xf[0], &xf[1], &xf[2], &xf[3]);
    for (int i=0; i<4; i++) {
        sf[i] = sinf(xf[i]);
        cf[i] = cosf(xf[i]);
    }
    *s = pack(sf[0], sf[1], sf[2], sf[3]);
    *c = pack(cf[0], cf[1], cf[2], cf[3]);
}


static __m128 atan2_dean(__m128 y, __m128 x) {
    float xf[4];
    float yf[4];
    float rf[4];
    unpack(x, &xf[0], &xf[1], &xf[2], &xf[3]);
    unpack(y, &yf[0], &yf[1], &yf[2], &yf[3]);

    for (int i=0; i<4; i++) {
        rf[i] = atan2f(yf[i], xf[i]);
    }
    return pack(rf[0], rf[1], rf[2], rf[3]);
}

static __m128 sqrt_dean(__m128 x) {
    float xf[4];
    float rf[4];
    unpack(x, &xf[0], &xf[1], &xf[2], &xf[3]);
    for (int i=0; i<4; i++) {
        rf[i] = sqrtf(xf[i]);
    }
    return pack(rf[0], rf[1], rf[2], rf[3]);
}


float frand() {
    union {
        float f;
        unsigned int i;
    } tmp;
    tmp.i = (unsigned int) rand();
    return tmp.f;
}

int main(int argc, char** argv) {
    float input_1[4], input_2[4];
    float sin_n[4], sin_s[4];
    float cos_n[4], cos_s[4];
    float atan_n[4], atan_s[4];
    float atan_n2[4], atan_s2[4];
    unsigned long int total = 0, failcount = 0;

    __m128 in1, in2;
    __m128 s, c, t, t1;

    for (float f=0; f<90.f; f+=0.004f) {
        for (int i=0; i<4; i++) {
            input_1[i] = f + (i * 0.0001f) * (M_PI / 180.0f);
            input_2[i] = f + (i * 0.0001f) * (M_PI / 180.0f) + 0.00003f;

            sin_n[i] = sinf(input_1[i]);
            cos_n[i] = cosf(input_1[i]);
            atan_n[i] = atan2f(input_1[i], input_2[i]);
            atan_n2[i] = atan2f(cos_n[i], sin_n[i]);
        }

        in1 = pack(input_1[0], input_1[1], input_1[2], input_1[3]);
        in2 = pack(input_2[0], input_2[1], input_2[2], input_2[3]);
        sincos_dean(in1, &s, &c);
        t = atan2_ps(in1, in2);
        t1 = atan2_ps(c, s);
        unpack(s, &sin_s[0], &sin_s[1], &sin_s[2], &sin_s[3]);
        unpack(c, &cos_s[0], &cos_s[1], &cos_s[2], &cos_s[3]);
        unpack(t, &atan_s[0], &atan_s[1], &atan_s[2], &atan_s[3]);
        unpack(t1, &atan_s2[0], &atan_s2[1], &atan_s2[2], &atan_s2[3]);

        mm_sincos(input_1, sin_s, cos_s);
        mm_atan2(input_1, input_2, atan_s);
        //mm_atan2(cos_s, sin_s, atan_s2);

        for (int i=0; i<4; i++) {
            total += 4;
            if (sin_n[i] == sin_s[i]) {
                printf("same(sin): input:%f, native:%f, sse:%f, diff:%.20f\n", input_1[i], sin_n[i], sin_s[i], sin_n[i] - sin_s[i]);
            } else {
                failcount ++;
                printf("diff(sin): input:%f, native:%f, sse:%f, diff:%.20f\n", input_1[i], sin_n[i], sin_s[i], sin_n[i] - sin_s[i]);
            }

            if (cos_n[i] == cos_s[i]) {
                printf("same(cos): %f, %f, %f, %.20f\n", input_1[i], cos_n[i], cos_s[i], cos_n[i] - cos_s[i]);
            } else {
                failcount ++;
                printf("diff(cos): %f, %f, %f, %.20f\n", input_1[i], cos_n[i], cos_s[i], cos_n[i] - cos_s[i]);
            }

            if (atan_n[i] == atan_s[i]) {
                printf("same(atan): %f, %f, %f, %.20f\n", input_1[i], atan_n[i], atan_s[i], atan_n[i] - atan_s[i]);
            } else {
                failcount ++;
                printf("diff(atan): %f, %f, %f, %.20f\n", input_1[i], atan_n[i], atan_s[i], atan_n[i] - atan_s[i]);
            }

            if (atan_n2[i] == atan_s2[i]) {
                printf("same(atan): %f, %f, %f, %.20f\n", input_1[i], atan_n2[i], atan_s2[i], atan_n2[i] - atan_s2[i]);
            } else {
                failcount ++;
                printf("diff(atan): %f, %f, %f, %.20f\n", input_1[i], atan_n2[i], atan_s2[i], atan_n2[i] - atan_s2[i]);
            }
            if (sin_n[i] * cos_n[i] == sin_s[i] * cos_s[i]) {
                printf("same(sin * cos): %.20f\n", (sin_n[i] * cos_n[i]) - (sin_s[i] * cos_s[i]));
            } else {
                printf("diff(sin * cos): %.20f\n", (sin_n[i] * cos_n[i]) - (sin_s[i] * cos_s[i]));
             }

        }
        if (total % (10000) == 0) {
            printf("total=%lu, failcount=%lu\n", total, failcount);
        }
    }
    return 0;
}
