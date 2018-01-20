/**
  ******************************************************************************
  * @file    spi.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 SPI模块驱动
  ******************************************************************************
  */
#include "spi.h"
/***********************************************************************************************
 功能：SPI 结构体初始化 填入默认的参数
 形参：SPI_InitStruct SPI 初始化结构
 返回：0
 详解：0
************************************************************************************************/
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
	SPI_InitStruct->SPI_DataSize = 8;
	SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_512;
	SPI_InitStruct->SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
}
/***********************************************************************************************
 功能：SPI 初始化
 形参：SPI_InitStruct SPI 初始化结构
 返回：0
 详解：0
************************************************************************************************/
void SPI_Init(SPI_InitTypeDef* SPI_InitStruct)
{
	SPI_Type *SPIx = NULL;
	PORT_Type *SPI_PORT = NULL;
	SPI_DataMapTypeDef *pSPI_DataMap = (SPI_DataMapTypeDef*)&(SPI_InitStruct->SPIxDataMap);
	SPI_CSMapTypeDef *pSPI_CSMap = (SPI_CSMapTypeDef*)&(SPI_InitStruct->SPIxPCSMap);
	
	//参数检测
	assert_param(IS_SPI_DATA_CHL(SPI_InitStruct->SPIxDataMap));
	assert_param(IS_SPI_PCS_CHL(SPI_InitStruct->SPIxPCSMap));
	assert_param(IS_SPI_BAUDRATE(SPI_InitStruct->SPI_BaudRatePrescaler));
	assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
	assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
	assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
	assert_param(IS_SPI_FIRSTBIT(SPI_InitStruct->SPI_FirstBit));
	
	//找出SPI模块 开SPI模块时钟
	switch(pSPI_DataMap->SPI_Index)
	{
		case 0:
			SIM->SCGC6 |= SIM_SCGC6_DSPI0_MASK;
			SPIx = SPI0;
			break;
		case 1:
			SIM->SCGC6 |= SIM_SCGC6_SPI1_MASK;
			SPIx = SPI1;
			break;
		case 2:
			SIM->SCGC3 |= SIM_SCGC3_SPI2_MASK;
		  SPIx = SPI2;
			break;
		default:break;     
	}
	//找出对应的PORT
	switch(pSPI_DataMap->SPI_GPIO_Index)
	{
		case 0:
			SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
			SPI_PORT = PORTA;
			break;
		case 1:
			SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
			SPI_PORT = PORTB;
			break;
		case 2:
			SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
			SPI_PORT = PORTC;
			break;
		case 3:
			SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
			SPI_PORT = PORTD;
			break;
		case 4:
			SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
			SPI_PORT = PORTE;
			break;
		default:break;
	}
	//开启对应的引脚 SCK SOUT SIN
	SPI_PORT->PCR[pSPI_DataMap->SPI_SCK_Pin_Index] &= ~PORT_PCR_MUX_MASK;
	SPI_PORT->PCR[pSPI_DataMap->SPI_SIN_Pin_Index] &= ~PORT_PCR_MUX_MASK;
	SPI_PORT->PCR[pSPI_DataMap->SPI_SOUT_Pin_Index] &= ~PORT_PCR_MUX_MASK;
	SPI_PORT->PCR[pSPI_DataMap->SPI_SCK_Pin_Index] |= PORT_PCR_MUX(pSPI_DataMap->SPI_Alt_Index);
	SPI_PORT->PCR[pSPI_DataMap->SPI_SIN_Pin_Index] |= PORT_PCR_MUX(pSPI_DataMap->SPI_Alt_Index);
	SPI_PORT->PCR[pSPI_DataMap->SPI_SOUT_Pin_Index] |= PORT_PCR_MUX(pSPI_DataMap->SPI_Alt_Index);
	//配置PCS
	//找出对应的PORT
	switch(pSPI_CSMap->SPI_GPIO_Index)
	{
		case 0:
			SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
			SPI_PORT = PORTA;
			break;
		case 1:
			SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
			SPI_PORT = PORTB;
			break;
		case 2:
			SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
			SPI_PORT = PORTC;
			break;
		case 3:
			SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
			SPI_PORT = PORTD;
			break;
		case 4:
			SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
			SPI_PORT = PORTE;
			break;
		default:break;
	}
	SPI_PORT->PCR[pSPI_CSMap->SPI_PCS_Pin_Index] &= ~PORT_PCR_MUX_MASK;
	SPI_PORT->PCR[pSPI_CSMap->SPI_PCS_Pin_Index] |= PORT_PCR_MUX(pSPI_CSMap->SPI_Alt_Index);
	//设置主从模式
	(SPI_InitStruct->SPI_Mode == SPI_Mode_Master)?(SPIx->MCR  |= SPI_MCR_MSTR_MASK):(SPIx->MCR  &= ~SPI_MCR_MSTR_MASK);
	//配置SPI主模式寄存器
	SPIx->MCR  = 0 & (~SPI_MCR_MDIS_MASK) 
									|SPI_MCR_HALT_MASK        //让SPI进入停止模式
									|SPI_MCR_MSTR_MASK        //配置SPI为主机模式
									|SPI_MCR_PCSIS_MASK       //PCS为高电平当在SPI不工作的时候
									|SPI_MCR_CLR_TXF_MASK     //首先要清除MDIS，清除TXF_MASK和RXF_MASK
									|SPI_MCR_CLR_RXF_MASK  
									|SPI_MCR_DIS_TXF_MASK     //然后再禁止TXD和RXD FIFO 模式 ，将SPI配置成正常模式
									|SPI_MCR_DIS_RXF_MASK; 
	//配置分频及波特率
	SPIx->CTAR[1] = 0| SPI_CTAR_DBR_MASK	 //设置通信的
									| SPI_CTAR_PCSSCK(0)
									| SPI_CTAR_PASC(0)
									| SPI_CTAR_PBR(0)
									| SPI_CTAR_CSSCK(0)
									| SPI_CTAR_FMSZ(SPI_InitStruct->SPI_DataSize -1) //设置数据传输的位数
									| SPI_CTAR_PDT(0);                                //设置片选信号在数据完成后的延时值 
	//分频设置
	SPIx->CTAR[1] |=SPI_CTAR_BR(SPI_InitStruct->SPI_BaudRatePrescaler);							 
	//时钟相位设置
	(SPI_InitStruct->SPI_CPHA == SPI_CPHA_1Edge)?(SPIx->CTAR[1] &= ~SPI_CTAR_CPHA_MASK):(SPIx->CTAR[1] |= SPI_CTAR_CPHA_MASK);
	//时钟极性
	(SPI_InitStruct->SPI_CPOL == SPI_CPOL_Low)?(SPIx->CTAR[1] &= ~SPI_CTAR_CPOL_MASK):(SPIx->CTAR[1] |= SPI_CTAR_CPOL_MASK);
	//配置MSB或者LSD
	(SPI_InitStruct->SPI_FirstBit == SPI_FirstBit_MSB)?(SPIx->CTAR[1] &= ~SPI_CTAR_LSBFE_MASK):(SPIx->CTAR[1] |= SPI_CTAR_LSBFE_MASK);
	//清空状态
  SPIx->SR = SPI_SR_EOQF_MASK   //队列结束标志 w1c  (write 1 to clear)     
            | SPI_SR_TFUF_MASK    //TX FIFO underflow flag  w1c
            | SPI_SR_TFFF_MASK    //TX FIFO fill      flag  w1c
            | SPI_SR_RFOF_MASK    //RX FIFO overflow  flag  w1c
            | SPI_SR_RFDF_MASK    //RX FIFO fill      flasg w1c (0时为空)
					  | SPI_SR_TCF_MASK;
	//开始传输
	 SPIx->MCR &= ~SPI_MCR_HALT_MASK;    //开始传输，见参考手册1129页
}

