/**
  ******************************************************************************
  * @file    i2c.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 IIC 头文件
  ******************************************************************************
  */
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "sys.h"

//I2C 初始化结构 
typedef struct
{
	uint32_t I2CxMAP;
  uint32_t I2C_ClockSpeed;        
}I2C_InitTypeDef;
//参数检查器														
#define IS_I2C_ALL_PERIPH(PERIPH) ((PERIPH) == I2C0 || (PERIPH) == I2C1)

//I2C 速度定义
#define I2C_CLOCK_SPEED_50KHZ                   ( 50*1000)
#define I2C_CLOCK_SPEED_100KHZ                  (100*1000)
#define I2C_CLOCK_SPEED_150KHZ                  (150*1000)
#define I2C_CLOCK_SPEED_200KHZ                  (200*1000)
#define I2C_CLOCK_SPEED_250KHZ                  (250*1000)
#define I2C_CLOCK_SPEED_300KHZ                  (300*1000)
//参数检查器
#define IS_I2C_CLOCK_SPEED(SPEED)  (((SPEED) == I2C_CLOCK_SPEED_50KHZ)  || \
                                    ((SPEED) == I2C_CLOCK_SPEED_100KHZ) || \
                                    ((SPEED) == I2C_CLOCK_SPEED_150KHZ) || \
                                    ((SPEED) == I2C_CLOCK_SPEED_200KHZ) || \
                                    ((SPEED) == I2C_CLOCK_SPEED_250KHZ) || \
                                    ((SPEED) == I2C_CLOCK_SPEED_300KHZ))

//I2C 外设定义
typedef struct
{
    uint32_t I2C_Index:4;
    uint32_t I2C_GPIO_Index:4;
    uint32_t I2C_Alt_Index:4;
    uint32_t I2C_SCL_Pin_Index:6;
		uint32_t I2C_SDA_Pin_Index:6;
	  uint32_t I2C_Reserved:8;
}I2C_MapTypeDef;

//I2C 设备外设引脚定义
#define I2C1_SCL_PE1_SDA_PE0       (0x00001641U)
#define I2C0_SCL_PB0_SDA_PB1       (0x00040210U)
#define I2C0_SCL_PB2_SDA_PB3       (0x000c2210U)
#define I2C1_SCL_PC10_SDA_PC11     (0x002ca221U)
//参数检查
#define IS_I2C_DATA_CHL(CHL)     (((CHL) == I2C1_SCL_PE1_SDA_PE0) || \
                                  ((CHL) == I2C0_SCL_PB0_SDA_PB1) || \
                                  ((CHL) == I2C0_SCL_PB2_SDA_PB3) || \
                                  ((CHL) == I2C1_SCL_PC10_SDA_PC11))

//中断配置
#define I2C_IT_TCF             (uint16_t)(0)
#define I2C_IT_IAAS            (uint16_t)(1)
#define I2C_IT_ARBL            (uint16_t)(2)
#define I2C_IT_SLTF            (uint16_t)(3)
#define I2C_IT_SHTF2           (uint16_t)(4)
//参数检查器
#define IS_I2C_IT(IT) (((IT) == I2C_IT_TCF)     || \
                       ((IT) == I2C_IT_SLTF)    || \
                       ((IT) == I2C_IT_ARBL)    || \
                       ((IT) == I2C_IT_SHTF2)   || \
                       ((IT) == I2C_IT_IAAS))

//DMA命令
#define I2C_DMAReq_TCF             ((uint16_t)0)
#define IS_I2C_DMAREQ(REQ)   ((REQ) == I2C_DMAReq_TCF)

//I2C主机读写方向
#define I2C_MASTER_WRITE   (0)
#define I2C_MASTER_READ    (1)
//参数检查
#define IS_I2C_MASTER_DIRECTION(DIR)    (((DIR) == I2C_MASTER_WRITE) || \
                                        ((DIR) == I2C_MASTER_READ))
              

//本构件实现的接口函数
void I2C_Init(I2C_InitTypeDef* I2C_InitStruct);
void I2C_GenerateSTART(I2C_Type *I2Cx);
void I2C_GenerateRESTART(I2C_Type *I2Cx);
void I2C_GenerateSTOP(I2C_Type *I2Cx);
void I2C_SendData(I2C_Type *I2Cx,uint8_t data8);
void I2C_Send7bitAddress(I2C_Type* I2Cx, uint8_t Address, uint8_t I2C_Direction);
uint8_t I2C_WaitAck(I2C_Type *I2Cx);
void I2C_SetMasterMode(I2C_Type* I2Cx,uint8_t I2C_Direction);
void I2C_GenerateAck(I2C_Type *I2Cx);
void I2C_EnableAck(I2C_Type *I2Cx);
void I2C_ITConfig(I2C_Type* I2Cx, uint16_t I2C_IT, FunctionalState NewState);
ITStatus I2C_GetITStatus(I2C_Type* I2Cx, uint16_t I2C_IT);
void I2C_DMACmd(I2C_Type* I2Cx, uint16_t I2C_DMAReq, FunctionalState NewState);
void I2C_ClearITPendingBit(I2C_Type* I2Cx, uint16_t I2C_IT);

#ifdef __cplusplus
}
#endif


#endif


