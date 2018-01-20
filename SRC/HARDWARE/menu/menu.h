#ifndef _MENU_H_
#define _MENU_H_

#include "sys.h"
#include "extern.h"
#define Number_All 44

struct Menu_Select
{
    char name[10];
    int16_t *num;
    uint16_t sub;
};

#if (Number_All >= 1)
#define name0 "Mode"
#define name0_num Mode
#define name0_sub 1
#endif

#if (Number_All >= 2)
#define name1 "Level"
#define name1_num Level
#define name1_sub 1
#endif

#if (Number_All >= 3)
#define name2 "SpTurn"
#define name2_num SpTurn
#define name2_sub 10
#endif

#if (Number_All >= 4)
#define name3 "AngMid"
#define name3_num Ang_ACC_Mid
#define name3_sub 1
#endif

#if (Number_All >= 5)
#define name4 "DIRP"
#define name4_num Direction_PID.Kp
#define name4_sub 5
#endif

#if (Number_All >= 6)
#define name5 "Thres"
#define name5_num Threshold
#define name5_sub 1
#endif

#if (Number_All >= 7)
#define name6 "SPEEDLP"
#define name6_num Speed_L_PID.Kp
#define name6_sub 5
#endif

#if (Number_All >= 8)
#define name7 "SPEEDLI"
#define name7_num Speed_L_PID.Ki
#define name7_sub 1
#endif

#if (Number_All >= 9)
#define name8 "RingDirA"
#define name8_num Ring_Dir_Flag[0]
#define name8_sub 1
#endif

#if (Number_All >= 10)
#define name9 "RingDirB"
#define name9_num Ring_Dir_Flag[1]
#define name9_sub 1
#endif

#if (Number_All >= 11)
#define name10 "RingDirC"
#define name10_num Ring_Dir_Flag[2]
#define name10_sub 1
#endif

#if (Number_All >= 12)
#define name11 "RingDirD"
#define name11_num Ring_Dir_Flag[3]
#define name11_sub 1
#endif

#if (Number_All >= 13)
#define name12 "UpSpeed"
#define name12_num Up_Speed
#define name12_sub 5
#endif

#if (Number_All >= 14)
#define name13 "DoSpeed"
#define name13_num Down_Speed
#define name13_sub 5
#endif

#if (Number_All >= 15)
#define name14 "PodaoA"      //laxian
#define name14_num SetPodaoA //
#define name14_sub 50
#endif

#if (Number_All >= 16)
#define name15 "PodaoC"
#define name15_num SetPodaoC
#define name15_sub 50
#endif

#if (Number_All >= 17)
#define name16 "RampUp"
#define name16_num Ramp_Up_Num
#define name16_sub 1
#endif

#if (Number_All >= 18)
#define name17 "RampDo"
#define name17_num Ramp_Down_Num
#define name17_sub 1
#endif

#if (Number_All >= 19)
#define name18 "Obstacle"
#define name18_num Obstacle_down
#define name18_sub 1
#endif

#if (Number_All >= 20)
#define name19 "Debug"
#define name19_num Debug
#define name19_sub 1
#endif

#if (Number_All >= 21)
#define name20 "ANGLEP"
#define name20_num Angle_PID.Kp
#define name20_sub 5
#endif

#if (Number_All >= 22)
#define name21 "ANGLED"
#define name21_num Angle_PID.Kd
#define name21_sub 5
#endif

#if (Number_All >= 23)
#define name22 "DIRTD"
#define name22_num Direction_PID.KTd
#define name22_sub 1
#endif

#if (Number_All >= 24)
#define name23 "DIRD"
#define name23_num Direction_PID.Kd
#define name23_sub 1
#endif

#if (Number_All >= 25)
#define name24 "MChoose"
#define name24_num Mode_Choose
#define name24_sub 1
#endif

#if (Number_All >= 26)
#define name25 "Buzzer"
#define name25_num Buzzer_Open
#define name25_sub 1
#endif

#if (Number_All >= 27)
#define name26 "Ramp"
#define name26_num Ramp_Choose
#define name26_sub 1
#endif

#if (Number_All >= 28)
#define name27 "Start"
#define name27_num Start_Open
#define name27_sub 1
#endif

#if (Number_All >= 29)
#define name28 "RingI"
#define name28_num Ring_jianshu
#define name28_sub 1
#endif

#if (Number_All >= 30)
#define name29 "RampRing"
#define name29_num Ramp_Ring
#define name29_sub 1
#endif

#if (Number_All >= 31)
#define name30 "ITimeA"
#define name30_num I_TimeA
#define name30_sub 5
#endif

#if (Number_All >= 32)
#define name31 "ITimeB"
#define name31_num I_TimeB
#define name31_sub 5
#endif

#if (Number_All >= 33)
#define name32 "guaisw"
#define name32_num guai_switch_flag
#define name32_sub 1
#endif

#if (Number_All >= 34)
#define name33 "allsmall"
#define name33_num small_state_2
#define name33_sub 1
#endif

#if (Number_All >= 35)
#define name34 "smallnum"
#define name34_num small_state_num
#define name34_sub 1
#endif

#if (Number_All >= 36)
#define name35 "twopB"
#define name35_num small_state_2_p
#define name35_sub 5
#endif

#if (Number_All >= 37)
#define name36 "smallsw"
#define name36_num small_ring
#define name36_sub 1
#endif

#if (Number_All >= 38)
#define name37 "smallpC"
#define name37_num small_p
#define name37_sub 5
#endif

#if (Number_All >= 39)
#define name38 "midpC"
#define name38_num mid_p
#define name38_sub 5
#endif

#if (Number_All >= 40)
#define name39 "bigpB"
#define name39_num big_p
#define name39_sub 5
#endif

#if (Number_All >= 41)
#define name40 "midsw"
#define name40_num lanxian_flag
#define name40_sub 1
#endif

#if (Number_All >= 42)
#define name41 "laxian"
#define name41_num laxian_k
#define name41_sub 1
#endif

#if (Number_All >= 43)
#define name42 "ftmFlag"
#define name42_num ftm_add_flag
#define name42_sub 1
#endif

#if (Number_All >= 44)
#define name43 "ftmadd"
#define name43_num ftm_add
#define name43_sub 5
#endif

void Menu_Init(void);
void anjian_menu(void);
void Data_Init(void);
void Flash_Read(void);
void Flash_Write(void);

#endif
