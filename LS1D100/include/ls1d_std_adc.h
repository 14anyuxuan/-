
/********************************************************************
* 文件名:  ls1d6_std_adc.h
* 版本：	  V1.0
* 作者:    白一方、李鑫
* 日期:    2021.10.18
* 说明:    本文件包含adc的底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef _ADC_H_
#define _ADC_H_

#include "ls1d.h"
#include "ls1d_std_clock.h"
#include "ls1d_std_cslreg.h"
#include "ls1d_std_Interrupt.h"
#include "ls1d_std_printf.h"


/**
 * @说明  ADC寄存器设置宏定义
 */
#define ADC0_IEN    2
#define ADC1_IEN    4


#define ADC_CHANNEL_ADC0    0
#define ADC_CHANNEL_ADC1    (1<<4)
// #define ADC_CHANNEL_ADC1    0x10
#define ADC_CHANNEL_VRCAP   (2<<4)
#define ADC_CHANNEL_V1_0    (3<<4)
#define ADC_CHANNEL_VROUT   (4<<4)
#define ADC_CHANNEL_VR1_0   (5<<4)
#define ADC_CHANNEL_VREF    (6<<4)
#define ADC_CHANNEL_DACAMC  (7<<4)

#define ADC_DIV_2    0
#define ADC_DIV_4    (1<<1)
#define ADC_DIV_8    (2<<1)

#define ADC_RUN     1

/**
 * @说明  ADC中断相关寄存器设置宏定义
 */

// #define ADC_INT_EN      0x40

/**
 * @说明  ADC 变量参数宏定义
 */
#define VDD_VALUE_MV    3300    //单位mv,电源VDD 3.3V 标准电压
// #define	REF_AD_V	    1000	//单位mv,内部LDO 1.0V 参考电压

#define SAMPLE_TIME		10	    //采样时间
#define MAX_DELT	    20		//最大误差范围定义，单位mv
#define BOUNDAERY_V	    920		//分界电压，单位mv

#define ADC_AnalogInputMode    0
#define ADC_DigitalInputMode   1
#define IRQ_ADC         				((uint8_t)0x40)
#define IRQ_ADC_CLR						((uint8_t)0x06)
/**
 * @说明  ADC变量声明
 */
extern int16_t g_adc_data;		//ADC数据最终值
extern int16_t g_adc_diff;		//ADC临时变量
extern int16_t MaxAdc,MinAdc,MidAdc,MaxDiff;	//ADC临时变量

/**
 * @说明  ADC函数声明
 */
void ADC_Init(void);
void ADC_Start(uint32_t channel);
uint16_t ADC_Measure(uint32_t channel);
uint16_t ADC_Mv(uint16_t adval);

void Insert_Sort(uint16_t *num, uint16_t n);
uint16_t ADC_DetectPower(uint32_t channel);

#if 1
void ADC_Sample(uint32_t channel);
void ADC_Channel0InputMode(uint32_t mode);
#endif





#endif
