/**
  ******************************************************************************
  * @file    dma.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 DMA驱动
  ******************************************************************************
  */
#include "dma.h"
//PIT触发DMA有BUG 启动后就会不停的传输
/***********************************************************************************************
 功能：初始化结构体 填入默认参数
 形参：DMA_InitStruct: 初始化结构
 返回：0
 详解：0
************************************************************************************************/
void DMA_StructInit(DMA_InitTypeDef *DMA_InitStruct)
{
	//配置DMA通道 参数
	DMA_InitStruct->Channelx = DMA_CH0;
	DMA_InitStruct->DMAAutoClose = DISABLE;
	DMA_InitStruct->EnableState = DISABLE;
	DMA_InitStruct->PeripheralDMAReq  = 0;
	//配置目的地址传输参数
	DMA_InitStruct->DestBaseAddr = (uint32_t)NULL;
	DMA_InitStruct->DestDataSize = DMA_DST_8BIT;
	DMA_InitStruct->DestMajorInc = 0;
	DMA_InitStruct->DestMinorInc = 0;
	//配置源地址传输参数
	DMA_InitStruct->SourceBaseAddr = (uint32_t)NULL;
	DMA_InitStruct->SourceDataSize = DMA_SRC_8BIT;
	DMA_InitStruct->SourceMajorInc = 0;
	DMA_InitStruct->SourceMinorInc = 0;
}

/***********************************************************************************************
 功能：初始化DMA模块
 形参：DMA_InitStruct: 初始化结构
 返回：0
 详解：0
************************************************************************************************/
void DMA_Init(DMA_InitTypeDef *DMA_InitStruct)
{
	//参数检查
	assert_param(IS_DMA_REQ(DMA_InitStruct->PeripheralDMAReq));
	assert_param(IS_DMA_ATTR_SSIZE(DMA_InitStruct->SourceDataSize));
	assert_param(IS_DMA_ATTR_DSIZE(DMA_InitStruct->DestDataSize));
	assert_param(IS_DMA_CH(DMA_InitStruct->Channelx));
	assert_param(IS_DMA_MINOR_LOOP(DMA_InitStruct->MinorLoopLength));
	
	//打开DMA0和DMAMUX时钟源
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;    
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	//配置DMA触发源
	DMAMUX->CHCFG[DMA_InitStruct->Channelx] = DMAMUX_CHCFG_SOURCE(DMA_InitStruct->PeripheralDMAReq);
	//设置源地址信息	
	DMA0->TCD[DMA_InitStruct->Channelx].SADDR = DMA_InitStruct->SourceBaseAddr;
	//执行完源地址操作后，是否在源地址基础上累加
	DMA0->TCD[DMA_InitStruct->Channelx].SOFF = DMA_SOFF_SOFF(DMA_InitStruct->SourceMinorInc);
	//设置源地址传输宽度
	DMA0->TCD[DMA_InitStruct->Channelx].ATTR  = 0;
	DMA0->TCD[DMA_InitStruct->Channelx].ATTR |= DMA_ATTR_SSIZE(DMA_InitStruct->SourceDataSize);
	//主循环进行完后 是否更改源地址
	DMA0->TCD[DMA_InitStruct->Channelx].SLAST = DMA_InitStruct->SourceMajorInc;
	
	//设置目的地址信息
	DMA0->TCD[DMA_InitStruct->Channelx].DADDR = DMA_InitStruct->DestBaseAddr;
	//执行完源地址操作后，是否在源地址基础上累加
	DMA0->TCD[DMA_InitStruct->Channelx].DOFF = DMA_DOFF_DOFF(DMA_InitStruct->DestMinorInc);
	//设置目的地址传输宽度
	DMA0->TCD[DMA_InitStruct->Channelx].ATTR |= DMA_ATTR_DSIZE(DMA_InitStruct->DestDataSize);
	//主循环进行完后 是否更改源地址
	DMA0->TCD[DMA_InitStruct->Channelx].DLAST_SGA = DMA_InitStruct->DestMajorInc;
	
	//设置计数器长度 循环次数
	//设置数据长度 长度每次递减 也被称作当前主循环计数 current major loop count
	DMA0->TCD[DMA_InitStruct->Channelx].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(DMA_InitStruct->MinorLoopLength );
	//起始循环计数器 当主循环计数器为0 时候 将装载起始循环计数器的值
	DMA0->TCD[DMA_InitStruct->Channelx].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(DMA_InitStruct->MinorLoopLength);
	//设置每一次传输字节的个数  个数到达上限时 DMA便将数据存入RAM 
	DMA0->TCD[DMA_InitStruct->Channelx].NBYTES_MLNO = DMA_NBYTES_MLNO_NBYTES(DMA_InitStruct->TransferBytes);
//设置DMA TCD控制寄存器
	DMA0->TCD[DMA_InitStruct->Channelx].CSR = 0;
	if(DMA_InitStruct->DMAAutoClose == ENABLE)
	{
		 DMA0->TCD[DMA_InitStruct->Channelx].CSR  |=DMA_CSR_DREQ_MASK; 
	}
	else
	{
		 DMA0->TCD[DMA_InitStruct->Channelx].CSR  &=(~DMA_CSR_DREQ_MASK); 
	}
	//使能此寄存器DMA开始工作
	DMA_SetEnableReq(DMA_InitStruct->Channelx,DMA_InitStruct->EnableState);
	//DMA 通道使能
	DMAMUX->CHCFG[DMA_InitStruct->Channelx] |= DMAMUX_CHCFG_ENBL_MASK;
}

