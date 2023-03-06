#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char** argv) {
    unsigned char test[] = {0x00, 0x01};
    unsigned short little, big;
    printf("input: ");
    for (int i=0; i<sizeof(test); i++) {
        printf("%02x ", test[i]);
    }
    printf("\n");

    //little = *(unsigned short *) test;
    memcpy(&little, test, 2);
    big = htons(little);

    printf("little=%d(0x%04hx), big=%d(0x%04hx)\n", little, little, big, big);

    return 0;
}
