/**
  ******************************************************************************
  * @file    adc.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 ADC模块驱动
  ******************************************************************************
  */
#include "adc.h"
static uint8_t ADC_Cal(ADC_Type *ADCx);
/***********************************************************************************************
 功能：初始化ADC模块
 形参：ADC_InitStruct: ADC初始化结构
 返回：0
 详解：0
************************************************************************************************/
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct)
{
	ADC_MapTypeDef *pADC_Map = (ADC_MapTypeDef*)&ADC_InitStruct->ADCxMap;
	PORT_Type *ADC_PORT = NULL;
	ADC_Type *ADCx = NULL;
	//参数检查
	assert_param(IS_ADC_PRECISION(IS_ADC_PRECISION(ADC_InitStruct->ADC_Precision)));
	
	//找到对应的GPIO 并配置为ADC模式
	if(pADC_Map->ADC_IsAnalogChl == 0) //如果是普通GPIO 的ADC通道
	{
		switch(pADC_Map->ADC_GPIO_Index)
		{
			case 0:
				SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
				ADC_PORT = PORTA;
				break;
			case 1:
				SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
				ADC_PORT = PORTB;
				break;
			case 2:
				SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
				ADC_PORT = PORTC;
				break;
			case 3:
				SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
				ADC_PORT = PORTD;
				break;
			case 4:
				SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
				ADC_PORT = PORTE;
				break;
			default:break;
		}
		//配置对应引脚为ADC模式
		ADC_PORT->PCR[pADC_Map->ADC_Pin_Index] &= ~PORT_PCR_MUX_MASK;
		ADC_PORT->PCR[pADC_Map->ADC_Pin_Index] |= PORT_PCR_MUX(pADC_Map->ADC_Alt_Index);
	}
	//找出ADC端口
	switch(pADC_Map->ADC_Index)
	{
		case 0:
			SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
			//SIM->SOPT7 &= ~(SIM_SOPT7_ADC0ALTTRGEN_MASK  | SIM_SOPT7_ADC0PRETRGSEL_MASK); 
			//SIM->SOPT7 = SIM_SOPT7_ADC0TRGSEL(0);
			ADCx = ADC0;
			break;
		case 1:
			SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK;
			//SIM->SOPT7 &= ~(SIM_SOPT7_ADC1ALTTRGEN_MASK  | SIM_SOPT7_ADC1PRETRGSEL_MASK); 
			//SIM->SOPT7 = SIM_SOPT7_ADC1TRGSEL(0);
			ADCx = ADC1;
			break;
		default:break;
	}
	//配置转换精度
	ADCx->CFG1 &= ~(ADC_CFG1_MODE_MASK); 
	ADCx->CFG1 |= ADC_CFG1_MODE(ADC_InitStruct->ADC_Precision);
	//输入时钟源位BusClock
	ADCx->CFG1 &= ~ADC_CFG1_ADICLK_MASK;
	ADCx->CFG1 |=  ADC_CFG1_ADICLK(0); 
	//快速采样
	ADCx->CFG1 &= ~ADC_CFG1_ADLSMP_MASK;
	//配置ADC分频 最低分频
	ADCx->CFG1 &= ~ADC_CFG1_ADIV_MASK;
	ADCx->CFG1 |= ADC_CFG1_ADIV(3); 
	//设置 A或者B通道
	ADCx->CFG2 = 0;
	if(pADC_Map->ADC_IsChlAB == 0)
	{
		ADCx->CFG2 &= ~ADC_CFG2_MUXSEL_MASK;
	}
	else
	{
		ADCx->CFG2 |= ADC_CFG2_MUXSEL_MASK;
	}
	//其他杂项配置
	ADCx->CFG2 |= (ADACKEN_DISABLED|ADHSC_HISPEED|ADC_CFG2_ADLSTS(ADLSTS_20));
  ADCx->CV1 = 0x1234u; 
	ADCx->CV2 = 0x5678u;
	ADCx->SC2 = (ACFE_DISABLED|ACFGT_GREATER|ACREN_ENABLED|DMAEN_DISABLED| ADC_SC2_REFSEL(REFSEL_EXT));
	ADCx->SC3 = (CAL_OFF|ADCO_SINGLE|AVGE_ENABLED|ADC_SC3_AVGS(AVGS_32));
	ADCx->PGA = (PGAEN_DISABLED|PGACHP_NOCHOP|PGALP_NORMAL|ADC_PGA_PGAG(PGAG_64));

	//单端或者差分配置
	if(pADC_Map->ADC_SingleDifferential == 0)
	{
		ADCx->SC1[pADC_Map->ADC_IsChlAB] &= ~ADC_SC1_DIFF_MASK; 
	}
	else if (pADC_Map->ADC_SingleDifferential == 1)
	{
		ADCx->SC1[pADC_Map->ADC_IsChlAB] |= ADC_SC1_DIFF_MASK; 
	}
	//校准
  ADC_Cal(ADCx);
	//配置触发源
	(ADC_TRIGGER_HW == ADC_InitStruct->ADC_TriggerSelect)?(ADCx->SC2 |= ADC_SC2_ADTRG_MASK):(ADCx->SC2 &= ~ADC_SC2_ADTRG_MASK);
}
/***********************************************************************************************
 功能：软件触发 采样一个通道
 形参：ADCxMap: ADC通道定义
			 @arg  ADC0_SE6B_PD5: ADC0模块 6通道 PD5引脚
       @arg ...
 返回：0
 详解：0
************************************************************************************************/
uint16_t ADC_GetConversionValue(uint32_t ADCxMap)
{
	ADC_Type *ADCx = NULL;
	ADC_MapTypeDef *pADC_Map = (ADC_MapTypeDef*)&ADCxMap;
	
	//参数检查
	
	
	switch(pADC_Map->ADC_Index)
	{
		case 0:
			ADCx = ADC0;
			break;
		case 1:
			ADCx = ADC1;
			break;
		default:break;
	}
	//配置通道
	ADCx->SC1[pADC_Map->ADC_IsChlAB] &= ~(ADC_SC1_ADCH_MASK);	
	ADCx->SC1[pADC_Map->ADC_IsChlAB] |= pADC_Map->ADC_Chl;
	//等待转换完成
	while((ADCx->SC1[pADC_Map->ADC_IsChlAB] & ADC_SC1_COCO_MASK) == 0);
	//返回ADC输出返回结果
	return ADCx->R[pADC_Map->ADC_IsChlAB];
}

