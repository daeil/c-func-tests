#ifndef ETC_H_
#define ETC_H_

/**Include**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <xmmintrin.h>
#include <time.h>
//#include <stdint.h>


//typedef char					char_t;
//typedef signed char				int8_t;
//typedef signed short			int16_t;
//typedef signed int				int32_t;
//typedef unsigned char			uint8_t;
//typedef unsigned short			uint16_t;
//typedef unsigned int			uint32_t;
//typedef float					float32_t;
//typedef double					float64_t;
//typedef long double				float128_t;

/**Define***********************************************************************/ 
#define LoopCnt                 100000000
#define CONSTCnt                10
#define XY_MAX                  1000000
#define IF_THRS_RHO_SQ          0.5f
#define ELSEIF_THRS_RHO_SQ      0.8f
#define BREAK_CNT               89999999
#define XY_SUM_CNT_THRS         40.f
#define USE_SSE2

#define _PS_CONST(Name, Val)    const float Name[4] = { Val, Val, Val, Val }
#define _EPI_CONST(Name, Val)   const int Name[4] = { Val, Val, Val, Val }

typedef struct st_XY
{
    float X[XY_MAX];
    float Y[XY_MAX];
    int XY_SUM_CNT;
} st_XY;


/* __m128 is ugly to write */
typedef __m128 v4sf;  // vector of 4 float (sse1)

#ifdef USE_SSE2
# include <emmintrin.h>
typedef __m128i v4si; // vector of 4 int (sse2)
#else
typedef __m64 v2si;   // vector of 2 int (mmx)
#endif


/**Global Variable Declaration**************************************************/


/**Global Extern Function Declaration*******************************************/


#endif