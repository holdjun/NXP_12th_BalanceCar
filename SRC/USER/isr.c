#include "isr.h"
#include "oled.h"
#include "camera.h"
#include "ftm.h"
#include "led.h"
#include "oled.h"
#include "extern.h"
#include "IMU_IIC.h"
#include "L3G4200D.h"
#include "mma8451.h"
#include "Angle.h"
#include "uart.h"
#include "data_sd.h"
#include "data_sent.h"
#include "menu.h"
#include "Run.h"
#include "dmacnt.h"
#include "Filter.h"
//控制周期计数,标志位
uint8_t Threshold_Temper = 0;
uint8_t g_nSpeedControlCount = 0,
        g_nDirectionControlCount = 0,
        g_nSpeedControlPeriod = 0,
        g_nDirectionControlPeriod = 0;
uint16_t rownum = 0, count_4 = 0;
uint8_t *Pointer_P_Pixels_Temp,
    *Pointer_P_DMA = P_DMA,
    Now_H = 0;
uint16_t *Pointer_Camera_Valid_Row = Camera_Valid_Row,
         *Pointer_Camera_Valid_Line = Camera_Valid_Line;
uint8_t *Pointer_Threshold = Thre;
#include "mymath.h"
//场中断
void VIsr(void)
{
    rownum = 0;
    Pointer_P_Pixels_Temp = Pixels[0];
    Pointer_Camera_Valid_Line = Camera_Valid_Line;
    Now_H = 0;
    NVIC_EnableIRQ(HIsr_NVIC);
    GPIO_ClearITPendingBit(VIsr_Port, VIsr_Pin);
}
//行中断
void HIsr(void)
{
    rownum++;
    if (rownum == (*Pointer_Camera_Valid_Line))
    {
        DMA_SetEnableReq(DMA_CH0, ENABLE);
        Pointer_Camera_Valid_Line++;
        if (Ramp_Flag == 1 && Now_H > Final_Line)
            Threshold_Temper = *(Pointer_Threshold + Now_H) + 10;
        else if (Element_Flag == 2)
        {
            Threshold_Temper = *(Pointer_Threshold + Now_H) + 5;
            if (Now_H > Final_Line)
                Threshold_Temper = *(Pointer_Threshold + Now_H) + 5;
        }
        else
            Threshold_Temper = *(Pointer_Threshold + Now_H);
        if (Angle < 1000)
            Threshold_Temper = Threshold_Temper + (1000 - Angle) / 100;
        Now_H++;
    }
    if (rownum >= (*(Camera_Valid_Line + 69)))
    {
        P_Gather_Flag_OK = 1;
        NVIC_DisableIRQ(HIsr_NVIC);
        //DMA_SetEnableReq (DMA_CH0 , DISABLE);
    }
    GPIO_ClearITPendingBit(HIsr_Port, HIsr_Pin);
}

//DMA
void DMA0_IRQHandler(void)
{
    uint8_t Threshold_Temper_F = 0;
    for (count_4 = 0; count_4 < 200; count_4++)
    {
        //if((count_4>170 )&&Now_H<Final_Line)
        //Threshold_Temper_F=Threshold_Temper-15;
        //else
        Threshold_Temper_F = Threshold_Temper;
        if (Threshold_Temper_F < 117)
            Threshold_Temper_F = 117;
        if (Pointer_P_DMA[Pointer_Camera_Valid_Row[count_4]] >= Threshold_Temper_F)
        {
            *Pointer_P_Pixels_Temp = 1;
        }
        else
        {
            *Pointer_P_Pixels_Temp = 0;
        }
        Pointer_P_Pixels_Temp++;
    }
    DMA0->TCD[DMA_CH0].DADDR = (uint32_t)P_DMA;
    DMA_ClearITPendingBit(DMA0, DMA_IT_MAJOR, DMA_CH0);
}
void PIT1_IRQHandler(void)
{
    //编码器临时值
    int16_t Encoder_Left_Temp, Encoder_Right_Temp;
    g_nSpeedControlCount++;
    g_nDirectionControlCount++;

    jishuqi++;
    if (jishuqi == 200)
    {
        jishuqiqi++;
        jishuqi = 0;
    }

    Get_Angle();
    AngleControl();
    if (g_nDirectionControlCount >= DIRECTION_CONTROL_COUNT)
    {
        if (Encoder_Direction_Left == 1)
            Encoder_Left_Temp = DMACNT_GetValue(DMA_CH1);
        else
            Encoder_Left_Temp = -DMACNT_GetValue(DMA_CH1);

        if (Encoder_Direction_Right == 1)
            Encoder_Right_Temp = -DMACNT_GetValue(DMA_CH2);
        else
            Encoder_Right_Temp = DMACNT_GetValue(DMA_CH2);
        //Encoder_Left[2]=Encoder_Left_Temp;
        //Encoder_Right[2]=Encoder_Right_Temp;
        Encoder_Left[2] = L_Encoder_Average_Filter(Encoder_Left_Temp);
        Encoder_Right[2] = R_Encoder_Average_Filter(Encoder_Right_Temp);
        g_CarSpeed = Speed_Add(Encoder_Left[2], Encoder_Right[2]);
        g_nDirectionControlCount = 0;
    }
    if (g_nSpeedControlCount >= SPEED_CONTROL_COUNT)
    {
        SpeedControl();
        g_nSpeedControlCount = 0;
    }
    //平滑输出
    SpeedControlOutput();
    DirectionControlOutput();
    MotorOutput();
    PIT_ClearITPendingBit(PIT1, PIT_IT_TIF);
}
