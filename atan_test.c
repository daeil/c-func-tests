#include <stdio.h>
#include <math.h>

#include "common.h"

#define MIN_X 0.f
#define MAX_X 10.f
#define TABLE_SIZE 9000
static float TABLE[TABLE_SIZE+1] = {};


#define PI M_PI
#define atan_table TABLE
#define ATAN_TABLE_SIZE TABLE_SIZE
#define ATAN_MAX_X MAX_X

static void createAtanTable2()
{
    int idx = 0;
    for (float r = 0; r <= M_PI/2; r+= ((M_PI/2) / TABLE_SIZE)) {
        float x = 1 / tanf(r);
        TABLE[idx++] = atanf(x);
    }
}

static void createAtanTable()
{
    for (int i=0; i<=TABLE_SIZE; i++)
    {
        float x = i * MAX_X / TABLE_SIZE;
        TABLE[i] = atanf(x);
    }
}


static inline float32_t getAtanf(float32_t x)
{
    if (x > MAX_X) return M_PI/2;
	int32_t index = (int32_t) roundf (x * TABLE_SIZE / MAX_X);
    return TABLE[index];
}

static inline float32_t getAtanFromTable(float32_t x)
{
    if (x > ATAN_MAX_X) return PI / 2;
    float32_t v = x * ATAN_TABLE_SIZE / ATAN_MAX_X;
    float32_t x1, x2;
    x1 = atan_table[(int32_t) ceilf(v)];
    x2 = atan_table[(int32_t) floorf(v)];
    float r = x1 + ((x2 - x1) / (v - x1));
    return r;
}

static float32_t getAtan2f(float32_t y, float32_t x)
{
    float32_t result;
    if (x == 0 && y == 0) return 0.f;
    result = getAtanFromTable(fabsf(y / x));

    if (x >= 0 && y >= 0) return result;
    if (x >= 0 && y < 0) return -result;
    if (x < 0 && y >= 0) return M_PI - result;
    if (x < 0 && y < 0) return result - M_PI;

    return result;
}

int main(int argc, char** argv) {
    int count = 0;
    createAtanTable();

        for (float y=-5.f; y<=5.f; y += 1) {
    for (float x=-5; x<=5.f; x += 1) {
            float r = y / x;
            if (fabsf(atan2f(y,x) - getAtan2f(y,x)) > 0.001f) {
                printf("DIFF\n");
            }
            printf("%9f vs %9f\n", atan2f(y,x), getAtan2f(y,x));
        }
    }
    return 0;
}

