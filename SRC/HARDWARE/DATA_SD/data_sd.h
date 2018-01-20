#ifndef __DATA_SD_h_
#define __DATA_SD_h_

#include "sys.h"

#define SD_DATA_LENGTH 1750  //存sd图像数据长度
#define SD_8G_BlocksNum 15000000//16777216//8G内存的扇区数//原先大小太大溢出了
#define SD_4G_BlocksNum 7500000

#define SD_DATA_NUM 80 //存sd参数个数 存的数据为16位 每个数据分成2个8位


void MySD_Init(void);
void Unpack_Data(void);
void SD_datachange16to8(void);
void SD_datachange8to16(void);
void SD_Many_Write(const uint8_t *pbuffer,uint16_t Count,uint8_t BlockNum);
void SD_Write(void);
void SD_ReadData(void);
void data_give(void);
void SD_ManyWT_Init(void);
void SD_ManyWT_ONE(const uint8_t *pbuffer,uint16_t Count);
void MySD_Init1(void);
void Live_Transmission(void);
#endif
