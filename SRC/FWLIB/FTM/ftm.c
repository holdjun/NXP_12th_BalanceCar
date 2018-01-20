/**
  ******************************************************************************
  * @file    ftm.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 FTM 定时器 驱动 驱动文件
  ******************************************************************************
  */
#include "ftm.h"

/***********************************************************************************************
 功能：设置PWM工作模式
 形参：FTM_PWM_InitTypeDef:PWM初始化结构
 返回：0
 详解：0
************************************************************************************************/
static void FTM_PWM_SetMode(FTM_InitTypeDef *FTM_InitStruct)
{
	FTM_Type *FTMx = NULL;
	FTM_PWM_MapTypeDef *pFTM_Map = NULL;
	pFTM_Map = (FTM_PWM_MapTypeDef*)&(FTM_InitStruct->FTMxMAP);
	//找出FTM口
	switch(pFTM_Map->FTM_Index)
	{
		case 0:
			FTMx = FTM0;
			break;
		case 1:
			FTMx = FTM1;
			break;
		case 2:
			FTMx = FTM2;
			break;
		default:break;	
	}
	switch(FTM_InitStruct->FTM_Mode)
	{
		case FTM_Mode_EdgeAligned: //边沿对齐模式
			//禁止写保护
			FTMx->MODE |= FTM_MODE_WPDIS_MASK;
		  //禁止增强模式
			FTMx->MODE &= ~FTM_MODE_FTMEN_MASK;
		  //禁止正交编码模式
			FTMx->QDCTRL &= ~FTM_QDCTRL_QUADEN_MASK;
		  //边沿对齐
			FTMx->SC &= ~FTM_SC_CPWMS_MASK;
			FTMx->CONTROLS[pFTM_Map->FTM_CH_Index].CnSC = 0;
			FTMx->CONTROLS[pFTM_Map->FTM_CH_Index].CnSC |= (FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);	
			switch(pFTM_Map->FTM_CH_Index)
			{
				case 0:
				case 1:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN0_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_COMBINE0_MASK;	
					break;
				case 2:
				case 3:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN1_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_COMBINE1_MASK;					
					break;
				case 4:
				case 5:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN2_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_COMBINE2_MASK;	
					break;
				case 6:
				case 7:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN3_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_COMBINE3_MASK;	
					break;
				default:break;
			}
			break;
		case FTM_Mode_CenterAligned: //居中对齐模式
			//禁止写保护 可以写入所有FTM寄存器 禁止增强模式
			FTMx->MODE |= FTM_MODE_WPDIS_MASK;
			FTMx->MODE &= ~FTM_MODE_FTMEN_MASK;
			FTMx->QDCTRL &= ~FTM_QDCTRL_QUADEN_MASK;
			FTMx->SC |= FTM_SC_CPWMS_MASK;
			FTMx->CONTROLS[pFTM_Map->FTM_CH_Index].CnSC = 0;
			FTMx->CONTROLS[pFTM_Map->FTM_CH_Index].CnSC |= (FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);	
			switch(pFTM_Map->FTM_CH_Index)
			{
				case 0:
				case 1:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN0_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_COMBINE0_MASK;	
					break;
				case 2:
				case 3:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN1_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_COMBINE1_MASK;					
					break;
				case 4:
				case 5:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN2_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_COMBINE2_MASK;	
					break;
				case 6:
				case 7:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN3_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_COMBINE3_MASK;	
					break;
				default:break;
			}
			break;
		case FTM_Mode_Combine:  //组合模式 Chl(n) & Chl(n+1) 组合 在Chl(n) 输出
			//禁止写保护 可以写入所有FTM寄存器 开启增强模式
			FTMx->MODE |= FTM_MODE_WPDIS_MASK;
			FTMx->MODE |= FTM_MODE_FTMEN_MASK;
			FTMx->QDCTRL &= ~FTM_QDCTRL_QUADEN_MASK;
			FTMx->SC &= ~FTM_SC_CPWMS_MASK;
		  //死区控制
			//FTMx->DEADTIME=FTM_DEADTIME_DTPS(2)|FTM_DEADTIME_DTVAL(10);
		  //同步控制
			FTMx->SYNC = FTM_SYNC_CNTMIN_MASK|FTM_SYNC_CNTMAX_MASK;
			FTMx->SYNC |= FTM_SYNC_SWSYNC_MASK;
		  //装入计数值
			FTMx->CONTROLS[pFTM_Map->FTM_CH_Index].CnSC = 0;
			FTMx->CONTROLS[pFTM_Map->FTM_CH_Index].CnSC |= (FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);	
			switch(pFTM_Map->FTM_CH_Index)
			{
				case 0:
				case 1:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN0_MASK;
					FTMx->COMBINE |= FTM_COMBINE_COMBINE0_MASK;	
					FTMx->COMBINE &= ~FTM_COMBINE_COMP0_MASK;
				  FTMx->COMBINE |= FTM_COMBINE_SYNCEN0_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_DTEN0_MASK;
					break;
				case 2:
				case 3:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN1_MASK;
					FTMx->COMBINE |= FTM_COMBINE_COMBINE1_MASK;	
					FTMx->COMBINE &= ~FTM_COMBINE_COMP1_MASK;
				  FTMx->COMBINE |= FTM_COMBINE_SYNCEN1_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_DTEN1_MASK;
					break;
				case 4:
				case 5:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN2_MASK;
					FTMx->COMBINE |= FTM_COMBINE_COMBINE2_MASK;	
					FTMx->COMBINE &= ~FTM_COMBINE_COMP2_MASK;
				  FTMx->COMBINE |= FTM_COMBINE_SYNCEN2_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_DTEN2_MASK;
					break;
				case 6:
				case 7:
					FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN3_MASK;
					FTMx->COMBINE |= FTM_COMBINE_COMBINE3_MASK;	
					FTMx->COMBINE &= ~FTM_COMBINE_COMP3_MASK;
				  FTMx->COMBINE |= FTM_COMBINE_SYNCEN3_MASK;
					FTMx->COMBINE &= ~FTM_COMBINE_DTEN3_MASK;
					break;
				default:break;
			}
			case FTM_Mode_Complementary:
			{
				//禁止写保护 可以写入所有FTM寄存器 开启增强模式
				FTMx->MODE |= FTM_MODE_WPDIS_MASK;
				FTMx->MODE |= FTM_MODE_FTMEN_MASK;
				FTMx->QDCTRL &= ~FTM_QDCTRL_QUADEN_MASK;
				FTMx->SC &= ~FTM_SC_CPWMS_MASK;
				//死区控制
				FTMx->DEADTIME=FTM_DEADTIME_DTPS(2)|FTM_DEADTIME_DTVAL(5);
				//同步控制
				FTMx->SYNC = FTM_SYNC_CNTMIN_MASK|FTM_SYNC_CNTMAX_MASK;
				FTMx->SYNC |= FTM_SYNC_SWSYNC_MASK;
				//装入计数值
				FTMx->CONTROLS[pFTM_Map->FTM_CH_Index].CnSC = 0;
				FTMx->CONTROLS[pFTM_Map->FTM_CH_Index].CnSC |= (FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);
				switch(pFTM_Map->FTM_CH_Index)
				{
					case 0:
					case 1:
						FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN0_MASK;
						FTMx->COMBINE |= FTM_COMBINE_COMBINE0_MASK;	
						FTMx->COMBINE |= FTM_COMBINE_COMP0_MASK;
						FTMx->COMBINE |= FTM_COMBINE_SYNCEN0_MASK;
						FTMx->COMBINE |= FTM_COMBINE_DTEN0_MASK;
						break;
					case 2:
					case 3:
						FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN1_MASK;
						FTMx->COMBINE |= FTM_COMBINE_COMBINE1_MASK;	
						FTMx->COMBINE |= FTM_COMBINE_COMP1_MASK;
						FTMx->COMBINE |= FTM_COMBINE_SYNCEN1_MASK;
						FTMx->COMBINE |= FTM_COMBINE_DTEN1_MASK;
						break;
					case 4:
					case 5:
						FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN2_MASK;
						FTMx->COMBINE |= FTM_COMBINE_COMBINE2_MASK;	
						FTMx->COMBINE |= FTM_COMBINE_COMP2_MASK;
						FTMx->COMBINE |= FTM_COMBINE_SYNCEN2_MASK;
						FTMx->COMBINE |= FTM_COMBINE_DTEN2_MASK;
						break;
					case 6:
					case 7:
						FTMx->COMBINE &= ~FTM_COMBINE_DECAPEN3_MASK;
						FTMx->COMBINE |= FTM_COMBINE_COMBINE3_MASK;	
						FTMx->COMBINE |= FTM_COMBINE_COMP3_MASK;
						FTMx->COMBINE |= FTM_COMBINE_SYNCEN3_MASK;
						FTMx->COMBINE |= FTM_COMBINE_DTEN3_MASK;
						break;
					default:break;
				}
			}
			default:break;
	}
}
/***********************************************************************************************
 功能：改变PWM通道占空比
 形参：FTMxMAP:PWM 通道选择
			 @arg  FTM0_CH0_PC1: FTM0模块 0 通道 PC1引脚
			 @arg  FTM0_CH0_PA3: FTM0模块 0 通道 PA3引脚
			 @arg  ...
			 PWMDuty: 占空比0-10000 对应0-100%
 返回：0
 详解：0
************************************************************************************************/
void FTM_PWM_ChangeDuty(uint32_t FTMxMAP,uint32_t PWMDuty)
{
	uint32_t cv = 0;
	FTM_Type *FTMx = NULL;
	FTM_PWM_MapTypeDef* pFTM_Map = (FTM_PWM_MapTypeDef*) &FTMxMAP;
	//检测参数
	assert_param(IS_FTM_PWM_MAP(FTMxMAP));
	assert_param(IS_FTM_PWM_DUTY(PWMDuty));
	
	switch(pFTM_Map->FTM_Index)
	{
		case 0:
			FTMx = FTM0;
			break;
		case 1:
			FTMx = FTM1;
			break;
		case 2:
			FTMx = FTM2;
			break;
		default:break;
	}
	cv = ((FTMx->MOD)*(PWMDuty))/10000; //计算比较值
	FTMx->CONTROLS[pFTM_Map->FTM_CH_Index].CnV = cv; 
}
/***********************************************************************************************
 功能：初始化PWM功能
 形参：FTM_PWM_InitTypeDef PWM初始化结构
 返回：0
 详解：0
************************************************************************************************/
void FTM_Init(FTM_InitTypeDef *FTM_InitStruct)
{
	uint8_t prescaler;   //分频因数
	uint32_t mod;
	FTM_Type *FTMx = NULL;
	PORT_Type *FTM_PORT = NULL;
	FTM_PWM_MapTypeDef *pFTM_Map = (FTM_PWM_MapTypeDef*)&(FTM_InitStruct->FTMxMAP);
	
	//检测参数
	assert_param(IS_FTM_PWM_MAP(FTM_InitStruct->FTMxMAP));
	assert_param(IS_FTM_PWM_MODE(FTM_InitStruct->FTM_Mode));
	assert_param(IS_FTM_PWM_DUTY(FTM_InitStruct->InitalDuty));
	
	//找出FTM口
	switch(pFTM_Map->FTM_Index)
	{
		case 0:
			SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;
			FTMx = FTM0;
			break;
		case 1:
			SIM->SCGC6 |= SIM_SCGC6_FTM1_MASK;
			FTMx = FTM1;
			break;
		case 2:
			SIM->SCGC3 |= SIM_SCGC3_FTM2_MASK;
			FTMx = FTM2;
			break;
		default:break;	
	}
	//找出PORT端口
	switch(pFTM_Map->FTM_GPIO_Index)
	{
		case 0:
			FTM_PORT = PORTA;
			SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
			break;
		case 1:
			FTM_PORT = PORTB;
			SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;
			break;	
		case 2:
			FTM_PORT = PORTC;
			SIM->SCGC5|=SIM_SCGC5_PORTC_MASK;
			break;
		case 3:
			FTM_PORT = PORTD;
			SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;
			break;
		case 4:
			FTM_PORT = PORTE;
			SIM->SCGC5|=SIM_SCGC5_PORTE_MASK;
			break;
	}
	//设置对应的IO口为PWM模式
	FTM_PORT->PCR[pFTM_Map->FTM_Pin_Index] &= ~PORT_PCR_MUX_MASK;
	FTM_PORT->PCR[pFTM_Map->FTM_Pin_Index] |= PORT_PCR_MUX(pFTM_Map->FTM_Alt_Index);
  //计算分频和MODE参数 
	prescaler = (CPUInfo.BusClock/(FTM_InitStruct->Frequency))/65535;
 //PS>4时总会出错
	if(prescaler >= 4 ) prescaler = 4;
	//计算MODE装载参数
	mod = (CPUInfo.BusClock/((FTM_InitStruct->Frequency)*(1<<prescaler)));
  //时钟源及分频选择
	FTMx->SC &=~ FTM_SC_CLKS_MASK;
	FTMx->SC &= ~FTM_SC_PS_MASK;
	FTMx->SC |= (FTM_SC_CLKS(1)| FTM_SC_PS(prescaler));         
	
  //设置PWM周期及占空比
	FTMx->MOD = mod;                     //计数器最大值
	FTMx->CNTIN = 0x0000u;	             //计数器初始化时的计数值
	FTMx->CNT = 0x0000u;                 //计数器开始的值
	//适当延时
	for(mod=0;mod < 400000;mod++){}; //做适当延时 等待硬件模块启动操作
	//设置各个通道的模式
	 FTM_PWM_SetMode(FTM_InitStruct);
  //设置初始占空比	
	FTM_PWM_ChangeDuty(FTM_InitStruct->FTMxMAP,FTM_InitStruct->InitalDuty);
}

