/**
  ******************************************************************************
  * @file    key.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核原子核核心板 BSP构件 KEY驱动
  ******************************************************************************
  */

#include "key.h"

//KEY状态机定义
#define _KEY_STATE_0  (0)
#define _KEY_STATE_1  (1)
#define _KEY_STATE_2  (2)
#define _KEY_STATE_3  (3)

/***********************************************************************************************
 功能：按键初始化
 形参：0
 返回：0
 详解：初始化板子上的KEY 调用GPIO构件
************************************************************************************************/
void KEY_Init(void)
{
	//定义GPIO初始化结构
	GPIO_InitTypeDef GPIO_InitStruct1;	
	
	GPIO_InitStruct1.GPIO_Pin = KEY1_PIN;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	if(KEY_STATE_DOWN == 1)
	{
		GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD; //下拉输入
	}
	else
	{
		GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	}
	GPIO_InitStruct1.GPIOx = KEY1_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	
}

/***********************************************************************************************
 功能：获得按键状态
 形参：0
 返回：@arg KEY_STATE_DOWN: 按键被按下
       @arg KEY_STATE_UP  : 按键未被按下
 详解：0
************************************************************************************************/
uint8_t KEY_GetKeyValue(void)
{
	return KEY1;
}

//按键层扫描中间层函数 不开放给用户
static uint8_t SKEY_Driver(void)
{
	static uint8_t key_time;
	static uint8_t key_state;
	uint8_t key_press;
	uint8_t key_return = KEY_NO_KEY;
	//获得状态
	key_press = KEY_GetKeyValue();
	//开始状态机
	switch(key_state)
	{
		case _KEY_STATE_0:            //按键初始状态
			if(key_press == KEY_STATE_DOWN) 
			{
				key_state = _KEY_STATE_1;
			}
		break; 
		case _KEY_STATE_1:            //按键消抖与确认态
			if(key_press == KEY_STATE_DOWN)
			{
				key_time = 0;
				key_state = _KEY_STATE_2;
			}
			else
			{
				key_state = _KEY_STATE_0;
			}
		break;
		case _KEY_STATE_2:
			if(key_press == KEY_STATE_UP)  // 此时按键释放，说明是产生一次短操作，回送S_key 
			{
				key_return = KEY_SINGLE;
				key_state = _KEY_STATE_0;
			}
			else if (++key_time > 100)  //继续按下，计时加10ms（10ms为本函数循环执行间隔） 
			{
				key_return = KEY_LONG;
				key_state = _KEY_STATE_3;
			}
			break;
		case _KEY_STATE_3: // 等待按键释放状态，此状态只返回无按键事件 
			if(key_press == KEY_STATE_UP)           
			{
				key_state = _KEY_STATE_0;  // 转换到等待按键释放状态 
			}
		break;
	}
	return key_return; 
}

/***********************************************************************************************
 功能：获得按键状态
 形参：0
 返回：@arg KEY_NO_KEY  :  无按键
       @arg KEY_SINGLE  :  单击
       @arg KEY_DOUBLE  :  双击
       @arg KEY_LONG    :  长按键
 详解：必须以10MS的频率调用这个函数才能发回正确的值 
************************************************************************************************/
uint8_t KEY_Scan(void)
{
	uint8_t key_return = KEY_NO_KEY;
	uint8_t key_temp = KEY_NO_KEY;
	static uint8_t key_time;
	static uint8_t key_state;
	key_temp = SKEY_Driver();
		switch(key_state)
		{
			case _KEY_STATE_0:
				if(key_temp == KEY_SINGLE)
				{
					key_time = 0;
					key_state = _KEY_STATE_1;
				}
				else
				{
					key_return = key_temp;
				}
			break;
			case _KEY_STATE_1:
				if(key_temp == KEY_SINGLE)// 又一次单击 (间隔肯定<500ms)
				{
					key_return = KEY_DOUBLE;
					key_state = _KEY_STATE_0;
				}
				else
				{
					if(++key_time > 25)
					{
						key_return = KEY_SINGLE;
						key_state = _KEY_STATE_0;
					}
				}
			break;
		}
	return key_return;
}
