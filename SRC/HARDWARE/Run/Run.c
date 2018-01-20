#include "run.h"
#include "ftm.h"
#include "oled.h"
#include "extern.h"
#include "camera.h"
#include "menu.h"
#include "delay.h"
#include "math.h"
#include "stdint.h"
#include "angle.h"
#include "mymath.h"
#define byte uint8_t
//控制周期宏定义
uint8_t SPEED_CONTROL_COUNT = 20;
uint8_t DIRECTION_CONTROL_COUNT = 4;
/*********************************************************************
                                                   特定区间减速参数
************************************************************************/
uint16_t I_Flag = 0;
uint16_t I_Speed = 0;
uint16_t I_TimeA = 0;
uint16_t I_TimeB = 0;

/*********************************************************************
                                                    偏差获取参数
************************************************************************/
uint8_t Mid_Line = 100;
int16_t Angle_Line = 0;
int16_t Speed_Line = 0;

int16_t Hang_Max = 0, Hang_Min = 0;
/*********************************************************************
                                                    控制参数
************************************************************************/

uint16_t Base_Kp = 690;
uint16_t Temper_DIR_CONTROL_P = 0;
uint16_t Temper_DIR_CONTROL_TD = 0;
uint16_t Temper_DIR_CONTROL_D = 0;
int16_t Set_Ang_Mid = 0; //目标速度

int16_t Setwan_Ang_Mid = 0; //目标速度
int16_t Set_Speed = 0;      //目标速度
int R_ControlOut = 0;       //右轮输出
int L_ControlOut = 0;       //左轮输出
int R_ControlOut_Last = 0;  //右轮输出
int L_ControlOut_Last = 0;  //左轮输出
int D_pwn_temp = 0;
int P_pwn_temp = 0;

int pwm_out = 0;
int16_t Least_ControlOut = 0; //电机死区
//int16_t ControlOutMax = 9999;  //最大正向输出
//int16_t ControlOutMin = -9999; //最大反向输出
int16_t SpeedControlOutMax = 10000;
int16_t SpeedControlOutMin = -10000;
int16_t I_L_Max = 4000;
int16_t Encoder_Max = 500;      //编码器正向保护值
int16_t Encoder_Min = -500;     //编码器反向保护值
int16_t Encoder_Left[3] = {0};  //编码器左轮速度
int16_t Encoder_Right[3] = {0}; //编码器右轮速度
int16_t g_CarSpeed = 0;         //整体速度
int P_L = 0, D_L = 0, I_L = 0;
int G_I_L = 0;
uint8_t Accer_Folloew_Flag = 0;
uint16_t Accer_Folloew_Count = 0;
uint16_t Start_Line_Count = 0;
uint16_t Time_Clock_5Ms = 0;
uint16_t Time_Clock_500Ms = 0;
/*******坡道速度******/
uint16_t Ramp_Angle = 1000;   //300
uint16_t RampXia_Angle = 300; //150
uint16_t Rampxiacount = 0;
uint16_t Ramp4count = 0;
uint16_t Ramp_Count = 0;
uint16_t Rampshangcount = 0;
/*刚开头下倾多**/
uint16_t BiggestJiaCount = 0;

uint16_t nSpeedStopCount = 0;
/*___________分段打角___Start___________*/

uint16_t Direct_Control_P_Big = 10; //方向控制比例项  68

uint16_t Direct_Control_P_Normal = 5; //方向控制比例项  68

uint16_t Direct_Control_P_Small = 100;

uint16_t Direct_Control_P_L_Help = 6;

uint16_t Dajiao_Change_RangeB = 40;

uint16_t Dajiao_Change_RangeS = 15;
/*___________分段打角___End___________*/
/*******模糊打角************/
double Final_P;
double Final_D;
double Findl_D_T;

#define RANGE_MOHU_S 5  //小区域
#define RANGE_MOHU_B 10 //大区域
/*********************************************************************
                                                    赛道类型
************************************************************************/
uint8_t Element_Flag = 0, //1为直道2为弯道
    SmallS_Flag = 0,      //小S
    BigS_Flag = 0,        //大S
    Ring_Flag = 0;        //环形

uint8_t Element = 0;

/*********************************************************************

                                                    图像处理参数
************************************************************************/
uint8_t Obstacle_Processing_Flag = 0, Obstacle_Processing_Count = 0;
uint8_t Field_Cross_Flag = 0;
uint8_t Oblique_Direct_Cross_Flag = 0, Oblique_Direct_Cross_Line = 0;
uint8_t Final_Line_Flag = 0;

uint8_t L_Turningpoint_Max = 0, R_Turningpoint_Min = 0;
uint8_t Ring_BlackFind_Line = 0;
uint8_t Ramp_Check_Flag = 0, NoRamp_Flag = 0, Ramp_Flag_Line = 0;
uint8_t Small_S_Count = 0, ring_switch = 0;
uint8_t Ramp_Line[4] = {0};
uint8_t Ramp_New_Count = 0;
int16_t Line_40 = 0;
int16_t Speed_spout = 0, deBug_Flag = 0;
uint16_t SetPodaoA = 1000, SetPodaoB = 1000, SetPodaoC = 500, SetPodao = 500, SetPodaoxia = 0;

int16_t PValue = 0;
int16_t DValue = 0;
int16_t TDValue = 0;
int16_t DTDValue = 0;

/*****************补线****************/
byte Mid = 100;
byte RowNum = 0;
byte NoElement_Flag = 0;
byte L_Width = 0, R_Width = 0;
byte find_l = 110, find_r = 90;
byte All_L_Loss = 0, All_R_Loss = 0;
byte Final_Line = 0, Last_Line = 0, Last_Line_Flag = 0;
byte L_Loss = 0, R_Loss = 0, First_L_Loss_Flag = 0, First_R_Loss_Flag = 0;
/************************************/

uint8_t L_Turningpoint_Line[5];
uint8_t R_Turningpoint_Line[5];

/*****************十字****************/
byte L_Oblique_Cross_Flag = 0, R_Oblique_Cross_Flag = 0, Oblique_Cross_Line = 0;
byte Direct_Cross_Flag = 0, Direct_Cross_Line = 0, Direct_Cross_Field_Count = 0;
byte L_Inflection_Line = 0, L_Inflection_Flag = 0;
byte R_Inflection_Line = 0, R_Inflection_Flag = 0;
byte Element_Cross = 0;
byte UnCross_Flag = 0;
byte Zheng_Cross_Flag = 0;
byte Cross_State = 0;
/************************************/

