#include <stdio.h>
#include <xmmintrin.h>

#define MAX(a,b) ((a > b) ? a : b)
static float sData[16];


void test_if(void) {
    // SISD
    float subTotal = 0.f;
    for (int i=0; i<16; i++) {
        if ((i%4) == 0) {
            subTotal += sData[i];
        }
    }
    printf("subTotal=%f\n", subTotal);


    // SIMD
    subTotal = 0.f;
    __m128 mZeros = _mm_set_ps(0.f, 0.f, 0.f, 0.f);
    __m128 mSubTotal = _mm_set_ps (0.f, 0.f, 0.f, 0.f);
    for (int i=0; i<16; i+=4) {
        __m128 tmp = _mm_set_ps((float)(i%4), (float)((i+1)%4), (float)((i+2)%4), (float)((i+3)%4));
        __m128 cond = _mm_cmpeq_ps(tmp, mZeros);
        __m128 d = _mm_set_ps(sData[i], sData[i+1], sData[i+2], sData[i+3]);
        d = _mm_and_ps(cond, d);
        mSubTotal = _mm_add_ps(mSubTotal, d);
    }

    float totals[4];
    _mm_store_ps(totals, mSubTotal);
    for (int i=0; i<4; i++) {
        subTotal += totals[i];
    }
    printf("subTotal=%f\n", subTotal);
}


int main(int argc, char** argv) {

    for(int i=0; i<16; i++) {
        sData[i] = rand();
    }


    // SISD
    float max = 0;
    for (int i=0; i<16; i++) {
        max = MAX(sData[i], max);
    }
    printf("max=%f\n", max);

    // SIMD
    __m128 mMax = _mm_set_ps(0.f, 0.f, 0.f, 0.f);
    for (int i=0; i<4; i+=4) {
        __m128 temp = _mm_set_ps(sData[i], sData[i+1], sData[i+2], sData[i+3]);
        mMax = _mm_max_ps(mMax, temp);
    }

    float maxs[4];
    _mm_store_ps(maxs, mMax);
    for (int i=0; i<4; i++) {
        max = MAX(maxs[i], max);
    }
    printf("max=%f\n", max);

    test_if();

    return 0;
}
