#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char** argv) {
    unsigned char test[] = {0x01, 0x02};
    unsigned short i;
    memcpy(&i, test, 2);

    printf("i=%x\n", i);

    unsigned short big = htons(i);
    i = htons(i);
    printf("big=%x, i=%x\n", big, i);

    return 0;
}
