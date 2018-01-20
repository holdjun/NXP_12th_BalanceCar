#include "Motor.h"
//#include "run.h"
#include "ftm.h"
#include "oled.h"
#include "extern.h"
#include "camera.h"
#include "menu.h"
#include "math.h"
#include "stdint.h"
#include "angle.h"
#include "menu.h"
#include "delay.h"
#include "mymath.h"



////中断标志位
//uint8_t g_nSpeedControlPeriod=0; 
//uint8_t  g_nDirectionControlPeriod=0;
//uint8_t g_nSpeedControlCount=0;
//uint8_t g_nDirectionControlCount=0;

////
//int16_t Speed_fDelta_Last=0;
//int16_t Speed_Delta_Max=40;
//int16_t Set_Speed=0;
//int16_t Run_Speed=200;
//int16_t RSpeed=0;
//int16_t LSpeed=0;
//int16_t Max=9999;
//int16_t Min=-9999;
//int16_t Encoder_Max=800;
//int16_t Encoder_Min=-800;
//int16_t  Least_Speed=0;
//int16_t Encoder_Left;
//int16_t Encoder_Right;
//int LSpeed_Last=0;
//int RSpeed_Last=0;

////int16_t Encoder_Left_Temp=0;
////int16_t Encoder_Right_Temp=0;
//int16_t M_LeftError[3];
//int16_t M_RightError[3];

////不用的xxxx
//float ML_kp=1;
//float ML_ki=0;
//float ML_kd=0;
//float MR_kp=1;
//float MR_ki=0;
//float MR_kd=0;
//int16_t g_CarSpeed_Last=0;
//int16_t Encoder_Left_Last=0;
//int16_t Encoder_Right_Last=0;
//int16_t g_CarSpeed=0;
//int g_fAngleControlOut=0;
//int g_SpeedControlIntegral=0;
//int g_fSpeedControlOutOld;
//int g_fSpeedControlOutNew;
//int g_fSpeedControlOut=0;
//int g_fDirectionControlOutOld;
//int g_fDirectionControlOutNew;
//int g_fDirectionControlOut=0;
//int16_t g_fLeftMotorOut;
//int16_t g_fRightMotorOut;
////电机PID公式--------------------------------------------------------
//int Motor_LeftPID(int set,int yout)
//{
//	int M_LeftOut=0;//目标与输出的偏差值
//	M_LeftError[2]=set-yout;
//	M_LeftOut+=ML_ki*M_LeftError[2];
//	M_LeftOut+=ML_kp*(M_LeftError[2]-M_LeftError[1]);	
//	M_LeftOut+=ML_kd*(M_LeftError[2]-2*M_LeftError[1]+M_LeftError[0]);
//	M_LeftError[0]=M_LeftError[1];
//	M_LeftError[1]=M_LeftError[2];
//	return M_LeftOut;
//}	
//int Motor_RightPID(int set,int yout)
//{
//	int M_RightOut=0;//目标与输出的偏差值
//	M_RightError[2]=set-yout;
//	M_RightOut+=MR_ki*M_RightError[2];
//	M_RightOut+=MR_kp*(M_RightError[2]-M_RightError[1]);	
//	M_RightOut+=MR_kd*(M_RightError[2]-2*M_RightError[1]+M_RightError[0]);
//	M_RightError[0]=M_RightError[1];
//	M_RightError[1]=M_RightError[2];
//	return M_RightOut;
//}	

////	//PID输出*******************
////	LSpeed=Motor_LeftPID(Left_Aim,Left_Speed)+LSpeed;
////	RSpeed=Motor_RightPID(Right_Aim,Right_Speed)+RSpeed;

//void Encoder_Protection()
//{
//	if(Encoder_Left>Encoder_Max&&Encoder_Right>Encoder_Max)
//	{
//			while(1)
//			{
//				NVIC_DisableIRQ(PIT1_IRQn);
//				FTM_PWM_ChangeDuty(FTM_Right_Forward,0);
//				FTM_PWM_ChangeDuty(FTM_Left_Forward,0);		
//				FTM_PWM_ChangeDuty(FTM_Right_Backward,0);
//				FTM_PWM_ChangeDuty(FTM_Left_Backward,0);
//				
//				if(Key_In==0)
//				{	
//					DelayMs (10);
//					if(Key_In==0)
//					{
//						OLED_Clear();	
//						NVIC_EnableIRQ(PIT1_IRQn);						
//						while(Key_In==0);
//						break;
//					}
//			}		
//		}	
//	}
//	else if(Encoder_Right<Encoder_Min&&Encoder_Left<Encoder_Min)
//	{

//			while(1)
//			{
//				NVIC_DisableIRQ(PIT1_IRQn);
//				FTM_PWM_ChangeDuty(FTM_Right_Forward,0);
//				FTM_PWM_ChangeDuty(FTM_Left_Forward,0);		
//				FTM_PWM_ChangeDuty(FTM_Right_Backward,0);
//				FTM_PWM_ChangeDuty(FTM_Left_Backward,0);
//				
//				if(Key_In==0)
//				{	
//					DelayMs (10);
//					if(Key_In==0)
//					{
//						OLED_Clear();	
//						NVIC_EnableIRQ(PIT1_IRQn);						
//						while(Key_In==0);
//						break;
//					}
//				}		
//			}	
//	}		
//}
//void Speed_In(int16_t LSpeed,int16_t RSpeed)
//{
//		
//	if(LSpeed>Max)
//		LSpeed=Max;
//	else if(LSpeed<Min)
//		LSpeed=Min;
//	if(RSpeed>Max)
//		RSpeed=Max;
//	else if(RSpeed<Min)
//		RSpeed=Min;
//	
//	if(LSpeed>=0&&RSpeed>=0)
//	{		
//		FTM_PWM_ChangeDuty(FTM_Left_Forward,Least_Speed+LSpeed);
//		FTM_PWM_ChangeDuty(FTM_Left_Backward,0);
//		FTM_PWM_ChangeDuty(FTM_Right_Forward,Least_Speed+RSpeed);
//		FTM_PWM_ChangeDuty(FTM_Right_Backward,0);
//	}
//	else if(LSpeed<0&&RSpeed<0)
//	{
//		FTM_PWM_ChangeDuty(FTM_Left_Forward,0);
//		FTM_PWM_ChangeDuty(FTM_Left_Backward,Least_Speed-LSpeed);
//		FTM_PWM_ChangeDuty(FTM_Right_Forward,0);
//		FTM_PWM_ChangeDuty(FTM_Right_Backward,Least_Speed-RSpeed);
//	}
//	else if(LSpeed>=0&&RSpeed<0)
//	{
//		FTM_PWM_ChangeDuty(FTM_Left_Forward,Least_Speed+LSpeed);
//		FTM_PWM_ChangeDuty(FTM_Left_Backward,0);
//		FTM_PWM_ChangeDuty(FTM_Right_Forward,0);
//		FTM_PWM_ChangeDuty(FTM_Right_Backward,Least_Speed-RSpeed);
//	}
//	else if (LSpeed<0&&RSpeed>=0)
//	{
//		FTM_PWM_ChangeDuty(FTM_Left_Forward,0);
//		FTM_PWM_ChangeDuty(FTM_Left_Backward,Least_Speed-LSpeed);
//		FTM_PWM_ChangeDuty(FTM_Right_Forward,Least_Speed+RSpeed);
//		FTM_PWM_ChangeDuty(FTM_Right_Backward,0);
//	}
//}



//void AngleControl(void) 
//{
//	g_fAngleControlOut = (int)(Angle-Ang_ACC_Mid)* ANGLE_CONTROL_P/10 +(int)(Ang_Gyro_Y+4)* ANGLE_CONTROL_D/10;
//}

//void SpeedControl(void) 
//{
//	int16_t fDelta;
//	int  fP;
//	int  fD;
//	g_fSpeedControlOutOld = g_fSpeedControlOutNew;
//	Encoder_Left_Last=Encoder_Left;
//	Encoder_Right_Last=Encoder_Right;		
//	g_CarSpeed= (Encoder_Left+Encoder_Right)/2;
//	fDelta = Set_Speed - g_CarSpeed;
//	fP = (int)(fDelta) * SPEED_CONTROL_P/10;
////	g_SpeedControlIntegral+=fDelta*SPEED_CONTROL_I/10;
////	if(g_SpeedControlIntegral>5000)
////		g_SpeedControlIntegral=5000;
////	else if(g_SpeedControlIntegral<-5000)
////		g_SpeedControlIntegral=-5000;	
//	fD=(int)(fDelta-Speed_fDelta_Last)*SPEED_CONTROL_D/10;
//	Speed_fDelta_Last=fDelta;
//  g_fSpeedControlOutNew = fP+fD; 
//	if(g_fSpeedControlOutNew>=8000)
//		g_fSpeedControlOutNew=8000;
//	else if(g_fSpeedControlOutNew<=-1000)
//		g_fSpeedControlOutNew=-1000;
//}
////void SpeedControl(void) 
////{
////	uint8_t index;
////	int16_t fDelta;
////	int  fP;
////	int fI;
////	g_CarSpeed= (Encoder_Left+Encoder_Right)/2;
////	fDelta = SpTurn - g_CarSpeed;
////	if(fI>=6000)
////	{	
////		if(Math_Abs(fDelta)>=Speed_Delta_Max) //积分分离过程      
////		{
////				index=0;
////		}
////		else
////		{
////			index=1;
////			if(fDelta<0)
////			{
////					g_SpeedControlIntegral+=fDelta;
////			}
////		}
////	}
////	else if(fI<=-6000)
////	{	
////		if(Math_Abs(fDelta)>=Speed_Delta_Max) //积分分离过程      
////		{
////				index=0;
////		}
////		else
////		{
////			index=1;
////			if(fDelta>0)
////			{
////					g_SpeedControlIntegral+=fDelta;
////			}
////		}
////	}
////	else
////	{
////		if(Math_Abs(fDelta)>=Speed_Delta_Max) //积分分离过程      
////		{
////				index=0;
////		}
////		else
////		{
////				index=1;
////				g_SpeedControlIntegral+=fDelta;
////		}
////	}
////	g_fSpeedControlOutOld = g_fSpeedControlOutNew;
////	fP = (int)(fDelta) * SPEED_CONTROL_P/10;
////	fI =index*(int)(g_SpeedControlIntegral) * SPEED_CONTROL_I/10;
////	//限幅
////	if(fI>=8000)
////		fI=8000;
////	else if(fI<=-8000)
////		fI=-8000;
////	if(fP>=9000)
////		fP=9000;
////	else if(fP<=-9000)
////		fP=-9000;
////	
////  g_fSpeedControlOutNew =  fP+fI;  
////	if(g_fSpeedControlOutNew>=9000)
////		g_fSpeedControlOutNew=9000;
////	else if(g_fSpeedControlOutNew<=-9000)
////		g_fSpeedControlOutNew=-9000;
////}
//void SpeedControlOutput(void) 
//{
//	int16_t fValue;
//	fValue = g_fSpeedControlOutNew - g_fSpeedControlOutOld;
//	g_fSpeedControlOut = (int16_t)(fValue * (g_nSpeedControlCount + 1)*1.0 /SPEED_CONTROL_COUNT + g_fSpeedControlOutOld);
//}
//void DirectionControl(void) 
//{
//	int fPValue;
//	int fDValue;
//	g_fDirectionControlOutOld = g_fDirectionControlOutNew;
//	fPValue =(int)Error_turn* DIR_CONTROL_P/10;
//	fDValue =(int)(Ang_Gyro_Z)*DIR_CONTROL_D/10;
//	g_fDirectionControlOutNew = fPValue-fDValue;
//		//限幅
////	if(g_fDirectionControlOutNew>=7000)
////		g_fDirectionControlOutNew=7000;
////	else if(g_fDirectionControlOutNew<=-7000)
////		g_fDirectionControlOutNew=-7000;	
//}
//void DirectionControlOutput(void) 
//{
//	int16_t Value;
//	Value = g_fDirectionControlOutNew - g_fDirectionControlOutOld;
//	g_fDirectionControlOut = Value * (g_nDirectionControlCount + 1) / DIRECTION_CONTROL_COUNT + g_fDirectionControlOutOld;
//}
//void MotorOutput(void) 
//{	

//LSpeed = g_fAngleControlOut - g_fSpeedControlOut - g_fDirectionControlOut;
//RSpeed = g_fAngleControlOut - g_fSpeedControlOut + g_fDirectionControlOut;
////if(Encoder_Left>=SpTurn+80&&Encoder_Right>=SpTurn-80)
////{
////	LSpeed=LSpeed_Last;
////}
////if(Encoder_Right>=SpTurn+80&&Encoder_Left>=SpTurn-80)
////{
////	RSpeed=RSpeed_Last;
////}
////LSpeed_Last=LSpeed;
////RSpeed_Last=RSpeed;
////LSpeed = g_fAngleControlOut - g_fSpeedControlOut;
////RSpeed = g_fAngleControlOut - g_fSpeedControlOut ;
//	
////	LSpeed = g_fAngleControlOut ;
////	RSpeed = g_fAngleControlOut;
////	
////	LSpeed = SpTurn;
////	RSpeed = SpTurn;
////	}

////	LSpeed = g_fAngleControlOut-1000;
////	RSpeed = g_fAngleControlOut+1000 ;
////		LSpeed = g_fAngleControlOut - g_fSpeedControlOut + 1000;
////	RSpeed = g_fAngleControlOut - g_fSpeedControlOut - 1000;
//}











