/**
  ******************************************************************************
  * @file    uart.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.25
  * @brief   超核K60固件库 UART 串口 驱动库 头文件
  ******************************************************************************
  */
#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "sys.h"
	 
//串口初始化位图映射结构
typedef struct
{
    uint32_t UART_Index:3;
    uint32_t UART_Alt_Index:3;
    uint32_t UART_GPIO_Index:3;
    uint32_t UART_TX_Pin_Index:5;
    uint32_t UART_RX_Pin_Index:5;
    uint32_t UART_CTS_Pin_Index:5;
    uint32_t UART_RTS_Pin_Index:5;
}UART_MapTypeDef;


//可使用的UART初始化结构
//例如: UART0_RX_PA1_TX_PA2: UART0 PA1引脚作为TX  PA2引脚作为RX
#define UART0_RX_PA1_TX_PA2    (0x00004410U)
#define UART0_RX_PA14_TX_PA15  (0x00039E18U)
#define UART0_RX_PB16_TX_PB17  (0x00042258U)
#define UART0_RX_PD6_TX_PD7    (0x00018ED8U)
#define UART1_RX_PE0_TX_PE1    (0x00000319U)
#define UART1_RX_C3_TX_C4      (0x0000C899U)
#define UART2_RX_D2_TX_D3      (0x000086DAU)
#define UART3_RX_B10_TX_B11    (0x0002965BU)
#define UART3_RX_C16_TX_C17    (0x0004229BU)
#define UART3_RX_E4_TX_E5      (0x00010B1BU)
#define UART4_RX_E24_TX_E25    (0x0006331CU)
#define UART4_RX_C14_TX_C15    (0x00039E9CU)
#define UART5_RX_E9_TX_E8      (0x0002511DU)

//参数检查器
#define IS_UART_MAP(MAP)        (((MAP) == UART0_RX_PA1_TX_PA2)   || \
																((MAP) == UART0_RX_PA14_TX_PA15)  || \
																((MAP) == UART0_RX_PB16_TX_PB17)  || \
																((MAP) == UART0_RX_PD6_TX_PD7)    || \
																((MAP) == UART1_RX_PE0_TX_PE1)    || \
																((MAP) == UART1_RX_C3_TX_C4)      || \
																((MAP) == UART2_RX_D2_TX_D3)      || \
																((MAP) == UART3_RX_B10_TX_B11)    || \
																((MAP) == UART3_RX_C16_TX_C17)    || \
																((MAP) == UART3_RX_E4_TX_E5)      || \
																((MAP) == UART4_RX_E24_TX_E25)    || \
																((MAP) == UART5_RX_E9_TX_E8)      || \
																((MAP) == UART4_RX_C14_TX_C15))
//参数检查器														
#define IS_UART_ALL_PERIPH(PERIPH) (((PERIPH) == UART0) || \
                                    ((PERIPH) == UART1) || \
                                    ((PERIPH) == UART2) || \
                                    ((PERIPH) == UART3) || \
																		((PERIPH) == UART5) || \
                                    ((PERIPH) == UART4))												
																
//串口初始化结构
typedef struct
{
  uint32_t UART_BaudRate;      //波特率
	uint32_t UARTxMAP;           //初始化结构
} UART_InitTypeDef;


#define IS_UART_ALL_PERIPH(PERIPH) (((PERIPH) == UART0) || \
                                    ((PERIPH) == UART1) || \
                                    ((PERIPH) == UART2) || \
                                    ((PERIPH) == UART3) || \
																		((PERIPH) == UART5) || \
                                    ((PERIPH) == UART4))												
																
//中断定义
#define UART_IT_TDRE        (uint16_t)(0)
#define UART_IT_TC          (uint16_t)(1)
#define UART_IT_RDRF        (uint16_t)(2)
#define UART_IT_IDLE        (uint16_t)(3)
#define IS_UART_IT(IT) (((IT) == UART_IT_TDRE)   || \
                        ((IT) == UART_IT_TC)     || \
                        ((IT) == UART_IT_RDRF)   || \
                        ((IT) == UART_IT_IDLE))

//DMA命令
#define UART_DMAReq_Tx                      ((uint16_t)0)
#define UART_DMAReq_Rx                      ((uint16_t)1)
#define UART_DMAREQ(REQ)  (((REQ) == UART_DMAReq_Tx) || ((REQ) == UART_DMAReq_Rx))

//缓冲区最大值
#define MAX_TX_BUF_SIZE     128

typedef struct
{
	uint8_t TxBuf[MAX_TX_BUF_SIZE];
	uint8_t Length;
	uint8_t Offset;
	uint8_t IsComplete;
	uint16_t MaxBufferSize;
}UART_TxSendTypeDef;
//串口中断发送结构
extern UART_TxSendTypeDef UART_TxIntStruct1;

//本构件实现的接口函数列表
void UART_SendData(UART_Type* UARTx,uint8_t Data);
uint8_t UART_ReceiveData(UART_Type *UARTx,uint8_t *ch);
void UART_SendDataInt(UART_Type* UARTx,uint8_t* DataBuf,uint8_t Len);
void UART_Init(UART_InitTypeDef* UART_InitStruct);
void DisplayCPUInfo(void);
void UART_SendDataIntProcess(UART_Type* UARTx);
void UART_DMACmd(UART_Type* UARTx, uint16_t UART_DMAReq, FunctionalState NewState);
void UART_DebugPortInit(uint32_t UARTxMAP,uint32_t UART_BaudRate);
void UART_ITConfig(UART_Type* UARTx, uint16_t UART_IT, FunctionalState NewState);
ITStatus UART_GetITStatus(UART_Type* UARTx, uint16_t UART_IT);
void UART_printf(char *fmt, ...);  
#ifdef __cplusplus
}
#endif

#endif
