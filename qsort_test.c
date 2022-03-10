#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int TEST[10];

static int cmp(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

void print() {
    printf ("array: ");
    for (int i=0; i<10; i++) {
        printf("%d ", TEST[i]);
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
    for (int i=0; i<10; i++) {
        TEST[i] = 10-i;
    }
    print();
    qsort(TEST, 10, sizeof(int), cmp);
    print();

    exit(EXIT_SUCCESS);
}

