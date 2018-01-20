/**
  ******************************************************************************
  * @file    gpio.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.25
  * @brief   超核K60固件库 GPIO 函数库 API函数
  ******************************************************************************
  */
 #include "gpio.h"
 
/***********************************************************************************************
 功能：GPIO初始化
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
			 GPIO_InitStruct
       GPIO 初始化结构
 返回：0
 详解：0
************************************************************************************************/
void GPIO_Init(GPIO_InitTypeDef* GPIO_InitStruct)
{
	GPIO_Type *GPIOx = NULL;
	PORT_Type *PORTx = NULL;
	//参数检测
	assert_param(IS_GPIO_ALL_PERIPH(GPIO_InitStruct->GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
	assert_param(IS_GPIO_BIT_ACTION(GPIO_InitStruct->GPIO_InitState )); 
	assert_param(IS_GPIO_IRQC(GPIO_InitStruct->GPIO_IRQMode));
	assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
	
	GPIOx = GPIO_InitStruct->GPIOx;
	//开端口时钟
	switch((uint32_t)GPIOx)
	{
		case PTA_BASE:PORTx=PORTA;SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;break; //开启PORTA口使能时钟，在设置前首先开启使能时钟参见k10手册268页，
	  case PTB_BASE:PORTx=PORTB;SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;break;	//开启PORTB口使能时钟
	  case PTC_BASE:PORTx=PORTC;SIM->SCGC5|=SIM_SCGC5_PORTC_MASK;break;	//开启PORTC口使能时钟
	  case PTD_BASE:PORTx=PORTD;SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;break;	//开启PORTD口使能时钟
	  case PTE_BASE:PORTx=PORTE;SIM->SCGC5|=SIM_SCGC5_PORTE_MASK;break;	//开启PORTE口使能时钟
	  default : break;
	} 
	//设置为GPIO模式
	PORTx->PCR[GPIO_InitStruct->GPIO_Pin]&=~(PORT_PCR_MUX_MASK);    
	PORTx->PCR[GPIO_InitStruct->GPIO_Pin]|=PORT_PCR_MUX(1); 
	//确定是输入还是输出
	if((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OOD) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OPP))
	{
		//配置GPIOx口的第GPIO_Pin引脚为输出
		GPIOx->PDDR |= (1<<(GPIO_InitStruct->GPIO_Pin));	
		//作为输出口时关闭该引脚的上下拉电阻功能
	  PORTx->PCR[(GPIO_InitStruct->GPIO_Pin)]&=~(PORT_PCR_PE_MASK); 
		//输出电平配置
		(Bit_SET == GPIO_InitStruct->GPIO_InitState)?(GPIOx->PDOR |= (1<<(GPIO_InitStruct->GPIO_Pin))):(GPIOx->PDOR &= ~(1<<(GPIO_InitStruct->GPIO_Pin)));
		//开漏或者推挽输出
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OOD)
		{
			PORTx->PCR[GPIO_InitStruct->GPIO_Pin]|= PORT_PCR_ODE_MASK;
		}
		else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OPP)
		{
			PORTx->PCR[GPIO_InitStruct->GPIO_Pin]&= ~PORT_PCR_ODE_MASK;
		}
	}
	//如果是输入模式
	else if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN_FLOATING) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU))
	{
		//配置GPIOx口的第GPIO_Pin引脚为输入
		GPIOx->PDDR &= ~(1<<(GPIO_InitStruct->GPIO_Pin));		
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN_FLOATING)
		{
			//关闭上下拉电阻
			PORTx->PCR[GPIO_InitStruct->GPIO_Pin]&=~PORT_PCR_PE_MASK; 	//上下拉电阻DISABLE
		}
		else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD) //下拉
		{
			//开启上拉电阻
			PORTx->PCR[GPIO_InitStruct->GPIO_Pin]|= PORT_PCR_PE_MASK; 	//上下拉电阻使能
			PORTx->PCR[GPIO_InitStruct->GPIO_Pin]&= ~PORT_PCR_PS_MASK;
			
		}
		else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU) //上拉
		{
			//开启上拉电阻
			PORTx->PCR[GPIO_InitStruct->GPIO_Pin]|= PORT_PCR_PE_MASK; 	//上下拉电阻使能
			PORTx->PCR[GPIO_InitStruct->GPIO_Pin]|= PORT_PCR_PS_MASK;
		}
	}
	//配置中断模式
	PORTx->PCR[GPIO_InitStruct->GPIO_Pin]&=~PORT_PCR_IRQC_MASK;
	PORTx->PCR[GPIO_InitStruct->GPIO_Pin]|=PORT_PCR_IRQC(GPIO_InitStruct->GPIO_IRQMode);//外部中断触发设置 
}
/***********************************************************************************************
 功能：GPIO获得中断标志
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
			 GPIO_Pin
       GPIO 端口号 GPIO_Pin_0 - GPIO_Pin_31
 返回：0
 详解：0
************************************************************************************************/
ITStatus GPIO_GetITStates(GPIO_Type *GPIOx,uint16_t GPIO_Pin)
{
	PORT_Type *PORTx = NULL;
	//开端口时钟
	switch((uint32_t)GPIOx)
	{
		case PTA_BASE:PORTx = PORTA;break;
	  case PTB_BASE:PORTx = PORTB;break;
	  case PTC_BASE:PORTx = PORTC;break;
	  case PTD_BASE:PORTx = PORTD;break;
	  case PTE_BASE:PORTx = PORTE;break;
	  default : break;
	} 
	//返回标志位
	if(PORTx->ISFR & (1<<GPIO_Pin))
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}
/***********************************************************************************************
 功能：GPIO清楚中断标志
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
			 GPIO_Pin
       GPIO 端口号 GPIO_Pin_0 - GPIO_Pin_31
 返回：0
 详解：在GPIO中断中调用此函数清楚标志位
************************************************************************************************/
void GPIO_ClearITPendingBit(GPIO_Type *GPIOx,uint16_t GPIO_Pin)
{
	PORT_Type *PORTx = NULL;
	//开端口时钟
	switch((uint32_t)GPIOx)
	{
		case PTA_BASE:PORTx=PORTA;SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;break; //开启PORTA口使能时钟，在设置前首先开启使能时钟参见k10手册268页，
	  case PTB_BASE:PORTx=PORTB;SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;break;	//开启PORTB口使能时钟
	  case PTC_BASE:PORTx=PORTC;SIM->SCGC5|=SIM_SCGC5_PORTC_MASK;break;	//开启PORTC口使能时钟
	  case PTD_BASE:PORTx=PORTD;SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;break;	//开启PORTD口使能时钟
	  case PTE_BASE:PORTx=PORTE;SIM->SCGC5|=SIM_SCGC5_PORTE_MASK;break;	//开启PORTE口使能时钟
	  default : break;
	} 
	PORTx->ISFR |= (1<<GPIO_Pin);
}
/***********************************************************************************************
 功能：初始化结构体 填入默认参数
 形参：GPIO_InitStruct: 初始化结构
 返回：0
 详解：0
************************************************************************************************/
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
	GPIO_InitStruct->GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN_FLOATING;
}
/***********************************************************************************************
 功能：将一个IO Pin设置为0 或 1
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
		 	 GPIO_Pin：
			 @arg : 0-31 数字
			 BitVal:
			 @arg Bit_RESET: 设置为0
			 @arg Bit_SET  : 设置为1
 返回：0
 详解：0
************************************************************************************************/
void GPIO_WriteBit(GPIO_Type *GPIOx,uint16_t GPIO_Pin,BitAction BitVal)
{	 
	//检测参数
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));
	assert_param(IS_GPIO_BIT_ACTION(BitVal)); 
	
  if (BitVal != Bit_RESET)
  {
    GPIOx->PSOR |= (1<<GPIO_Pin);
  }
  else
  {
    GPIOx->PCOR |= (1<<GPIO_Pin);
  }
}
/***********************************************************************************************
 功能：将一个IO Pin设置为1
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
		 	 GPIO_Pin：
			 @arg : 0-31 数字
 返回：0
 详解：0
************************************************************************************************/
void GPIO_SetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
	//检测参数
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));
	GPIOx->PSOR |= (1<<GPIO_Pin);
}
/***********************************************************************************************
 功能：将一个IO Pin设置为0
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
		 	 GPIO_Pin：
			 @arg : 0-31 数字
 返回：0
 详解：0
************************************************************************************************/
void GPIO_ResetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
	//检测参数
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));
	GPIOx->PCOR |= (1<<GPIO_Pin);
}

