#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <time.h>

#define KB (1024)
#define MB (1024 * 1024)

static inline unsigned long get_timestamp(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1e3 + tv.tv_usec * 1e-3;
}

void check_performance(unsigned long size) {
    unsigned char *p1, *p2;
    unsigned long t1, elap_memcpy, elap_memset;

    p1 = malloc(size);
    p2 = malloc(size);

    // memset
    t1 = get_timestamp();
    memset(p1, 0, size);
    elap_memset = get_timestamp() - t1;

    // memcpy
    t1 = get_timestamp();
    memcpy(p2, p1, size);
    elap_memcpy = get_timestamp() - t1;

    free(p1);
    free(p2);

    printf("%ldMB: memset:%ldms, memcpy:%ldms\n", size / MB, elap_memset, elap_memcpy);
}

int main(int argc, char *argv[])
{
    for (int i=0; i<=1000; i+=100) {
        check_performance(i*MB);
    }
    return 0;
}
