//
// Created by MHR on 2023-6-11.
//

#ifndef SVPWM_TRANSFORM_H
#define SVPWM_TRANSFORM_H
#define sqrt3_2  0.8660254f
#define sqrt3 1.7320508f
#define clark_k 0.6666667f
#define pi  3.1415926535f
#define h_pi  314.15926535f

void ab_to_dq(float a, float b, float theta, float *d, float *q);

void dq_to_ab(float d, float q, float theta, float *a, float *b);

void abc_to_ab(float a, float b, float c, float *alpha, float *beta);

void ab_to_abc(float alpha, float beta, float *a, float *b, float *c);

#endif //SVPWM_TRANSFORM_H
