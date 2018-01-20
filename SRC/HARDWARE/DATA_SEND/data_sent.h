#ifndef __DATA_SENT_H__
#define __DATA_SENT_H__



#ifdef __cplusplus
 extern "C" {
#endif
     
#include "uart.h" 
#include "OLED.h"        

#include "dma.h"
#include "sys.h"
#include "gpio.h"
#include "mk60dz10.h"
#include "data_sd.h"

//#include "extern.h"
	 
//#include "ini_flash.h" 
extern  int Pwm_Servo;
extern int16_t car_data[SD_DATA_NUM/2];
	 

#define DMA_UART_TX_DB       ((uint8_t*)&(UART5->D))
#define DMA_UART_TX_SB       Sent_Data //设置DMA原地址
     
#define  DMA_UART_CHx                DMA_CH5 //选取DMA通道     
#define  UARTx_TRAN_DMAREQ           UART5_TRAN_DMAREQ //选取DMA中断源     

#define UINT          0x00
#define IINT          0x01 
#define FLOAT         0x02 

#define Pardefault    0
#define Typedefault   UINT   
     
#define Bit8          0x08
#define Bit16         0x10


#define ParMODE       0x01 //参数模式
#define PicBazMODE    0x03 //二值图像模式  

#define Send_Mode     PicBazMODE      //设置发送模式
#define DMAUART_BANDRATE     640000

#define DataNum       40

#define Par_Num 1

 
#if(DataNum)     
#if(DataNum>=1)
#define    DefaultParValue1            car_data[0]
#endif

#if(DataNum>=2)
#define    DefaultParValue2            car_data[1]
#endif

#if(DataNum>=3)
#define    DefaultParValue3            car_data[2]
#endif

#if(DataNum>=4)
#define    DefaultParValue4            car_data[3]
#endif

#if(DataNum>=5)
#define    DefaultParValue5            car_data[4]
#endif

#if(DataNum>=6)
#define    DefaultParValue6            car_data[5]
#endif

#if(DataNum>=7) 
#define    DefaultParValue7            car_data[6]
#endif

#if(DataNum>=8)
#define    DefaultParValue8            car_data[7]
#endif

#if(DataNum>=9)
#define    DefaultParValue9            car_data[8]
#endif

#if(DataNum>=10)
#define    DefaultParValue10            car_data[9]
#endif

#if(DataNum>=11)
#define    DefaultParValue11            car_data[10]
#endif

#if(DataNum>=12)
#define    DefaultParValue12            car_data[11]
#endif

#if(DataNum>=13)
#define    DefaultParValue13            car_data[12]
#endif

#if(DataNum>=14)
#define    DefaultParValue14            car_data[13]
#endif

#if(DataNum>=15)
#define    DefaultParValue15            car_data[14]
#endif

#if(DataNum>=16)
#define    DefaultParValue16            car_data[15]
#endif

#if(DataNum>=17)
#define    DefaultParValue17            car_data[16]
#endif

#if(DataNum>=18)
#define    DefaultParValue18            car_data[17]
#endif

#if(DataNum>=19)
#define    DefaultParValue19            car_data[18]
#endif

#if(DataNum>=20)
#define    DefaultParValue20            car_data[19]
#endif

#if(DataNum>=21)
#define    DefaultParValue21            car_data[20]
#endif

#if(DataNum>=22)
#define    DefaultParValue22            car_data[21]
#endif

#if(DataNum>=23)
#define    DefaultParValue23            car_data[22]
#endif

#if(DataNum>=24)
#define    DefaultParValue24            car_data[23]
#endif

#if(DataNum>=25)
#define    DefaultParValue25            car_data[24]
#endif

#if(DataNum>=26)
#define    DefaultParValue26            car_data[25]
#endif

#if(DataNum>=27)
#define    DefaultParValue27            car_data[26]
#endif

#if(DataNum>=28)
#define    DefaultParValue28            car_data[27]
#endif

#if(DataNum>=29)
#define    DefaultParValue29            car_data[28]
#endif

#if(DataNum>=30)
#define    DefaultParValue30            car_data[29]
#endif

#if(DataNum>=31)
#define    DefaultParValue31            car_data[30]
#endif

#if(DataNum>=32)
#define    DefaultParValue32            Pardefault
#endif

#if(DataNum>=33)
#define    DefaultParValue33            Pardefault
#endif

#if(DataNum>=34)
#define    DefaultParValue34            Pardefault
#endif

#if(DataNum>=35)
#define    DefaultParValue35            Pardefault
#endif

#if(DataNum>=36)
#define    DefaultParValue36            Pardefault
#endif

#if(DataNum>=37)
#define    DefaultParValue37            Pardefault
#endif

#if(DataNum>=38)
#define    DefaultParValue38            Pardefault
#endif

#if(DataNum>=39)
#define    DefaultParValue39            Pardefault
#endif

#if(DataNum>=40)
#define    DefaultParValue40            Pardefault
#endif

#if(DataNum>=41)
#define    DefaultParValue41            Pardefault
#endif

#if(DataNum>=42)
#define    DefaultParValue42            Pardefault
#endif

#if(DataNum>=43)
#define    DefaultParValue43            Pardefault
#endif

#if(DataNum>=44)
#define    DefaultParValue44            Pardefault
#endif

#if(DataNum>=45)
#define    DefaultParValue45            Pardefault
#endif

#if(DataNum>=46)
#define    DefaultParValue46            Pardefault
#endif

#if(DataNum>=47)
#define    DefaultParValue47            Pardefault
#endif

#if(DataNum>=48)
#define    DefaultParValue48            Pardefault
#endif

#if(DataNum>=49)
#define    DefaultParValue49            Pardefault
#endif

#if(DataNum>=50)
#define    DefaultParValue50            Pardefault
#endif

#if(DataNum>=51)
#define    DefaultParValue51            Pardefault
#endif

#if(DataNum>=52)
#define    DefaultParValue52            Pardefault
#endif

#if(DataNum>=53)
#define    DefaultParValue53            Pardefault
#endif

#if(DataNum>=54)
#define    DefaultParValue54            Pardefault
#endif

#if(DataNum>=55)
#define    DefaultParValue55            Pardefault
#endif

#if(DataNum>=56)
#define    DefaultParValue56            Pardefault
#endif

#if(DataNum>=57)
#define    DefaultParValue57            Pardefault
#endif

#if(DataNum>=58)
#define    DefaultParValue58            Pardefault
#endif

#if(DataNum>=59)
#define    DefaultParValue59            Pardefault
#endif

#if(DataNum>=60)
#define    DefaultParValue60            Pardefault
#endif

#if(DataNum>=61)
#define    DefaultParValue61            Pardefault
#endif

#if(DataNum>=62)
#define    DefaultParValue62            Pardefault
#endif

#if(DataNum>=63)
#define    DefaultParValue63            Pardefault
#endif

#if(DataNum>=64)
#define    DefaultParValue64            Pardefault
#endif

#if(DataNum>=65)
#define    DefaultParValue65            Pardefault
#endif

#if(DataNum>=66)
#define    DefaultParValue66            Pardefault
#endif

#if(DataNum>=67)
#define    DefaultParValue67            Pardefault
#endif

#if(DataNum>=68)
#define    DefaultParValue68            Pardefault
#endif

#if(DataNum>=69)
#define    DefaultParValue69            Pardefault
#endif

#if(DataNum>=70)
#define    DefaultParValue70            Pardefault
#endif

#if(DataNum>=71)
#define    DefaultParValue71            Pardefault
#endif

#if(DataNum>=72)
#define    DefaultParValue72            Pardefault
#endif

#if(DataNum>=73)
#define    DefaultParValue73            Pardefault
#endif

#if(DataNum>=74)
#define    DefaultParValue74            Pardefault
#endif

#if(DataNum>=75)
#define    DefaultParValue75            Pardefault
#endif

#if(DataNum>=76)
#define    DefaultParValue76            Pardefault
#endif

#if(DataNum>=77)
#define    DefaultParValue77            Pardefault
#endif

#if(DataNum>=78)
#define    DefaultParValue78            Pardefault
#endif

#if(DataNum>=79)
#define    DefaultParValue79            Pardefault
#endif

#if(DataNum>=80)
#define    DefaultParValue80            Pardefault
#endif

#if(DataNum>=81)
#define    DefaultParValue81            Pardefault
#endif

#if(DataNum>=82)
#define    DefaultParValue82            Pardefault
#endif

#if(DataNum>=83)
#define    DefaultParValue83            Pardefault
#endif

#if(DataNum>=84)
#define    DefaultParValue84            Pardefault
#endif

#if(DataNum>=85)
#define    DefaultParValue85            Pardefault
#endif

#if(DataNum>=86)
#define    DefaultParValue86            Pardefault
#endif

#if(DataNum>=87)
#define    DefaultParValue87            Pardefault
#endif

#if(DataNum>=88)
#define    DefaultParValue88            Pardefault
#endif

#if(DataNum>=89)
#define    DefaultParValue89            Pardefault
#endif

#if(DataNum>=90)
#define    DefaultParValue90            Pardefault
#endif

#if(DataNum>=91)
#define    DefaultParValue91            Pardefault
#endif

#if(DataNum>=92)
#define    DefaultParValue92            Pardefault
#endif

#if(DataNum>=93)
#define    DefaultParValue93            Pardefault
#endif

#if(DataNum>=94)
#define    DefaultParValue94            Pardefault
#endif

#if(DataNum>=95)
#define    DefaultParValue95            Pardefault
#endif

#if(DataNum>=96)
#define    DefaultParValue96            Pardefault
#endif

#if(DataNum>=97)
#define    DefaultParValue97            Pardefault
#endif

#if(DataNum>=98)
#define    DefaultParValue98            Pardefault
#endif

#if(DataNum>=99)
#define    DefaultParValue99            Pardefault
#endif

#if(DataNum>=100)
#define    DefaultParValue100            Pardefault
#endif

#if(DataNum>=101)
#define    DefaultParValue101            Pardefault
#endif

#if(DataNum>=102)
#define    DefaultParValue102            Pardefault
#endif

#if(DataNum>=103)
#define    DefaultParValue103            Pardefault
#endif

#if(DataNum>=104)
#define    DefaultParValue104            Pardefault
#endif

#if(DataNum>=105)
#define    DefaultParValue105            Pardefault
#endif

#if(DataNum>=106)
#define    DefaultParValue106            Pardefault
#endif

#if(DataNum>=107)
#define    DefaultParValue107            Pardefault
#endif

#if(DataNum>=108)
#define    DefaultParValue108            Pardefault
#endif

#if(DataNum>=109)
#define    DefaultParValue109            Pardefault
#endif

#if(DataNum>=110)
#define    DefaultParValue110            Pardefault
#endif

#if(DataNum>=111)
#define    DefaultParValue111            Pardefault
#endif

#if(DataNum>=112)
#define    DefaultParValue112            Pardefault
#endif

#if(DataNum>=113)
#define    DefaultParValue113            Pardefault
#endif

#if(DataNum>=114)
#define    DefaultParValue114            Pardefault
#endif

#if(DataNum>=115)
#define    DefaultParValue115            Pardefault
#endif

#if(DataNum>=116)
#define    DefaultParValue116            Pardefault
#endif

#if(DataNum>=117)
#define    DefaultParValue117            Pardefault
#endif

#if(DataNum>=118)
#define    DefaultParValue118            Pardefault
#endif

#if(DataNum>=119)
#define    DefaultParValue119            Pardefault
#endif

#if(DataNum>=120)
#define    DefaultParValue120            Pardefault
#endif

#if(DataNum>=121)
#define    DefaultParValue121            Pardefault
#endif

#if(DataNum>=122)
#define    DefaultParValue122            Pardefault
#endif

#if(DataNum>=123)
#define    DefaultParValue123            Pardefault
#endif

#if(DataNum>=124)
#define    DefaultParValue124            Pardefault
#endif

#if(DataNum>=125)
#define    DefaultParValue125            Pardefault
#endif

#if(DataNum>=126)
#define    DefaultParValue126            Pardefault
#endif

#if(DataNum>=127)
#define    DefaultParValue127            Pardefault
#endif

#if(DataNum>=128)
#define    DefaultParValue128            Pardefault
#endif

#if(DataNum>=129)
#define    DefaultParValue129            Pardefault
#endif

#if(DataNum>=130)
#define    DefaultParValue130            Pardefault
#endif

#if(DataNum>=131)
#define    DefaultParValue131            Pardefault
#endif

#if(DataNum>=132)
#define    DefaultParValue132            Pardefault
#endif

#if(DataNum>=133)
#define    DefaultParValue133            Pardefault
#endif

#if(DataNum>=134)
#define    DefaultParValue134            Pardefault
#endif

#if(DataNum>=135)
#define    DefaultParValue135            Pardefault
#endif

#if(DataNum>=136)
#define    DefaultParValue136            Pardefault
#endif

#if(DataNum>=137)
#define    DefaultParValue137            Pardefault
#endif

#if(DataNum>=138)
#define    DefaultParValue138            Pardefault
#endif

#if(DataNum>=139)
#define    DefaultParValue139            Pardefault
#endif

#if(DataNum>=140)
#define    DefaultParValue140            Pardefault
#endif

#if(DataNum>=141)
#define    DefaultParValue141            Pardefault
#endif

#if(DataNum>=142)
#define    DefaultParValue142            Pardefault
#endif

#if(DataNum>=143)
#define    DefaultParValue143            Pardefault
#endif

#if(DataNum>=144)
#define    DefaultParValue144            Pardefault
#endif

#if(DataNum>=145)
#define    DefaultParValue145            Pardefault
#endif

#if(DataNum>=146)
#define    DefaultParValue146            Pardefault
#endif

#if(DataNum>=147)
#define    DefaultParValue147            Pardefault
#endif

#if(DataNum>=148)
#define    DefaultParValue148            Pardefault
#endif

#if(DataNum>=149)
#define    DefaultParValue149            Pardefault
#endif

#if(DataNum>=150)
#define    DefaultParValue150            Pardefault
#endif

#if(DataNum>=151)
#define    DefaultParValue151            Pardefault
#endif

#if(DataNum>=152)
#define    DefaultParValue152            Pardefault
#endif

#if(DataNum>=153)
#define    DefaultParValue153            Pardefault
#endif

#if(DataNum>=154)
#define    DefaultParValue154            Pardefault
#endif

#if(DataNum>=155)
#define    DefaultParValue155            Pardefault
#endif

#if(DataNum>=156)
#define    DefaultParValue156            Pardefault
#endif

#if(DataNum>=157)
#define    DefaultParValue157            Pardefault
#endif

#if(DataNum>=158)
#define    DefaultParValue158            Pardefault
#endif

#if(DataNum>=159)
#define    DefaultParValue159            Pardefault
#endif

#if(DataNum>=160)
#define    DefaultParValue160            Pardefault
#endif

#if(DataNum>=161)
#define    DefaultParValue161            Pardefault
#endif

#if(DataNum>=162)
#define    DefaultParValue162            Pardefault
#endif

#if(DataNum>=163)
#define    DefaultParValue163            Pardefault
#endif

#if(DataNum>=164)
#define    DefaultParValue164            Pardefault
#endif

#if(DataNum>=165)
#define    DefaultParValue165            Pardefault
#endif

#if(DataNum>=166)
#define    DefaultParValue166            Pardefault
#endif

#if(DataNum>=167)
#define    DefaultParValue167            Pardefault
#endif

#if(DataNum>=168)
#define    DefaultParValue168            Pardefault
#endif

#if(DataNum>=169)
#define    DefaultParValue169            Pardefault
#endif

#if(DataNum>=170)
#define    DefaultParValue170            Pardefault
#endif

#if(DataNum>=171)
#define    DefaultParValue171            Pardefault
#endif

#if(DataNum>=172)
#define    DefaultParValue172            Pardefault
#endif

#if(DataNum>=173)
#define    DefaultParValue173            Pardefault
#endif

#if(DataNum>=174)
#define    DefaultParValue174            Pardefault
#endif

#if(DataNum>=175)
#define    DefaultParValue175            Pardefault
#endif

#if(DataNum>=176)
#define    DefaultParValue176            Pardefault
#endif

#if(DataNum>=177)
#define    DefaultParValue177            Pardefault
#endif

#if(DataNum>=178)
#define    DefaultParValue178            Pardefault
#endif

#if(DataNum>=179)
#define    DefaultParValue179            Pardefault
#endif

#if(DataNum>=180)
#define    DefaultParValue180            Pardefault
#endif

#if(DataNum>=181)
#define    DefaultParValue181            Pardefault
#endif

#if(DataNum>=182)
#define    DefaultParValue182            Pardefault
#endif

#if(DataNum>=183)
#define    DefaultParValue183            Pardefault
#endif

#if(DataNum>=184)
#define    DefaultParValue184            Pardefault
#endif

#if(DataNum>=185)
#define    DefaultParValue185            Pardefault
#endif

#if(DataNum>=186)
#define    DefaultParValue186            Pardefault
#endif

#if(DataNum>=187)
#define    DefaultParValue187            Pardefault
#endif

#if(DataNum>=188)
#define    DefaultParValue188            Pardefault
#endif

#if(DataNum>=189)
#define    DefaultParValue189            Pardefault
#endif

#if(DataNum>=190)
#define    DefaultParValue190            Pardefault
#endif

#if(DataNum>=191)
#define    DefaultParValue191            Pardefault
#endif

#if(DataNum>=192)
#define    DefaultParValue192            Pardefault
#endif

#if(DataNum>=193)
#define    DefaultParValue193            Pardefault
#endif

#if(DataNum>=194)
#define    DefaultParValue194            Pardefault
#endif

#if(DataNum>=195)
#define    DefaultParValue195            Pardefault
#endif

#if(DataNum>=196)
#define    DefaultParValue196            Pardefault
#endif

#if(DataNum>=197)
#define    DefaultParValue197            Pardefault
#endif

#if(DataNum>=198)
#define    DefaultParValue198            Pardefault
#endif

#if(DataNum>=199)
#define    DefaultParValue199            Pardefault
#endif

#if(DataNum>=200)
#define    DefaultParValue200            Pardefault
#endif

#if(DataNum>=201)
#define    DefaultParValue201            Pardefault
#endif

#if(DataNum>=202)
#define    DefaultParValue202            Pardefault
#endif

#if(DataNum>=203)
#define    DefaultParValue203            Pardefault
#endif

#if(DataNum>=204)
#define    DefaultParValue204            Pardefault
#endif

#if(DataNum>=205)
#define    DefaultParValue205            Pardefault
#endif

#if(DataNum>=206)
#define    DefaultParValue206            Pardefault
#endif

#if(DataNum>=207)
#define    DefaultParValue207            Pardefault
#endif

#if(DataNum>=208)
#define    DefaultParValue208            Pardefault
#endif

#if(DataNum>=209)
#define    DefaultParValue209            Pardefault
#endif

#if(DataNum>=210)
#define    DefaultParValue210            Pardefault
#endif

#if(DataNum>=211)
#define    DefaultParValue211            Pardefault
#endif

#if(DataNum>=212)
#define    DefaultParValue212            Pardefault
#endif

#if(DataNum>=213)
#define    DefaultParValue213            Pardefault
#endif

#if(DataNum>=214)
#define    DefaultParValue214            Pardefault
#endif

#if(DataNum>=215)
#define    DefaultParValue215            Pardefault
#endif

#if(DataNum>=216)
#define    DefaultParValue216            Pardefault
#endif

#if(DataNum>=217)
#define    DefaultParValue217            Pardefault
#endif

#if(DataNum>=218)
#define    DefaultParValue218            Pardefault
#endif

#if(DataNum>=219)
#define    DefaultParValue219            Pardefault
#endif

#if(DataNum>=220)
#define    DefaultParValue220            Pardefault
#endif

#if(DataNum>=221)
#define    DefaultParValue221            Pardefault
#endif

#if(DataNum>=222)
#define    DefaultParValue222            Pardefault
#endif

#if(DataNum>=223)
#define    DefaultParValue223            Pardefault
#endif

#if(DataNum>=224)
#define    DefaultParValue224            Pardefault
#endif

#if(DataNum>=225)
#define    DefaultParValue225            Pardefault
#endif

#if(DataNum>=226)
#define    DefaultParValue226            Pardefault
#endif

#if(DataNum>=227)
#define    DefaultParValue227            Pardefault
#endif

#if(DataNum>=228)
#define    DefaultParValue228            Pardefault
#endif

#if(DataNum>=229)
#define    DefaultParValue229            Pardefault
#endif

#if(DataNum>=230)
#define    DefaultParValue230            Pardefault
#endif

#if(DataNum>=231)
#define    DefaultParValue231            Pardefault
#endif

#if(DataNum>=232)
#define    DefaultParValue232            Pardefault
#endif

#if(DataNum>=233)
#define    DefaultParValue233            Pardefault
#endif

#if(DataNum>=234)
#define    DefaultParValue234            Pardefault
#endif

#if(DataNum>=235)
#define    DefaultParValue235            Pardefault
#endif

#if(DataNum>=236)
#define    DefaultParValue236            Pardefault
#endif

#if(DataNum>=237)
#define    DefaultParValue237            Pardefault
#endif

#if(DataNum>=238)
#define    DefaultParValue238            Pardefault
#endif

#if(DataNum>=239)
#define    DefaultParValue239            Pardefault
#endif

#if(DataNum>=240)
#define    DefaultParValue240            Pardefault
#endif

#if(DataNum>=241)
#define    DefaultParValue241            Pardefault
#endif

#if(DataNum>=242)
#define    DefaultParValue242            Pardefault
#endif

#if(DataNum>=243)
#define    DefaultParValue243            Pardefault
#endif

#if(DataNum>=244)
#define    DefaultParValue244            Pardefault
#endif

#if(DataNum>=245)
#define    DefaultParValue245            Pardefault
#endif

#if(DataNum>=246)
#define    DefaultParValue246            Pardefault
#endif

#if(DataNum>=247)
#define    DefaultParValue247            Pardefault
#endif

#if(DataNum>=248)
#define    DefaultParValue248            Pardefault
#endif

#if(DataNum>=249)
#define    DefaultParValue249            Pardefault
#endif

#if(DataNum>=250)
#define    DefaultParValue250            Pardefault
#endif

#if(DataNum>=251)
#define    DefaultParValue251            Pardefault
#endif

#if(DataNum>=252)
#define    DefaultParValue252            Pardefault
#endif

#if(DataNum>=253)
#define    DefaultParValue253            Pardefault
#endif

#if(DataNum>=254)
#define    DefaultParValue254            Pardefault
#endif

#if(DataNum>=255)
#define    DefaultParValue255            Pardefault
#endif

#if(DataNum>=256)
#define    DefaultParValue256            Pardefault
#endif



#endif

#define Image_FitDataLen 490

//自动计算出数据长度
#define  Buff_Sub                        4  //补偿 防止DMA或者单片机不稳定所导致的数组溢出问题
#define  Ver_Sub                         7  //验证及各种信息
#define  ParValue_Length     ((DataNum<<3)+ (Par_Num<<3))//参数长度
  

#if(Send_Mode==PicBazMODE)
#define  Pixels_Length       ((Image_Width*Image_Height)>>3)//存储图像大小，为了减少计算,编译器优化
#define  Data_Length         (Pixels_Length+Image_FitDataLen) //数据长度计算,编译器优化 Image_FitDataLen拟图数据长度
#define  Data_All_Length     (Data_Length+ParValue_Length+Ver_Sub +Buff_Sub) //数据和参数信息总长度,编译器优化 
#endif
#if(Send_Mode==ParMODE)
#define  Pixels_Length       (Image_Width*Image_Height)//存储图像大小，为了减少计算,编译器优化
#define  Data_Length         (Pixels_Length+Image_FitDataLen) //数据长度计算,编译器优化 Image_FitDataLen拟图数据长度
#define  Data_All_Length     (ParValue_Length + Ver_Sub +Buff_Sub) //数据和参数信息总长度,编译器优化 
#endif


typedef struct 
{
    uint8_t LEnd;
    uint8_t REnd;
    uint8_t LStart;
    uint8_t RStart;
    uint8_t left;
    uint8_t right;
    uint8_t center;
}LCR;

#define  Image_Width  200
#define  Image_Height  70


typedef struct 
{
    uint8_t Verific[5];
    uint8_t Pixels_width;
    uint8_t Pixels_height;
    uint8_t Coefficient_Num;
    uint8_t Parameter_Num;  
    uint8_t Data_Con[DataNum*8];
    uint8_t Par_Con[Par_Num*8];//暂时不发      
    LCR Lcr[Image_Height];//暂时不发
    uint8_t Pixels[Pixels_Length];  
}Data_Type;


struct Byte8_Struct
{
 uint8_t bit1:1;
 uint8_t bit2:1;
 uint8_t bit3:1;
 uint8_t bit4:1;
 uint8_t bit5:1;
 uint8_t bit6:1;
 uint8_t bit7:1;
 uint8_t bit8:1;
};





void Set_DataToCon(void);
void UART_Send_Con(void);
void Data_Uart_Init(void);     
void  DMA_Uart_ClearITPendingBit(void);//清除UART DMA中断标记
void Set_Uart_DMA_Enable(FunctionalState DMA_ON_OFF);//开启或关闭uartDMA   
void Set_Uart_DMA_DAddr(uint32_t DMA_Addr);//修改DMA目的地址
void Compressed_Data(void);//8位数据压缩成一位数据
void Unpack_Data(void);//8位数据压缩成一位数据

#ifdef __cplusplus
}
#endif

#endif


