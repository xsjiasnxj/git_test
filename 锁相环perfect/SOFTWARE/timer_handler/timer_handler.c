#include "stm32f4xx.h"
#include "timer_handler.h"
#include "global.h"
#include "AD7606.h"
#include "main.h"
#include "spwm.h"
#include "OLED.h"
#include "gpio.h"
#include "sys.h"
#include "transform.h"
#include "Vofa.h"
#include "MENU.h"

//计数变量
int cnt=0;
int cnt_s=0;
int init_cnt=0;
//采样+控制

void TIM2_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{		

       AD7606_read();
       input_voltage = adc_real[0];
      // input_current = adc_real[1];
      sogi(&sogi_v, input_voltage, &input_voltage_alpha, &input_voltage_beta);
      ab_to_dq(input_voltage_alpha, input_voltage_beta, theta, &input_voltage_d, &input_voltage_q);
      pll(&pll_v, input_voltage_q, &omega, &theta);//电压锁相环
      if(omega > 312.0f && omega < 316.0f)
      {
          sogi_para_update(&sogi_v, omega);

      }
      else
      {
          sogi_para_update(&sogi_v, h_pi);
          
      }
       //ab_to_dq(input_current_alpha, input_current_beta, theta, &input_current_d, &input_current_q);
        
        //判断是否锁上环
        if(fabsf(omega - h_pi) <= 1.0f)
        {
         //   Counter_sine=(int)(400*theta/2/M_PI);
         //   Counter_sine_I=(Counter_sine+200)%400;
            pll_is_locked = 1;
            LED0=1;
        }
        else
        {
            pll_is_locked = 0;
            LED0=0;
        }
//        arm_sqrt_f32(input_voltage_d*input_voltage_d + input_voltage_q*input_voltage_q, &input_voltage_peak);
//        arm_sqrt_f32(input_current_d*input_current_d + input_current_q*input_current_q, &input_current_peak);
//       
//        //并联端输入电压电流峰值计算
//        arm_sqrt_f32(port_voltage_d*port_voltage_d + port_voltage_q*port_voltage_q, &port_voltage_peak);
//        arm_sqrt_f32(port_current_alpha*port_current_alpha + port_current_beta*port_current_beta, &port_current_peak);
//        //功率计算
//        input_power_factor_angle = -1.0f * atanf(input_current_q/input_current_d);	//电压超前电流角度，弧度制。
//        input_power_factor = arm_cos_f32(input_power_factor_angle);
//        input_apparent_power = input_voltage_peak * input_current_peak * 0.5f;
//        input_active_power = input_apparent_power * input_power_factor;
        
        //串口传输数据
        vofa_databuffer[0]=talab[Counter_sine]*MI;
        vofa_databuffer[1]=talab[Counter_sine_I]*MI;
        Vofa_JustFloat(&vofa1,vofa_databuffer,2);
/**********************作调试用************************************/
        cnt++;
        if(cnt>=1/Ts)
        {
            cnt_s++;
            cnt=0;
            
        }
/**********************************************************/
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //清除中断标志位
}

//按键检测+显示
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{	
       
      //  key_command_callback(&key1);
        OLED_Clear();
        OLED_ShowNum(0,0,cnt_s,4,8);
        OLED_ShowFloatNum(0,16,omega/(2*M_PI),3,2,8);
        OLED_ShowFloatNum(0,48,theta,3,2,8);
        OLED_ShowNum(0,32,Counter_sine,4,8);
        OLED_Update();
        //if(key1.key_num=='S')
    // MENU_RunMainMenu();
       // MENU_RunMainMenu();
//			OLED_Clear();
//      OLED_ShowChar(0,0,A,OLED_8X16);
//			OLED_Update();
	
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //清除中断标志位
}
//SPWM输出
void TIM1_CC_IRQHandler(void) 
{	
//    Counter_sine=(int)(400*theta/2/M_PI);
//    Counter_sine_I=(Counter_sine+200)%400;
	if(Counter_sine>=400)
	{

		Counter_sine = Counter_sine-400;
	}
	if(Counter_sine_I>=400)
	{
       
		Counter_sine_I = Counter_sine_I-400;
	}
	if(MI>MI_MAX)
    {
        MI=MI_MAX;
    }
	//CCR1	
	if (TIM_GetITStatus(TIM1, TIM_IT_CC1)!=RESET)
	{
        Counter_sine=(int)(400*theta/2/M_PI);
		TIM_SetCompare1(TIM1,(uint32_t)(talab[Counter_sine]*MI));	//A相	
		TIM_ClearITPendingBit(TIM1 , TIM_IT_CC1);
	 }
	//CCR2
    if (TIM_GetITStatus(TIM1, TIM_IT_CC2) !=RESET)
	{
        Counter_sine_I=(Counter_sine+200)%400;
		TIM_SetCompare2(TIM1,((uint32_t)talab[Counter_sine_I])*MI);	//B相
		TIM_ClearITPendingBit(TIM1 , TIM_IT_CC2);
	}

}