/***********************************************************************************************
 功能：翻转一个IO Pin的电平
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
		 	 GPIO_Pin：
			 @arg : 0-31 数字
 返回：0
 详解：0
************************************************************************************************/
void GPIO_ToggleBit(GPIO_Type *GPIOx,uint16_t GPIO_Pin)
{
	//检测参数
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));
	
	GPIOx->PTOR |= (1<<GPIO_Pin);	//将引脚的电平进行翻转，参考k10手册1483页
}
/***********************************************************************************************
 功能：写入端口IO电平 输出
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
		 	 PortVal：
			 @arg : 端口数据
 返回：0
 详解：0
************************************************************************************************/
void GPIO_Write(GPIO_Type *GPIOx,uint32_t PortVal)
{
	//检测参数
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	GPIOx->PDOR = PortVal;
}
/***********************************************************************************************
 功能：读取一个已经设置为输出的IO Pin的 电平
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
		 	 GPIO_Pin：
			 @arg 0-31: 端口号
 返回：端口电平
 详解：实际上就是读取PDOR的值
************************************************************************************************/
uint8_t GPIO_ReadOutputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
	uint8_t bitstatus = 0x00;
	//检测参数
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));
	
  if(((GPIOx->PDOR >> GPIO_Pin) & 1 ) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}
/***********************************************************************************************
 功能：读取一个已经设置为输出的IO的 电平
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
 返回：端口电平
 详解：实际上就是读取PDOR的值
************************************************************************************************/
uint32_t GPIO_ReadOutputData(GPIO_Type* GPIOx)
{
  //检测参数
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    
  return ((uint16_t)GPIOx->PDOR);
}
/***********************************************************************************************
 功能：读取一个IO端口的某一个PIN的电平
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
			 GPIO_Pin:
			 @arg 0-31 数字
 返回：逻辑电平 0 或者 1
 详解：必须先设置端口为输入端口
************************************************************************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{	 
	uint8_t bitstatus = 0x00;
	//检测参数
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));
	
  if (((GPIOx->PDIR >> GPIO_Pin)& 0x01) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}
/***********************************************************************************************
 功能：读取一个IO端口的输入电平
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
 返回：端口电平
 详解：必须先设置端口为输入端口
************************************************************************************************/
uint32_t GPIO_ReadInputData(GPIO_Type *GPIOx)
{
	//检测参数
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	
	 return(GPIOx->PDIR);
}

