#include "DATA_SD.h"
#include "sd.h"
#include "data_sent.h"
#include "camera.h"
#include "extern.h"

#define ImageWidth 200
#define ImageLength 70
#define SD_Data_Num 2

extern Data_Type DATA_ALL;
extern Data_Type *Sent_Data;

int16_t car_data[SD_DATA_NUM / 2];
int16_t CarData[512];

uint32_t sdnum = 0; //SD卡的扇区选择数

/**********************************************************
*                    SD卡初始化
***********************************************************/
void MySD_Init1(void)
{
    SD_InitTypeDef SD_InitStruct1;
    SD_InitStruct1.SD_BaudRate = 10000000;
    //等待SD卡初始化成功
    while (SD_Init(&SD_InitStruct1) != ESDHC_OK);
}
/***********************************************************
*                  多块写命令函数
************************************************************/
void SD_ManyWT_Init(void)
{
    SD_CommandTypeDef SD_CommandStruct1;
    SD_CommandStruct1.COMMAND = ESDHC_CMD25;
    SD_CommandStruct1.BLOCKS = SD_8G_BlocksNum;
    SD_CommandStruct1.BLOCKSIZE = 512;
    SD_CommandStruct1.ARGUMENT = 0; //sd卡初始地址
    SD_SendCommand(&SD_CommandStruct1);
}

