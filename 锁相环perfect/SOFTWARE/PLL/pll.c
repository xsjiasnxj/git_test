//
// Created by MHR on 2023-6-11.
//

#include "pll.h"
#include "transform.h"


void pll_init(plltype *pt, float Ts, float pll_kp, float pll_ki)
{
    pt->pll_Ts = Ts;
    pt->pll_kp = pll_kp;
    pt->pll_ki = pll_ki;
    pt->pll_theta_b0 = 4.0f;
    pt->pll_theta_b1 = -8.0f;
    pt->pll_theta_b2 = 4.0f;
    pt->pll_theta_a0 =
            pt->pll_ki * pt->pll_Ts * pt->pll_Ts - 2.0f * pt->pll_kp * pt->pll_Ts;
    pt->pll_theta_a1 = 2.0f * pt->pll_ki * pt->pll_Ts * pt->pll_Ts;
    pt->pll_theta_a2 =
            2.0f * pt->pll_kp * pt->pll_Ts + pt->pll_Ts * pt->pll_Ts * pt->pll_ki;
    pt->pll_omega_a1 = 2.0f * pt->pll_kp + pt->pll_Ts * pt->pll_ki;
    pt->pll_omega_a0 = pt->pll_Ts * pt->pll_ki - 2.0f * pt->pll_kp;
    pt->pll_omega_b0 = -2.0f;
    pt->pll_omega_b1 = 2.0f;
    pt->pll_out_theta0 = 0;
    pt->pll_out_theta1 = 0;
    pt->pll_out_theta2 = 0;
    pt->pll_out_omega0 = h_pi;
    pt->pll_out_omega1 = h_pi;
    pt->pll_in0 = 0;
    pt->pll_in1 = 0;
    pt->pll_in2 = 0;
		
}

void pll(plltype *pt, float vq, float *omega, float *theta)
{

    pt->pll_in2 = pt->pll_in1;
    pt->pll_in1 = pt->pll_in0;
    pt->pll_in0 = vq;    //pwm整流中q代表无功分量
    pt->pll_out_omega1 = pt->pll_out_omega0;
    pt->pll_out_omega0 =
            (pt->pll_omega_a1 * pt->pll_in0 + pt->pll_omega_a0 * pt->pll_in1 -
             pt->pll_omega_b0 * pt->pll_out_omega1) / pt->pll_omega_b1;
    pt->pll_out_theta2 = pt->pll_out_theta1;
    pt->pll_out_theta1 = pt->pll_out_theta0;
    pt->pll_out_theta0 =
            (pt->pll_theta_a2 * pt->pll_in0 + pt->pll_theta_a1 * pt->pll_in1 +
             pt->pll_theta_a0 * pt->pll_in2 - pt->pll_theta_b1 * pt->pll_out_theta1 -
             pt->pll_theta_b0 * pt->pll_out_theta2) / pt->pll_theta_b2;
    
     if (pt->pll_out_theta0 > 2 * pi)
    {
        pt->pll_out_theta0 = pt->pll_out_theta0 - 2 * pi;
    }
    else if (pt->pll_out_theta0 <= 0)
    {
        pt->pll_out_theta0 = pt->pll_out_theta0 + 2 * pi;
    }

    *theta = pt->pll_out_theta0;
    *omega = pt->pll_out_omega0/2.0f;
}