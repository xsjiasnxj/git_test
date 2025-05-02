#ifndef	__GLOBAL_H__
#define	__GLOBAL_H__

#include "pid.h"
#include "pll.h"
#include "sogi.h"
#include "Vofa.h"
#include "key.h"

#define h_pi 					314.15926535f
#define M_PI 					3.1415926535f
#define sqrt2 					1.41421356f

#define Ts 			            0.0005f         //采样时间
#define disp_time   			0.01f

#define MI_MAX                  0.98f           //调制比最大值
//#define pid_time   			    0.001f


//频率设置
#define CKTIM	        ((u32)168000000uL)  //主频
#define TIM_CKTIM	    ((u32) 84000000uL)  //定时器频率
#define PWM_PRSC        ((u8)0)            //TIM3分频系数
#define PWM_FREQ        ((u16) 20000)      //PWM频率(Hz)
#define PWM_PERIOD      ((u16) (TIM_CKTIM / (u32)( 2*PWM_FREQ *(PWM_PRSC+1))))  //因为是中心对齐计数模式，所以要乘2
//采样+控制
#define TIM2_PRSC		((u8)4)
#define TIM2_PERIOD     ((u16) (TIM_CKTIM / (u32)(1.0f/Ts*(TIM2_PRSC+1))))
//显示
#define TIM3_PRSC		((u8)400)
#define TIM3_PERIOD     ((u16) (TIM_CKTIM / (u32)(1.0f/disp_time*(TIM3_PRSC+1))))

////控制
//#define TIM4_PRSC		((u8)4)
//#define TIM4_PERIOD  ((u16) (CKTIM / (u32)( 1.0f/pid_time*(TIM4_PRSC+1))))

//pid参数
#define kp_pll 0.0005f
#define ki_pll 0.0001f

#define kp1	0.00003f
#define ki1 0.00008f
#define kd1	0.00f

#define kp2	0.00003f
#define ki2	0.00008f
#define kd2	0.00f

#define kp3	0
#define ki3	0
#define kd3	0

#define kp4	0.01f
#define ki4	0.0001f
#define kd4	0

//标志位变量
extern uint16_t pll_is_locked;
extern char test_flag;
//vofa
extern Vofa_HandleTypedef vofa1;
extern float vofa_databuffer[8];
//按键
extern Key_HandleTypeDef key1;
//采样变量
extern uint16_t adc_buffer[8];
extern float adc_real[8];

extern uint16_t test_num;
extern uint16_t filter_cnt;
extern uint16_t timer_cnt;


//采样还原参数(k,b，补偿)
extern float  sample2real_k[8];
extern float  sample2real_b[8];
extern float  Compensation[8];

//pid
extern pidtype pid1,pid2,pid3,pid4;



extern float MI;

//输入信号
extern float port_voltage ;
extern float port_current ;
extern float port_voltage_alpha ;
extern float port_voltage_beta ;
extern float port_current_alpha ;
extern float port_current_beta;
extern float port_voltage_d;
extern float port_voltage_q ;
extern float port_current_d;
extern float port_current_q ;
extern float port_theta;
extern float port_omega;
extern float port_voltage_peak;
extern float port_current_peak; 

extern float input_voltage ;
extern float input_current ;
extern float input_voltage_peak ;
extern float input_current_peak ;
extern float input_apparent_power ;
extern float input_active_power ;
extern float input_power_factor ;
extern float input_power_factor_angle;

//SOGI锁相变量
extern sogitype sogi_v;
extern sogitype sogi_i;
extern plltype  pll_v;

extern float input_voltage_alpha;
extern float input_voltage_beta;
extern float input_voltage_d;
extern float input_voltage_q;

extern float input_current_alpha;
extern float input_current_beta;
extern float input_current_d;
extern float input_current_q;


extern float omega;
extern float theta;

//期望输出
extern float target_current_d ;
extern float target_current_q ;
extern float target_current_d3 ;
extern float target_current_q3 ;
 
extern float target_voltage_d ;
extern float target_voltage_q ;
extern float target_voltage_d3 ;
extern float target_voltage_q3 ;

extern float target_voltage_alpha ;
extern float target_voltage_beta ;
extern float target_voltage_alpha3;
extern float target_voltage_beta3;

extern float target_voltage_peak;
extern float set_power_factor_angle;

//显示及功能变量
extern unsigned char mode;
extern unsigned char index;
extern unsigned char page;

#endif