/***********************************************************************************************
 功能：ADC模块中断配置
 形参：ADCx: ADC模块号
       @arg ADC0 : ADC模块0
       @arg ADC1 : ADC模块1
       ADC_Mux : 复用选择
       @arg A : 复用A 
       @arg B : 复用B
       ADC_IT : ADC中断
       @arg ADC_IT_AI : ADC转换完成中断
			 NewState : 使能或者关闭
       @arg ENABLE : 使能
       @arg DISABLE: 关闭
 返回：0
 详解：0
************************************************************************************************/
void ADC_ITConfig(ADC_Type* ADCx,uint8_t ADC_Mux, uint16_t ADC_IT, FunctionalState NewState)
{
	//参数检查
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_IT(ADC_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	switch(ADC_IT)
	{
		case ADC_IT_AI:
			(ENABLE == NewState)?(ADCx->SC1[ADC_Mux] |= ADC_SC1_AIEN_MASK):(ADCx->SC1[ADC_Mux] &= ~ADC_SC1_AIEN_MASK);
			break;
		default:break;
	}
}
/***********************************************************************************************
 功能：ADC模块中断配置
 形参：ADCx: ADC模块号
       @arg ADC0 : ADC模块0
       @arg ADC1 : ADC模块1
       ADC_Mux : 复用选择
       @arg A : 复用A 
       @arg B : 复用B
       ADC_IT : ADC中断
       @arg ADC_IT_AI : ADC转换完成中断
 返回：SET  或者  RESET 
 详解：0
************************************************************************************************/
ITStatus ADC_GetITStatus(ADC_Type* ADCx, uint8_t ADC_Mux, uint16_t ADC_IT)
{
	ITStatus retval;
	//参数检查
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_MUX(ADC_Mux));
	assert_param(IS_ADC_IT(ADC_IT));
	
	switch(ADC_IT)
	{
		case ADC_IT_AI:
			(ADCx->SC1[ADC_Mux] & ADC_SC1_COCO_MASK)?(retval = SET):(retval = RESET);
			break;
		default:break;
	}
	return retval;
}

