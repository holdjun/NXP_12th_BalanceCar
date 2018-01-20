
#ifndef _OLED_H_
#define _OLED_H_

#include "stdint.h"
#include "MK60DZ10.h"
//#include "extern.h"
//#include "data.h"

/******************** Device Config ********************/

/* OLED端口宏定义 */
#define OLED_PORT  PTE
#define OLED_SCL   28     //D0
#define OLED_SDA   27     //D1
#define OLED_RST   26     //RST
#define OLED_DC    25     //DC

#define Font   1//1是大字体 0是小字体 小字体比较省空间


/* OLED分辨率宏定义 */
#define  X_WIDTH  128
#define  Y_WIDTH  64



/* OLED IO输出宏替换 */
#define OLED_D0_OL		OLED_PORT->PCOR |= (1<<OLED_SCL)//D0 IO口输出低电平
#define OLED_D0_OH		OLED_PORT->PSOR |= (1<<OLED_SCL)//D0 IO口输出高电平

#define OLED_D1_OL		OLED_PORT->PCOR |= (1<<OLED_SDA)	//D1 IO口输出低电平
#define OLED_D1_OH		OLED_PORT->PSOR |= (1<<OLED_SDA)	//D1 IO口输出高电平

#define OLED_RST_OL		OLED_PORT->PCOR |= (1<<OLED_RST)	//RST IO口输出低电平
#define OLED_RST_OH		OLED_PORT->PSOR |= (1<<OLED_RST)	//RST IO口输出高电平

#define OLED_DC_OL		OLED_PORT->PCOR |= (1<<OLED_DC)	//DC IO口输出低电平
#define OLED_DC_OH		OLED_PORT->PSOR |= (1<<OLED_DC)	//DC IO口输出高电平



/* Function Prototypes */
/*
 *  数据写入
 */
void OLED_WrDat(uint8_t data);

/*
 *  命令写入
 */
void OLED_WrCmd(uint8_t cmd);

/*
 *  坐标设置
 */
void OLED_Set_XY(uint8_t x, uint8_t y);

/*
 *  清屏函数
 */
void OLED_Clear(void);

/*
 *  延时函数
 */
void OLED_Delay_ms(uint16_t ms);

/*
 *  液晶初始化
 */
void OLED_Init(void);        
     

/******************************************************************************
 函数名称 ：OLED_Write_Char
 功能描述 ：字符显示
 参数说明 ：x  SmallChars(小字体) -- (0 - 20)共21列
               LargeChars(大字体) -- (0 - 15)共16列
            y  SmallChars(小字体) -- (0 - 7) 共 8行
               LargeChars(大字体) -- (0 - 6) 共 4行  ** y只能取"0, 2, 4, 6" 4行 **
            c  字体库中任意字符
 函数返回 ：无
 示    例 ：OLED_Write_Char(0, 0, 'A'); -- 在0行0列开始输出 A
*******************************************************************************/
void OLED_Write_Char(uint8_t x, uint8_t y, uint8_t c);


/******************************************************************************
 函数名称 ：OLED_Write_String
 功能描述 ：字符串显示
 参数说明 ：x  SmallChars(小字体) -- (0 - 20)共21列
               LargeChars(大字体) -- (0 - 15)共16列
            y  SmallChars(小字体) -- (0 - 7) 共 8行
               LargeChars(大字体) -- (0 - 6) 共 4行  ** y只能取"0, 2, 4, 6" 4行 **
            *s 字符串
 函数返回 ：无
 示    例 ：OLED_Write_String(0, 2, (uint8_t*)"Hello"); -- 在2行0列开始输出 Hello
*******************************************************************************/   
void OLED_Write_String(uint8_t x, uint8_t y, uint8_t *s);


/******************************************************************************
 函数名称 ：OLED_Write_Num3
 功能描述 ：3位数字显示
 参数说明 ：x   SmallChars(小字体) -- (0 - 20)共21列
                LargeChars(大字体) -- (0 - 15)共16列
            y   SmallChars(小字体) -- (0 - 7) 共 8行
                LargeChars(大字体) -- (0 - 6) 共 4行  ** y只能取"0, 2, 4, 6" 4行 **
            num xxx  3位数字
 函数返回 ：无
 示    例 ：OLED_Write_Num3(0, 0, 199);
*******************************************************************************/
void OLED_Write_Num3(uint8_t x, uint8_t y, uint16_t num);


/******************************************************************************
 函数名称 ：OLED_Write_Char
 功能描述 ：4位数字显示
 参数说明 ：x   SmallChars(小字体) -- (0 - 20)共21列
                LargeChars(大字体) -- (0 - 15)共16列
            y   SmallChars(小字体) -- (0 - 7) 共 8行
                LargeChars(大字体) -- (0 - 6) 共 4行  ** y只能取"0, 2, 4, 6" 4行 **
            num xxxx  4位数字
 函数返回 ：无
 示    例 ：OLED_Write_Num4(0, 0, 1999);
*******************************************************************************/ 
void OLED_Write_Num4(uint8_t x, uint8_t y, int16_t num);

void OLED_Write_Num5(uint8_t x, uint8_t y, uint16_t num);

void OLED_Write_Num2(uint8_t x, uint8_t y, uint8_t num);

void OLED_Write_Value(uint8_t x, uint8_t y, uint16_t num,uint8_t Type);

void OLED_Pin_Init(GPIO_Type *GPIOx,uint8_t GPIO_Pin);

void OLED_Tupian(void);



#endif /* _OLED_H_ */

