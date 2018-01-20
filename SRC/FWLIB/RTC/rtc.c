/**
  ******************************************************************************
  * @file    rtc.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 实时时钟驱动
  ******************************************************************************
  */
#include "rtc.h"

/***********************************************************************************************
 功能：RTC初始化
 形参：0
 返回：0
 详解：初始化RTC
************************************************************************************************/
void RTC_Init(void)
{
	uint32_t i = 0;
	//开启RTC模块时钟
	SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
	//禁止 所有中断
	RTC->IER &= ~(RTC_IER_TIIE_MASK|RTC_IER_TOIE_MASK |RTC_IER_TAIE_MASK);
	//配置16pf电容，不向外界输出，开启晶振
	RTC->CR |= (0|RTC_CR_OSCE_MASK|RTC_CR_SC16P_MASK);
  //是晶振稳定的工作延时
	for(i=0;i<0x600000;i++);
	//使能RTC计时
	RTC->SR |= RTC_SR_TCE_MASK;  
	RTC_ITConfig(RTC_IT_TAF,ENABLE);	
	//将TAR定位到TSR 产生中断
	RTC->TAR = RTC->TSR;  
}


//中断配置
void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState)
{
	//检查参数
	assert_param(IS_RTC_IT(RTC_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	switch(RTC_IT)
	{
		case RTC_IT_TAF:
			(ENABLE == NewState)?(RTC->IER |= RTC_IER_TAIE_MASK):(RTC->IER &= ~RTC_IER_TAIE_MASK);
			break;
		case RTC_IT_TOF:
			(ENABLE == NewState)?(RTC->IER |= RTC_IER_TOIE_MASK):(RTC->IER &= ~RTC_IER_TOIE_MASK);
			break;
		case RTC_IT_TIF:
			(ENABLE == NewState)?(RTC->IER |= RTC_IER_TIIE_MASK):(RTC->IER &= ~RTC_IER_TIIE_MASK);
			break;
		default:break;
	}
	
}

//获得中断状态
ITStatus RTC_GetITStatus(uint16_t RTC_IT)
{
	ITStatus retval;
	//检查参数
	assert_param(IS_RTC_IT(RTC_IT));
	
	switch(RTC_IT)
	{
		case RTC_IT_TAF:
 		 (RTC->SR & RTC_SR_TAF_MASK)?(retval = SET):(retval = RESET);
			break;
		case RTC_IT_TOF:
 		 (RTC->SR & RTC_SR_TOF_MASK)?(retval = SET):(retval = RESET);
			break;
		case RTC_IT_TIF:
 		 (RTC->SR & RTC_SR_TIF_MASK)?(retval = SET):(retval = RESET);
			break;
		default:break;
	}
	return retval;
}


/***********************************************************************************************
 功能：判断是否是闰年
 形参：年份
 返回：1 闰年 0 平年
 详解：判断是否是闰年函数
			月份   1  2  3  4  5  6  7  8  9  10 11 12
			闰年   31 29 31 30 31 30 31 31 30 31 30 31
			非闰年 31 28 31 30 31 30 31 31 30 31 30 31
************************************************************************************************/
static uint8_t RTC_IsLeapYear(uint16_t year)
{
	if(year % 4 == 0) //必须能被4整除
	{ 
		if(year % 100 == 0) 
		{ 
			if(year % 400 == 0)return 1;//如果以00结尾,还要能被400整除 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}
//设置时钟
//把输入的时钟转换为秒钟
//以1970年1月1日为基准
//1970~2099年为合法年份
//返回值:0,成功;其他:错误代码.
//月份数据表			
static uint8_t const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表	  
//平年的月份日期表
static const uint8_t mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
/***********************************************************************************************
 功能：设置RTC时间
 形参：RTC 数据
 返回：无意义
 详解：
************************************************************************************************/
uint8_t RTC_SetCalander(RTC_CalanderTypeDef * RTC_CalanderStruct)
{
	uint16_t t;
	uint32_t seccount=0;
	if(RTC_CalanderStruct->Year < 1970||RTC_CalanderStruct->Year > 2099)return 1;	   
	for(t=1970;t<RTC_CalanderStruct->Year;t++)	//把所有年份的秒钟相加
	{
		if(RTC_IsLeapYear(t))seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000;			  //平年的秒钟数
	}
	RTC_CalanderStruct->Month-=1;
	for(t=0;t<RTC_CalanderStruct->Month;t++)	   //把前面月份的秒钟数相加
	{
		seccount+=(uint32_t)mon_table[t]*86400;//月份秒钟数相加
		if(RTC_IsLeapYear(RTC_CalanderStruct->Year)&& t == 1)seccount+=86400;//闰年2月份增加一天的秒钟数	   
	}
	seccount += (uint32_t)((RTC_CalanderStruct->Date)-1)*86400;//把前面日期的秒钟数相加 
	seccount += (uint32_t)(RTC_CalanderStruct->Hour)*3600;//小时秒钟数
	seccount += (uint32_t)(RTC_CalanderStruct->Minute)*60;	 //分钟秒钟数
	seccount += RTC_CalanderStruct->Second ;//最后的秒钟加上去
	RTC->SR &= ~RTC_SR_TCE_MASK;//关闭计数器，见参考手册k10 1024页
	RTC->TSR = RTC_TSR_TSR(seccount);	
	RTC->TAR = RTC->TSR+1;
	RTC->SR |= RTC_SR_TCE_MASK;//开启计数器，见参考手册k10 1024页
	return 0;
}

/***********************************************************************************************
 功能：从年月日计算时分秒
 形参：年月日
 返回：星期代码
 详解：输入公历日期得到星期(只允许1901-2099年)
************************************************************************************************/
static uint8_t RTC_GetWeek(uint16_t year,uint8_t month,uint8_t day)
{	
	uint16_t temp2;
	uint8_t yearH,yearL;
	yearH=year/100;	yearL=year%100; 
	// 如果为21世纪,年份数加100  
	if (yearH>19)yearL+=100;
	// 所过闰年数只算1900年之后的  
	temp2 = yearL+yearL/4;
	temp2 = temp2%7; 
	temp2 = temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}			

/***********************************************************************************************
 功能：获得RTC数据
 形参：0
 返回：无意义
 详解：得到当前的时间，结果保存在calendar结构体里面
************************************************************************************************/
#define SEC_IN_DAY  86400
void RTC_GetCalander(RTC_CalanderTypeDef * RTC_CalanderStruct)
{

	static uint16_t daycnt=0;
	uint32_t timecount = 0; 
	uint32_t temp = 0;
	uint16_t temp1 = 0;	  
	timecount = RTC->TSR;	 
	RTC_CalanderStruct->TSRValue = RTC->TSR;
 	temp = timecount/SEC_IN_DAY;   //得到天数(秒钟数对应的)
	if(daycnt != temp)//超过一天了
	{	  
		daycnt = temp;
		temp1 = 1970;	//从1970年开始
		while(temp >= 365)
		{				 
			if(RTC_IsLeapYear(temp1))//是闰年
			{
				if(temp>=366)temp-=366;//闰年的秒钟数
				else {temp1++;break;}  
			}
			else temp-=365;	  //平年 
			temp1++;  
		}   
		RTC_CalanderStruct->Year=temp1;//得到年份
		temp1=0;
		while(temp>=28)//超过了一个月
		{
			if(RTC_IsLeapYear(RTC_CalanderStruct->Year) && temp1 == 1)//当年是不是闰年/2月份
			{
				if(temp >= 29)temp-=29;//闰年的秒钟数
				else break; 
			}
			else 
			{
				if(temp >= mon_table[temp1])temp-= mon_table[temp1];//平年
				else break;
			}
			temp1++;  
		}
		RTC_CalanderStruct->Month = temp1+1;	//得到月份
		RTC_CalanderStruct->Date = temp+1;  	//得到日期 
	}
	temp = timecount%86400;     		//得到秒钟数   	   
	RTC_CalanderStruct->Hour = temp/3600;     	//小时
	RTC_CalanderStruct->Minute = (temp%3600)/60; 	//分钟	
	RTC_CalanderStruct->Second = (temp%3600)%60; 	//秒钟
	RTC_CalanderStruct->Week = RTC_GetWeek(RTC_CalanderStruct->Year,RTC_CalanderStruct->Month,RTC_CalanderStruct->Date);//获取星期   
}	

/***********************************************************************************************
 功能：RTC秒中断调用函数
 形参：RTCx用户结构体
 返回：0
 详解：在RTX秒中断中调用此函数，更新RTC用户接口
************************************************************************************************/
void RTC_SecondIntProcess(void)
{
	RTC->SR &= ~RTC_SR_TCE_MASK; //关闭计时器
	RTC->TAR++;
	RTC->SR |= RTC_SR_TCE_MASK; //开启计数器
}
