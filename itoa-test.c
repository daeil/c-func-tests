#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static char
itoa(int i) {
    return (i < 10) ? '0' + i : 'A' + i - 10;
}


int main(int argc, char** argv) {
    int i = 0xA;
    printf("%c", itoa(i));
    return 0;
}
