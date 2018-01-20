/**
  ******************************************************************************
  * @file    lptm.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 LPTM 低功耗定时器 驱动 驱动头文件
  ******************************************************************************
  */
#ifndef __LPTM_H__
#define __LPTM_H__

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "sys.h"

//初始化模式
typedef enum
{
	LPTM_Mode_PC_RISING,   //脉冲计数模式 上升沿计数
	LPTM_Mode_PC_FALLING,  //脉冲计数模式 下降沿计数
	LPTM_Mode_TC,          //TimerCounter模式
}LPTM_Mode_TpyeDef;
//参数检查器
#define IS_LPTM_PC_MODE(MODE) (((MODE) == LPTM_Mode_PC_RISING)   || \
															 ((MODE) == LPTM_Mode_PC_FALLING)  || \
											         ((MODE) == LPTM_Mode_TC))
	 
#define IS_LPTM_ALL_PERIPH(PERIPH) ((PERIPH) == LPTMR0)


typedef struct
{
	uint32_t LPTMxMap;                 //通道定义
	LPTM_Mode_TpyeDef LPTM_Mode;       //工作模式
	uint32_t LPTM_InitCompareValue;    //比较寄存器初始值
}LPTM_InitTypeDef;
	 

//中断源定义
#define LPTM_IT_TCF     (uint16_t)(0)
#define IS_LPTM_IT(IT)  ((IT) == LPTM_IT_TCF)

//LPLTM 脉冲计数模式通道定义
#define LPTM_CH1_PA19  (0x12345670U)
#define LPTM_CH2_PC5   (0x12345671U)
//参数检查器
#define IS_LPTM_MAP(CHL) (((CHL) == LPTM_CH1_PA19) || \
												  ((CHL) == LPTM_CH2_PC5))

#define IS_LPTM_DELAY_TIME(TIME) ((TIME) <= 65535)

//本构件所实现的接口
void LPTM_Init(LPTM_InitTypeDef* LPTM_InitStruct);
void LPTM_SetCompareValue(LPTMR_Type* LPTMx, uint32_t Value);
uint32_t LPTM_GetCompareValue(LPTMR_Type* LPTMx);
uint32_t LPTM_GetTimerCounterValue(LPTMR_Type* LPTMx);
void LPTM_ITConfig(LPTMR_Type* LPTMx, uint16_t LPTM_IT, FunctionalState NewState);
ITStatus LPTM_GetITStatus(LPTMR_Type* LPTMx, uint16_t LPTM_IT);
void LPTM_ClearITPendingBit(LPTMR_Type *LPTMx, uint16_t LPTM_IT);
void LPTM_DelayMs(LPTMR_Type* LPTMx, uint32_t ms);
void LPTM_ResetTimeCounter(LPTMR_Type* LPTMx);

#ifdef __cplusplus
}
#endif

#endif