/***********************************************************************************************
 功能：启动或者关闭DMA传输
 形参：DMAChl: DMA0_CH0 - DMA_CH15
			 EnableState: 是否开启传输
			 @arg ENABLE : 开启传输
			 @arg x: 关闭传输
 返回：0
 详解：0
************************************************************************************************/
void DMA_SetEnableReq(uint8_t DMAChl,FunctionalState EnableState)
{
	//检测参数
	assert_param(IS_DMA_CH(DMAChl));
	assert_param(IS_FUNCTIONAL_STATE(EnableState));
	
	if(EnableState == ENABLE)
	{  
		DMA0->ERQ |= (1<<DMAChl);
	}
	else
	{
		DMA0->ERQ &= ~(1<<DMAChl);
	}
}

/***********************************************************************************************
 功能：判断DMA传输是否完成
 形参：DMAChl: DMA0_CH0 - DMA_CH15
 返回：
			 @arg TRUE:  传输完成
			 @arg FLASE: 传输未完成
 详解：0
************************************************************************************************/
uint8_t DMA_IsComplete(uint8_t DMAChl)
{
	//检测参数
	assert_param(IS_DMA_CH(DMAChl));
	
	if((DMA0->TCD[DMAChl].CSR & DMA_CSR_DONE_MASK))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/***********************************************************************************************
 功能：设置DMA MINOR LOOP LENGTH
 形参：DMAChl: DMA0_CH0 - DMA_CH15
			 DataNumber: 循环长度
 返回：0
 详解：0
************************************************************************************************/
void DMA_SetCurrDataCounter(uint8_t DMAChl,uint16_t DataNumber)
{
	//检测参数
	assert_param(IS_DMA_CH(DMAChl));
	assert_param(IS_DMA_MINOR_LOOP(DataNumber));
	
	DMA0->TCD[DMAChl].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(DataNumber);
}

/***********************************************************************************************
 功能：获得 DMA MINOR LOOP LENGTH
 形参：DMAChl: DMA0_CH0 - DMA_CH15
 返回：当前剩余的循环次数
 详解：0
************************************************************************************************/
uint16_t DMA_GetCurrDataCounter(uint8_t DMAChl)
{
	//检测参数
	assert_param(IS_DMA_CH(DMAChl));
	return (DMA0->TCD[DMAChl].CITER_ELINKNO & DMA_CITER_ELINKNO_CITER_MASK);
}
//时能中断
void DMA_ITConfig(DMA_Type* DMAx, uint16_t DMA_IT, uint8_t DMA_CH, FunctionalState NewState)
{
	
	switch(DMA_IT)
	{
		case DMA_IT_HALF:
			(ENABLE == NewState)?( DMA0->TCD[DMA_CH].CSR  |= DMA_CSR_INTHALF_MASK):( DMA0->TCD[DMA_CH].CSR  &= ~DMA_CSR_INTHALF_MASK);
			break;
		case DMA_IT_MAJOR:
			(ENABLE == NewState)?( DMA0->TCD[DMA_CH].CSR  |= DMA_CSR_INTMAJOR_MASK):( DMA0->TCD[DMA_CH].CSR  &= ~DMA_CSR_INTMAJOR_MASK);
			break;
		default:break;
	}
}

//获得中断标志
ITStatus DMA_GetITStatus(DMA_Type* DMAx, uint16_t DMA_IT, uint8_t DMA_CH)
{
	ITStatus retval = RESET;
	switch(DMA_IT)
	{
		case DMA_IT_HALF:
		case DMA_IT_MAJOR:
		(DMA0->TCD[DMA_CH].CSR & DMA_CSR_DONE_MASK)?(retval = SET):(retval = RESET);
		 break;
		default:break;
	}
	return retval;
}
//清除中断Pending
void DMA_ClearITPendingBit(DMA_Type* DMAx, uint16_t DMA_IT, uint8_t DMA_CH)
{
	switch(DMA_IT)
	{
		case DMA_IT_HALF:
		case DMA_IT_MAJOR:
			DMAx->INT |= (1 << DMA_CH);
			break;
		default:break;
	}
}