/***********************************************************************************************
 功能：SPI 读写一次数据
 形参：SPICSMap SPI 片选通道定义
       @arg SPI0_PCS0_PA14: SPI0通道 PCS0 PA14引脚
			 @arg ...
			 Data: 需要发送的数据
			 PCS_State: 片选信号状态
			 @arg SPI_PCS_Asserted: 发送完数据后 片选信号拉高
			 @arg SPI_PCS_Inactive: 发送完数据后 片选信号保持低电平
 返回：接收到的数据
 详解：0
************************************************************************************************/
uint16_t SPI_ReadWriteByte(uint32_t SPICSMap,uint16_t Data,uint16_t PCS_State)
{
	uint16_t temp = 0;
	SPI_Type *SPIx = NULL;
	SPI_CSMapTypeDef *pSPI_CSMap = (SPI_CSMapTypeDef*)&(SPICSMap);
	//参数检查
	assert_param(IS_SPI_PCS_STATE(PCS_State));
	assert_param(IS_SPI_PCS_CHL(SPICSMap));
	//找出SPI端口
	switch(pSPI_CSMap->SPI_Index)
	{
		case 0:
			SPIx = SPI0;
			break;
		case 1:
			SPIx = SPI1;
			break;
		case 2:
			SPIx = SPI2;
			break;
		default:break;
	}
	while((SPIx->SR & SPI_SR_TFFF_MASK) == 0){};  //等待发送缓冲区有空位
	SPIx->PUSHR = (((uint32_t)(((uint32_t)(PCS_State))<<SPI_PUSHR_CONT_SHIFT))&SPI_PUSHR_CONT_MASK) //是否拉起CS
							 | SPI_PUSHR_CTAS(1)      
						   | SPI_PUSHR_PCS(1<<(pSPI_CSMap->SPI_PCS_CH_Index))//使能信号
						 	 | SPI_PUSHR_TXDATA(Data); //写数据
	while(!(SPIx->SR & SPI_SR_TCF_MASK)){};     //等待发送完成
  SPIx->SR |= SPI_SR_TCF_MASK ;               //清除发送缓冲标志位
  //使接收缓冲器为空
  while((SPIx->SR & SPI_SR_RFDF_MASK) == 0){};   //RX FIFO 未接收到数据则一直等待
  temp = (uint8_t)(SPIx->POPR & 0xFF);           //数据以32位形式存在POPR中，转化格式 
  SPIx->SR |= SPI_SR_RFDF_MASK;                  //清除标志位
  return temp;
}

