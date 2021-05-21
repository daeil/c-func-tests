#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


void printLog(const char *fmt, va_list valist)
{
#if 1

    int size = 0;
    char* p = NULL;

    va_list l;
    va_copy(l, valist);
    size = vsnprintf(p, 0, fmt, l); // get size of valist and null terminator
    size++; // for \0
    va_end(l);

    //size = 1024;

    printf("size:%d\n", size);

    p = malloc(size);
    if (p == NULL) {
        return;
    }
    vsprintf(p, fmt, valist);
    printf("%s(%s) %s\n", "LEVEL", "TAG", p);

    free(p);
#else
    int size = 0;
    char *p = NULL;
    va_list ap;

    /* Determine required size */
    //va_start(ap, fmt);
    size = vsnprintf(p, size, fmt, );
    //va_end(ap);

    if (size < 0)
        return size;

    size++;             /* For '\0' */
    p = malloc(size);
    if (p == NULL)
        return -1;

    va_start(ap, fmt);
    size = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    if (size < 0) {
        free(p);
        return -1;
    }

    printf("%s\n", p);
#endif

}


#define MAX_SIZE 8
void printLog2(const char *fmt, va_list valist) {
    char buf[MAX_SIZE + 10] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int cnt = vsnprintf(buf, MAX_SIZE, fmt, valist);
    for (int i=0; i< sizeof(buf); i++) {
        printf("0x%x\n", buf[i]);
    }
    printf("%d, %s\n", cnt, buf);
}

void print(const char *fmt, ...)
{
    va_list valist;
    va_start(valist, fmt);

    printLog2(fmt, valist);

    va_end(valist);
}

int print2(const char *fmt, ...)
{

    int size = 0;
    char *p = NULL;
    va_list ap;

    /* Determine required size */
    va_start(ap, fmt);
    size = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    if (size < 0)
        return size;

    size++;             /* For '\0' */
    p = malloc(size);
    if (p == NULL)
        return -1;

    va_start(ap, fmt);
    size = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    if (size < 0) {
        free(p);
        return -1;
    }

    return printf("%s\n", p);
}

int main () {
    int i;
    for (i=0; i<10; i++) {
        //print2("%s, %d", "DEAN", i);
        print("%s, %d", "DEAN ABCDEFGHI", i);
    }
}
