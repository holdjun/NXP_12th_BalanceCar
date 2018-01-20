/**
  ******************************************************************************
  * @file    pdb.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 可编程延时模块 头文件
  ******************************************************************************
  */
#ifndef __PDB_H__
#define __PDB_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "sys.h"

//PDB分频系数选择
#define PDB_PRESC_1       (0)
#define PDB_PRESC_2       (1)
#define PDB_PRESC_4       (2)
#define PDB_PRESC_8       (3)
#define PDB_PRESC_16      (4)
#define PDB_PRESC_32      (5)
#define PDB_PRESC_64      (6)
#define PDB_PRESC_128     (7)

#define PDB_MULT_1        (0)
#define PDB_MULT_10       (1)
#define PDB_MULT_20       (2)
#define PDB_MULT_40       (3)


//PDB触发源选择
#define TRIGGER_IN0      (0)
#define TRIGGER_IN1      (1)
#define TRIGGER_IN2      (2)
#define TRIGGER_IN3      (3)
#define TRIGGER_IN4      (4)
#define TRIGGER_IN5      (5)
#define TRIGGER_IN6      (6)
#define TRIGGER_IN7      (7)
#define TRIGGER_IN8      (8)
#define TRIGGER_IN9      (9)
#define TRIGGER_IN10     (10)
#define TRIGGER_IN11     (11)
#define TRIGGER_IN12     (12)
#define TRIGGER_IN13     (13)
#define TRIGGER_IN14     (14)
#define TRIGGER_IN15     (15)
#define TRIGGER_IN_SOFTWARE_TRIGER   TRIGGER_IN15


//PDB工作模式选择 
#define PDB_CONT_MODE_ONESHOT  (0)
#define PDB_CONT_MODE_CONTINUE (1)
#define IS_PDB_CONT_MODE(MODE) (((MODE) == PDB_CONT_MODE_ONESHOT) || (MODE) == PDB_CONT_MODE_CONTINUE)

//LoadMode选择
//LDMOD0 当LDOK=1后 MOD IDLY CHnDLYm INTx POyDLY寄存器立即加载
//LDMOD1 LOOK=1 和 PDB计数器到达MOD后 MOD IDLY CHnDLYm INTx POyDLY立即加载
//LDMOD2 当LDOK=1 和 一个输入时间设置为1后 立即加载
//LDMOD3 当LDOK=1 和一个输入时间或 PDB计数倒带MOD
#define LDMOD0       (0)
#define LDMOD1       (1)
#define LDMOD2       (2)
#define LDMOD3       (3)
#define IS_PDB_LDMOD(MODE) (((MODE) == LDMOD0) || \
                            ((MODE) == LDMOD1) || \
                            ((MODE) == LDMOD2) || \
												    ((MODE) == LDMOD3))
													 
													 
//PDB触发连接
#define PDB_ADC0_TRIGGER   (uint8_t)(0)
#define PDB_ADC1_TRIGGER   (uint8_t)(1)
#define PDB_DAC0_TRIGGER   (uint8_t)(2)
#define PDB_DAC1_TRIGGER   (uint8_t)(3)
#define IS_PDB_TRIGGER_CH(CHL)  ((CHL) == PDB_ADC0_TRIGGER || (CHL) == PDB_ADC1_TRIGGER)


//PDB预触发通道选择
#define PDB_ADC_PRE_TRIGGER_CH0        (uint8_t)(0)
#define PDB_ADC_PRE_TRIGGER_CH1        (uint8_t)(1)
#define IS_PDB_ADC_PRE_TRIGGER_CHL(CHL)  ((CHL) == PDB_ADC_PRE_TRIGGER_CH0 || (CHL) == PDB_ADC_PRE_TRIGGER_CH1)

//PDB初始化结构
typedef struct
{
	uint32_t PDB_TriggerSourceSelect;
	uint32_t PDB_ContinuousMode;
	uint8_t  PDB_LoadMode;
	uint32_t PDB_Period;
}PDB_InitTypeDef;

//PDB触发DAC初始化结构 
typedef struct
{
	uint8_t PDB_ADC_TriggerSelect;    //触发ADC0还是ADC1
	uint8_t PDB_ADC_PreTriggerChl;    // 0 - 1
	FunctionalState PDB_ADC_BBEnable; //是否使能BB
	FunctionalState PDB_ADC_Enable;   //是否开启
}PDB_ADC_PreTriggerInitTypeDef;


//中断源定义
#define PDB_IT_ERR                (uint16_t)(0)
#define PDB_IT_IF                 (uint16_t)(1)
#define IS_PDB_IT(IT)  (((IT) == PDB_IT_ERR) || ((IT) == PDB_IT_IF))

//DMA命令
#define PDB_DMAReq_IF             ((uint16_t)0)
#define IS_PDB_DMAREQ(REQ)   ((REQ) == PDB_DMAReq_IF)

//参数检查器														
#define IS_PDB_ALL_PERIPH(PERIPH) ((PERIPH) == PDB0)

//本构件实现的接口函数
void PDB_Init(PDB_InitTypeDef * PDB_InitStruct);
void PDB_ADC_TriggerInit(PDB_ADC_PreTriggerInitTypeDef * PDB_ADC_InitStruct);
void PDB_ITConfig(PDB_Type* PDBx, uint16_t PDB_IT, FunctionalState NewState);
ITStatus PDB_GetITStatus(PDB_Type* PDBx, uint16_t PDB_IT);
void PDB_DMACmd(PDB_Type* PDBx, uint16_t PDB_DMAReq, FunctionalState NewState);
void PDB_ClearITPendingBit(PDB_Type *PDBx,uint16_t PDB_IT);

#ifdef __cplusplus
}
#endif

#endif

