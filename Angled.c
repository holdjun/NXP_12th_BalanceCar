#include "angle.h"
#include "IMU_IIC.h"
#include "L3G4200D.h"
#include "mma8451.h"
#include "math.h"
#include "extern.h"
#include "oled.h"
#include "menu.h"
#include "kaman.h"
#include "stdint.h"
#include "stdio.h"
#include "Filter.h"

int16_t MMA8451_OUT_X = 0, MMA8451_OUT_Y = 0, MMA8451_OUT_Z = 0;
int16_t L3G4200D_OUT_Y, L3G4200D_OUT_Z, L3G4200D_OUT_X;
int16_t Ang_ACC_X;
int16_t Ang_ACC_Z;
int16_t Ang_Gyro_X;
int16_t Ang_Gyro_Y;
int16_t Ang_Gyro_Z;
int16_t Ang_Gyro_Y_Zero;
int16_t Ang_Gyro_Z_Zero;
int16_t Ang_IGyro_Temper = 0;
double Angle = 0;
double Ang_IGyro = 0;
double Angle_Temper = 0;

int16_t Max3(int16_t O1, int16_t O2, int16_t O3)
{
    int16_t max = 0;
    if (O1 > O2)
        max = O1;
    else
        max = O2;
    if (max < O3)
        max = O3;
    return max;
}
int16_t Min3(int16_t O1, int16_t O2, int16_t O3)
{
    int16_t min = 0;
    if (O1 < O2)
        min = O1;
    else
        min = O2;
    if (min > O3)
        min = O3;
    return min;
}

int16_t Pseudo_median_filtering(int16_t nowdata)
{
    int16_t Final = 0;
    int8_t i = 0;
    int16_t Max_Min = 0,
            Min_Max = 0;
    static int16_t Data[5] = {0};
    for (i = 4; i > 0; i--)
    {
        *(Data + i) = *(Data + i - 1);
    }
    *Data = nowdata;
    Max_Min = Max3(Min3(Data[0], Data[1], Data[2]), Min3(Data[1], Data[2], Data[3]), Min3(Data[2], Data[3], Data[4]));
    Min_Max = Min3(Max3(Data[0], Data[1], Data[2]), Max3(Data[1], Data[2], Data[3]), Max3(Data[2], Data[3], Data[4]));
    Final = (Max_Min + Min_Max) >> 1;
    return Final;
}

void Get_Angle()
{
    MMA8451_OUT_X = MMA8451_GetResult(MMA8451_STATUS_Z_READY, MMA8451_REG_OUTZ_MSB);
    L3G4200D_OUT_Y = L3G4200D_GetResult(L3G4200D_STATUS_REG, L3G4200D_OUT_Y_H) - Ang_Gyro_Y_Zero;
    L3G4200D_OUT_Z = -L3G4200D_GetResult(L3G4200D_STATUS_REG, L3G4200D_OUT_X_H) - Ang_Gyro_Z_Zero;
    Ang_ACC_X = Kaman_Accelerometer(MMA8451_OUT_X);
    Ang_ACC_X = Ang_ACC_Moving_Average_Filter(Ang_ACC_X);
    Ang_Gyro_Y = Kaman_Gyroscope(L3G4200D_OUT_Y);
    Ang_Gyro_Z = Kaman_Gyroscope_Z(L3G4200D_OUT_Z);
    Angle_Temper = Ang_IGyro * 1.0 + Ang_Gyro_Y * Dt * 0.0001;
    Ang_IGyro = Angle_Temper * 1.0 + (Ang_ACC_X - Angle_Temper) * Kg * 0.001;
    Angle = Angle_Temper;
}
