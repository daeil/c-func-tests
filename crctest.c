#include <stdio.h>
#include <stdint.h>

static uint16_t CRC_TABLE[256] = { };

uint16_t getCrc16Table2(uint16_t u16_index)
{
    uint16_t u16_tableEle = (u16_index << 8);
    for (char i = 0; i < 8; i++)
      u16_tableEle = (u16_tableEle & 0x8000L) ? (u16_tableEle << 1) ^ 0x1021
                                              : (u16_tableEle << 1);
    return u16_tableEle;
}

void createCrcTable() {
    for (uint16_t i=0; i<=0xFF; i++) {
        CRC_TABLE[i] = getCrc16Table2(i);
        printf("%d:%04x\n", i, getCrc16Table2(i));
    }
}

uint16_t getCrc16Table(uint16_t u16_index)
{
    return CRC_TABLE[u16_index];
}

int main (int argc, char** argv) {
    int i = 0x12345678;

    createCrcTable();
    for (i=0; i <= 0xFF; i++) {
        printf("0x%04x", getCrc16Table(i));
        if ((i % 8) != 7) {
            printf(" ");
        } else {
            printf("\n");
        }

    }

    return 0;
}
