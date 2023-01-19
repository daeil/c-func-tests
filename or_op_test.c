#include <stdio.h>

static int
get_fail() {
    printf("%s\n", __func__);
    return -1;
}

static int
get_success() {
    printf("%s\n", __func__);
    return 0;
}




int main(int argc, char** argv) {
    int res = 0;

    res = res || get_fail();
    printf("res=%d\n", res);

    printf("0 || -1 = %d\n", (0 || -1));
    res = res || get_success();
    printf("res=%d\n", res);

    res = 0;
    res = res || (get_success() == 0) ? 0 : 1;
    printf("res=%d\n", res);
    res = res || (get_success() == 0) ? 0 : 1;
    printf("res=%d\n", res);

    return 0;
}
