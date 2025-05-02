//
// Created by MHR on 2023-7-8.
//

#include "sogi.h"
#include "vofa.h"
Vofa_HandleTypedef vofa2;
float vofa_databuffer1[16];
double z1,z2,z3,z4;
void sogi_para_update(sogitype *st, float omega)
{
    st->sogi_omega = omega;
    st->sogi_x = 2.0f * st->sogi_k * st->sogi_omega * st->sogi_Ts;
    st->sogi_y = st->sogi_omega * st->sogi_Ts * st->sogi_omega * st->sogi_Ts;
    st->sogi_temp = 1.0f / (st->sogi_x + st->sogi_y + 4.0f);
    st->sogi_b0 = st->sogi_x * st->sogi_temp;
    st->sogi_b2 = (-1.0f) * st->sogi_b0;
    st->sogi_a1 = (2.0f) * (4.0f - st->sogi_y) * st->sogi_temp;
    st->sogi_a2 = (st->sogi_x - st->sogi_y - 4.0f) * st->sogi_temp;
    st->sogi_qb0 = (st->sogi_k * st->sogi_y) * st->sogi_temp;
    st->sogi_qb1 = st->sogi_qb0 * (2.0f);
    st->sogi_qb2 = st->sogi_qb0;
}

void sogi_init(sogitype *st, float Ts1, float omega)
{
    st->sogi_Ts = Ts1;
    st->sogi_k = 0.5f;
    st->sogi_omega = omega;
    st->sogi_x = 2.0f * st->sogi_k * st->sogi_omega * st->sogi_Ts;
    st->sogi_y = st->sogi_omega * st->sogi_Ts * st->sogi_omega * st->sogi_Ts;
    st->sogi_temp = 1.0f / (st->sogi_x + st->sogi_y + 4.0f);
    st->sogi_b0 = st->sogi_x * st->sogi_temp;
    st->sogi_b2 = (-1.0f) * st->sogi_b0;
    st->sogi_a1 = (2.0f) * (4.0f - st->sogi_y) * st->sogi_temp;
    st->sogi_a2 = (st->sogi_x - st->sogi_y - 4) * st->sogi_temp;
    st->sogi_qb0 = (st->sogi_k * st->sogi_y) * st->sogi_temp;
    st->sogi_qb1 = st->sogi_qb0 * (2.0f);
    st->sogi_qb2 = st->sogi_qb0;
}

void sogi(sogitype *st, float vi, float *vo, float *qvo)
{
    __disable_irq();
	//更新序列值
    st->vi2 = st->vi1;
    st->vi1 = st->vi0;
    st->vi0 = vi;
    st->vo2 = st->vo1;
    st->vo1 = st->vo0;
    //对应离散序列
	
	z1= st->sogi_b0 * st->vi0;
	z2=st->sogi_b2 * st->vi2;
	z3=(st->sogi_a1 * st->vo1);
	z4=(st->sogi_a2 * st->vo2);
//    st->vo0 = st->sogi_b0 * st->vi0 + st->sogi_b2 * st->vi2 + (st->sogi_a1 * st->vo1) + (st->sogi_a2 * st->vo2);
	st->vo0 =z1+z2+z3+z4;
    st->qvo2 = st->qvo1;
    st->qvo1 = st->qvo0;
    //对应离散序列
	double t1,t2,t3,t4,t5;
 st->qvo0 =
            (st->sogi_qb0 * st->vi0) + (st->sogi_qb1 * st->vi1) + (st->sogi_qb2 * st->vi2) + (st->sogi_a1 * st->qvo1) +
            (st->sogi_a2 * st->qvo2);
    //输出
    *vo = st->vo0;
    *qvo = st->qvo0;

//	     { vofa_databuffer1[0]=st->vi2; 
//        vofa_databuffer1[1]=st->vi1; 
//				vofa_databuffer1[3]=st->vi0; 
//        vofa_databuffer1[4]=st->vo2; 
//				vofa_databuffer1[5]=st->vo1; 
//        vofa_databuffer1[6]=st->vo0;
//				vofa_databuffer1[7]=st->qvo2;
//        vofa_databuffer1[8]=st->qvo1;
//				vofa_databuffer1[9]=st->qvo0;
////        vofa_databuffer[2]st->qvo1=omega;
////        vofa_databuffer[3]//对应离=theta;
//        Vofa_JustFloat(&vofa2,vofa_databuffer1,10);}
			 __enable_irq();
}

