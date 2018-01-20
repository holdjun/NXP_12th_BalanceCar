/**
  ******************************************************************************
  * @file    led.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核原子核核心板 BSP构件 LED驱动
  ******************************************************************************
  */
#ifndef __LED_H__
#define __LED_H__

#include "gpio.h"

#ifdef __cplusplus
 extern "C" {
#endif

//LED头文件
//IO 口
#define LED1_PORT PTC
#define LED2_PORT PTC
#define LED3_PORT PTC
#define LED4_PORT PTD
//引脚
#define LED1_PIN  (16)
#define LED2_PIN  (17)
#define LED3_PIN  (18)
#define LED4_PIN  (1)
//位宏
#define LED1      PCout(LED1_PIN) 
#define LED2      PCout(LED2_PIN) 
#define LED3      PCout(LED3_PIN) 
#define LED4      PDout(LED4_PIN) 

//本构件所实现的函数接口列表
void LED_Init(void);

#ifdef __cplusplus
}
#endif

#endif
