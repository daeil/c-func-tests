#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>

static uint32_t CRC32_TABLE[256]= {
    0x00000000L, 0xce58c2b1L, 0xae7183fbL, 0x6029414aL, 0x6e23016fL, 0xa07bc3deL, 0xc0528294L, 0x0e0a4025L,
    0xdc4602deL, 0x121ec06fL, 0x72378125L, 0xbc6f4394L, 0xb26503b1L, 0x7c3dc100L, 0x1c14804aL, 0xd24c42fbL,
    0x8a4c0325L, 0x4414c194L, 0x243d80deL, 0xea65426fL, 0xe46f024aL, 0x2a37c0fbL, 0x4a1e81b1L, 0x84464300L,
    0x560a01fbL, 0x9852c34aL, 0xf87b8200L, 0x362340b1L, 0x38290094L, 0xf671c225L, 0x9658836fL, 0x580041deL,
    0x265800d3L, 0xe800c262L, 0x88298328L, 0x46714199L, 0x487b01bcL, 0x8623c30dL, 0xe60a8247L, 0x285240f6L,
    0xfa1e020dL, 0x3446c0bcL, 0x546f81f6L, 0x9a374347L, 0x943d0362L, 0x5a65c1d3L, 0x3a4c8099L, 0xf4144228L,
    0xac1403f6L, 0x624cc147L, 0x0265800dL, 0xcc3d42bcL, 0xc2370299L, 0x0c6fc028L, 0x6c468162L, 0xa21e43d3L,
    0x70520128L, 0xbe0ac399L, 0xde2382d3L, 0x107b4062L, 0x1e710047L, 0xd029c2f6L, 0xb00083bcL, 0x7e58410dL,
    0x4cb001a6L, 0x82e8c317L, 0xe2c1825dL, 0x2c9940ecL, 0x229300c9L, 0xeccbc278L, 0x8ce28332L, 0x42ba4183L,
    0x90f60378L, 0x5eaec1c9L, 0x3e878083L, 0xf0df4232L, 0xfed50217L, 0x308dc0a6L, 0x50a481ecL, 0x9efc435dL,
    0xc6fc0283L, 0x08a4c032L, 0x688d8178L, 0xa6d543c9L, 0xa8df03ecL, 0x6687c15dL, 0x06ae8017L, 0xc8f642a6L,
    0x1aba005dL, 0xd4e2c2ecL, 0xb4cb83a6L, 0x7a934117L, 0x74990132L, 0xbac1c383L, 0xdae882c9L, 0x14b04078L,
    0x6ae80175L, 0xa4b0c3c4L, 0xc499828eL, 0x0ac1403fL, 0x04cb001aL, 0xca93c2abL, 0xaaba83e1L, 0x64e24150L,
    0xb6ae03abL, 0x78f6c11aL, 0x18df8050L, 0xd68742e1L, 0xd88d02c4L, 0x16d5c075L, 0x76fc813fL, 0xb8a4438eL,
    0xe0a40250L, 0x2efcc0e1L, 0x4ed581abL, 0x808d431aL, 0x8e87033fL, 0x40dfc18eL, 0x20f680c4L, 0xeeae4275L,
    0x3ce2008eL, 0xf2bac23fL, 0x92938375L, 0x5ccb41c4L, 0x52c101e1L, 0x9c99c350L, 0xfcb0821aL, 0x32e840abL,
    0x9960034cL, 0x5738c1fdL, 0x371180b7L, 0xf9494206L, 0xf7430223L, 0x391bc092L, 0x593281d8L, 0x976a4369L,
    0x45260192L, 0x8b7ec323L, 0xeb578269L, 0x250f40d8L, 0x2b0500fdL, 0xe55dc24cL, 0x85748306L, 0x4b2c41b7L,
    0x132c0069L, 0xdd74c2d8L, 0xbd5d8392L, 0x73054123L, 0x7d0f0106L, 0xb357c3b7L, 0xd37e82fdL, 0x1d26404cL,
    0xcf6a02b7L, 0x0132c006L, 0x611b814cL, 0xaf4343fdL, 0xa14903d8L, 0x6f11c169L, 0x0f388023L, 0xc1604292L,
    0xbf38039fL, 0x7160c12eL, 0x11498064L, 0xdf1142d5L, 0xd11b02f0L, 0x1f43c041L, 0x7f6a810bL, 0xb13243baL,
    0x637e0141L, 0xad26c3f0L, 0xcd0f82baL, 0x0357400bL, 0x0d5d002eL, 0xc305c29fL, 0xa32c83d5L, 0x6d744164L,
    0x357400baL, 0xfb2cc20bL, 0x9b058341L, 0x555d41f0L, 0x5b5701d5L, 0x950fc364L, 0xf526822eL, 0x3b7e409fL,
    0xe9320264L, 0x276ac0d5L, 0x4743819fL, 0x891b432eL, 0x8711030bL, 0x4949c1baL, 0x296080f0L, 0xe7384241L,
    0xd5d002eaL, 0x1b88c05bL, 0x7ba18111L, 0xb5f943a0L, 0xbbf30385L, 0x75abc134L, 0x1582807eL, 0xdbda42cfL,
    0x09960034L, 0xc7cec285L, 0xa7e783cfL, 0x69bf417eL, 0x67b5015bL, 0xa9edc3eaL, 0xc9c482a0L, 0x079c4011L,
    0x5f9c01cfL, 0x91c4c37eL, 0xf1ed8234L, 0x3fb54085L, 0x31bf00a0L, 0xffe7c211L, 0x9fce835bL, 0x519641eaL,
    0x83da0311L, 0x4d82c1a0L, 0x2dab80eaL, 0xe3f3425bL, 0xedf9027eL, 0x23a1c0cfL, 0x43888185L, 0x8dd04334L,
    0xf3880239L, 0x3dd0c088L, 0x5df981c2L, 0x93a14373L, 0x9dab0356L, 0x53f3c1e7L, 0x33da80adL, 0xfd82421cL,
    0x2fce00e7L, 0xe196c256L, 0x81bf831cL, 0x4fe741adL, 0x41ed0188L, 0x8fb5c339L, 0xef9c8273L, 0x21c440c2L,
    0x79c4011cL, 0xb79cc3adL, 0xd7b582e7L, 0x19ed4056L, 0x17e70073L, 0xd9bfc2c2L, 0xb9968388L, 0x77ce4139L,
    0xa58203c2L, 0x6bdac173L, 0x0bf38039L, 0xc5ab4288L, 0xcba102adL, 0x05f9c01cL, 0x65d08156L, 0xab8843e7L,
};

