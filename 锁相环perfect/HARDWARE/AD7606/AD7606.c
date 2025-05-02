#include "stm32f4xx.h"
#include "delay.h"
#include "AD7606.h"
#include "spi.h"
#include "global.h"
//-----------------------------------------------------------------
// 初始化程序区
//-----------------------------------------------------------------
//-----------------------------------------------------------------
// void GPIO_AD7606_Configuration(void)
//-----------------------------------------------------------------
//
// 函数功能: AD7606引脚配置函数
// 入口参数: 无
// 返回参数: 无
// 全局变量: 无
// 注意事项: 用GPIO驱动方式和FSMC驱动方式下的引脚配置不一样
//			
//-----------------------------------------------------------------
void GPIO_AD7606_Configuration(void)
{ 

	// 使能IO口时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOA时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOA时钟
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// AD7606 
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// 控制线配置 
    
    GPIO_InitTypeDef GPIO_InitStructure;
	//             CS_N      
    GPIO_InitStructure.GPIO_Pin = cs_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(cs_PORT, &GPIO_InitStructure);//初始化GPIO
  
	//        rst convstB convstA 

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉

    GPIO_InitStructure.GPIO_Pin = rst_Pin;
    GPIO_Init(rst_PORT, &GPIO_InitStructure);//初始化GPIO
    GPIO_InitStructure.GPIO_Pin = convstA_Pin;
    GPIO_Init(convstA_PORT, &GPIO_InitStructure);//初始化GPIO
//    GPIO_InitStructure.GPIO_Pin = convstB_Pin;
//    GPIO_Init(convstB_PORT, &GPIO_InitStructure);//初始化GPIO
}  

//-----------------------------------------------------------------
// void AD7606_Init(void)
//-----------------------------------------------------------------
//
// 函数功能: AD7606初始化函数
// 入口参数: 无
// 返回参数: 无
// 全局变量: 无
// 调用模块:    
// 注意事项: 无
//-----------------------------------------------------------------
void AD7606_Init(void)
{
    GPIO_AD7606_Configuration();
	convstA_Set;
	//convstB_Set;
	delay_ms(1);
//	STby_Set;
	cs_Set;	
//  OS10_Reset;
//	OS11_Reset;
//	OS12_Reset;
	AD7606_reset();  
	delay_ms(1);
	AD7606_startconvst();
}

/*   * 名称：AD7606_startconvst()  * 功能：启动转换  */  
void AD7606_startconvst(void)
{  
	convstA_Reset;	
	//convstB_Reset;	
	delay_us(1);
	convstA_Set;
	//convstB_Set;
}
  
/*   * 名称：AD7606_reset()  * 功能：复位模块  */
void AD7606_reset(void) 
{ 
	rst_Reset;
	rst_Set; 
	delay_us(1);
	rst_Reset; 
}  

/* 
* 名称：AD7606_read_data() 
* 功能：读取数据 
* 返回值：返回一个结构体指针，该指针为指向结构体数组的首地址  
*/ 
//uint16_t AD7606_read_data() 
//{
//    uint16_t data;
//    
//	cs_Reset;    
//	 
//	data=SPI2_ReadWriteByte(0xff);
//	
//	cs_Set;
//	AD7606_startconvst();
//	return data;
//}

void AD7606_read_data(uint16_t *data) 
{
    int i;
	cs_Reset;    
	for(i=0;i<NUM_CHS;i++) 
    {
       data[i]=SPI2_ReadWriteByte(0xff);
    }
	cs_Set;
	AD7606_startconvst();
}
//转换为实际值
void AD7606_read()
{
    AD7606_read_data(adc_buffer);
    for(int i=0;i<NUM_CHS;i++)
    {
        if(adc_buffer[i]<32768)
        {
            adc_real[i]=((adc_buffer[i])*10.0f  ) / 32768; 
        }
        else{
            adc_buffer[i] = (~adc_buffer[i])+1;
            adc_real[i]=((adc_buffer[i])*10.0f * (-1.0f) ) / 32768;
        }
        adc_real[i]=(adc_real[i]-sample2real_b[i])/sample2real_k[i]+Compensation[i];
    }
}