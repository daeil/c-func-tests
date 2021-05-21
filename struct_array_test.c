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

#define MAX 20
int main (int argc, char** argv) {
    B data[MAX] = { 0 };

    for (int i=0; i<MAX; i++) {
        B *p = data + i;
        p->ba = i;
    }

    for (int i=0; i<MAX; i++) {
        B b;
        memcpy(&b, data + i, sizeof(B));
        printf("%d: %d\n", i, b.ba);
    }

    for (int i=0; i<MAX; i++) {
        B *p = data + i;
        printf("%d: %d\n", i, p->ba);
    }

    return 0;
}
