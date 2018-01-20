#include "menu.h"
#include "oled.h"
#include "delay.h"
#include "string.h"
#include "flash.h"
#include "xjb.h"
#include "extern.h"

struct Menu_Select Menu_name[Number_All];
uint16_t flash_buffer[512];
/*
 *菜单预编译
 *加菜单速度很快 只要几步
 */
void Menu_Init(void)
{
#if (Number_All >= 1)
    strcpy(Menu_name[0].name, name0);
    Menu_name[0].num = (uint16_t *)&(name0_num);
    Menu_name[0].sub = name0_sub;
#endif

#if (Number_All >= 2)
    strcpy(Menu_name[1].name, name1);
    Menu_name[1].num = (uint16_t *)&(name1_num);
    Menu_name[1].sub = name1_sub;
#endif

#if (Number_All >= 3)
    strcpy(Menu_name[2].name, name2);
    Menu_name[2].num = (uint16_t *)&(name2_num);
    Menu_name[2].sub = name2_sub;
#endif

#if (Number_All >= 4)
    strcpy(Menu_name[3].name, name3);
    Menu_name[3].num = (uint16_t *)&(name3_num);
    Menu_name[3].sub = name3_sub;
#endif

#if (Number_All >= 5)
    strcpy(Menu_name[4].name, name4);
    Menu_name[4].num = (uint16_t *)&(name4_num);
    Menu_name[4].sub = name4_sub;
#endif

#if (Number_All >= 6)
    strcpy(Menu_name[5].name, name5);
    Menu_name[5].num = (uint16_t *)&(name5_num);
    Menu_name[5].sub = name5_sub;
#endif

#if (Number_All >= 7)
    strcpy(Menu_name[6].name, name6);
    Menu_name[6].num = (uint16_t *)&(name6_num);
    Menu_name[6].sub = name6_sub;
#endif

#if (Number_All >= 8)
    strcpy(Menu_name[7].name, name7);
    Menu_name[7].num = (uint16_t *)&(name7_num);
    Menu_name[7].sub = name7_sub;
#endif

#if (Number_All >= 9)
    strcpy(Menu_name[8].name, name8);
    Menu_name[8].num = (uint16_t *)&(name8_num);
    Menu_name[8].sub = name8_sub;
#endif

#if (Number_All >= 10)
    strcpy(Menu_name[9].name, name9);
    Menu_name[9].num = (uint16_t *)&(name9_num);
    Menu_name[9].sub = name9_sub;
#endif

#if (Number_All >= 11)
    strcpy(Menu_name[10].name, name10);
    Menu_name[10].num = (uint16_t *)&(name10_num);
    Menu_name[10].sub = name10_sub;
#endif

#if (Number_All >= 12)
    strcpy(Menu_name[11].name, name11);
    Menu_name[11].num = (uint16_t *)&(name11_num);
    Menu_name[11].sub = name11_sub;
#endif

#if (Number_All >= 13)
    strcpy(Menu_name[12].name, name12);
    Menu_name[12].num = (uint16_t *)&(name12_num);
    Menu_name[12].sub = name12_sub;
#endif

#if (Number_All >= 14)
    strcpy(Menu_name[13].name, name13);
    Menu_name[13].num = (uint16_t *)&(name13_num);
    Menu_name[13].sub = name13_sub;
#endif

#if (Number_All >= 15)
    strcpy(Menu_name[14].name, name14);
    Menu_name[14].num = (uint16_t *)&(name14_num);
    Menu_name[14].sub = name14_sub;
#endif

#if (Number_All >= 16)
    strcpy(Menu_name[15].name, name15);
    Menu_name[15].num = (uint16_t *)&(name15_num);
    Menu_name[15].sub = name15_sub;
#endif

#if (Number_All >= 17)
    strcpy(Menu_name[16].name, name16);
    Menu_name[16].num = (uint16_t *)&(name16_num);
    Menu_name[16].sub = name16_sub;
#endif

#if (Number_All >= 18)
    strcpy(Menu_name[17].name, name17);
    Menu_name[17].num = (uint16_t *)&(name17_num);
    Menu_name[17].sub = name17_sub;
#endif

#if (Number_All >= 19)
    strcpy(Menu_name[18].name, name18);
    Menu_name[18].num = (uint16_t *)&(name18_num);
    Menu_name[18].sub = name18_sub;
#endif

#if (Number_All >= 20)
    strcpy(Menu_name[19].name, name19);
    Menu_name[19].num = (uint16_t *)&(name19_num);
    Menu_name[19].sub = name19_sub;
#endif

#if (Number_All >= 21)
    strcpy(Menu_name[20].name, name20);
    Menu_name[20].num = (uint16_t *)&(name20_num);
    Menu_name[20].sub = name20_sub;
#endif

#if (Number_All >= 22)
    strcpy(Menu_name[21].name, name21);
    Menu_name[21].num = (uint16_t *)&(name21_num);
    Menu_name[21].sub = name21_sub;
#endif

#if (Number_All >= 23)
    strcpy(Menu_name[22].name, name22);
    Menu_name[22].num = (uint16_t *)&(name22_num);
    Menu_name[22].sub = name22_sub;
#endif

#if (Number_All >= 24)
    strcpy(Menu_name[23].name, name23);
    Menu_name[23].num = (uint16_t *)&(name23_num);
    Menu_name[23].sub = name23_sub;
#endif

#if (Number_All >= 25)
    strcpy(Menu_name[24].name, name24);
    Menu_name[24].num = (uint16_t *)&(name24_num);
    Menu_name[24].sub = name24_sub;
#endif

#if (Number_All >= 26)
    strcpy(Menu_name[25].name, name25);
    Menu_name[25].num = (uint16_t *)&(name25_num);
    Menu_name[25].sub = name25_sub;
#endif

#if (Number_All >= 27)
    strcpy(Menu_name[26].name, name26);
    Menu_name[26].num = (uint16_t *)&(name26_num);
    Menu_name[26].sub = name26_sub;
#endif

#if (Number_All >= 28)
    strcpy(Menu_name[27].name, name27);
    Menu_name[27].num = (uint16_t *)&(name27_num);
    Menu_name[27].sub = name27_sub;
#endif

#if (Number_All >= 29)
    strcpy(Menu_name[28].name, name28);
    Menu_name[28].num = (uint16_t *)&(name28_num);
    Menu_name[28].sub = name28_sub;
#endif

#if (Number_All >= 30)
    strcpy(Menu_name[29].name, name29);
    Menu_name[29].num = (uint16_t *)&(name29_num);
    Menu_name[29].sub = name29_sub;
#endif
#if (Number_All >= 31)
    strcpy(Menu_name[30].name, name30);
    Menu_name[30].num = (uint16_t *)&(name30_num);
    Menu_name[30].sub = name30_sub;
#endif
#if (Number_All >= 32)
    strcpy(Menu_name[31].name, name31);
    Menu_name[31].num = (uint16_t *)&(name31_num);
    Menu_name[31].sub = name31_sub;
#endif
#if (Number_All >= 33)
    strcpy(Menu_name[32].name, name32);
    Menu_name[32].num = (uint16_t *)&(name32_num);
    Menu_name[32].sub = name32_sub;
#endif
#if (Number_All >= 34)
    strcpy(Menu_name[33].name, name33);
    Menu_name[33].num = (uint16_t *)&(name33_num);
    Menu_name[33].sub = name33_sub;
#endif
#if (Number_All >= 35)
    strcpy(Menu_name[34].name, name34);
    Menu_name[34].num = (uint16_t *)&(name34_num);
    Menu_name[34].sub = name34_sub;
#endif
#if (Number_All >= 36)
    strcpy(Menu_name[35].name, name35);
    Menu_name[35].num = (uint16_t *)&(name35_num);
    Menu_name[35].sub = name35_sub;
#endif
#if (Number_All >= 37)
    strcpy(Menu_name[36].name, name36);
    Menu_name[36].num = (uint16_t *)&(name36_num);
    Menu_name[36].sub = name36_sub;
#endif
#if (Number_All >= 38)
    strcpy(Menu_name[37].name, name37);
    Menu_name[37].num = (uint16_t *)&(name37_num);
    Menu_name[37].sub = name37_sub;
#endif
#if (Number_All >= 39)
    strcpy(Menu_name[38].name, name38);
    Menu_name[38].num = (uint16_t *)&(name38_num);
    Menu_name[38].sub = name38_sub;
#endif
#if (Number_All >= 40)
    strcpy(Menu_name[39].name, name39);
    Menu_name[39].num = (uint16_t *)&(name39_num);
    Menu_name[39].sub = name39_sub;
#endif
#if (Number_All >= 41)
    strcpy(Menu_name[40].name, name40);
    Menu_name[40].num = (uint16_t *)&(name40_num);
    Menu_name[40].sub = name40_sub;
#endif
#if (Number_All >= 42)
    strcpy(Menu_name[41].name, name41);
    Menu_name[41].num = (uint16_t *)&(name41_num);
    Menu_name[41].sub = name41_sub;
#endif
#if (Number_All >= 43)
    strcpy(Menu_name[42].name, name42);
    Menu_name[42].num = (uint16_t *)&(name42_num);
    Menu_name[42].sub = name42_sub;
#endif

#if (Number_All >= 44)
    strcpy(Menu_name[43].name, name43);
    Menu_name[43].num = (uint16_t *)&(name43_num);
    Menu_name[43].sub = name43_sub;
#endif
#if (Number_All >= 45)
    strcpy(Menu_name[44].name, name44);
    Menu_name[44].num = (uint16_t *)&(name44_num);
    Menu_name[44].sub = name44_sub;
#endif

#if (Number_All)
    anjian_menu();
#endif
}
/*
 *Flash参数读
 */
