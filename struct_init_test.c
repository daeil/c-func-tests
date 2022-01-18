#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int aa;
    int ab;
    int ac;
} A;

typedef struct {
    int ba;
    A bb[10];
} B;

void test() {
    //B data[10];
    //B data[10] = {};
    B data[10] = {0};
    char *p = (char *) data;
    for (int i=0; i<sizeof(data); i++) {
        printf("%02x", *p++);
        if ((i % 16) == 15) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

void init() {
    int buf[1024];
    memset(buf, 1, 1024);
}

int main (int argc, char** argv) {
    init();
    test();
    return 0;
}
