#include <stdio.h>

typedef signed char     int8_t;
typedef signed short    int16_t;
typedef signed int      int32_t;
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
typedef float           float32_t;
typedef double          float64_t;
typedef long double     float128_t;

typedef struct LSPR_DATA_INFO
{
    uint8_t u8_LDRFail;
    uint16_t u16_DelayTime;
    uint16_t u16_TimeStamp;
    uint8_t u8_DataIndex;
    uint8_t u8_NumObject;
    //LSPR_OBJ_INFO_t arst_ObjInfo[SEND_NUM_OBJECT];
} LSPR_DATA_INFO_t;


static FILE *file;
#define HEX_DUMP(data, size)                        \
    {                                               \
        if (file == NULL)                           \
            file = fopen("/tmp/hex_dump.txt", "w"); \
        fprintf(file, "%s\n", #data);               \
        unsigned char *c = (unsigned char *)data;   \
        for (unsigned int i = 0; i < size; i++)     \
        {                                           \
            fprintf(file, "%02x", *(c + i));        \
            if (i % 16 == 15 || i == size)          \
                fprintf(file, "\n");                \
            else                                    \
                fprintf(file, " ");                 \
        }                                           \
    }

void dumpLspDataInfo(LSPR_DATA_INFO_t* dataInfo)
{
    if (file == NULL) file = fopen("/tmp/lspr_data_info", "w");
    HEX_DUMP(dataInfo, sizeof(LSPR_DATA_INFO_t));
}

int main(int argc, char** argv) {

    LSPR_DATA_INFO_t dataInfo;
    dataInfo.u8_LDRFail = 1;
    dataInfo.u16_DelayTime = 0;
    dataInfo.u16_TimeStamp = 0x1313;
    dataInfo.u8_DataIndex = 0x55;
    dataInfo.u8_NumObject = 1;
    dumpLspDataInfo(&dataInfo);
    return 0;
}
