#ifndef __DMACNT_H__
#define __DMACNT_H__


#include "dma.h"
#include "gpio.h"
#endif /* __DMACNT_H__ */

#define DMACNT_MODE_RISING    (uint8_t)(0)    //上升沿触发
#define DMACNT_MODE_FALLING   (uint8_t)(1)    //下降沿触发

typedef struct
{
	uint8_t DMA_Chl;              //通道号
	GPIO_Type *GPIOx;             //GPIO端口号
	uint8_t GPIO_Pin;             // 引脚号
  uint8_t DMACNT_Mode;	        //工作模式
}DMACNT_InitTypeDef;

//本构件实现的接口函数列表
void DMACNT_Init(DMACNT_InitTypeDef* DMACNT_InitStruct);
uint16_t DMACNT_GetValue(uint8_t DMA_Chl);




