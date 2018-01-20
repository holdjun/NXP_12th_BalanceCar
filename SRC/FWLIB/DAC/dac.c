/**
  ******************************************************************************
  * @file    dac.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 DAC模块驱动
  ******************************************************************************
  */
#include "DAC.h"
/***********************************************************************************************
 功能：初始化结构体 填入默认参数
 形参：DAC_InitStruct: 初始化结构
 返回：0
 详解：0
************************************************************************************************/
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
	DAC_InitStruct->DAC_TrigerMode = DAC_TRIGER_MODE_SOFTWARE;
	DAC_InitStruct->DAC_BufferMode = BUFFER_MODE_NORMAL;
	DAC_InitStruct->DAC_BufferStartPostion = 0;
	DAC_InitStruct->DAC_BufferUpperLimit = 15;
	DAC_InitStruct->DAC_WaterMarkMode = WATER_MODE_4WORD;
}
/***********************************************************************************************
 功能：DAC初始化
 形参：DAC_InitStruct: DAC初始化结构
 返回：0
 详解：0
************************************************************************************************/
void DAC_Init(DAC_InitTypeDef* DAC_InitStruct)
{
	//参数检查
	assert_param(IS_DAC_TRIGGER_MODE(DAC_InitStruct->DAC_TrigerMode));
	assert_param(IS_DAC_BUFFER_MODE(DAC_InitStruct->DAC_BufferMode));
	assert_param(IS_DAC_WATERMARK_MODE(DAC_InitStruct->DAC_WaterMarkMode));
	
	//开启DAC模块时钟
	SIM->SCGC2|=SIM_SCGC2_DAC0_MASK;  
	//配置BUFFER模式
	switch(DAC_InitStruct->DAC_BufferMode)
	{
		case DAC_TRIGER_MODE_NONE:
			DAC0->C0 &= ~DAC_C0_DACTRGSEL_MASK;
			DAC0->C0 |= DAC_C0_DACSWTRG_MASK;
			break;
		case DAC_TRIGER_MODE_SOFTWARE:
			DAC0->C0 |= DAC_C0_DACTRGSEL_MASK;
			DAC0->C0 |= DAC_C0_DACSWTRG_MASK;
			break;
		case DAC_TRIGER_MODE_HARDWARE:
			DAC0->C0 &= ~DAC_C0_DACTRGSEL_MASK;
			DAC0->C0 &= ~DAC_C0_DACSWTRG_MASK;
			break;
		default:break;
	}
	//选择参考源2
	DAC0->C0 |= DAC_C0_DACRFS_MASK;  
	//开启DAC模块
	DAC0->C0 |= DAC_C0_DACEN_MASK ;
	
	//配置DAC_C1寄存器 配置BUFFER模式
	switch(DAC_InitStruct->DAC_BufferMode)
	{
		case BUFFER_MODE_NORMAL:
			DAC0->C1 |= DAC_C1_DACBFEN_MASK;
			DAC0->C1 |= DAC_C1_DACBFMD(0);
			break;
		case BUFFER_MODE_SWING:
			DAC0->C1 |= DAC_C1_DACBFEN_MASK;
			DAC0->C1 |= DAC_C1_DACBFMD(1);  
			break;
		case BUFFER_MODE_ONETIMESCAN:
			DAC0->C1 |= DAC_C1_DACBFEN_MASK;
			DAC0->C1 |= DAC_C1_DACBFMD(2);
			break;
		case BUFFER_MODE_DISABLE:
			DAC0->C1 &= ~DAC_C1_DACBFEN_MASK;
			break;
	}
	//设置水位
	switch(DAC_InitStruct->DAC_WaterMarkMode)
	{
		case WATER_MODE_1WORD:
			DAC0->C1 |= DAC_C1_DACBFWM(0);
			break;
		case WATER_MODE_2WORD:
			DAC0->C1 |= DAC_C1_DACBFWM(1);
			break;
		case WATER_MODE_3WORD:
			DAC0->C1 |= DAC_C1_DACBFWM(2);
			break;
		case WATER_MODE_4WORD:
			DAC0->C1 |= DAC_C1_DACBFWM(3);
			break;
		default:break;
	}

  //配置C2寄存器 设置上限和下线
	DAC0->C2 =  DAC_C2_DACBFUP(DAC_InitStruct->DAC_BufferUpperLimit);
	DAC0->C2 |= DAC_C2_DACBFRP(DAC_InitStruct->DAC_BufferStartPostion);
}

/***********************************************************************************************
 功能：使能DAC的DMA模块
 形参：DACx: DAC模块
       @arg DAC0 : DAC0模块
       DAC_DMAReq : DAC DMA触发源
       @arg DAC_DMAReq_DAC: DAC缓冲区标志置位
       NewState : 使能或者关闭
       @arg ENABLE : 使能
       @arg DISABLE: 关闭
 返回：0
 详解：0
************************************************************************************************/
void DAC_DMACmd(DAC_Type* DACx, uint16_t DAC_DMAReq, FunctionalState NewState)
{
	//参数检查
	assert_param(IS_DAC_ALL_PERIPH(DACx));
	assert_param(IS_DAC_DMAREQ(DAC_DMAReq));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	switch(DAC_DMAReq)
	{
		case DAC_DMAReq_DAC :
			(ENABLE == NewState)?(DACx->C1 |= DAC_C1_DMAEN_MASK):(DACx->C1 &= ~DAC_C1_DMAEN_MASK);
			break;
			default:break;
	}
}

