/**
  ******************************************************************************
  * @file    pdb.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 可编程延时模块 驱动文件
  ******************************************************************************
  */
#include "pdb.h"
/***********************************************************************************************
 功能：PDB 初始化
 形参：PDB_InitStruct: PDB初始化结构
 返回：0
 详解：0
************************************************************************************************/
void PDB_Init(PDB_InitTypeDef * PDB_InitStruct)
{
	uint8_t i;
	uint32_t p;
	//参数检查 
	assert_param(IS_PDB_CONT_MODE(PDB_InitStruct->PDB_ContinuousMode));
	assert_param(IS_PDB_LDMOD(PDB_InitStruct->PDB_LoadMode));  
	
  //使能PDB时钟
  SIM->SCGC6 |= SIM_SCGC6_PDB_MASK ;
	//清0状态寄存器
	PDB0->SC = 0x00;
	//设置触发源
	PDB0->SC |= PDB_SC_TRGSEL(PDB_InitStruct->PDB_TriggerSourceSelect);
	//连续或者单次工作
	(PDB_InitStruct->PDB_ContinuousMode == PDB_CONT_MODE_ONESHOT)?(PDB0->SC &= ~PDB_SC_CONT_MASK):(PDB0->SC |= PDB_SC_CONT_MASK);
	//计算配置分频数
	p = ((CPUInfo.BusClock)*PDB_InitStruct->PDB_Period)/65535;
	for(i=0;i<8;i++)
	{
		if(p/(1<<i) < 40) break;
	}
	if(i > 7) i = 7;
	//设置分频率
  PDB0->SC |= PDB_SC_MULT(PDB_MULT_40);
	PDB0->SC |= PDB_SC_PRESCALER(i);
	//设置MOD和 IDLY 
	PDB0->MOD =  ((PDB_InitStruct->PDB_Period)*(CPUInfo.BusClock/1000))/(40*(1<<i));
	PDB0->IDLY = ((PDB_InitStruct->PDB_Period)*(CPUInfo.BusClock/1000))/(40*(1<<i));
	//使能PDB
	PDB0->SC |= PDB_SC_PDBEN_MASK; 
	//PDB开始工作
	PDB0->SC |= PDB_SC_LDOK_MASK;
	//使能软件触发
	PDB0->SC |= PDB_SC_SWTRIG_MASK;
	
}

/***********************************************************************************************
 功能：PDB DAC触发初始化配置
 形参：PDB_ADC_InitStruct: PDB_ADC 初始化结构
 返回：0
 详解：专为PDB模块触发DAC模块设计的初始化函数  不许在PDB_Init后调用
************************************************************************************************/
void PDB_ADC_TriggerInit(PDB_ADC_PreTriggerInitTypeDef * PDB_ADC_InitStruct)
{
	uint16_t pt_value = 0;
	//参数检查
	assert_param(IS_PDB_TRIGGER_CH(PDB_ADC_InitStruct->PDB_ADC_TriggerSelect));
	assert_param(IS_PDB_ADC_PRE_TRIGGER_CHL(PDB_ADC_InitStruct->PDB_ADC_PreTriggerChl));
	assert_param(IS_FUNCTIONAL_STATE(PDB_ADC_InitStruct->PDB_ADC_Enable));
	assert_param(IS_FUNCTIONAL_STATE(PDB_ADC_InitStruct->PDB_ADC_BBEnable));
	
	pt_value = (1<<PDB_ADC_InitStruct->PDB_ADC_PreTriggerChl);
	//开启或者关闭模块
	if(ENABLE == PDB_ADC_InitStruct->PDB_ADC_Enable)
	{
		PDB0->CH[PDB_ADC_InitStruct->PDB_ADC_TriggerSelect].C1 |= PDB_C1_TOS(pt_value)|PDB_C1_EN(pt_value);
	}
	else
	{
		PDB0->CH[PDB_ADC_InitStruct->PDB_ADC_TriggerSelect].C1 &= ~(PDB_C1_TOS(pt_value)|PDB_C1_EN(pt_value));
	}
	//是否使能BB
	if(ENABLE == PDB_ADC_InitStruct->PDB_ADC_BBEnable)
	{
		PDB0->CH[PDB_ADC_InitStruct->PDB_ADC_TriggerSelect].C1 |= PDB_C1_BB(pt_value);
	}
	else
	{
		PDB0->CH[PDB_ADC_InitStruct->PDB_ADC_TriggerSelect].C1 &= ~PDB_C1_BB(pt_value);
	}
	//DLY
	PDB0->CH[PDB_ADC_InitStruct->PDB_ADC_TriggerSelect].DLY[PDB_ADC_InitStruct->PDB_ADC_PreTriggerChl] = 0;
}

