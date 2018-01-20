/**
  ******************************************************************************
  * @file    sys.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 系统级API函数头文件
  ******************************************************************************
  */
	 
#ifndef __SYS_H__
#define __SYS_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "MK60DZ10.h"
//配置宏
#define USE_FULL_ASSERT                          //是否启动参数检测机制，如果启用需要用户实现 assert_failed函数
#define DEBUG_PRINT                              //是否用串口打印调试信息
//#define SYSTEM_SUPPORT_OS				               //支持uCOS操作系统

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))
typedef enum{FALSE = 0, TRUE = !FALSE} ErrorState;

#ifndef NULL
	#define NULL 0
#endif

//版本
#define  FW_VERSION                 (240)                //CH_K60固件库版本
//参数检测器
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */




//处理器信息及主频信息结构
typedef struct
{
	uint8_t FamilyType;    //Kinetis系列家族类型号 
	uint8_t ResetState;    //复位原因
	uint8_t SiliconRev;    //SiliconRev
	uint16_t PinCnt;       //引脚数量
	uint32_t PFlashSize;   //PFlash大小
	uint32_t FlexNVMSize;  //FlexNVM大小
	uint32_t RAMSize;      //RAM大小
	uint32_t CoreClock;    //内核时钟
	uint32_t BusClock;     //总线时钟
	uint32_t FlexBusClock; //FlexBus时钟
	uint32_t FlashClock;   //Flash时钟
} CPUInfoType_t;
extern CPUInfoType_t CPUInfo;

//MCG时钟源选择
#define ClockSource_IRC     ((uint8_t)0x0)
#define ClockSource_EX50M  	((uint8_t)0x5)
#define ClockSource_EX8M			((uint8_t)0x6)
//参数检测器宏
#define IS_CLOCK_OPTION(SOURCE)			 (((SOURCE)  == ClockSource_IRC)  ||  \
                                       ((SOURCE) == ClockSource_EX50M) || \
                                       ((SOURCE) == ClockSource_EX8M))
//MCG时钟输出选择
#define CoreClock_200M      ((uint8_t)0x13) //最高100M频率 200M属于为小车设计的超频
#define CoreClock_100M			((uint8_t)0x12)
#define CoreClock_96M				((uint8_t)0x11)
#define CoreClock_72M				((uint8_t)0x10)
#define CoreClock_64M				((uint8_t)0x9)
#define CoreClock_48M				((uint8_t)0x8)
//参数检测宏
#define IS_CLOCK_SELECT(CLOCK_TYPE)   (((CLOCK_TYPE) ==    CoreClock_100M)||   \
																			 ((CLOCK_TYPE) ==    CoreClock_200M)||   \
																			 ((CLOCK_TYPE) ==    CoreClock_96M) ||   \
																			 ((CLOCK_TYPE) ==    CoreClock_72M) ||   \
																			 ((CLOCK_TYPE) ==    CoreClock_64M) ||   \
																			 ((CLOCK_TYPE) ==    CoreClock_48M))
//NVIC中断分组选择
#define NVIC_PriorityGroup_0         ((uint32_t)0x7) /*!< 0 bits for pre-emption priority   4 bits for subpriority */                                               
#define NVIC_PriorityGroup_1         ((uint32_t)0x6) /*!< 1 bits for pre-emption priority   3 bits for subpriority */                                                  
#define NVIC_PriorityGroup_2         ((uint32_t)0x5) /*!< 2 bits for pre-emption priority   2 bits for subpriority */                                                   
#define NVIC_PriorityGroup_3         ((uint32_t)0x4) /*!< 3 bits for pre-emption priority   1 bits for subpriority */                                                   
#define NVIC_PriorityGroup_4         ((uint32_t)0x3) /*!< 4 bits for pre-emption priority   0 bits for subpriority */
//参数检测器宏
#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PriorityGroup_0) || \
                                       ((GROUP) == NVIC_PriorityGroup_1) || \
                                       ((GROUP) == NVIC_PriorityGroup_2) || \
                                       ((GROUP) == NVIC_PriorityGroup_3) || \
                                       ((GROUP) == NVIC_PriorityGroup_4))
#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)
#define IS_NVIC_SUB_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

//VETOR_OFFSET检测宏
#define IS_VECTOR_OFFSET(OFFSET)  ((OFFSET) % 4 == 0)

//本构件实现的接口函数列表
void SystemClockSetup(uint8_t ClockOption,uint16_t CoreClock);  //设置系统时钟
void SystemSoftReset(void);                                     //软复位
void GetCPUInfo(void);                                          //获得处理器信息
void EnableInterrupts(void);                                    //时能总中断
void DisableInterrupts(void);                                   //关闭总中断
void SetVectorTable(uint32_t offset);                           //设置中断向量起始位置
void NVIC_EnableIRQ(IRQn_Type IRQn);                            //开启中断                  
void NVIC_DisableIRQ(IRQn_Type IRQn);                           //关闭中断
void NVIC_Init(IRQn_Type IRQn,uint32_t PriorityGroup,uint32_t PreemptPriority,uint32_t SubPriority); //设置中断优先级
uint16_t GetFWVersion(void);

#ifdef __cplusplus
}
#endif

#endif