/*******************************************************
*              把要发的数据存到car_data数组
*******************************************************/
void data_give(void)
{
    int Temper_AngleControlOut_Max=32000;
	int Temper_AngleControlOut=Angle_PID.ControlOut;
    if(Angle_PID.ControlOut>Temper_AngleControlOut_Max)
		Temper_AngleControlOut=Temper_AngleControlOut_Max;
	else if(Angle_PID.ControlOut<-Temper_AngleControlOut_Max)
		Temper_AngleControlOut=-Temper_AngleControlOut_Max;
//    if (Mode == 4 && Mode_Choose == 1)
//    {
//        car_data[0] = (int16_t)MMA8451_OUT_X;
//        car_data[1] =(int16_t) Ang_ACC_X;
//        car_data[2] = (int16_t)Angle;
//        car_data[3] = (int16_t)Ang_IGyro;
//        car_data[4] = (int16_t)L3G4200D_OUT_Y;
//        car_data[5] =(int16_t) Ang_Gyro_Y;
//        car_data[6] = (int16_t)L3G4200D_OUT_Z;
//        car_data[7] = (int16_t)Ang_Gyro_Z;
//        car_data[8] = (int16_t)(Angle + Ang_ACC_Mid);
//        car_data[9] = 0;
//        car_data[10] = 0;
//    }
//    else
//    {	
//        car_data[0] =(int16_t)Angle;
//        car_data[1] = (int16_t)Angle_Line;
//        car_data[2] = (int16_t)Encoder_Left[2];
//        car_data[3] = (int16_t)Encoder_Right[2];
//        car_data[4] = (int16_t)g_CarSpeed;
//        car_data[5] =(int16_t) Direction_PID.ControlOut;//Direction_PID.Error[1];
//        car_data[6] = (int16_t) Temper_AngleControlOut;
//        car_data[7] = (int16_t)Speed_L_PID.ControlOut;
//        car_data[8] = (int16_t)L_ControlOut;
//        car_data[9] =(int16_t) Ramp_Flag;
//        car_data[10] = (int16_t)Element_Flag;
//        car_data[11] = (int16_t)Ring_State_Flag;	
//        car_data[12] = (int16_t)Hang_Min;	
//        car_data[13] = (int16_t)Hang_Max;;
//    }
    
    if (sentdata==0)
    {
        car_data[0] = (int16_t)MMA8451_OUT_X;
        car_data[1] =(int16_t) Ang_ACC_X;
        car_data[2] = (int16_t)Angle;
        car_data[3] = (int16_t)Ang_IGyro;
        car_data[4] = (int16_t)L3G4200D_OUT_Y;
        car_data[5] =(int16_t) Ang_Gyro_Y;
        car_data[6] = (int16_t)L3G4200D_OUT_Z;
        car_data[7] = (int16_t)Ang_Gyro_Z;
        car_data[8] = (int16_t)(Angle + Ang_ACC_Mid);
        car_data[9] = 0;
        car_data[10] = 0;
    }
    else   if (sentdata==1)
    {	
        car_data[0] =(int16_t)Angle;
        car_data[1] = (int16_t)Angle_Line;
        car_data[2] = (int16_t)Encoder_Left[2];
        car_data[3] = (int16_t)Encoder_Right[2];
        car_data[4] = (int16_t)g_CarSpeed;
        car_data[5] =(int16_t) Direction_PID.ControlOut;//Direction_PID.Error[1];
        car_data[6] = (int16_t) Temper_AngleControlOut;
        car_data[7] = (int16_t)Speed_L_PID.ControlOut;
        car_data[8] = (int16_t)L_ControlOut;
        car_data[9] =(int16_t) Ramp_Flag;
        car_data[10] = (int16_t)Element_Flag;
        car_data[11] = (int16_t)Ring_State_Flag;	
        car_data[12] = (int16_t)Hang_Min;	
        car_data[13] = (int16_t)Hang_Max;
    }
	 else   if (sentdata==2)
    {	
		car_data[0]=(int16_t)Threshold_Temper;
        car_data[1] =(int16_t)Angle;
		car_data[2] = (int16_t)(Angle-Ang_ACC_Mid);
		car_data[3] =(int16_t)Hang_Max;	
        car_data[4] = (int16_t)Hang_Min;	
        car_data[5] = (int16_t)Angle_Line;
        car_data[6] = (int16_t)Encoder_Left[2];
        car_data[7] = (int16_t)Encoder_Right[2];
        car_data[8] = (int16_t)g_CarSpeed;
		car_data[9] = (int16_t) Temper_AngleControlOut;
		car_data[10] = (int16_t)Speed_L_PID.ControlOut;
		car_data[11] = (int16_t)(Temper_AngleControlOut-Speed_L_PID.ControlOut);
		car_data[12] =(int16_t)I_L;
        car_data[13] =(int16_t) Direction_PID.ControlOut;
		car_data[14] = (int16_t)Direction_PID.Error[1];	
        car_data[15] = (int16_t)L_ControlOut;
		car_data[16] = (int16_t)R_ControlOut;
        car_data[17] =(int16_t) Ramp_Flag;
        car_data[18] = (int16_t)Element_Flag;
        car_data[19] = (int16_t)Ring_State_Flag;
    }
	 else   if (sentdata==3)
    {	
		car_data[0]=(int16_t)Threshold_Temper;
        car_data[1] =(int16_t)Angle;
		car_data[2] = (int16_t)(Angle-Ang_ACC_Mid);
		car_data[3] =(int16_t)Hang_Max;	
        car_data[4] = (int16_t)Hang_Min;	
        car_data[5] = (int16_t)Angle_Line;
        car_data[6] = (int16_t)Encoder_Left[2];
        car_data[7] = (int16_t)Encoder_Right[2];
        car_data[8] = (int16_t)g_CarSpeed;
		car_data[9] = (int16_t) Temper_AngleControlOut;
		car_data[10] = (int16_t)Speed_L_PID.ControlOut;
		car_data[11] = (int16_t)(Temper_AngleControlOut-Speed_L_PID.ControlOut);
		car_data[12] =(int16_t)I_L;
        car_data[13] =(int16_t) Direction_PID.ControlOut;
		car_data[14] = (int16_t)Direction_PID.Error[1];	
        car_data[15] = (int16_t)L_ControlOut;
		car_data[16] = (int16_t)R_ControlOut;
		car_data[17] = (int16_t)Element_Flag;
		car_data[18] = (int16_t)Ring_State_Flag;
		car_data[19] = (int16_t)Set_Speed;
		car_data[20] =(int16_t) Ramp_Flag; 
		car_data[21] = (int16_t)Speed_jian_Flag;
		car_data[22] = (int16_t)Speed_jian_Count;
    }   
    
}


/**********************************************************
*                    SD卡初始化
***********************************************************/
void MySD_Init(void)
{
    SD_InitTypeDef SD_InitStruct1;
    SD_InitStruct1.SD_BaudRate = 40000000;
    //等待SD卡初始化成功
    while (SD_Init(&SD_InitStruct1) != ESDHC_OK)
        ;
}