/***********************************************************************************************
 功能：ADC模块中断配置
 形参：ADCx: ADC模块号
       @arg ADC0 : ADC模块0
       @arg ADC1 : ADC模块1
       ADC_DMAReq : ADC触发源选择
       @arg ADC_DMAReq_COCO : ADC完成准换触发
			 NewState : 使能或者关闭
       @arg ENABLE : 使能
       @arg DISABLE: 关闭
 返回：SET  或者  RESET 
 详解：0
************************************************************************************************/
void ADC_DMACmd(ADC_Type* ADCx, uint16_t ADC_DMAReq, FunctionalState NewState)
{
	//参数检查
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_DMAREQ(ADC_DMAReq));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	switch(ADC_DMAReq)
	{
		case ADC_DMAReq_COCO:
			(NewState == ENABLE)?(ADCx->SC2 |= ADC_SC2_DMAEN_MASK):(ADCx->SC2 &= ~ADC_SC2_DMAEN_MASK);
			break;
			default:break;
	}
}
/*
static const ADC_MapTypeDef ADC_Check_Maps[] = 
{  //I  P  G  A  S  A   C
	  //ADC0 查分输入通道
    {0, 0, 0, 0, 1, 1 ,0, 0}, //ADC0_DP0_DM0
    {0, 0, 0, 0, 1, 1 ,0, 1}, //ADC0_DP1_DM1
    {0, 0, 0, 0, 1, 1 ,0, 2}, //ADC0_PGA0_DP_DM
    {0, 0, 0, 0, 1, 1 ,0, 3}, //ADC0_DP3_DM3
    {0, 0, 0, 0, 1, 1 ,0,26}, //ADC0_TEMP_SENOR_DIFF
    //ADC0 单端输入通道
    {0, 0, 0, 0, 0, 1 ,0,0}, //ADC0_SE0_DP0	
    {0, 0, 0, 0, 0, 1 ,0,1}, //ADC0_SE1_DP1	
    {0, 0, 0, 0, 0, 1 ,0,2}, //ADC0_SE2_PGA0_DP	
    {0, 0, 0, 0, 0, 1 ,0,3}, //ADC0_SE3_DP3	
    {0, 2, 2, 0, 0, 0 ,1,4}, //ADC0_SE4B_PC2	
    {0, 1, 3, 0, 0, 0 ,1,5}, //ADC0_SE5B_PD1	
    {0, 5, 3, 0, 0, 0 ,1,6}, //ADC0_SE6B_PD5	
		{0, 6, 3, 0, 0, 0 ,1,7}, //ADC0_SE7B_PD6	
		{0, 0, 1, 0, 0, 0 ,0,8}, //ADC0_SE8_PB0	
		{0, 1, 1, 0, 0, 0 ,0,9}, //ADC0_SE9_PB1	
		{0, 2, 1, 0, 0, 0 ,0,12}, //ADC0_SE12_PB2	
		{0, 3, 1, 0, 0, 0 ,0,13}, //ADC0_SE13_PB3	
		{0, 0, 2, 0, 0, 0 ,0,14}, //ADC0_SE14_PC0
		{0, 1, 2, 0, 0, 0 ,0,15}, //ADC0_SE15_PC1
		{0,24, 4, 0, 0, 0 ,0,17}, //ADC0_SE17_E24
		{0,25, 4, 0, 0, 0 ,0,18}, //ADC0_SE18_E25
		{0, 0, 0, 0, 0, 1 ,0,19}, //ADC0_SE19_DM0	
		{0, 0, 0, 0, 0, 1 ,0,20}, //ADC0_SE20_DM1	
		{0, 0, 0, 0, 0, 1 ,0,26}, //ADC1_TEMP_SENOR_SE		
	 //I  P  G  A  S  A   C
		//ADC1差分输入通道
		{1, 0, 0, 0, 1, 1 ,0, 0}, //ADC1_DP0_DM0	
		{1, 0, 0, 0, 1, 1 ,0, 1}, //ADC1_DP1_DM1	
		{1, 0, 0, 0, 1, 1 ,0, 2}, //ADC1_PGA1_DP_DM	
		{1, 0, 0, 0, 1, 1 ,0, 3}, //ADC1_DP3_DM3	
		{1, 0, 0, 0, 1, 1 ,0,26}, //ADC1_TEMP_SENOR_DIFF
    //ADC1单端输入通道
		{1, 0, 0, 0, 0, 1 ,0, 0}, //ADC1_SE0_DP0		
		{1, 0, 0, 0, 0, 1 ,0, 1}, //ADC1_SE1_DP1
		{1, 0, 0, 0, 0, 1 ,0, 2}, //ADC1_SE2_PGA1_DP	
		{1, 0, 0, 0, 0, 1 ,0, 3}, //ADC1_SE3_DP3	
		{1, 0, 4, 0, 0, 0 ,0, 4}, //ADC1_SE4_PE0	
		{1, 1, 4, 0, 0, 0 ,0, 5}, //ADC1_SE5_PE1	
		{1, 2, 4, 0, 0, 0 ,0, 6}, //ADC1_SE6_PE2	
		{1, 3, 4, 0, 0, 0 ,0, 7}, //ADC1_SE7_PE3	
		{1, 8, 2, 0, 0, 0 ,1, 4}, //ADC1_SE4B_PC8	
		{1, 9, 2, 0, 0, 0 ,1, 5}, //ADC1_SE5B_PC9	
		{1,10, 2, 0, 0, 0 ,1, 6}, //ADC1_SE6B_PC10	
		{1,11, 2, 0, 0, 0 ,1, 7}, //ADC1_SE7B_PC11	
		{1, 0, 1, 0, 0, 0 ,0, 8}, //ADC1_SE8_PB0		
		{1, 1, 1, 0, 0, 0 ,0, 9}, //ADC1_SE9_PB1	
		{1,10, 1, 0, 0, 0 ,0, 14}, //ADC1_SE14_PB10	
		{1,11, 1, 0, 0, 0 ,0, 15}, //ADC1_SE15_PB11	
		{1,17, 0, 0, 0, 0 ,0, 17}, //ADC1_SE17_PA17		
		{1, 0, 0, 0, 0, 1 ,0, 19}, //ADC1_SE19_DM0		
		{1, 0, 0, 0, 0, 1 ,0, 20}, //ADC1_SE20_DM1	
		{1, 0, 0, 0, 0, 1 ,0, 26}, //ADC1_TEMP_SENOR_SE		
};

void ADC_CalConstValue(void)
{
	uint8_t i =0;
	uint32_t value = 0;
	for(i=0;i<sizeof(ADC_Check_Maps)/sizeof(ADC_MapTypeDef);i++)
	{
		value = ADC_Check_Maps[i].ADC_Index<<0;
		value|= ADC_Check_Maps[i].ADC_Pin_Index<<6;
		value|= ADC_Check_Maps[i].ADC_GPIO_Index<<12;
		value|= ADC_Check_Maps[i].ADC_Alt_Index<<16;
		value|= ADC_Check_Maps[i].ADC_SingleDifferential<<20;
		value|= ADC_Check_Maps[i].ADC_IsAnalogChl<<22;
		value|= ADC_Check_Maps[i].ADC_IsChlAB<<24;
		value|= ADC_Check_Maps[i].ADC_Chl<<26;
		printf("(0x%08xU)\r\n",value);
	}
}
*/

