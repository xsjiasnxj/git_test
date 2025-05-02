#include "exti.h"
#include "delay.h" 
#include "main.h"
#include "gpio.h"
#include "global.h"
#include "OLED.h"
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com								  
////////////////////////////////////////////////////////////////////////////////// 
/*
			EC1_phase_a	--->>	B7
			EC1_button	--->>	B8
			EC2_phase_a	--->>	C5	 
			EC2_button	--->>	C4
*/

//外部中断初始化程序

void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	//KEY_Init(); //按键对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
    //外部中断线配置
	SYSCFG_EXTILineConfig(EC1_phase_a_PORT, EC1_phase_a_Pin);
	SYSCFG_EXTILineConfig(EC1_button_PORT, EC1_button_Pin);
	SYSCFG_EXTILineConfig(EC2_phase_a_Pin, EC2_phase_a_Pin);
	SYSCFG_EXTILineConfig(EC2_button_PORT, EC2_button_Pin);
	
	/* 配置EXTI_Line4 （EC2_button）*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;//LINE4
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE4
	EXTI_Init(&EXTI_InitStructure);//配置
	
	/* 配置EXTI_Line5,7,8 (EC2_phase_a,EC1_phase_a,EC1_button)*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line5 | EXTI_Line7 ;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
	EXTI_Init(&EXTI_InitStructure);//配置
	
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line8 ;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发
	EXTI_Init(&EXTI_InitStructure);//配置
	
    /* 配置NVIC中断通道*/
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置
		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断9_5
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置
	
}

void EXTI4_IRQHandler(void)
{
	//delay_ms(20);	//消抖
	
	if(EXTI_GetITStatus(EXTI_Line4)==SET)	 
	{
		EXTI_EC_handler(EC2_BUTTON);	
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4); 
}	

void EXTI9_5_IRQHandler(void)
{
   //delay_ms(20);	//消抖
	if(EXTI_GetITStatus(EXTI_Line5)==SET)	 
	{
		EXTI_EC_handler(EC2_PHASEA);
		EXTI_ClearITPendingBit(EXTI_Line5);
		return;
	}		 
	 
	if(EXTI_GetITStatus(EXTI_Line7)==SET)	 
	{
		EXTI_EC_handler(EC1_PHASEA);
		EXTI_ClearITPendingBit(EXTI_Line7);
		return;
	}		 
	
	//delay_ms(20);
	if(EXTI_GetITStatus(EXTI_Line8)==SET)	 
	{
		EXTI_EC_handler(EC1_BUTTON);
		EXTI_ClearITPendingBit(EXTI_Line8);
		return;
	}		 

}

//编码器中断处理函数（驱动层）
void EXTI_EC_handler(u8 EC_flag)
{
	
	//OLED_Clear();
	switch(EC_flag)
	{
		case EC1_PHASEA:
		{
			u8 PS=GPIO_ReadInputDataBit(EC1_phase_b_PORT,EC1_phase_b_Pin);
			if(PS==Bit_SET)
			{
               
			}
			else
			{
                
			}																																		
			break;
		}
        
		case EC1_BUTTON:
		{
           
			break;
		}	
        
		case EC2_PHASEA:
		{
			u8 PS=GPIO_ReadInputDataBit(EC2_phase_b_PORT,EC2_phase_b_Pin);
			if(PS==Bit_SET)
			{
                
			}
			else
			{
               
			}																																		
			break;
		}
        
		case EC2_BUTTON:
		{
           
			break;
		}	
	}
}


////编码器中断处理函数（用户更改）
//void EXTI_EC_handler(u8 EC_flag)
//{
//	
//	//OLED_Clear();
//	switch(EC_flag)
//	{
//		case EC1_PHASEA:
//		{
//			u8 PS=GPIO_ReadInputDataBit(EC1_phase_b_PORT,EC1_phase_b_Pin);
//			if(PS==Bit_SET)
//			{
//                
//			}
//			else
//			{

//			}																																		
//			break;
//		}
//        
//		case EC1_BUTTON:
//		{

//			break;
//		}	
//        
//		case EC2_PHASEA:
//		{
//			u8 PS=GPIO_ReadInputDataBit(EC2_phase_b_PORT,EC2_phase_b_Pin);
//			if(PS==Bit_SET)
//			{
//                
//			}
//			else
//			{

//			}																																		
//			break;
//		}
//        
//		case EC2_BUTTON:
//		{

//			break;
//		}	
//	}
//}








