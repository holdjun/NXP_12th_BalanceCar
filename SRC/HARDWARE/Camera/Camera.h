#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "gpio.h"

#define HIsr_Port PTD
#define HIsr_Pin 8
#define HIsr PORTD_IRQHandler
#define HIsr_NVIC PORTD_IRQn

#define VIsr_Port PTA
#define VIsr_Pin 5
#define VIsr PORTA_IRQHandler
#define VIsr_NVIC PORTA_IRQn

#define Camera_AD_Port PTB
#define Camera_AD_Pin_0	0
#define Camera_AD_Pin_1	1
#define Camera_AD_Pin_2	2
#define Camera_AD_Pin_3	3
#define Camera_AD_Pin_4	4
#define Camera_AD_Pin_5	5
#define Camera_AD_Pin_6	6
#define Camera_AD_Pin_7	7

#define Pixels_W  200
#define Pixels_H  70

//½Ó¿Úº¯Êý
void Camera_Init(void);
void Camera_OLED(uint8_t (*P)[128]);
void Camera_DMA_Init(void);
#endif
