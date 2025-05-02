//
// Created by MHR on 2023-6-11.
//
#include "transform.h"
#include "math.h"
#include "arm_math.h"
//float arm_sin_f32(float theta);

//float arm_cos_f32(float theta);
////模拟stm32


void ab_to_dq(float a, float b, float theta, float *d, float *q)
{
    float sin_theta = arm_sin_f32(theta);
    float cos_theta = arm_cos_f32(theta);
    *d = a * cos_theta + b * sin_theta;
    *q = b * cos_theta - a * sin_theta;
}

void dq_to_ab(float d, float q, float theta, float *a, float *b)
{
    float sin_theta = arm_sin_f32(theta);
    float cos_theta = arm_cos_f32(theta);
    *a = d * cos_theta - q * sin_theta;
    *b = q * cos_theta + d * sin_theta;
}

void abc_to_ab(float a, float b, float c, float *alpha, float *beta)    //等幅值变换，k=2/3
{
    *alpha = (a - 0.5f * b - 0.5f * c) * clark_k;
    *beta = (sqrt3_2 * b - sqrt3_2 * c) * clark_k;
}

void ab_to_abc(float alpha, float beta, float *a, float *b, float *c)
{
    *a = alpha;
    *b = ((sqrt3 * beta) - alpha) / 2.0f;
    *c = -1.0f * (*a + *b);
}

//float arm_cos_f32(float theta)
//{
//    return cosf(theta);
//}

//float arm_sin_f32(float theta)
//{
//    return sinf(theta);
//}