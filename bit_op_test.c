#include <stdio.h>
#include <stdint.h>

#define B0 (1 << 0)
#define B1 (1 << 1)
#define B2 (1 << 2)
#define B3 (1 << 3)

int main(int argc, char** argv) {

    uint8_t a, b, c;
    
    a = B1 | B2;
    b = B1;

    c = (a & (~B1)) | (b & B1);

    //c = (a | B1) & (b & B1);

    printf("a=%x, b=%x, c=%x\n", a,b,c);
    return 0;
}