/***********************************************************************************************
 功能：SPI 中断配置
 形参：SPIx SPI 模块号
       @arg: SPI0 模块
			 @arg: SPI1 模块
       @arg: SPI2 模块
			 SPI_IT: 中断标志
			 @arg  SPI_IT_EOQF: 队列结束标志
       NewState : 开启或者关闭
       @arg ENABLE : 开启
       @arg DISABLE: 关闭
 返回：0
 详解：0
************************************************************************************************/
void SPI_ITConfig(SPI_Type* SPIx, uint16_t SPI_IT, FunctionalState NewState)
{
	//参数检查
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_IT(SPI_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	switch(SPI_IT)
	{
		case SPI_IT_EOQF:
			(ENABLE == NewState)?(SPIx->RSER |= SPI_RSER_EOQF_RE_MASK):(SPIx->RSER &= ~SPI_RSER_EOQF_RE_MASK);
			break;
		case SPI_IT_TFFF:
			(ENABLE == NewState)?(SPIx->RSER |= SPI_RSER_TFFF_RE_MASK):(SPIx->RSER &= ~SPI_RSER_TFFF_RE_MASK);
			break;
		case SPI_IT_TCF:
			(ENABLE == NewState)?(SPIx->RSER |= SPI_RSER_TCF_RE_MASK):(SPIx->RSER &= ~SPI_RSER_TCF_RE_MASK);
			break;
		case SPI_IT_TFUF:
			(ENABLE == NewState)?(SPIx->RSER |= SPI_RSER_TFUF_RE_MASK):(SPIx->RSER &= ~SPI_RSER_TFUF_RE_MASK);
			break;
		case SPI_IT_RFDF:
			(ENABLE == NewState)?(SPIx->RSER |= SPI_RSER_RFDF_RE_MASK):(SPIx->RSER &= ~SPI_RSER_RFDF_RE_MASK);
			break;
		case SPI_IT_RFOF:
			(ENABLE == NewState)?(SPIx->RSER |= SPI_RSER_RFOF_RE_MASK):(SPIx->RSER &= ~SPI_RSER_RFOF_RE_MASK);
			break;
		default:break;
	}
}
/***********************************************************************************************
 功能：SPI 获得中断标志
 形参：SPIx SPI 模块号
       @arg: SPI0 模块
			 @arg: SPI1 模块
       @arg: SPI2 模块
			 SPI_IT: 中断标志
			 @arg  SPI_IT_EOQF: 队列结束标志
 返回：SET OR RESET
 详解：0
************************************************************************************************/
ITStatus SPI_GetITStatus(SPI_Type* SPIx, uint16_t SPI_IT)
{
	ITStatus retval;
	//参数检查
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_IT(SPI_IT));
	
	switch(SPI_IT)
	{
		case SPI_IT_EOQF:
			(SPIx->SR & SPI_SR_EOQF_MASK)?(retval = SET):(retval = RESET);
			break;
		case SPI_IT_TFFF:
			(SPIx->SR & SPI_SR_TFFF_MASK)?(retval = SET):(retval = RESET);
			break;
		case SPI_IT_TCF:
			(SPIx->SR & SPI_SR_TCF_MASK)?(retval = SET):(retval = RESET);
			break;
		case SPI_IT_TFUF:
			(SPIx->SR & SPI_SR_TFUF_MASK)?(retval = SET):(retval = RESET);
			break;
		case SPI_IT_RFDF:
			(SPIx->SR & SPI_SR_RFDF_MASK)?(retval = SET):(retval = RESET);
			break;
		case SPI_IT_RFOF:
			(SPIx->SR & SPI_SR_RFOF_MASK)?(retval = SET):(retval = RESET);
			break;
		default:break;
	}
	return retval;
}

