/**
  ******************************************************************************
  * @file    spi.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 SPI模块驱动
  ******************************************************************************
  */
#ifndef __SPI_H_
#define	__SPI_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "sys.h"

typedef struct
{
	uint32_t SPIxDataMap;               //数据端口定义
	uint32_t SPIxPCSMap;                //片选端口定义
	uint8_t SPI_DataSize;               //数据位定义
	uint8_t SPI_CPOL;                   //SCK 极性定义
	uint8_t SPI_Mode;                   //主从模式定义
	uint8_t SPI_CPHA;                   //时钟相位定义
  uint16_t SPI_BaudRatePrescaler;     //波特率分频数
	uint16_t SPI_FirstBit;              //MSB 还是 LSB
}SPI_InitTypeDef;

//FTM_PWM映射
typedef struct
{
    uint32_t SPI_Index:2;
	  uint32_t SPI_Alt_Index:3;
    uint32_t SPI_GPIO_Index:3;
    uint32_t SPI_SCK_Pin_Index:6;
		uint32_t SPI_SOUT_Pin_Index:6;
	  uint32_t SPI_SIN_Pin_Index:6;
}SPI_DataMapTypeDef;
//SPI数据端口位图定义
#define SPI0_SCK_PA15_SOUT_PA16_SIN_PA17   (0x01140f08U)
#define SPI0_SCK_PC5_SOUT_PC6_SIN_PC7      (0x00718548U)
#define SPI0_SCK_PD1_SOUT_PD2_SIN_PD3      (0x00308168U)
#define SPI1_SCK_PE2_SOUT_PE1_SIN_PE3      (0x00304289U)
#define SPI1_SCK_PB11_SOUT_PB16_SIN_PB17   (0x01140b29U)
#define SPI2_SCK_PB21_SOUT_PB22_SIN_PB23   (0x0175952aU)
#define IS_SPI_DATA_CHL(CH)      (((CH) == SPI0_SCK_PA15_SOUT_PA16_SIN_PA17)         || \
                                  ((CH) == SPI0_SCK_PC5_SOUT_PC6_SIN_PC7)            || \
																	((CH) == SPI0_SCK_PD1_SOUT_PD2_SIN_PD3)            || \
                                  ((CH) == SPI1_SCK_PE2_SOUT_PE1_SIN_PE3)            || \
																	((CH) == SPI1_SCK_PB11_SOUT_PB16_SIN_PB17)         || \
																	((CH) == SPI2_SCK_PB21_SOUT_PB22_SIN_PB23))		

//SPI 片选映射
typedef struct
{
    uint32_t SPI_Index:2;
	  uint32_t SPI_Alt_Index:3;
    uint32_t SPI_GPIO_Index:3;
    uint32_t SPI_PCS_Pin_Index:6;
    uint32_t SPI_PCS_CH_Index:6;
}SPI_CSMapTypeDef;
//SPI片选信号定义
#define SPI0_PCS0_PA14   (0x00000e08U)
#define SPI0_PCS1_PC3    (0x00000348U)
#define SPI0_PCS2_PC2    (0x00000248U)
#define SPI0_PCS3_PC1    (0x00000148U)
#define SPI0_PCS4_PC0    (0x00000048U)
#define SPI1_PCS0_PB10   (0x00000a29U)
#define SPI1_PCS1_PB9    (0x00000929U)
#define SPI1_PCS2_PE5    (0x00000589U)
#define SPI1_PCS3_PE6    (0x00000689U)
#define SPI2_PCS0_PB20   (0x0000142aU)
#define IS_SPI_PCS_CHL(CH)       (((CH) == SPI0_PCS0_PA14)        || \
                                  ((CH) == SPI0_PCS1_PC3)         || \
																	((CH) == SPI0_PCS2_PC2)         || \
                                  ((CH) == SPI0_PCS3_PC1)         || \
																	((CH) == SPI0_PCS4_PC0)         || \
                                  ((CH) == SPI1_PCS0_PB10)        || \
																	((CH) == SPI1_PCS1_PB9)         || \
                                  ((CH) == SPI1_PCS2_PE5)        || \
																	((CH) == SPI1_PCS3_PE6)        || \
																	((CH) == SPI2_PCS0_PB20))		


