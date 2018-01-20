#ifndef _RUN_H_
#define _RUN_H_
#include "stdint.h"
#define Image_Height 70
#define Image_Width 200
void Stop(void);
void Run(void);
void SignalProcess(void);
void AngleControl(void);
void SpeedControl(void);
void SpeedControlOutput(void);
void DirectionControl(void);
void DirectionControlOutput(void);
void MotorOutput(void); 
void Encoder_Protection(void);
int16_t Speed_Add(int16_t speedl,int16_t speedr);
#endif