/***********************************************************************************************
 功能：SPI 清楚中断标志位
 形参：SPIx SPI 模块号
       @arg: SPI0 模块
			 @arg: SPI1 模块
       @arg: SPI2 模块
			 SPI_IT: 中断标志
			 @arg  SPI_IT_EOQF: 队列结束标志
 返回：0
 详解：0
************************************************************************************************/
void SPI_ClearITPendingBit(SPI_Type *SPIx,uint16_t SPI_IT)
{
	//参数检查
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_IT(SPI_IT));
	
	switch(SPI_IT)
	{
		case SPI_IT_EOQF:
			(SPIx->SR |= SPI_SR_EOQF_MASK);
			break;
		case SPI_IT_TFFF:
			(SPIx->SR |= SPI_SR_TFFF_MASK);
			break;
		case SPI_IT_TCF:
			(SPIx->SR |= SPI_SR_TCF_MASK);
			break;
		case SPI_IT_TFUF:
			(SPIx->SR |= SPI_SR_TFUF_MASK);
			break;
		case SPI_IT_RFDF:
			(SPIx->SR |= SPI_SR_RFDF_MASK);
			break;
		case SPI_IT_RFOF:
			(SPIx->SR |= SPI_SR_RFOF_MASK);
			break;
		default:break;
	}
}

