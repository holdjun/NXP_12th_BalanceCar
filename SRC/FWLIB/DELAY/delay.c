/**
  ******************************************************************************
  * @file    delay.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.25
  * @brief   超核K60固件库 延时 函数库 API函数
  ******************************************************************************
  */
#include "delay.h"

//延时驱动C 文件
static uint8_t  fac_us=0;//us延时倍乘数
static uint32_t fac_ms=0;//ms延时倍乘数
#ifdef SYSTEM_SUPPORT_OS 	//如果使用UCOS兼容模式
#include "includes.h"					//ucos 使用	 
uint32_t OS_ReloadValue;         //SysTick重装值
/***********************************************************************************************
 功能：SysTick内核中断
 形参：0
 返回：0
 详解：主要用于为操作系统提供时钟节拍
************************************************************************************************/
void SysTick_Handler (void)
{
	OSIntEnter();		//进入中断
	OSTimeTick();       //调用ucos的时钟服务程序               
	OSIntExit();        //触发任务切换软中断
}
#endif
/***********************************************************************************************
 功能：初始化延时模块
 形参：0
 返回：0
 详解：此函数用于初始化延时模块,使用函数时必须调用。否则会造成延时函数出错
			 在使用uCOS时 必须在OSInit();之后调用DelayInit(); 以启动OS节拍
************************************************************************************************/
void DelayInit()//SYSCLK默认等于核心频率为48MHz 频率在MDK启动文件中设置 CLOCK_SETUP 宏
{
	SysTick->CTRL|=0x04;							//设置系统滴答时钟源为系统内核频率
	GetCPUInfo();  							//计算系统时钟
	fac_us=CPUInfo.CoreClock/1000000;
#ifdef SYSTEM_SUPPORT_OS					//如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
	SysTick->CTRL|=1<<1;   						//开启SYSTICK中断
	SysTick->LOAD=CPUInfo.CoreClock/OS_TICKS_PER_SEC; 	//每1/OS_TICKS_PER_SEC秒中断一次	
	OS_ReloadValue=SysTick->LOAD;                     //记录使用UCOS时的延时值
	SysTick->CTRL|=1<<0;   														//开启SYSTICK 
#else
	fac_ms=(uint32_t)fac_us*1000;
#endif
}

#ifdef SYSTEM_SUPPORT_OS	      //如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
/***********************************************************************************************
 功能：US级延时函数
 形参：US 需要延时多少US
 返回：0
 详解：带操作系统下的延时US
************************************************************************************************/
void DelayUs(uint32_t us)
{  
	uint32_t temp;
	uint32_t told;
	told=SysTick->VAL;								//刚进入时的计数器值
	OSSchedLock();										//阻止ucos调度，防止打断us延时
	SysTick->CTRL&=~(1<<1);   				//关闭SYSTICK中断
	SysTick->LOAD=us*fac_us; 					//时间加载
	SysTick->VAL=0x00;  						  //清空计数器
	SysTick->CTRL|=1<<0	; 						//开始倒数   
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); //等待时间到达   
	SysTick->LOAD=OS_ReloadValue;      //恢复OS 延时值
	SysTick->VAL=told;                 //恢复初值
	SysTick->CTRL|=1<<1;               //开启SYSTICK中断
	OSSchedUnlock();			             //开启ucos调度 								
}
/***********************************************************************************************
 功能：MS级延时函数
 形参：MS需要延时多少MS
 返回：0
 详解：带操作系统下的延时MS
************************************************************************************************/
void DelayMs(uint32_t ms)    
{
	if(OSRunning == TRUE)//如果os已经在跑了	 
	{ 
		if(ms>=(1000/OS_TICKS_PER_SEC))//延时的时间大于ucos的最少时间周期 
		{
   			OSTimeDly(ms/(1000/OS_TICKS_PER_SEC));//ucos延时
		}
		ms%=(1000/OS_TICKS_PER_SEC);			//ucos已经无法提供这么小的延时了,采用普通方式延时    
	}	
	if(ms != 0) DelayUs((uint32_t)(ms*1000));	//普通方式延时 	
}

#else //不用UCOS情况下

/***********************************************************************************************
 功能：US级延时函数
 形参：US 需要延时多少US
 返回：0
 详解：裸机下的延时US
************************************************************************************************/
void DelayUs(uint32_t us)
{ 
	uint32_t temp;
   SysTick->LOAD=us*fac_us; 					//时间加载
   SysTick->VAL=0x00;   							//清空计数器
   SysTick->CTRL|=0x01	;						 	//开始倒数   
		do
		{
			temp=SysTick->CTRL;
		}
	while(temp&0x01&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL&=~0x01;      				  //关闭计数器
}
/***********************************************************************************************
 功能：MS级延时函数
 形参：MS需要延时多少MS
 返回：0
 详解：裸机下的延时MS
************************************************************************************************/
void DelayMs(uint32_t ms)    
{
	uint32_t temp;
	uint16_t i;
	for(i=0;i<ms;i++)      			 		 //延时 MS 
	{
		SysTick->LOAD=fac_ms;  					 //时间加载1ms
		SysTick->VAL=0x00;    				   //清空计数器
		SysTick->CTRL|=0x01;   				 	 //开始倒数   
		do
		{
			temp=SysTick->CTRL;
		}
		while(temp&0x01&&!(temp&(1<<16)));  //等待时间到达   
		SysTick->CTRL&=~0x01;             	//关闭计数器
	}
}
#endif

