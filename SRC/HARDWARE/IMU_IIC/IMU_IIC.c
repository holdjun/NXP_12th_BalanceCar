#include "IMU_IIC.h"
#include "sys.h"
#include "gpio.h"
//此处请添加相关的头文件






 
//SA0必须接地

//内部数据定义
uint8_t IIC_ad_main; //器件从地址	    
uint8_t IIC_ad_sub;  //器件子地址	   
uint8_t *IIC_buf;    //发送|接收数据缓冲区	    
uint8_t IIC_num;     //发送|接收数据个数	     

#define ack 1      //主应答
#define no_ack 0   //从应答	 


void nops()		 
{
    uint8_t k=11;	 
    while(--k);
}

void IMU_IIC_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct1;
	GPIO_InitStruct1.GPIO_Pin = IIC_SCL_PIN;                 
	GPIO_InitStruct1.GPIO_InitState = Bit_SET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = IIC_SCL_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = IIC_SDA_PIN;                 
	GPIO_InitStruct1.GPIO_InitState = Bit_SET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = IIC_SDA_PORT;
	GPIO_Init(&GPIO_InitStruct1);
}
void IIC_start(void)
{
	SCL=0;	//时钟线低
	SDA_OUT = 1;//数据线低
	nops();
	SCL = 1;//时钟线高
	nops();	
	SDA_OUT = 0;//数据线从高跳变到低
	nops();	
	SCL = 0;//时钟线低
}
//************************************************
//送停止位 SDA=0->1
void IIC_stop(void)
{
	SCL = 0;//时钟线低
	SDA_OUT = 0;//数据线低
	nops();
	SCL = 1;//时钟线高
	nops();	
	SDA_OUT = 1;//数据线正跳变
	nops();
	SCL = 0;//时钟线低
}
//************************************************
//主应答(包含ack:SDA=0和no_ack:SDA=0)
void IIC_ack_main(uint8_t ack_main)
{
	SCL = 0;	
	if(ack_main)
	{
	  SDA_OUT = 0; //ack主应答
	}
	else 
	{
	  SDA_OUT = 1; //no_ack无需应答
	}
	nops();	
	SCL = 1;
	nops();	
	SCL = 0;
}
//*************************************************
//字节发送程序
//发送c(可以是数据也可是地址)，送完后接收从应答
//不考虑从应答位
void send_byte(uint8_t c)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		SCL = 0;
		nops();
		if((c<<i) & 0x80)
		{
		  SDA_OUT = 1; //判断发送位
		}
		else 
		{
		  SDA_OUT = 0;
		}
		nops();
		SCL = 1;
		nops();	
		SCL = 0;
	}
	nops();//第九个脉冲
	SDA_OUT = 1; //发送完8bit，释放总线准备接收应答位
	nops();
	SCL = 1;	
	nops();//sda上数据即是从应答位              
	SCL = 0; //不考虑从应答位|但要控制好时序
}
//**************************************************
//字节接收程序
//接收器件传来的数据，此程序应配合|主应答函数|IIC_ack_main()使用
//return: uchar型1字节
uint8_t read_byte(void)
{
	uint8_t i;
	uint8_t c;
	c=0;
	SCL = 0;
	nops();
	SDA_OUT = 1; //置数据线为输入方式
	nops();
	//	//配置为输入
	IIC_SDA_PORT ->PDDR &= ~(1<<IIC_SDA_PIN);	//输入
	//开启上拉电阻
	IIC_SDA_PORTx->PCR[IIC_SDA_PIN]|= PORT_PCR_PE_MASK; 	//上下拉电阻使能
	IIC_SDA_PORTx->PCR[IIC_SDA_PIN]|= PORT_PCR_PS_MASK;
	for(i=0;i<8;i++)
	{
		nops();
		SCL = 0; //置时钟线为低，准备接收数据位
		nops();
		SCL = 1; //置时钟线为高，使数据线上数据有效
		nops();
		c<<=1;
		if(SDA_IN == 1)
		  c+=1; //读数据位，将接收的数据存c
	}
	SCL = 0;	
	nops();
	//重新配置为输出
	IIC_SDA_PORT ->PDDR |= (1<<IIC_SDA_PIN);//输出
	IIC_SDA_PORTx->PCR[IIC_SDA_PIN]&=~(PORT_PCR_PE_MASK); 
	IIC_SDA_PORT ->PDOR |= (1<<IIC_SDA_PIN);
	IIC_SDA_PORTx->PCR[IIC_SDA_PIN]&= ~PORT_PCR_ODE_MASK;
	return c;
}

/*******************************


							以下没用到

**************************************/






//***************************************************
//向无子地址器件发送单字节数据
void send_to_byte(uint8_t ad_main,uint8_t c)
{
	IIC_start();
	send_byte(ad_main); //发送器件地址
	send_byte(c); //发送数据c
	IIC_stop();
}
//***************************************************
//向有子地址器件发送多字节数据
void send_to_nbyte(uint8_t ad_main,uint8_t ad_sub,uint8_t *buf,uint8_t num)
{
	uint8_t i;
	IIC_start();
	send_byte(ad_main); //发送器件地址
	send_byte(ad_sub); //发送器件子地址
	for(i=0;i<num;i++)
	{
		send_byte(*buf); //发送数据*buf
		buf++;
	}
	IIC_stop();
}
//***************************************************
//从无子地址器件读单字节数据
//function:器件地址，所读数据存在接收缓冲区当前字节
void read_from_byte(uint8_t ad_main,uint8_t *buf)
{
	IIC_start();
	send_byte(ad_main); //发送器件地址
	*buf=read_byte();
	IIC_ack_main(no_ack); //无需应答<no_ack=0>
	IIC_stop();
}
//***************************************************
//从有子地址器件读多个字节数据
//function:
void read_from_nbyte(uint8_t ad_main,uint8_t ad_sub,uint8_t *buf,uint8_t num)
{
	uint8_t i;
	IIC_start();
	send_byte(ad_main);
	send_byte(ad_sub);
	for(i=0;i<num-1;i++)
	{
		*buf=read_byte();
		IIC_ack_main(ack); //主应答<ack=1>
		buf++;
	}
	*buf=read_byte();
	buf++; //本次指针调整无意义，目的是操作后buf指向下一地址
	IIC_ack_main(no_ack); //无需应答<no_ack=0>
	IIC_stop();
}