/***********************************************************************************************
 功能：SPI DMA命令
 形参：SPIx SPI 模块号
       @arg: SPI0 模块
			 @arg: SPI1 模块
       @arg: SPI2 模块
			 SPI_IT: 中断标志
			 @arg  SPI_DMAReq_TFFF: 发送队列结束标志
       @arg  SPI_DMAReq_RFDF: 接收缓冲区满
 返回：0
 详解：0
************************************************************************************************/
void SPI_DMACmd(SPI_Type* SPIx, uint16_t SPI_DMAReq, FunctionalState NewState)
{
	//参数检查
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(SPI_DMAREQ(SPI_DMAReq));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	switch(SPI_DMAReq)
	{
		case SPI_DMAReq_TFFF:
			(ENABLE == NewState)?(SPIx->RSER |= SPI_RSER_TFFF_DIRS_MASK):(SPIx->RSER &= ~SPI_RSER_TFFF_DIRS_MASK);
			break;
		case SPI_DMAReq_RFDF:
			(ENABLE == NewState)?(SPIx->RSER |= SPI_RSER_RFDF_DIRS_MASK):(SPIx->RSER &= ~SPI_RSER_RFDF_DIRS_MASK);
			break;
		default:break;
	}
}

/*
static const SPI_CSMapTypeDef SPI_CSCheck_Maps[] = 
{ 
    {0, 2, 0, 14, 0}, //SPI0_PCS0_PA14
    {0, 2, 2,  3, 1}, //SPI0_PCS1_PC3
    {0, 2, 2,  2, 2}, //SPI0_PCS2_PC2
    {0, 2, 2,  1, 3}, //SPI0_PCS3_PC1
    {0, 2, 2,  0, 4}, //SPI0_PCS4_PC0
    {1, 2, 1, 10, 0}, //SPI1_PCS0_PB10
    {1, 2, 1,  9, 1}, //SPI1_PCS1_PB9
    {1, 2, 4,  5, 2}, //SPI1_PCS2_PE5
    {1, 2, 4,  6, 3}, //SPI1_PCS3_PE6
    {2, 2, 1, 20, 0}, //SPI2_PCS0_PB20
};

void SPI_CalCSConstValue(void)
{
	uint8_t i =0;
	uint32_t value = 0;
	for(i=0;i<sizeof(SPI_CSCheck_Maps)/sizeof(SPI_CSMapTypeDef);i++)
	{
		value = SPI_CSCheck_Maps[i].SPI_Index<<0;
		value|= SPI_CSCheck_Maps[i].SPI_Alt_Index<<2;
		value|= SPI_CSCheck_Maps[i].SPI_GPIO_Index<<5;
		value|= SPI_CSCheck_Maps[i].SPI_PCS_Pin_Index<<8;
		printf("(0x%08xU)\r\n",value);
	}
}

static const SPI_DataMapTypeDef SPI_DataCheck_Maps[] = 
{ 
    {0, 2, 0, 15, 16, 17},
    {0, 2, 2, 5 , 6 ,  7},
    {0, 2, 3, 1 , 2 ,  3},
    {1, 2, 4, 2 , 1 ,  3},
    {1, 2, 1, 11, 16, 17},
    {2, 2, 1, 21, 22, 23},
};

void SPI_CalDataConstValue(void)
{
	uint8_t i =0;
	uint32_t value = 0;
	for(i=0;i<sizeof(SPI_DataCheck_Maps)/sizeof(SPI_DataMapTypeDef);i++)
	{
		value = SPI_DataCheck_Maps[i].SPI_Index<<0;
		value|= SPI_DataCheck_Maps[i].SPI_Alt_Index<<2;
		value|= SPI_DataCheck_Maps[i].SPI_GPIO_Index<<5;
		value|= SPI_DataCheck_Maps[i].SPI_SCK_Pin_Index<<8;
		value|= SPI_DataCheck_Maps[i].SPI_SOUT_Pin_Index<<14;
		value|= SPI_DataCheck_Maps[i].SPI_SIN_Pin_Index<<20;
		printf("(0x%08xU)\r\n",value);
	}
}
*/
