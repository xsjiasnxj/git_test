#include "stm32f4xx.h"
#include "global.h"
#include "key.h"


//标志位变量
uint16_t pll_is_locked=0;
char test_flag=0;
//vofa
Vofa_HandleTypedef vofa1;
float vofa_databuffer[8];
//按键
Key_HandleTypeDef key1;

//采样变量
uint16_t adc_buffer[8]={0};
float adc_real[8]={0};

uint16_t test_num;
uint16_t filter_cnt=0;
uint16_t timer_cnt=0;


//采样还原参数(k,b，补偿)
float  sample2real_k[8]={0.3096f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f};
float  sample2real_b[8]={0.005f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
float  Compensation[8]={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};

//pid
pidtype pid1,pid2,pid3,pid4;

//float input_voltage_test;
//float test_voltage_target=1.854;
//float test_voltage_target_d=1;

float MI=0.5f;      //调制比

//输入信号

float port_voltage = 0;
float port_current = 0;
float port_voltage_alpha = 0;
float port_voltage_beta = 0;
float port_current_alpha = 0;
float port_current_beta = 0;
float port_voltage_d = 0;
float port_voltage_q = 0;
float port_current_d = 0;
float port_current_q = 0;
float port_theta = 0;
float port_omega = 0;
float port_voltage_peak = 0;
float port_current_peak = 0;

float input_voltage = 0;
float input_current = 0;
float input_voltage_peak = 0;
float input_current_peak = 0;
float input_apparent_power = 0;
float input_active_power = 0;
float input_power_factor = 0;
float input_power_factor_angle = 0;


//float input_voltage3 = 0;
//float input_current3 = 0;

//锁相变量
sogitype sogi_v;
sogitype sogi_i;
plltype  pll_v;

float input_voltage_alpha=0;
float input_voltage_beta=0;
float input_voltage_d=0;
float input_voltage_q=0;

float input_current_alpha=0;
float input_current_beta=0;
float input_current_d=0;
float input_current_q=0;

float omega=h_pi;
float theta=0;

//期望输出
float target_current_d = 1;
float target_current_q = 0;
float target_current_d3 = 0;
float target_current_q3 = 0;


float target_voltage_d = 0;
float target_voltage_q = 0;
float target_voltage_d3 = 0;
float target_voltage_q3 = 0;

float target_voltage_alpha = 0;
float target_voltage_beta = 0;
float target_voltage_alpha3 = 0;
float target_voltage_beta3 = 0;

float target_voltage_peak = 1;
float set_power_factor_angle = 0;


//显示及功能变量

unsigned char mode=0;
unsigned char index=0;
unsigned char page=0;


