#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int id;
	float v;
} Point;
static Point TEST[10];

#define CMP(a,b) (a >= b) ? 1 : -1

int cmp(const void* pv_A, const void* pv_B)
{
	const Point *pst_A = (Point *)pv_A;
	const Point *pst_B = (Point *)pv_B;
	return CMP(pst_B->v, pst_A->v);
}

void print() {
    printf ("TEST: ");
    for (int i=0; i<10; i++) {
        printf("%d: %.2f\n", TEST[i].id, TEST[i].v);
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
    for (int i=0; i<10; i++) {
        TEST[i].id = i;
        TEST[i].v = (float) (i % 5) * 0.5;
    }
    print();
    qsort(TEST, sizeof(TEST)/sizeof(TEST[0]), sizeof(TEST[0]), cmp);
    print();

    exit(EXIT_SUCCESS);
}

