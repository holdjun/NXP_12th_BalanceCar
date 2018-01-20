/**
  ******************************************************************************
  * @file    adc.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 ADC模块驱动 头文件
  ******************************************************************************
  */
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "sys.h"


//ADC 精度定义
#define ADC_PRECISION_8BIT    (0x00U)
#define ADC_PRECISION_10BIT   (0x02U)
#define ADC_PRECISION_12BIT   (0x01U)
#define ADC_PRECISION_16BIT   (0x03U)
//参数检查
#define IS_ADC_PRECISION(VALUE) (((VALUE) == ADC_PRECISION_8BIT) ||  \
	                               ((VALUE) == ADC_PRECISION_10BIT) || \
	                               ((VALUE) == ADC_PRECISION_12BIT) || \
	                               ((VALUE) == ADC_PRECISION_16BIT))
//ADC初始化结构
typedef struct
{
  uint32_t ADCxMap;              
	uint32_t ADC_Precision;
	uint16_t ADC_TriggerSelect; //触发源选择
}ADC_InitTypeDef;

#define IS_ADC_ALL_PERIPH(PERIPH)  (((PERIPH) == ADC0) || \
                                    ((PERIPH) == ADC1))		


//AD转换触发源定义
#define ADC_TRIGGER_HW     (uint16_t)(0)
#define ADC_TRIGGER_SW     (uint16_t)(1)
#define IS_ADC_TRIGGER_SELECT(TRIGGER)  (((TRIGGER) == ADC_TRIGGER_HW) || ((TRIGGER) == ADC_TRIGGER_SW))

//中断源定义
#define ADC_IT_AI       (uint16_t)(0)
#define IS_ADC_IT(IT)  ((IT) == ADC_IT_AI)
//DMA命令
#define ADC_DMAReq_COCO                     ((uint16_t)0)
#define IS_ADC_DMAREQ(REQ)   ((REQ) == ADC_DMAReq_COCO)

//ADC 通道位图定义
typedef struct
{
    uint32_t ADC_Index:6;
    uint32_t ADC_Pin_Index:6;
    uint32_t ADC_GPIO_Index:4;
    uint32_t ADC_Alt_Index:4;
		uint32_t ADC_SingleDifferential:2;
	  uint32_t ADC_IsAnalogChl:2;
		uint32_t ADC_IsChlAB:2;
	  uint32_t ADC_Chl:6;
}ADC_MapTypeDef;

