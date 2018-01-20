#include "IMU_IIC.h"
#include "L3G4200D.h"
#include "sys.h"
#include "gpio.h"
#include "mymath.h"



//延时函数
void tly_delay(uint16_t k)		 
{
    uint8_t i;	 

    while(--k)
    {
        for(i=0;i<100;i++); //延时时间长短，0--255可选
    }
}

//读取L3G4200D的1个字节
uint8_t L3G4200D_readbyte(uint8_t address)
{
	uint8_t ret;
	IIC_start();		//启动
	send_byte(SlaveAddress);	//写入设备ID及写信号
	send_byte(address);	//X地址
	IIC_start();		//重新发送开始
	send_byte(SlaveAddress+1);	//写入设备ID及读信
	ret = read_byte();	//读取一字节
	IIC_stop();

	return ret;
}



//写入L3G4200D的1个字节
void L3G4200D_writebyte(uint8_t address, uint8_t thedata)
{
	IIC_start();		//启动
	send_byte(SlaveAddress);	//写入设备ID及写信号
	send_byte(address);	//X地址
	send_byte(thedata);	//写入设备ID及读信
	IIC_stop();
}

/*
 * 函数功能：读L3G4200D角速度输出
 * 参数
 *       Status - 数据寄存器状态
 *       Regs_Addr - 数据寄存器地址
 * 函数返回值：加速度值（int16）
 */   
int16_t L3G4200D_GetResult(uint8_t Status, uint8_t Regs_Addr) 
{
  uint8_t ret=0;
  uint16_t cnt=0;
  int16_t result,temp;
  
  if(Regs_Addr>L3G4200D_OUT_Z_H)//Regs_Addr>L3G4200D_OUT_Z_H
    return 0;
  
  // 等待转换完成并取出值 
  while(!(ret&Status)) 
  {
    ret = L3G4200D_readbyte( L3G4200D_STATUS_REG);
    if(++cnt>500)
      break;
  }
  
  result= L3G4200D_readbyte( Regs_Addr);
  temp  = L3G4200D_readbyte( Regs_Addr-1);
  result=result<<8;
  result=result|temp;
  
  return result>>2;
}

//读取3轴角速度
int16_t Gyro_X, Gyro_Y, Gyro_Z;
void L3G4200D_XYZ()
{
    Gyro_X = -(L3G4200D_GetResult(L3G4200D_STATUS_REG, L3G4200D_OUT_X_H)+5);
    Gyro_Y = L3G4200D_GetResult(L3G4200D_STATUS_REG, L3G4200D_OUT_Y_H);
    Gyro_Z = L3G4200D_GetResult(L3G4200D_STATUS_REG, L3G4200D_OUT_Z_H);
    
    if(Math_Abs(Gyro_X)>55&&Math_Abs(Gyro_X)<69)  {   Gyro_X=0;   }
    if(Math_Abs(Gyro_Y)>55&&Math_Abs(Gyro_Y)<69)  {   Gyro_Y=0;   }
    if(Math_Abs(Gyro_Z)>55&&Math_Abs(Gyro_Z)<69)  {   Gyro_Z=0;   }
}

//*****************************************************************

//初始化L3G4200D，根据需要请参考pdf进行修改************************
void L3G4200D_Init()
{
   while(L3G4200D_readbyte(L3G4200D_WHO_AM_I)!=0xD3);
   tly_delay(10);
   L3G4200D_writebyte(L3G4200D_CTRL_REG1, 0xFF);   
   tly_delay(10);
   L3G4200D_writebyte(L3G4200D_CTRL_REG2, 0x00);   // 
   tly_delay(10);
   L3G4200D_writebyte(L3G4200D_CTRL_REG3, 0x08);   //
   tly_delay(10);
   L3G4200D_writebyte(L3G4200D_CTRL_REG4, 0x30);  //+-2000dps 量程2000度/秒 灵敏度70mdps/digit->X*70/1000=Y度每秒
   tly_delay(10);
   L3G4200D_writebyte(L3G4200D_CTRL_REG5, 0x00);
   tly_delay(10);
}