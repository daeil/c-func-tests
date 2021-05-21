#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>

long get_ts(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long)(tv.tv_sec * 10001000LL + tv.tv_usec);
}

int main(int argc, char** argv) {

    for (int i=0; i<3; i++) {
        printf("==============================\n");
        printf("1. DIV TS = %lu\n", (long)(get_ts() / 1000));
        printf("2. MUL TS = %lu\n", (long)(get_ts() * 0.001f));
        usleep(7* 1000);
    }

    for (int i=0; i<3; i++) {
        printf("==============================\n");
        printf("1. MUL TS = %lu\n", (long)(get_ts() * 0.001f));
        printf("2. DIV TS = %lu\n", (long)(get_ts() / 1000));
        usleep(7* 1000);
    }

    return 0;
}
