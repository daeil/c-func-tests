#include <stdio.h>

//#define COPY_POINT(src, dst) { for (int i = 0; i < 3; i++) ##dst[i] = ##src[i]; }
#define TEST TEST

#define GET_PARAM(lpTitle, lpPosTitle, value, index) \
        printf("%s, %s\n", lpTitle, "f_#index #TEST");

void f_1_TEST() {
    printf("%s\n", __func__);
}


int main(int argc, char** argv) {
    float f[3] = {0, 1, 2};
    float o[3];

    //COPY_POINT(f, o)

    printf("o[0]=%f\n", o[0]);
    printf("o[1]=%f\n", o[1]);
    printf("o[2]=%f\n", o[2]);

    GET_PARAM("IDEAL_PLANE_GROUND",PLANE_1_L, eol_params->EOL_IDEAL_PLANE_GROUND_1L, i);
    //for (int i=0; i<3; i++) {
    //    GET_PARAM("IDEAL_PLANE_GROUND",PLANE_1_L, eol_params->EOL_IDEAL_PLANE_GROUND_1L, i);
    //}


    return 0;
}
