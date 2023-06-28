#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int TEST[10] = { 8, 9, 7, 6, 5, 4, 3, 2, 0, 1 };

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
    print();
    qsort(TEST, 10, sizeof(int), cmp);
    print();

    exit(EXIT_SUCCESS);
}
