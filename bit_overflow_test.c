#include <stdio.h>
#include <stdint.h>

int main(int argc, char** argv) {
    uint32_t i = 0xFF;

    printf("i=0x%x\n", i);
    printf("i<<24 = 0x%x\n", i << 24);
    printf("i<<25 = 0x%x\n", i << 25);

    return 0;
}
