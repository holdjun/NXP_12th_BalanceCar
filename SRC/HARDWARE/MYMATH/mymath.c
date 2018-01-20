#include "mymath.h"
#include "stdint.h"


/********************************************************************************************************/
/*                                               mymath                                                 */
/********************************************************************************************************/

float mult_r(float get_data,float mult_get)
{

	float temp;

	temp = get_data/mult_get;
	return temp;

}


int16_t Math_Abs(int16_t value)//求绝对值
{
	  if(value < 0)
	  {
		    return -value;
	  }
	  else
	  {
		    return value;
	  }
}

float Math_Sign(float value,float range)//单位斜坡函数
{
    if(Math_Abs(value) < range)
    {
   		  return value / range;
    }
    else
    {
    	  if(value > 0)
    	  {
    		    return 1;
    	  }
        else if(value < 0)
        {
        	  return -1;	
        }
        else
        {
            return 0;
        }	
    }
}



float Math_Limit(float value, int limit)//限制幅度
{
	  if(value > limit)
	  {
		    return limit;
	  }
	  else if(value < -limit)
	  {
		    return -limit;
	  }
	  else
	  {
		    return value;
	  }
}

float Math_Max(float value1, float value2)//求最大值
{
	  if(value1 > value2)
	  {
		    return value1;
	  }
	  else
	  {
		    return value2;
	  }
}

float Math_Min(float value1, float value2)//求最小值
{
	  if(value1 > value2)
	  {
		    return value2;
	  }
	  else
	  {
		    return value1;
	  }
}

float Math_Hysteresis(float value,float Hys_range)//迟滞函数
{
	static uint8_t Hys_Flag=0;
	if(Hys_Flag)
	{
			if(value > -Hys_range)
			{
					Hys_Flag=0;
				  return 1;
			}
			else 
			{
					return -1;
			}
	}
	if(!Hys_Flag)
  {
			if(value < Hys_range)
			{
					Hys_Flag=1;
				  return -1;
			}
			else 
			{
					return 1;
			}	
	}
	return 0;
}
/****************************************************/
/*函数功能：快速求ln(x)*/
/*函数特点：cnt为运算次数*/
/*函数特点：减少运算量，并提高运算速度*/
/*函数注意：为增加运算速度可以将double改为float*/
/****************************************************/
double Math_In(double Value,int cnt)
{
   int i=0;
   double tmp = (Value - 1) / (Value + 1);
   double func=0;
   for(i=cnt;i>=0;i--)
   {
       func=func*tmp+1/(2*i+1);//秦九昭算法求多项式值
   }
   func=func*tmp*2;
   return func;
}



/****************************************************/
/*函数功能：泰勒展开级数求sin(x)*/
/*函数注意：要求绝对误差小Q=0.775,P=0.225，相对误差小 Q=0.782,P=0.218，输入为弧度不是角度*/
/*函数注意：为增加运算速度可以将double改为float*/
/****************************************************/
double Math_sin(double Value)
{
   const double P=0.225;//Q=0.775;// Q=0.782,P=0.218
   const double div4PI=1.27324;//4/PI
   const double div4PI2=0.40528;//-4/PI/PI
   double func;
   const double mPI=3.14159;//4/PI
   while(Math_Abs(Value)>=mPI)
    {
       if(Value>0)
        {
           Value=Value-mPI;
        }
       else
        {
           Value=Value+mPI;
        }
    }
   func=div4PI*Value-div4PI2*Value*Math_Abs(Value);
   func=P*(func*Math_Abs(func)-func)+func;
   return func;
}

/****************************************************/
/*函数功能：泰勒展开级数求cos(x)*/
/*函数注意：要求绝对误差小Q=0.775,P=0.225，相对误差小 Q=0.782,P=0.218，输入为弧度不是角度*/
/*函数注意：为增加运算速度可以将double改为float*/
/****************************************************/
double Math_cos(double Value)
{
	const double div2PI=1.57080;
	return Math_sin(div2PI-Value);
}

/****************************************************/
/*函数功能：迭代法求sqrt(a)*/
/*函数特点：cnt为运算次数*/
/*函数注意：为增加运算速度可以将double改为float,并且输入值可以适当归一化*/
/****************************************************/
double Math_Sqrt(double Value,int cnt)
{
   int i=0;
   double tmp;
   double func=0;
   for(i=cnt;i>=0;i--)
   {
       tmp=(tmp+Value/tmp)/2;//迭代法求多项式值
   }
   func=tmp;
   return func;
}

/****************************************************/
/*函数功能：迭代法求勒让德多项式值*/
/*函数特点：n为运算次数*/
/*函数注意：为增加运算速度可以将double改为float,并且输入值可以适当归一化*/
/****************************************************/

float LegendreP(int n, float Value)
{
	if (n == 0)
	{
		return 1;
	}
	else if (n == 1)
	{
		return Value;
	}
	else
	{
		return (float)((2 * n - 1) * Value * LegendreP(n - 1, Value) - (n - 1) * LegendreP(n - 2, Value)) / n;
	}
}

