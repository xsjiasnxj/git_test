#ifndef	__DMA_H__
#define	__DMA_H__

void MYDMA_Config(void);
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr);

#endif