void Flash_Read()
{
    if (Level == 0)
    {
        FLASH_ReadByte(242, 150, (uint8_t *)flash_buffer);
        Mode = flash_buffer[0];
        Threshold = flash_buffer[1];
        SpTurn = flash_buffer[2];
        Ang_ACC_Mid = flash_buffer[3];
        Angle_PID.Kp = flash_buffer[4];
        Angle_PID.Kd = flash_buffer[5];
        Direction_PID.Kp = flash_buffer[6];
        Direction_PID.KTd = flash_buffer[7];
        Direction_PID.Kd = flash_buffer[8];
        Speed_L_PID.Kp = flash_buffer[9];
        Speed_L_PID.Ki = flash_buffer[10];
        Speed_L_PID.Kd = flash_buffer[11];
        Speed_R_PID.Kp = flash_buffer[12];
        Speed_R_PID.Ki = flash_buffer[13];
        Speed_R_PID.Kd = flash_buffer[14];
        Ring_Dir_Flag[0] = flash_buffer[15];
        Ang_Gyro_Y_Zero = flash_buffer[16];
        Ang_Gyro_Z_Zero = flash_buffer[17];
        Mode_Choose = flash_buffer[18];
        Buzzer_Open = flash_buffer[19];
        Kg = flash_buffer[20];
        Dt = flash_buffer[21];
        Ring_Dir_Flag[1] = flash_buffer[22];
        Ring_Dir_Flag[2] = flash_buffer[23];
        Start_Open = flash_buffer[24];
        Ramp_Choose = flash_buffer[25];
        Debug = flash_buffer[26];
        SetPodaoA = flash_buffer[27];
        SetPodaoC = flash_buffer[28];
        sentdata = flash_buffer[29];
        Ramp_Ring = flash_buffer[30];
        Obstacle_down = flash_buffer[31];
        Ring_jianshu = flash_buffer[32];

        laxian_k = flash_buffer[33];

        Podao_bisai = flash_buffer[34];
        Up_Speed = flash_buffer[35];
        Angle_Line = flash_buffer[36];
        Down_Speed = flash_buffer[37];
        I_TimeA = flash_buffer[38];
        I_TimeB = flash_buffer[39];

        Ramp_Up_Num = flash_buffer[40];
        Ramp_Down_Num = flash_buffer[41];
        lanxian_flag = flash_buffer[42];
        small_p = flash_buffer[43];
        mid_p = flash_buffer[44];
        big_p = flash_buffer[45];
        small_ring = flash_buffer[46];
        guai_switch_flag = flash_buffer[47];
        small_state_2 = flash_buffer[48];
        small_state_num = flash_buffer[49];
        small_state_2_p = flash_buffer[50];
        ftm_add_flag = flash_buffer[51];
        ftm_add = flash_buffer[52];
        if (Mode < 0 || Mode > 20)
        {
            Data_Init();
        }
    }
}
/*
 *Flash参数写
 */
