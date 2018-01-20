/**
  ******************************************************************************
  * @file    lptm.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 LPTM 低功耗定时器 驱动
  ******************************************************************************
  */
#include "lptm.h"

/***********************************************************************************************
 功能：LPTMR 低功耗定时器 初始化
 形参：LPTM_InitStruct: LPTMR初始化结构 
 返回：0
 详解：0
************************************************************************************************/
void LPTM_Init(LPTM_InitTypeDef* LPTM_InitStruct)
{
	LPTMR_Type* LPTMx = LPTMR0;
	//参数检查
	assert_param(IS_LPTM_PC_MODE(LPTM_InitStruct->LPTM_Mode));
	assert_param(IS_LPTM_MAP(LPTM_InitStruct->LPTMxMap));
	
	//开启LPTM定时器模块
	SIM->SCGC5 |= SIM_SCGC5_LPTIMER_MASK; 
	//清空寄存器
	LPTMx->CSR = 0x00; 
  LPTMx->PSR = 0x00;
  LPTMx->CMR = 0x00;
	//定时计数模式
	if(LPTM_InitStruct->LPTM_Mode == LPTM_Mode_TC)
	{
		LPTMx->CSR &= ~LPTMR_CSR_TMS_MASK; 
		//不分频 采用1KHZ时钟源	
		LPTMx->PSR = LPTMR_PSR_PCS(0x1)|LPTMR_PSR_PBYP_MASK; 
		//设定初始值
		LPTMx->CMR = LPTMR_CMR_COMPARE(LPTM_InitStruct->LPTM_InitCompareValue); 
		//开启模块	
		LPTMx->CSR |= LPTMR_CSR_TEN_MASK;  
	}
	else //外部脉冲计数模式
	{
		LPTMx->CSR |= LPTMR_CSR_TMS_MASK; 
		//设置上升或者下降沿计数
		switch(LPTM_InitStruct->LPTM_Mode)
		{
			case LPTM_Mode_PC_RISING:
				LPTMx->CSR &= ~LPTMR_CSR_TPP_MASK;
				break;
			case LPTM_Mode_PC_FALLING:
				LPTMx->CSR |= LPTMR_CSR_TPP_MASK;
				break;
			default:break;
		}
		switch(LPTM_InitStruct->LPTMxMap)
		{
			case LPTM_CH1_PA19:
				SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
				//配置IO口为LPTM通道
				PORTA->PCR[19] &= ~(PORT_PCR_MUX_MASK);
				PORTA->PCR[19] |= PORT_PCR_MUX(6); 
				PORTA->PCR[19] |= PORT_PCR_PE_MASK; //使能上下拉功能
				//选择输入通道	 
				LPTMx->CSR |= LPTMR_CSR_TPS(1);
				break;
			case LPTM_CH2_PC5:
				SIM->SCGC5|=SIM_SCGC5_PORTC_MASK;
				//配置IO口为LPTM通道
				PORTC->PCR[5] &= ~(PORT_PCR_MUX_MASK);
				PORTC->PCR[5] |= PORT_PCR_MUX(4);
				PORTC->PCR[5] |= PORT_PCR_PE_MASK;    //使能上下拉功能
				//选择输入通道	 
				LPTMx->CSR |= LPTMR_CSR_TPS(2);
				break;
		}
		//自由运行模式
		LPTMx->CSR |= LPTMR_CSR_TFC_MASK;   
		LPTMx->PSR |= LPTMR_PSR_PBYP_MASK;  
		//开启模块	
		LPTMx->CSR |= LPTMR_CSR_TEN_MASK;  
	}
}

