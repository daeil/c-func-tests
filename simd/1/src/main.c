#include "./etc.h"

void main(int argc, char *argv[])
{
    st_XY XY = { 0 }, XYsimd = { 0 };
    float x = 0.f, y = 0.f, r_sq = 0.f, sum_xy = 0.f;
    int val_i = 0;
    int idx = 0;

    v4sf xmm_x = { 0.f }, xmm_y = { 0.f }, xmm_r_sqy = { 0.f }, xmm_x_elif0 = { 0.f }, xmm_y_elif0 = { 0.f };
    v4sf xmm_cond1_if = { 0.f }, xmm_cond1_elif0 = { 0.f };
    v4si emm_val_i = { 0 };

    memset(&XY, 0, sizeof(st_XY));
    memset(&XYsimd, 0, sizeof(st_XY));

    //legacy code...
    clock_t start1 = clock();
    for (int i = 0; i < LoopCnt; i++)
    {
        x = (float)rand() / (float)RAND_MAX;
        y = (float)rand() / (float)RAND_MAX;

        r_sq = (x * x + y * y);

        val_i = i % XY_MAX;

        if (r_sq < IF_THRS_RHO_SQ)
        {
            XY.X[val_i] += x;
            XY.Y[val_i] += y;
        }
        else if (r_sq < ELSEIF_THRS_RHO_SQ)
        {
            XY.X[val_i] += x/2.f;
            XY.Y[val_i] += y/2.f;
        }
        else
        {
            ;   //do nothing...
        }

        if (i != BREAK_CNT)
        {
            XY.X[val_i] += 0.0001f;
            XY.Y[val_i] += 0.0001f;
        }
        else
        {
            break;
        }
    }

    printf("legacy code...: %8.5f\n", (float)(clock() - start1) / CLOCKS_PER_SEC);

    //Simd used code...
    clock_t start2 = clock();
    for (int i = 0; i < LoopCnt; i += 4)
    {
        xmm_x = _mm_set_ps(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX));
        xmm_y = _mm_set_ps(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX));
        xmm_r_sqy = _mm_mul_ps(xmm_x, xmm_x);
        xmm_r_sqy = _mm_add_ps(xmm_r_sqy, _mm_mul_ps(xmm_y, xmm_y));

        emm_val_i = _mm_set_epi32(((i + 3) % XY_MAX), ((i + 2) % XY_MAX), ((i + 1) % XY_MAX), (i % XY_MAX));

        _PS_CONST(_PS_IF_THRS_RHO_SQ, IF_THRS_RHO_SQ);
        _PS_CONST(_PS_ELSEIF_THRS_RHO_SQ, ELSEIF_THRS_RHO_SQ);
        _PS_CONST(_PS_CONST_2f, 2.f);

        xmm_cond1_if = _mm_cmplt_ps(xmm_r_sqy, *(v4sf*)_PS_IF_THRS_RHO_SQ);
        xmm_cond1_elif0 = _mm_cmplt_ps(xmm_r_sqy, *(v4sf*)_PS_ELSEIF_THRS_RHO_SQ);
        xmm_cond1_elif0 = _mm_andnot_ps(xmm_cond1_if, xmm_cond1_elif0);

        xmm_x_elif0 = _mm_div_ps(xmm_x, *(v4sf*)_PS_CONST_2f);
        xmm_y_elif0 = _mm_div_ps(xmm_y, *(v4sf*)_PS_CONST_2f);

        xmm_x = _mm_and_ps(xmm_cond1_if, xmm_x);
        xmm_y = _mm_and_ps(xmm_cond1_if, xmm_y);
        xmm_x = _mm_add_ps(xmm_x, _mm_and_ps(xmm_x_elif0, xmm_cond1_elif0));
        xmm_y = _mm_add_ps(xmm_y, _mm_and_ps(xmm_y_elif0, xmm_cond1_elif0));

        //unpacking flow... (cannot be pararell execution in cpu...)
        XYsimd.X[*(int*)&emm_val_i] += *(float*)&xmm_x;
        XYsimd.X[*((int*)&emm_val_i + 1)] += *((float*)&xmm_x + 1);
        XYsimd.X[*((int*)&emm_val_i + 2)] += *((float*)&xmm_x + 2);
        XYsimd.X[*((int*)&emm_val_i + 3)] += *((float*)&xmm_x + 3);

        XYsimd.Y[*(int*)&emm_val_i] += *(float*)&xmm_y;
        XYsimd.Y[*((int*)&emm_val_i + 1)] += *((float*)&xmm_y + 1);
        XYsimd.Y[*((int*)&emm_val_i + 2)] += *((float*)&xmm_y + 2);
        XYsimd.Y[*((int*)&emm_val_i + 3)] += *((float*)&xmm_y + 3);

        //simd used code break...
        if ((i + 3) < BREAK_CNT)
        {
            XYsimd.X[*(int*)&emm_val_i] += 0.0001f;
            XYsimd.X[*((int*)&emm_val_i + 1)] += 0.0001f;
            XYsimd.X[*((int*)&emm_val_i + 2)] += 0.0001f;
            XYsimd.X[*((int*)&emm_val_i + 3)] += 0.0001f;

            XYsimd.Y[*(int*)&emm_val_i] += 0.0001f;
            XYsimd.Y[*((int*)&emm_val_i + 1)] += 0.0001f;
            XYsimd.Y[*((int*)&emm_val_i + 2)] += 0.0001f;
            XYsimd.Y[*((int*)&emm_val_i + 3)] += 0.0001f;
        }
        else
        {
            int j = 0;
            while ((i + j) < BREAK_CNT)
            {
                XYsimd.X[*((int*)&emm_val_i + j)] += 0.0001f;
                XYsimd.Y[*((int*)&emm_val_i + j)] += 0.0001f;

                j++;
            }

            break;
        }
    }

    printf("Simd used code...: %8.5f\n", (float)(clock() - start2) / CLOCKS_PER_SEC);

    //temp code...for just loop execute......
    for (int i = 0; i < XY_MAX; i++)
    {
        sum_xy = XY.X[i] + XY.Y[i];

        if (sum_xy > XY_SUM_CNT_THRS)
        {
            XY.XY_SUM_CNT++;
        }
        else
        {
            ;   //do nothing...
        }
    }
    
    printf("XY->XY_SUM_CNT: %d\n", XY.XY_SUM_CNT);

    //temp code...for just loop execute......
    for (int i = 0; i < XY_MAX; i++)
    {
        sum_xy = XYsimd.X[i] + XYsimd.Y[i];

        if (sum_xy > XY_SUM_CNT_THRS)
        {
            XYsimd.XY_SUM_CNT++;
        }
        else
        {
            ;   //do nothing...
        }
    }

    printf("XYsimd->XY_SUM_CNT: %d\n", XYsimd.XY_SUM_CNT);

    system("pause");

    return;
}