//ADC0查分信号输入选择
#define ADC0_DP0_DM0          (0x00500000U)    
#define ADC0_DP1_DM1          (0x04500000U)
#define ADC0_PGA0_DP_DM       (0x08500000U)
#define ADC0_DP3_DM3          (0x0c500000U)
#define ADC0_TEMP_SENSOR_DIFF  (0x68500000U)
//ADC0单端信号输入选择
#define ADC0_SE0_DP0           (0x00400000U)
#define ADC0_SE1_DP1           (0x04400000U)
#define ADC0_SE2_PGA0_DP       (0x08400000U)
#define ADC0_SE3_DP3           (0x0c400000U)  
#define ADC0_SE4B_PC2          (0x11002080U)
#define ADC0_SE5B_PD1          (0x15003040U)
#define ADC0_SE6B_PD5          (0x19003140U)
#define ADC0_SE7B_PD6          (0x1d003180U)
#define ADC0_SE8_PB0           (0x20001000U)
#define ADC0_SE9_PB1           (0x24001040U)
#define ADC0_SE12_PB2          (0x30001080U)
#define ADC0_SE13_PB3          (0x340010c0U)
#define ADC0_SE14_PC0          (0x38002000U)
#define ADC0_SE15_PC1          (0x3c002040U)
#define ADC0_SE17_E24          (0x44004600U)
#define ADC0_SE18_E25          (0x48004640U)
#define ADC0_SE19_DM0          (0x4c400000U)
#define ADC0_SE20_DM1          (0x50400000U)
#define ADC0_TEMP_SENSOR_SE     (0x68400000U)
//ADC1查分输入选择
#define ADC1_DP0_DM0           (0x00500001U)   
#define ADC1_DP1_DM1           (0x04500001U)
#define ADC1_PGA1_DP_DM        (0x08500001U)
#define ADC1_DP3_DM3           (0x0c500001U)
#define ADC1_TEMP_SENSOR_DIFF   (0x68500001U)
//ADC1单端输入通道
#define ADC1_SE0_DP0           (0x00400001U)
#define ADC1_SE1_DP1           (0x04400001U)
#define ADC1_SE2_PGA1_DP       (0x08400001U)
#define ADC1_SE3_DP3           (0x0c400001U)
#define ADC1_SE4_PE0           (0x10004001U)
#define ADC1_SE5_PE1           (0x14004041U)
#define ADC1_SE6_PE2           (0x18004081U)
#define ADC1_SE7_PE3           (0x1c0040c1U)
#define ADC1_SE4B_PC8          (0x11002201U)
#define ADC1_SE5B_PC9          (0x15002241U)
#define ADC1_SE6B_PC10         (0x19002281U)
#define ADC1_SE7B_PC11         (0x1d0022c1U)
#define ADC1_SE8_PB0           (0x20001001U)
#define ADC1_SE9_PB1           (0x24001041U)
#define ADC1_SE14_PB10         (0x38001281U)
#define ADC1_SE15_PB11         (0x3c0012C1U)
#define ADC1_SE17_PA17         (0x44000441U)
#define ADC1_SE19_DM0          (0x4c400001U)
#define ADC1_SE20_DM1          (0x50400001U)
#define ADC1_TEMP_SENSOR_SE    (0x68400001U)

/************************* #Defines ******************************************/

#define A                 0x0
#define B                 0x1
#define IS_ADC_MUX(MUX)   (((MUX) == A) || ((MUX) == B))
//// ADCSC1 (register)

// Conversion Complete (COCO) mask
#define COCO_COMPLETE     ADC_SC1_COCO_MASK
#define COCO_NOT          0x00

// ADC interrupts: enabled, or disabled.
#define AIEN_ON           ADC_SC1_AIEN_MASK
#define AIEN_OFF          0x00

// Differential or Single ended ADC input
#define DIFF_SINGLE       0x00
#define DIFF_DIFFERENTIAL ADC_SC1_DIFF_MASK

//// ADCCFG1

// Power setting of ADC
#define ADLPC_LOW         ADC_CFG1_ADLPC_MASK
#define ADLPC_NORMAL      0x00

// Clock divisor
#define ADIV_1            0x00
#define ADIV_2            0x01
#define ADIV_4            0x02
#define ADIV_8            0x03

// Long samle time, or Short sample time
#define ADLSMP_LONG       ADC_CFG1_ADLSMP_MASK
#define ADLSMP_SHORT      0x00

// How many bits for the conversion?  8, 12, 10, or 16 (single ended).
#define MODE_8            0x00
#define MODE_12           0x01
#define MODE_10           0x02
#define MODE_16           0x03

// ADC Input Clock Source choice? Bus clock, Bus clock/2, "altclk", or the 
//                                ADC's own asynchronous clock for less noise
#define ADICLK_BUS        0x00
#define ADICLK_BUS_2      0x01
#define ADICLK_ALTCLK     0x02
#define ADICLK_ADACK      0x03

//// ADCCFG2

// Select between B or A channels
#define MUXSEL_ADCB       ADC_CFG2_MUXSEL_MASK
#define MUXSEL_ADCA       0x00

// Ansync clock output enable: enable, or disable the output of it
#define ADACKEN_ENABLED   ADC_CFG2_ADACKEN_MASK
#define ADACKEN_DISABLED  0x00

// High speed or low speed conversion mode
#define ADHSC_HISPEED     ADC_CFG2_ADHSC_MASK
#define ADHSC_NORMAL      0x00

