#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    uint32_t LSP_SwVer : 32;
} PARAM_t;

void dump(PARAM_t *p) {

    //printf("%u %u\n", (char) p->LSP_SwVer, ((char *)&p->LSP_SwVer)[1]);
    //printf("%u: %u %u\n", p->LSP_SwVer, p->LSP_SwVer & 0xFF, p->LSP_SwVer >> 8 & 0xFF);
#define DUMPVI4(NAME) printf("%s : %u.%u.%u.%u", #NAME,  #NAME, p->NAME & 0xFF, p->NAME >> 8 & 0xFF, p->NAME >> 16 & 0xFF, p->NAME >> 24 & 0xFF)
    DUMPVI4(LSP_SwVer);

    //DUMPX(p->LSP_SwVer);
#undef DUMPVI4
}

int main(int argc, char** argv) {

    PARAM_t ver;
    ver.LSP_SwVer = 1 | 8 << 8 | 1 << 16 | 0 << 24;
    dump(&ver);

#define DUMPX(NAME) printf("%s : %hd.%hd.%hd.%hd\n", #NAME, ((char *)&NAME)[0], ((char *)&NAME)[1], ((char *)&NAME)[2],((char *)&NAME)[3])

#define SPEED_SCALE 0.01f
#define SCALE_MPH_TO_KPH 3.6f
#define SPEED(velX, velY) { sqrtf( (velX * SPEED_SCALE * SCALE_MPH_TO_KPH) *  (velX * SPEED_SCALE * SCALE_MPH_TO_KPH) + (velY * SPEED_SCALE * SCALE_MPH_TO_KPH) * (velY * SPEED_SCALE * SCALE_MPH_TO_KPH))}

#define SPEED2(velX, velY) { sqrtf(velX * velX + velY * velY) * SPEED_SCALE * SCALE_MPH_TO_KPH }

    //DUMPX(LSP_SwVer);
    int velX = 443;
    int velY = -66;
    //float speed = sqrtf( (velX * SPEED_SCALE * SCALE_MPH_TO_KPH) *  (velX * SPEED_SCALE * SCALE_MPH_TO_KPH) + (velY * SPEED_SCALE * SCALE_MPH_TO_KPH) * (velY * SPEED_SCALE * SCALE_MPH_TO_KPH));
    float speed = SPEED(velX, velY);
    printf("speed: %f\n", speed);
    float speed2 = SPEED2(velX, velY);
    printf("speed2: %f\n", speed2);

    printf("bool %d\n", (1 && !(1) && !(0) ));

    int v = 0;
    v |= 1 << 8 | 1 << 4;

    printf("v=%d, v=%d\n", v, v & ~(1 << 8));

    return 0;
}

