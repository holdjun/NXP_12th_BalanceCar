/**
  ******************************************************************************
  * @file    pit.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 内部定时器驱动 头文件
  ******************************************************************************
  */
#ifndef __PIT_H__
#define __PIT_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "sys.h"

#define PIT0   (uint8_t)(0)
#define PIT1   (uint8_t)(1)
#define PIT2   (uint8_t)(2)
#define PIT3   (uint8_t)(3)
//参数检查器
#define IS_PIT_CH(CH)     (((CH) == PIT0) || \
													((CH) == PIT1)  || \
													((CH) == PIT2)  || \
													((CH) == PIT3))

//PIT 中断定义
#define PIT_IT_TIF     (uint16_t)(0)
#define IS_PIT_IT(IT)  ((IT) == PIT_IT_TIF)

	 
//PIT 初始化结构
typedef struct
{
	uint8_t PITx;             //PIT通道
	uint32_t PIT_Interval;    //PIT定时时间 单位MS
}PIT_InitTypeDef;

//本构件所实现的接口函数
void PIT_Init(PIT_InitTypeDef* PIT_InitStruct);
uint32_t PIT_GetLoadValue(uint8_t PITx);
uint32_t PIT_GetCurrentValue(uint8_t PITx);
void PIT_SetLoadValue(uint8_t PITx, uint32_t Value);
void PIT_Start(uint8_t PITx);
void PIT_Stop(uint8_t PITx);
void PIT_ITConfig(uint8_t PITx, uint16_t PIT_IT, FunctionalState NewState);
ITStatus PIT_GetITStatus(uint8_t PITx, uint16_t PIT_IT);
void PIT_ClearITPendingBit(uint8_t PITx,uint16_t PIT_IT);

#ifdef __cplusplus
}
#endif

#endif
