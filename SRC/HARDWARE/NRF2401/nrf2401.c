/**
  ******************************************************************************
  * @file    nrf2401.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核原子核核心板 BSP构件 NRF2401驱动
  ******************************************************************************
  */
#include "NRF2401.H"
/***********************************************************************************************
 功能：NRF24L01 读写一个字节
 形参：发送的数据
 返回：读到的数据
 详解：调用SPI模块
************************************************************************************************/
static uint8_t NRF2401_ReadWriteByte(uint8_t dat)
{
	uint8_t RecByte = 0;
	RecByte = SPI_ReadWriteByte(SPI0_PCS0_PA14,dat,SPI_PCS_Inactive);
	return(RecByte);           		  // return read byte
}
/***********************************************************************************************
 功能：NRF24L01 写寄存器
 形参：reg: 寄存器
       value:写入的值
 返回：读到的数据
 详解：无
************************************************************************************************/
static uint8_t NRF2401_ReadWriteReg(uint8_t reg,uint8_t value)
{
	uint8_t status;
	NRF2401_CSN = 0;                   // CSN low, init SPI transaction
	status = NRF2401_ReadWriteByte(reg);      // select register
	NRF2401_ReadWriteByte(value);             // ..and write value to it..
	NRF2401_CSN = 1;                   // CSN high again
	return(status);            // return nRF24L01 status byte
}
/***********************************************************************************************
 功能：NRF24L01 写寄存器
 形参：reg: 寄存器
       value:写入的值
 返回：读到的数据
 详解：无
************************************************************************************************/
static uint8_t NRF2401_WriteBuffer(uint8_t reg,uint8_t *pBuf,uint8_t bytes)
{
	uint8_t status,i;
	NRF2401_CSN = 0; 
	status = NRF2401_ReadWriteByte(reg);    // Select register to write to and read status byte
	for(i=0; i<bytes; i++) // then write all byte in buffer(*pBuf)
	{
		NRF2401_ReadWriteByte(*pBuf++);
	}
	NRF2401_CSN = 1;                 // Set CSN high again
	return(status);          // return nRF24L01 status byte
}
/***********************************************************************************************
 功能：NRF24L01 读Buffer
 形参：reg: 寄存器
       pBuf:数据指针
		 	 bytes: 写入的字节数
 返回：读状态
 详解：无
************************************************************************************************/
static uint8_t NRF2401_ReadBuffer(uint8_t reg,uint8_t *pBuf,uint8_t bytes)
{
	uint8_t status,i;
	NRF2401_CSN = 0;                    		// Set CSN low, init SPI tranaction
	status = NRF2401_ReadWriteByte(reg);       		// Select register to write to and read status byte
	for(i=0;i<bytes;i++)
	{
		pBuf[i] = NRF2401_ReadWriteByte(0);    // Perform SPI_RW to read byte from nRF24L01
	}
	NRF2401_CSN = 1;                           // Set CSN high again
	return(status);                    // return nRF24L01 status byte
}

