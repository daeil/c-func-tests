#include <stdio.h>
typedef struct _A {
    float f;
    int i;
} A;

typedef struct _B {
    float f;
    int i;
} B;

int main(int argc, char** argv) {

    A *a;
    B b;

    b.f = 3.141592f;
    b.i = 12345;

    a = (A *)&b;

    printf("a(%p) a->f=%f, a->i=%d\n", a, a->f, a->i);
    printf("b(%p) b.f=%f, b.i=%d\n", &b, b.f, b.i);
    return 0;
}
