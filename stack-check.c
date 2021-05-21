#define _GNU_SOURCE

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define logV(fmt, ...) printf((fmt), ##__VA_ARGS__); printf("\n")

#define STACK_SIZE 2*1024*1024 // 2MB
#define MAGIC_PATTERN 90 // 0x5A (0101 1010)

//static struct {
//    int enabled;
//    uint8_t *pEndOfStack;
//    size_t stackSize;
//} memcheck[4];

typedef unsigned char uint8_t;

uint8_t *pEndOfStack;
int memchk_enabled;

void memcheck_report(void) {
    if (!memchk_enabled) return;
    int unusedSize = 0;
    // Find last dirty area
    uint8_t *p = pEndOfStack;
    while (*p == MAGIC_PATTERN) {
        unusedSize++;
        p++;
    }
    logV("%s, total=%d, used:%d unused=%d", __func__, STACK_SIZE, STACK_SIZE-unusedSize, unusedSize);
}

void memcheck_report_atexit(void) {
    memcheck_report();
}

void memcheck_init(void) {
    if (!memchk_enabled) return;
    uint8_t buf[STACK_SIZE];
    memset(buf, MAGIC_PATTERN, sizeof(buf));
    pEndOfStack = buf;
    logV("stack range=(%p - %p), size=%dKB, pEndOfStack=%d", buf, &buf[STACK_SIZE -1], STACK_SIZE/1024, *pEndOfStack);
}


size_t get_stack_size() {

    void *addr;
    size_t size;
    pthread_attr_t attr;
    pthread_getattr_np(pthread_self(), &attr);
    pthread_attr_getstack(&attr, &addr, &size);

    logV("%s, addr=%p, size=%ld", __func__, addr, size);

    return size;
}

void memcheck_setEnabled(int enable) {
    if (enable == memchk_enabled)
        return;
    memchk_enabled = enable;
    memcheck_init();
    //atexit(memcheck_report_atexit);
}

int memcheck_getEnabled(void) {
    return memchk_enabled;
}


static inline void use_stack_1MB(void) {
    char test[1024 * 1024];
    memset(test, 0xFF, sizeof(test));
    logV("test=%p", test);
}

static void *
loop(void *arg) {
    int a;
    printf("a=%p\n", &a);
    printf("loop started\n");
    get_stack_size();
    memcheck_setEnabled(1);
    sleep(1);
    use_stack_1MB();
    sleep(1);
    memcheck_report();
}

int main(int argc, char** argv)
{
    pthread_t pt;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, STACK_SIZE*2);
    pthread_create(&pt, &attr, loop, NULL);

    void *addr;
    size_t size;
    pthread_attr_getstack(&attr, &addr, &size);
    logV("%s, addr=%p, size=%ld", __func__, &addr, size);

    pthread_attr_destroy(&attr);

    sleep(3);
    return 0;
}
