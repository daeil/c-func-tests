#include <stdio.h>
#include <stdint.h>
#include <string.h>


struct TEST {
    uint16_t pitch;
    uint16_t yaw;
    uint16_t roll;
    uint8_t errorStatus;
} result;


int main(int argc, char** argv) {

    const char EcuId[] = "FR_C_LDR_TEST";
    printf("sizeof(%s) = %ld, sizeof(struct TEST)=%ld\n", EcuId, sizeof(EcuId), sizeof(struct TEST));
    return 0;
}
