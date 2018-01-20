/**
  ******************************************************************************
  * @file    gpio.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.25
  * @brief   超核K60固件库 GPIO API函数 头文件
  ******************************************************************************
  */
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "sys.h"

//位带操作,实现51类似的GPIO控制功能
//IO口操作宏定义
#define BITBAND(addr,bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (PTA_BASE+0) //0x4001080C 
#define GPIOB_ODR_Addr    (PTB_BASE+0) //0x40010C0C 
#define GPIOC_ODR_Addr    (PTC_BASE+0) //0x4001100C 
#define GPIOD_ODR_Addr    (PTD_BASE+0) //0x4001140C 
#define GPIOE_ODR_Addr    (PTE_BASE+0) //0x4001180C 
#define GPIOF_ODR_Addr    (PTF_BASE+0) //0x40011A0C    
#define GPIOG_ODR_Addr    (PTG_BASE+0) //0x40011E0C    

#define GPIOA_IDR_Addr    (PTA_BASE+0x10) //0x40010808 
#define GPIOB_IDR_Addr    (PTB_BASE+0x10) //0x40010C08 
#define GPIOC_IDR_Addr    (PTC_BASE+0x10) //0x40011008 
#define GPIOD_IDR_Addr    (PTD_BASE+0x10) //0x40011408 
#define GPIOE_IDR_Addr    (PTE_BASE+0x10) //0x40011808 
#define GPIOF_IDR_Addr    (PTF_BASE+0x10) //0x40011A08 
#define GPIOG_IDR_Addr    (PTG_BASE+0x10) //0x40011E08 

//IO口操作,只对单一的IO口!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 
  
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入


#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == PTA) || \
                                    ((PERIPH) == PTB) || \
                                    ((PERIPH) == PTC) || \
                                    ((PERIPH) == PTD) || \
                                    ((PERIPH) == PTE))


#define IS_PORT_ALL_PERIPH(PERIPH) (((PERIPH) == PORTA) || \
                                    ((PERIPH) == PORTB) || \
                                    ((PERIPH) == PORTC) || \
                                    ((PERIPH) == PORTD) || \
                                    ((PERIPH) == PORTE))

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;
#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))


//GPIO引脚
#define GPIO_Pin_0             (uint16_t)(0)
#define GPIO_Pin_1             (uint16_t)(1)
#define GPIO_Pin_2             (uint16_t)(2)
#define GPIO_Pin_3             (uint16_t)(3)
#define GPIO_Pin_4             (uint16_t)(4)
#define GPIO_Pin_5             (uint16_t)(5)
#define GPIO_Pin_6             (uint16_t)(6)
#define GPIO_Pin_7             (uint16_t)(7)
#define GPIO_Pin_8             (uint16_t)(8)
#define GPIO_Pin_9             (uint16_t)(9)
#define GPIO_Pin_10            (uint16_t)(10)
#define GPIO_Pin_11            (uint16_t)(11)
#define GPIO_Pin_12            (uint16_t)(12)
#define GPIO_Pin_13            (uint16_t)(13)
#define GPIO_Pin_14            (uint16_t)(14)
#define GPIO_Pin_15            (uint16_t)(15)
#define GPIO_Pin_16            (uint16_t)(16)
#define GPIO_Pin_17            (uint16_t)(17)
#define GPIO_Pin_18            (uint16_t)(18)
#define GPIO_Pin_19            (uint16_t)(19)
#define GPIO_Pin_20            (uint16_t)(20)
#define GPIO_Pin_21            (uint16_t)(21)
#define GPIO_Pin_22            (uint16_t)(22)
#define GPIO_Pin_23            (uint16_t)(23)
#define GPIO_Pin_24            (uint16_t)(24)
#define GPIO_Pin_25            (uint16_t)(25)
#define GPIO_Pin_26            (uint16_t)(26)
#define GPIO_Pin_27            (uint16_t)(27)
#define GPIO_Pin_28            (uint16_t)(28)
#define GPIO_Pin_29            (uint16_t)(29)
#define GPIO_Pin_30            (uint16_t)(30)
#define GPIO_Pin_31            (uint16_t)(31)
#define IS_GPIO_PIN(PIN)            ((PIN < 32))



typedef enum
{
  GPIO_Mode_IN_FLOATING = 0x04,     //浮空输入
  GPIO_Mode_IPD = 0x05,             //下拉输入
  GPIO_Mode_IPU = 0x06,             //上拉输入
  GPIO_Mode_OOD = 0x07,             //开漏输出
  GPIO_Mode_OPP = 0x08,             //推挽输出
}GPIO_Mode_TypeDef;
#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IN_FLOATING) || \
                            ((MODE) == GPIO_Mode_IPD)         || \
                            ((MODE) == GPIO_Mode_IPU)         || \
                            ((MODE) == GPIO_Mode_OOD)         || \
                            ((MODE) == GPIO_Mode_OPP))
//中断配置
typedef enum
{
  GPIO_IT_DISABLE = 0x00,              //禁止外部中断
	GPIO_IT_DMA_RISING = 0x01,           //DMA上升沿触发
  GPIO_IT_DMA_FALLING = 0x02,          //DMA下降沿触发
	GPIO_IT_DMA_RASING_FALLING = 0x03,   //DMA上升或下降沿触发
	GPIO_IT_LOW = 0x08,                  //逻辑0状态触发
	GPIO_IT_RISING = 0x09,               //上升沿触发
	GPIO_IT_FALLING = 0x0A,              //下降沿触发
	GPIO_IT_RISING_FALLING = 0x0B,       //上升或下降沿触发
	GPIO_IT_HIGH = 0x0C,                 //逻辑1触发
}GPIO_IT_TypeDef;

#define IS_GPIO_IRQC(TRIGGER)    (((TRIGGER) == GPIO_IT_DISABLE)            || \
                                  ((TRIGGER) == GPIO_IT_DMA_RISING)         || \
																	((TRIGGER) == GPIO_IT_DMA_FALLING)        || \
                                  ((TRIGGER) == GPIO_IT_DMA_RASING_FALLING) || \
																	((TRIGGER) == GPIO_IT_LOW)                || \
                                  ((TRIGGER) == GPIO_IT_RISING)             || \
																	((TRIGGER) == GPIO_IT_FALLING)            || \
                                  ((TRIGGER) == GPIO_IT_RISING_FALLING)     || \
																	((TRIGGER) == GPIO_IT_HIGH))

typedef struct
{
  uint16_t GPIO_Pin;                //引脚
	BitAction GPIO_InitState;         //初始状态
	GPIO_IT_TypeDef GPIO_IRQMode;     //GPIO中断状态配置
  GPIO_Mode_TypeDef GPIO_Mode;      //GPIO模式配置
	GPIO_Type *GPIOx;                 //GPIO端口号
}GPIO_InitTypeDef;

//本构件实现的接口函数列表
void GPIO_Init(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_WriteBit(GPIO_Type *GPIOx,uint16_t GPIO_Pin,BitAction BitVal);
void GPIO_SetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
void GPIO_ToggleBit(GPIO_Type *GPIOx,uint16_t GPIO_Pin);
void GPIO_Write(GPIO_Type *GPIOx,uint32_t PortVal);
uint8_t GPIO_ReadOutputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
uint32_t GPIO_ReadOutputData(GPIO_Type* GPIOx);
uint8_t GPIO_ReadInputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
uint32_t GPIO_ReadInputData(GPIO_Type *GPIOx);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
ITStatus GPIO_GetITStates(GPIO_Type *GPIOx,uint16_t GPIO_Pin);
void GPIO_ClearITPendingBit(GPIO_Type *GPIOx,uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif
