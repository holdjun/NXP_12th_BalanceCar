/**
  ******************************************************************************
  * @file    can.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 CAN 驱动文件
  ******************************************************************************
  */
#include "can.h"
/***********************************************************************************************
 功能：CAN 设置波特率
 形参：CAN_Type: CAN结构
       @arg CAN0 : CAN0模块
			 @arg CAN1 : CAN1模块
			 baudrate: 波特率
			 @arg CAN_SPEED_33K
			 @arg CAN_SPEED_83K
			 @arg CAN_SPEED_50K
			 @arg CAN_SPEED_100K
			 @arg CAN_SPEED_125K
			 @arg CAN_SPEED_250K
			 @arg CAN_SPEED_500K
			 @arg CAN_SPEED_1000K			 
 返回：0
 详解：0
************************************************************************************************/
static uint8_t CAN_SetBaudrate(CAN_Type *can,uint8_t baudrate)
{
	switch(baudrate)
	{
		case CAN_SPEED_33K:
			 // 48M/120= 400k sclock, 12Tq
			 // PROPSEG = 3, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0, SAMP = 1
			 // RJW = 3, PSEG1 = 4, PSEG2 = 4,PRESDIV = 120
			can->CTRL1 = (0 | CAN_CTRL1_PROPSEG(2) 
											| CAN_CTRL1_RJW(2)
											| CAN_CTRL1_PSEG1(3) 
											| CAN_CTRL1_PSEG2(3)
											| CAN_CTRL1_PRESDIV(119));
		  break;
		case CAN_SPEED_83K:
			 // 48M/48= 1M sclock, 12Tq
			 // PROPSEG = 3, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0, SAMP = 1
			 // RJW = 3, PSEG1 = 4, PSEG2 = 4,PRESDIV = 48
			can->CTRL1 = (0 | CAN_CTRL1_PROPSEG(2) 
											| CAN_CTRL1_RJW(2)
											| CAN_CTRL1_PSEG1(3) 
											| CAN_CTRL1_PSEG2(3)
											| CAN_CTRL1_PRESDIV(47));
		  break;	
		case CAN_SPEED_50K:
			 // 48M/80= 0.6M sclock, 12Tq
			 // PROPSEG = 3, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0, SAMP = 1
			 // RJW = 3, PSEG1 = 4, PSEG2 = 4, PRESDIV = 40
			can->CTRL1 = (0 | CAN_CTRL1_PROPSEG(2) 
											| CAN_CTRL1_RJW(1)
											| CAN_CTRL1_PSEG1(3) 
											| CAN_CTRL1_PSEG2(3)
											| CAN_CTRL1_PRESDIV(79));	
		break;
		case CAN_SPEED_100K:
			 // 48M/40= 1.2M sclock, 12Tq
			 // PROPSEG = 3, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0, SAMP = 1
			 // RJW = 3, PSEG1 = 4, PSEG2 = 4, PRESDIV = 40
			can->CTRL1 = (0 | CAN_CTRL1_PROPSEG(2) 
											| CAN_CTRL1_RJW(2)
											| CAN_CTRL1_PSEG1(3) 
											| CAN_CTRL1_PSEG2(3)
											| CAN_CTRL1_PRESDIV(39));	
		break;
		case CAN_SPEED_125K:
			 // 48M/32= 1.5M sclock, 12Tq
			 // PROPSEG = 3, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0, SAMP = 1
			 // RJW = 3, PSEG1 = 4, PSEG2 = 4, PRESDIV = 32
			can->CTRL1 = (0 | CAN_CTRL1_PROPSEG(2) 
											| CAN_CTRL1_RJW(2)
											| CAN_CTRL1_PSEG1(3) 
											| CAN_CTRL1_PSEG2(3)
											| CAN_CTRL1_PRESDIV(31));		
		break;
		case CAN_SPEED_250K:
			 // 48M/16= 3M sclock, 12Tq
			 // PROPSEG = 3, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0, SAMP = 1
			 // RJW = 2, PSEG1 = 4, PSEG2 = 4, PRESDIV = 16
			can->CTRL1 = (0 | CAN_CTRL1_PROPSEG(2) 
											| CAN_CTRL1_RJW(1)
											| CAN_CTRL1_PSEG1(3) 
											| CAN_CTRL1_PSEG2(3)
											| CAN_CTRL1_PRESDIV(15));		
		break;
		case CAN_SPEED_500K:
			 // 48M/8=6M sclock, 12Tq
			 // PROPSEG = 3, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0, SAMP = 1
			 // RJW = 2, PSEG1 = 4, PSEG2 = 4, PRESDIV = 6
			can->CTRL1 = (0 | CAN_CTRL1_PROPSEG(2) 
											| CAN_CTRL1_RJW(1)
											| CAN_CTRL1_PSEG1(3) 
											| CAN_CTRL1_PSEG2(3)
											| CAN_CTRL1_PRESDIV(7));		
		break;
		case CAN_SPEED_1000K:
			 // 48M/6=8M sclock
			 // PROPSEG = 4, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0, SAMP = 1
			 // RJW = 1, PSEG1 = 1, PSEG2 = 2, PRESCALER = 6
			can->CTRL1 = (0 | CAN_CTRL1_PROPSEG(3) 
											| CAN_CTRL1_RJW(0)
											| CAN_CTRL1_PSEG1(0) 
											| CAN_CTRL1_PSEG2(1)
											| CAN_CTRL1_PRESDIV(5));	
		break;
		default: return 1;
	}
	return 0;
}

