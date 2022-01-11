#include <stdio.h>
#include <stdlib.h>

//#define N_MAX (1000 * 1000)
//#define MAX_VALUE (1e12)


#define N_MAX (1000)
#define MAX_VALUE (1e6)

static inline long mul(long start, long size) {
    long r = 1;
    for (long i=0; i<size; i++) {
        r = r * (start + i);
    }
    return r;
}

static inline int isContain(long mat[], long size, long value) {
    if (size < 0) return 0;
    for (long i=0; i<size; i++) {
        if (mat[i] == value) return 1;
    }
    return 0;
}

static inline int compar(const void *a, const void *b) {
    return (*(long *)a - *(long *)b);
}

#define SZ_MAT (N_MAX * 12)
long get_result(int n) {
    long n = 0;
    for (long i=1; i<N_MAX; i++) {
        for (long j=2; j<12; j++) {
            long result = mul(i, j);
            printf("result=%ld\n", result);
            if (result > MAX_VALUE) break;
            if (isContain(matrix, n-1, result) == 0) {
                matrix[n] = result;
                n++;
                if (n >= SZ_MAT) break;
            }
        }
        if (n >= SZ_MAT) break;
    }

    qsort(matrix, SZ_MAT, sizeof(long), compar);

    for (int i=0; i<10; i++) {
        printf("%d = %ld\n", i, matrix[i]);
    }
    return matrix[i];
}

int main(int argc, void** argv) {
    printf("100 : %ld", get_result(100));
}

