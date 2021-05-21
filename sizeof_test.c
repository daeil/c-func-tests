#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {

    const char EcuId[] = "FR_C_LDR_TEST";
    printf("sizeof(%s) = %ld\n", EcuId, sizeof(EcuId));
    return 0;
}