/***********************************************************************************************
 功能：CAN 初始化
 形参：CAN_InitStruct: CAN 初始化结构
 返回：0
 详解：0
************************************************************************************************/
void CAN_Init(CAN_InitTypeDef* CAN_InitStruct)
{
	uint8_t i = 0;
	PORT_Type *CAN_PORT = NULL;
	CAN_MapTypeDef *pCAN_Map = (CAN_MapTypeDef*)&(CAN_InitStruct->CANxMap);
  CAN_Type  *CANx = NULL;
	//参数检测
	assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->FilterEnable));
	assert_param(IS_CAN_MAP(CAN_InitStruct->CANxMap));
	assert_param(IS_CAN_SPEED(CAN_InitStruct->CAN_BaudRateSelect));
	//找出CAN模块 开启CAN模块时钟
	switch(pCAN_Map->CAN_Index )
	{
		case 0:
			SIM->SCGC6 |= SIM_SCGC6_FLEXCAN0_MASK;
			CANx = CAN0;
			break;
		case 1:
			SIM->SCGC3 |= SIM_SCGC3_FLEXCAN1_MASK;
			CANx = CAN1;
			break;
		default:break;     
	}
	//找出对应的PORT
	switch(pCAN_Map->CAN_GPIO_Index)
	{
		case 0:
			SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
			CAN_PORT = PORTA;
			break;
		case 1:
			SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
			CAN_PORT = PORTB;
			break;
		case 2:
			SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
			CAN_PORT = PORTC;
			break;
		case 3:
			SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
			CAN_PORT = PORTD;
			break;
		case 4:
			SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
			CAN_PORT = PORTE;
			break;
		default:break;
	}
	//开启对应的引脚 
	CAN_PORT->PCR[pCAN_Map->CAN_TX_Pin_Index] &= ~PORT_PCR_MUX_MASK;
	CAN_PORT->PCR[pCAN_Map->CAN_RX_Pin_Index] &= ~PORT_PCR_MUX_MASK;
	CAN_PORT->PCR[pCAN_Map->CAN_TX_Pin_Index] |= PORT_PCR_MUX(pCAN_Map->CAN_Alt_Index);
	CAN_PORT->PCR[pCAN_Map->CAN_RX_Pin_Index] |= PORT_PCR_MUX(pCAN_Map->CAN_Alt_Index);
	//选择为BusClock时钟
	CANx->CTRL1 |=  CAN_CTRL1_CLKSRC_MASK;	
	//使能冻结模式 只有进入冻结模式才能配置波特率
	CANx->MCR|=CAN_MCR_FRZ_MASK;
	//开启CAN通信模块 
	CANx->MCR &= ~CAN_MCR_MDIS_MASK;
	//等待通信模块复位启动
	while((CAN_MCR_LPMACK_MASK & (CANx->MCR)));
	//软件复位模块 //等待软件复位完成
	CANx->MCR |= CAN_MCR_SOFTRST_MASK;
	while(CAN_MCR_SOFTRST_MASK & (CANx->MCR));
	// 等待模块进入冻结模式
	while(!(CAN_MCR_FRZACK_MASK & (CANx->MCR)));
	for(i=0;i<16;i++)
	{
		CANx->MB[i].CS = 0x00000000;
		CANx->MB[i].ID = 0x00000000;
		CANx->MB[i].WORD0 = 0x00000000;
		CANx->MB[i].WORD1 = 0x00000000;
	}
	//配置远程请求产生，接收邮箱过滤ide，远程请求不比较，
	//邮箱首先从接收fifo匹配后再邮箱中匹配见参考手册
	CANx->CTRL2 = (0|CAN_CTRL2_TASD(22)); 
	//配置ID模式，目前选择的是A格式
	//按照工作要求配置MCR寄存器
	CANx->MCR |= CAN_MCR_IDAM(0); 
	//使能个别滤波和接受队列特点?
	//配置通信频率和初始化CTRL1  （自己理解的，设置传输一bite的时间）	 |CAN_CTRL1_LPB_MASK
  CANx->MCR |= CAN_MCR_IRMQ_MASK;    
  //设置传输速率
	CAN_SetBaudrate(CANx,CAN_InitStruct->CAN_BaudRateSelect);
	CANx->MCR |= CAN_MCR_IDAM(0); //配置ID模式，目前选择的是A格式
	//设置屏蔽功能
	if(CAN_InitStruct->FilterEnable == ENABLE)
	{
		for(i = 0; i < 16 ; i++)
		{
			CANx->RXIMR[i] = 0x1FFFFFFF; //设置16个接收id的掩码寄存器 
			CANx->RXMGMASK = 0x1FFFFFFF;
		} 	
	}
	else
	{
		for(i = 0; i < 16 ; i++)
		{
			CANx->RXIMR[i] = 0; //设置16个接收id的掩码寄存器 
			CANx->RXMGMASK = 0;
		} 		
	}
	//只有在冻结模式下才能配置 配置完退出冻结模式
	CANx->MCR &= ~(CAN_MCR_HALT_MASK);
	//等待模块推出冻结模式
	while((CAN_MCR_FRZACK_MASK & (CANx->MCR)));  
	//等待同步
	while(((CANx->MCR)&CAN_MCR_NOTRDY_MASK));    
	//设置接收ID过滤功能
}

