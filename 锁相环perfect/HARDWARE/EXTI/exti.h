#ifndef __EXTI_H
#define __EXIT_H	 

#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com								  
////////////////////////////////////////////////////////////////////////////////// 	 


#define EC1_BUTTON	(u8)0
#define EC1_PHASEA	(u8)1
#define EC2_BUTTON	(u8)2
#define EC2_PHASEA	(u8)3

#define EC_COROTATION   1
#define EC_REVERSAL     -1

void EXTIX_Init(void);	//外部中断初始化	
void EXTI_EC_handler(u8 EC_flag);


#endif

