/***********************************************************************************************
 功能：PDB 中端配置
 形参：PDBx : PDB模块号
       @arg PDB0 ： PDB模块0
       PDB_IT : PDB模块中断源
       @arg PDB_IT_ERR : PDB顺序错误中断
       @arg PDB_IT_IF  : PDB计数到达中断
       NewState : 使能或者禁止
       @arg ENABLE : 使能
       @arg DISABLE: 禁止
 返回：0
 详解：0
************************************************************************************************/
void PDB_ITConfig(PDB_Type* PDBx, uint16_t PDB_IT, FunctionalState NewState)
{
	//参数检查器
	assert_param(IS_PDB_ALL_PERIPH(PDBx));
	assert_param(IS_PDB_IT(PDB_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	switch(PDB_IT)
	{
		case PDB_IT_ERR:
			(ENABLE == NewState)?(PDBx->SC |= PDB_SC_PDBEIE_MASK):(PDBx->SC &= ~PDB_SC_PDBEIE_MASK);
			break;
		case PDB_IT_IF:
			(ENABLE == NewState)?(PDBx->SC |= PDB_SC_PDBIE_MASK):(PDBx->SC &= ~PDB_SC_PDBIE_MASK);
			break;
		default:break;
	}
}

/***********************************************************************************************
 功能：PDB 获得中断标志
 形参：PDBx : PDB模块号
       @arg PDB0 ： PDB模块0
       PDB_IT : PDB模块中断源
       @arg PDB_IT_ERR : PDB顺序错误中断
       @arg PDB_IT_IF  : PDB计数到达中断
 返回：0
 详解：0
************************************************************************************************/
ITStatus PDB_GetITStatus(PDB_Type* PDBx, uint16_t PDB_IT)
{
	ITStatus retval;
	//参数检查器
	assert_param(IS_PDB_ALL_PERIPH(PDBx));
	assert_param(IS_PDB_IT(PDB_IT));
	
	switch(PDB_IT)
	{
		case PDB_IT_ERR:
			
			break;
		case PDB_IT_IF:
			(PDBx->SC & PDB_SC_PDBIF_MASK)?(retval = SET):(retval = RESET);
			break;
		default:break;
	}
	return retval;
}

/***********************************************************************************************
 功能：PDB DMA配置
 形参：PDBx : PDB模块号
       @arg PDB0 ： PDB模块0
       PDB_DMAReq : PDB模块DMA触发源
       @arg PDB_DMAReq_IF : PDB模块计数到达
       NewState : 使能或者禁止
       @arg ENABLE : 使能
       @arg DISABLE: 禁止
 返回：0
 详解：0
************************************************************************************************/
void PDB_DMACmd(PDB_Type* PDBx, uint16_t PDB_DMAReq, FunctionalState NewState)
{
	//参数检查器
	assert_param(IS_PDB_ALL_PERIPH(PDBx));
	assert_param(IS_PDB_DMAREQ(PDB_DMAReq));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	switch(PDB_DMAReq)
	{
		case PDB_DMAReq_IF:
			(ENABLE == NewState)?(PDBx->SC |= PDB_SC_DMAEN_MASK):(PDBx->SC &= ~PDB_SC_DMAEN_MASK);
			break;
		default:break;
	}
}
/***********************************************************************************************
 功能：PDB 清楚中断标志 
 形参：PDBx : PDB模块号
       @arg PDB0 ： PDB模块0
       PDB_IT : PDB模块中断源
       @arg PDB_IT_ERR : PDB顺序错误中断
       @arg PDB_IT_IF  : PDB计数到达中断
 返回：0
 详解：0
************************************************************************************************/
void PDB_ClearITPendingBit(PDB_Type *PDBx,uint16_t PDB_IT)
{
	//参数检查
	assert_param(IS_PDB_ALL_PERIPH(PDBx));
	assert_param(IS_PDB_IT(PDB_IT));
	
	switch(PDB_IT)
	{
		case PDB_IT_ERR:
			
			break;
		case PDB_IT_IF:
			PDBx->SC &= ~PDB_SC_PDBIF_MASK;
			break;
		default:break;
	}
}