/***********************************************************************************************
 功能：CAN 使能邮箱接收功能
 形参：CAN_Type: CAN结构
       @arg CAN0 : CAN0模块
			 @arg CAN1 : CAN1模块
			 RxMessage : 接收消息结构
 返回：0
 详解：0
************************************************************************************************/
void CAN_EnableReceiveMB(CAN_Type* CANx,CAN_RxMsgTypeDef* RxMessage)
{
	//参数检查
	assert_param(IS_CAN_ALL_PERIPH(CANx));
	assert_param(IS_CAN_MB_NUM(RxMessage->MBIndex));

	//不激活邮箱
	CANx->MB[RxMessage->MBIndex].CS = CAN_CS_CODE(0);
	//写入ID
	//拓展帧还是普通帧
	if(RxMessage->IDE == CAN_IDE_Extended)
	{
		CANx->MB[RxMessage->MBIndex].ID = RxMessage->Id;
		CANx->MB[RxMessage->MBIndex].CS = (0|CAN_CS_CODE(4)|CAN_CS_IDE_MASK);	 // 激活这个 MB 作为接受数据
	}
	else
	{
		CANx->MB[RxMessage->MBIndex].ID = RxMessage->Id<<18; 
		CANx->MB[RxMessage->MBIndex].CS = CAN_CS_CODE(4); 
	}
}

