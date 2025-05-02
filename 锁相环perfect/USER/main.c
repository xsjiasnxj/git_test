#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "OLED.h"
#include "exti.h"
#include "timer.h"
#include "gpio.h"
#include "buzzer.h"
#include "global.h"
#include "main.h"
#include "key.h"
#include "usart.h"
#include "math.h"
#include "AD7606.h"
#include "Vofa.h"
#include "spi.h"
#include "sogi.h"
#include "pll.h"
#include "arm_math.h"

/***********************************************************************
  * @ 函数名  ： bsp_Init
  * @ 功能说明： 所有外设初始化函数，方便管理
  * @ 参数    ：   
  * @ 返回值  ： 无
  *********************************************************************/
void bsp_Init()
{
    pid_init(&pid1, kp1, ki1, kd1);
	pid_init(&pid2, kp2, ki2, kd2);
    
    sogi_init(&sogi_v,Ts, h_pi);
 //   sogi_init(&sogi_i, Ts, h_pi);
    pll_init(&pll_v, Ts, 100, 100);
    

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组 4
    delay_init(168);
    AD7606_Init();
    SPI2_Init();
	GPIO_Config_Init();
    EXTIX_Init();	
	OLED_Init();
    uart_init(2000000);   


    TIM1_Config_Init();//专门用于PWM输出
	TIM2_Config_Init();//专门用于数据采样+计算+控制
	TIM3_Config_Init();//专门用于显示

	OLED_Clear();
}

int main(void)
{
    bsp_Init();
	while (1)
	{	  
       

	}
		
}