/* CRC-32C (iSCSI) polynomial in reversed bit order. */
//#define POLY 0x82f63b78
#define POLY 0x9960034CL


/* Table for a quadword-at-a-time software crc. */
static pthread_once_t crc32c_once_sw = PTHREAD_ONCE_INIT;
static uint32_t crc32c_table[8][256];


#define CREATE_CRC32_TABLE 1
#if CREATE_CRC32_TABLE
static void genCrc32Table(void)
{
#define POLYNOMIAL 0x9960034CL
    uint32_t rem;
    for (int32_t i = 0; i < 256; i++)
    {
        rem = i;
        for (int32_t j = 0; j < 8; j++)
        {
            if (rem & 1)
            {
                rem >>= 1;
                rem ^= POLYNOMIAL;
            }
            else
            {
                rem >>= 1;
            }
        }
        CRC32_TABLE[i] = rem;
    }
#undef POLYNOMIAL
}
#endif

static void printCrc32Table(void)
{
    printf("static uint32_t CRC32_TABLE[256]= {\n    ");
    for (int32_t i = 0; i < 256; i++)
    {
        printf("0x%08x,", CRC32_TABLE[i]);
        if (i == 255)
        {
            printf("\n};\n");
        }
        else if (i % 8 == 7)
        {
            printf("\n    ");
        }
        else
        {
            printf(" ");
        }
    }
}

uint32_t common_genCRC32(uint8_t *buf, size_t len)
{
#if CREATE_CRC32_TABLE
    static int isTableCreated;
    if (!isTableCreated) {
        genCrc32Table();
        isTableCreated = 1;
    }
#endif
    uint32_t crc = 0xFFFFFFFF;
    for (int i=0; i<len; i++)
    {
        crc = (crc >> 8) ^ CRC32_TABLE[(crc & 0xFF) ^ *(buf + i)];
    }
    return ~crc;
}



/* Construct table for software CRC-32C calculation. */
static void crc32c_init_sw(void)
{
    uint32_t n, crc, k;

    for (n = 0; n < 256; n++) {
        crc = n;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc32c_table[0][n] = crc;
    }
    for (n = 0; n < 256; n++) {
        crc = crc32c_table[0][n];
        for (k = 1; k < 8; k++) {
            crc = crc32c_table[0][crc & 0xff] ^ (crc >> 8);
            crc32c_table[k][n] = crc;
        }
    }
}


static uint32_t crc32c_sw(uint32_t crci, const void *buf, size_t len)
{
    const unsigned char *next = buf;
    uint64_t crc;

    pthread_once(&crc32c_once_sw, crc32c_init_sw);
    crc = crci ^ 0xffffffff;
    while (len && ((uintptr_t)next & 7) != 0) {
        crc = crc32c_table[0][(crc ^ *next++) & 0xff] ^ (crc >> 8);
        len--;
    }
    while (len >= 8) {
        crc ^= *(uint64_t *)next;
        crc = crc32c_table[7][crc & 0xff] ^
              crc32c_table[6][(crc >> 8) & 0xff] ^
              crc32c_table[5][(crc >> 16) & 0xff] ^
              crc32c_table[4][(crc >> 24) & 0xff] ^
              crc32c_table[3][(crc >> 32) & 0xff] ^
              crc32c_table[2][(crc >> 40) & 0xff] ^
              crc32c_table[1][(crc >> 48) & 0xff] ^
              crc32c_table[0][crc >> 56];
        next += 8;
        len -= 8;
    }
    while (len) {
        crc = crc32c_table[0][(crc ^ *next++) & 0xff] ^ (crc >> 8);
        len--;
    }
    return (uint32_t)crc ^ 0xffffffff;
}


int main()
{
    genCrc32Table();
    printCrc32Table();
    unsigned char *s = "The quick brown fox jumps over the lazy dog";

    uint32_t crc = common_genCRC32(s, strlen(s));
    uint32_t new_crc = crc32c_sw(0, s, strlen(s));


    printf("CRC: 0x%x\n", crc);
    printf("NEW: 0x%x\n", new_crc);

    // unsigned char c= 0xcc;
	// printf("%" PRIX32 "\n", calcCrc32(&c, 1));

	printf("%" PRIX32 "\n", common_genCRC32(s, strlen(s)));
    return 0;
}
