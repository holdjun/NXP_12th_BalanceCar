#include "sys.h"
#include "gpio.h"
#include "delay.h"
#include "led.h"
#include "wdog.h"
#include "pit.h"
#include "dma.h"
#include "ftm.h"
#include "lptm.h"
#include "key.h"
#include "adc.h"
#include "tsi.h"
#include "dac.h"
#include "spi.h"
#include "i2c.h"
#include "pdb.h"
#include "sd.h"
#include "flash.h"
#include "spilcd.h"
#include "stdio.h"
#include "uart.h"
#include "oled.h"
#include "camera.h"
#include "data_sd.h"
#include "data_sent.h"
#include "menu.h"
#include "extern.h"
#include "run.h"
#include "IMU_IIC.h"
#include "L3G4200D.h"
#include "mma8451.h"
#include "Angle.h"
#include "math.h"
#include "dmacnt.h"
#include "image.h"
#include "kaman.h"
#include "mymath.h"
#include "xjb.h"

struct PID Speed_L_PID, Speed_R_PID, Direction_PID, Angle_PID, Direction_IN_PID, Angle_PID_A, Angle_PID_G;
int16_t jishuqi = 0, jishuqiqi = 0, Ang_ACC_Mid = -1165;
uint16_t
    Mode_Choose = 0,
    sentdata = 0,
    Menu_Mode = 0,
    Buzzer_Open = 0,
    Start_Open = 0,
    Threshold = 125,
    Debug = 0,
    Kg = 5,
    Dt = 865,
    Level = 0,
    Mode = 0,
    SpTurn = 200;

void Data_Init()
{
    uint8_t i = 0;
    Mode = 3;
    Kg = 5;
    Dt = 865;
    Level = 0;
    SpTurn = 320;
    Mode_Choose = 2;
    Ramp_Choose = 2;
    Buzzer_Open = 0;
    Start_Open = 2;
    Threshold = 124;
    Ang_ACC_Mid = -600;
    Angle_PID.Kp = 185;
    Angle_PID.Kd = 140;
    Direction_PID.Kp = 650;
    Direction_PID.KTd = 30;
    Direction_PID.Kd = 170;
    Speed_L_PID.Kp = 1500;
    Speed_L_PID.Ki = 20;
    Speed_L_PID.Kd = 0;
    SetPodaoA = 200;
    SetPodaoC = 0;
    Direction_PID.Error[0] = 0;
    Direction_PID.Error[1] = 0;
    Speed_L_PID.Error[0] = 0;
    Speed_L_PID.Error[1] = 0;
    Speed_L_PID.Error[2] = 0;
    Direction_PID.ControlOutOld = 0;
    Speed_L_PID.ControlOutOld = 0;
    Debug = 1;
    sentdata = 3;
    Ramp_Ring = 6;
    Obstacle_down = 6;
    Up_Speed = 260;
    Down_Speed = 310;
    Ring_jianshu = 0;
    I_TimeA = 10;
    I_TimeB = 20;
    laxian_k = 25;
    Ramp_Up_Num = 40;
    Ramp_Down_Num = 10;
    lanxian_flag = 0;
    small_p = 670;
    mid_p = 700;
    big_p = 700;
    Ring_jianshu = 0;
    small_ring = 0;
    guai_switch_flag = 1;
    small_state_2_p = 650;
    small_state_num = 6;
    small_state_2 = 0;
    ftm_add_flag = 1;
    ftm_add = 200;
    for (i = 0; i < 10; i++)
    {
        Ring_Dir_Flag[i] = 1;
    }
}

void MyPIT_Init(void)
{
    PIT_InitTypeDef PIT_InitStruct1;
    PIT_InitStruct1.PITx = PIT1;

    PIT_InitStruct1.PIT_Interval = 5;
    5MS PIT_Init(&PIT_InitStruct1);
    PIT_ITConfig(PIT1, PIT_IT_TIF, ENABLE);
    NVIC_DisableIRQ(PIT1_IRQn);
}

