#ifndef _AD7606_H
#define _AD7606_H

//SPI2_SCK -> PB13
//SPI2_MISO -> PB14
  
#define rst_PORT 	 	GPIOB
#define rst_Pin  		GPIO_Pin_0
#define convstB_PORT 	GPIOB
#define convstB_Pin     GPIO_Pin_3
#define convstA_PORT 	GPIOB
#define convstA_Pin     GPIO_Pin_5
#define cs_PORT 	  	GPIOC	
#define cs_Pin    		GPIO_Pin_8
	
                        

#define rst_Set 	 	GPIO_SetBits(rst_PORT,rst_Pin)
#define rst_Reset  		GPIO_ResetBits(rst_PORT,rst_Pin)
//#define convstB_Set 	GPIO_SetBits(convstB_PORT,convstB_Pin)
//#define convstB_Reset   GPIO_ResetBits(convstB_PORT,convstB_Pin)
#define convstA_Set 	GPIO_SetBits(convstA_PORT,convstA_Pin)
#define convstA_Reset   GPIO_ResetBits(convstA_PORT,convstA_Pin)
#define cs_Set 	  		GPIO_SetBits(cs_PORT,cs_Pin)
#define cs_Reset   		GPIO_ResetBits(cs_PORT,cs_Pin)

//通道数定义
#define NUM_CHS         8


void GPIO_AD7606_Configuration(void);
void AD7606_Init(void);
void AD7606_startconvst(void);
void AD7606_reset(void) ;
//extern uint16_t AD7606_read_data();
void AD7606_read_data(uint16_t *data) ;
void AD7606_read(void);
#endif
