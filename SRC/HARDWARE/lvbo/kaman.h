#include "sys.h"
//#include "jifen.h"
#include <math.h>
#include "oled.h"
#define TYPEKAMN int16_t
/*________加速度滤波大法____________*/
/*________加速度滤波大法____________*/
/*________加速度滤波大法____________*/



/*________加速度滤波大法____________*/


/*________加速度滤波大法____________*/
/*________加速度滤波大法____________*/
/*________加速度滤波大法____________*/
#define Accelerometer_R (240)//加速度计的R
#define Accelerometer_Q (25)//加速度计的Q
#define Gyroscope_R (320)//陀螺仪的R
#define Gyroscope_Q (40)//陀螺仪的Q
#define Gyroscope_R_Z (320)
#define Gyroscope_Q_Z (40)





#define Diroct_R (160)//陀螺仪的R
#define Diroct_Q (80)//陀螺仪的Q
TYPEKAMN Kaman_Accelerometer(TYPEKAMN signal);
TYPEKAMN Kaman_Gyroscope(TYPEKAMN signal);
TYPEKAMN Kaman_Gyroscope_Z(TYPEKAMN signal);
float Kalman_LvBo(int16_t angle, int16_t Gyro_X);
double Kaman_Angle(double signal);
int Kaman_Diroct_Out(int data);

//void Kaman_Init(void);
/*
  500-3
	100-0.8
	300-0.8
	      Q:过程噪声,Q增大,动态响应变快，收敛稳定性变坏
        R:测量噪声,R增大，动态响应变慢，收敛稳定性变好
*/
//extern uint16_t pianzhi ;

