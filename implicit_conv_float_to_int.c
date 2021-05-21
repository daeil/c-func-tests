#include <stdio.h>

int main(int argc, char** argv) {
    float f = 0.1857;
    for (int i=0; i<16; i++) {
        f += 0.01f;
        int d = f / 0.1f;
        printf("f=%f, d=%i\n", f, d);
    }

    return 0;
}
