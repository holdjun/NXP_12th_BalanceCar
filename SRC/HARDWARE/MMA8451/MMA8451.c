#include "mma8451.h"
#include "IMU_IIC.h"
#include "sys.h"
//此处请添加相关的头文件


void mma_delay(uint16_t k)		 //延时函数
{
    uint8_t i;	 //在函数中，必须先声明变量，然后才能调用
    while(--k)
    {
       for(i=0;i<100;i++); //延时时间长短，0--255可选
    }
}


//读取MMA8451的1个字节
uint8_t MMA8451_readbyte(uint8_t address)
{
	uint8_t ret;
	IIC_start();		//启动
	send_byte(MMA845x_IIC_ADDRESS);	//写入设备ID及写信号
	send_byte(address);	//X地址
	IIC_start();		//重新发送开始
	send_byte(MMA845x_IIC_ADDRESS+1);	//写入设备ID及读信
	ret = read_byte();	//读取一字节
	IIC_stop();
	return ret;
}



//写入MMA8451的1个字节
void MMA8451_writebyte(uint8_t address, uint8_t thedata)
{
	IIC_start();		//启动
	send_byte(MMA845x_IIC_ADDRESS);	//写入设备ID及写信号
	send_byte(address);	//X地址
	send_byte(thedata);	//写入设备ID及读信
	IIC_stop();
}


/*
 * 函数功能：读MAA8451加速度输出
 * 参数
 *       Status - 数据寄存器状态
 *       Regs_Addr - 数据寄存器地址
 * 函数返回值：加速度值（int16）
 */   
int16_t MMA8451_GetResult(uint8_t Status, uint8_t Regs_Addr) 
{
  uint8_t ret=0;
  uint16_t cnt=0;
  int16_t result,temp;
  
  if(Regs_Addr>MMA8451_REG_OUTZ_LSB)
    return 0;
  
  // 等待转换完成并取出值 
  while(!(ret&Status)) 
  {
    ret = MMA8451_readbyte( MMA8451_REG_STATUS);
    if(++cnt>500)
      break;
  }
  
  result= MMA8451_readbyte( Regs_Addr);
  temp  = MMA8451_readbyte( Regs_Addr+1);
  result=result<<8;
  result=result|temp;
  
  return result>>2;
}


//读取3轴加速度
int16_t ACC_X, ACC_Y,ACC_Z,ACC_Z1; 
void MMA8451_XYZ()
{
    ACC_X = MMA8451_GetResult(MMA8451_STATUS_X_READY, MMA8451_REG_OUTX_MSB);
    ACC_Y = MMA8451_GetResult(MMA8451_STATUS_Y_READY, MMA8451_REG_OUTY_MSB);  
    ACC_Z = MMA8451_GetResult(MMA8451_STATUS_X_READY, MMA8451_REG_OUTZ_MSB); 
    
    ACC_Y = ACC_Y>3300 ? 3300 : ACC_Y;
    ACC_Y = ACC_Y<400  ? 400  : ACC_Y;
}


//MMA8451初始化
void MMA8451_Init()
{	

  while(MMA8451_readbyte(MMA8451_REG_WHOAMI)!=0x1a);
	mma_delay(10);
	MMA8451_writebyte(MMA8451_REG_SYSMOD,0x00);	   //默认模式Standby Mode
	mma_delay(10);
	MMA8451_writebyte(MMA8451_REG_CTRL_REG2,0x02); //High Resolution
  mma_delay(10);
	MMA8451_writebyte(MMA8451_REG_CTRL_REG1,0x01); //主动模式,800H
	mma_delay(10);
	MMA8451_writebyte(MMA8451_XYZ_DATA_CFG,0x00); //12位AD X/4096=度
	mma_delay(10);
	MMA8451_writebyte(MMA8451_HP_FILTER_CUTOFF,0x10); //高通滤波
}



  		
  
