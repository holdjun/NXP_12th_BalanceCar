#ifndef __EXTERN_H__
#define __EXTERN_H__
#include "stdint.h"
#include "menu.h"
#define byte uint8_t
//按键引脚宏定义
#define Key_Up PDin(13)    //
#define Key_Down PDin(11)  //
#define Key_Add PDin(10)   //
#define Key_Minus PDin(12) //
#define Key_In PDin(14)    //
#define Key_Out PDin(15)   //

#define Pin_Up GPIO_Pin_13
#define Pin_Down GPIO_Pin_11
#define Pin_Add GPIO_Pin_10
#define Pin_Minus GPIO_Pin_12
#define Pin_In GPIO_Pin_14
#define Pin_Out GPIO_Pin_15

#define Port_Up PTD
#define Port_Down PTD
#define Port_Add PTD
#define Port_Minus PTD
#define Port_In PTD
#define Port_Out PTD
//FTM引脚宏定义
#define FTM_Left_Forward 	FTM1_CH1_PA9
#define FTM_Right_Forward   FTM0_CH3_PA6
#define FTM_Left_Backward  FTM1_CH0_PA8
#define FTM_Right_Backward   FTM0_CH4_PA7
//编码器引脚宏定义
#define Port_Encoder_Left PTC
#define Port_Encoder_Direction_Left PTC
#define Port_Encoder_Right PTD
#define Port_Encoder_Direction_Right PTD

#define Pin_Encoder_Left GPIO_Pin_17
#define Pin_Encoder_Direction_Left GPIO_Pin_16
#define Pin_Encoder_Right GPIO_Pin_0
#define Pin_Encoder_Direction_Right GPIO_Pin_1

#define Encoder_Direction_Left PCin(16)
#define Encoder_Direction_Right PDin(1)

//蜂鸣器引脚宏定义
#define Port_Buzzer PTC
#define Pin_Buzzer GPIO_Pin_12
#define Buzzer PCin(12)

//控制周期宏定义
extern uint8_t SPEED_CONTROL_COUNT;
extern uint8_t DIRECTION_CONTROL_COUNT;

//标志位
extern uint8_t g_nSpeedControlCount;
extern uint8_t g_nDirectionControlCount;
//编码器
extern int16_t Encoder_Left[3];
extern int16_t Encoder_Right[3];
extern int16_t g_CarSpeed;
//陀螺仪编码器
//滤波前
extern int16_t MMA8451_OUT_X;
extern int16_t MMA8451_OUT_Y;
extern int16_t MMA8451_OUT_Z;
extern int16_t L3G4200D_OUT_Y;
extern int16_t L3G4200D_OUT_Z;
extern int16_t L3G4200D_OUT_X;
extern int16_t Ang_Gyro_Y_Zero;
extern int16_t Ang_Gyro_Z_Zero;
//滤波后
extern double Angle_Temper; //综合角度
extern double Angle;        //综合角度
extern double Ang_IGyro;    //角速度积分
extern int16_t Ang_ACC_X;  //X轴加速度值
extern int16_t Ang_ACC_Z;  //Z轴加速度值
extern int16_t Ang_Gyro_X; //绕X轴角速度
extern int16_t Ang_Gyro_Y; //绕Y轴角速度
extern int16_t Ang_Gyro_Z; //绕Z轴角速度
//Run
extern uint8_t Start_Flag;
extern uint16_t Start_Count;
extern int16_t Set_Speed;
extern int R_ControlOut;
extern int L_ControlOut;
extern int D_pwn_temp;

extern int32_t P_pwn_temp;
extern uint8_t Final_Line;
extern uint8_t Last_Line;
extern uint8_t Mid;
extern uint8_t Field_Flag;
extern int16_t Angle_Line;
extern int16_t Speed_Line;
extern uint16_t Base_Kp;
extern int16_t jishuqi,jishuqiqi;

extern int I_L;
//SD
extern int sector;

//摄像头采集
extern uint8_t Pixels[70][200];
extern uint8_t L_black[70]; //左线点储存数组
extern uint8_t LCenter[70]; //中线点储存数组
extern uint8_t R_black[70]; //右线点储存数组
extern uint8_t Thre[70];    //阈值
extern uint8_t P_Gather_Flag_OK;
extern uint8_t P_DMA[700];
extern uint8_t P_Pixels_Temp[14000];
extern uint16_t Camera_Valid_Line[70];
extern uint16_t Camera_Valid_Row[200];
extern uint8_t OLED_P_Pixels[70][128];
extern uint8_t Threshold_Temper;

extern uint8_t Element_Flag, //1为直道2为弯道
    SmallS_Flag,             //小S
    BigS_Flag,               //大S
    Ring_Flag,               //环形
    Ramp_Flag,              //坡道
    Starting_Line_Flag,      //起跑线
    L_Obstacle_Flag,         //左障碍
    R_Obstacle_Flag,         //右障碍
    First_L_Loss_Flag,       //第一行左丟线
    First_R_Loss_Flag;       //第一行右丟线
extern uint8_t Element,
               Field_Cross_Flag,
				Ramp_Ring,
                Ramp_New_Count,
               jiaRamp_Flag;

//减速处理

extern uint16_t I_Flag;
extern uint16_t I_Speed;
extern uint16_t I_TimeA;
extern uint16_t I_TimeB;

//坡道处理
extern uint16_t Speed_jian_Flag,
				Speed_jian_Count,
				Up_Speed,
				Down_Speed,
				SetPodao,
				SetPodaoxia,
				SetPodaoA,
				SetPodaoC,
				SetPodaoB;
extern uint8_t Accer_Folloew_Flag,ring_switch,Ring_Find_Flag,Ring_State_Flag;
extern int16_t Speed_spout,
               Line_40;
extern uint16_t

    Buzzer_Open,
    Mode_Choose,
    hang,
    Threshold,
    Kg,
    sentdata,
    Menu_Mode,
    Ring_Dir_Flag[10],
    Ramp_Choose,
	Debug,
    flash_flag,
    Ring_jianshu,
    laxian_k,
    Podao_bisai,
    Obstacle_down,
    lanxian_flag,
small_ring,
guai_switch_flag,
small_state_2,
small_state_num,
small_state_2_p,
small_p,
ftm_add_flag,
ftm_add,
mid_p,
big_p,
    Start_Open;
extern uint16_t
    Dt,
    Mode,
    Level,
    SpTurn;
extern int16_t
    Ang_ACC_Mid,
    Hang_Min,
    Hang_Max,
    DValue,
    TDValue,
    PValue,
    DTDValue;

extern uint16_t  Ramp_Up_Num,
                Ramp_Down_Num;







struct PID
{
    int Kp;
    int Kd;
    int Ki;
    int KTd;
    int Error[3];
    int ControlOut;
    int ControlOutLast;
    int ControlOutNew;
    int ControlOutOld;
};

extern struct PID Speed_L_PID, Speed_R_PID, Direction_PID, Angle_PID,Direction_IN_PID;

#endif
