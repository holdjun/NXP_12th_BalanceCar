/**
  ******************************************************************************
  * @file    key.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核原子核核心板 BSP构件 KEY驱动
  ******************************************************************************
  */
#ifndef _KEY_H_
#define _KEY_H_

#include "gpio.h"

#ifdef __cplusplus
 extern "C" {
#endif

//LED头文件
//IO 口
#define KEY1_PORT  PTB
//引脚
#define KEY1_PIN  (9)
//位宏
#define KEY1      PBin(KEY1_PIN)
//按键电平值定义
#define KEY_STATE_DOWN  (1)  //按下时是高电平
#define KEY_STATE_UP    (!KEY_STATE_DOWN)

//KEY返回值 定义 
#define KEY_NO_KEY   (uint8_t)(0)           //无键 
#define KEY_SINGLE   (uint8_t)(1)           //单键 
#define KEY_DOUBLE   (uint8_t)(2)           //双键 
#define KEY_LONG     (uint8_t)(3)           //长键 

//本构件所实现的接口函数	 
void KEY_Init(void);
uint8_t KEY_GetKeyValue(void);
uint8_t KEY_Scan(void);

#ifdef __cplusplus
}
#endif

#endif