/***********************************************************************************************
 功能：FTM 正交解码器 初始化  这个函数还未经过测试  将在后续版本中开放 技术支持请联系QQ 1453363089
 形参：ftm  : FTM0  FTM1   FTM2
			  FTM0: 无效
			  FTM1: 
				  FTM1_QDA  PTA12   PTB0
          FTM1_QDB  PTA13   PTB1
			  FTM2: 
					FTM2_QDA  PTB18
					FTM2_QDB  PTB19
 返回：0
 详解：未测试
************************************************************************************************/
/*
uint8_t FTM_QUADInit(FTM_Type *ftm)
{
	//开启PORT时钟
	SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
	SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5|=SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;
	SIM->SCGC5|=SIM_SCGC5_PORTE_MASK;
 //开启响应PWM时钟
	switch((uint32_t)ftm)
	{
	  case FTM0_BASE:SIM->SCGC6|=SIM_SCGC6_FTM0_MASK;break;     
	  case FTM1_BASE:SIM->SCGC6|=SIM_SCGC6_FTM1_MASK;break;
	  case FTM2_BASE:SIM->SCGC3|=SIM_SCGC3_FTM2_MASK;break; 
	}
	//初始化引脚
	switch((uint32_t)ftm)
	{
		case FTM0_BASE:
			
			break;
		case FTM1_BASE:
		  PORTA->PCR[12]&=~(PORT_PCR_MUX_MASK); 
			PORTA->PCR[12]|=PORT_PCR_MUX(7); 
			PORTA->PCR[13]&=~(PORT_PCR_MUX_MASK); 
			PORTA->PCR[13]|=PORT_PCR_MUX(7); 
		  PORTB->PCR[0]&=~(PORT_PCR_MUX_MASK); 
			PORTB->PCR[0]|=PORT_PCR_MUX(6); 
			PORTB->PCR[1]&=~(PORT_PCR_MUX_MASK); 
			PORTB->PCR[1]|=PORT_PCR_MUX(6); 
			break;
		case FTM2_BASE:
		  PORTB->PCR[18]&=~(PORT_PCR_MUX_MASK); 
			PORTB->PCR[18]|=PORT_PCR_MUX(6); 
			PORTB->PCR[19]&=~(PORT_PCR_MUX_MASK); 
			PORTB->PCR[19]|=PORT_PCR_MUX(6); 
			break;
		default:break;
	}
	ftm->MOD = 14000; //根据需要设置
	ftm->CNTIN = 0;
	ftm->MODE |= FTM_MODE_WPDIS_MASK; //禁止写保护
	ftm->MODE |= FTM_MODE_FTMEN_MASK; //FTMEN=1,关闭TPM兼容模式，开启FTM所有功能
	ftm->QDCTRL &= ~FTM_QDCTRL_QUADMODE_MASK; //选定编码模式为A相与B相编码模式 
	ftm->QDCTRL |= FTM_QDCTRL_QUADEN_MASK; //使能正交解码模式
	//设置时钟
	ftm->SC |= FTM_SC_CLKS(1)|FTM_SC_PS(5);

	return 0;
}
*/