void Flash_Write() 
{
    if (Level == 0)
    {
        flash_buffer[0] = Mode;
        flash_buffer[1] = Threshold;
        flash_buffer[2] = SpTurn;
        flash_buffer[3] = Ang_ACC_Mid;
        flash_buffer[4] = Angle_PID.Kp;
        flash_buffer[5] = Angle_PID.Kd;
        flash_buffer[6] = Direction_PID.Kp;
        flash_buffer[7] = Direction_PID.KTd;
        flash_buffer[8] = Direction_PID.Kd;
        flash_buffer[9] = Speed_L_PID.Kp;
        flash_buffer[10] = Speed_L_PID.Ki;
        flash_buffer[11] = Speed_L_PID.Kd;
        flash_buffer[12] = Speed_R_PID.Kp;
        flash_buffer[13] = Speed_R_PID.Ki;
        flash_buffer[14] = Speed_R_PID.Kd;
        flash_buffer[15] = Ring_Dir_Flag[0];
        flash_buffer[16] = Ang_Gyro_Y_Zero;
        flash_buffer[17] = Ang_Gyro_Z_Zero;
        flash_buffer[18] = Mode_Choose;
        flash_buffer[19] = Buzzer_Open;
        flash_buffer[20] = Kg;
        flash_buffer[21] = Dt;
        flash_buffer[22] = Ring_Dir_Flag[1];
        flash_buffer[23] = Ring_Dir_Flag[2];
        flash_buffer[24] = Start_Open;
        flash_buffer[25] = Ramp_Choose;
        flash_buffer[26] = Debug;
        flash_buffer[27] = SetPodaoA;
        flash_buffer[28] = SetPodaoC;
        flash_buffer[29] = sentdata;
        flash_buffer[30] = Ramp_Ring;
        flash_buffer[31] = Obstacle_down;
        flash_buffer[32] = Ring_jianshu;

        flash_buffer[33] = laxian_k;
        flash_buffer[34] = Podao_bisai;
        flash_buffer[35] = Up_Speed;
        flash_buffer[36] = Angle_Line;
        flash_buffer[37] = Down_Speed;
        flash_buffer[38] = I_TimeA;
        flash_buffer[39] = I_TimeB;
        flash_buffer[40] = Ramp_Up_Num;
        flash_buffer[41] = Ramp_Down_Num;
        flash_buffer[42] = lanxian_flag;
        flash_buffer[43] = small_p;
        flash_buffer[44] = mid_p;
        flash_buffer[45] = big_p;
        flash_buffer[46] = small_ring;
        flash_buffer[47] = guai_switch_flag;
        flash_buffer[48] = small_state_2;
        flash_buffer[49] = small_state_num;
        flash_buffer[50] = small_state_2_p;

        flash_buffer[51] = ftm_add_flag;
        flash_buffer[52] = ftm_add;
        FLASH_EraseSector(242);
        FLASH_WriteSector(242, 150, (uint8_t *)flash_buffer);
    }
}
/*
 *好像没怎么用
 */
