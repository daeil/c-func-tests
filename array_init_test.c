#include <stdio.h>
#include <string.h>


void
print_array(int a[]) {
    for (int i=0; i<10; i++) {
        printf(" a[%d]=%d\n", i, a[i]);
    }
}

void
prep() {
    int a[10];
    memset(a, 0xff, 10);
}

void
init_0() {
    int a[10];
    printf("%s\n", __func__);
    print_array(a);
}

void
init_1() {
    int a[10] = { -1 };
    printf("%s\n", __func__);
    print_array(a);
}


void
init_2() {
    int a[10] = {[0 ... 9] = -1 };
    printf("%s\n", __func__);
    print_array(a);
}

void
init_3() {
    int a[10] = {-1,-1,-1,-1,-1, -1,-1,-1,-1,-1};
    printf("%s\n", __func__);
    print_array(a);
}

void
init_4() {
    int a[10];
    memset(a, -1, 10);
    printf("%s\n", __func__);
    print_array(a);
}


int main(int argc, char** argv) {

    prep();

    init_0();
    init_1();
    init_2();
    init_3();
    init_4();
    return 0;
}
