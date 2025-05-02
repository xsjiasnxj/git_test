//
// Created by MHR on 2023-7-8.
//

#ifndef DSOGI_PLL_SOGI_H
#define DSOGI_PLL_SOGI_H

typedef struct
{
    float vo0;
    float vo1;
    float vo2;//输出变量
    float qvo0;
    float qvo1;
    float qvo2;//输出正交变量
    float vi0;
    float vi1;
    float vi2;//输入变量
    float sogi_omega;
    float sogi_k;
    float sogi_Ts;
    float sogi_x;
    float sogi_y;
    float sogi_temp;
    float sogi_b0;
    float sogi_b2;
    float sogi_a1;
    float sogi_a2;
    float sogi_qb0;
    float sogi_qb1;
    float sogi_qb2;
} sogitype;

void sogi_para_update(sogitype *st, float omega);

void sogi_init(sogitype *st, float Ts1, float omega);

void sogi(sogitype *st, float vi, float *vo, float *qvo);

#endif //DSOGI_PLL_SOGI_H