void Level_Switch()
{
    if (Level == 1)
    {
        Mode = 3;
        SpTurn = 300;
        Angle_PID.Kp = 185;
        Angle_PID.Kd = 140;
        Direction_PID.Kp = 650;
        Direction_PID.KTd = 30;
        Direction_PID.Kd = 0;
        Speed_L_PID.Kp = 1500;
        Speed_L_PID.Ki = 20;
        Speed_L_PID.Kd = 0;
        SetPodaoA = 150;
        SetPodaoC = 0;
        Up_Speed = 260;
        Down_Speed = 310;
        Ring_jianshu = 0;
        Obstacle_down = 6;
        Ramp_Ring = 6;
        lanxian_flag = 1;
        laxian_k = 25;
        small_ring = 0;
        small_p = 660;
        mid_p = 700;
        big_p = 700;
    }
    else if (Level == 2)
    {
        Mode = 3;
        SpTurn = 320;
        Angle_PID.Kp = 185;
        Angle_PID.Kd = 140;
        Direction_PID.Kp = 650;
        Direction_PID.KTd = 30;
        Direction_PID.Kd = 0;
        Speed_L_PID.Kp = 1500;
        Speed_L_PID.Ki = 20;
        Speed_L_PID.Kd = 0;
        SetPodaoA = 250;
        SetPodaoC = 0;
        Up_Speed = 260;
        Down_Speed = 310;
        Ring_jianshu = 0;
        Obstacle_down = 6;
        Ramp_Ring = 6;
        lanxian_flag = 0;
        //laxian_k = 25;
        small_ring = 0;
        small_p = 670;
        mid_p = 700;
        big_p = 700;
    }
    else if (Level == 3)
    {
        Mode = 3;
        SpTurn = 330;
        Angle_PID.Kp = 185;
        Angle_PID.Kd = 140;
        Direction_PID.Kp = 650;
        Direction_PID.KTd = 30;
        Direction_PID.Kd = 0;
        Speed_L_PID.Kp = 1500;
        Speed_L_PID.Ki = 20;
        Speed_L_PID.Kd = 0;
        SetPodaoA = 250;
        SetPodaoC = 0;
        Up_Speed = 250;
        Down_Speed = 320;
        Ring_jianshu = 0;
        Obstacle_down = 6;
        Ramp_Ring = 6;
        lanxian_flag = 0;
        //laxian_k = 25;3

        small_ring = 0;
        small_p = 680;
        mid_p = 700;
        big_p = 700;
    }
    else if (Level == 4)
    {
        Mode = 3;
        SpTurn = 340;
        Angle_PID.Kp = 185;
        Angle_PID.Kd = 140;
        Direction_PID.Kp = 650;
        Direction_PID.KTd = 30;
        Direction_PID.Kd = 0;
        Speed_L_PID.Kp = 1500;
        Speed_L_PID.Ki = 20;
        Speed_L_PID.Kd = 0;
        SetPodaoA = 300;
        SetPodaoC = 0;
        Up_Speed = 250;
        Down_Speed = 330;
        Ring_jianshu = 0;
        Obstacle_down = 6;
        Ramp_Ring = 6;
        lanxian_flag = 0;
        //laxian_k = 25;
        small_ring = 0;
        small_p = 690;
        mid_p = 700;
        big_p = 700;
    }
}
/*
 *菜单 最重要的部分
 */
