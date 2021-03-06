#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SIZ 8
int* getarray() {
    int array[SIZ];
    for (int i=0; i<SIZ; i++) {
        array[i] = i;
    }
    return array;
}


int find_index_of_most_voted_member(const uint32_t arr[], const uint32_t size) {
    uint32_t index;
    uint32_t max_value;
    for (uint32_t i = 0; i < size; i++) {
        printf("DEAN %d\n", i);
        if (arr[i] > max_value) {
            max_value = arr[i];
            index = i;
        }
    }
    return index;
}


void test(float f[SIZ]) {
    printf("%s\n", __func__);
    for(int i=0; i<SIZ; i++) {
        printf("f[%d]=%f\n", i, f[i]);
    }
}

int main(int argc, char** argv) {
    //unsigned char array[8] = {0,1,2,3,4,5,6,7};
#if 0
    int* r = getarray();
    for (int i=0; i<SIZ; i++) {
        printf("%d\n", *(r+i));
    }
#endif

#if 0

    float d[SIZ][SIZ];
    for (int i=0; i<SIZ; i++) {
        for (int j=0; j<SIZ; j++) {
            d[i][j] = i*10 + j;
        }
    }

    for (int i=0; i<10; i++) {
        float* f = d[i];
        for (int j=0; j<10; j++) {
            printf("%03d=%.02f\n", i*10 + j, d[i][j]);
            printf("f=%.02f\n", *(f+j));

        }
    }

    printf("sizeof(d)=%ld\n", sizeof(d));


    {
        float d1[SIZ][SIZ];
        float d2[SIZ][SIZ];

        float (*input[2])[SIZ];
        for (int i=0; i<2; i++) {
            input[i] = d1;
            for (int j=0; j<SIZ; j++) {
                test(input[i][j]);
            }
        }
    }


    {
        int plane1_vec_voting_L[100] = {0,};
        printf("start\n");
        int index = find_index_of_most_voted_member(plane1_vec_voting_L, 100);
        printf("end, %d\n", index);
    }

#endif
    {
#define VERSION(arr3) (((uint32_t)arr3[0] << 24) | ((uint32_t)'.' << 16) | ((uint32_t)arr3[1] << 8) | ((uint32_t)arr3[2]))

        char arr[9];
        char vl[3] = {0x01, 0x02, 0x03};
        char vr[3] = {0x04, 0x05, 0x06};
        int ivl = VERSION(vl);
        int ivr = VERSION(vr);
        memcpy(arr, &ivl, 4);
        arr[4] = ' ';
        memcpy(arr+5, &ivr, 4);

        for(int i=0; i<9; i++) {
            printf("%d: 0x%02x\n", i, arr[i]);
        }

#undef VERSION
    }



    return 0;
}

