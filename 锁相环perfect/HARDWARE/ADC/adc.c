#include "stm32f4xx.h"
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "global.h"

//初始化 ADC
//这里我们仅以规则通道为例
	

//ADC1

	//PC3 通道 13
	//PC2 通道 12
	//PC1 通道 11	
	//PC0 通道 10	
	//PA3 通道 3	
	//PA2 通道 2	
	//PA1 通道 1			
	//PA0 通道 0	
	
	
void ADC_Config_Init(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);//使能GPIOA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//使能ADC时钟
	MYDMA_Config();
	/*初始化ADC1通道3 的IO口*/
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;/*模拟输入*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;/*通道3*/
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;/*不带上下拉*/
	GPIO_Init(GPIOC,&GPIO_InitStructure);/*初始化*/
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;/*模拟输入*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;/*通道3*/
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;/*不带上下拉*/
	GPIO_Init(GPIOA,&GPIO_InitStructure);/*初始化*/

	//ADC_TempSensorVrefintCmd(ENABLE);/*使能内部温度传感器*/
	
	/*通用控制寄存器的配置*/
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;/*DMA失能*/
	ADC_CommonInitStructure.ADC_Mode          = ADC_Mode_Independent;/*独立模式*/
	ADC_CommonInitStructure.ADC_Prescaler     = ADC_Prescaler_Div4;/*APB2的4分频 即84/4=21M*/
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;/*两个采样阶段的延时5个时钟*/
	ADC_CommonInit(&ADC_CommonInitStructure);/*初始化*/
	/*初始化ADC1*/
	ADC_InitStructure.ADC_Resolution  = ADC_Resolution_12b;/*12位模式*/
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;/*扫描模式*/
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;/*连续转换*/
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;/*禁止触发检测 使用软件触发*/
	ADC_InitStructure.ADC_DataAlign    = ADC_DataAlign_Right;/*右对齐*/
	ADC_InitStructure.ADC_NbrOfConversion = 8;/*只使用1通道 规则通为1*/
	ADC_Init(ADC1,&ADC_InitStructure);/*初始化*/
	
	ADC_Cmd(ADC1,ENABLE);/*开启转换*/
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13,1,ADC_SampleTime_480Cycles);/*设置规则通道16 3个序列 采样时间 */
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,2,ADC_SampleTime_480Cycles);/*设置规则通道3 2个序列 采样时间 */
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,3,ADC_SampleTime_480Cycles);/*设置规则通道2 1个序列 采样时间 */
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,4,ADC_SampleTime_480Cycles);/*设置规则通道16 3个序列 采样时间 */
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,5,ADC_SampleTime_480Cycles);/*设置规则通道3 2个序列 采样时间 */
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,6,ADC_SampleTime_480Cycles);/*设置规则通道2 1个序列 采样时间 */
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,7,ADC_SampleTime_480Cycles);/*设置规则通道16 3个序列 采样时间 */
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,8,ADC_SampleTime_480Cycles);/*设置规则通道3 2个序列 采样时间 */
	
	ADC_SoftwareStartConv(ADC1);/*启动软件转换*/
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);//源数据变化时开启DMA传输
	ADC_DMACmd(ADC1,ENABLE);//使能ADC传输
} 


void get_adc(void)
{
	adc_real[0] = adc_buffer[0] * 3.3f / 4095.0f;
	adc_real[1] = adc_buffer[1] * 3.3f / 4095.0f;
	adc_real[2] = adc_buffer[2] * 3.3f / 4095.0f;
	adc_real[3] = adc_buffer[3] * 3.3f / 4095.0f;
	adc_real[4] = adc_buffer[4] * 3.3f / 4095.0f;
	adc_real[5] = adc_buffer[5] * 3.3f / 4095.0f;
	adc_real[6] = adc_buffer[6] * 3.3f / 4095.0f;
	adc_real[7] = adc_buffer[7] * 3.3f / 4095.0f;
}
////获得 ADC 值
////ch:通道值 0~16: ch: @ref ADC_channels
////返回值:转换结果
//u16 Get_ADC(u8 ch) 
//{
//	//设置指定 ADC 的规则组通道，一个序列，采样时间
//	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles ); 
//	ADC_SoftwareStartConv(ADC1); //使能指定的 ADC1 的软件转换启动功能
//	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
//	return ADC_GetConversionValue(ADC1); //返回最近一次 ADC1 规则组的转换结果
//}

////获取通道 ch 的转换值，取 times 次,然后平均
////ch:通道编号 times:获取次数
////返回值:通道 ch 的 times 次转换结果平均值
//u16 Get_ADC_Average(u8 ch,u8 times)
//{
//	u32 temp_val=0; u8 t;
//	for(t=0;t<times;t++)
//	{
//	temp_val+=Get_Adc(ch); delay_ms(5);
//	}
//	return temp_val/times;

//}