/***********************************************************************************************
 功能：检测NRF24L01 是否存在
 形参：
 返回：NRF_OK : 成功   NRF_ERR:失败
 详解：无
************************************************************************************************/
static uint8_t NRF24L01_Check(void)
{
	uint8_t buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uint8_t i;
	NRF2401_WriteBuffer(WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.	
	NRF2401_ReadBuffer(TX_ADDR,buf,5); //读出写入的地址  
	for(i=0;i<5;i++)
	{
		if(buf[i] != 0xA5) return NRF_ERR;
	}
	return NRF_OK;
}	 	

uint8_t NRF2401_Init(void)
{
	SPI_InitTypeDef SPI_InitStruct1;
	GPIO_InitTypeDef GPIO_InitStruct1;
	//CE引脚初始化
	GPIO_InitStruct1.GPIO_Pin = NRF2401_CE_PIN;
	GPIO_InitStruct1.GPIO_InitState = Bit_SET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = NRF2401_CE_PORT;
	GPIO_Init(&GPIO_InitStruct1);

	 //IRQ引脚初始化
	GPIO_InitStruct1.GPIO_Pin = NRF2401_IRQ_PIN;
	GPIO_InitStruct1.GPIO_InitState = Bit_SET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct1.GPIOx = NRF2401_IRQ_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	//初始化SPI串行接口引擎
	SPI_InitStruct1.SPIxDataMap = NRF2401_PORT_DATA;
	SPI_InitStruct1.SPIxPCSMap =  NRF2401_PORT_CS;
	SPI_InitStruct1.SPI_DataSize = 8;
	SPI_InitStruct1.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitStruct1.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct1.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct1.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct1.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(&SPI_InitStruct1);
	//初始化硬件GPIO引擎
	//不适用硬件 CS 使用GPIO做CS
	GPIO_InitStruct1.GPIO_Pin = NRF2401_CSN_PIN;
	GPIO_InitStruct1.GPIO_InitState = Bit_SET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = NRF2401_CSN_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	//IO电平初始化
	NRF2401_CE = 0;			  // chip enable
	NRF2401_CSN = 1;			// Spi disable	
	//检测NRF2401 是否存在
	return NRF24L01_Check();
}

const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //接收地址
//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了		   
void NRF2401_SetRXMode(void)
{
	NRF2401_CE=0;	  
	NRF2401_WriteBuffer(WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
	NRF2401_ReadWriteReg(WRITE_REG+EN_AA,0x01);    //使能通道0的自动应答    
	NRF2401_ReadWriteReg(WRITE_REG+EN_RXADDR,0x01);//使能通道0的接收地址  	 
	NRF2401_ReadWriteReg(WRITE_REG+RF_CH,40);	     //设置RF通信频率		  
	NRF2401_ReadWriteReg(WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 	    
	NRF2401_ReadWriteReg(WRITE_REG+RF_SETUP,0x0f);//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF2401_ReadWriteReg(WRITE_REG+CONFIG, 0x0f);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	NRF2401_CE = 1; //CE为高,进入接收模式 
}			
//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
//PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了		   
//CE为高大于10us,则启动发送.	 
void NRF2401_SetTXMode(void)
{				
	NRF2401_CE=0;	    
	NRF2401_WriteBuffer(WRITE_REG+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址 
	NRF2401_WriteBuffer(WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  
	NRF2401_ReadWriteReg(WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
	NRF2401_ReadWriteReg(WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
	NRF2401_ReadWriteReg(WRITE_REG+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
	NRF2401_ReadWriteReg(WRITE_REG+RF_CH,40);       //设置RF通道为40
	NRF2401_ReadWriteReg(WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF2401_ReadWriteReg(WRITE_REG+CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	NRF2401_CE=1;//CE为高,10us后启动发送
}


//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:发送完成状况
uint8_t NRF2401_SendData(uint8_t *txbuf)
{
	uint8_t sta;
	NRF2401_CE=0;
	NRF2401_WriteBuffer(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
 	NRF2401_CE=1;//启动发送	  
	while(NRF2401_IRQ!=0);//等待发送完成
	sta = NRF2401_ReadWriteReg(STATUS,0xFF);  //读取状态寄存器的值	
	NRF2401_ReadWriteReg(WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	
	if(sta&MAX_TX)//达到最大重发次数
	{
		NRF2401_ReadWriteReg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(sta&TX_OK)//发送完成
	{
		return TX_OK;
	}
	return 0xff;//其他原因发送失败
}

//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
uint8_t NRF2401_RecData(uint8_t *rxbuf)
{
	uint8_t sta;		    							   
	sta=NRF2401_ReadWriteReg(STATUS,0xFF);  //读取状态寄存器的值    	 
	NRF2401_ReadWriteReg(WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&RX_OK)//接收到数据
	{
		NRF2401_ReadBuffer(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
		NRF2401_ReadWriteReg(FLUSH_RX,0xff);//清除RX FIFO寄存器 
		return 0; 
	}	   
	return 1;//没收到任何数据
}			