/***********************************************************************************************
 功能：LPTMR 设置定时器比较值
 形参：LPTMx: LPTMR模块号
       @arg LPTMR0 : LPTMR0模块
			 Value : 值 0-0xFFFF
 返回：0
 详解：0
************************************************************************************************/
void LPTM_SetCompareValue(LPTMR_Type* LPTMx, uint32_t Value)
{
	//参数检查
	assert_param(IS_LPTM_ALL_PERIPH(LPTMx));
	
	LPTMx->CMR = LPTMR_CMR_COMPARE(Value); 
}
/***********************************************************************************************
 功能：LPTMR 获得定时器比较值
 形参：LPTMx: LPTMR模块号
       @arg LPTMR0 : LPTMR0模块
 返回：CMR值  0-0xFFFF
 详解：0
************************************************************************************************/
uint32_t LPTM_GetCompareValue(LPTMR_Type* LPTMx)
{
	//参数检查
	assert_param(IS_LPTM_ALL_PERIPH(LPTMx));
	
	return (uint32_t)(LPTMx->CMR & LPTMR_CMR_COMPARE_MASK);
}
/***********************************************************************************************
 功能：LPTMR 获得计时器值
 形参：LPTMx: LPTMR模块号
       @arg LPTMR0 : LPTMR0模块
 返回：CNR值  0-0xFFFF
 详解：0
************************************************************************************************/
uint32_t LPTM_GetTimerCounterValue(LPTMR_Type* LPTMx)
{
	//参数检查
	assert_param(IS_LPTM_ALL_PERIPH(LPTMx));
	
	return (uint32_t)(LPTMx->CNR & LPTMR_CNR_COUNTER_MASK); 
}
/***********************************************************************************************
 功能：LPTMR 中断配置
 形参：LPTMx: LPTMR模块号
       @arg LPTMR0 : LPTMR0模块
			 LPTM_IT: 中断源
			 @arg LPTM_IT_TCF : LPTM定时器溢出中断
       NewState : 使能
       @arg ENABLE:  使能
       @arg DISABLE: 禁止
 返回：CNR值  0-0xFFFF
 详解：0
************************************************************************************************/
void LPTM_ITConfig(LPTMR_Type* LPTMx, uint16_t LPTM_IT, FunctionalState NewState)
{
	//参数检查
	assert_param(IS_LPTM_ALL_PERIPH(LPTMx));
	
	if(LPTM_IT == LPTM_IT_TCF)
	{
		(ENABLE == NewState)?(LPTMx->CSR |= LPTMR_CSR_TIE_MASK):(LPTMx->CSR &= ~LPTMR_CSR_TIE_MASK);
	}
}
/***********************************************************************************************
 功能：LPTMR 获得LPTM中断标志
 形参：LPTMx: LPTMR模块号
       @arg LPTMR0 : LPTMR0模块
			 LPTM_IT: 中断源
			 @arg LPTM_IT_TCF : LPTM定时器溢出中断
 返回：ITStatus : 标志
       @arg SET :  置位
       @arg RESET: 复位
 详解：0
************************************************************************************************/
ITStatus LPTM_GetITStatus(LPTMR_Type* LPTMx, uint16_t LPTM_IT)
{
	ITStatus retval;
	//参数检查
	assert_param(IS_LPTM_ALL_PERIPH(LPTMx));
	
	if(LPTM_IT == LPTM_IT_TCF)
	{
		(LPTMx->CSR & LPTMR_CSR_TCF_MASK)?(retval = SET):(retval = RESET);
	}
	return retval;
}
/***********************************************************************************************
 功能：LPTMR 清除IT标志位
 形参：LPTMx: LPTMR模块号
       @arg LPTMR0 : LPTMR0模块
			 LPTM_IT: 中断源
			 @arg LPTM_IT_TCF : LPTM定时器溢出中断
 返回：0
 详解：0
************************************************************************************************/
void LPTM_ClearITPendingBit(LPTMR_Type *LPTMx, uint16_t LPTM_IT)
{
	//参数检查
	assert_param(IS_LPTM_ALL_PERIPH(LPTMx));
	
	if(LPTM_IT == LPTM_IT_TCF)
	{
		LPTMx->CSR |= LPTMR_CSR_TCF_MASK;
	}
}
/***********************************************************************************************
 功能：LPTM 定时计数模式下 延时
 形参：ms: 0- 65535 设置定时器时间
 返回：0
 详解：0
************************************************************************************************/
void LPTM_DelayMs(LPTMR_Type* LPTMx, uint32_t ms)
{
  //参数检查
	assert_param(IS_LPTM_DELAY_TIME(ms));
	assert_param(IS_LPTM_ALL_PERIPH(LPTMx));
	//设置计时模式
  LPTMx->CMR = LPTMR_CMR_COMPARE(ms); 
	//开启定时器
	LPTMx->CSR |= LPTMR_CSR_TEN_MASK;		
	while(LPTM_GetITStatus(LPTMx,LPTM_IT_TCF) == RESET) {};
	//关闭定时器
	LPTMx->CSR &= ~LPTMR_CSR_TEN_MASK;		
}
/***********************************************************************************************
 功能：LPTMR 重置计数器
 形参：LPTMx: LPTMR模块号
       @arg LPTMR0 : LPTMR0模块
 返回：0
 详解：0
************************************************************************************************/
void LPTM_ResetTimeCounter(LPTMR_Type* LPTMx)
{
	//参数检查
	assert_param(IS_LPTM_ALL_PERIPH(LPTMx));
	
	//重启模块
	LPTMx->CSR &= ~(LPTMR_CSR_TEN_MASK);
	LPTMx->CSR |= LPTMR_CSR_TEN_MASK;
}


