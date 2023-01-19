#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define MAX_PAYLOAD (1024 * 1024)

int main(int argc, char **argv)
{
    uint8_t buf[MAX_PAYLOAD];
    for (int i = 0; i < sizeof(buf); i++) {
        buf[i] = i;
    }

    Byte compr[MAX_PAYLOAD];
    Byte uncompr[MAX_PAYLOAD];

    uLong comprLen = MAX_PAYLOAD;
    uLong uncomprLen = comprLen;

    int ret = compress(compr, &comprLen, (const Bytef *)buf, sizeof(buf));
    printf("ret=%d, compress: %ld -> %ld\n", ret, sizeof(buf), comprLen);

    ret = uncompress(uncompr, &uncomprLen, compr, comprLen);
    printf("ret=%d, uncompress: %ld -> %ld\n", ret, comprLen, uncomprLen);

    ret = memcmp(buf, uncompr, uncomprLen);
    printf("ret=%d\n", ret);

    return 0;
}