/***********************************************************
*                 解压函数
************************************************************/
void Unpack_Data(void) //数据解压
{
    uint8_t *P;
    uint8_t H, W;
    uint8_t *Data_Pixels = Sent_Data->Pixels;
    uint16_t count = 0;
    union //定义一个公用体
    {
        uint8_t Byte;
        struct Byte8_Struct Byte_Bit;
    } BIT;
    P = *Pixels; //将指针指向当前需要处理的行
    Data_Pixels += 0;
    for (H = 0; H < Image_Height; H++)
    {
        for (W = 0; W < (Image_Width >> 3); W++)
        {
            BIT.Byte = *Data_Pixels++;

            *P++ = BIT.Byte_Bit.bit8;
            *P++ = BIT.Byte_Bit.bit7;
            *P++ = BIT.Byte_Bit.bit6;
            *P++ = BIT.Byte_Bit.bit5;
            *P++ = BIT.Byte_Bit.bit4;
            *P++ = BIT.Byte_Bit.bit3;
            *P++ = BIT.Byte_Bit.bit2;
            *P++ = BIT.Byte_Bit.bit1;
        }
    }
}

/********************************************************
*                  多块写入函数
*             *pbuffer:写入数据原地址
*              Count  :写入数据长度
*              BlockNum:写入的扇区数
*********************************************************/
void SD_Many_Write(const uint8_t *pbuffer, uint16_t Count, uint8_t BlockNum)
{
    uint32_t j;
    uint8_t *ptr = (uint8_t *)pbuffer;

    for (j = 0; j < (BlockNum * ((512 + 3) >> 2)); j++)
    {
        while (0 == (SDHC->PRSSTAT & SDHC_PRSSTAT_BWEN_MASK))
            ; //等待数据准备好

        if ((j << 2) < Count)
        {
            SDHC->DATPORT = *(uint32_t *)ptr;
            ptr += 4;
        }
        else
        {
            SDHC->DATPORT = 0xFFFFFFFF;
        }
    }
}

/********************************************************************
*                     SD卡写入函数
*********************************************************************/
void SD_Write(void)
{
    uint8_t *Data_Pixels = Sent_Data->Pixels;
    Set_DataToCon();
    Compressed_Data();
    data_give();
    SD_Many_Write(Data_Pixels, SD_DATA_LENGTH, 4);
    SD_Many_Write((uint8_t *)L_black, 70, 1);
    SD_Many_Write((uint8_t *)LCenter, 70, 1);
    SD_Many_Write((uint8_t *)R_black, 70, 1);
    SD_Many_Write((uint8_t *)car_data, SD_DATA_NUM, 1);
}

//读线函数
void Live_Transmission()
{
    LCR *Lcr = (LCR *)Sent_Data->Lcr; //传拟图所需定义
    uint8_t i = 0;
    for (i = 0; i < 70; i++)
    {
        Lcr[i].left = L_black[i];
        Lcr[i].right = R_black[i];
        Lcr[i].center = LCenter[i];
    }
    data_give();
    UART_Send_Con();
}

/******************************************************************
*                     读SD卡函数
******************************************************************/
void SD_ReadData(void)
{
    LCR *Lcr = (LCR *)Sent_Data->Lcr; //传拟图所需定义
    uint8_t i;
    uint8_t *Data_Pixels = Sent_Data->Pixels;
    OLED_Clear();
    while (SD_ReadSingleBlock(sdnum, Data_Pixels) != ESDHC_OK)
        ;
    sdnum++;
    Data_Pixels += 512;
    while (SD_ReadSingleBlock(sdnum, Data_Pixels) != ESDHC_OK)
        ;
    sdnum++;
    Data_Pixels += 512;
    while (SD_ReadSingleBlock(sdnum, Data_Pixels) != ESDHC_OK)
        ;
    sdnum++;
    Data_Pixels += 512;
    while (SD_ReadSingleBlock(sdnum, Data_Pixels) != ESDHC_OK)
        ;
    sdnum++;
    while (SD_ReadSingleBlock(sdnum, L_black) != ESDHC_OK)
        ;
    sdnum++;
    while (SD_ReadSingleBlock(sdnum, LCenter) != ESDHC_OK)
        ;
    sdnum++;
    while (SD_ReadSingleBlock(sdnum, R_black) != ESDHC_OK)
        ;
    sdnum++;
    while (SD_ReadSingleBlock(sdnum, (uint8_t *)car_data) != ESDHC_OK)
        ;
    sdnum++;

    for (i = 0; i < 70; i++)
    {
        Lcr[i].left = L_black[i];
        Lcr[i].center = LCenter[i];
        Lcr[i].right = R_black[i];
    }
    Unpack_Data();
    UART_Send_Con();
}
