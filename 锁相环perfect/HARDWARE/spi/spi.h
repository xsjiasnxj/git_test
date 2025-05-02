#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

//SPI 驱动代码	   
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com									  
//SPI2_SCK -> PB13
//SPI2_MOSI -> PB15
//SPI2_MISO -> PB14
////////////////////////////////////////////////////////////////////////////////// 	
 	    													  
void SPI2_Init(void);			 //初始化SPI2口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPI2速度   
u16 SPI2_ReadWriteByte(u16 TxData);//SPI2总线读写一个字节
		 
#endif