void anjian_menu(void)
{
    static uint8_t hang = 1;
    uint8_t final_hang = 0, page = 0, i, Level_Last = 0;
    OLED_Clear();

    while (1)
    {
        if (Level_Last != Level)
        {
            Level_Switch();
            Level_Last = Level;
        }
        if (Debug == 1 && Level == 0)
            Accer_Folloew_Flag = 1;
        else
            Accer_Folloew_Flag = 0;

        if (Key_Up == 0)
        {
            DelayMs(100);
            if (Key_Up == 0)
            {
                hang--;
                if (hang == 0)
                    hang = Number_All;
                OLED_Clear();
            }
        }

        if (Key_Down == 0) //??ò?
        {
            DelayMs(100);
            if (Key_Down == 0)
            {
                hang++;
                if (hang == Number_All + 1)
                    hang = 1;
                OLED_Clear();
            }
        }

        if (Key_Add == 0) //?ó
        {
            DelayMs(100);
            if (Key_Add == 0)
                (*(Menu_name[hang - 1].num)) = (*(Menu_name[hang - 1].num)) + Menu_name[hang - 1].sub;
        }

        if (Key_Minus == 0) //??
        {
            DelayMs(100);
            if (Key_Minus == 0)
            {
                if (*(Menu_name[hang - 1].num) >= 0)
                {

                    if ((*(Menu_name[hang - 1].num)) - Menu_name[hang - 1].sub >= 0)
                    {
                        (*(Menu_name[hang - 1].num)) = (*(Menu_name[hang - 1].num)) - Menu_name[hang - 1].sub;
                    }

                    else
                    {

                        (*(Menu_name[hang - 1].num)) = 0;
                    }
                }
                else
                {
                    *(Menu_name[hang - 1].num) = (*(Menu_name[hang - 1].num)) - Menu_name[hang - 1].sub;
                }
            }
        }

        OLED_Write_Char(0, (hang - 1) % 4 * 2, 43); //?yí·

        if ((Number_All - 1) / 4 > (hang - 1) / 4)
        {
            page = (hang - 1) / 4;
            final_hang = 4;
        }

        else
        {
            page = (Number_All - 1) / 4;
            final_hang = Number_All % 4;
            if (final_hang == 0)
                final_hang = 4;
        }

        for (i = 1; i <= final_hang; i++)
        {
            OLED_Write_String(2, (i - 1) * 2, (uint8_t *)Menu_name[i - 1 + 4 * page].name);
            OLED_Write_String(10, (i - 1) * 2, (uint8_t *)":");
            OLED_Write_Num4(11, (i - 1) * 2, *(Menu_name[i - 1 + 4 * page].num));
        }

        if (Key_In == 0)
        {
            DelayMs(100);
            if (Key_In == 0)
            {
                OLED_Clear();
                Menu_Mode = 1;
                return;
            }
        }

        if (Key_Out == 0)
        {
            DelayMs(100);
            if (Key_Out == 0)
            {
                Flash_Write();
                OLED_Clear();
                OLED_Write_String(2, 2, (uint8_t *)"flash ok");
                DelayMs(300);
                return;
            }
        }
    }
}
