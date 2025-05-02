#include "stm32f4xx.h"
#include "dma.h"
#include "global.h"

//DMAx 的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8 位数据宽度/存储器增量模式
//DMA_Streamx:DMA 数据流,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMA 通道选择, @ref DMA_channel DMA_Channel_0~DMA_Channel_7
//par:外设地址 mar:存储器地址 ndtr:数据传输量 
void MYDMA_Config()
{ 
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);/*DMA2的时钟使能*/
	while(DMA_GetCmdStatus(DMA2_Stream0)!=DISABLE);/*等待DMA可以配置*/	
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;/*DMA通道0*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_BASE+0x4C;/*外设地址*/
	DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)adc_buffer;/*存取器地址*/
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;/*方向从外设到内存*/
	DMA_InitStructure.DMA_BufferSize = 8;/*数据传输的数量为8*/
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;/*地址不增加*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;/*地址增加*/
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;/*数据长度半字*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;/*数据长度半字*/
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;/*高优先级*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;/*循环模式*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;/*禁止FIFO*/
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;/*FIFO的值*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;/*单次传输*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;/*单次传输*/
	DMA_Init(DMA2_Stream0,&DMA_InitStructure);/**/
	DMA_Cmd(DMA2_Stream0,ENABLE);//开启DMA传输
} 
//开启一次 DMA 传输
//DMA_Streamx:DMA 数据流,DMA1_Stream0~7/DMA2_Stream0~7 
//ndtr:数据传输量 
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)
{
	DMA_Cmd(DMA_Streamx, DISABLE); //关闭 DMA 传输
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){} //确保 DMA 可以被设置 
	DMA_SetCurrDataCounter(DMA_Streamx,ndtr); //数据传输量 
	DMA_Cmd(DMA_Streamx, ENABLE); //开启 DMA 传输
}