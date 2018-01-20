/**
  ******************************************************************************
  * @file    falsh.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.6.23
  * @brief   超核K60固件库 片内flash 驱动文件
  ******************************************************************************
  */
#include "flash.h"
/***********************************************************************************************
 功能：内部函数 检查命令是否完成
 形参：0
 返回：FLASH_OK 成功    FLASH_ERROR 失败 
 详解：
************************************************************************************************/
static uint8_t CommandLaunch(void)
{
    // 清除访问错误标志位和非法访问标志位 
    FTFL->FSTAT |=(FTFL_FSTAT_ACCERR_MASK|FTFL_FSTAT_FPVIOL_MASK|FTFL_FSTAT_RDCOLERR_MASK);
    // 启动命令
    FTFL->FSTAT |= FTFL_FSTAT_CCIF_MASK;
    // 等待命令结束
    while((FTFL->FSTAT &FTFL_FSTAT_CCIF_MASK)==0);
    // 检查错误标志
    if(FTFL->FSTAT & (FTFL_FSTAT_ACCERR_MASK|FTFL_FSTAT_FPVIOL_MASK|FTFL_FSTAT_MGSTAT0_MASK|FTFL_FSTAT_RDCOLERR_MASK))
    return(FLASH_ERROR); //出错
    return (FLASH_OK); //成功
}

/***********************************************************************************************
 功能：初始化片内Flash模块
 形参：0
 返回：0
 详解：0
************************************************************************************************/
void FLASH_Init(void)
{
	//清除FMC缓冲区
	FMC->PFB0CR |= FMC_PFB0CR_S_B_INV_MASK;
	FMC->PFB1CR |= FMC_PFB0CR_S_B_INV_MASK;
	// 禁止看门狗
	WDOG->UNLOCK = 0xC520;
	WDOG->UNLOCK = 0xD928;
	WDOG->STCTRLH = 0;    // 禁止看门狗
	//检查Flash访问错误
  if(FTFL->FSTAT & FTFL_FSTAT_ACCERR_MASK)
  {
    FTFL->FSTAT |= FTFL_FSTAT_ACCERR_MASK;       //清除错误标志
  }
  //检查保护错误
  else if (FTFL->FSTAT & FTFL_FSTAT_FPVIOL_MASK)
  {
    FTFL->FSTAT |= FTFL_FSTAT_FPVIOL_MASK;
  }
  //检查读冲突错误
  else if (FTFL->FSTAT & FTFL_FSTAT_RDCOLERR_MASK)
  {
    FTFL->FSTAT |= FTFL_FSTAT_RDCOLERR_MASK;
  }
  //禁用Flash模块的数据缓存
  FMC->PFB0CR &= ~FMC_PFB0CR_B0DCE_MASK;
  FMC->PFB1CR &= ~FMC_PFB1CR_B1DCE_MASK;
}

/***********************************************************************************************
 功能：片内Flash读取数据
 形参：FlashStartAdd : 地址
       len           : 读取的长度
       *pbuffer      : 缓存区指针
 返回：0
 详解：
************************************************************************************************/
void FLASH_ReadByte(uint32_t FlashStartAdd,uint32_t len,uint8_t *pbuffer)
{
	uint32_t i = 0;
	for(i=0;i<len;i++)
	{
	  pbuffer[i] = *(uint8_t *)((FlashStartAdd<<11)+i);		//读取指定地址的数据
	}
}

/***********************************************************************************************
 功能：FALSH写一个扇区
 形参：sectorNo      : 扇区号(地址/2048)
       len           : 读取的长度
       *pbuffer      : 缓存区指针
 返回：0
 详解：一个扇区2048字节 所以至少写2048字节
************************************************************************************************/
uint8_t FLASH_WriteSector(uint32_t sectorNo,uint16_t count,uint8_t const *buffer)
{
	uint16_t i;
	union
	{
		uint32_t  word;
		uint8_t   byte[4];
	} dest;
	dest.word = (uint32_t)(sectorNo*(1<<11));

	// 设置写入命令
	FTFL->FCCOB0 = PGM4;
	// 四字节对齐
	for(i=0;i<count;i+=4)
	{
		// 设置存储地址
		FTFL->FCCOB1 = dest.byte[2];
		FTFL->FCCOB2 = dest.byte[1];
		FTFL->FCCOB3 = dest.byte[0];
		// 拷贝数据	（此数据排列按照从低位到高位存储）
		FTFL->FCCOB4 = buffer[3];
		FTFL->FCCOB5 = buffer[2];
		FTFL->FCCOB6 = buffer[1];
		FTFL->FCCOB7 = buffer[0];
		dest.word+=4; buffer+=4;
		//检测命令是否执行正常 
		if(FLASH_OK != CommandLaunch()) 
		return FLASH_ERROR;
    }
    return FLASH_OK;
}

/***********************************************************************************************
 功能：FALSH 擦除一个扇区
 形参：sectorNo      : 扇区号(地址/2048)
 返回：0
 详解：0
************************************************************************************************/
uint8_t FLASH_EraseSector(uint32_t sectorNo)
{
	union
	{
		uint32_t  word;
		uint8_t   byte[4];
	} dest;
	dest.word = (uint32_t)(sectorNo*(1<<11));
	// 设置擦除命令
	FTFL->FCCOB0 = ERSSCR; // 擦除扇区命令
	// 设置目标地址
	FTFL->FCCOB1 = dest.byte[2];
	FTFL->FCCOB2 = dest.byte[1];
	FTFL->FCCOB3 = dest.byte[0];
	//检测命令是否执行正常
		
	if(FLASH_OK == CommandLaunch())
	{
		return FLASH_OK;
	}
	else
	{
		return FLASH_ERROR;
	}
}