void NVIC_Rank(void)
{
    NVIC_Init(PIT1_IRQn, NVIC_PriorityGroup_2, 2, 0);
    NVIC_Init(PORTA_IRQn, NVIC_PriorityGroup_2, 0, 1);
    NVIC_Init(PORTD_IRQn, NVIC_PriorityGroup_2, 0, 2);
    NVIC_Init(DMA0_IRQn, NVIC_PriorityGroup_2, 0, 0);
}
void All_Init()
{
    SystemClockSetup(ClockSource_EX50M, CoreClock_200M);
    XJB_Init();
    NVIC_Rank();
    Camera_Init();
    Camera_DMA_Init();
    Data_Uart_Init();
    DelayInit();
    OLED_Init();
    IMU_IIC_Init();
    L3G4200D_Init();
    MMA8451_Init();
    MyPIT_Init();
    Data_Init();
    FLASH_Init();
}
void Clear()
{
    OLED_Clear();
    NVIC_DisableIRQ(PIT1_IRQn);
    FTM_PWM_ChangeDuty(FTM_Right_Forward, 0);
    FTM_PWM_ChangeDuty(FTM_Left_Forward, 0);
    FTM_PWM_ChangeDuty(FTM_Right_Backward, 0);
    FTM_PWM_ChangeDuty(FTM_Left_Backward, 0);
    Menu_Mode = 0;
}

void Mode0()
{
    NVIC_EnableIRQ(PIT1_IRQn);
    while (1)
    {
        OLED_Write_Num5(0, 2, L3G4200D_OUT_Y);
        OLED_Write_Num5(0, 4, L3G4200D_OUT_Z);
        OLED_Write_Num5(0, 6, jishuqiqi);
        OLED_Write_Num5(0, 0, Ang_ACC_X);
        OLED_Write_Num5(10, 0, (int16_t)Angle);
        OLED_Write_Num5(10, 2, (int16_t)(Angle - Ang_ACC_Mid));
        OLED_Write_Num5(10, 4, Encoder_Left[2]);
        OLED_Write_Num5(10, 6, Encoder_Right[2]);
        data_give();
        UART_Send_Con();
        if (Ang_Gyro_Z > 3500 || Ang_Gyro_Z < -3500)
        {
            OLED_Write_String(6, 2, (uint8_t *)"GyroStop");
            Stop();
        }
        if (Key_Out == 0)
        {
            Clear();
            while (Key_Out == 0)
                ;
            break;
        }
    }
}

void Mode1()
{
    NVIC_EnableIRQ(VIsr_NVIC);
    NVIC_EnableIRQ(PIT1_IRQn);
    while (1)
    {
        if (Key_Minus == 0)
        {
            Threshold -= 1;
            while (!Key_Minus)
                ;
        }
        if (Key_Add == 0)
        {
            Threshold += 1;
            while (!Key_Add)
                ;
        }

        if (P_Gather_Flag_OK == 1)
        {

            SignalProcess();
            Run();
            Get_OLED_Pixels();
            Camera_OLED(OLED_P_Pixels);
            P_Gather_Flag_OK = 0;
        }
        if (Key_Out == 0)
        {
            Clear();
            while (Key_Out == 0)
                ;
            break;
        }
    }
}
void Mode2()
{
    NVIC_EnableIRQ(VIsr_NVIC);
    NVIC_EnableIRQ(PIT1_IRQn);
    while (1)
    {
        if (Key_Out == 0)
        {
            DelayMs(100);
            if (Key_Out == 0)
            {
                Clear();
                while (Key_Out == 0)
                    ;
                break;
            }
        }
        if (P_Gather_Flag_OK == 1)
        {
            SignalProcess();
            Run();
            Show_Midline();
            Get_OLED_Pixels();
            Camera_OLED(OLED_P_Pixels);
            P_Gather_Flag_OK = 0;
        }
    }
}

void Mode3()
{
    NVIC_EnableIRQ(PIT1_IRQn);
    NVIC_EnableIRQ(VIsr_NVIC);
    OLED_Write_String(6, 2, (uint8_t *)"RUN");
    while (1)
    {
        if (P_Gather_Flag_OK == 1)
        {
            SignalProcess();
            Run();
            P_Gather_Flag_OK = 0;
        }
    }
}

