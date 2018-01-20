#include "dmacnt.h"
uint8_t Dummy = 0;
//DMA 脉冲计数初始化
void DMACNT_Init(DMACNT_InitTypeDef* DMACNT_InitStruct)
{
	DMA_InitTypeDef DMA_InitStruct1;
	GPIO_InitTypeDef GPIO_InitStruct1;
	
	//配置GPIO
	GPIO_InitStruct1.GPIO_Pin = DMACNT_InitStruct->GPIO_Pin;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	if(DMACNT_MODE_RISING == DMACNT_InitStruct->DMACNT_Mode)
	{
		GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DMA_RISING;
	}
	else
	{
		GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DMA_FALLING;
	}
	GPIO_InitStruct1.GPIOx = DMACNT_InitStruct->GPIOx;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(&GPIO_InitStruct1);
	//配置DMA
	DMA_InitStruct1.Channelx = DMACNT_InitStruct->DMA_Chl;
	DMA_InitStruct1.DMAAutoClose = DISABLE;
	DMA_InitStruct1.EnableState = ENABLE;
	DMA_InitStruct1.MinorLoopLength = 30000;
	switch((uint32_t)DMACNT_InitStruct->GPIOx)
	{
		case PTA_BASE: DMA_InitStruct1.PeripheralDMAReq  = PORTA_DMAREQ; break;
		case PTB_BASE: DMA_InitStruct1.PeripheralDMAReq  = PORTB_DMAREQ; break;
		case PTC_BASE: DMA_InitStruct1.PeripheralDMAReq  = PORTC_DMAREQ; break;
		case PTD_BASE: DMA_InitStruct1.PeripheralDMAReq  = PORTD_DMAREQ; break;
		case PTE_BASE: DMA_InitStruct1.PeripheralDMAReq  = PORTE_DMAREQ; break;
	  default : break;
	}
	DMA_InitStruct1.TransferBytes = 1; 
	//配置目的地址传输参数
	DMA_InitStruct1.DestBaseAddr = (uint32_t)&Dummy;
	DMA_InitStruct1.DestDataSize = DMA_DST_8BIT;
	DMA_InitStruct1.DestMajorInc = 0;
	DMA_InitStruct1.DestMinorInc = 0;
 
	//配置源地址传输参数
	DMA_InitStruct1.SourceBaseAddr = (uint32_t)&Dummy;
	DMA_InitStruct1.SourceDataSize = DMA_SRC_8BIT;
	DMA_InitStruct1.SourceMajorInc = 0;
	DMA_InitStruct1.SourceMinorInc = 0;
	DMA_Init(&DMA_InitStruct1);
}


//DMA脉冲计数 获得计数值
uint16_t DMACNT_GetValue(uint8_t DMA_Chl)
{
	uint16_t DMA_Value = 0;
	DMA_Value = DMA_GetCurrDataCounter(DMA_Chl);
	DMA_SetCurrDataCounter(DMA_Chl,30000);
	return (30000-DMA_Value);
}


