#include <lzma.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD (1024 * 1024)

int compress(uint8_t *out, size_t *outlen, const uint8_t *in, size_t inlen)
{
    lzma_stream strm = LZMA_STREAM_INIT;
    uint32_t preset = 9;  // level: 0 - 9
    lzma_ret ret = lzma_easy_encoder(&strm, preset, LZMA_CHECK_CRC64);
    if (ret != LZMA_OK) {
        printf("lzma_easy_encoder error: %d\n", ret);
        return -1;
    }
    lzma_action action = LZMA_FINISH;
    strm.next_in = in;
    strm.avail_in = inlen;
    strm.next_out = out;
    strm.avail_out = inlen;
    printf("strm.avail_out=%ld\n", strm.avail_out);
    ret = lzma_code(&strm, action);
    if (ret != LZMA_STREAM_END) {
        printf("lzma_code error: %d\n", ret);
        return -1;
    }
    *outlen = inlen - strm.avail_out;
    printf("strm.avail_out=%ld\n", strm.avail_out);
    lzma_end(&strm);
    return 0;
}

int decompress(uint8_t *out, size_t *outlen, const uint8_t *in, size_t inlen)
{
    lzma_stream strm = LZMA_STREAM_INIT;
    lzma_ret ret = lzma_stream_decoder(&strm, UINT64_MAX, LZMA_CONCATENATED);
    if (ret != LZMA_OK) {
        printf("lzma_stream_decoder error: %d\n", ret);
        return -1;
    }
    lzma_action action = LZMA_FINISH;
    strm.next_in = in;
    strm.avail_in = inlen;
    strm.next_out = out;
    strm.avail_out = MAX_PAYLOAD;
    ret = lzma_code(&strm, action);
    if (ret != LZMA_STREAM_END) {
        printf("lzma_code error: %d\n", ret);
        return -1;
    }
    *outlen = MAX_PAYLOAD - strm.avail_out;
    lzma_end(&strm);
    return 0;
}

int main(int argc, char **argv)
{
    uint8_t buf[MAX_PAYLOAD];
    for (int i = 0; i < sizeof(buf); i++) {
        buf[i] = i;
    }

    uint8_t compr[MAX_PAYLOAD] = {0};
    uint8_t uncompr[MAX_PAYLOAD] = {0};

    size_t comprLen = MAX_PAYLOAD;
    size_t uncomprLen = comprLen;

    int ret = compress(compr, &comprLen, buf, sizeof(buf));
    printf("ret=%d, compress: %ld -> %ld\n", ret, sizeof(buf), comprLen);

    ret = decompress(uncompr, &uncomprLen, compr, comprLen);
    printf("ret=%d, uncompress: %ld -> %ld\n", ret, comprLen, uncomprLen);

    ret = memcmp(buf, uncompr, uncomprLen);

    printf("ret=%d\n", ret);
    for (int i=0; i<comprLen; i++) {
        printf("%02x ", compr[i]);
    }
    printf("\n");
    printf("uncomprLen=%ld\n", uncomprLen);
    for (int i = 0; i < 160; i++) {
        if (i % 16 == 0) printf("\n");
        printf("%02x ", uncompr[i]);
    }
    printf("\nBUF==");
    for (int i = 0; i < 160; i++) {
        if (i % 16 == 0) printf("\n");
        printf("%02x ", buf[i]);
    }
    printf("\n");
    return 0;
}
