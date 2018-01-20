/**
  ******************************************************************************
  * @file    sys.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 系统级API函数
  ******************************************************************************
  */
#include "sys.h"
CPUInfoType_t CPUInfo; //处理器运行信息结构体
extern uint32_t SystemCoreClock;
/***********************************************************************************************
 功能：获得系统信息
 形参：0
 返回：0
 详解：获得处理器型号 引脚   获得内核时钟,总线时钟，FlexBus时钟，Flash时钟 等     
************************************************************************************************/
void GetCPUInfo(void)
{
	//首先获得复位状态信息
	if (MC->SRSH & MC_SRSH_SW_MASK)     CPUInfo.ResetState = 1;
	if (MC->SRSH & MC_SRSH_LOCKUP_MASK) CPUInfo.ResetState = 2;
	if (MC->SRSH & MC_SRSH_JTAG_MASK)   CPUInfo.ResetState = 3;
	if (MC->SRSL & MC_SRSL_POR_MASK)    CPUInfo.ResetState = 4;
	if (MC->SRSL & MC_SRSL_PIN_MASK)  	CPUInfo.ResetState = 5;
	if (MC->SRSL & MC_SRSL_COP_MASK)    CPUInfo.ResetState = 6;
	if (MC->SRSL & MC_SRSL_LOC_MASK)    CPUInfo.ResetState = 7;
	if (MC->SRSL & MC_SRSL_LVD_MASK)    CPUInfo.ResetState = 8;
	if (MC->SRSL & MC_SRSL_WAKEUP_MASK) CPUInfo.ResetState = 9;
	//确定Kinetis系列型号
	switch((SIM->SDID & SIM_SDID_FAMID(0x7))>>SIM_SDID_FAMID_SHIFT) 
	{  
    	case 0x0: CPUInfo.FamilyType = 10; break;
    	case 0x1: CPUInfo.FamilyType = 20; break;
		  case 0x2: CPUInfo.FamilyType = 30; break;
			case 0x3: CPUInfo.FamilyType = 40; break;
			case 0x4: CPUInfo.FamilyType = 60; break;
			case 0x5: CPUInfo.FamilyType = 70; break;
			case 0x6: CPUInfo.FamilyType = 50; break;
			case 0x7: CPUInfo.FamilyType = 53; break;
			 default: CPUInfo.FamilyType = 0;  break;
	}
	//封装信息
	switch((SIM->SDID & SIM_SDID_PINID(0xF))>>SIM_SDID_PINID_SHIFT) 
	{  
		case 0x02: CPUInfo.PinCnt = 32;  break;
		case 0x04: CPUInfo.PinCnt = 48;  break;
		case 0x05: CPUInfo.PinCnt = 64;  break;
		case 0x06: CPUInfo.PinCnt = 80;  break;
		case 0x07: CPUInfo.PinCnt = 81;  break;
		case 0x08: CPUInfo.PinCnt = 100; break;
		case 0x09: CPUInfo.PinCnt = 104; break;
		case 0x0A: CPUInfo.PinCnt = 144; break;
		case 0x0C: CPUInfo.PinCnt = 196; break;
 		case 0x0E: CPUInfo.PinCnt = 256; break;
	  default:  CPUInfo.PinCnt = 0;   break;	
	}  
   //SiliconRevID
    switch((SIM->SDID & SIM_SDID_REVID(0xF))>>SIM_SDID_REVID_SHIFT) 
    { 
			case 0x0: CPUInfo.SiliconRev = 10;break;
			case 0x1: CPUInfo.SiliconRev = 11;break;
			case 0x2: CPUInfo.SiliconRev = 12;break;
			default:  CPUInfo.SiliconRev = 0; break;
    }	
	//PFlash大小
	switch((SIM->FCFG1 & SIM_FCFG1_PFSIZE(0xF))>>SIM_FCFG1_PFSIZE_SHIFT)
	{
		case 0x7: CPUInfo.PFlashSize = 128*1024;break;
		case 0x9: CPUInfo.PFlashSize = 256*1024;break;
		case 0xB: CPUInfo.PFlashSize = 512*1024;break;
		case 0xF: CPUInfo.PFlashSize = 512*1024;break;
	 	default:  CPUInfo.PFlashSize = 0*1024;  break; 		
	}
	//如果有FlexNVM 确定FlexNVM大小
	if (SIM->FCFG2 & SIM_FCFG2_PFLSH_MASK) 
	{
		CPUInfo.FlexNVMSize = 0;
	}
	else
	{
		//确定FLexNVM大小
		switch((SIM->FCFG1 & SIM_FCFG1_NVMSIZE(0xF))>>SIM_FCFG1_NVMSIZE_SHIFT)
		{
			case 0x0: CPUInfo.FlexNVMSize = 0;break;
			case 0x7: CPUInfo.FlexNVMSize = 128*1024;break;
			case 0x9: CPUInfo.FlexNVMSize = 256*1024;break;
			case 0xF: CPUInfo.FlexNVMSize = 256*1024;break;
			default:  CPUInfo.FlexNVMSize = 0;break; 		
		}
	}
	//RAM大小
	switch((SIM->SOPT1 & SIM_SOPT1_RAMSIZE(0xF))>>SIM_SOPT1_RAMSIZE_SHIFT)
	{
		case 0x5: CPUInfo.RAMSize = 32*1024;  break;
		case 0x7: CPUInfo.RAMSize = 64*1024;  break;
		case 0x8: CPUInfo.RAMSize = 96*1024;  break;
		case 0x9: CPUInfo.RAMSize = 128*1024; break;
		default:  CPUInfo.RAMSize = 0*1024;   break;	
	}
	//时钟计算
	//SystemCoreClockUpdate();            //重新计算CoreClock
	CPUInfo.CoreClock = SystemCoreClock;
	CPUInfo.BusClock=(SystemCoreClock/(((SIM->CLKDIV1&SIM_CLKDIV1_OUTDIV2_MASK)>>SIM_CLKDIV1_OUTDIV2_SHIFT)+1));     //计算BusClock
	CPUInfo.FlexBusClock=(SystemCoreClock/(((SIM->CLKDIV1&SIM_CLKDIV1_OUTDIV3_MASK)>>SIM_CLKDIV1_OUTDIV3_SHIFT)+1)); //计算FlexBusClock
	CPUInfo.FlashClock=(SystemCoreClock/(((SIM->CLKDIV1&SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT)+1));   //计算FlashClock
}
/***********************************************************************************************
 功能：设置 更改系统主频
 形参：ClockOption 时钟源选择
			 @arg  ClockSource_IRC    : 内部时钟源
			 @arg  ClockSource_EX8M   : 外部8M晶振
			 @arg  ClockSource_EX50M  : 外部50M晶振
			 CoreClock   希望达到的内核频率
			 @arg  CoreClock_48M : CoreClock = 48M
			 @arg  CoreClock_64M : CoreClock = 64M
			 @arg  CoreClock_72M : CoreClock = 72M
			 @arg  CoreClock_96M : CoreClock = 96M
			 @arg  CoreClock_100M : CoreClock = 100M
 返回：0
 详解：不是所有的频率都能达到 调用该函后 推荐使用DisplayCPUInfo来显示一个主频
       SystemClockSetup(ClockSource_EX50M,CoreClock_100M) 外部50M晶振 PLL倍频到CoreClock = 100M
************************************************************************************************/
void SystemClockSetup(uint8_t ClockOption,uint16_t CoreClock)
{
	//检测参数
	assert_param(IS_CLOCK_OPTION(ClockOption));
	assert_param(IS_CLOCK_SELECT(CoreClock));
	//使用内部晶振
		//分频策略:  
		//SIM_CLKDIV1_OUTDIV1(0) CORE     CLOCK  1分频   UP TO 100M  
		//SIM_CLKDIV1_OUTDIV2(1) BUS      CLOCK  2分频   UP TO 50M 
		//SIM_CLKDIV1_OUTDIV3(1) FlexBus  ClOCK  2分频   UP TO 50M 
		//SIM_CLKDIV1_OUTDIV4(3) Flash    ClOCK  3分频   UP TO 25M 
	if(ClockOption == ClockSource_IRC)
	{
		SIM->CLKDIV1 = (uint32_t)0xFFFFFFFFu; //配置系统预分频器 先设置为都为最低分频
		// 转到 FEI 模式 
		MCG->C1 = (uint8_t)0x06u;
		MCG->C2 = (uint8_t)0x00u;
		MCG->C4 &= ~((1<<6)|(1<<7)|(1<<5));
		switch(CoreClock)
		{
			case CoreClock_96M:
				MCG->C4|= (1<<6)|(1<<7)|(1<<5);  
				SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));
				SystemCoreClock	= 96000000;
				break;
			case CoreClock_72M:
				MCG->C4|= (1<<6)|(1<<7)|(0<<5);  
				SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(2));	
				SystemCoreClock	= 72000000;
				break;
			case CoreClock_48M:
				MCG->C4|= (0<<6)|(1<<7)|(1<<5);  
				SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(0)|SIM_CLKDIV1_OUTDIV3(0)|SIM_CLKDIV1_OUTDIV4(1));	
				SystemCoreClock	= 48000000;
				break;
			default: //48M
				MCG->C4|= (0<<6)|(1<<7)|(1<<5);  
				SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(0)|SIM_CLKDIV1_OUTDIV3(0)|SIM_CLKDIV1_OUTDIV4(1));	
				SystemCoreClock	= 48000000;
				break;
		}
		MCG->C5 = (uint8_t)0x00u;
		MCG->C6 = (uint8_t)0x00u;
		while((MCG->S & MCG_S_IREFST_MASK) == 0u);  //检查 FLL参考时钟是内部参考时钟
		while((MCG->S & 0x0Cu) != 0x00u);           //等待FLL被选择
	}
	if(ClockOption == ClockSource_EX8M || ClockOption == ClockSource_EX50M)
	{
		SIM->CLKDIV1 = (uint32_t)0xFFFFFFFFu; //配置系统预分频器 先设置为都为最低分频
		//转到 FBE 模式 
		OSC->CR = (uint8_t)0x00u;
		SIM->SOPT2 &= (uint8_t)~(uint8_t)0x01u;
		MCG->C2 = (uint8_t)0x24u;
		MCG->C1 = (uint8_t)0x9Au;
		MCG->C4 &= (uint8_t)~(uint8_t)0xE0u;
		MCG->C5 = (uint8_t)0x03u;
		MCG->C6 = (uint8_t)0x00u;
		while((MCG->S & MCG_S_OSCINIT_MASK) == 0u);//检查 FLL参考时钟是内部参考时钟 
		while((MCG->S & MCG_S_IREFST_MASK) != 0u); //检查 FLL参考时钟是内部参考时钟
		while((MCG->S & 0x0Cu) != 0x08u);          //等待 FBE 被选择
		if(ClockOption == ClockSource_EX8M)
		{
			MCG->C5 = (uint8_t)MCG_C5_PRDIV(3);        //8/4 = 2M
		}
		else if (ClockOption == ClockSource_EX50M)
		{
			MCG->C5 = (uint8_t)MCG_C5_PRDIV(24);        //50/25 = 2M
		}
		switch(CoreClock)
		{
			case CoreClock_48M:
				MCG->C6 = (uint8_t)(0x40u|MCG_C6_VDIV(0));
				SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(0)|SIM_CLKDIV1_OUTDIV3(0)|SIM_CLKDIV1_OUTDIV4(1));	
				SystemCoreClock	= 48000000;
				break;		
			case CoreClock_64M:
				MCG->C6 = (uint8_t)(0x40u|MCG_C6_VDIV(8));
				SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(2));
				SystemCoreClock	= 64000000;
				break;		
			case CoreClock_72M:
				MCG->C6 = (uint8_t)(0x40u|MCG_C6_VDIV(12));
				SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(2));
				SystemCoreClock	= 72000000;
				break;			
			case CoreClock_96M:
				MCG->C6 = (uint8_t)(0x40u|MCG_C6_VDIV(24));
				SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));		
				SystemCoreClock	= 96000000;
				break;		
			case CoreClock_100M:
				MCG->C6 = (uint8_t)(0x40u|MCG_C6_VDIV(26));
				SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));	
				SystemCoreClock	= 100000000;
				break;	
			case CoreClock_200M:
				if(ClockOption == ClockSource_EX8M)
				{
					MCG->C5 = (uint8_t)MCG_C5_PRDIV(1);        //8/2 = 4M
					MCG->C6 = (uint8_t)(0x40u|MCG_C6_VDIV(26));
					SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(7));	
				}
				else if (ClockOption == ClockSource_EX50M)
				{
					MCG->C5 = (uint8_t)MCG_C5_PRDIV(12);
					MCG->C6 = (uint8_t)(0x40u|MCG_C6_VDIV(28));
					SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(7));	
				}
				SystemCoreClock	= 200000000;
				break;			
			default:
				MCG->C6 = (uint8_t)(0x40u|MCG_C6_VDIV(0));
				SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(0)|SIM_CLKDIV1_OUTDIV3(0)|SIM_CLKDIV1_OUTDIV4(1));
				SystemCoreClock	= 48000000;
				break;
		} 
		while((MCG->S & MCG_S_PLLST_MASK) == 0u);   //等待PLLS 时钟源转到 PLL
		while((MCG->S & MCG_S_LOCK_MASK) == 0u);    //等待锁定
		//转到PEE
		MCG->C1 = (uint8_t)0x1Au;
		while((MCG->S & 0x0Cu) != 0x0Cu);           //等待PLL输出
		while((MCG->S & MCG_S_LOCK_MASK) == 0u);      //等待PLL锁定
	}
	GetCPUInfo();//获取CPU信息 重新计算各个总线频率
}
/***********************************************************************************************
 功能：设置一个中断的优先级
 形参：IRQn 中断号
			 PriorityGroup 优先级分组 
		   @arg NVIC_PriorityGroup_0
			 @arg NVIC_PriorityGroup_1
		   @arg NVIC_PriorityGroup_2
			 @arg NVIC_PriorityGroup_3
		   @arg NVIC_PriorityGroup_4
		 	 PreemptPriority  抢占优先级
			 SubPriority      子优先级(响应优先级)
 返回：0
 详解：如果两个中断的抢占优先级和响应优先级都一样的话 则看哪种中断先发生就先执行
			 高优先级的抢占优先级是可以打断低优先级的抢占优先级中断的
			 而抢占优先级相同的中断 高优先级的响应优先级不可以打断低优先级的响应优先级 
************************************************************************************************/
void NVIC_Init(IRQn_Type IRQn,uint32_t PriorityGroup,uint32_t PreemptPriority,uint32_t SubPriority)
{
	//检测参数
  assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(PreemptPriority));  
  assert_param(IS_NVIC_SUB_PRIORITY(SubPriority));
	//设置NVIC中断分组
	NVIC_SetPriorityGrouping(PriorityGroup);
	//配置中断优先级
	NVIC_SetPriority(IRQn,NVIC_EncodePriority(PriorityGroup,PreemptPriority,SubPriority));
}
/***********************************************************************************************
 功能：软复位
 形参：0
 返回：0
 详解：软复位
************************************************************************************************/
void SystemSoftReset(void)
{   
	//SCB->AIRCR =0X05FA0000|(uint32_t)0x04;	 
	NVIC_SystemReset();
} 
/***********************************************************************************************
 功能：使能总中断
 形参：0
 返回：0
 详解：调用  CMSIS Cortex-M Core Function Access 层 函数 在.core_cmFunc.h
************************************************************************************************/
void EnableInterrupts(void)
{
	__enable_irq();
}
/***********************************************************************************************
 功能：关闭总中断
 形参：0
 返回：0
 详解：调用  CMSIS Cortex-M Core Function Access 层 函数 在.core_cmFunc.h
************************************************************************************************/
void DisableInterrupts(void)
{
	__disable_irq();
}
/***********************************************************************************************
 功能：设置中断向量表起始位置
 形参：0
 返回：0
 详解：
************************************************************************************************/
void SetVectorTable(uint32_t VectorOffset)
{
	//检测参数
  assert_param(IS_VECTOR_OFFSET(VectorOffset));
	SCB->VTOR = VectorOffset;  //更改中断向量表偏移地址
}
/***********************************************************************************************
 功能：获得固件库版本
 形参：0
 返回：固件库版本
 详解：
************************************************************************************************/
uint16_t GetFWVersion(void)
{
	return(FW_VERSION);
}
