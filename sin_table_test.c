#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define	PI							3.14159265358979f
#define	DEG2RAD						0.01745329251994f /* PI/180 */
#define	RAD2DEG						57.2957795130824f /* 180/PI */

#include "SinTable.h"
#include "TanTable.h"

#define RESOLUTION 1e-2
#define TABLE_SIZE (90 / RESOLUTION)

static float getTanf(float r)
{
    float d = r * RAD2DEG;
    d = fmodf(d, 180);
    if (d < 0) d += 180;
    int sign = 1;
    if (d > 90) {
        sign = -1;
        d = 180 - d;
    }
    int index = (int) roundf(d / RESOLUTION);
    return tan_table[index] * sign;
}

static float getSinf(float r)
{
    float degree = r * RAD2DEG;
    if (degree >= 360) {
        degree = fmodf(degree, 360);
    } else if (degree < 0) {
        degree = degree + 360;
    }
    float convD = degree;
    if (degree >= 180) {
        convD = degree - 180;
    }
    if (convD > 90) {
        convD = 180 - convD;
    }
    int index = (int) roundf(convD * 100.0f);
    float result = sinTable[index];
    if (degree >= 180) {
        result = -result;
    }
    return result;
}

int main(int argc, char** argv)
{
    for (int i=-180; i<180; i++) {
        float d = i;
        float r = d * DEG2RAD;
        //printf("sin: %f vs %f\n", sinf(r), getSinf(r));
        //printf("cos: %f vs %f\n", cosf(r), getCosf(r));
        printf("%f: tanf()=%f vs getTanf()=%f\n", d, tanf(r), getTanf(r));
        //printf("f=%f, fmodf=%f\n", i * 1.f, fmodf(i, 90));
    }
    return 0;
}
