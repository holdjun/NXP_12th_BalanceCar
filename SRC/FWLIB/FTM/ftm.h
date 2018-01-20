/**
  ******************************************************************************
  * @file    ftm.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 FTM 定时器 驱动 头文件
  ******************************************************************************
  */
#ifndef __FTM_H_
#define	__FTM_H_

#ifdef __cplusplus
	extern "C" {
#endif

#include "sys.h"

//可用的PWM单端输出端口
//例: FTM0_CH0_PC1:  FTM0模块 0 通道 引脚为PTC1
#define FTM0_CH0_PC1    (0x00108100U)
#define FTM0_CH0_PA3		(0x000c0300U)   //与TJAG冲突 慎用
#define FTM0_CH1_PC2    (0x00108210U)
#define FTM0_CH1_PA4    (0x000c0410U)
#define FTM0_CH2_PC3    (0x00108320U)
#define FTM0_CH2_PA5    (0x000c0520U)  //与TJAG冲突 慎用
#define FTM0_CH3_PC4    (0x00108430U)
#define FTM0_CH4_PD4    (0x0010c440U)
#define FTM0_CH5_PD5    (0x0010c550U)
#define FTM0_CH5_PA0    (0x000c0050U)  //与TJAG冲突 慎用
#define FTM0_CH6_PD6    (0x0010c660U)
#define FTM0_CH6_PA1    (0x000c0160U)  //与TJAG冲突 慎用
#define FTM0_CH7_PD7    (0x0010c770U)
#define FTM0_CH7_PA2    (0x000c0270U)  //与TJAG冲突 慎用
#define FTM1_CH0_PA12   (0x000c0c01U)
#define FTM1_CH0_PB0    (0x000c4001U)
#define FTM1_CH1_PA13   (0x000c0d11U)
#define FTM1_CH1_PB1    (0x000c4111U)
#define FTM2_CH0_PB18   (0x000c5202U)
#define FTM2_CH1_PB19   (0x000c5312U)

#define FTM0_CH3_PA6    (0x000c0630U)
#define FTM0_CH4_PA7		(0x000c0740U)
#define FTM1_CH0_PA8		(0x000c0801U)
#define FTM1_CH1_PA9		(0x000c0911U)

//参数检查器
#define IS_FTM_PWM_MAP(MAP)  (((MAP) == FTM0_CH0_PC1)  || \
                              ((MAP) == FTM0_CH0_PA3)  || \
                              ((MAP) == FTM0_CH1_PC2)  || \
                              ((MAP) == FTM0_CH1_PA4)  || \
                              ((MAP) == FTM0_CH2_PC3)  || \
                              ((MAP) == FTM0_CH2_PA5)  || \
                              ((MAP) == FTM0_CH3_PC4)  || \
                              ((MAP) == FTM0_CH4_PD4)  || \
                              ((MAP) == FTM0_CH5_PD5)  || \
                              ((MAP) == FTM0_CH5_PA0)  || \
                              ((MAP) == FTM0_CH6_PD6)  || \
															((MAP) == FTM0_CH6_PA1)  || \
															((MAP) == FTM0_CH7_PD7)  || \
															((MAP) == FTM0_CH7_PA2)  || \
															((MAP) == FTM1_CH0_PA12) || \
															((MAP) == FTM1_CH0_PB0)  || \
															((MAP) == FTM1_CH1_PA13) || \
															((MAP) == FTM1_CH1_PB1)  || \
															((MAP) == FTM2_CH0_PB18) || \
															((MAP) == FTM0_CH3_PA6)	 ||	\
															((MAP) == FTM0_CH4_PA7)	 ||	\
															((MAP) == FTM1_CH0_PA8)	 ||	\
															((MAP) == FTM1_CH1_PA9)	 ||	\
															((MAP) == FTM2_CH1_PB19))								
													
//FTM_PWM映射
typedef struct
{
    uint32_t FTM_Index:4;
    uint32_t FTM_CH_Index:4;
    uint32_t FTM_Pin_Index:6;
    uint32_t FTM_GPIO_Index:4;
    uint32_t FTM_Alt_Index:4;
		uint32_t FTM_Sesevred:10;
}FTM_PWM_MapTypeDef;


//FTM  模式选择
typedef enum
{
	FTM_Mode_EdgeAligned,     //边沿对齐
	FTM_Mode_CenterAligned,   //中心对齐 频率是边沿对齐的一半
	FTM_Mode_Combine,         //组合模式
	FTM_Mode_Complementary,   //互补模式
}FTM_Mode_TypeDef;


//参数检查器
#define IS_FTM_PWM_MODE(MODE) (((MODE) == FTM_Mode_EdgeAligned)    || \
                               ((MODE) == FTM_Mode_CenterAligned)  || \
													  	 ((MODE) == FTM_Mode_Combine)        || \
                               ((MODE) == FTM_Mode_Complementary))
#define IS_FTM_PWM_DUTY(DUTY)   ((DUTY) <= 10000)
#define IS_FTM_ALL_PERIPH(PERIPH)  (((PERIPH) == FTM0) || \
                                    ((PERIPH) == FTM1) || \
                                    ((PERIPH) == FTM2))

//单端PWM占空比输出 初始化结构
typedef struct
{
  uint32_t Frequency;      //波特率
	uint32_t FTMxMAP;        //初始化结构
	uint32_t InitalDuty;     //初始占空比
	FTM_Mode_TypeDef  FTM_Mode;
}FTM_InitTypeDef;

//FTM中断源
#define FTM_IT_TOF           (uint16_t)(10)
#define FTM_IT_CHF0          (uint16_t)(0)
#define FTM_IT_CHF1          (uint16_t)(1)
#define FTM_IT_CHF2          (uint16_t)(2)
#define FTM_IT_CHF3          (uint16_t)(3)
#define FTM_IT_CHF4          (uint16_t)(4)
#define FTM_IT_CHF5          (uint16_t)(5)
#define FTM_IT_CHF6          (uint16_t)(6)
#define FTM_IT_CHF7          (uint16_t)(7)
#define IS_FTM_IT(IT)   (((IT) == FTM_IT_TOF)   || \
                         ((IT) == FTM_IT_CHF0)  || \
                         ((IT) == FTM_IT_CHF1)  || \
                         ((IT) == FTM_IT_CHF2)  || \
                         ((IT) == FTM_IT_CHF3)  || \
                         ((IT) == FTM_IT_CHF4)  || \
                         ((IT) == FTM_IT_CHF5)  || \
                         ((IT) == FTM_IT_CHF6)  || \
                         ((IT) == FTM_IT_CHF7)  || \
                         ((IT) == FTM_IT_CHF0))





//本构件实现的接口函数列表
void FTM_Init(FTM_InitTypeDef *FTM_InitStruct);
void FTM_PWM_ChangeDuty(uint32_t FTMxMAP,uint32_t PWMDuty);
void FTM_ITConfig(FTM_Type* FTMx, uint16_t FTM_IT, FunctionalState NewState);
ITStatus FTM_GetITStatus(FTM_Type* FTMx, uint16_t FTM_IT);
void FTM_ClearITPendingBit(FTM_Type *FTMx,uint16_t FTM_IT);


#ifdef __cplusplus
}
#endif

#endif


