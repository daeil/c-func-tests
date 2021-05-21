#include <stdio.h>
#include <stdint.h>

int main(int argc, char** argv) {
    uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t *pu8_Data;

    int32_t s32_I = 0;
    pu8_Data = data;

    uint64_t u[8];
    uint64_t result;

    for (s32_I = 0; s32_I < 8; s32_I++) {
        u[s32_I] = (uint64_t)(*(pu8_Data + s32_I)) << (8 * s32_I);
        printf("A %0lx \n", u[s32_I]);

        u[s32_I] = ((uint64_t)*(pu8_Data + s32_I)) << (8 * s32_I);
        //u= ((uint64_t)*(pu8_Data + s32_I)) << (8 * s32_I);
        printf("B %0lx \n", u[s32_I]);

        u[s32_I] = (*(uint64_t *)(pu8_Data + s32_I)) << (8 * s32_I);
        printf("C %0lx \n", u[s32_I]);
    }
    result = u[0] | u[1] | u[2] | u[3] | u[4] | u[5] | u[6] | u[7];
    printf("RESULT: %0lx \n", result);


/*
    uint64_t u;
    uint8_t u8 = 1;
    u = (uint64_t)(u8 << 48);

    printf("%0lx \n", u);
    u = (uint64_t)(((uint64_t)u8) << 48);
    printf("%0lx \n", u);
    u = (uint64_t)(1 << 48);
    printf("%0lx \n", u);
*/

    return 0;
}
