#include <stdio.h>
#include <stdint.h>


#define NN_CLASS_NUM 4

typedef struct tCLASSIFIC_DATA
{
    uint32_t                    u32_ClassNum;

    double                   arf32_HistConf[NN_CLASS_NUM];
    double                   arf32_FrameConf[NN_CLASS_NUM];
    double                   arf32_FrameConfforUO[NN_CLASS_NUM];
    int32_t                     ars32_PersCnt;

    uint32_t                    aru32_ClassSelectNum[NN_CLASS_NUM]; // 20.04.01 JK (Name Change)
    uint32_t                    aru32_MaxClassSelectNum[NN_CLASS_NUM]; // 20.04.01 JK (Name Change)
    uint32_t                    u32_ClassChangeCond; // 20.04.01 JK (Name Change)

    uint32_t                    u32_PrevInnerClass; // 200319 SJ (Polyspace)
    uint32_t                    u32_CurInnerClass; //20.03.31 JK
    uint32_t                    u32_FrameClassIdx; // 20.02.05 JK
    uint32_t                    u32_HistClassIdx; // 20.02.04 JK
    uint32_t                    u32_LockedClassIndx;

    uint32_t                    u32_ClassifierSelectNum;

} CLASSIFIC_DATA_t;


typedef struct {
    float mat[3][3];
} rotMat3_t;


void funcVal(const CLASSIFIC_DATA_t t) {
    printf("%s, %p\n", __func__, &t);
}

void funcRef(const CLASSIFIC_DATA_t *t) {
    printf("%s, %p\n", __func__, t);
}

int main (int argc, char** argv) {
    CLASSIFIC_DATA_t data = {0};
    data.u32_ClassNum = 0x00550033;
    data.u32_CurInnerClass = 0x11223344;

    char* p = (char*)&data;

    for (int i=0; i < sizeof(CLASSIFIC_DATA_t); i++) {
        printf("%02x", *(p+i));
    }
    printf("\n");

    printf("%s   , %p\n", __func__, &data);
    funcVal(data);
    funcRef(&data);

    for (int j=0; j<10000; j++) {
        rotMat3_t rot = {0};
        for (int i=0; i < 9; i++) {
            if (rot.mat[i] != 0) {
                printf("rot[%d]=%f\n", i, *rot.mat[i]);
            }
        }
    }

    return 0;
}