/***********************************************************************************************
 功能：CAN 发送一则消息
 形参：CAN_Type: CAN结构
       @arg CAN0 : CAN0模块
			 @arg CAN1 : CAN1模块
			 TxMessage : 发送消息结构
 返回：0
 详解：0
************************************************************************************************/
uint8_t CAN_Transmit(CAN_Type* CANx, CAN_TxMsgTypeDef* TxMessage)
{
	uint32_t temp_id = 0;
	uint16_t i,j;
	uint32_t word[2] = {0};
	//参数检查
	assert_param(IS_CAN_MB_NUM(TxMessage->MBIndex));
	assert_param(IS_CAN_RTR(TxMessage->RTR));
	assert_param(IS_CAN_IDE(TxMessage->IDE));
	assert_param(IS_CAN_ALL_PERIPH(CANx));
	assert_param(IS_CAN_DLC(TxMessage->DLC));
	assert_param(IS_CAN_IDE(TxMessage->IDE ));

	//转换数据格式
	for(i=0;i<TxMessage->DLC;i++)
	{
		if(i < 4)
		{
			word[0] |= ((TxMessage->Data[i])<<((3-i)*8));
		}
		else
		{
			word[1] |= ((TxMessage->Data[i])<<((7-i)*8));		
		}
	}
	//拓展帧还是普通帧
	(TxMessage->IDE == CAN_IDE_Extended)?(temp_id = ((1<<29)|TxMessage->Id)):(temp_id = ((1<<29)|(TxMessage->Id << 18)));
	//传输处理
	CANx->MB[TxMessage->MBIndex].CS = CAN_CS_CODE(8); // 写非激活代码
	CANx->MB[TxMessage->MBIndex].ID = temp_id;    
	CANx->MB[TxMessage->MBIndex].WORD0 = word[0];
	CANx->MB[TxMessage->MBIndex].WORD1 = word[1];  
	for(i = 0;i < 50;i++);	   //延时处理，让硬件准备好
	if(TxMessage->IDE == 1)
	{
		CANx->MB[TxMessage->MBIndex].CS = CAN_CS_CODE(12)|CAN_CS_IDE_MASK|CAN_CS_DLC(TxMessage->DLC)|CAN_CS_SRR_MASK;
	}
	else
	{
		CANx->MB[TxMessage->MBIndex].CS = CAN_CS_CODE(12)|CAN_CS_DLC(TxMessage->DLC);
	}
	//远程帧还是数据帧
	(TxMessage->RTR == CAN_RTR_Remote)?(CANx->MB[TxMessage->MBIndex].CS |= CAN_CS_RTR_MASK):(CANx->MB[TxMessage->MBIndex].CS &= ~CAN_CS_RTR_MASK);
	j=0; 
	//等待数据发送完成或则超时
	while(!(CANx->IFLAG1 & (1<<TxMessage->MBIndex)))
	{
		if((j++)>0x1000)
		return FALSE;
	}
	//清报文缓冲区中断标志
	CANx->IFLAG1 = (1<<TxMessage->MBIndex);	 //必须清除
	return TRUE;
}

