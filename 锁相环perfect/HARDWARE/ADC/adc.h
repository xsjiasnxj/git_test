#ifndef	__ADC_H__
#define	__ADC_H__

void ADC_Config_Init(void);
void get_adc(void);

// DMA1 数据流0 通道2
#define ADC_DMA_STREAM   DMA1_Stream0
#define ADC_DMA_CHANNEL  DMA_Channel_2
//ADC1 DR寄存器地址
#define ADC_DR_ADDR     ((uint32_t)0x4001204C)
//转换的通道个数
#define NUMOFCHANNEL       8

#endif