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

int16_t jishuqi = 0, jishuqiqi = 0;
int16_t Ang_ACC_Mid = -1165;
uint16_t Mode_Choose = 0, sentdata = 0, Menu_Mode = 0, Buzzer_Open = 0, Start_Open = 0, Threshold = 125, Debug = 0, Kg = 5;
uint16_t Dt = 865, Level = 0, Mode = 0, SpTurn = 200;

/*
 *数据初始化
 *这不重要
 */
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
/*
 *PIT初始化
 */
void MyPIT_Init(void)
{
    PIT_InitTypeDef PIT_InitStruct1;
    PIT_InitStruct1.PITx = PIT1;
    PIT_InitStruct1.PIT_Interval = 5;
    PIT_Init(&PIT_InitStruct1);
    PIT_ITConfig(PIT1, PIT_IT_TIF, ENABLE);
    NVIC_DisableIRQ(PIT1_IRQn);
}
/*
 *中断优先级
 */
void NVIC_Rank(void)
{
    NVIC_Init(PIT1_IRQn, NVIC_PriorityGroup_2, 2, 0);
    NVIC_Init(PORTA_IRQn, NVIC_PriorityGroup_2, 0, 1);
    NVIC_Init(PORTD_IRQn, NVIC_PriorityGroup_2, 0, 2);
    NVIC_Init(DMA0_IRQn, NVIC_PriorityGroup_2, 0, 0);
}
/*
 *所有初始化
 *格式和命名很不规范
 */
void All_Init()
{
    SystemClockSetup(ClockSource_EX50M, CoreClock_200M); //k60 200m
    XJB_Init(); //瞎几把初始化 - 当时写代码命名比较愉悦吧
    NVIC_Rank(); //中断优先级
    Camera_Init(); //摄像头初始化
    Camera_DMA_Init(); //DMA初始化
    Data_Uart_Init(); //UART初始化
    DelayInit(); //延迟初始化
    OLED_Init(); //OLED初始化

    IMU_IIC_Init(); //IIC初始化
    OLED_Write_Num3(0, 0, 0); //成功的话 OLED显示
    L3G4200D_Init(); //陀螺仪初始化 里面其实和 IIC 是一样的
    OLED_Write_Num3(0, 0, 1); //同上
    MMA8451_Init(); //加速度初始化 和 IIC 一样的
    OLED_Write_Num3(0, 0, 2); //同上

    MyPIT_Init(); //PIT初始化
    Data_Init(); //数据初始化
}
/*
 *清除状态
 *格式和命名很不规范
 */
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
/*
 *跑模式
 *有好几种模式 为了代码看起来方便 删了其他的
 */
void Mode3()
{
    NVIC_EnableIRQ(PIT1_IRQn); //在跑的时候开启 PIT 中断
    NVIC_EnableIRQ(VIsr_NVIC); //还有摄像头的场中断
    OLED_Write_String(6, 2, (uint8_t *)"RUN"); //意思一下
    while (1)
    {
        if (P_Gather_Flag_OK == 1) //图像获取完成 FLAG
        {
            SignalProcess(); //图像处理
            Run(); //控制算法
            P_Gather_Flag_OK = 0;
        }
    }
}
/*
 *主函数
 *上面的代码建议不用看
 *直接从主函数开始
 */
int main(void)
{
    All_Init(); //大部分初始化
    Flash_Read(); //FLASH 读取
    Angle_Temper = Ang_ACC_Mid; //角度
    while (1)
    {
        Menu_Init(); //菜单初始化
        Threshold_Change(); //调整阈值

        while (Menu_Mode == 1)
        {
            // 模式很多
            // 有直立模式 原始图像 实时向上位机传输图像 跑模式 零点校验 传数据模式。。。。
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
    while (1);
}