/***********************************************************************************************
 功能：DAC 中断配置
 形参：DACx: DAC模块
       @arg DAC0 : DAC0模块
       DAC_IT : DAC中断源
			 @arg DAC_IT_POINTER_BUTTOM: POINTER到达底部时触发
			 @arg DAC_IT_POINTER_TOP:    POINTER到达顶部时触发 
			 @arg DAC_IT_WATER_MARK:     POINTER到达水位时触发
       NewState : 使能或者关闭
       @arg ENABLE : 使能
       @arg DISABLE: 关闭
 返回：0
 详解：0
************************************************************************************************/
void DAC_ITConfig(DAC_Type* DACx, uint16_t DAC_IT, FunctionalState NewState)
{
	//参数检查
	assert_param(IS_DAC_ALL_PERIPH(DACx));
	assert_param(IS_DAC_IT(DAC_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	switch(DAC_IT)
	{
		case DAC_IT_POINTER_BUTTOM:
			(ENABLE == NewState)?(DAC0->C0 |= DAC_C0_DACBBIEN_MASK):(DAC0->C0 &= ~DAC_C0_DACBBIEN_MASK);
			break;
		case DAC_IT_POINTER_TOP:
			(ENABLE == NewState)?(DAC0->C0 |= DAC_C0_DACBTIEN_MASK):(DAC0->C0 &= ~DAC_C0_DACBTIEN_MASK);
			break;
		case DAC_IT_WATER_MARK:
			(ENABLE == NewState)?(DAC0->C0 |= DAC_C0_DACBWIEN_MASK):(DAC0->C0 &= ~DAC_C0_DACBWIEN_MASK);
			break;
		default:break;
	}
}
/***********************************************************************************************
 功能：DAC 获得中断标志状态
 形参：DACx: DAC模块
       @arg DAC0 : DAC0模块
       DAC_IT : DAC中断源
			 @arg DAC_IT_POINTER_BUTTOM: POINTER到达底部时触发
			 @arg DAC_IT_POINTER_TOP:    POINTER到达顶部时触发 
			 @arg DAC_IT_WATER_MARK:     POINTER到达水位时触发
 返回：SET or RESET
 详解：0
************************************************************************************************/
ITStatus DAC_GetITStatus(DAC_Type* DACx, uint16_t DAC_IT)
{
	ITStatus retval;
	//参数检查
	assert_param(IS_DAC_ALL_PERIPH(DACx));
	assert_param(IS_DAC_IT(DAC_IT));
	
	switch(DAC_IT)
	{
		case DAC_IT_POINTER_BUTTOM:
		  (DACx->SR & DAC_SR_DACBFRPBF_MASK)?(retval = SET):(retval = RESET);
			break;
		case DAC_IT_POINTER_TOP:
			(DACx->SR & DAC_SR_DACBFRPTF_MASK)?(retval = SET):(retval = RESET);
			break;
		case DAC_IT_WATER_MARK:
			(DACx->SR & DAC_SR_DACBFWMF_MASK)?(retval = SET):(retval = RESET);
			break;
		default:break;
	}
	return retval;
}

/***********************************************************************************************
 功能：DAC 软件触发一次
 形参：DACx: DAC模块
       @arg DAC0 : DAC0模块
 返回：0
 详解：0
************************************************************************************************/
void DAC_SoftwareTrigger(DAC_Type *DACx)
{
	//参数检查
	assert_param(IS_DAC_ALL_PERIPH(DACx));
	
  DAC0->C0 |= DAC_C0_DACSWTRG_MASK;//软件触发一次
}

/***********************************************************************************************
 功能：DAC 设置DAC缓冲区
 形参：DACx: DAC模块
       @arg DAC0 : DAC0模块
			 pDACBuffer : 缓冲区指针
       NumberOfBuffer : 缓冲区大小 <=15
 返回：0
 详解：0
************************************************************************************************/
void DAC_SetBuffer(DAC_Type *DACx, uint16_t* pDACBuffer,uint8_t NumberOfBuffer)
{
	uint8_t i;
	//参数检查
	assert_param(IS_DAC_ALL_PERIPH(DACx));
	assert_param(IS_DAC_BUFFER_CNT(NumberOfBuffer));
	
	for(i=0;i<NumberOfBuffer;i++)
	{
		DACx->DAT[i].DATL = (pDACBuffer[i] & 0x00FF);
		DACx->DAT[i].DATH = (pDACBuffer[i] & 0xFF00)>>8;
	}                       
}
/***********************************************************************************************
 功能：当 DAC禁止BUFFER模式时 设置DAC输出值
 形参：DACx: DAC模块
       @arg DAC0 : DAC0模块
			 DAC_Value : 输出值 0-4095
 返回：0
 详解：实际上 设置DACBuffer[0] 的值 
************************************************************************************************/
void DAC_SetValue(DAC_Type *DACx,uint16_t DAC_Value)
{
	//参数检查
	assert_param(IS_DAC_ALL_PERIPH(DACx));
	assert_param(IS_DAC_BUFFER_VALUE(DAC_Value));
	
	DACx->DAT[0].DATL = (DAC_Value & 0x00FF);
	DACx->DAT[0].DATH = (DAC_Value & 0xFF00)>>8;
}