/***********************************************************************************************
 功能：FTM 正交解码器 读取数据  这个函数还未经过测试  将在后续版本中开放 技术支持请联系QQ 1453363089
 形参：ftm  : FTM0  FTM1   FTM2
			  FTM0: 无效
			  FTM1: 
				  FTM1_QDA  PTA12   PTB0
          FTM1_QDB  PTA13   PTB1
			  FTM2: 
					FTM2_QDA  PTB18
					FTM2_QDB  PTB19
			 uint32_t* value :计数值
			 uint8_t* dir    :方向
 返回：0
 详解：未测试
************************************************************************************************/
/*
uint8_t FTM_GetQUADValue(FTM_Type *ftm,uint32_t* value,uint8_t* dir)
{
	*dir = (((ftm->QDCTRL)>>FTM_QDCTRL_QUADIR_MASK)&1);
	*value = (ftm->CNT);
	return 0;
}
*/
/*
//生成
static const FTM_PWM_MapTypeDef FTM_PWM_Check_Maps[] = 
{ 
    {0, 0, 1, 2, 4},  //FTM0_CH0_PC1
    {0, 0, 3, 0, 3},  //FTM0_CH0_PA3
    {0, 1, 2, 2, 4},  //FTM0_CH1_PC2
    {0, 1, 4, 0, 3},  //FTM0_CH1_PA4
    {0, 2, 3, 2, 4},  //FTM0_CH2_PC3
    {0, 2, 5, 0, 3},  //FTM0_CH2_PA5
    {0, 3, 4, 2, 4},  //FTM0_CH3_PC4
    {0, 4, 4, 3, 4},  //FTM0_CH4_PD4
    {0, 5, 5, 3, 4},  //FTM0_CH5_PD5
    {0, 5, 0, 0, 3},  //FTM0_CH5_PA0
    {0, 6, 6, 3, 4},  //FTM0_CH6_PD6
    {0, 6, 1, 0, 3},  //FTM0_CH6_PA1
    {0, 7, 7, 3, 4},  //FTM0_CH7_PD7
    {0, 7, 2, 0, 3},  //FTM0_CH7_PA2
    {1, 0,12, 0, 3},  //FTM1_CH0_PA12
    {1, 0, 0, 1, 3},  //FTM1_CH0_PB0
    {1, 1,13, 0, 3},  //FTM1_CH1_PA13
    {1, 1, 1, 1, 3},  //FTM1_CH1_PB1
    {2, 0,18, 1, 3},  //FTM2_CH0_PB18
    {2, 1,19, 1, 3},  //FTM2_CH1_PB19
};

void PWM_CalConstValue(void)
{
	uint8_t i =0;
	uint32_t value = 0;
	for(i=0;i<sizeof(FTM_PWM_Check_Maps)/sizeof(FTM_PWM_MapTypeDef);i++)
	{
		value = FTM_PWM_Check_Maps[i].FTM_Index<<0;
		value|= FTM_PWM_Check_Maps[i].FTM_CH_Index<<4;
		value|= FTM_PWM_Check_Maps[i].FTM_Pin_Index<<8;
		value|= FTM_PWM_Check_Maps[i].FTM_GPIO_Index<<14;
		value|= FTM_PWM_Check_Maps[i].FTM_Alt_Index<<18;
		printf("(0x%08xU)\r\n",value);
	}
}
*/
/***********************************************************************************************
 功能：FTM_ITConfig
 形参：FTMx : FTM模块通道 
       @arg FTM0 : FTM0模块
			 @arg FTM1 : FTM1模块
			 @arg FTM2 : FTM2模块
			 FTM_IT ： FTM中断源
			 @arg FTM_IT_TOF          
			 @arg FTM_IT_CHF0          
			 @arg FTM_IT_CHF1          
			 @arg FTM_IT_CHF2          
			 @arg FTM_IT_CHF3          
			 @arg FTM_IT_CHF4          
			 @arg FTM_IT_CHF5          
			 @arg FTM_IT_CHF6          
			 @arg FTM_IT_CHF7         
			 NewState: 关闭或者使能
			 @arg ENABLE : 使能
			 @arg DISABLE:禁止
 返回：0
 详解：0
************************************************************************************************/
void FTM_ITConfig(FTM_Type* FTMx, uint16_t FTM_IT, FunctionalState NewState)
{
	//参数检查
	assert_param(IS_FTM_ALL_PERIPH(FTMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	switch(FTM_IT)
	{
		case FTM_IT_TOF:
			(ENABLE == NewState)?(FTMx->SC |= FTM_SC_TOIE_MASK):(FTMx->SC &= ~FTM_SC_TOIE_MASK);
			break;
		case FTM_IT_CHF0:
		case FTM_IT_CHF1:
		case FTM_IT_CHF2:
		case FTM_IT_CHF3:
		case FTM_IT_CHF4:
		case FTM_IT_CHF5:
		case FTM_IT_CHF6:
		case FTM_IT_CHF7:	
			(ENABLE == NewState)?(FTMx->CONTROLS[FTM_IT].CnSC |= FTM_CnSC_CHIE_MASK):(FTMx->CONTROLS[FTM_IT].CnSC &= ~FTM_CnSC_CHIE_MASK);		
			break;
		default:break;
	}
}
/***********************************************************************************************
 功能：FTM_GetITStatus 获得IT标志位
 形参：FTMx : FTM模块通道 
       @arg FTM0 : FTM0模块
			 @arg FTM1 : FTM1模块
			 @arg FTM2 : FTM2模块
			 FTM_IT ： FTM中断源
			 @arg FTM_IT_TOF          
			 @arg FTM_IT_CHF0          
			 @arg FTM_IT_CHF1          
			 @arg FTM_IT_CHF2          
			 @arg FTM_IT_CHF3          
			 @arg FTM_IT_CHF4          
			 @arg FTM_IT_CHF5          
			 @arg FTM_IT_CHF6          
			 @arg FTM_IT_CHF7         
 返回：ITStatus:标志
       @arg SET:标志位置位
       @arg RESET:标志位清0
 详解：0
************************************************************************************************/
ITStatus FTM_GetITStatus(FTM_Type* FTMx, uint16_t FTM_IT)
{
	ITStatus retval;
	//参数检查
	assert_param(IS_FTM_ALL_PERIPH(FTMx));
	assert_param(IS_FTM_IT(FTM_IT));
	

	switch(FTM_IT)
	{
		case FTM_IT_TOF:
			(FTMx->SC & FTM_SC_TOF_MASK)?(retval = SET):(retval = RESET);
		break;
		case FTM_IT_CHF0:
		case FTM_IT_CHF1:
		case FTM_IT_CHF2:
		case FTM_IT_CHF3:
		case FTM_IT_CHF4:
		case FTM_IT_CHF5:
		case FTM_IT_CHF6:
		case FTM_IT_CHF7:	
			(FTMx->CONTROLS[FTM_IT].CnSC& FTM_CnSC_CHF_MASK)?(retval = SET):(retval = RESET);
			break;
	}
	return retval;
}
/***********************************************************************************************
 功能：清IT 标志位
 形参：FTMx : FTM模块通道 
       @arg FTM0 : FTM0模块
			 @arg FTM1 : FTM1模块
			 @arg FTM2 : FTM2模块
			 FTM_IT ： FTM中断源
			 @arg FTM_IT_TOF          
			 @arg FTM_IT_CHF0          
			 @arg FTM_IT_CHF1          
			 @arg FTM_IT_CHF2          
			 @arg FTM_IT_CHF3          
			 @arg FTM_IT_CHF4          
			 @arg FTM_IT_CHF5          
			 @arg FTM_IT_CHF6          
			 @arg FTM_IT_CHF7         
 返回：0
 详解：0
************************************************************************************************/
void FTM_ClearITPendingBit(FTM_Type *FTMx,uint16_t FTM_IT)
{
	uint32_t read_value = 0;
	//参数检查
	assert_param(IS_FTM_ALL_PERIPH(FTMx));
	assert_param(IS_FTM_IT(FTM_IT));
	
	read_value = read_value;
	switch(FTM_IT)
	{
		case FTM_IT_TOF:
			read_value = FTMx->SC;
		break;
		case FTM_IT_CHF0:
		case FTM_IT_CHF1:
		case FTM_IT_CHF2:
		case FTM_IT_CHF3:
		case FTM_IT_CHF4:
		case FTM_IT_CHF5:
		case FTM_IT_CHF6:
		case FTM_IT_CHF7:	
			read_value = FTMx->CONTROLS[FTM_IT].CnSC;
			break;
	}
}