/****************************************************/
/*函数功能：迭代法求拉盖尔多项式值*/
/*函数特点：n为运算次数*/
/*函数注意：当alpha!=0时该算法自动转换为广义拉盖尔*/
/*函数注意：为增加运算速度可以将double改为float,并且输入值可以适当归一化*/
/****************************************************/
double LaguerreL(int N, double alpha, double Value)
{
	int i;
	double Lagu = 1, Bin = 1;
	for (i = N; i > 0; i--)//使用秦九昭算法
	{
		Bin = Bin * (alpha + i) / (N + 1 - i);
		Lagu = Bin - Value * Lagu / i;
	}
	return Lagu;
}
/********************************************************************************************************/
/*                                               Buffer                                                 */
/********************************************************************************************************/

float FIFO(double data_in,double* data_out,int DATACNT)//先入先出寄存器
{
    int i;
    
    float result;
    
    result=*(data_out+DATACNT-1);
    
    for(i=1;i<DATACNT;i++)
    {
        
        *(data_out+i)=*(data_out+i-1);          //对数据进行移位操作
        
    }
    
    *data_out=data_in;
    
    return result;                              //返还先入先出结果
}


/********************************************************************************************************/
/*                                               Filter                                                 */
/********************************************************************************************************/

float Kalman_Buffer(float *Data,int DataCnt)//卡曼滤波
{
    float kg,x_mid,x_now,x_last,p_mid,p_now;   
    
    static float p_last=10;
    
    const float Q=100;
    
    const float R=1;
    
    int i;
    
    for(i=0;i<DataCnt;i++)
    {                                          //x(k|k-1)=F(k)*x^(k-1|k-1)+B(k)*u(k-1)   //隐含条件
        
            x_mid=x_last;                      //x_last=x(k-1|k-1),   x_mid=x(k|k-1)
        
            p_mid=p_last+Q;                    //p_mid=p(k|k-1),      p_last=p(k-1|k-1),Q=噪声  //F(k)=1 H(k)=1
        
            kg=p_mid/(p_mid+R);                //kg为kalman filter，R为噪声      //kg=p(k|k-1)/(p(k|k-1)+R(k))                       
        
            x_now=x_mid+kg*(*(Data+i)-x_mid);  //估计出的最优值       //e(k)=y(k)-x(k|k-1)      //x^(k)=x(k|k-1)+Kg*e(k) 
        
            p_now=(1-kg)*p_mid;                //最优值对应的covariance   //p(k|k)=(1-kg)*p(k|k-1)

            p_last = p_now;                    //更新covariance值
        
            x_last = x_now;                    //更新系统状态值
    }
    
    
    return x_now;

}


int kalman_ACC1(int data)
{
  static float p1=6;
  static float c1=5;
  const int q=5;
  const int r=10;
  float kg,c2,p2;

  p2=p1+q;
  kg=p2*p2/(p2*p2+r*r);
  c2=c1+kg*(data-c1);
  p1=(1-kg)/p2;
  c1=c2;

  return c1; 
}


int kalman_ACC2(int data)
{
  static float p1=6;
  static float c1=5;
  const int q=5;
  const int r=10;
  float kg,c2,p2;

  p2=p1+q;
  kg=p2*p2/(p2*p2+r*r);
  c2=c1+kg*(data-c1);
  p1=(1-kg)/p2;
  c1=c2;

  return c1; 
}



int kalman_GYRO1(int data)
{
  static float p1=6;
  static float c1=5;
  const int q=3;
  const int r=10;
  float kg,c2,p2;

  p2=p1+q;
  kg=p2*p2/(p2*p2+r*r);
  c2=c1+kg*(data-c1);
  p1=(1-kg)/p2;
  c1=c2;

  return c1; 
}


int kalman_GYRO2(int data)
{
  static float p1=6;
  static float c1=5;
  const int q=5;
  const int r=10;
  float kg,c2,p2;

  p2=p1+q;
  kg=p2*p2/(p2*p2+r*r);
  c2=c1+kg*(data-c1);
  p1=(1-kg)/p2;
  c1=c2;

  return c1; 
}



int kalman_OUT(int data)
{
  static float p1=6;
  static float c1=5;
  const int q=2;
  const int r=10;
  float kg,c2,p2;

  p2=p1+q;
  kg=p2*p2/(p2*p2+r*r);
  c2=c1+kg*(data-c1);
  p1=(1-kg)/p2;
  c1=c2;

  return c1; 
}

float kalman_Steer(float data)
{
  static float p1=6;
  static float c1=5;
  const float q=5;
  const float r=10;
  float kg,c2,p2;

  p2=p1+q;
  kg=p2*p2/(p2*p2+r*r);
  c2=c1+kg*(data-c1);
  p1=(1-kg)/p2;
  c1=c2;

  return c1; 
}




//数字滤波
float Buffer(float data)
{
	static float Y[5];
	static float YBuffer[5];
	
	YBuffer[0]=YBuffer[1];		
	YBuffer[1]=YBuffer[2];	
	YBuffer[2]=YBuffer[3];
	YBuffer[3]=YBuffer[4];
	YBuffer[4]=data;
	
	Y[0]=Y[1];
	Y[1]=Y[2];	
	Y[2]=Y[3];	
	Y[3]=Y[4];
	Y[4]=0.0022*YBuffer[4]+0.0089*YBuffer[3]+ 0.0134*YBuffer[2]+0.0089*YBuffer[1]+0.0022*YBuffer[0]-(0.2645*Y[0]-1.4035*Y[1]+2.8674*Y[2]-2.6926*Y[3] );
	return Y[4];
}




