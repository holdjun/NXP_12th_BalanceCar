#include "Filter.h"
//滑动平均滤波
int16_t Ang_ACC_Moving_Average_Filter(int16_t nowdata)
{
	int16_t Final=0;
	int8_t i=0;
	static int16_t Data[8]=	{	0	};	//X轴加速度临时值
	for(i=7;i>0;i--)
	{
		*(Data+i) = *(Data+i-1);
	}
	*Data = nowdata;
	Final=(*Data +*(Data+1)+*(Data+2)+*(Data+3)+*(Data+4)+*(Data+5)+*(Data+6)+*(Data+7))>>3;
	for(i=7;i>0;i--)
	{
		*(Data+i) = *(Data+i-1);
	}
	*Data = Final;
	return Final;
}
//滑动平均滤波
int16_t Ang_Gyro_Moving_Average_Filter(int16_t nowdata)
{
	int16_t Final=0;
	int8_t i=0;
	static int16_t Data[8]=	{	0	};	//X轴加速度临时值
	for(i=7;i>0;i--)
	{
		*(Data+i) = *(Data+i-1);
	}
	*Data = nowdata;
	Final=(*Data +*(Data+1)+*(Data+2)+*(Data+3)+*(Data+4)+*(Data+5)+*(Data+6)+*(Data+7))>>3;
	for(i=7;i>0;i--)
	{
		*(Data+i) = *(Data+i-1);
	}
	*Data = Final;
	return Final;
}

//加权滑动平均滤波
int16_t L_Encoder_Average_Filter(int16_t nowdata)
{
	int16_t Final=0;
	int8_t i=0;
	static int16_t Data[5]=	{	0	};	//编码速度临时值
	for(i=4;i>0;i--)
	{
		*(Data+i) = *(Data+i-1);
	}
	*Data = nowdata;
	Final=(*Data*30+*(Data+1)*25+*(Data+2)*20+*(Data+3)*15+*(Data+4)*10)/100;
	for(i=4;i>0;i--)
	{
		*(Data+i) = *(Data+i-1);
	}
	*Data = Final;
	return Final;
}
//加权滑动平均滤波
int16_t R_Encoder_Average_Filter(int16_t nowdata)
{
	int16_t Final=0;
	int8_t i=0;
	static int16_t Data[5]=	{	0	};	//编码速度临时值
	for(i=4;i>0;i--)
	{
		*(Data+i) = *(Data+i-1);
	}
	*Data = nowdata;
	Final=(*Data*30+*(Data+1)*25+*(Data+2)*20+*(Data+3)*15+*(Data+4)*10)/100;
	for(i=4;i>0;i--)
	{
		*(Data+i) = *(Data+i-1);
	}
	*Data = Final;
	return Final;
}
//加权滑动平均滤波
int16_t Ang_Gyro_Y_Average_Filter(int16_t nowdata)
{
	int16_t Final=0;
	int8_t i=0;
	static int16_t Data[5]=	{	0	};	//编码速度临时值
	for(i=4;i>0;i--)
	{
		*(Data+i) = *(Data+i-1);
	}
	*Data = nowdata;
	Final=(*Data*30+*(Data+1)*25+*(Data+2)*20+*(Data+3)*15+*(Data+4)*10)/100;
	for(i=4;i>0;i--)
	{
		*(Data+i) = *(Data+i-1);
	}
	*Data = Final;
	return Final;
}
//Butter滤波
double Butter(uint16_t nowdata)
{
	static double data[5]={0};
	static double outfinal[5]={0};
  double final=0;
	
	data[0]=data[1];
	data[1]=data[2];
	data[2] =data[3];
	data[3] =data[4];
	data[4] =nowdata;
	final =(B1*data[4]+B2*data[3]+B3*data[2]+B4*data[1]+B5*data[0]-A2*outfinal[4]-A3*outfinal[3]-A4*outfinal[2]-A5*outfinal[1])/A1;
	outfinal[0]=outfinal[1];
	outfinal[1]=outfinal[2];
	outfinal[2] =outfinal[3];
	outfinal[3] =outfinal[4];
	outfinal[4] =final;	
	return final;
}