//ADC校准程序
static uint8_t ADC_Cal(ADC_Type *ADCx)
{
  unsigned short cal_var;
  ADCx->SC2 &= ~ADC_SC2_ADTRG_MASK;
	ADCx->SC3 &= ( ~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK ); 
	ADCx->SC3 |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(AVGS_32) ); 
  ADCx->SC3 |= ADC_SC3_CAL_MASK ;      // Start CAL 
	while((ADCx->SC1[A] & ADC_SC1_COCO_MASK) == COCO_NOT);
	if((ADCx->SC3 & ADC_SC3_CALF_MASK) == CALF_FAIL)
	{
		return 1;
	}
  // Calculate plus-side calibration
  cal_var = 0x00;
  cal_var =  ADCx->CLP0; 
  cal_var += ADCx->CLP1; 
  cal_var += ADCx->CLP2; 
  cal_var += ADCx->CLP3; 
  cal_var += ADCx->CLP4; 
  cal_var += ADCx->CLPS; 
  cal_var = cal_var/2;
  cal_var |= 0x8000; // Set MSB
	ADCx->PG =  ADC_PG_PG(cal_var);
  // Calculate minus-side calibration
  cal_var = 0x00;
  cal_var =  ADCx->CLM0; 
  cal_var += ADCx->CLM1; 
  cal_var += ADCx->CLM2; 
  cal_var += ADCx->CLM3; 
  cal_var += ADCx->CLM4; 
  cal_var += ADCx->CLMS; 
  cal_var = cal_var/2;
  cal_var |= 0x8000; // Set MSB
	ADCx->MG = ADC_MG_MG(cal_var); 
  ADCx->SC3 &= ~ADC_SC3_CAL_MASK;
  return 0;
}
