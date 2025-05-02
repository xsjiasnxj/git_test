//
// Created by MHR on 2023-6-11.
//

#ifndef SVPWM_PLL_H
#define SVPWM_PLL_H

typedef struct
{
    float pll_Ts;
    float pll_kp;
    float pll_ki;
    float pll_theta_b0;
    float pll_theta_b1;
    float pll_theta_b2;
    float pll_theta_a0;
    float pll_theta_a1;
    float pll_theta_a2;
    float pll_omega_a1;
    float pll_omega_a0;
    float pll_omega_b0;
    float pll_omega_b1;
    float pll_out_theta0;
    float pll_out_theta1;
    float pll_out_theta2;
    float pll_out_omega0;
    float pll_out_omega1;
    float pll_in0;
    float pll_in1;
    float pll_in2;
} plltype;

void pll_init(plltype *pt, float Ts, float pll_kp, float pll_ki);

void pll(plltype *pt, float vq, float *omega, float *theta);

#endif //SVPWM_PLL_H
