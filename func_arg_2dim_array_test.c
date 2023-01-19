#include <stdio.h>
#include <string.h>
#include <stdint.h>

struct A {
    int i;
    int j;
};

#define ROW 2
#define COL 3

// OK
// static void mul_10(uint8_t (*dst)[COL], const uint8_t (*src)[COL]) 

static void mul_10(struct A dst[ROW][COL], const struct A src[ROW][COL])
{
    for (int i=0; i<ROW; i++) {
        for (int j=0; j<COL; j++) {
            dst[i][j].i = src[i][j].i * 10;
            dst[i][j].j = src[i][j].j * 100;
        }
    }
}

int main(int argc, char** argv) {

    struct A in[ROW][COL];
    for (int i=0; i<ROW; i++) {
        for (int j=0; j<COL; j++) {
            in[i][j].i = i;
            in[i][j].j = j;
        }
    }
    struct A out[ROW][COL];
    memset(out, 0, sizeof(out));

    mul_10(out, in);

    for (int i=0; i<ROW; i++) {
        for (int j=0; j<COL; j++) {
            printf("(%hd, %hd) -> (%hd, %hd)\n", in[i][j].i, in[i][j].j, out[i][j].i, out[i][j].j);
        }
    }

    return 0;
}
