#ifndef	__MAIN_H__
#define	__MAIN_H__

//外部中断定义
#define	EC1_phase_a_PORT				EXTI_PortSourceGPIOB				//EXTI6
#define	EC1_phase_a_Pin				    EXTI_PinSource7
#define	EC1_phase_b_PORT				GPIOB
#define	EC1_phase_b_Pin				    GPIO_Pin_12
#define	EC1_button_PORT				    EXTI_PortSourceGPIOB				//EXTI7
#define	EC1_button_Pin					EXTI_PinSource8

#define	EC2_phase_a_PORT				EXTI_PortSourceGPIOC				//EXTI5
#define	EC2_phase_a_Pin				    EXTI_PinSource5
#define	EC2_phase_b_PORT				GPIOE
#define	EC2_phase_b_Pin				    GPIO_Pin_15
#define	EC2_button_PORT				    EXTI_PortSourceGPIOC				//EXTI4
#define	EC2_button_Pin					EXTI_PinSource4

//板载ADC通道端口定义
#define ADC1_CH13_adc0_Pin 			    GPIO_Pin_3
#define ADC1_CH13_adc0_GPIO_Port 	    GPIOC
#define ADC1_CH12_adc1_Pin 			    GPIO_Pin_2
#define ADC1_CH12_adc1_GPIO_Port 	    GPIOC
#define ADC1_CH11_adc2_Pin 			    GPIO_Pin_1
#define ADC1_CH11_adc2_GPIO_Port 	    GPIOC
#define ADC1_CH10_adc3_Pin 			    GPIO_Pin_0
#define ADC1_CH10_adc3_GPIO_Port 	    GPIOC
#define ADC1_CH2_adc4_Pin 				GPIO_Pin_2
#define ADC1_CH2_adc4_GPIO_Port 		GPIOA
#define ADC1_CH3_adc5_Pin 				GPIO_Pin_3
#define ADC1_CH3_adc5_GPIO_Port 		GPIOA
#define ADC1_CH0_adc6_Pin 				GPIO_Pin_0
#define ADC1_CH0_adc6_GPIO_Port 		GPIOA
#define ADC1_CH1_adc7_Pin 				GPIO_Pin_1
#define ADC1_CH1_adc7_GPIO_Port 		GPIOA


//#define	EXTI0_PORT						GPIOB
//#define	EXTI0_Pin						GPIO_Pin_6
//#define	EXTI1_PORT						GPIOA
//#define	EXTI1_Pin						GPIO_Pin_15
//#define	EXTI2_PORT						GPIOA
//#define	EXTI2_Pin						GPIO_Pin_11
//#define	EXTI3_PORT						GPIOA
//#define	EXTI3_Pin						GPIO_Pin_12

//矩阵键盘
#define C3_Pin 							GPIO_Pin_2
#define C3_GPIO_Port 					GPIOE
#define C2_Pin 							GPIO_Pin_3
#define C2_GPIO_Port 					GPIOE
#define C1_Pin 							GPIO_Pin_4
#define C1_GPIO_Port 					GPIOE
#define C0_Pin 							GPIO_Pin_5
#define C0_GPIO_Port 					GPIOE
#define R3_Pin 							GPIO_Pin_6
#define R3_GPIO_Port 					GPIOE
#define R2_Pin 							GPIO_Pin_13
#define R2_GPIO_Port 					GPIOC
#define R1_Pin 							GPIO_Pin_0
#define R1_GPIO_Port 					GPIOE
#define R0_Pin 							GPIO_Pin_1
#define R0_GPIO_Port 					GPIOE


#endif