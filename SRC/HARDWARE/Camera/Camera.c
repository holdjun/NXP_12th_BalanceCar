#include "gpio.h"
#include "oled.h"
#include "dma.h"
#include "camera.h"
#include "extern.h"

void Camera_DMA_Init(void)
{
    DMA_InitTypeDef DMA_InitStruct1;

    DMA_InitStruct1.Channelx = DMA_CH0; //使用DMA0通道  (0-15)
    DMA_InitStruct1.DMAAutoClose = ENABLE; //传输完毕后自动关闭
    DMA_InitStruct1.EnableState = DISABLE; //初始化后不开始传输
    DMA_InitStruct1.MinorLoopLength = 700; //传输700次
    DMA_InitStruct1.PeripheralDMAReq = DMA_MUX2; //不需要触发源 尽最大努力传输
    DMA_InitStruct1.TransferBytes = 1; //每次传输一个字节
    //配置目的地址传输参数
    DMA_InitStruct1.DestBaseAddr = (uint32_t)(&P_DMA[0]); //指向目的地址
    DMA_InitStruct1.DestDataSize = DMA_DST_8BIT;  //数组为1Byte
    DMA_InitStruct1.DestMajorInc = 0;  //只执行一次大循环
    DMA_InitStruct1.DestMinorInc = 1;  //每次传输完地址+1

    //配置源地址传输参数
    DMA_InitStruct1.SourceBaseAddr = (uint32_t)(&(PTB->PDIR));
    DMA_InitStruct1.SourceDataSize = DMA_SRC_8BIT;
    DMA_InitStruct1.SourceMajorInc = 0;
    DMA_InitStruct1.SourceMinorInc = 0;
    DMA_Init(&DMA_InitStruct1);
    NVIC_EnableIRQ(DMA0_IRQn);
    DMA_ITConfig(DMA0, DMA_IT_MAJOR, DMA_CH0, ENABLE); //开启传输完成中断
}

void Camera_Init(void)
{
    //定义GPIO初始化结构
    GPIO_InitTypeDef GPIO_InitStruct1;
    //行中断 A5
    GPIO_InitStruct1.GPIOx = HIsr_Port;
    GPIO_InitStruct1.GPIO_InitState = Bit_SET;
    GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_RISING; //上升沿 下降沿 触发中断G
    GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct1.GPIO_Pin = HIsr_Pin;
    GPIO_Init(&GPIO_InitStruct1);
    //NVIC_EnableIRQ (PORTA_IRQn);//开启GPIO中断

    //场中断 D8
    GPIO_InitStruct1.GPIOx = VIsr_Port;
    GPIO_InitStruct1.GPIO_InitState = Bit_SET;
    GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_RISING_FALLING; //上升沿 下降沿 触发中断，奇场 偶场都要  的点
    GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct1.GPIO_Pin = VIsr_Pin;
    GPIO_Init(&GPIO_InitStruct1);
    //NVIC_EnableIRQ (VIsr_NVIC);//开启GPIO中断
    //B0-B7------------AD
    GPIO_InitStruct1.GPIOx = Camera_AD_Port;
    GPIO_InitStruct1.GPIO_InitState = Bit_SET;
    GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
    GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct1.GPIO_Pin = Camera_AD_Pin_0;
    GPIO_Init(&GPIO_InitStruct1);

    GPIO_InitStruct1.GPIOx = Camera_AD_Port;
    GPIO_InitStruct1.GPIO_InitState = Bit_SET;
    GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
    GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct1.GPIO_Pin = Camera_AD_Pin_1;
    GPIO_Init(&GPIO_InitStruct1);

    GPIO_InitStruct1.GPIOx = Camera_AD_Port;
    GPIO_InitStruct1.GPIO_InitState = Bit_SET;
    GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
    GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct1.GPIO_Pin = Camera_AD_Pin_2;
    GPIO_Init(&GPIO_InitStruct1);

    GPIO_InitStruct1.GPIOx = Camera_AD_Port;
    GPIO_InitStruct1.GPIO_InitState = Bit_SET;
    GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
    GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct1.GPIO_Pin = Camera_AD_Pin_3;
    GPIO_Init(&GPIO_InitStruct1);

    GPIO_InitStruct1.GPIOx = Camera_AD_Port;
    GPIO_InitStruct1.GPIO_InitState = Bit_SET;
    GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
    GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct1.GPIO_Pin = Camera_AD_Pin_4;
    GPIO_Init(&GPIO_InitStruct1);

    GPIO_InitStruct1.GPIOx = Camera_AD_Port;
    GPIO_InitStruct1.GPIO_InitState = Bit_SET;
    GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
    GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct1.GPIO_Pin = Camera_AD_Pin_5;
    GPIO_Init(&GPIO_InitStruct1);

    GPIO_InitStruct1.GPIOx = Camera_AD_Port;
    GPIO_InitStruct1.GPIO_InitState = Bit_SET;
    GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
    GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct1.GPIO_Pin = Camera_AD_Pin_6;
    GPIO_Init(&GPIO_InitStruct1);

    GPIO_InitStruct1.GPIOx = Camera_AD_Port;
    GPIO_InitStruct1.GPIO_InitState = Bit_SET;
    GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
    GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct1.GPIO_Pin = Camera_AD_Pin_7;
    GPIO_Init(&GPIO_InitStruct1);
}

void Camera_OLED(uint8_t (*P)[128])
{
    uint8_t count = 8, count_2 = 0, Pixels = 0;

    for (count = 0; count < 8; count++)
    {
        OLED_Set_XY(0, count);
        for (count_2 = 0; count_2 < 128; count_2++)
        {
            Pixels = ((*(*(P + count * 8 + 0) + count_2)) << 0) + ((*(*(P + count * 8 + 1) + count_2)) << 1) + ((*(*(P + count * 8 + 2) + count_2)) << 2) + ((*(*(P + count * 8 + 3) + count_2)) << 3) + ((*(*(P + count * 8 + 4) + count_2)) << 4) + ((*(*(P + count * 8 + 5) + count_2)) << 5) + ((*(*(P + count * 8 + 6) + count_2)) << 6) + ((*(*(P + count * 8 + 7) + count_2)) << 7);
            OLED_WrDat(Pixels);
        }
    }
}