/***********************************************************************************************
 功能：CAN 接收一则消息
 形参：CAN_Type: CAN结构
       @arg CAN0 : CAN0模块
			 @arg CAN1 : CAN1模块
			 RxMessage   : CAN邮箱接收结构
 返回：
			 @arg TRUE  : 接收成功
			 @arg FALSE : 接收失败
 详解：0
************************************************************************************************/
uint8_t CAN_Receive(CAN_Type* CANx,CAN_RxMsgTypeDef* RxMessage)
{
	uint8_t code = 0;
	uint8_t i = 0;
	uint8_t len = 0;
	uint32_t word[2] = {0};
	//参数检查
	assert_param(IS_CAN_MB_NUM(RxMessage->MBIndex));
	assert_param(IS_CAN_ALL_PERIPH(CANx));


	code = CANx->TIMER;    // 全局解锁 MB 操作
	
	//查看标志位
	if((CANx->IFLAG1 & (1<<(RxMessage->MBIndex))) == 0)
	{
		return FALSE;
	}
	code = CAN_get_code(CANx->MB[RxMessage->MBIndex].CS);
	if(code != 0x02)
	{
		//接收失败
		RxMessage->IDE = 0;
		return FALSE;
	}
	len = CAN_get_length(CANx->MB[RxMessage->MBIndex].CS);
	if(len < 1)
	{
		RxMessage->IDE = 0;
		return FALSE;
	}
	RxMessage->IDE = len;
	code = CANx->TIMER;    // 全局解锁 MB 操作
	CANx->IFLAG1 = (1<<(RxMessage->MBIndex));//必须清除
	word[0] = CANx->MB[RxMessage->MBIndex].WORD0;   //读取接收的数据
	word[1] = CANx->MB[RxMessage->MBIndex].WORD1;   //读取接收的数据
	//判断是标准帧还是拓展帧
	if(CANx->MB[RxMessage->MBIndex].CS & CAN_CS_IDE_MASK)
	{
		RxMessage->IDE = CAN_IDE_Extended;
		RxMessage->Id =  CANx->MB[RxMessage->MBIndex].ID;
	}
	else
	{
		RxMessage->IDE = CAN_IDE_Standard;
		RxMessage->Id =  CANx->MB[RxMessage->MBIndex].ID>>18;
	}
	//读取地址
	for(i=0;i<len;i++)
  {  
	 if(i < 4)
	 (RxMessage->Data[0+i])=(word[0]>>((3-i)*8));
	 else									 //数据存储转换
	 (RxMessage->Data[0+i])=(word[1]>>((7-i)*8));
  }
	return TRUE;
}
/***********************************************************************************************
 功能：CAN 中断配置
 形参：CAN_Type: CAN结构
       @arg CAN0 : CAN0模块
			 @arg CAN1 : CAN1模块
			 CAN_IT   : 中断源
       @arg CAN_IT_MB0 : 邮箱0中断
       @arg CAN_IT_MB1 : 邮箱1中断
       @arg CAN_IT_MB2 : 邮箱2中断
       @arg ... 
			 NewState : 开启或者关闭 
			 @arg ENABLE:  开启
       @arg DISABLE: 关闭
 返回：0
 详解：0
************************************************************************************************/
void CAN_ITConfig(CAN_Type* CANx, uint16_t CAN_IT, FunctionalState NewState)
{
  //参数检查
	assert_param(IS_CAN_ALL_PERIPH(CANx));
	assert_param(IS_CAN_IT_MB(CAN_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(CAN_IT <= CAN_IT_MB15)
	{
		(ENABLE == NewState)?(CANx->IMASK1 |= (1<<CAN_IT)):(CANx->IMASK1 &= ~(1<<CAN_IT));
	}
}
/***********************************************************************************************
 功能：CAN 获得IT状态
 形参：CAN_Type: CAN结构
       @arg CAN0 : CAN0模块
			 @arg CAN1 : CAN1模块
			 CAN_IT   : 中断源
       @arg CAN_IT_MB0 : 邮箱0中断
       @arg CAN_IT_MB1 : 邮箱1中断
       @arg CAN_IT_MB2 : 邮箱2中断
       @arg ... 
 返回：SET OR RESET
 详解：0
************************************************************************************************/
ITStatus CAN_GetITStatus(CAN_Type* CANx, uint16_t CAN_IT)
{
	ITStatus retval = RESET;
	
	if(CAN_IT <= CAN_IT_MB15)
	{
		((CANx->IFLAG1 >> CAN_IT) & 0x01)?(retval = SET):(retval = RESET);
	}
	return retval;
}
/***********************************************************************************************
 功能：CAN 清楚中断Pending
 形参：CAN_Type: CAN结构
       @arg CAN0 : CAN0模块
			 @arg CAN1 : CAN1模块
			 CAN_IT   : 中断源
       @arg CAN_IT_MB0 : 邮箱0中断
       @arg CAN_IT_MB1 : 邮箱1中断
       @arg CAN_IT_MB2 : 邮箱2中断
       @arg ... 
 返回：0
 详解：0
************************************************************************************************/
void CAN_ClearITPendingBit(CAN_Type* CANx, uint16_t CAN_IT)
{
  //参数检查
	assert_param(IS_CAN_ALL_PERIPH(CANx));
	assert_param(IS_CAN_IT_MB(CAN_IT));
	
	if(CAN_IT <= CAN_IT_MB15)
	{
		CANx->IFLAG1 |= (1<<CAN_IT);
	}
}
/***********************************************************************************************
 功能：CAN 清楚所有中断Pending
 形参：CAN_Type: CAN结构
       @arg CAN0 : CAN0模块
			 @arg CAN1 : CAN1模块
 返回：SET OR RESET
 详解：0
************************************************************************************************/
void CAN_ClearAllITPendingBit(CAN_Type* CANx)
{
  //参数检查
	assert_param(IS_CAN_ALL_PERIPH(CANx));
	
	CANx->IFLAG1 = 0xFFFF;
}

/*
static const CAN_MapTypeDef CAN_Check_Maps[] = 
{ 
    {0, 2, 0,12,13}, //CAN0_TX_PA12_RX_PA13
    {0, 2, 1,18,19}, //CAN0_TX_PB18_RX_PB19
    {1, 2, 4,24,25}, //CAN1_TX_PE24_RX_PE25
    {1, 2, 2,17,16}, //CAN1_TX_PC17_RX_PC16
};
void CAN_CalConstValue(void)
{
	uint8_t i =0;
	uint32_t value = 0;
	for(i=0;i<sizeof(CAN_Check_Maps)/sizeof(CAN_MapTypeDef);i++)
	{
		value = CAN_Check_Maps[i].CAN_Index <<0;
		value|= CAN_Check_Maps[i].CAN_Alt_Index <<2;
		value|= CAN_Check_Maps[i].CAN_GPIO_Index <<5;
		value|= CAN_Check_Maps[i].CAN_TX_Pin_Index<<8;
		value|= CAN_Check_Maps[i].CAN_RX_Pin_Index<<14;
		printf("(0x%08xU)\r\n",value);
	}
}
*/




