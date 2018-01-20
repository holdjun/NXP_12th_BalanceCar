/**
  ******************************************************************************
  * @file    pit.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 内部定时器驱动
  ******************************************************************************
  */
#include "pit.h"
/***********************************************************************************************
 功能：初始化PIT模块
 形参：PIT_InitStruct：PIT初始化结构
 返回：0
 详解：
************************************************************************************************/
void PIT_Init(PIT_InitTypeDef* PIT_InitStruct)
{	 
	uint32_t time = 0;
	//检测参数
	assert_param(IS_PIT_CH(PIT_InitStruct->PITx));
	//计算分频数
	GetCPUInfo();
	time = (PIT_InitStruct->PIT_Interval)*(CPUInfo.BusClock/1000);
	//使能PIT时钟
	SIM->SCGC6|=SIM_SCGC6_PIT_MASK;
	//使能模块
	PIT->MCR&=~PIT_MCR_MDIS_MASK;
	//开始计时
	PIT->MCR|=PIT_MCR_FRZ_MASK;
	PIT->CHANNEL[PIT_InitStruct->PITx].LDVAL = (uint32_t)time;//设置延时时间
	PIT->CHANNEL[PIT_InitStruct->PITx].TFLG |= PIT_TFLG_TIF_MASK;//清除标志位
	PIT->CHANNEL[PIT_InitStruct->PITx].TCTRL |= (PIT_TCTRL_TEN_MASK);//开启定时器及中断，见参考手册976页
}
/***********************************************************************************************
 功能：PIT 获得预设定时器值大小
 形参：PITx：PIT通道
       @arg PIT0 : PIT0通道
       @arg PIT1 : PIT1通道
       @arg PIT2 : PIT2通道
       @arg PIT3 : PIT3通道
 返回：0
 详解：
************************************************************************************************/
uint32_t PIT_GetLoadValue(uint8_t PITx)
{
	//检测参数
	assert_param(IS_PIT_CH(PITx));
	
	return 	PIT->CHANNEL[PITx].LDVAL;
}
/***********************************************************************************************
 功能：PIT 获得当前运行定时器值大小
 形参：PITx：PIT通道
       @arg PIT0 : PIT0通道
       @arg PIT1 : PIT1通道
       @arg PIT2 : PIT2通道
       @arg PIT3 : PIT3通道
 返回：0
 详解：
************************************************************************************************/
uint32_t PIT_GetCurrentValue(uint8_t PITx)
{
	//检测参数
	assert_param(IS_PIT_CH(PITx));
		
	return PIT->CHANNEL[PITx].CVAL;
}
/***********************************************************************************************
 功能：PIT 设置预设值定时大小
 形参：PITx：PIT通道
       @arg PIT0 : PIT0通道
       @arg PIT1 : PIT1通道
       @arg PIT2 : PIT2通道
       @arg PIT3 : PIT3通道
			 Value : 值 0-0xFFFFFFFF
 返回：0
 详解：
************************************************************************************************/
void PIT_SetLoadValue(uint8_t PITx, uint32_t Value)
{
	//检测参数
	assert_param(IS_PIT_CH(PITx));
	
	PIT->CHANNEL[PITx].LDVAL = Value;
}
/***********************************************************************************************
 功能：PIT 开始工作
 形参：PITx：PIT通道
       @arg PIT0 : PIT0通道
       @arg PIT1 : PIT1通道
       @arg PIT2 : PIT2通道
       @arg PIT3 : PIT3通道
 返回：0
 详解：
************************************************************************************************/
void PIT_Start(uint8_t PITx)
{
	//检测参数
	assert_param(IS_PIT_CH(PITx));
	
	PIT->CHANNEL[PITx].TCTRL |= PIT_TCTRL_TEN_MASK;
}
/***********************************************************************************************
 功能：PIT 暂停
 形参：PITx：PIT通道
       @arg PIT0 : PIT0通道
       @arg PIT1 : PIT1通道
       @arg PIT2 : PIT2通道
       @arg PIT3 : PIT3通道
 返回：0
 详解：
************************************************************************************************/
void PIT_Stop(uint8_t PITx)
{
	//检测参数
	assert_param(IS_PIT_CH(PITx));
	
	PIT->CHANNEL[PITx].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}
/***********************************************************************************************
 功能：PIT 中断配置
 形参：PITx：PIT通道
       @arg PIT0 : PIT0通道
       @arg PIT1 : PIT1通道
       @arg PIT2 : PIT2通道
       @arg PIT3 : PIT3通道
			 PIT_IT : 中断号
       @arg PIT_IT_TIF : PIT定时中断
       NewState : 开启或者关闭
			 @arg ENABLE : 开启 
       @arg DISABLE: 关闭
 返回：0
 详解：
************************************************************************************************/
void PIT_ITConfig(uint8_t PITx, uint16_t PIT_IT, FunctionalState NewState)
{
	//检查参数
	assert_param(IS_PIT_IT(PIT_IT));
	assert_param(IS_PIT_CH(PITx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(PIT_IT == PIT_IT_TIF)
	{
		(ENABLE == NewState)?(PIT->CHANNEL[PITx].TCTRL |= PIT_TCTRL_TIE_MASK):(PIT->CHANNEL[PITx].TCTRL &= ~PIT_TCTRL_TIE_MASK);
	}
}
/***********************************************************************************************
 功能：PIT 获得中断标志
 形参：PITx：PIT通道
       @arg PIT0 : PIT0通道
       @arg PIT1 : PIT1通道
       @arg PIT2 : PIT2通道
       @arg PIT3 : PIT3通道
			 PIT_IT : 中断号
       @arg PIT_IT_TIF : PIT定时中断
 返回：SET:中断标志置位 RESET:没有发生中断
 详解：
************************************************************************************************/
ITStatus PIT_GetITStatus(uint8_t PITx, uint16_t PIT_IT)
{
	//检查参数
	assert_param(IS_PIT_IT(PIT_IT));
	assert_param(IS_PIT_CH(PITx));
	
	if(PIT_IT == PIT_IT_TIF)
	{
		if(PIT->CHANNEL[PITx].TFLG & PIT_TFLG_TIF_MASK)
		{
			return SET;
		}
		else
		{
			return RESET;
		}
	}
	return RESET;
}
/***********************************************************************************************
 功能：PIT 清除中断标志
 形参：PITx：PIT通道
       @arg PIT0 : PIT0通道
       @arg PIT1 : PIT1通道
       @arg PIT2 : PIT2通道
       @arg PIT3 : PIT3通道
			 PIT_IT : 中断号
       @arg PIT_IT_TIF : PIT定时中断
 返回：0
 详解：中断函数中调用
************************************************************************************************/
void PIT_ClearITPendingBit(uint8_t PITx,uint16_t PIT_IT)
{
	//检查参数
	assert_param(IS_PIT_IT(PIT_IT));
	assert_param(IS_PIT_CH(PITx));
	
	PIT->CHANNEL[PITx].TFLG |= PIT_TFLG_TIF_MASK;
}