// Long Sample Time selector: 20, 12, 6, or 2 extra clocks for a longer sample time
#define ADLSTS_20          0x00
#define ADLSTS_12          0x01
#define ADLSTS_6           0x02
#define ADLSTS_2           0x03

////ADCSC2

// Read-only status bit indicating conversion status
#define ADACT_ACTIVE       ADC_SC2_ADACT_MASK
#define ADACT_INACTIVE     0x00

// Trigger for starting conversion: Hardware trigger, or software trigger.
// For using PDB, the Hardware trigger option is selected.
#define ADTRG_HW           ADC_SC2_ADTRG_MASK
#define ADTRG_SW           0x00

// ADC Compare Function Enable: Disabled, or Enabled.
#define ACFE_DISABLED      0x00
#define ACFE_ENABLED       ADC_SC2_ACFE_MASK

// Compare Function Greater Than Enable: Greater, or Less.
#define ACFGT_GREATER      ADC_SC2_ACFGT_MASK
#define ACFGT_LESS         0x00

// Compare Function Range Enable: Enabled or Disabled.
#define ACREN_ENABLED      ADC_SC2_ACREN_MASK
#define ACREN_DISABLED     0x00

// DMA enable: enabled or disabled.
#define DMAEN_ENABLED      ADC_SC2_DMAEN_MASK
#define DMAEN_DISABLED     0x00

// Voltage Reference selection for the ADC conversions
// (***not*** the PGA which uses VREFO only).
// VREFH and VREFL (0) , or VREFO (1).

#define REFSEL_EXT         0x00
#define REFSEL_ALT         0x01
#define REFSEL_RES         0x02     /* reserved */
#define REFSEL_RES_EXT     0x03     /* reserved but defaults to Vref */

////ADCSC3

// Calibration begin or off
#define CAL_BEGIN          ADC_SC3_CAL_MASK
#define CAL_OFF            0x00

// Status indicating Calibration failed, or normal success
#define CALF_FAIL          ADC_SC3_CALF_MASK
#define CALF_NORMAL        0x00

// ADC to continously convert, or do a sinle conversion
#define ADCO_CONTINUOUS    ADC_SC3_ADCO_MASK
#define ADCO_SINGLE        0x00

// Averaging enabled in the ADC, or not.
#define AVGE_ENABLED       ADC_SC3_AVGE_MASK
#define AVGE_DISABLED      0x00

// How many to average prior to "interrupting" the MCU?  4, 8, 16, or 32
#define AVGS_4             0x00
#define AVGS_8             0x01
#define AVGS_16            0x02
#define AVGS_32            0x03

////PGA

// PGA enabled or not?
#define PGAEN_ENABLED      ADC_PGA_PGAEN_MASK
#define PGAEN_DISABLED     0x00 

// Chopper stabilization of the amplifier, or not.
#define PGACHP_CHOP        ADC_PGA_PGACHP_MASK 
#define PGACHP_NOCHOP      0x00

// PGA in low power mode, or normal mode.
#define PGALP_LOW          ADC_PGA_PGALP_MASK
#define PGALP_NORMAL       0x00

// Gain of PGA.  Selectable from 1 to 64.
#define PGAG_1             0x00
#define PGAG_2             0x01
#define PGAG_4             0x02
#define PGAG_8             0x03
#define PGAG_16            0x04
#define PGAG_32            0x05
#define PGAG_64            0x06


//本构件所实现的函数接口
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct);
uint16_t ADC_GetConversionValue(uint32_t ADCxMap);
void ADC_ITConfig(ADC_Type* ADCx,uint8_t ADC_Mux, uint16_t ADC_IT, FunctionalState NewState);
ITStatus ADC_GetITStatus(ADC_Type* ADCx, uint8_t ADC_Mux, uint16_t ADC_IT);
void ADC_DMACmd(ADC_Type* ADCx, uint16_t ADC_DMAReq, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif


