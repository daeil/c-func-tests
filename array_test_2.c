#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint8_t arr[8][16];
int main(int argc, char** argv) {

    uint8_t *p = (uint8_t *)arr;
    for (int i=0; i<sizeof(arr); i++) {
        *(p+i) = i;
    }

    for (int i=0; i<sizeof(arr); i++) {
        printf("%02x ", *(p + i));
    }

    printf("\n");
    return 0;
}