void Mode4()
{
    NVIC_EnableIRQ(PIT1_IRQn);
    NVIC_EnableIRQ(VIsr_NVIC);
    while (1)
    {
        if (P_Gather_Flag_OK == 1)
        {
            SignalProcess();
            Run();
            OLED_Write_Num3(0, 2, LCenter[0]);
            OLED_Write_Num3(0, 0, LCenter[68]);
            Live_Transmission();
            P_Gather_Flag_OK = 0;
        }
    }
}
void Mode5()
{
    MySD_Init();
    SD_ManyWT_Init();
    OLED_Write_String(6, 2, (uint8_t *)"SD:RUN");
    NVIC_EnableIRQ(PIT1_IRQn);
    NVIC_EnableIRQ(VIsr_NVIC);
    while (1)
    {
        if (P_Gather_Flag_OK == 1)
        {
            SignalProcess();
            Run();
            SD_Write();
            P_Gather_Flag_OK = 0;
        }
    }
}
void Mode6()
{
    MySD_Init1();
    SD§Ô
        OLED_Write_String(6, 2, (uint8_t *)"transfer");
    while (1)
    {
        SD_ReadData();
    }
}
void Mode7()
{
    int16_t Count = 0;
    int16_t All_Ang_Gyro_Y = 0,
            All_Ang_Gyro_Z = 0;
    OLED_Write_String(6, 2, (uint8_t *)"Wait");
    DelayMs(2000);
    Clear();
    OLED_Write_String(4, 2, (uint8_t *)"Checking");
    OLED_Write_String(4, 4, (uint8_t *)"No Touth");
    while (Count < 1024)
    {
        All_Ang_Gyro_Y = All_Ang_Gyro_Y + (L3G4200D_GetResult(L3G4200D_STATUS_REG, L3G4200D_OUT_Y_H));
        OLED_Write_Num5(4, 6, All_Ang_Gyro_Y);
        DelayMs(2);
        All_Ang_Gyro_Z = All_Ang_Gyro_Z + (-L3G4200D_GetResult(L3G4200D_STATUS_REG, L3G4200D_OUT_X_H));
        DelayMs(2);
        OLED_Write_Num5(10, 6, All_Ang_Gyro_Z);
        Count++;
    }
    Count = 0;
    Clear();
    OLED_Write_String(4, 0, (uint8_t *)"Finish");
    Ang_Gyro_Y_Zero = All_Ang_Gyro_Y >> 10;
    Ang_Gyro_Z_Zero = All_Ang_Gyro_Z >> 10;
    OLED_Write_String(0, 2, (uint8_t *)"YZero:");
    OLED_Write_Num5(10, 2, Ang_Gyro_Y_Zero);
    OLED_Write_String(0, 4, (uint8_t *)"ZZero:");
    OLED_Write_Num5(10, 4, Ang_Gyro_Z_Zero);
    while (1)
    {
        if (Key_Out == 0)
        {
            Clear();
            while (Key_Out == 0)
                ;
            break;
        }
    }
}
void Mode8()
{
    OLED_Write_String(4, 0, (uint8_t *)"DataInit");
    Data_Init();
    Flash_Write();
    Flash_Read();
    while (1)
    {
        if (Key_Out == 0)
        {
            Clear();
            while (Key_Out == 0)
                ;
            break;
        }
    }
}

int main(void)
{
    All_Init();
    Flash_Read();
    Angle_Temper = Ang_ACC_Mid;
    while (1)
    {
        Menu_Init();
        Threshold_Change();
        while (Menu_Mode == 1)
        {
            switch (Mode)
            {
            case 0:
                Mode0();
                break;
            case 1:
                Mode1();
                break;
            case 2:
                Mode2();
                break;
            case 3:
                Mode3();
                break;
            case 4:
                Mode4();
                break;
            case 5:
                Mode5();
                break;
            case 6:
                Mode6();
                break;
            case 7:
                Mode7();
                break;
            case 8:
                Mode8();
                break;
            default:
                break;
            }
        }
    }
}

void assert_failed(uint8_t *file, uint32_t line)
{

    UART_printf("assert_failed:line:%d %s\r\n", line, file);
    while (1)
        ;
}
