#include <stdio.h>
#include <math.h>

#define D2R M_PI / 180.0f
#define R2D 180.0f / M_PI

int main(int argc, char** argv) {


    for (float d=0; d<=90; d++) {
        printf("sin(%f), cos(%f)\n", sin(d * D2R), cos(d * R2D));
    }
    return 0;
}
