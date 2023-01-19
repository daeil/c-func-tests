#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define VERSION(arr3) ((uint8_t[]){(arr3[0]), '.', (arr3[1]), (arr3[2])})
void version() {
    uint8_t version[] = {'A', '0', '1'};
    uint8_t data[4];

    memcpy(data, VERSION(version), sizeof(data));
    printf("%02x %02x %02x %02x\n", data[0], data[1], data[2], data[3]);

}
#undef VERSION

int main(int argc, char** argv) {

    // 2018-09-03 (0x33 0x30 0x2D 0x39 0x30 0x2D 0x38 0x31 0x30 0x32)
    // => 0x20 0x18 0x03 0x06
    const uint8_t raw[] = {0x33, 0x30, 0x2D, 0x39, 0x30, 0x2D, 0x38, 0x31, 0x30, 0x32};
    uint8_t ret[4];

    /*
    int index = 0;
    int cnt = 1;
    uint8_t tmp;
    for (int i=sizeof(raw); i>=0; i--) {
        int v = raw[i] - 0x30;
        if (v < 0) continue;
        cnt *= -1;
        if (cnt < 0) {
            tmp = v << 4;
        } else {
            ret[index] = tmp | v;
            index++;
        }
    }
    */

    ret[0] = ((raw[9]-0x30) << 4) + (raw[8]-0x30);
    ret[1] = ((raw[7]-0x30) << 4) + (raw[6]-0x30);
    ret[2] = ((raw[4]-0x30) << 4) + (raw[3]-0x30);
    ret[3] = ((raw[1]-0x30) << 4) + (raw[0]-0x30);


    printf("INPUT : ");
    for (int i=0; i<sizeof(raw); i++) {
        printf("0x%02x ", raw[i]);
    }
    printf("\n");

    printf("OUTPUT: ");
    for (int i=0; i<sizeof(ret); i++) {
        printf("0x%02x ", ret[i]);
    }
    printf("\n");

    version();
    return 0;
}
