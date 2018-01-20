#include "butter.h"
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