/*****************障碍****************/
byte L_Obstacle_Count = 0, R_Obstacle_Count = 0;
byte L_Obstacle_Line = 0, R_Obstacle_Line = 0;
byte L_Obstacle_Flag = 0, R_Obstacle_Flag = 0;
byte Obstacle_Wide = 0, Obstacle_Wide_Last = 0;
byte Obstacle_L_Line = 0, Obstacle_R_Line = 0;
uint16_t Obstacle_down = 0;
byte Obstacle_num = 0;
/************************************/
uint8_t Ramp_Ring = 1;
/*****************环路****************/
uint16_t Ring_Dir_Flag[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte Loop_L_Max = 0, Loop_R_Max = 0;
byte Loop_Last_L_Max = 0, Loop_Last_R_Max = 0;
byte Loop_guai_L = 0, Loop_guai_R = 0;
byte Loop_last_guai_L = 0, Loop_last_guai_R = 0, Loop_guai_flag = 0;
byte guai_R = 0, guai_L = 0;
byte State_flag = 0;
byte Ring_State_Flag = 0;
byte Ring_Find_Flag = 0;
byte Ring_Dir_num = 0;
byte jiaRamp_Flag = 0;
byte black_flag = 0;
byte state_4 = 0;
byte state_5 = 0;
byte num_jishu = 0;
byte BigRing_Count = 0;
byte MidRing_Count = 0;
byte Loop_L_Inflection_Line = 0, Loop_L_Inflection_Flag = 0, Loop_R_Inflection_Line = 0, Loop_R_Inflection_Flag = 0;
byte Ring_CD = 0;
byte Ring_qusi_4 = 0;
byte Loop_L_guai = 0, Loop_R_guai = 0;
byte Loop_Last_L_guai = 0, Loop_Last_R_guai = 0;

byte R_Turning_Point_Flag = 0;
byte L_Turning_Point_Flag = 0;
byte Loop_hei_flag = 0;
byte Z_black_flag = 0;
uint16_t lanxian_flag = 0;
uint16_t small_p = 0;
uint16_t mid_p = 0;
uint16_t big_p = 0;

uint16_t small_ring = 0;
uint16_t guai_switch_flag = 0;
uint16_t small_state_2 = 0;
uint16_t small_state_num = 0;
uint16_t small_state_2_p = 650;
uint16_t small_speed = 0;
uint16_t ftm_add_flag = 0;
uint16_t ftm_add = 0;
/************************************/

/*****************坡道****************/
byte Ramp_New = 0;
byte Ramp_Flag = 0;
uint16_t Ramp_Choose = 0;
byte L_black_Temp = 0;
byte R_black_Temp = 0;
byte L_black_Memory1 = 0;
byte R_black_Memory1 = 0;
byte L_black_Memory2 = 0;
byte R_black_Memory2 = 0;
float L_black_Slope1 = 0;
float L_black_Slope2 = 0;
float R_black_Slope1 = 0;
float R_black_Slope2 = 0;
byte Stay_Flag = 0;
uint16_t Ramp_Up_Num = 40;
uint16_t Ramp_Down_Num = 10;
/************************************/

byte Starting_Line_Flag = 0; //起跑线
byte StarteTime = 50;
uint16_t Ring_jianshu = 0;
uint16_t laxian_k = 27;
/*****************坡道处理*******************/
uint16_t Up_Speed = 280;
uint16_t Speed_jian_Count = 0;
uint16_t Down_Speed = 280;
uint16_t Speed_jian_Flag = 0;

uint16_t Podao_bisai = 0;
uint8_t LStart[70]; //中线点储存数组
uint8_t RStart[70]; //右线点储存数组
uint8_t fixValue[70] =
{
        135, 135, 133, 132, 131, 130, 129, 128, 127, 127,
        125, 124, 122, 121, 120, 120, 118, 116, 115, 114,
        113, 111, 110, 109, 107, 106, 105, 103, 102, 101,
        100, 99, 97, 96, 94, 93, 92, 90, 88, 88,
        87, 86, 84, 82, 81, 80, 79, 76, 74, 72,
        71, 68, 68, 67, 65, 64, 62, 60, 59, 59,
        57, 54, 52, 51, 47, 45, 43, 40, 37, 35,
};

/*********************************************************************
                                                    图像处理
************************************************************************/

int16_t fabss(int16_t a1, int16_t a2) //绝对值
{
    if (a1 > a2)
        return (int16_t)(a1 - a2);
    else
        return (int16_t)(a2 - a1);
}

byte MinNum(byte Value1, byte Value2)
{

    if (Value1 >= Value2)
    {
        return Value2;
    }
    else
        return Value1;
}

void Buzzer_Sart()
{
    if (Buzzer_Open == 1)
    {

        if (Starting_Line_Flag == 1)
            GPIO_SetBits(Port_Buzzer, Pin_Buzzer);
        //        else if (SmallS_Flag == 1)
        //            GPIO_SetBits(Port_Buzzer, Pin_Buzzer);
        //        else if (Element_Flag == 3)
        //                GPIO_SetBits(Port_Buzzer, Pin_Buzzer);
        //        else if (Ring_Find_Flag == 1)
        //                GPIO_SetBits(Port_Buzzer, Pin_Buzzer);
        else if (Ramp_Flag > 0)
            GPIO_SetBits(Port_Buzzer, Pin_Buzzer);
        //        else if (L_Obstacle_Flag == 1 || R_Obstacle_Flag == 1)
        //            GPIO_SetBits(Port_Buzzer, Pin_Buzzer);
        //        else if (fabss(g_CarSpeed,SpTurn) < 20)
        //            GPIO_SetBits(Port_Buzzer, Pin_Buzzer);
        else
            GPIO_ResetBits(Port_Buzzer, Pin_Buzzer);
    }
}

void Image_Init() //把每场图像处理里数据里需要初始化的变量初始化
{
    Field_Cross_Flag = 0;

    /*****************补线****************/
    RowNum = 0;
    NoElement_Flag = 0;
    L_Width = 0;
    R_Width = 0;
    All_L_Loss = 0;
    All_R_Loss = 0;
    Final_Line = 0;
    Last_Line = 0;
    Last_Line_Flag = 0;
    L_Loss = 0;
    R_Loss = 0;
    First_L_Loss_Flag = 0;
    First_R_Loss_Flag = 0;
    /************************************/

    /*****************十字****************/
    L_Oblique_Cross_Flag = 0;
    R_Oblique_Cross_Flag = 0;
    Oblique_Cross_Line = 0;
    Direct_Cross_Flag = 0;
    Direct_Cross_Line = 0;
    L_Inflection_Line = 0;
    L_Inflection_Flag = 0;
    R_Inflection_Line = 0;
    R_Inflection_Flag = 0;
    Element_Cross = 0;
    UnCross_Flag = 0;
    Zheng_Cross_Flag = 0;
    /************************************/

    /*****************障碍****************/
    L_Obstacle_Line = 0;
    R_Obstacle_Line = 0;
    /************************************/

    /*****************环路****************/
    jiaRamp_Flag = 0;
    Loop_L_Max = 0;
    Loop_R_Max = 0;
    black_flag = 0;
    Loop_guai_flag = 0;
    Loop_L_Inflection_Line = 0;
    Loop_L_Inflection_Flag = 0;
    Loop_R_Inflection_Line = 0;
    Loop_R_Inflection_Flag = 0;
    Loop_L_guai = 0;
    Loop_R_guai = 0;
    R_Turning_Point_Flag = 0;
    L_Turning_Point_Flag = 0;

    Ring_Dir_Flag[3] = 1;
    Ring_Dir_Flag[4] = 1;
    Ring_Dir_Flag[5] = Ring_Dir_Flag[2];
    Ring_Dir_Flag[6] = 0;
    Ring_Dir_Flag[7] = 0;
    Ring_Dir_Flag[8] = 0;
    Ring_Dir_Flag[9] = 0;
    Loop_hei_flag = 0;
    Z_black_flag = 0;
    //    Ring_State_Flag = 0;
    //    Ring_Find_Flag = 0;
    /************************************/

    /*****************坡道****************/
    Ramp_New = 0;
    L_black_Temp = 0;
    R_black_Temp = 0;
    L_black_Memory1 = 0;
    R_black_Memory1 = 0;
    L_black_Memory2 = 0;
    R_black_Memory2 = 0;
    L_black_Slope1 = 0;
    L_black_Slope2 = 0;
    R_black_Slope1 = 0;
    R_black_Slope2 = 0;
    /************************************/
}
void Turning_Point(byte LineNum, byte Dir)
{
    int Scan_Length = 4;
    byte R_Max = 0, R_Max_Line = 0;
    byte L_Max = 200, L_Max_Line = 0;
    byte i = 0, j = 0;
    //Turning_Point_Flag= 0;
    //Dir为零时为右线
    if (LineNum > 3 && LineNum < Last_Line - 4)
    {
        if (Dir == 0 && R_black[LineNum] - 6 >= 0 && R_Turning_Point_Flag == 0)
        {
            if (R_black[LineNum] - R_black[LineNum + 1] > 8)
            {
                if ((Pixels[LineNum + 1][R_black[LineNum] - 3] != 0 && Pixels[LineNum + 2][R_black[LineNum] - 6] != 0))
                {
                    R_Max = R_black[LineNum];
                    R_Max_Line = LineNum;
                    R_Turning_Point_Flag = 1;
                    //setText用户自定义("R_Max_Line" + R_Max_Line + "_" + "R_Max" + R_Max);
                }
            }

            else if (R_black[LineNum] >= R_black[LineNum - 1] && R_black[LineNum] > R_black[LineNum - Scan_Length] && R_black[LineNum] > R_black[LineNum + Scan_Length])
            {
                for (i = (byte)(LineNum - Scan_Length); i <= LineNum + Scan_Length; i++)
                {
                    if (R_black[i] >= R_Max)
                    {
                        R_Max = R_black[i];
                        R_Max_Line = i;
                    }
                }
                if (R_Max == R_black[LineNum])
                {
                    if (Pixels[R_Max_Line + 4][R_black[R_Max_Line] - 6] != 0)
                    {
                        R_Turning_Point_Flag = 1;
                        //setText用户自定义("R_Max_Line" + R_Max_Line + "_" + "R_Max" + R_Max);
                    }
                }
            }
        }
        else if (Dir == 1 && L_black[LineNum] + 6 <= 199 && L_Turning_Point_Flag == 0)
        {
            if (L_black[LineNum + 1] - L_black[LineNum] > 8)
            {
                if ((Pixels[LineNum + 1][L_black[LineNum] + 3] != 0 && Pixels[LineNum + 2][L_black[LineNum] + 6] != 0))
                {
                    L_Max = L_black[LineNum];
                    L_Max_Line = LineNum;
                    L_Turning_Point_Flag = 1;
                    //setText用户自定义("L_Max_Line" + L_Max_Line + "_" + "L_Max" + L_Max);
                }
            }
            else if (L_black[LineNum] <= L_black[LineNum - 1] && L_black[LineNum] < L_black[LineNum - Scan_Length] && L_black[LineNum] < L_black[LineNum + Scan_Length])
            {
                for (i = (byte)(LineNum - Scan_Length); i <= LineNum + Scan_Length; i++)
                {
                    if (L_black[i] <= L_Max)
                    {
                        L_Max = L_black[i];
                        L_Max_Line = i;
                    }
                }
                if (L_Max == L_black[LineNum])
                {
                    if (Pixels[L_Max_Line + 4][R_black[L_Max_Line] + 6] != 0)
                    {
                        L_Turning_Point_Flag = 1;
                        //setText用户自定义("L_Max_Line" + L_Max_Line + "_" + "L_Max" + L_Max);
                    }
                }
            }
        }
    }
}
void Turning_Point_nei(byte LineNum, byte Dir)
{
    int Scan_Length = 4;
    byte R_Max = 0, R_Max_Line = 0;
    byte L_Max = 200, L_Max_Line = 0;
    byte i = 0, j = 0;
    //Turning_Point_Flag= 0;
    //Dir为零时为右线
    if (LineNum > 3 && LineNum < Last_Line - 4)
    {
        if (Dir == 0 && R_Turning_Point_Flag == 0)
        {
            if (R_black[LineNum] >= R_black[LineNum - 1] && R_black[LineNum] > R_black[LineNum - Scan_Length] && R_black[LineNum] > R_black[LineNum + Scan_Length])
            {
                for (i = (byte)(LineNum - Scan_Length); i <= LineNum + Scan_Length; i++)
                {
                    if (R_black[i] > R_Max)
                    {
                        R_Max = R_black[i];
                        R_Max_Line = i;
                    }
                }
                if (R_Max == R_black[LineNum])
                {
                    R_Max = R_black[LineNum];
                    R_Max_Line = LineNum;
                    R_Turning_Point_Flag = 1;
                    //setText用户自定义("R_Max_Line" + R_Max_Line + "_" + "R_Max" + R_Max);
                }
            }
        }
        else if (Dir == 1 && L_Turning_Point_Flag == 0)
        {
            if (L_black[LineNum] <= L_black[LineNum - 1] && L_black[LineNum] < L_black[LineNum - Scan_Length] && L_black[LineNum] < L_black[LineNum + Scan_Length])
            {
                for (i = (byte)(LineNum - Scan_Length); i <= LineNum + Scan_Length; i++)
                {
                    if (L_black[i] < L_Max)
                    {
                        L_Max = L_black[i];
                        L_Max_Line = i;
                    }
                }
                if (L_Max == L_black[LineNum])
                {
                    L_Max = L_black[LineNum];
                    L_Max_Line = LineNum;
                    L_Turning_Point_Flag = 1;
                    //setText用户自定义("L_Max_Line" + L_Max_Line + "_" + "L_Max" + L_Max);
                }
            }
        }
    }
}
byte Limit(int i) //限制越界
{
    if (i > 199)
    {
        i = 199;
        if (NoElement_Flag == 0)
            NoElement_Flag = 1;
    }
    else if (i < 0)
    {
        i = 0;
        if (NoElement_Flag == 0)
            NoElement_Flag = 1;
    }
    return (byte)i;
}
byte Track_Continuity_Determine(byte i) //赛道连续判断
{
    int L_Error, R_Error, Track_Continuity_Flag = 0, Continuity_Degree = 3;
    if (i > 3 && L_black[i] != 199 && R_black[i] != 0)
    {
        L_Error = (L_black[i] - L_black[i - 1]) - (L_black[i - 1] - L_black[i - 2]);
        R_Error = (R_black[i] - R_black[i - 1]) - (R_black[i - 1] - R_black[i - 2]);
        if (L_Error > -Continuity_Degree && L_Error < Continuity_Degree && R_Error > -Continuity_Degree && R_Error < Continuity_Degree)
            Track_Continuity_Flag = 1;
        else
            Track_Continuity_Flag = 0;
    }
    return (byte)Track_Continuity_Flag;
}
void Center_Scan(byte Line_Center, byte i) //本行中心扫线
{
    byte j;
    for (j = Line_Center; j <= 199; j++)
    {
        if (Pixels[i][j] == 0)
        {
            L_black[i] = j;
            break;
        }
        if (j == 199)
        {
            L_black[i] = 199;
            break;
        }
    }

    for (j = Line_Center; j >= 0; j--)
    {
        if (Pixels[i][j] == 0)
        {
            R_black[i] = j;
            break;
        }
        if (j == 0)
        {
            R_black[i] = 0;
            break;
        }
    }

    LCenter[i] = (byte)((L_black[i] + R_black[i]) >> 1);
}

void Edge_Scan(byte i) //完全贴边线扫线
{
    byte j, p;
    byte L_Scan_Row = 0, R_Scan_Row = 0;     //扫线用
    byte R_black_flag = 0, L_black_flag = 0; //黑点flag
    byte Z_black_Row = 0;

    if (i == 0)
    {
        if (find_l == 0 && find_r == 0)
        {
            find_l = 110;
            find_r = 90;
        }
        L_Scan_Row = find_l;
        R_Scan_Row = find_r;
    }
    else
    {
        L_Scan_Row = L_black[i - 1];
        R_Scan_Row = R_black[i - 1];
    }

    L_Scan_Row = Limit(L_Scan_Row);
    R_Scan_Row = Limit(R_Scan_Row);

    if (i == 69)
    {
        Last_Line_Flag = 1;
        Last_Line = 70;
    }

    if (Pixels[i][L_Scan_Row] == 0)
    {
        for (j = L_Scan_Row; j > 0; j--)
        {
            if (Pixels[i][j] > 0)
            {
                L_black[i] = (byte)(j + 1);
                break;
            }
            if (j == 1)
            {
                L_black[i] = 0;
                break;
            }
        }
    }
    else
    {
        if (L_Scan_Row == 199)
            L_black[i] = 199;
        else
        {
            for (j = L_Scan_Row; j < 199; j++)
            {
                if (Pixels[i][j] == 0)
                {
                    L_black[i] = j;
                    break;
                }
                if (j == 198)
                    L_black[i] = 199;
            }
        }
    }
    if (Pixels[i][R_Scan_Row] == 0)
    {
        for (j = R_Scan_Row; j < 199; j++)
        {
            if (Pixels[i][j] > 0)
            {
                R_black[i] = (byte)(j - 1);
                break;
            }
            if (j == 198)
                R_black[i] = 199;
        }
    }
    else
    {
        if (R_Scan_Row == 0)
            R_black[i] = 0;
        else
        {
            for (j = R_Scan_Row; j > 0; j--)
            {
                if (Pixels[i][j] == 0)
                {
                    R_black[i] = j;
                    break;
                }
                if (j == 1)
                {
                    R_black[i] = 0;
                    break;
                }
            }
        }
    }

    if (i > 3 && i < 58)
    {
        /***************疑似右拐点**********************/
        if ((R_black[i] - R_black[i - 1] <= 0 && R_black[i - 1] - R_black[i - 3] >= 0) && R_black[i - 1] - 6 >= 0) //有bug
        {
            if (Pixels[i + 2][R_black[i - 1] - 3] != 0 && Pixels[i + 3][R_black[i - 1] - 6] != 0)
            {
                /*****************判断为右拐点**************/
                if (Loop_R_Inflection_Flag == 0)
                {
                    Loop_R_Inflection_Flag = 1;
                    Loop_R_Inflection_Line = (byte)(i - 1);
                    //Text用户自定义("-" + Loop_R_Inflection_Line);
                }
            }
        }
        /***************疑似左拐点**********************/
        if (L_black[i] - L_black[i - 1] >= 0 && L_black[i - 1] - L_black[i - 3] <= 0 && L_black[i - 1] + 6 <= 199)
        {
            if (Pixels[i + 2][L_black[i - 1] + 3] != 0 && Pixels[i + 3][L_black[i - 1] + 6] != 0)
            {
                /*****************判断为左拐点**************/
                if (Loop_L_Inflection_Flag == 0)
                {
                    Loop_L_Inflection_Flag = 1;
                    Loop_L_Inflection_Line = (byte)(i - 1);
                    //Text用户自定义("-" + Loop_L_Inflection_Line);
                }
            }
        }
    }

    if (i < 60 && L_black[i] >= L_black[0] && R_black[i] <= R_black[0] && Z_black_flag == 0 && Element_Cross == 0 && Ring_Find_Flag == 0 && Ring_CD > 30 && R_Obstacle_Flag == 0 && L_Obstacle_Flag == 0 && L_black[i] - R_black[i] > 150) //环判断 左右线重新赋值
    {
        if (Loop_R_Inflection_Line > 0 && Loop_L_Inflection_Line > 0 && 40 > Loop_L_Inflection_Line && 40 > Loop_R_Inflection_Line && fabss(Loop_L_Inflection_Line, Loop_R_Inflection_Line) < 15)
        {
            for (j = (byte)(R_black[i] + 1); j <= L_black[i] - 1; j++)
            {
                if (Pixels[i][j] == 0 && Pixels[i][j + 1] == 0 && Pixels[i][j - 1] > 0 && R_black_flag == 0)
                {
                    RStart[i] = j;
                    R_black_flag = i;
                }

                if (Pixels[i][j] == 0 && Pixels[i][j - 1] == 0 && Pixels[i][j + 1] > 0 && L_black_flag == 0)
                {
                    LStart[i] = j;
                    L_black_flag = i;
                }

                if (L_black_flag > 0 && R_black_flag > 0 && fabss(LStart[i], RStart[i]) > 5)
                {
                    break;
                }
            }

            if (L_black_flag > 0 && R_black_flag > 0 && fabss(LStart[i], RStart[i]) > 5)
            {
                Z_black_Row = Limit((int)(((L_black[0] + R_black[0]) / 2) + (((L_black[MinNum(Loop_R_Inflection_Line, Loop_L_Inflection_Line)] + R_black[MinNum(Loop_R_Inflection_Line, Loop_L_Inflection_Line)]) / 2) - ((L_black[0] + R_black[0]) / 2)) * 1.0 * i / MinNum(Loop_R_Inflection_Line, Loop_L_Inflection_Line)));

                //Text用户自定义(Z_black_Row + "-" + i);
                if (Pixels[i][Z_black_Row] == 0 && Pixels[i + 1][Z_black_Row] == 0 && Pixels[i + 2][Z_black_Row] == 0)
                {
                    Loop_hei_flag++;
                    if (Loop_hei_flag >= 2)
                    {
                        if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 4)
                        {
                            L_black[i] = RStart[i];
                            Ring_Find_Flag = 1;
                            Ring_State_Flag = 1;
                            black_flag = i;
                        }
                        else if (Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3 || Ring_Dir_Flag[Ring_Dir_num] == 5)
                        {
                            R_black[i] = LStart[i];
                            Ring_Find_Flag = 1;
                            Ring_State_Flag = 1;
                            black_flag = i;
                        }
                    }
                }
            }
        }
        else if (Loop_R_Inflection_Line > 0 && Loop_L_Inflection_Line == 0 && 40 > Loop_R_Inflection_Line)
        {
            for (j = (byte)(R_black[i] + 1); j <= L_black[i] - 1; j++)
            {
                if (Pixels[i][j] == 0 && Pixels[i][j + 1] == 0 && Pixels[i][j - 1] > 0 && R_black_flag == 0)
                {
                    RStart[i] = j;
                    R_black_flag = i;
                }

                if (Pixels[i][j] == 0 && Pixels[i][j - 1] == 0 && Pixels[i][j + 1] > 0 && L_black_flag == 0)
                {
                    LStart[i] = j;
                    L_black_flag = i;
                }

                if (L_black_flag > 0 && R_black_flag > 0 && fabss(LStart[i], RStart[i]) > 5)
                {
                    break;
                }
            }

            if (L_black_flag > 0 && R_black_flag > 0 && fabss(LStart[i], RStart[i]) > 5)
            {
                Z_black_Row = Limit((int)(((L_black[0] + R_black[0]) / 2) + (R_black[Loop_R_Inflection_Line] - R_black[0]) * 1.0 * i / Loop_R_Inflection_Line));

                //Text用户自定义(Z_black_Row + "-" + i);
                if (Pixels[i][Z_black_Row] == 0 && Z_black_Row < 199 && Pixels[i + 1][Z_black_Row] == 0 && Pixels[i + 2][Z_black_Row] == 0)
                {
                    Loop_hei_flag++;
                    if (Loop_hei_flag >= 2)
                    {
                        if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 4)
                        {
                            L_black[i] = RStart[i];
                            Ring_Find_Flag = 1;
                            Ring_State_Flag = 1;
                            black_flag = i;
                        }
                        else if (Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3 || Ring_Dir_Flag[Ring_Dir_num] == 5)
                        {
                            R_black[i] = LStart[i];
                            Ring_Find_Flag = 1;
                            Ring_State_Flag = 1;
                            black_flag = i;
                        }
                    }
                }
            }
        }
        else if (Loop_R_Inflection_Line == 0 && Loop_L_Inflection_Line > 0 && 40 > Loop_L_Inflection_Line)
        {
            for (j = (byte)(R_black[i] + 1); j <= L_black[i] - 1; j++)
            {
                if (Pixels[i][j] == 0 && Pixels[i][j + 1] == 0 && Pixels[i][j - 1] > 0 && R_black_flag == 0)
                {
                    RStart[i] = j;
                    R_black_flag = i;
                }

                if (Pixels[i][j] == 0 && Pixels[i][j - 1] == 0 && Pixels[i][j + 1] > 0 && L_black_flag == 0)
                {
                    LStart[i] = j;
                    L_black_flag = i;
                }

                if (L_black_flag > 0 && R_black_flag > 0 && fabss(LStart[i], RStart[i]) > 5)
                {
                    break;
                }
            }

            if (L_black_flag > 0 && R_black_flag > 0 && fabss(LStart[i], RStart[i]) > 5)
            {
                Z_black_Row = Limit((int)(((L_black[0] + R_black[0]) / 2) + (L_black[Loop_L_Inflection_Line] - L_black[0]) * 1.0 * i / Loop_L_Inflection_Line));

                //Text用户自定义(Z_black_Row + "-" + i);
                if (Pixels[i][Z_black_Row] == 0 && Z_black_Row > 0 && Pixels[i + 1][Z_black_Row] == 0 && Pixels[i + 2][Z_black_Row] == 0)
                {
                    Loop_hei_flag++;
                    if (Loop_hei_flag >= 2)
                    {
                        if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 4)
                        {
                            L_black[i] = RStart[i];
                            Ring_Find_Flag = 1;
                            Ring_State_Flag = 1;
                            black_flag = i;
                        }
                        else if (Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3 || Ring_Dir_Flag[Ring_Dir_num] == 5)
                        {
                            R_black[i] = LStart[i];
                            Ring_Find_Flag = 1;
                            Ring_State_Flag = 1;
                            black_flag = i;
                        }
                    }
                }
                else if (Z_black_Row == 199)
                {
                    Z_black_flag = 1;
                }
            }
        }
    }

    else if (i < 60 && Ring_State_Flag > 0)
    {
        for (j = (byte)(R_black[i] + 1); j <= L_black[i] - 1; j++)
        {
            if (Pixels[i][j] == 0 && Pixels[i][j + 1] == 0 && Pixels[i][j - 1] > 0)
            {
                RStart[i] = j;
                R_black_flag = i;
            }

            if (Pixels[i][j] == 0 && Pixels[i][j - 1] == 0 && Pixels[i][j + 1] > 0)
            {
                LStart[i] = j;
                L_black_flag = i;
            }

            if (L_black_flag > 0 && R_black_flag > 0 && LStart[i] - RStart[i] > 5 && Ring_State_Flag >= 3 && Pixels[i + 2][(L_black[i] + LStart[i]) / 2] > 0 && Pixels[i + 2][(R_black[i] + RStart[i]) / 2] > 0)
            {
                if ((Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 4) && black_flag == 0 && RStart[i] - R_black[i] > 5)
                {
                    L_black[i] = RStart[i];
                    black_flag = i;
                }
                else if ((Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3 || Ring_Dir_Flag[Ring_Dir_num] == 5) && black_flag == 0 && L_black[i] - LStart[i] > 5)
                {
                    R_black[i] = LStart[i];
                    black_flag = i;
                }
            }
            else if (L_black_flag > 0 && R_black_flag > 0 && LStart[i] - RStart[i] > 5 && Ring_State_Flag <= 2)
            {
                if ((Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 4) && black_flag == 0 && RStart[i] - R_black[i] > 5)
                {
                    L_black[i] = RStart[i];
                    black_flag = i;
                }
                else if ((Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3 || Ring_Dir_Flag[Ring_Dir_num] == 5) && black_flag == 0 && L_black[i] - LStart[i] > 5)
                {
                    R_black[i] = LStart[i];
                    black_flag = i;
                }
            }
        }
    }

    LCenter[i] = (byte)((L_black[i] + R_black[i]) >> 1);
    if (L_black[i] - R_black[i] <= 3)
    {
        Last_Line_Flag = 1;
        Last_Line = i;
    }
}

