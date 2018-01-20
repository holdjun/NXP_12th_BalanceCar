/**
  ******************************************************************************
  * @file    tsi.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.6.23
  * @brief   超核K60固件库 片内tsi 驱动文件
  ******************************************************************************
  */
#ifndef __TSI_H_
#define	__TSI_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "sys.h"

//TSI通道定义
#define TSI0_CH1_PA0              (0x00000005U)
#define TSI0_CH2_PA1              (0x00004009U)
#define TSI0_CH3_PA2              (0x0000800dU)
#define TSI0_CH4_PA3              (0x0000c011U)
#define TSI0_CH5_PA4              (0x00010015U)
#define TSI0_CH0_PB0              (0x00000801U)
#define TSI0_CH6_PB1              (0x00004819U)
#define TSI0_CH7_PB2              (0x0000881dU)
#define TSI0_CH8_PB3              (0x0000c821U)
#define TSI0_CH9_PB16             (0x00040825U)
#define TSI0_CH10_PB17            (0x00044829U)
#define TSI0_CH11_PB18            (0x0004882dU)
#define TSI0_CH12_PB19            (0x0004c831U)
#define TSI0_CH13_PC0             (0x00001035U)
#define TSI0_CH14_PC1             (0x00005039U)
#define TSI0_CH15_PC2             (0x0000903dU)

//TSI 通道定义
#define TSI0_CH0            (0)
#define TSI0_CH1            (1)
#define TSI0_CH2            (2)
#define TSI0_CH3            (3)
#define TSI0_CH4            (4)
#define TSI0_CH5            (5)
#define TSI0_CH6            (6)
#define TSI0_CH7            (7)
#define TSI0_CH8            (8)
#define TSI0_CH9            (9)
#define TSI0_CH10           (10)
#define TSI0_CH11           (11)
#define TSI0_CH12           (12)
#define TSI0_CH13           (13)
#define TSI0_CH14           (14)
#define TSI0_CH15           (15)



//TSI中断扫描模式定义
#define TSI_IT_MODE_END_OF_SCAN           (0)
#define TSI_IT_MODE_OUT_OF_RANGE          (1)
#define IS_TSI_IT_MODE(MODE)   ((MODE) == TSI_IT_MODE_END_OF_SCAN  || (MODE) == TSI_IT_MODE_OUT_OF_RANGE)
//TSI MAP结构定义
typedef struct
{
    uint32_t TSI_Index:2;
		uint32_t TSI_CH_Index:6;
	  uint32_t TSI_Alt_Index:3;
    uint32_t TSI_GPIO_Index:3;
    uint32_t TSI_Pin_Index:6;
}TSI_MapTypeDef;

//TSI初始化结构
typedef struct
{
	uint32_t TSIxMAP;        //初始化结构
	uint8_t  TSI_ITMode;    //扫描模式
}TSI_InitTypeDef;


//中断配置选项
#define TSI_IT_EOSF           (uint16_t)(0)
#define TSI_IT_OUTRGF         (uint16_t)(1)
#define TSI_IT_EXTERF         (uint16_t)(2)
#define TSI_IT_OVRF           (uint16_t)(3) 
#define IS_TSI_IT(IT)      ((IT) == TSI_IT_EOSF)    || \
                           ((IT) == TSI_IT_OUTRGF)  || \
                           ((IT) == TSI_IT_EXTERF)  || \
                           ((IT) == TSI_IT_OVRF))


/*********************消抖用宏定义********************************/
#define ELECTRODE_SHAKE  1000  //相对阀值容错系数   越大触摸越稳定灵敏度低 越小越不稳定 灵敏度高

/*********************外部电容计数器******************************/	   
//为了解决飞思卡尔极2!的寄存器设置
#define ELECTRODE0_COUNT  (uint16_t)((TSI0->CNTR1)&0x0000FFFF)
#define ELECTRODE1_COUNT  (uint16_t)((TSI0->CNTR1>>16)&0x0000FFFF)
#define ELECTRODE2_COUNT  (uint16_t)((TSI0->CNTR3)&0x0000FFFF)
#define ELECTRODE3_COUNT  (uint16_t)((TSI0->CNTR3>>16)&0x0000FFFF)
#define ELECTRODE4_COUNT  (uint16_t)((TSI0->CNTR5>>16)&0x0000FFFF)
#define ELECTRODE5_COUNT  (uint16_t)((TSI0->CNTR5>>16)&0x0000FFFF)
#define ELECTRODE6_COUNT  (uint16_t)((TSI0->CNTR7)&0x0000FFFF)
#define ELECTRODE7_COUNT  (uint16_t)((TSI0->CNTR7>>16)&0x0000FFFF)
#define ELECTRODE8_COUNT  (uint16_t)((TSI0->CNTR9)&0x0000FFFF)
#define ELECTRODE9_COUNT  (uint16_t)((TSI0->CNTR9>>16)&0x0000FFFF)
#define ELECTRODE10_COUNT  (uint16_t)((TSI0->CNTR11)&0x0000FFFF)
#define ELECTRODE11_COUNT  (uint16_t)((TSI0->CNTR11>>16)&0x0000FFFF)
#define ELECTRODE12_COUNT  (uint16_t)((TSI0->CNTR13)&0x0000FFFF)
#define ELECTRODE13_COUNT  (uint16_t)((TSI0->CNTR13>>16)&0x0000FFFF)
#define ELECTRODE14_COUNT  (uint16_t)((TSI0->CNTR15)&0x0000FFFF)
#define ELECTRODE15_COUNT  (uint16_t)((TSI0->CNTR15>>16)&0x0000FFFF)
//本构件实现的接口函数
void TSI_SelfCalibration(uint8_t TSI_Ch);
uint32_t TSI_GetCounter(uint8_t TSI_Ch);
void TSI_Init(TSI_InitTypeDef* TSI_InitStruct);
void TSI_ITConfig(TSI_Type *TSIx,uint16_t TSI_IT,FunctionalState NewState);
void TSI_ClearAllITPendingFlag(TSI_Type *TSIx);
uint8_t TSI_GetChannelOutOfRangleFlag(TSI_Type *TSIx,uint8_t TSI_CH);
void TSI_SelfCalibration(uint8_t TSI_Ch);
void TSI_ClearITPendingBit(TSI_Type* TSIx,uint16_t TSI_IT);
ITStatus TSI_GetITStatus(TSI_Type* TSIx, uint16_t TSI_IT);
void TSI_ITConfig(TSI_Type *TSIx,uint16_t TSI_IT,FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif
