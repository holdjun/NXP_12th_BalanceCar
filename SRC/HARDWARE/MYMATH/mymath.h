#ifndef __MYMATH_H__
#define __MYMATH_H__
#include "stdint.h"
#ifdef __cplusplus
	extern "C" {
#endif
		
float mult_r(float get_data,float mult_get);
int16_t Math_Abs(int16_t value);//求绝对值		
float Math_Sign(float value,float range);//单位斜坡函数		
float Math_Limit(float value, int limit);//限制幅度		
float Math_Max(float value1, float value2);//求最大值		
float Math_Min(float value1, float value2);//求最小值		
float Math_Hysteresis(float value,float Hys_range);//迟滞函数		
float FIFO(double data_in,double* data_out,int DATACNT);//先入先出寄存器		
float Kalman_Buffer(float *Data,int DataCnt);//卡曼滤波		
int kalman_ACC1(int data);		
int kalman_ACC2(int data);
int kalman_GYRO1(int data);
int kalman_GYRO2(int data);		
int kalman_OUT(int data);		
float LegendreP(int n, float Value);
double Math_Sqrt(double Value,int cnt);
double Math_cos(double Value);
double Math_sin(double Value);
double Math_In(double Value,int cnt);
double LaguerreL(int N, double alpha, double Value);
float Buffer(float data);
float kalman_Steer(float data);
#ifdef __cplusplus
}
#endif

#endif		