void Bend_Repair(byte i) //弯道补线
{
    if (i == 0 && L_black[i] == 199)
        First_L_Loss_Flag = 1;
    if (i == 0 && R_black[i] == 0)
        First_R_Loss_Flag = 1;
    if (L_black[i] != 199 && R_black[i] != 0)
    {
        R_Loss = 0;
        L_Loss = 0;
    }
    if (L_black[i] == 199 && R_black[i] != 0)
    {
        if (L_Loss == 0) //确定补线宽度
        {
            L_Loss++;
            All_L_Loss++;
            if (i == 0)
                L_Width = (uint8_t)((L_black[i] - R_black[i]) * 0.5);
            else
            {

                L_Width = (byte)((L_black[i - 1] - R_black[i - 1]) * 0.5);
                LCenter[i] = Limit((int)(R_black[i] + L_Width));
                // LCenter[i] = Limit((byte)(R_black[i] + L_Width));
            }
        }
        else
        {
            L_Loss++;
            All_L_Loss++;
            LCenter[i] = Limit((int)(R_black[i] + L_Width));
        }
    }
    else if (R_black[i] == 0 && L_black[i] != 199)
    {
        if (R_Loss == 0) //确定补线宽度
        {
            R_Loss++;
            All_R_Loss++;
            if (i == 0)
                R_Width = (uint8_t)((L_black[i] - R_black[i]) * 0.5);
            else
            {
                R_Width = (byte)((L_black[i - 1] - R_black[i - 1]) * 0.5);
                LCenter[i] = Limit((int)(L_black[i] - R_Width));
            }
        }
        else
        {
            R_Loss++;
            All_R_Loss++;
            LCenter[i] = Limit((int)(L_black[i] - R_Width));
        }
    }
}
void Cross_Determine(byte i) //十字判定//只扫到一个尖角线补不好//斜入十字时如果上面未搜到白块则截断
{
    byte Center_Row = 0;
    byte Center_Line = 0;
    float L_K = 0;
    float R_K = 0;
    byte j = 0;
    byte Cross_Repair_Flag = 0;
    byte Direct_Cross_Flag_Temp = 0;
    byte Oblique_Cross_Flag_Temp = 0;
    byte Track_Continuity_Count = 0;

    if (Ring_Find_Flag == 0)
    {
        if (i > 2 && i < 58 && UnCross_Flag == 0)
        {
            /***************疑似右拐点**********************/
            if ((R_black[i] - R_black[i - 1] < 0 && R_black[i - 1] - R_black[i - 3] >= 0) && R_black[i - 1] - 6 >= 0) //有bug
            {
                if (Pixels[i + 2][R_black[i - 1] - 3] != 0 && Pixels[i + 3][R_black[i - 1] - 6] != 0)
                {
                    /*****************判断为右拐点**************/
                    if (R_Inflection_Flag == 0)
                    {
                        R_Inflection_Flag = 1;
                        R_Inflection_Line = (byte)(i - 1);
                        //setText用户自定义("右拐点" + R_Inflection_Line);
                    }
                    /*****************判断为向左走十字**************/
                    if (L_black[i - 1] == 199 && L_Oblique_Cross_Flag == 0)
                    {
                        if (i - 1 <= 50)
                        {
                            L_Oblique_Cross_Flag = 1;
                            UnCross_Flag = 1;
                            Oblique_Cross_Line = (byte)(i - 1);
                        }
                    }
                }
            }
            /***************疑似左拐点**********************/
            if (L_black[i] - L_black[i - 1] > 0 && L_black[i - 1] - L_black[i - 3] <= 0 && L_black[i - 1] + 6 <= 199)
            {
                if (Pixels[i + 2][L_black[i - 1] + 3] != 0 && Pixels[i + 3][L_black[i - 1] + 6] != 0)
                {
                    /*****************判断为左拐点**************/
                    if (L_Inflection_Flag == 0)
                    {
                        L_Inflection_Flag = 1;
                        L_Inflection_Line = (byte)(i - 1);
                        //setText用户自定义("左拐点" + L_Inflection_Line);
                    }
                    /*****************判断为向右走十字**************/
                    if (R_black[i - 1] == 0 && R_Oblique_Cross_Flag == 0)
                    {
                        if (i - 1 <= 50)
                        {
                            R_Oblique_Cross_Flag = 1;
                            UnCross_Flag = 1;
                            Oblique_Cross_Line = (byte)(i - 1);
                        }
                    }
                }
            }
        }
        /************************出十字记忆******************************/
        if (R_Oblique_Cross_Flag == 0 && L_Oblique_Cross_Flag == 0 && UnCross_Flag == 0)
        {
            if (Direct_Cross_Field_Count == 1 && i == 0) //出十字记忆
            {
                if (R_black[0] == 0 || L_black[0] == 199)
                {
                    Direct_Cross_Flag = 1;
                    Direct_Cross_Line = i;
                }
                else
                {
                    Direct_Cross_Field_Count = 0;
                }
            }
            /************************斜入直入******************************/
            if (i == 6 && R_black[i] == 0 && L_black[6] - L_black[0] > 0)
            {
                if (L_black[6] - L_black[3] > 0 && L_black[5] - L_black[2] > 0 && L_black[4] - L_black[1] > 0)
                {
                    //st用户自定义("斜入直入十字往右" + i);
                    Direct_Cross_Flag = 1;
                    Direct_Cross_Line = i;
                }
            }

            else if (i == 6 && L_black[i] == 199 && R_black[6] - R_black[0] < 0)
            {
                if (R_black[6] - R_black[3] < 0 && R_black[5] - R_black[2] < 0 && R_black[4] - R_black[1] < 0)
                {
                    //st用户自定义("斜入直入十字往左" + i);
                    Direct_Cross_Flag = 1;
                    Direct_Cross_Line = i;
                }
            }
            /************************全白直入******************************/
            if (R_black[i] == 0 && L_black[i] == 199 && i < 50 && Direct_Cross_Flag == 0 && R_Oblique_Cross_Flag == 0 && L_Oblique_Cross_Flag == 0)
            {
                Direct_Cross_Flag = 1;
                Direct_Cross_Line = i;
            }
        }

        /************************计算十字搜线行***************************/
        if (R_Oblique_Cross_Flag == 1)
        {
            if (R_Inflection_Flag == 1 && R_Inflection_Line < Oblique_Cross_Line)
            {
                Center_Row = Limit((int)(LCenter[R_Inflection_Line] - (L_black[R_Inflection_Line] - L_black[Oblique_Cross_Line])));
                Center_Line = R_Inflection_Line;
            }
            else if (R_Inflection_Flag == 0)
            {
                Center_Row = LCenter[Oblique_Cross_Line];
                Center_Line = Oblique_Cross_Line;
                Oblique_Cross_Flag_Temp = 1;
            }
        }

        else if (L_Oblique_Cross_Flag == 1)
        {
            if (L_Inflection_Flag == 1 && L_Inflection_Line < Oblique_Cross_Line)
            {
                Center_Row = Limit((int)(LCenter[L_Inflection_Line] + (R_black[Oblique_Cross_Line] - R_black[L_Inflection_Line])));
                Center_Line = L_Inflection_Line;
            }
            else if (L_Inflection_Flag == 0)
            {
                Center_Row = LCenter[Oblique_Cross_Line];
                Center_Line = Oblique_Cross_Line;
                Oblique_Cross_Flag_Temp = 1;
            }
        }

        else if (Direct_Cross_Flag == 1)
        {
            UnCross_Flag = 1;
            if (R_Inflection_Flag == 1 && L_Inflection_Flag == 1) //判断补线起始行
            {
                if (L_Inflection_Line < R_Inflection_Line)
                {
                    Center_Line = L_Inflection_Line;
                }
                else
                {
                    Center_Line = R_Inflection_Line;
                }
                if (Center_Line > Direct_Cross_Line)
                {
                    Center_Line = Direct_Cross_Line;
                }
                Center_Row = LCenter[Center_Line];
            }
            else if (R_Inflection_Flag == 1 && L_Inflection_Flag == 0)
            {
                if (R_Inflection_Line < Direct_Cross_Line)
                {
                    Center_Line = R_Inflection_Line;
                }
                else
                {
                    Center_Line = Direct_Cross_Line;
                }
                Center_Row = LCenter[Center_Line];
            }
            else if (R_Inflection_Flag == 0 && L_Inflection_Flag == 1)
            {
                if (L_Inflection_Line < Direct_Cross_Line)
                {
                    Center_Line = L_Inflection_Line;
                }
                else
                {
                    Center_Line = Direct_Cross_Line;
                }

                Center_Row = LCenter[Center_Line];
            }
            else if (R_Inflection_Flag == 0 && L_Inflection_Flag == 0) //正入行以下无拐点
            {
                Direct_Cross_Flag_Temp = 1;
                Center_Line = Direct_Cross_Line;
                Center_Row = Mid;
            }

            for (i = (byte)(Direct_Cross_Line + 1); i < 70; i++) //搜索起始行为正入十字行+1
            {
                if (Pixels[i][Center_Row] > 0)
                {
                    Center_Scan(Center_Row, i);
                    if (L_black[i] != 199 && R_black[i] != 0 && L_black[i] - R_black[i] < 120 && Track_Continuity_Determine(i) == 1)
                    {
                        Track_Continuity_Count++;
                        if (Track_Continuity_Count == 4)
                        {
                            Cross_Repair_Flag = 1;
                            if (Direct_Cross_Line == 0)
                                Direct_Cross_Field_Count = 1;
                            if (i == 69)
                            {
                                Last_Line_Flag = 1;
                                Last_Line = 70;
                            }
                            break;
                        }
                    }
                    else if (i == 69)
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            /************************直入十字补线***************************/
            if (Cross_Repair_Flag == 1)
            {
                Element_Cross = 1;
                if (Direct_Cross_Flag_Temp == 1)
                {
                    L_Loss = 0;
                    R_Loss = 0;
                    for (j = 0; j < i - 4; j++)
                    {
                        L_black[j] = L_black[i - 4];
                        R_black[j] = R_black[i - 4];
                        LCenter[j] = (byte)((R_black[j] + L_black[j]) >> 1);
                        Bend_Repair(j);
                    }
                }
                else
                {
                    L_K = (float)(L_black[i] - L_black[Center_Line]) / (float)(i - Center_Line);
                    R_K = (float)(R_black[i] - R_black[Center_Line]) / (float)(i - Center_Line);
                    for (j = Center_Line; j <= i; j++)
                    {
                        L_black[j] = Limit((int)(L_black[Center_Line] + L_K * (j - Center_Line)));
                        R_black[j] = Limit((int)(R_black[Center_Line] + R_K * (j - Center_Line)));
                        LCenter[j] = (byte)((R_black[j] + L_black[j]) >> 1);
                    }
                }
                RowNum = i; //跳到从补线结束行
            }
            Direct_Cross_Flag = 0;
            R_Inflection_Flag = 0;
            L_Inflection_Flag = 0;
        }

        if (R_Oblique_Cross_Flag == 1 || L_Oblique_Cross_Flag == 1)
        {
            for (i = (byte)(Oblique_Cross_Line + 1); i < 70; i++)
            {
                if (Pixels[i][Center_Row] > 0)
                {
                    Center_Scan((byte)Center_Row, (byte)i);
                    if (R_black[i] >= R_black[Center_Line] && L_black[i] < L_black[Center_Line] && R_Oblique_Cross_Flag == 1)
                    {
                        Track_Continuity_Count++;
                        if (Track_Continuity_Count == 3)
                        {
                            //st用户自定义("RCenter1" + i);
                            Cross_Repair_Flag = 1;
                            if (i == 69)
                            {
                                Last_Line_Flag = 1;
                                Last_Line = 70;
                            }
                            break;
                        }
                    }
                    else if (R_black[i] > R_black[Center_Line] && L_black[i] <= L_black[Center_Line] && L_Oblique_Cross_Flag == 1)
                    {
                        Track_Continuity_Count++;
                        if (Track_Continuity_Count == 1)
                        {
                            //st用户自定义("LCenter1" + i);
                            Cross_Repair_Flag = 1;
                            if (i == 69)
                            {
                                Last_Line_Flag = 1;
                                Last_Line = 70;
                            }
                            break;
                        }
                    }

                    else if (i == 69)
                    {
                        Last_Line_Flag = 1;
                        Last_Line = Oblique_Cross_Line;
                        break;
                    }
                }
                else
                {
                    //                   if (i < 65 && Ring_Find_Flag == 0 && Ring_Dir_num < 1)
                    //                    {
                    //                        Ring_Find_Flag = 1;
                    //                        Ring_State_Flag = 1;
                    //                        //setText用户自定义("十字发现环");
                    //                    }
                    //                    break;
                    break;
                }
            }
            if (Cross_Repair_Flag == 1)
            {
                Element_Cross = 1;

                if (R_black[i] - 0 > 10 && Oblique_Cross_Flag_Temp == 1 && R_Oblique_Cross_Flag == 1)
                {
                    //setText用户自定义("Oblique_Cross_Flag_Temp2R");
                    L_K = (float)(L_black[i] - L_black[Center_Line]) / (float)(i - Center_Line);
                    R_K = (float)(R_black[i] - R_black[Center_Line / 2]) / (float)(i - Center_Line / 2);
                    for (j = Center_Line; j <= i; j++)
                    {
                        L_black[j] = Limit((int)(L_black[Center_Line] + L_K * (j - Center_Line)));
                    }
                    if (R_black[0] == 0 || R_black[5] == 0 || R_black[10] == 0)
                    {
                        for (j = 0; j <= i; j++)
                        {
                            R_black[j] = R_black[i];
                            LCenter[j] = (byte)((R_black[j] + L_black[j]) >> 1);
                            Bend_Repair((byte)j);
                        }
                    }
                    else
                    {
                        for (j = (byte)(Center_Line / 2); j <= i; j++)
                        {
                            R_black[j] = Limit((int)(R_black[Center_Line / 2] + R_K * (j - Center_Line / 2)));
                            LCenter[j] = (byte)((R_black[j] + L_black[j]) >> 1);
                            Bend_Repair((byte)j);
                        }
                    }

                    // R_K = (float)(R_black[i] - R_black[i - 3]) / (float)(3);

                    //for (j = 0; j <= i; j++)
                    //{
                    //    R_black[j] = R_black[i];
                    //    LCenter[j] = (byte)((R_black[j] + L_black[j]) >> 1);
                    //    Bend_Repair((byte)j);
                    //}
                }

                else if (199 - L_black[i] > 10 && Oblique_Cross_Flag_Temp == 1 && L_Oblique_Cross_Flag == 1)
                {
                    //setText用户自定义("Oblique_Cross_Flag_Temp2L");
                    L_K = (float)(L_black[i] - L_black[Center_Line / 2]) / (float)(i - Center_Line / 2);
                    R_K = (float)(R_black[i] - R_black[Center_Line]) / (float)(i - Center_Line);
                    for (j = Center_Line; j <= i; j++)
                    {
                        R_black[j] = Limit((int)(R_black[Center_Line] + R_K * (j - Center_Line)));
                    }
                    if (L_black[0] == 199 || L_black[5] == 199 || L_black[10] == 199)
                    {
                        for (j = 0; j <= i; j++)
                        {
                            L_black[j] = L_black[i];
                            LCenter[j] = (byte)((R_black[j] + L_black[j]) >> 1);
                            Bend_Repair((byte)j);
                        }
                    }
                    else
                    {
                        for (j = (byte)(Center_Line / 2); j <= i; j++)
                        {
                            L_black[j] = Limit((int)(L_black[Center_Line / 2] + L_K * (j - Center_Line / 2)));
                            LCenter[j] = (byte)((R_black[j] + L_black[j]) >> 1);
                            Bend_Repair((byte)j);
                        }
                    }

                    //for (j = 0; j <= i; j++)
                    //{
                    //    L_black[j] = L_black[i];
                    //    LCenter[j] = (byte)((R_black[j] + L_black[j]) >> 1);
                    //    Bend_Repair((byte)j);
                    //}
                }
                else
                {
                    L_K = (float)(L_black[i] - L_black[Center_Line]) / (float)(i - Center_Line);
                    R_K = (float)(R_black[i] - R_black[Center_Line]) / (float)(i - Center_Line);
                    for (j = Center_Line; j <= i; j++)
                    {
                        L_black[j] = Limit((int)(L_black[Center_Line] + L_K * (j - Center_Line)));
                        R_black[j] = Limit((int)(R_black[Center_Line] + R_K * (j - Center_Line)));
                        LCenter[j] = (byte)((R_black[j] + L_black[j]) >> 1);
                        Bend_Repair((byte)j);
                    }
                }
                RowNum = i;
            }
            R_Inflection_Flag = 0;
            R_Oblique_Cross_Flag = 0;
            L_Inflection_Flag = 0;
            L_Oblique_Cross_Flag = 0;

            Bend_Repair(RowNum); //弯道补线
        }
    }
}
void Starting_Line_Determine(byte i) //起跑线判定
{
    byte j;
    byte Jump_Count = 0;
    if ((i == 10 || i == 4) && L_black[i] != 199 && R_black[i] != 0)
    {
        for (j = R_black[i]; j < L_black[i]; j++)
        {
            if (Pixels[i][j + 1] != Pixels[i][j])
            {
                Jump_Count++;
            }
            if (Jump_Count > 10)
            {
                Starting_Line_Flag = 1;
            }
        }
    }
}
void ImageProcess() //图像行处理
{
    Edge_Scan(RowNum); //边缘扫线
    if (Accer_Folloew_Flag == 1)
    {
        if (Last_Line_Flag == 0) //所在行有效
        {

            if (Time_Clock_5Ms > 2000 && Start_Open == Ring_Dir_num && Start_Open > 0)
                Starting_Line_Determine(RowNum); //起跑线
            Bend_Repair(RowNum);                 //弯道补线
            if (NoElement_Flag == 0)
            {
                if (Time_Clock_5Ms > 200)
                {
                    Cross_Determine(RowNum); //十字
                }
            }
            /*********************采集元素******************************/
            if (RowNum > 5 && RowNum < 66)
            {
                if (L_black[RowNum] >= L_black[0] && R_black[RowNum] <= R_black[0] && jiaRamp_Flag == 0)
                {
                    jiaRamp_Flag = 1;
                }
            }
        }
    }
}
void FieldProcess() //图像场处理函数内联
{
    byte i, j, p;
    byte xiaocao = 0, xiaocao_k = 0; //小草 斜率
    byte L_Obstacle_Last_Line = 0, R_Obstacle_Last_Line = 0;
    byte Loop_L_Line = 0, Loop_R_Line = 0, Loop_L_Min = 199, Loop_R_Min = 0; //环处理
    byte black_new_line = 0, black_new_line_x = 0;
    byte state2_tiao = 0;

    Final_Line = Last_Line;

    if (Accer_Folloew_Flag == 1)
    {
        /********************小草算法************************/
        for (i = 0; i < Last_Line; i++)
        {
            for (j = 0; j < i; j++)
            {
                xiaocao = (byte)((LCenter[0] - (LCenter[0] - LCenter[i]) * j / i));
                if (LCenter[j] > xiaocao + 5 || LCenter[j] + 5 < xiaocao)
                    break;
            }
            if (i == j)
            {
                xiaocao = i;
            }
            else
            {
                xiaocao = j;
                break;
            }
        }
        if (xiaocao != 0)
        {
            if (LCenter[xiaocao] - LCenter[0] > 0)
            {
                xiaocao_k = (byte)((LCenter[xiaocao] - LCenter[0]) * 10 / xiaocao);
            }
            else
            {
                xiaocao_k = (byte)((LCenter[0] - LCenter[xiaocao]) * 10 / xiaocao);
            }
        }
        /********************截断行************************/
        for (i = 0; i < Last_Line; i++)
        {
            //补到199或0时截断
            if (LCenter[i] == 199 || LCenter[i] == 0) //截断行
            {
                Final_Line = (byte)(i);
                break;
            }
            else
                Final_Line = Last_Line;
            //在非障碍时回弯拉回或者截断
            if (L_Obstacle_Flag == 0 && R_Obstacle_Flag == 0)
            {
                if (i > 0 && (L_black[i - 1] == 199 || R_black[i - 1] == 0) && L_black[i] != 199 && R_black[i] != 0) //过滤回弯
                {
                    if (Last_Line - i > 20)
                    {
                        for (j = 0; j < i; j++)
                        {
                            LCenter[j] = (byte)((L_black[j] + R_black[j]) >> 1);
                        }
                    }
                    else
                    {
                        Final_Line = i;
                        break;
                    }
                }
            }
        }

        if (Time_Clock_5Ms > 200)
        {

            /********************障碍************************/
            if (1)
            {
                //                L_Obstacle_Last_Line = cjb(0, 4, 1);
                //            R_Obstacle_Last_Line = cjb(0, 4, 0);
                if (Final_Line > 55 && L_Obstacle_Flag == 0 && R_Obstacle_Flag == 0 && jiaRamp_Flag == 0)
                {
                    for (i = 5; i < Final_Line; i++)
                    {
                        if (L_black[i - 5] >= L_black[i] && R_black[i - 5] <= R_black[i])
                        {
                            if (Pixels[i][((L_black[i] + LCenter[i]) >> 1)] == 0)
                            {
                                for (p = (byte)((L_black[i] + LCenter[i]) >> 1); p < L_black[i]; p++)
                                {
                                    if (Pixels[i][p] > 0)
                                    {
                                        Obstacle_L_Line = p;
                                        break;
                                    }
                                }
                                for (p = (byte)((L_black[i] + LCenter[i]) >> 1); p > LCenter[i]; p--)
                                {
                                    if (Pixels[i][p] > 0)
                                    {
                                        Obstacle_R_Line = p;
                                        break;
                                    }
                                }
                                if (Obstacle_R_Line > 0 && Obstacle_L_Line > 0 && (Obstacle_L_Line - Obstacle_R_Line) * 4.4 > (L_black[i] - R_black[i])) // && R_Obstacle_Last_Line > p - 5 && L_Obstacle_Last_Line > p - 5)
                                {
                                    L_Obstacle_Line++;
                                }
                                //                    else
                                //                    {
                                //                        break;
                                //                    }
                            }
                            else if (Pixels[i][((R_black[i] + LCenter[i]) >> 1)] == 0)
                            {
                                for (p = (byte)((R_black[i] + LCenter[i]) >> 1); p < LCenter[i]; p++)
                                {
                                    if (Pixels[i][p] > 0)
                                    {
                                        Obstacle_L_Line = p;
                                        break;
                                    }
                                }
                                for (p = (byte)((R_black[i] + LCenter[i]) >> 1); p > R_black[i]; p--)
                                {
                                    if (Pixels[i][p] > 0)
                                    {
                                        Obstacle_R_Line = p;
                                        break;
                                    }
                                }
                                if (Obstacle_R_Line > 0 && Obstacle_L_Line > 0 && (Obstacle_L_Line - Obstacle_R_Line) * 4.4 > (L_black[i] - R_black[i])) // && R_Obstacle_Last_Line > p - 5 && L_Obstacle_Last_Line > p - 5)
                                {
                                    R_Obstacle_Line++;
                                }
                                //                    else
                                //                    {
                                //                        break;
                                //                    }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                if (L_Obstacle_Line >= 5)
                {
                    L_Obstacle_Line = 0;
                    L_Obstacle_Flag = 1;
                }
                else if (R_Obstacle_Line >= 5)
                {
                    R_Obstacle_Line = 0;
                    R_Obstacle_Flag = 1;
                }

                if (L_Obstacle_Flag == 1)
                {
                    if (Pixels[0][((L_black[0] + LCenter[0]) >> 1)] == 0) //|| ((Kuan_First-(L_black [0]-R_black [0])>=15)&&L_black[0]!=199))
                    {
                        L_Obstacle_Flag = 2;
                    }
                }
                else if (L_Obstacle_Flag == 2)
                {
                    for (p = (byte)(R_black[0] + 1); p <= L_black[0]; p++)
                    {
                        if (Pixels[0][p] == 0 || p == 199)
                        {
                            Obstacle_Wide = (byte)(p - R_black[0]);
                            break;
                        }
                    }

                    if (Obstacle_Wide_Last > 0 && Obstacle_Wide_Last < (Obstacle_Wide - 8))
                    {
                        L_Obstacle_Flag = 3;
                        Obstacle_Wide_Last = 0;
                    }
                    //setText?????("-" + Obstacle_Wide_Last + "- " + Obstacle_Wide);
                    Obstacle_Wide_Last = Obstacle_Wide;
                }
                else if (L_Obstacle_Flag == 3)
                {
                    L_Obstacle_Count++;
                    if (L_Obstacle_Count == 3)
                    {
                        Obstacle_num++;
                        L_Obstacle_Count = 0;
                        L_Obstacle_Flag = 0;
                    }
                }

                if (R_Obstacle_Flag == 1)
                {
                    if (Pixels[0][((R_black[0] + LCenter[0]) >> 1)] == 0) //|| ((Kuan_First-(L_black [0]-R_black [0])>=15)&&R_black[0]!=0))
                    {
                        R_Obstacle_Flag = 2;
                    }
                }
                else if (R_Obstacle_Flag == 2)
                {
                    for (p = (byte)(L_black[0] - 1); p >= R_black[0]; p--)
                    {
                        if (Pixels[0][p] == 0 || p == 0)
                        {
                            Obstacle_Wide = (byte)(L_black[0] - p);
                            break;
                        }
                    }
                    if (Obstacle_Wide_Last > 0 && Obstacle_Wide_Last < (Obstacle_Wide - 8))
                    {
                        R_Obstacle_Flag = 3;
                        Obstacle_Wide_Last = 0;
                    }
                    Obstacle_Wide_Last = Obstacle_Wide;
                }
                else if (R_Obstacle_Flag == 3)
                {
                    R_Obstacle_Count++;
                    if (R_Obstacle_Count == 3)
                    {
                        Obstacle_num++;
                        R_Obstacle_Count = 0;
                        R_Obstacle_Flag = 0;
                    }
                }

                //障碍补线
                for (i = 0; i < Final_Line; i++)
                {
                    if (L_Obstacle_Flag > 0)
                    {
                        LCenter[i] = Limit((int)((L_black[i] - R_black[i]) / 3 + R_black[i]));
                    }
                    else if (R_Obstacle_Flag > 0)
                    {
                        LCenter[i] = Limit((int)(L_black[i] - (L_black[i] - R_black[i]) / 3));
                    }
                }
            }
            /******************类型*********************/
            if (xiaocao_k < 6 && Final_Line > 50)
            {
                Element_Flag = 1;
            }
            //    else
            //    {
            //        Small_S_Count = 0;
            //        Element_Flag = 2; //弯道
            //    }
            else
            {
                if (L_black[0] < 199 && R_black[0] > 0 && Final_Line > 20 && Final_Line < 45 && Last_Line - Final_Line < 10 && Ramp_Flag == 0)
                {

                    Element_Flag = 3;
                }
                // setText用户自定义("RU弯道");
                else
                {

                    Small_S_Count = 0;
                    Element_Flag = 2; //弯道
                }
                // setText用户自定义("zcw");
            }

            if (xiaocao_k > 4 && xiaocao_k < 10 && Final_Line > 65)
            {
                Small_S_Count++;
                if (Small_S_Count > 6)
                    SmallS_Flag = 1;
            }
            if (Final_Line < 65 && SmallS_Flag == 1)
            {
                Small_S_Count = 0;
                SmallS_Flag = 0;
            }

            if (L_Obstacle_Flag != 0 && R_Obstacle_Flag != 0)
            {
                Small_S_Count = 0;
                SmallS_Flag = 0;
            }
            //******************坡道***********************************/
            if ((Ramp_Choose > 0 && Last_Line > 50 && xiaocao_k < 4 && L_black[0] < 199 && R_black[0] > 1 && Ramp_Flag == 0 && Element_Cross == 0 && Ring_Find_Flag == 0 && jiaRamp_Flag == 0) || Ramp_Flag > 0)
            {
                //判断第几行为有效直道行
                for (j = 0; j < Final_Line - 1; j++)
                {
                    for (i = 0; i < j; i++)
                    {
                        L_black_Temp = (byte)(L_black[0] - (L_black[0] - L_black[j]) * i / j);
                        if (L_black[i] > L_black_Temp + 2 || L_black[i] + 2 < L_black_Temp)
                            break;
                    }
                    if (i == j)
                    {
                        L_black_Memory1 = j;
                    }
                    else
                    {
                        break;
                    }
                }
                L_black_Slope1 = (float)((L_black[L_black_Memory1] - L_black[0]) * 1.0 / L_black_Memory1);
                for (j = L_black_Memory1; j < Final_Line - 1; j++)
                {
                    for (i = L_black_Memory1; i < j; i++)
                    {
                        L_black_Temp = (byte)(L_black[L_black_Memory1] - (L_black[L_black_Memory1] - L_black[j]) * (i - L_black_Memory1) / (j - L_black_Memory1));
                        if (L_black[i] > L_black_Temp + 2 || L_black[i] + 2 < L_black_Temp)
                            break;
                    }
                    if (i == j)
                    {
                        L_black_Memory2 = j;
                    }
                    else
                    {
                        break;
                    }
                }
                if (L_black_Memory2 > L_black_Memory1)
                {
                    L_black_Slope2 = (float)((L_black[L_black_Memory2] - L_black[L_black_Memory1]) * 1.0 / (L_black_Memory2 - L_black_Memory1));
                    if (Ramp_Flag == 0 && L_black_Memory1 > 20)
                    {
                        //setText用户自定义("-" + L_black_Memory1 + "-" + L_black_Memory2 + "-" + L_black_Slope1 + "-" + L_black_Slope2);
                        if (L_black_Slope2 > L_black_Slope1 + Ramp_Down_Num * 0.01 && L_black_Slope2 < L_black_Slope1 + Ramp_Up_Num * 0.01 && Ramp_Flag == 0 && L_black_Memory2 - L_black_Memory1 > 14)
                        {
                            Ramp_New++;
                            //setText用户自定义("满足1");
                        }
                    }
                    else if (Ramp_Flag == 1 && L_black_Memory2 - L_black_Memory1 < 4 && L_black_Memory2 < 28)
                    {
                        //setText用户自定义("-" + L_black_Memory1 + "-" + L_black_Memory2 + "-" + L_black_Slope1 + "-" + L_black_Slope2);

                        if (L_black_Slope1 * 10 > L_black_Slope2)
                        {
                            Ramp_New++;
                            //setText用户自定义("满足2");
                        }
                    }
                }
                //判断第几行为有效直道行
                for (j = 0; j < Final_Line - 1; j++)
                {
                    for (i = 0; i < j; i++)
                    {
                        R_black_Temp = (byte)(R_black[0] - (R_black[0] - R_black[j]) * i / j);
                        if (R_black[i] > R_black_Temp + 2 || R_black[i] + 2 < R_black_Temp)
                            break;
                    }
                    if (i == j)
                    {
                        R_black_Memory1 = j;
                    }
                    else
                    {
                        break;
                    }
                }
                R_black_Slope1 = (float)((R_black[R_black_Memory1] - R_black[0]) * 1.0 / R_black_Memory1);
                for (j = R_black_Memory1; j < Final_Line - 1; j++)
                {
                    for (i = R_black_Memory1; i < j; i++)
                    {
                        R_black_Temp = (byte)(R_black[R_black_Memory1] - (R_black[R_black_Memory1] - R_black[j]) * (i - R_black_Memory1) / (j - R_black_Memory1));
                        if (R_black[i] > R_black_Temp + 2 || R_black[i] + 2 < R_black_Temp)
                            break;
                    }
                    if (i == j)
                    {
                        R_black_Memory2 = j;
                    }
                    else
                    {
                        break;
                    }
                }

                if (R_black_Memory2 > R_black_Memory1)
                {
                    R_black_Slope2 = (float)((R_black[R_black_Memory2] - R_black[R_black_Memory1]) * 1.0 / (R_black_Memory2 - R_black_Memory1));
                    if (Ramp_Flag == 0 && L_black_Memory1 > 20)
                    {
                        //setText用户自定义("-" + R_black_Memory1 + "-" + R_black_Memory2 + "-" + R_black_Slope1 + "-" + R_black_Slope2);
                        if (R_black_Slope1 > R_black_Slope2 + Ramp_Down_Num * 0.01 && R_black_Slope1 < R_black_Slope2 + Ramp_Up_Num * 0.01 && Ramp_Flag == 0 && R_black_Memory2 - R_black_Memory1 > 14)
                        {
                            Ramp_New++;
                            //setText用户自定义("满足2");
                        }
                    }
                    else if (Ramp_Flag == 1 && R_black_Memory2 - R_black_Memory1 < 4 && R_black_Memory2 < 28)
                    {
                        //setText用户自定义("-" + R_black_Memory1 + "-" + R_black_Memory2 + "-" + R_black_Slope1 + "-" + R_black_Slope2);
                        if (R_black_Slope1 < R_black_Slope2 * 10)
                        {
                            Ramp_New++;
                            //setText用户自定义("满足2");
                        }
                    }
                }
                //                    if ( Final_Line > 60&&R_black_Slope1 > R_black_Slope2 + 0.6 && R_black_Slope1 < R_black_Slope2 + 1 && Ramp_Flag == 0)
                //                    {
                //                        if (L_black[Final_Line / 2] < L_black[0] && L_black[Final_Line-1] < L_black[Final_Line / 2])
                //                        {
                //                             //setText用户自定义("这是坡道斜上");
                //                            Ramp_Flag = 1;
                //                            Ramp_New = 0;
                //                        }
                //

                //                    }
                //                    if ( Final_Line > 60&&L_black_Slope1 > L_black_Slope2 + 0.6 && L_black_Slope1 < L_black_Slope2 + 1 && Ramp_Flag == 0)
                //                    {
                //                        if (R_black[Final_Line / 2] > R_black[0] && R_black[Final_Line-1] > R_black[Final_Line / 2])
                //                        {
                //                            //setText用户自定义("这是坡道斜上");
                //                            Ramp_Flag = 1;
                //                            Ramp_New = 0;
                //                        }
                //                    }
                if (Ramp_New == 2 && Ramp_Flag == 0)
                {
                    Ramp_Flag = 1;
                    Ramp_New = 0;
                    //setText用户自定义("这是坡道上上上上上上上上上上上上上");
                }
                else if (Ramp_New == 2 && Ramp_Flag == 1)
                {
                    Ramp_Flag = 2;
                    Ramp_New = 0;
                    //setText用户自定义("这是坡道面面面面面面面面面面面面面面面");
                }
                else if (Ramp_Flag == 2)
                {
                    if (L_black[0] - R_black[0] < 90 && L_black[3] - R_black[3] < 90)
                    {
                        Ramp_Flag = 3;
                        //setText用户自定义("这是坡道下下下下下下下下下下");
                    }
                }
                if (Ramp_Flag > 0 && L_black[0] - R_black[0] > 110 && ((L_black[0] > 190 && R_black[0] > 30) || (L_black[0] < 170 && R_black[0] < 10) || (L_black[5] > 190 && R_black[5] > 30) || (L_black[5] < 170 && R_black[5] < 10)))
                {
                    Ramp_Flag = 0;
                }
            }

            /*******************环路***********************************/
            if (Ring_Find_Flag == 1)
            {
                //*******************预备
                if (Ring_State_Flag >= 3)
                {
                    if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 4)
                    {
                        if (Last_Line > 50)
                        {
                            for (i = 2; i < 50; i++)
                            {
                                if (L_black[i - 1] - L_black[i] > 15 && Loop_L_Max == 0)
                                {
                                    Loop_L_Max = i;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            for (i = 2; i < Last_Line; i++)
                            {
                                if (L_black[i - 1] - L_black[i] > 15 && Loop_L_Max == 0)
                                {
                                    Loop_L_Max = i;
                                    break;
                                }
                            }
                        }
                    }
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3 || Ring_Dir_Flag[Ring_Dir_num] == 5)
                    {
                        if (Last_Line > 50)
                        {
                            for (i = 2; i < 50; i++)
                            {
                                if (R_black[i] - R_black[i - 1] > 15 && Loop_R_Max == 0)
                                {
                                    Loop_R_Max = i;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            for (i = 2; i < Last_Line; i++)
                            {
                                if (R_black[i] - R_black[i - 1] > 15 && Loop_R_Max == 0)
                                {
                                    Loop_R_Max = i;
                                    break;
                                }
                            }
                        }
                    }
                }

                if (Last_Line < 60 && Ring_State_Flag == 1)
                {
                    for (i = 3; i < Last_Line - 3; i++)
                    {
                        if (R_Turning_Point_Flag == 0)
                        {
                            if (guai_switch_flag == 0)
                                Turning_Point(i, 0);
                            else if (guai_switch_flag == 1)
                                Turning_Point_nei(i, 0);

                            if (R_Turning_Point_Flag == 1)
                            {
                                Loop_R_guai = i;
                            }
                        }
                        if (L_Turning_Point_Flag == 0)
                        {

                            //Turning_Point(i, 1);
                            if (guai_switch_flag == 0)
                                Turning_Point(i, 1);
                            else if (guai_switch_flag == 1)
                                Turning_Point_nei(i, 1);

                            if (L_Turning_Point_Flag == 1)
                            {
                                Loop_L_guai = i;
                            }
                        }
                        if (Loop_R_guai > 0 && Loop_L_guai > 0)
                        {
                            break;
                        }
                    }
                }
                else if (Ring_State_Flag == 1)
                {
                    for (i = 3; i < 58; i++)
                    {
                        if (R_Turning_Point_Flag == 0)
                        {
                            if (guai_switch_flag == 0)
                                Turning_Point(i, 0);
                            else if (guai_switch_flag == 1)
                                Turning_Point_nei(i, 0);

                            //Turning_Point(i, 0);

                            if (R_Turning_Point_Flag == 1)
                            {
                                Loop_R_guai = i;
                            }
                        }
                        if (L_Turning_Point_Flag == 0)
                        {
                            if (guai_switch_flag == 0)
                                Turning_Point(i, 1);
                            else if (guai_switch_flag == 1)
                                Turning_Point_nei(i, 1);

                            //Turning_Point(i, 1);

                            if (L_Turning_Point_Flag == 1)
                            {
                                Loop_L_guai = i;
                            }
                        }
                        if (Loop_R_guai > 0 && Loop_L_guai > 0)
                        {
                            break;
                        }
                    }
                }

                if (Last_Line < 40 && Ring_State_Flag > 2)
                {
                    for (i = 3; i < Last_Line - 3; i++)
                    {
                        if (R_Turning_Point_Flag == 0 && L_black[i] - R_black[i] > 40)
                        {
                            Turning_Point_nei(i, 0);

                            if (R_Turning_Point_Flag == 1)
                            {
                                Loop_R_guai = i;
                            }
                        }
                        if (L_Turning_Point_Flag == 0 && L_black[i] - R_black[i] > 40)
                        {

                            Turning_Point_nei(i, 1);

                            if (L_Turning_Point_Flag == 1)
                            {
                                Loop_L_guai = i;
                            }
                        }
                        if (Loop_R_guai > 0 && Loop_L_guai > 0)
                        {
                            break;
                        }
                    }
                }

                else
                {
                    for (i = 3; i < 38; i++)
                    {
                        if (R_Turning_Point_Flag == 0 && L_black[i] - R_black[i] > 40)
                        {

                            Turning_Point_nei(i, 0);

                            if (R_Turning_Point_Flag == 1)
                            {
                                Loop_R_guai = i;
                            }
                        }
                        if (L_Turning_Point_Flag == 0 && L_black[i] - R_black[i] > 40)
                        {

                            Turning_Point_nei(i, 1);

                            if (L_Turning_Point_Flag == 1)
                            {
                                Loop_L_guai = i;
                            }
                        }
                        if (Loop_R_guai > 0 && Loop_L_guai > 0)
                        {
                            break;
                        }
                    }
                }

                /********出环进入State=5*********/
                if (Ring_State_Flag == 4)
                {
                    if (((Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 4) && Loop_L_Max > Loop_Last_L_Max + 10 && Loop_Last_L_Max > 0) || ((Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 4) && Loop_L_Max == 0 && Loop_Last_L_Max > 0))
                    {
                        state_4 = 1;
                    }
                    else if (((Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3 || Ring_Dir_Flag[Ring_Dir_num] == 5) && Loop_R_Max > Loop_Last_R_Max + 10 && Loop_Last_R_Max > 0) || ((Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3 || Ring_Dir_Flag[Ring_Dir_num] == 5) && Loop_R_Max == 0 && Loop_Last_R_Max > 0))
                    {
                        state_4 = 1;
                    }

                    if (L_black[0] - R_black[0] > 180)
                        state_5 = 1;

                    if ((state_4 == 1 && Ring_Dir_Flag[Ring_Dir_num] < 4) || (Ring_Dir_Flag[Ring_Dir_num] >= 4 && state_5 == 1 && state_4 == 1))
                    {
                        if ((L_black[0] < 195 && R_black[0] > 5) || (L_black[0] > 195 && R_black[0] > 50) || (L_black[0] < 150 && R_black[0] < 5))
                        {
                            Ring_Dir_num++;
                            Ring_State_Flag = 0;
                            Ring_Find_Flag = 0;
                            Ring_CD = 0;
                            state_5 = state_4 = 0;
                        }
                    }
                }
                else if (Ring_State_Flag == 3)
                {
                    if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 4)
                    {
                        if ((Loop_R_guai <= 8 && Loop_Last_R_guai > Loop_R_guai) || (Loop_Last_R_guai <= 8 && Loop_Last_R_guai < Loop_R_guai && Loop_Last_R_guai > 0))
                        {
                            Ring_State_Flag = 4;
                        }
                    }
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3 || Ring_Dir_Flag[Ring_Dir_num] == 5)
                    {
                        if ((Loop_L_guai <= 8 && Loop_Last_L_guai > Loop_L_guai) || (Loop_Last_L_guai <= 8 && Loop_Last_L_guai < Loop_L_guai && Loop_Last_L_guai > 0))
                        {
                            Ring_State_Flag = 4;
                        }
                    }
                }
                else if (Ring_State_Flag == 2)
                {
                    if (Ring_Dir_Flag[Ring_Dir_num] <= 3)
                    {
                        if (L_black[0] - R_black[0] > 170)
                            State_flag = 1;

                        if (L_black[0] - R_black[0] < 150 && State_flag == 1)
                        {
                            Ring_State_Flag = 3;
                            State_flag = 0;
                        }
                    }
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 4)
                    {
                        if (L_black[0] >= 198)
                            State_flag = 2;
                        if (State_flag == 2 && L_black[0] <= 190)
                        {
                            Ring_State_Flag = 3;
                            State_flag = 0;
                        }
                    }
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 5)
                    {
                        if (R_black[0] <= 1)
                            State_flag = 2;
                        if (State_flag == 2 && R_black[0] >= 10)
                        {
                            Ring_State_Flag = 3;
                            State_flag = 0;
                        }
                    }
                }
                else if (Ring_State_Flag == 1)
                {
                    if (Ring_Dir_Flag[Ring_Dir_num] <= 3)
                    {
                        if ((Loop_L_guai > Loop_Last_L_guai + 5 && Loop_Last_L_guai > 0 && Loop_Last_L_guai < 20) || (Loop_L_guai < 5 && Loop_Last_L_guai > 0))
                            guai_R = 1;

                        if ((Loop_R_guai > Loop_Last_R_guai + 5 && Loop_Last_R_guai > 0 && Loop_Last_R_guai < 20) || (Loop_R_guai < 5 && Loop_Last_R_guai > 0))
                            guai_L = 1;

                        if ((guai_R == 1 && guai_L == 1) || (L_black[0] - R_black[0] > 185))
                        {
                            Ring_State_Flag = 2;
                            guai_L = guai_R = 0;
                            Loop_Last_L_guai = Loop_Last_R_guai = 0;
                        }
                    }

                    if (Ring_Dir_Flag[Ring_Dir_num] >= 4)
                    {
                        if ((Loop_L_guai > Loop_Last_L_guai + 5 && Loop_Last_L_guai > 0 && Loop_Last_L_guai < 20) || (Loop_L_guai < 4 && Loop_Last_L_guai > 0))
                            guai_R = 1;

                        if ((Loop_R_guai > Loop_Last_R_guai + 5 && Loop_Last_R_guai > 0 && Loop_Last_R_guai < 20) || (Loop_R_guai < 4 && Loop_Last_R_guai > 0))
                            guai_L = 1;

                        if ((guai_R == 1 && guai_L == 1) || (L_black[0] - R_black[0] > 185))
                        {
                            Ring_State_Flag = 2;
                            guai_L = guai_R = 0;
                            Loop_Last_L_guai = Loop_Last_R_guai = 0;
                        }
                    }

                    if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 4)
                    {
                        if (Loop_L_guai > 0)
                        {
                            for (i = Loop_L_guai; i < Last_Line; i++)
                            {
                                black_new_line = Limit((int)(((L_black[0] + R_black[0]) / 2) + (((L_black[Loop_L_guai] + R_black[Loop_L_guai]) / 2) - ((L_black[0] + R_black[0]) / 2)) * 1.0 * i / Loop_L_guai));

                                if (Pixels[i][black_new_line] == 0)
                                {
                                    black_new_line_x = i;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            for (i = 0; i < Last_Line; i++)
                            {
                                if (Pixels[i][((L_black[0] + R_black[0]) / 2)] == 0)
                                {
                                    black_new_line_x = i;
                                    black_new_line = (byte)((L_black[0] + R_black[0]) / 2);
                                    break;
                                }
                            }
                        }
                    }
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3 || Ring_Dir_Flag[Ring_Dir_num] == 5)
                    {
                        if (Loop_R_guai > 0)
                        {
                            for (i = Loop_R_guai; i < Last_Line; i++)
                            {
                                black_new_line = Limit((int)(((L_black[0] + R_black[0]) / 2) + (((L_black[Loop_R_guai] + R_black[Loop_R_guai]) / 2) - ((L_black[0] + R_black[0]) / 2)) * 1.0 * i / Loop_R_guai));

                                if (Pixels[i][black_new_line] == 0)
                                {
                                    black_new_line_x = i;
                                    break;
                                }
                            }
                        }
                        for (i = 0; i < Last_Line; i++)
                        {
                            if (Pixels[i][((L_black[0] + R_black[0]) / 2)] == 0)
                            {
                                black_new_line_x = i;
                                black_new_line = (byte)((L_black[0] + R_black[0]) / 2);
                                break;
                            }
                        }
                    }
                }

                //*************************补线
                if (Ring_State_Flag == 1)
                {
                    /*********向右走环路 Ring_Dir_Flag=0**********/
                    if (Ring_Dir_Flag[Ring_Dir_num] == 0)
                    {
                        //if (Loop_R_guai > 0)
                        //{
                        if (Loop_R_guai > Loop_L_guai)
                        {
                            for (i = (Loop_L_guai); i < black_new_line_x; i++)
                            {
                                L_black[i] = (byte)(L_black[(Loop_L_guai)] - (L_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                if (small_ring == 0)
                                    LCenter[i] = (byte)(LCenter[(Loop_L_guai)] - (L_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                else if (small_ring == 1)
                                    LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                            }
                        }
                        else
                        {
                            for (i = (byte)(Loop_R_guai); i < black_new_line_x; i++)
                            {
                                L_black[i] = (byte)(L_black[(Loop_R_guai)] - (L_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                if (small_ring == 0)
                                    LCenter[i] = (byte)(LCenter[(Loop_R_guai)] - (L_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                else if (small_ring == 1)
                                    LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                            }
                        }
                        //}
                        //else
                        //{
                        //    for (i = 0; i < black_new_line_x; i++)
                        //    {
                        //        L_black[i] = (byte)(L_black[0] - (L_black[0] - black_new_line) * (i - 0) / (black_new_line_x - 0));
                        //        LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                        //    }
                        //}
                    }
                    /*********向左走环路 Ring_Dir_Flag!=0**********/
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 1)
                    {
                        //if (Loop_L_guai > 0)
                        //{
                        if (Loop_L_guai > Loop_R_guai)
                        {
                            for (i = (Loop_R_guai); i < black_new_line_x; i++)
                            {
                                R_black[i] = (byte)(R_black[(Loop_R_guai)] - (R_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                LCenter[i] = (byte)(LCenter[(Loop_R_guai)] - (R_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                //LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                            }
                        }
                        else
                        {
                            for (i = (Loop_L_guai); i < black_new_line_x; i++)
                            {
                                R_black[i] = (byte)(R_black[(Loop_L_guai)] - (R_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                LCenter[i] = (byte)(LCenter[(Loop_L_guai)] - (R_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                //LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                            }
                        }
                        //}
                        //else
                        //{
                        //    for (i = 0; i < black_new_line_x; i++)
                        //    {
                        //        R_black[i] = (byte)(R_black[0] - (R_black[0] - black_new_line) * (i - 0) / (black_new_line_x - 0));
                        //        LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                        //    }
                        //}
                    }
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 2)
                    {
                        //if (Loop_R_guai > 0)
                        //{
                        if (Loop_R_guai > Loop_L_guai)
                        {
                            for (i = (Loop_L_guai); i < black_new_line_x; i++)
                            {
                                L_black[i] = (byte)(L_black[(Loop_L_guai)] - (L_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                LCenter[i] = (byte)(LCenter[(Loop_L_guai)] - (L_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                //LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                            }
                        }
                        else
                        {
                            for (i = (byte)(Loop_R_guai); i < black_new_line_x; i++)
                            {
                                L_black[i] = (byte)(L_black[(Loop_R_guai)] - (L_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                LCenter[i] = (byte)(LCenter[(Loop_R_guai)] - (L_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                //LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                            }
                        }
                        //}
                        //else
                        //{
                        //    for (i = 0; i < black_new_line_x; i++)
                        //    {
                        //        L_black[i] = (byte)(L_black[0] - (L_black[0] - black_new_line) * (i - 0) / (black_new_line_x - 0));
                        //        LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                        //    }
                        //}
                    }
                    /*********向左走环路 Ring_Dir_Flag!=0**********/
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 3)
                    {
                        //if (Loop_L_guai > 0)
                        //{
                        if (Loop_L_guai > Loop_R_guai)
                        {
                            for (i = (Loop_R_guai); i < black_new_line_x; i++)
                            {
                                R_black[i] = (byte)(R_black[(Loop_R_guai)] - (R_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                LCenter[i] = (byte)(LCenter[(Loop_R_guai)] - (R_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                //LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                            }
                        }
                        else
                        {
                            for (i = (Loop_L_guai); i < black_new_line_x; i++)
                            {
                                R_black[i] = (byte)(R_black[(Loop_L_guai)] - (R_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                LCenter[i] = (byte)(LCenter[(Loop_L_guai)] - (R_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                //LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                            }
                        }
                        //}
                        //else
                        //{
                        //    for (i = 0; i < black_new_line_x; i++)
                        //    {
                        //        R_black[i] = (byte)(R_black[0] - (R_black[0] - black_new_line) * (i - 0) / (black_new_line_x - 0));
                        //        LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                        //    }
                        //}
                    }
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 4)
                    {
                        if (Loop_R_guai > 0)
                        {
                            if (Loop_R_guai > Loop_L_guai)
                            {
                                for (i = (Loop_L_guai); i < black_new_line_x; i++)
                                {
                                    L_black[i] = (byte)(L_black[(Loop_L_guai)] - (L_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                    LCenter[i] = (byte)(LCenter[(Loop_L_guai)] - (L_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                    //LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                                }
                            }
                            else
                            {
                                for (i = (Loop_R_guai); i < black_new_line_x; i++)
                                {
                                    L_black[i] = (byte)(L_black[(Loop_R_guai)] - (L_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                    LCenter[i] = (byte)(LCenter[(Loop_R_guai)] - (L_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                    //LCenter[i] = (byte)(R_black[i] + (L_black[i] - R_black[i]) / 2);
                                }
                            }
                        }
                        else
                        {
                            for (i = 0; i < black_new_line_x; i++)
                            {
                                L_black[i] = (byte)(L_black[0] - (L_black[0] - black_new_line) * (i - 0) / (black_new_line_x - 0));
                                LCenter[i] = (byte)(R_black[i] + (L_black[i] - R_black[i]) / 2);
                            }
                        }
                    }
                    /*********向左走环路 Ring_Dir_Flag!=0**********/
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 5)
                    {
                        if (Loop_L_guai > 0)
                        {
                            if (Loop_L_guai > Loop_R_guai)
                            {
                                for (i = (Loop_R_guai); i < black_new_line_x; i++)
                                {
                                    R_black[i] = (byte)(R_black[(Loop_R_guai)] - (R_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                    LCenter[i] = (byte)(LCenter[(Loop_R_guai)] - (R_black[(Loop_R_guai)] - black_new_line) * (i - (Loop_R_guai)) / (black_new_line_x - (Loop_R_guai)));
                                    //LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                                }
                            }
                            else
                            {
                                for (i = (byte)(Loop_L_guai); i < black_new_line_x; i++)
                                {
                                    R_black[i] = (byte)(R_black[(Loop_L_guai)] - (R_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                    LCenter[i] = (byte)(LCenter[(Loop_L_guai)] - (R_black[(Loop_L_guai)] - black_new_line) * (i - (Loop_L_guai)) / (black_new_line_x - (Loop_L_guai)));
                                    //LCenter[i] = (byte)(L_black[i] - (L_black[i] - R_black[i]) / 2);
                                }
                            }
                        }
                        else
                        {
                            for (i = 0; i < black_new_line_x; i++)
                            {
                                R_black[i] = (byte)(R_black[0] - (R_black[0] - black_new_line) * (i - 0) / (black_new_line_x - 0));
                                LCenter[i] = (byte)(L_black[i] - (L_black[i] - R_black[i]) / 2);
                            }
                        }
                    }
                }

                else if (Ring_State_Flag == 2)
                {
                    if (Last_Line > 55)
                    {
                        for (i = 10; i < 55; i++)
                        {
                            if (L_black[i] < Loop_L_Min && L_black[i] > 0)
                            {
                                Loop_L_Min = L_black[i];
                                Loop_L_Line = i;
                            }
                        }
                        for (i = 10; i < 55; i++)
                        {
                            if (R_black[i] > Loop_R_Min && R_black[i] > 0)
                            {
                                Loop_R_Min = R_black[i];
                                Loop_R_Line = i;
                            }
                        }
                    }
                    else
                    {
                        for (i = 10; i < Last_Line; i++)
                        {
                            if (L_black[i] < Loop_L_Min && L_black[i] > 0)
                            {
                                Loop_L_Min = L_black[i];
                                Loop_L_Line = i;
                            }
                        }
                        for (i = 10; i < Last_Line; i++)
                        {
                            if (R_black[i] > Loop_R_Min && R_black[i] > 0)
                            {
                                Loop_R_Min = R_black[i];
                                Loop_R_Line = i;
                            }
                        }
                    }
                    if (L_black[0] - R_black[0] > 150)
                    {
                        /*********向右走环路 Ring_Dir_Flag=0**********/
                        if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2)
                        {
                            for (i = 0; i < Loop_L_Line; i++)
                            {
                                LCenter[i] = (byte)(R_black[0] + (L_black[0] - R_black[0]) / 3 - (R_black[0] + (L_black[0] - R_black[0]) / 3 - (R_black[Loop_L_Line] + (L_black[Loop_L_Line] - R_black[Loop_L_Line]) / 2)) * (i) / (Loop_L_Line));
                            }
                        }
                        /*********向左走环路 Ring_Dir_Flag!=0**********/
                        else if (Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3)
                        {
                            for (i = 0; i < Loop_R_Line; i++)
                            {
                                LCenter[i] = (byte)(R_black[0] + (L_black[0] - R_black[0]) * 2 / 3 + ((L_black[Loop_R_Line] - (L_black[Loop_R_Line] - R_black[Loop_R_Line]) / 2) - (R_black[0] + (L_black[0] - R_black[0]) * 2 / 3)) * (i) / (Loop_R_Line));
                            }
                        }
                        else if (Ring_Dir_Flag[Ring_Dir_num] == 4)
                        {
                            for (i = 0; i < Loop_L_Line; i++)
                            {
                                LCenter[i] = (byte)(R_black[0] + (L_black[0] - R_black[0]) / 3 - (R_black[0] + (L_black[0] - R_black[0]) / 3 - (R_black[Loop_L_Line] + (L_black[Loop_L_Line] - R_black[Loop_L_Line]) / 2)) * (i) / (Loop_L_Line));
                            }
                        }
                        /*********向左走环路 Ring_Dir_Flag!=0**********/
                        else if (Ring_Dir_Flag[Ring_Dir_num] == 5)
                        {
                            for (i = 0; i < Loop_R_Line; i++)
                            {
                                LCenter[i] = (byte)(R_black[0] + (L_black[0] - R_black[0]) * 2 / 3 + ((L_black[Loop_R_Line] - (L_black[Loop_R_Line] - R_black[Loop_R_Line]) / 2) - (R_black[0] + (L_black[0] - R_black[0]) * 2 / 3)) * (i) / (Loop_R_Line));
                            }
                        }
                    }
                    else
                    {
                        /*********向右走环路 Ring_Dir_Flag=0**********/
                        if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2)
                        {
                            for (i = 0; i < Loop_L_Line; i++)
                            {
                                LCenter[i] = (byte)(R_black[0] + (L_black[0] - R_black[0]) / 2 - (R_black[0] + (L_black[0] - R_black[0]) / 2 - (R_black[Loop_L_Line] + (L_black[Loop_L_Line] - R_black[Loop_L_Line]) / 2)) * (i) / (Loop_L_Line));
                            }
                        }
                        /*********向左走环路 Ring_Dir_Flag!=0**********/
                        else if (Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3)
                        {
                            for (i = 0; i < Loop_R_Line; i++)
                            {
                                LCenter[i] = (byte)(R_black[0] + (L_black[0] - R_black[0]) / 2 + ((L_black[Loop_R_Line] - (L_black[Loop_R_Line] - R_black[Loop_R_Line]) / 2) - (R_black[0] + (L_black[0] - R_black[0]) / 2)) * (i) / (Loop_R_Line));
                            }
                        }
                        else if (Ring_Dir_Flag[Ring_Dir_num] == 4)
                        {
                            if (state2_tiao == 0)
                            {
                                for (i = Loop_L_Line; i > 0; i--)
                                {
                                    if (L_black[i] >= 195 && R_black[i] <= 5)
                                    {
                                        state2_tiao = (byte)(i + 1);
                                        break;
                                    }
                                    LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                                }
                            }
                            if (state2_tiao > 0)
                            {
                                for (i = 0; i <= state2_tiao + 1; i++)
                                {
                                    LCenter[i] = (byte)(R_black[0] + (L_black[0] - R_black[0]) / 2 - (R_black[0] + (L_black[0] - R_black[0]) / 2 - LCenter[state2_tiao + 1]) * (i) / (state2_tiao + 1));
                                }
                            }
                        }
                        /*********向左走环路 Ring_Dir_Flag!=0**********/
                        else if (Ring_Dir_Flag[Ring_Dir_num] == 5)
                        {
                            if (state2_tiao == 0)
                            {
                                for (i = Loop_R_Line; i > 0; i--)
                                {
                                    if (L_black[i] >= 195 && R_black[i] <= 5)
                                    {
                                        state2_tiao = (byte)(i + 1);
                                        break;
                                    }
                                    LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                                }
                            }
                            if (state2_tiao > 0)
                            {
                                for (i = 0; i <= state2_tiao + 1; i++)
                                {
                                    LCenter[i] = (byte)(R_black[0] + (L_black[0] - R_black[0]) / 2 + (LCenter[state2_tiao + 1] - (R_black[0] + (L_black[0] - R_black[0]) / 2)) * (i) / (state2_tiao + 1));
                                }
                            }
                        }
                    }
                }
                else if (Ring_State_Flag == 3)
                {
                    L_Loss = 0;
                    R_Loss = 0;

                    if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 4)
                    {
                        if (Loop_R_guai > 0 && Loop_R_guai < Loop_L_Max && Loop_Last_R_guai > Loop_R_guai)
                        {
                            for (i = Loop_R_guai; i < Loop_L_Max; i++)
                            {
                                L_black[i] = (byte)(L_black[Loop_R_guai] - (L_black[Loop_R_guai] - L_black[Loop_L_Max]) * (i - Loop_R_guai) / (Loop_L_Max - Loop_R_guai));
                            }
                        }
                    }
                    /*********向左走环路 Ring_Dir_Flag!=0**********/
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3 || Ring_Dir_Flag[Ring_Dir_num] == 5)
                    {
                        if (Loop_L_guai > 0 && Loop_L_guai < Loop_R_Max && Loop_Last_L_guai > Loop_L_guai)
                        {
                            for (i = Loop_L_guai; i < Loop_R_Max; i++)
                            {
                                R_black[i] = (byte)(R_black[Loop_L_guai] - (R_black[Loop_L_guai] - R_black[Loop_R_Max]) * (i - Loop_L_guai) / (Loop_R_Max - Loop_L_guai));
                            }
                        }
                    }

                    for (i = 0; i < Last_Line; i++)
                    {
                        LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                        Bend_Repair(i);
                    }
                }

                else if (Ring_State_Flag == 4)
                {
                    L_Loss = 0;
                    R_Loss = 0;
                    if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 2)
                    {
                        if (Loop_R_guai > 0 && Loop_R_guai < Loop_L_Max && Loop_Last_R_guai > Loop_R_guai)
                        {
                            for (i = Loop_R_guai; i < Loop_L_Max; i++)
                            {
                                L_black[i] = (byte)(L_black[Loop_R_guai] - (L_black[Loop_R_guai] - L_black[Loop_L_Max]) * (i - Loop_R_guai) / (Loop_L_Max - Loop_R_guai));
                            }
                        }
                        else if (Loop_Last_L_Max >= Loop_L_Max)
                        {
                            if (L_black[0] > 195)
                            {
                                if (Limit(L_black[Loop_L_Max + 1] + (L_black[Loop_L_Max + 1] - L_black[Loop_L_Max + 4]) * (Loop_L_Max + 1 - 0) / 3) < 199)
                                {
                                    for (i = 0; i < Loop_L_Max + 1; i++)
                                    {
                                        L_black[i] = Limit(L_black[Loop_L_Max + 1] + (L_black[Loop_L_Max + 1] - L_black[Loop_L_Max + 4]) * (Loop_L_Max + 1 - i) / 3);
                                    }
                                }
                                else
                                {
                                    for (i = 0; i < Loop_L_Max + 1; i++)
                                    {
                                        L_black[i] = Limit(L_black[0] - (L_black[0] - L_black[Loop_L_Max + 1]) * (i) / (Loop_L_Max + 1));
                                    }
                                }
                            }
                            else
                            {
                                for (i = 0; i < Loop_L_Max + 1; i++)
                                {
                                    L_black[i] = Limit(L_black[0] - (L_black[0] - L_black[Loop_L_Max + 1]) * (i) / (Loop_L_Max + 1));
                                }
                            }
                        }
                    }
                    /*********向左走环路 Ring_Dir_Flag!=0**********/
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 1 || Ring_Dir_Flag[Ring_Dir_num] == 3)
                    {
                        if (Loop_L_guai > 0 && Loop_L_guai < Loop_R_Max && Loop_Last_L_guai > Loop_L_guai)
                        {
                            for (i = Loop_L_guai; i < Loop_R_Max; i++)
                            {
                                R_black[i] = (byte)(R_black[Loop_L_guai] - (R_black[Loop_L_guai] - R_black[Loop_R_Max]) * (i - Loop_L_guai) / (Loop_R_Max - Loop_L_guai));
                            }
                        }
                        else if (Loop_Last_R_Max >= Loop_R_Max)
                        {
                            if (R_black[0] < 5)
                            {
                                if (Limit(R_black[Loop_R_Max + 1] + (R_black[Loop_R_Max + 1] - R_black[Loop_R_Max + 4]) * (Loop_R_Max + 1 - 0) / 3) > 0)
                                {
                                    for (i = 0; i < Loop_R_Max + 1; i++)
                                    {
                                        R_black[i] = Limit(R_black[Loop_R_Max + 1] + (R_black[Loop_R_Max + 1] - R_black[Loop_R_Max + 4]) * (Loop_R_Max + 1 - i) / 3);
                                    }
                                }
                                else
                                {
                                    for (i = 0; i < Loop_R_Max + 1; i++)
                                    {
                                        R_black[i] = Limit(R_black[0] + (R_black[Loop_R_Max + 1] - R_black[0]) * (i) / (Loop_R_Max + 1));
                                    }
                                }
                            }
                            else
                            {
                                for (i = 0; i < Loop_R_Max + 1; i++)
                                {
                                    R_black[i] = Limit(R_black[0] + (R_black[Loop_R_Max + 1] - R_black[0]) * (i) / (Loop_R_Max + 1));
                                }
                            }
                        }
                    }

                    else if (Ring_Dir_Flag[Ring_Dir_num] == 4)
                    {
                        if (Loop_R_guai > 0 && Loop_R_guai < Loop_L_Max && Loop_Last_R_guai > Loop_R_guai)
                        {
                            for (i = Loop_R_guai; i < Loop_L_Max; i++)
                            {
                                L_black[i] = (byte)(L_black[Loop_R_guai] - (L_black[Loop_R_guai] - L_black[Loop_L_Max]) * (i - Loop_R_guai) / (Loop_L_Max - Loop_R_guai));
                            }
                        }
                        else if (Loop_Last_L_Max >= Loop_L_Max)
                        {
                            if (L_black[0] > 195)
                            {
                                if (Limit(L_black[Loop_L_Max + 1] + (L_black[Loop_L_Max + 1] - L_black[Loop_L_Max + 4]) * (Loop_L_Max + 1 - 0) / 3) < 199)
                                {
                                    for (i = 0; i < Loop_L_Max + 1; i++)
                                    {
                                        L_black[i] = Limit(L_black[Loop_L_Max + 1] + (L_black[Loop_L_Max + 1] - L_black[Loop_L_Max + 4]) * (Loop_L_Max + 1 - i) / 3);
                                    }
                                }
                                else
                                {
                                    for (i = 0; i < Loop_L_Max + 1; i++)
                                    {
                                        L_black[i] = Limit(L_black[0] - (L_black[0] - L_black[Loop_L_Max + 1]) * (i) / (Loop_L_Max + 1));
                                    }
                                }
                            }
                            else
                            {
                                for (i = 0; i < Loop_L_Max + 1; i++)
                                {
                                    L_black[i] = Limit(L_black[0] - (L_black[0] - L_black[Loop_L_Max + 1]) * (i) / (Loop_L_Max + 1));
                                }
                            }
                        }
                    }
                    /*********向左走环路 Ring_Dir_Flag!=0**********/
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 5)
                    {
                        if (Loop_L_guai > 0 && Loop_L_guai < Loop_R_Max && Loop_Last_L_guai > Loop_L_guai)
                        {
                            for (i = Loop_L_guai; i < Loop_R_Max; i++)
                            {
                                R_black[i] = (byte)(R_black[Loop_L_guai] - (R_black[Loop_L_guai] - R_black[Loop_R_Max]) * (i - Loop_L_guai) / (Loop_R_Max - Loop_L_guai));
                            }
                        }
                        else if (Loop_Last_R_Max >= Loop_R_Max)
                        {
                            if (R_black[0] < 5)
                            {
                                if (Limit(R_black[Loop_R_Max + 1] + (R_black[Loop_R_Max + 1] - R_black[Loop_R_Max + 4]) * (Loop_R_Max + 1 - 0) / 3) > 0)
                                {
                                    for (i = 0; i < Loop_R_Max + 1; i++)
                                    {
                                        R_black[i] = Limit(R_black[Loop_R_Max + 1] + (R_black[Loop_R_Max + 1] - R_black[Loop_R_Max + 4]) * (Loop_R_Max + 1 - i) / 3);
                                    }
                                }
                                else
                                {
                                    for (i = 0; i < Loop_R_Max + 1; i++)
                                    {
                                        R_black[i] = Limit(R_black[0] + (R_black[Loop_R_Max + 1] - R_black[0]) * (i) / (Loop_R_Max + 1));
                                    }
                                }
                            }
                            else
                            {
                                for (i = 0; i < Loop_R_Max + 1; i++)
                                {
                                    R_black[i] = Limit(R_black[0] + (R_black[Loop_R_Max + 1] - R_black[0]) * (i) / (Loop_R_Max + 1));
                                }
                            }
                        }
                    }
                    if (Ring_Dir_Flag[Ring_Dir_num] <= 1 || Ring_Dir_Flag[Ring_Dir_num] >= 4)
                    {
                        for (i = 0; i < Last_Line; i++)
                        {
                            LCenter[i] = (byte)(L_black[i] - (L_black[i] - R_black[i]) * 10 / 20);
                            Bend_Repair(i);
                        }
                    }
                    if (Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 3)
                    {
                        if (lanxian_flag == 0)
                        {
                            for (i = 0; i < Last_Line; i++)
                            {
                                LCenter[i] = (byte)(L_black[i] - (L_black[i] - R_black[i]) * 10 / 20);
                                Bend_Repair(i);
                            }
                        }
                        else
                        {
                            if (Ring_Dir_Flag[Ring_Dir_num] == 2)
                            {
                                for (i = 0; i < Last_Line; i++)
                                {

                                    LCenter[i] = (byte)(R_black[i] + (L_black[i] - R_black[i]) * 10.0 / laxian_k);
                                    //Bend_Repair(i);
                                }
                            }
                            else if (Ring_Dir_Flag[Ring_Dir_num] == 3)
                            {
                                for (i = 0; i < Last_Line; i++)
                                {
                                    LCenter[i] = (byte)(L_black[i] - (L_black[i] - R_black[i]) * 10.0 / laxian_k);
                                    //Bend_Repair(i);
                                }
                            }
                        }
                    }
                }

                if (Ring_State_Flag >= 3)
                {
                    if (Loop_Last_L_Max == 0 || Loop_Last_L_Max > Loop_L_Max)
                    {
                        Loop_Last_L_Max = Loop_L_Max;
                    }
                    if (Loop_Last_R_Max == 0 || Loop_Last_R_Max > Loop_R_Max)
                    {
                        Loop_Last_R_Max = Loop_R_Max;
                    }
                }

                if (Ring_State_Flag != 2 && Loop_Last_L_guai == 0)
                    Loop_Last_L_guai = Loop_L_guai;
                else if (Loop_L_guai < Loop_Last_L_guai)
                    Loop_Last_L_guai = Loop_L_guai;

                if (Ring_State_Flag != 2 && Loop_Last_R_guai == 0)
                    Loop_Last_R_guai = Loop_R_guai;
                else if (Loop_R_guai < Loop_Last_R_guai)
                    Loop_Last_R_guai = Loop_R_guai;
            }

            Ring_CD++;
            if (Ring_CD > 100)
                Ring_CD = 110;
            //setText用户自定义("Final_Line--" + Final_Line + "-ring-" + Ring_State_Flag + "-" + xiaocao_k + "-" + Last_Line + "-" + Loop_guai_L + "-" + Loop_guai_R);
            OLED_Write_Num2(0, 0, Ring_State_Flag);

            if (Ring_Find_Flag != 0)
            {
                for (i = Last_Line; i < Image_Height; i++)
                {
                    L_black[i] = 0;
                    R_black[i] = 0;
                    LCenter[i] = 0;
                }
            }
            else
            {
                for (i = Final_Line; i < Image_Height; i++)
                {
                    L_black[i] = 0;
                    R_black[i] = 0;
                    LCenter[i] = 0;
                }
            }

            Buzzer_Sart();
        }
    }
}

void SignalProcess() //信息处理
{
    Image_Init();                                     //变量初始化
    for (RowNum = 0; RowNum < Image_Height; RowNum++) //循环叠加
    {
        ImageProcess(); //图像行处理 内联函数
        if (Last_Line_Flag == 1)
            break;
    }
    if (Final_Line > 3)
        Mid = LCenter[3];
    else
        Mid = LCenter[0];
    find_l = L_black[1];
    find_r = R_black[1];
    FieldProcess(); //图像场处理函数内联
}

/*********************************************************************
                                                        赛道类型判断
************************************************************************/

/*********************************************************************
                                 电机控制
************************************************************************/
/*--------------------------------------------------------------
                                                    和速度        
--------------------------------------------------------------*/
int16_t Speed_Add(int16_t speedl, int16_t speedr)
{
    if (speedl > 400)
        speedl = 400;
    if (speedr > 400)
        speedr = 400;
    return (speedl + speedr) / 2;
}
/*--------------------------------------------------------------
                                                    停车        
--------------------------------------------------------------*/
void Stop()
{
    while (1)
    {
        NVIC_DisableIRQ(PIT1_IRQn);

        FTM_PWM_ChangeDuty(FTM_Right_Forward, 0);
        FTM_PWM_ChangeDuty(FTM_Left_Forward, 0);
        FTM_PWM_ChangeDuty(FTM_Right_Backward, 0);
        FTM_PWM_ChangeDuty(FTM_Left_Backward, 0);

        if (Key_In == 0)
        {
            DelayMs(10);
            if (Key_In == 0)
            {
                NVIC_EnableIRQ(PIT1_IRQn);
                while (Key_In == 0)
                    ;

                break;
            }
        }
    }
}
/*--------------------------------------------------------------
                                                            速度保护
--------------------------------------------------------------*/
void Encoder_Protection()
{
    static uint8_t Stop_Count = 0;
    if (Encoder_Left[2] > Encoder_Max && Encoder_Right[2] > Encoder_Max)
    {
        Stop_Count++;
    }
    else if (Encoder_Right[2] < Encoder_Min && Encoder_Left[2] < Encoder_Min)
    {
        Stop_Count++;
    }
    if (Stop_Count > 3)
    {
        Stop_Count = 0;
        OLED_Write_String(6, 2, (uint8_t *)"SpeedStop");
        Stop();
    }
}

/*--------------------------------------------------------------
                                                                角度控制
--------------------------------------------------------------*/

void AngleControl(void)
{
    Set_Ang_Mid = 0;
    /**************************************************************************/
    if (Accer_Folloew_Count > 300 || Debug == 1) //1.5S直立
    {
        Accer_Folloew_Flag = 1;
    }
    else
    {
        Accer_Folloew_Count++;
    }
    if (Accer_Folloew_Flag == 1)
    {
        if (Time_Clock_5Ms < 24000)
            Time_Clock_5Ms++;
        /******************起跑线检测********************/
        if (Time_Clock_5Ms > 2000) //10S
        {
            /******************起跑线停车********************/
            if (Starting_Line_Flag == 1)
            {
                if (Start_Line_Count > StarteTime)
                {
                    OLED_Write_String(6, 2, (uint8_t *)"StartStop");
                    Stop();
                }
                else
                    Start_Line_Count++;
            }
        }
        if (Ramp_Flag >= 2)
        {
            Ramp_Count++;
            if (Ramp_Count > 250)
            {
                Ramp_Flag = 0;
                Ramp_Count = 0;
            }
        }
        else
        {
            Ramp_Count = 0;
        }
        if (Ramp_Flag == 3)
        {
            Rampxiacount++;
            if (Rampxiacount > 200)
            {
                Ramp_Flag = 0;
            }
        }
        else
            Rampxiacount = 0;

        if (Ramp_Flag > 0)
        {
            if (Ramp_Flag == 1 && g_CarSpeed > Down_Speed) //上坡道
            {
                Set_Ang_Mid = SetPodaoA;
            }
            else if (Ramp_Flag == 2) //坡面
            {
                Set_Ang_Mid = 0;
            }
            else if (Ramp_Flag == 3) //下坡道
            {
                Set_Ang_Mid = -SetPodaoC;
            }
        }
        else
        {
            Set_Ang_Mid = 0;
        }
        P_pwn_temp = (Angle + Set_Ang_Mid - Ang_ACC_Mid) * Angle_PID.Kp * 1.0 / 10;
        D_pwn_temp = (Ang_Gyro_Y)*Angle_PID.Kd * 1.0 / 10;
    }
    else
    {
        P_pwn_temp = (Angle - Ang_ACC_Mid) * Angle_PID.Kp * 1.0 / 10;
        D_pwn_temp = (Ang_Gyro_Y)*Angle_PID.Kd * 1.0 / 10;
    }
    Angle_PID.ControlOut = P_pwn_temp + D_pwn_temp;
    if (Angle_PID.ControlOut >= 42760)
    {
        Angle_PID.ControlOut = 42760;
    }
    else if (Angle_PID.ControlOut <= -42760)
    {
        Angle_PID.ControlOut = -42760;
    }

    Angle_PID.ControlOutLast = Angle_PID.ControlOut;
}

/*--------------------------------------------------------------
                                                                    速度控制
--------------------------------------------------------------*/
void SpeedControl(void)
{

    if (Mode == 0)
        Set_Speed = SpTurn;

    //	if(Encoder_Left[2]>400)
    //		Encoder_Left[2]=400;
    //	else if (Encoder_Left[2]<-400)
    //		Encoder_Left[2]=-400;
    //	if(Encoder_Right[2]>400)
    //		Encoder_Right[2]=400;
    //	else if (Encoder_Right[2]<-400)
    //		Encoder_Right[2]=-400;

    g_CarSpeed = Speed_Add(Encoder_Left[2], Encoder_Right[2]);

    /*********************************/
    //S内保持直立
    if (Accer_Folloew_Flag == 0)
    {
        Speed_L_PID.Error[2] = (0 - g_CarSpeed); //计算与设定的偏差值
    }
    else //行走
    {
        Speed_L_PID.Error[2] = (Set_Speed - g_CarSpeed); //计算与设定的偏差值
        if (BiggestJiaCount > 200)
        {
            // if (Ramp_Flag == 0) //非坡道情况下才允许积分
            {
                if (Speed_L_PID.Error[2] > 0 && I_L < 0) //达到了设定速度 不需要减速
                {
                    I_L = 0;
                }
                else
                {
                    I_L += (Speed_L_PID.Error[2]); //累加误差
                }
                if (I_L > I_L_Max) //积分限幅
                {
                    I_L = I_L_Max;
                }
                else if (I_L < -I_L_Max)
                {
                    I_L = -I_L_Max;
                }
            }
            //            else
            //            {
            //                I_L = 0;
            //            }
        }
    }

    Speed_L_PID.ControlOutOld = Speed_L_PID.ControlOutNew; //保存旧值
    if (Accer_Folloew_Flag == 1)                           //开跑了
    {
        if (Ramp_Flag > 0)
        {
            Speed_L_PID.ControlOutNew = Speed_L_PID.Kp * Speed_L_PID.Error[2] * 1.0 / 10 + Speed_L_PID.Ki * 0 / 10 * I_L + (Speed_L_PID.Error[2] - Speed_L_PID.Error[1]) * Speed_L_PID.Kd / 10; //获得输出值
        }
        else
        {
            Speed_L_PID.ControlOutNew = Speed_L_PID.Kp * Speed_L_PID.Error[2] * 1.0 / 10 + Speed_L_PID.Ki * 1.0 / 10 * I_L + (Speed_L_PID.Error[2] - Speed_L_PID.Error[1]) * Speed_L_PID.Kd / 10; //获得输出值
        }
    }
    else
    {
        Speed_L_PID.ControlOutNew = Speed_L_PID.Kp * Speed_L_PID.Error[2] * 1.0 / 10 + Speed_L_PID.Ki * 1.0 / 10 * I_L + (Speed_L_PID.Error[2] - Speed_L_PID.Error[1]) * Speed_L_PID.Kd / 10; //获得输出值
    }
}

/*--------------------------------------------------------------
                                                                    速度平滑输出
--------------------------------------------------------------*/
void SpeedControlOutput(void)
{
    int LValue;

    LValue = Speed_L_PID.ControlOutNew - Speed_L_PID.ControlOutOld;
    Speed_L_PID.ControlOut = LValue * (g_nSpeedControlCount + 1) * 1.0 / SPEED_CONTROL_COUNT + Speed_L_PID.ControlOutOld;
    if (Encoder_Left[2] > 370 && Encoder_Right[2] > 370 && Ramp_Flag <= 1)
    {
        Ramp_Flag = 2;
    }
    if (Accer_Folloew_Flag == 1)
    {
        BiggestJiaCount = 400;
        //快速起步
        if (BiggestJiaCount < 400)
        {
            BiggestJiaCount++;

            if (Speed_L_PID.ControlOut > 24000 - BiggestJiaCount * 20) //---100
            {
                SpeedControlOutMax = 24000 - BiggestJiaCount * 20;
            }
            SpeedControlOutMin = -10000;
        }
    }
    else
    {
        SpeedControlOutMax = 8000;
        SpeedControlOutMin = -8000;
    }

    if (Speed_L_PID.ControlOut > SpeedControlOutMax)
        Speed_L_PID.ControlOut = SpeedControlOutMax;
    else if (Speed_L_PID.ControlOut < SpeedControlOutMin)
        Speed_L_PID.ControlOut = SpeedControlOutMin;

    if (Speed_L_PID.ControlOut > Speed_L_PID.ControlOutLast && Speed_L_PID.ControlOut - Speed_L_PID.ControlOutLast > 300)
    {
        Speed_L_PID.ControlOut = Speed_L_PID.ControlOutLast + 300;
    }
    else if (Speed_L_PID.ControlOut < Speed_L_PID.ControlOutLast && Speed_L_PID.ControlOutLast - Speed_L_PID.ControlOut > 300)
    {
        Speed_L_PID.ControlOut = Speed_L_PID.ControlOutLast - 300;
    }
    Speed_L_PID.ControlOutLast = Speed_L_PID.ControlOut;
}

/*--------------------------------------------------------------
                                                                方向控制
--------------------------------------------------------------*/
void DirectionControl(void)
{
    static int16_t FinalPianCha[2];
    FinalPianCha[1] = Direction_PID.Error[1] * 0.7 + Direction_PID.Error[0] * 0.3;
    Direction_PID.ControlOutOld = Direction_PID.ControlOutNew;
    PValue = (int)FinalPianCha[1] * Direction_PID.Kp / 10;
    TDValue = (int)(Ang_Gyro_Z)*Direction_PID.KTd / 10;

    DValue = (FinalPianCha[1] - FinalPianCha[0]) * Direction_PID.Kd / 10;
    DTDValue = TDValue + DValue;
    FinalPianCha[0] = FinalPianCha[1];               //滤波后
    Direction_PID.Error[0] = Direction_PID.Error[1]; //滤波前
    Direction_PID.ControlOutNew = PValue - TDValue + DValue;
    if (Direction_PID.ControlOutNew > 3000)
        Direction_PID.ControlOutNew = 3000;
    else if (Direction_PID.ControlOutNew < -3000)
        Direction_PID.ControlOutNew = -3000;
}
/*Start:
*模糊PID 
*返回隶属度
*输入PianCha绝对值 基准数  小值 大值
*End*/
double MoHu_PID(double temppiancha, double basevalue, double smallvalue, double bigvalue)
{
    static double k1;
    static double k2;
    static int temp = 0;

    //无的区间
    if (temppiancha <= Dajiao_Change_RangeS - RANGE_MOHU_S) /* --x----x--*/
    {
        // setText用户自定义("中间:" + basevalue);
        return basevalue; //返回基准值
    }
    //无到小的装换区间内
    else if (temppiancha > Dajiao_Change_RangeS - RANGE_MOHU_S && temppiancha < Dajiao_Change_RangeS + RANGE_MOHU_S)
    {
        temp = temppiancha - (Dajiao_Change_RangeS - RANGE_MOHU_S); //计算超出的区域
        k1 = (2 * RANGE_MOHU_S - temp) * 1.0 / (2 * RANGE_MOHU_S);
        k2 = 1 - k1;                               //斜率相同 减少计算量
                                                   //                      setText用户自定义("无到小k1:" + k1);
                                                   //                      setText用户自定义("无到小k2:" + k2);
                                                   //                      setText用户自定义("无到小1:" + basevalue * k1);
                                                   //                      setText用户自定义("无到小2:" + smallvalue * k2);
        return (basevalue * k1 + smallvalue * k2); //返回基准值加上小区域的值
    }
    //小的区间
    else if (temppiancha >= Dajiao_Change_RangeS + RANGE_MOHU_S && temppiancha <= Dajiao_Change_RangeB - RANGE_MOHU_B) //已经处于小区域了
    {
        //  setText用户自定义("小:" + smallvalue);
        return (smallvalue);
    }
    //小到大的区间
    else if (temppiancha > Dajiao_Change_RangeB - RANGE_MOHU_B && temppiancha < Dajiao_Change_RangeB + RANGE_MOHU_B)
    {
        temp = temppiancha - (Dajiao_Change_RangeB - RANGE_MOHU_B); //计算超出的区域
        k1 = (2 * RANGE_MOHU_B - temp) * 1.0 / (2 * RANGE_MOHU_B);
        k2 = 1 - k1;
        //                        setText用户自定义("无到小k1:" + k1);
        //                        setText用户自定义("无到小k2:" + k2);
        //                        setText用户自定义("小到大1:" + smallvalue*k1);
        //                        setText用户自定义("小到大2:" + bigvalue*k2);
        return (smallvalue * k1 + bigvalue * k2); //返回基准值加上小区域的值
    }
    //大的区间
    else if (temppiancha >= Dajiao_Change_RangeB + RANGE_MOHU_B)
    {
        // setText用户自定义("大:" + bigvalue);
        return bigvalue;
    }
    else
    {
        //  setText用户自定义("错误取件");
        return 50; //返回错误值
    }
}

/*--------------------------------------------------------------
                                                                方向平滑输出
--------------------------------------------------------------*/
void DirectionControlOutput(void)
{
    int16_t Value;
    Value = Direction_PID.ControlOutNew - Direction_PID.ControlOutOld;
    if (g_nDirectionControlCount == 0)
    {
        Direction_PID.ControlOut = Value * (1) / DIRECTION_CONTROL_COUNT + Direction_PID.ControlOutOld;
    }
    else if (g_nDirectionControlCount == 1)
    {
        Direction_PID.ControlOut = Value * (2) / DIRECTION_CONTROL_COUNT + Direction_PID.ControlOutOld;
    }
    else if (g_nDirectionControlCount == 2)
    {
        Direction_PID.ControlOut = Value * (3) / DIRECTION_CONTROL_COUNT + Direction_PID.ControlOutOld;
    }
    else if (g_nDirectionControlCount == 3)
    {
        Direction_PID.ControlOut = Value * (4) / DIRECTION_CONTROL_COUNT + Direction_PID.ControlOutOld;
    }
    //   	if(Ring_Find_Flag>0)
    //	{
    if (Direction_PID.ControlOut > 3000)
        Direction_PID.ControlOut = 3000;
    else if (Direction_PID.ControlOut < -3000)
        Direction_PID.ControlOut = -3000;
    //}
    Direction_PID.ControlOutLast = Direction_PID.ControlOut;
}

/*--------------------------------------------------------------
                                                                    PWM综合输出
--------------------------------------------------------------*/
void MotorOutput(void)
{
    if (Accer_Folloew_Flag == 0)
    {
        pwm_out = Angle_PID.ControlOut;
    }
    else
    {
        pwm_out = Angle_PID.ControlOut - Speed_L_PID.ControlOut;
    }

    if (Mode == 0)
    {
        if (Mode_Choose == 0) //直立调试
        {
            L_ControlOut = Angle_PID.ControlOut;
            R_ControlOut = Angle_PID.ControlOut;
        }
        else if (Mode_Choose == 1) //直立速度调试
        {
            L_ControlOut = Angle_PID.ControlOut - Speed_L_PID.ControlOut;
            R_ControlOut = Angle_PID.ControlOut - Speed_L_PID.ControlOut;
        }
        else if (Mode_Choose == 2) //固定占空比调试
        {
            L_ControlOut = 2500;
            R_ControlOut = 2500 + ftm_add;
        }
        else if (Mode_Choose == 3) //陀螺仪水平检测
        {
            L_ControlOut = Angle_PID.ControlOut - 1000;
            R_ControlOut = Angle_PID.ControlOut + 1000;
        }
        else if (Mode_Choose == 4) //陀螺仪水平检测
        {
            L_ControlOut = Angle_PID.ControlOut + 1000;
            R_ControlOut = Angle_PID.ControlOut - 1000;
        }
    }
    else
    {

        if (Accer_Folloew_Flag == 0)
        {
            L_ControlOut = pwm_out - Direction_PID.ControlOut;
            R_ControlOut = pwm_out + Direction_PID.ControlOut;
        }
        else
        {

            if (Direction_PID.ControlOut > pwm_out * 0.95)
                Direction_PID.ControlOut = pwm_out * 0.95;
            else if (Direction_PID.ControlOut < -pwm_out * 0.95)
                Direction_PID.ControlOut = -pwm_out * 0.95;
            {

                if (Direction_PID.ControlOut > 0)
                {
                    L_ControlOut = pwm_out - Direction_PID.ControlOut * 1;
                    R_ControlOut = pwm_out + Direction_PID.ControlOut * 1;
                }
                else
                {

                    L_ControlOut = pwm_out - Direction_PID.ControlOut * 1;
                    R_ControlOut = pwm_out + Direction_PID.ControlOut * 1;
                }
            }
        }
    }
    if (ftm_add_flag == 1)
    {
        if (R_ControlOut >= 0)
            R_ControlOut = R_ControlOut + ftm_add;
        else if (R_ControlOut < 0)
            R_ControlOut = R_ControlOut - ftm_add;
    }

    if (L_ControlOut > 9997)
        L_ControlOut = 9997;
    else if (L_ControlOut < -9997)
        L_ControlOut = -9997;
    if (R_ControlOut > 9997)
        R_ControlOut = 9997;
    else if (R_ControlOut < -9997)
        R_ControlOut = -9997;

    if (Ramp_Flag > 0)
    {
        if (L_ControlOut < 0)
            L_ControlOut = 0;
        if (R_ControlOut < 0)
            R_ControlOut = 0;
    }
    if (1)
    {
        if (L_ControlOut >= 0 && R_ControlOut >= 0)
        {
            FTM_PWM_ChangeDuty(FTM_Left_Forward, Least_ControlOut + L_ControlOut);
            FTM_PWM_ChangeDuty(FTM_Left_Backward, 0);
            FTM_PWM_ChangeDuty(FTM_Right_Forward, Least_ControlOut + R_ControlOut);
            FTM_PWM_ChangeDuty(FTM_Right_Backward, 0);
        }
        else if (L_ControlOut < 0 && R_ControlOut < 0)
        {
            FTM_PWM_ChangeDuty(FTM_Left_Forward, 0);
            FTM_PWM_ChangeDuty(FTM_Left_Backward, Least_ControlOut - L_ControlOut);
            FTM_PWM_ChangeDuty(FTM_Right_Forward, 0);
            FTM_PWM_ChangeDuty(FTM_Right_Backward, Least_ControlOut - R_ControlOut);
        }
        else if (L_ControlOut >= 0 && R_ControlOut < 0)
        {
            FTM_PWM_ChangeDuty(FTM_Left_Forward, Least_ControlOut + L_ControlOut);
            FTM_PWM_ChangeDuty(FTM_Left_Backward, 0);
            FTM_PWM_ChangeDuty(FTM_Right_Forward, 0);
            FTM_PWM_ChangeDuty(FTM_Right_Backward, Least_ControlOut - R_ControlOut);
        }
        else if (L_ControlOut < 0 && R_ControlOut >= 0)
        {
            FTM_PWM_ChangeDuty(FTM_Left_Forward, 0);
            FTM_PWM_ChangeDuty(FTM_Left_Backward, Least_ControlOut - L_ControlOut);
            FTM_PWM_ChangeDuty(FTM_Right_Forward, Least_ControlOut + R_ControlOut);
            FTM_PWM_ChangeDuty(FTM_Right_Backward, 0);
        }
    }
}

/*--------------------------------------------------------------
                                                        误差提取 
--------------------------------------------------------------*/
void Run(void)
{
    uint16_t DIR_CONTROL_P = Direction_PID.Kp;
    uint16_t DIR_CONTROL_TD = Direction_PID.KTd;
    uint16_t DIR_CONTROL_D = Direction_PID.Kd;

    /******************设定速度********************/
    Set_Speed = SpTurn;
    Mid_Line = 100;

    /*--------------------------------------------------------------
                                  控制1 
--------------------------------------------------------------*/
    /******************和速度限制********************/
    if (g_CarSpeed < 0)
        g_CarSpeed = 0;
    if (Ramp_Flag > 0)
    {
        if (g_CarSpeed > 350)
            g_CarSpeed = 350;
    }
    if (Encoder_Left[2] > 370 && Encoder_Right[2] > 370 && Ramp_Flag <= 1)
    {
        Ramp_Flag = 2;
    }
    if (1)
    {
        /******************根据速度获取打角行********************/
        Hang_Max = 0.000003 * Angle * Angle + 0.025 * Angle + 23.45; //80
        //Hang_Max = 0.000003 * Angle *Angle +0.0229*Angle+ 15.626;//70
        Hang_Min = 0.000003 * Angle * Angle + 0.02 * Angle + 7.3262; //60
                                                                     //Hang_Min = 0.000001* Angle *Angle +0.0181*Angle-3.0134;//50

        if (Hang_Max > 70)
            Hang_Max = 70;
        if (Hang_Min > 70)
            Hang_Min = 70;

        if (g_CarSpeed <= 200)
        {
            if (g_CarSpeed <= 150)
                Angle_Line = (uint16_t)((g_CarSpeed) * (Hang_Min) / (240));
            else
                Angle_Line = (uint16_t)((g_CarSpeed) * (Hang_Min) / (220));
        }
        else if (g_CarSpeed <= 400)
        {
            if (g_CarSpeed < 250)
            {
                Angle_Line = (uint16_t)((g_CarSpeed - 200) * (Hang_Max - Hang_Min) / (360 - 200) + Hang_Min);
            }
            else if (g_CarSpeed <= 300)
            {
                Angle_Line = (uint16_t)((g_CarSpeed - 200) * (Hang_Max - Hang_Min) / (340 - 200) + Hang_Min);
            }
            else if (g_CarSpeed <= 320)
            {
                Angle_Line = (uint16_t)((g_CarSpeed - 200) * (Hang_Max - Hang_Min) / (320 - 200) + Hang_Min);
            }
            else if (g_CarSpeed <= 340)
            {
                Angle_Line = Hang_Max + (g_CarSpeed - 320) / 5;
            }
            else if (g_CarSpeed <= 360)
            {
                Angle_Line = Hang_Max + (g_CarSpeed - 320) / 7;
            }
            else if (g_CarSpeed <= 380)
            {
                Angle_Line = Hang_Max + (g_CarSpeed - 320) / 9;
            }
            else
            {
                Angle_Line = Hang_Max + (g_CarSpeed - 320) / 11;
            }
        }
        else
        {

            Angle_Line = Final_Line - 1;
        }
    }

    /*--------------------------------------------------------------
                                  控制2 
--------------------------------------------------------------*/

    /*--------------------------------------------------------------*/
    if (Ramp_Flag > 0)
    {

        if (Angle_Line > 40)
            Angle_Line = 40;
    }
    //防超出截止行
    if (Angle_Line >= Final_Line)
    {
        Angle_Line = Final_Line - 1;
    }
    else if (Angle_Line < 0)
        Angle_Line = 0;
    /*--------------------PD----------------------------*/

    /*--------------------特殊元素处理----------------------------*/
    /******************坡道处理********************/
    if (Accer_Folloew_Flag == 1 && BiggestJiaCount >= 400)
    {

        if (Ramp_Flag > 0)
        {
            if (Ramp_Choose == 2) //大坡道
            {
                if (Ramp_Flag == 1) //上坡道
                {

                    SpeedControlOutMax = 14000;
                    SpeedControlOutMin = -4000;
                    //GPIO_WriteBit(PTC, GPIO_Pin_12, Bit_SET);
                }
                else if (Ramp_Flag == 2) //坡面
                {

                    SpeedControlOutMax = 13000;
                    SpeedControlOutMin = 0;
                    //GPIO_WriteBit(PTC, GPIO_Pin_12, Bit_SET);
                }
                else if (Ramp_Flag == 3) //下坡道
                {

                    SpeedControlOutMax = 12000;
                    SpeedControlOutMin = 0;
                    //GPIO_WriteBit(PTC, GPIO_Pin_12, Bit_RESET);
                }
            }
            else if (Ramp_Choose == 1)
            {
                if (Ramp_Flag == 1) //上坡道
                {

                    SpeedControlOutMax = 13000;
                    SpeedControlOutMin = 0;
                    //GPIO_WriteBit(PTC, GPIO_Pin_12, Bit_SET);
                }
                else if (Ramp_Flag == 3) //下坡道
                {

                    SpeedControlOutMax = 10000;
                    SpeedControlOutMin = 0;
                    // GPIO_WriteBit(PTC, GPIO_Pin_12, Bit_RESET);
                }
            }
        }
        else
        {

            SpeedControlOutMax = 15000;
            SpeedControlOutMin = -14000;
        }
    }
    /******************坡道减速处理********************/
    if (Ramp_Flag > 0)
    {
        if (Speed_jian_Flag == 1)
        {
            Set_Speed = Down_Speed;
        }
        else
        {
            if (SpTurn * 0.94 < Up_Speed)
            {
                Set_Speed = SpTurn * 0.94;
            }
            else
            {
                Set_Speed = Up_Speed;
            }
            //			if(SpTurn * 0.94<Up_Speed)
            //			{
            //				Set_Speed = SpTurn * 0.94+Speed_jian_Count;
            //			}
            //			else
            //			{
            //				Set_Speed = Up_Speed+Speed_jian_Count;
            //			}
        }
        if (Speed_jian_Flag == 0) //上坡减速
        {
            Speed_jian_Count++;
            if (Speed_jian_Count > 30)
            {
                Speed_jian_Flag = 1;
            }
        }
        if (g_CarSpeed < Up_Speed && Speed_jian_Flag == 0)
        {
            Speed_jian_Flag = 1;
        }
    }
    else
    {
        Speed_jian_Flag = 0;
        Speed_jian_Count = 0;
    }
    /******************障碍处理********************/
    if (L_Obstacle_Flag > 0 || R_Obstacle_Flag > 0)
    {
        if (((R_Obstacle_Flag == 3 || L_Obstacle_Flag == 3) && (g_CarSpeed > Set_Speed && Set_Speed > 300)) && Obstacle_down == Obstacle_num)
        {
            I_L = I_L / 2;
        }
        Direction_PID.Kp = 700;
    }

    /******************环处理********************/
    if (Ring_Find_Flag > 0)
    {

        if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 1)
        {
            if (Ring_State_Flag == 3 && Set_Speed >= 300)
                Direction_PID.Kp = small_p;

            if (small_state_2 == 1 && Ring_State_Flag == 2)
            {
                Direction_PID.Kp = small_state_2_p;
            }
        }
        if (Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 3)
        {
            if (Ring_State_Flag == 3 && Set_Speed >= 300)
                Direction_PID.Kp = mid_p;
            //            if (Ring_State_Flag >= 3)
            //            {
            //                MidRing_Count++;
            //                if (BigRing_Count > 10)
            //                {
            //                    //GPIO_WriteBit(PTC, GPIO_Pin_12, Bit_SET);
            //                    if (Ring_Dir_Flag[Ring_Dir_num] == 2)
            //                        Mid_Line = 95;
            //                    else if (Ring_Dir_Flag[Ring_Dir_num] == 3)
            //                        Mid_Line = 105;
            //                }
            //			}
        }
        else
            MidRing_Count = 0;
        if (Ring_Dir_Flag[Ring_Dir_num] == 4 || Ring_Dir_Flag[Ring_Dir_num] == 5)
        {
            if (Ring_State_Flag == 2 && Set_Speed >= 300)
            {
                Direction_PID.Kp = big_p;
            }

            if (Ring_State_Flag >= 3)
            {
                BigRing_Count++;

                if (BigRing_Count > 15)
                {
                    //GPIO_WriteBit(PTC, GPIO_Pin_12, Bit_SET);
                    if (Ring_Dir_Flag[Ring_Dir_num] == 4)
                        Mid_Line = 90;
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 5)
                        Mid_Line = 110;
                }
            }
        }
        else
            BigRing_Count = 0;

        if (Ring_Dir_num == small_state_num && Ring_State_Flag == 2)
        {
            Direction_PID.Kp = small_state_2_p;
        }
        //        if (Ring_Dir_num == small_state_num)
        //        {
        //            Set_Speed = small_speed;
        //        }
    }

    /******************特定元素减速********************/
    if (Ring_Dir_num == Ramp_Ring && Ring_Find_Flag == 0)
    {
        if (num_jishu <= 5 * I_TimeB)
            num_jishu++;
        if (Ramp_Flag > 0)
            num_jishu = 5 * I_TimeB;
        if (num_jishu > 5 * I_TimeA)
        {
            if (num_jishu < 5 * I_TimeB)
            {
                //GPIO_WriteBit(PTC, GPIO_Pin_12, Bit_SET);
                Set_Speed = 280;
                I_L = 0;
                SpeedControlOutMin = 0;
                SpeedControlOutMax = 10000;
            }
            else
            {
                //GPIO_WriteBit(PTC, GPIO_Pin_12, Bit_RESET);
            }
            if ((L_black[0] == 199 || R_black[0] == 0) && num_jishu > 5 * I_TimeB)
                Set_Speed = SpTurn;
        }
    }

    if (Ring_Dir_num == 0 && Ring_jianshu == 1 && Ring_State_Flag < 3)
    {
        SpeedControlOutMax = 10000;
        //I_L = 0;
    }
    /******************环处理********************/
    if (0)
    {
        if (Ring_Find_Flag > 0)
        {

            if (Ring_Dir_Flag[Ring_Dir_num] == 2 || Ring_Dir_Flag[Ring_Dir_num] == 3)
            {

                if (Ring_State_Flag == 1)
                {
                    if (g_CarSpeed < 300)
                    {
                        //Set_Speed = SpTurn * 1.2;
                        Direction_PID.Kp = 630;
                    }

                    if (Set_Speed > 300)
                    {
                        Direction_PID.Kp = 700;
                    }
                }
                else if (Ring_State_Flag == 3)
                {
                    //                if (Set_Speed  < 320)
                    //                {
                    //                    Set_Speed = 320;
                    //                }
                    Direction_PID.Kp = 650;
                    if (Ring_Dir_Flag[Ring_Dir_num] == 2)
                        Mid_Line = 95;
                    else if (Ring_Dir_Flag[Ring_Dir_num] == 3)
                        Mid_Line = 105;

                    if (Set_Speed > 300)
                    {
                        Direction_PID.Kp = 700;
                    }
                }
                else if (Ring_State_Flag == 4)
                {
                    Mid_Line = 100;
                    Direction_PID.Kp = 700;
                }
            }
            else if (Ring_Dir_Flag[Ring_Dir_num] == 0 || Ring_Dir_Flag[Ring_Dir_num] == 1)
            {
                if (Ring_State_Flag == 1)
                {
                    if (g_CarSpeed < 300)
                    {
                        Direction_PID.Kp = 550;
                    }
                    else
                        Direction_PID.Kp = 620;
                }
                else if (Ring_State_Flag == 2)
                {
                }
                else if (Ring_State_Flag == 3)
                {
                    Direction_PID.Kp = 580;
                }
                else if (Ring_State_Flag == 4)
                {
                    Direction_PID.Kp = 730;
                    if (g_CarSpeed > 330)
                    {
                        Direction_PID.Kp = 740;
                    }
                }
            }
        }
    }

    /******************小S控制********************/
    if (SmallS_Flag == 1)
    {
        Direction_PID.KTd *= 2;
    }
    /******************旋转保护********************/
    if (Ang_Gyro_Z > 3000 || Ang_Gyro_Z < -3000)
    {
        OLED_Write_String(6, 2, (uint8_t *)"GyroStop");
        Stop();
    }
    /******************速度过快停止********************/
    if (Ramp_Flag == 0)
        Encoder_Protection();
    /******************方向控制********************/
    /*--------------------偏差获取----------------------------*/
    Direction_PID.Error[1] = LCenter[Angle_Line] - Mid_Line;
    DirectionControl();
    /******************处理完后恢复初始值********************/
    Direction_PID.Kp = DIR_CONTROL_P;
    Direction_PID.KTd = DIR_CONTROL_TD;
    Direction_PID.Kd = DIR_CONTROL_D;
}