//SPI 分频选择
#define SPI_BaudRatePrescaler_2         ((uint16_t)0x0000)
#define SPI_BaudRatePrescaler_4         ((uint16_t)0x0001)
#define SPI_BaudRatePrescaler_6         ((uint16_t)0x0002)
#define SPI_BaudRatePrescaler_8         ((uint16_t)0x0003)
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0004)
#define SPI_BaudRatePrescaler_32        ((uint16_t)0x0005)
#define SPI_BaudRatePrescaler_64        ((uint16_t)0x0006)
#define SPI_BaudRatePrescaler_128       ((uint16_t)0x0007)
#define SPI_BaudRatePrescaler_256       ((uint16_t)0x0008)
#define SPI_BaudRatePrescaler_512       ((uint16_t)0x0009)
#define SPI_BaudRatePrescaler_1024      ((uint16_t)0x000A)
#define SPI_BaudRatePrescaler_2048      ((uint16_t)0x000B)

#define IS_SPI_BAUDRATE(VALUE)    (((VALUE) == SPI_BaudRatePrescaler_2)        || \
                                  ((VALUE) == SPI_BaudRatePrescaler_4)         || \
																	((VALUE) == SPI_BaudRatePrescaler_6)         || \
                                  ((VALUE) == SPI_BaudRatePrescaler_8)         || \
																	((VALUE) == SPI_BaudRatePrescaler_16)        || \
                                  ((VALUE) == SPI_BaudRatePrescaler_32)        || \
																	((VALUE) == SPI_BaudRatePrescaler_64)        || \
                                  ((VALUE) == SPI_BaudRatePrescaler_128)       || \
																	((VALUE) == SPI_BaudRatePrescaler_256)       || \
                                  ((VALUE) == SPI_BaudRatePrescaler_512)       || \
																	((VALUE) == SPI_BaudRatePrescaler_1024)      || \
																	((VALUE) == SPI_BaudRatePrescaler_2048))		

//主从模式
#define SPI_Mode_Master                 ((uint16_t)0x0001)
#define SPI_Mode_Slave                  ((uint16_t)0x0002)
#define IS_SPI_MODE(MODE)  (((MODE) == SPI_Mode_Master) || ((MODE) == SPI_Mode_Slave))
//CPHA极性
#define SPI_CPHA_1Edge                  ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                  ((uint16_t)0x0001)
#define IS_SPI_CPHA(MODE)  (((MODE) == SPI_CPHA_1Edge) || ((MODE) == SPI_CPHA_2Edge))
//CPOL极性
#define SPI_CPOL_Low                    ((uint16_t)0x0000)
#define SPI_CPOL_High                   ((uint16_t)0x0002)
#define IS_SPI_CPOL(MODE)  (((MODE) == SPI_CPOL_Low) || ((MODE) == SPI_CPOL_High))
//发送后 片选是否拉高
#define SPI_PCS_Asserted                ((uint16_t)0x0000)
#define SPI_PCS_Inactive                ((uint16_t)0x0001)
#define IS_SPI_PCS_STATE(MODE)  (((MODE) == SPI_PCS_Asserted) || ((MODE) == SPI_PCS_Inactive))
//MSB还是LSB
#define SPI_FirstBit_MSB                ((uint16_t)0x0000)
#define SPI_FirstBit_LSB                ((uint16_t)0x0001)
#define IS_SPI_FIRSTBIT(MODE)  (((MODE) == SPI_FirstBit_MSB) || ((MODE) == SPI_FirstBit_LSB))

//中断定义
#define SPI_IT_EOQF        (uint16_t)(0)
#define SPI_IT_TFFF        (uint16_t)(1)
#define SPI_IT_TCF         (uint16_t)(2)
#define SPI_IT_TFUF        (uint16_t)(3)
#define SPI_IT_RFDF        (uint16_t)(4)
#define SPI_IT_RFOF        (uint16_t)(5)
#define IS_SPI_IT(IT)  (((IT) == SPI_IT_EOQF)  || \
                        ((IT) == SPI_IT_TFFF)  || \
                        ((IT) == SPI_IT_TCF)   || \
                        ((IT) == SPI_IT_RFDF)  || \
                        ((IT) == SPI_IT_RFDF)  || \
                        ((IT) == SPI_IT_RFOF))
//SPI模块宏定义 
#define IS_SPI_ALL_PERIPH(PERIPH)  (((PERIPH) == SPI0) || \
                                    ((PERIPH) == SPI1) || \
                                    ((PERIPH) == SPI2))


//DMA命令
#define SPI_DMAReq_TFFF                      ((uint16_t)0)
#define SPI_DMAReq_RFDF                      ((uint16_t)1)
#define SPI_DMAREQ(REQ)  (((REQ) == SPI_DMAReq_TFFF) || ((REQ) == SPI_DMAReq_RFDF))

//本构件实现的接口函数列表
void SPI_Init(SPI_InitTypeDef* SPI_InitStruct);
uint16_t SPI_ReadWriteByte(uint32_t SPICSMap,uint16_t Data,uint16_t PCS_State);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);

#ifdef __cplusplus
}
#endif

#endif
