/**
  ******************************************************************************
  * @file    delay.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.25
  * @brief   超核K60固件库 延时 函数库 头文件
  ******************************************************************************
  */
#ifndef __DELAY_H__
#define __DELAY_H__

#ifdef __cplusplus
	 extern "C" {
#endif


#include "sys.h"

//本构件实现的接口函数列表
void DelayInit(void); //延时初始化
void DelayUs(uint32_t us);      //延时us
void DelayMs(uint32_t ms);      //延时ms
		 
#ifdef __cplusplus
}
#endif
		 
#endif
