#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <float.h>

#define	PI  3.14159265358979f

typedef float float32_t;
float SINE_TABLE[9001];

/*
static inline float32_t getSinf(float32_t degree) {
    if (degree >= 360) {
        degree = fmodf(degree, 360);
    } else if (degree < 0) {
        degree = degree + 360;
    }
    float32_t tmpd = degree;
    if (degree >= 180) {
        tmpd = degree - 180;
    }
    if (tmpd > 90) {
        tmpd = 180 - tmpd;
    }

    int index = roundf(tmpd * 100.0f);
    float32_t result = SINE_TABLE[index];
    if (tmpd > 180) {
        result = -result;
    }
    float32_t r = degree * PI / 180.0f;
    float32_t s = sinf(r);
    if (fabsf(result - s) <= FLT_EPSILON) {
        printf("SAME, %2.5f %.20f %.20f\n", degree, result, s);
    } else {
        printf("DIFF, %2.5f %.20f %.20f\n", degree, result, s);
    }
    return result;
}

static inline float32_t getCosf(float32_t degree) {
    printf("cos ");
    return getSinf(degree + 90.0f);
}
*/

static inline float32_t getSinf(float32_t degree) {
    float d = degree;
    if (degree >= 360) {
        d = fmodf(degree, 360);
    } else if (degree < 0) {
        d = degree + 360;
    }
    float32_t convD = d;
    if (d >= 180) {
        convD = d - 180;
    }
    if (convD > 90) {
        convD = 180 - convD;
    }
    int index = roundf(convD * 100.0f);
    float32_t result = SINE_TABLE[index];
    if (d >= 180) {
        result = -result;
    }

    float s = sin(d * PI / 180.f);

    //if (fabsf(result - s) <= FLT_EPSILON) {
    if (result == s) {
        printf("SAME, %.5f %.20f %.20f, %d\n", degree, result, s, index);
    } else {
        printf("DIFF, %.5f %.20f %.20f, %d\n", degree, result, s, index);
    }

    return result;
}
static inline float32_t getCosf(float32_t degree) {
    return getSinf(degree + 90.0f);
}

float roundf2(float f) {
    return roundf(f * 100.f) / 100.f;
}

static void genSinTable()
{
    for (uint32_t data=0; data<=9000; data++) {
        float f = (float)(data / 100.f);
        float r = f * PI / 180.f;
        SINE_TABLE[data] = sinf(r);
    }
}
/*
static void genSinTable()
{
    int index = 0;
    for (float f=0; roundf2(f) <= 90.0f; f+=0.01f) {
        float r = roundf2(f) * PI / 180.f;
        SINE_TABLE[index++] = sinf(r);
    }
}
*/

int main(int argc, char** argv) {
    genSinTable();
    for (float f=0; f<=360.f; f += 0.01f) {
        float d = roundf2(f);
        float r1 = d * PI / 180.f;
        float r2 = (d + 90.f) * PI / 180.f;

        getSinf(d);

        if (sinf(r2) != cosf(r1)) {
            printf("sin(d+90) != cos(d), d:%f, s:%f, c:%f diff:%.20f\n", d, sinf(r2), cosf(r1), sinf(r2) - cosf(r1));
        }
        if (d > 90.f && d <= 180.f) {
            float r = (180.f - d) * PI / 180.f;
            if (sinf(r1) != sinf(r)) {
                printf("DIFF(sin(r) != sin(180-r), d:%f, s:%f, c:%f diff:%.20f\n", d, sinf(r1), sinf(r), sinf(r1) - sinf(r));
            }
        }

        if (d > 180.f && d <= 270.f) {
            float r = (d - 180.f) * PI / 180.f;
            if (sinf(r1) != -sinf(r)) {
                printf("DIFF(sin(r) != sin(r-180), d:%f, s:%f, c:%f diff:%.20f\n", d, sinf(r1), sinf(r), sinf(r1) + sinf(r));
            }
        }
        //getCosf(f);
    }
    return 0;
}

