/**
  ******************************************************************************
  * @file    wdog.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 看门狗 驱动头文件
  ******************************************************************************
  */
#ifndef __WDOG_H__
#define __WDOG_H__

#ifdef __cplusplus
	 extern "C" {
#endif

#include "sys.h"

//看门狗驱动头文件
void WDOG_Init(uint16_t FeedInterval);
void WDOG_Open(void);
void WDOG_Close(void);
void WDOG_Feed(void);
		 
#ifdef __cplusplus
}
#endif
 
#endif
