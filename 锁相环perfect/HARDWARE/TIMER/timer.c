#include "stm32f4xx.h"
#include "timer.h"
#include "pwm.h"
#include "global.h"

/**
  * @brief  定时器1初始化
  * @param  无
  * @retval 无
  */
  
void TIM2_Config_Init()	
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //使能 TIM2 时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = TIM2_PERIOD;				//自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler =TIM2_PRSC; 			//预分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);	
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //清除中断标志位
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );
	
	NVIC_InitTypeDef NVIC_InitStructure;	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; 					//定时器 1 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; 		//响应优先级 1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	TIM_Cmd(TIM2, ENABLE); //使能 TIMx 外设

}
void TIM3_Config_Init()	
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //使能 TIM2 时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = TIM3_PERIOD;				//自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler =TIM3_PRSC; 			//预分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //清除中断标志位
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );
	
	NVIC_InitTypeDef NVIC_InitStructure;	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 					//定时器 1 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x04; //抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; 		//响应优先级 3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	TIM_Cmd(TIM3, ENABLE); //使能 TIMx 外设
}
//void TIM4_Config_Init()	
//{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); //使能 TIM4 时钟
//	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//	TIM_TimeBaseStructure.TIM_Period = TIM4_PERIOD;				//自动重装值
//	TIM_TimeBaseStructure.TIM_Prescaler =TIM4_PRSC; 			//预分频系数
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);	
//	
//	TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //清除中断标志位
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE );
//	
//	NVIC_InitTypeDef NVIC_InitStructure;	
//	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; 				
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; 		
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	
//	TIM_Cmd(TIM4, ENABLE); //使能 TIMx 外设
//}

void TIM1_Mode_Config()	
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); //使能 TIM1 时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = PWM_PERIOD;			//自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler =PWM_PRSC; 			//预分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
	
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);	


	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//初始化 TIM14 Channel1 PWM 模式
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;              //配置为PWM模式1
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //使能CHx的PWM输出
   TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//互补输出使能，使能CHxN的PWM输出                     
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   
   TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;   
   TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;  
   TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;  
	                                                             
	TIM_OCInitStructure.TIM_Pulse = 100;  																				 
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);                       //配置CH1
	
	TIM_OCInitStructure.TIM_Pulse = 100;                         
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);                       //配置CH2
	
	TIM_OCInitStructure.TIM_Pulse = 0;                         
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);                       //配置CH3
	

	//死区时间
	TIM_BDTRInitTypeDef TIM1_BDTRInitStructure;
   TIM1_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable; 
   TIM1_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
   TIM1_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;   
   TIM1_BDTRInitStructure.TIM_DeadTime = 360;              //设置死区时间
   TIM1_BDTRInitStructure.TIM_Break = TIM_Break_Disable;	    
   TIM1_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;         
   TIM1_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;  
   TIM_BDTRConfig(TIM1, &TIM1_BDTRInitStructure);
 
 

	TIM_ClearITPendingBit(TIM1,TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3); //清除中断标志位
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ITConfig(TIM1,TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3,ENABLE);  //使能中断
	
   TIM_CtrlPWMOutputs(TIM1, ENABLE);                         //PWM输出使能    
   TIM_Cmd(TIM1, ENABLE);                                    //使能TIM1
}

void TIM1_GPIO_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); //使能 PORTF 时钟
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_TIM1); //PWM0A
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); //PWM0B
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_TIM1);//PWM1A
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);//PWM1B
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_TIM1);//PWM2A
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);//PWM2B
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度 100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //GPIOF9
	GPIO_Init(GPIOE,&GPIO_InitStructure); //初始化 PF9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //GPIOF9
	GPIO_Init(GPIOE,&GPIO_InitStructure); //初始化 PF9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //GPIOF9
	GPIO_Init(GPIOE,&GPIO_InitStructure); //初始化 PF9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //GPIOF9
	GPIO_Init(GPIOE,&GPIO_InitStructure); //初始化 PF9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //GPIOF9
	GPIO_Init(GPIOE,&GPIO_InitStructure); //初始化 PF9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //GPIOF9
	GPIO_Init(GPIOE,&GPIO_InitStructure); //初始化 PF9	
}
void TIM1_Config_Init()
{
	
	TIM1_Mode_Config();
	TIM1_GPIO_Config();
	
}

//void TIM1_CC_IRQHandler(void) 
//{	
//	if (TIM_GetITStatus(TIM1, TIM_IT_CC1)!=RESET)
//	{
//		
//		TIM_ClearITPendingBit(TIM1 , TIM_IT_CC1);
//	 }
//}



//void TIM1_CC_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM1,TIM_IT_CC1)==SET) //溢出中断
//	{		
//		num++;
//	}
//	TIM_ClearITPendingBit(TIM1,TIM_IT_CC1); //清除中断标志位
//}

