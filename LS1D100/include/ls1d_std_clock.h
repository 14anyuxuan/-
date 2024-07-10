
/********************************************************************
* 文件名:  ls1d6_std_clock.h
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.10.18
* 说明:    本文件包含clock的底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef _CLOCK_H_
#define _CLOCK_H_


#include "ls1d.h"


typedef struct
{
  uint32_t SYSCLK_Frequency;  /*!< returns SYSCLK/cpu clock frequency expressed in Hz */
  uint32_t PCLK_Frequency;    /*!< returns PCLK/power clock frequency expressed in Hz */
  uint32_t FLASHCLK_Frequency;   /*!< returns FLASHCLK clock frequency expressed in Hz */
  uint32_t SONARCLK_Frequency;   /*!< returns SONARCLK clock frequency expressed in Hz */
  uint32_t BUSCLK_Frequency;  /*!< returns BUSCLK clock frequency expressed in Hz */

}CLOCKS_TypeDef;


/* ------------ timing registers bit define  ----------- */




/** @defgroup Timming_configuration
  *
  */
#define CLOCK_HSE_FAIL                        	((uint32_t)0x80000000)
#define CLOCK_HSE_SELECT_STATUS               	((uint32_t)0x40000000)
#define CLOCK_LSE_FAIL                        	((uint32_t)0x20000000)
#define CLOCK_LSE_SELECT_STATUS               	((uint32_t)0x10000000)

#define CLOCK_SYSCLK_HSE_SELECT		      	  	((uint32_t)0x08000000)
#define CLOCK_MEASURE_HSE_ENABLE	          	((uint32_t)0x04000000)	//osc8mEn
#define CLOCK_LSE_SELECT	          		  	((uint32_t)0x02000000)
#define CLOCK_LSI_SPEED_1K	          			((uint32_t)0x00000000)//LA与mips不同
#define CLOCK_LSI_SPEED_32K	          			((uint32_t)0x01000000)
#define CLOCK_LSI_SPEED_MASK	          		((uint32_t)0x01000000)
/* 内部32K OSC Trimming 值*/
#define CLOCK_LSE_TRIM_15	          			((uint32_t)0x00F00000)
#define CLOCK_LSE_TRIM_14	          			((uint32_t)0x00E00000)
#define CLOCK_LSE_TRIM_13	          			((uint32_t)0x00D00000)
#define CLOCK_LSE_TRIM_12	          			((uint32_t)0x00C00000)
#define CLOCK_LSE_TRIM_11	          			((uint32_t)0x00B00000)
#define CLOCK_LSE_TRIM_10	          			((uint32_t)0x00A00000)
#define CLOCK_LSE_TRIM_9	          			((uint32_t)0x00900000)
#define CLOCK_LSE_TRIM_8	          			((uint32_t)0x00800000)
#define CLOCK_LSE_TRIM_7	         			((uint32_t)0x00700000)
#define CLOCK_LSE_TRIM_6	          			((uint32_t)0x00600000)
#define CLOCK_LSE_TRIM_5	          			((uint32_t)0x00500000)
#define CLOCK_LSE_TRIM_4	          			((uint32_t)0x00400000)
#define CLOCK_LSE_TRIM_3	          			((uint32_t)0x00300000)
#define CLOCK_LSE_TRIM_2	          			((uint32_t)0x00200000)
#define CLOCK_LSE_TRIM_1	          			((uint32_t)0x00100000)
#define CLOCK_LSE_TRIM_0	          			((uint32_t)0x00000000)
#define CLOCK_LSE_TRIM_MASK	      				((uint32_t)0x00F00000)

#define CLOCK_MEASURE_CRU_DIR	          	  	((uint32_t)0x00080000)
#define CLOCK_MEASURE_CRU_AUTO_DIR	          	((uint32_t)0x00040000)
#define CLOCK_MEASURE_CYCLE_ZERO	          	((uint32_t)0x00020000)
#define CLOCK_MEASURE_CRUISE_X	          	  	((uint32_t)0x00010000)

#define CLOCK_MEASURE_CRUISE_TEMP_128S	      	((uint32_t)0x0000C000)
#define CLOCK_MEASURE_CRUISE_TEMP_32S	      	((uint32_t)0x00008000)
#define CLOCK_MEASURE_CRUISE_TEMP_8S	      	((uint32_t)0x00004000)
#define CLOCK_MEASURE_CRUISE_TEMP_2S	      	((uint32_t)0x00000000)
#define CLOCK_MEASURE_CRUISE_TEMP_MASK	      	((uint32_t)0x0000C000)

#define CLOCK_MEASURE_CRUISE_TOF_2S	          	((uint32_t)0x00003000)
#define CLOCK_MEASURE_CRUISE_TOF_1S	      	  	((uint32_t)0x00002000)
#define CLOCK_MEASURE_CRUISE_TOF_DIV2S	      	((uint32_t)0x00001000)
#define CLOCK_MEASURE_CRUISE_TOF_DIV4S	      	((uint32_t)0x00000000)
#define CLOCK_MEASURE_CRUISE_TOF_MASK	      	((uint32_t)0x00003000)

#define CLOCK_MEASURE_CYCLE_TEMP_2_5	      	((uint32_t)0x00000C00)
#define CLOCK_MEASURE_CYCLE_TEMP_2	      	  	((uint32_t)0x00000800)
#define CLOCK_MEASURE_CYCLE_TEMP_1_5	      	((uint32_t)0x00000400)
#define CLOCK_MEASURE_CYCLE_TEMP_1	      	  	((uint32_t)0x00000000)
#define CLOCK_MEASURE_CYCLE_TEMP_MASK	      	((uint32_t)0x00000C00)

#define CLOCK_MEASURE_CYCLE_TOF_2_5	          	((uint32_t)0x00000300)
#define CLOCK_MEASURE_CYCLE_TOF_2	      	  	((uint32_t)0x00000200)
#define CLOCK_MEASURE_CYCLE_TOF_1_5	      	  	((uint32_t)0x00000100)
#define CLOCK_MEASURE_CYCLE_TOF_1	          	((uint32_t)0x00000000)
#define CLOCK_MEASURE_CYCLE_TOF_MASK	      	((uint32_t)0x00000300)

/* 校准陶瓷晶振的32K时钟周期数配置 */
#define CLOCK_MEASURE_CAL_RES_NUM_10	      	((uint32_t)0x000000C0)
#define CLOCK_MEASURE_CAL_RES_NUM_8	      	  	((uint32_t)0x00000080)
#define CLOCK_MEASURE_CAL_RES_NUM_4	      	  	((uint32_t)0x00000040)
#define CLOCK_MEASURE_CAL_RES_NUM_2	          	((uint32_t)0x00000000)
#define CLOCK_MEASURE_CAL_RES_NUM_MASK	      	((uint32_t)0x000000C0)

/* 市电频率选择 */
#define CLOCK_HZ60_SELECT	          		  	((uint32_t)0x00000020)
/* 高速晶振开启到开始测量的延迟 */
#define CLOCK_START_CLK_HS_5140US	      	  	((uint32_t)0x0000001C)
#define CLOCK_START_CLK_HS_2440US	      	  	((uint32_t)0x00000010)
#define CLOCK_START_CLK_HS_1460US	      	  	((uint32_t)0x0000000C)
#define CLOCK_START_CLK_HS_480US	          	((uint32_t)0x00000008)
#define CLOCK_START_CLK_HS_240US	          	((uint32_t)0x00000004)
#define CLOCK_START_CLK_HS_120US	          	((uint32_t)0x00000000)
#define CLOCK_START_CLK_HS_MASK	      			((uint32_t)0x0000001C)

/* 测量时钟参考分频 */
#define CLOCK_MEASURE_HSE_DIV4	      			((uint32_t)0x00000003)
#define CLOCK_MEASURE_HSE_DIV3	      			((uint32_t)0x00000002)
#define CLOCK_MEASURE_HSE_DIV2	      			((uint32_t)0x00000001)
#define CLOCK_MEASURE_HSE_DIV1	      			((uint32_t)0x00000000)
#define CLOCK_MEASURE_HSE_DIV_MASK	     	 	((uint32_t)0x00000003)
#define IS_CLOCK_MEASURE_HSE_DIV(DIV) (((DIV) == CLOCK_MEASURE_HSE_DIV4) || ((DIV) == CLOCK_MEASURE_HSE_DIV3)|| \
										((DIV) == CLOCK_MEASURE_HSE_DIV2)||((DIV) == CLOCK_MEASURE_HSE_DIV1))

/** @defgroup HSE_configuration
  * @{
  */
#define CLOCK_HSE_OFF                      ((uint32_t)0x00000000)
#define CLOCK_HSE_ON                       CLOCK_SYSCLK_HSE_SELECT
#define IS_CLOCK_HSE(HSE) (((HSE) == CLOCK_HSE_OFF) || ((HSE) == CLOCK_HSE_ON))



/** @defgroup HSE_configuration
  * @{
  */
#define CLOCK_LSE_OFF                       ((uint32_t)0x00000000)
#define CLOCK_LSE_ON                        CLOCK_LSE_SELECT
#define IS_CLOCK_LSE(LSE) (((HSE) == CLOCK_LSE_OFF) || ((HSE) == CLOCK_LSE_ON) )


/** @defgroup HSE_configuration
  * @{
  */
#define CLOCK_HSI_OFF                       CLOCK_SYSCLK_HSE_SELECT
#define CLOCK_HSI_ON                        ((uint32_t)0x00000000)
#define IS_CLOCK_HSI(LSE) (((HSE) == CLOCK_HSI_OFF) || ((HSE) == CLOCK_HSI_ON) )

/** @defgroup HSE_configuration
  * @{
  */
#define CLOCK_LSI_OFF                       CLOCK_LSE_SELECT
#define CLOCK_LSI_ON                        ((uint32_t)0x00000000)
#define IS_CLOCK_LSI(LSE) (((HSE) == CLOCK_LSI_OFF) || ((HSE) == CLOCK_LSI_ON) )


#define CLOCK_HSE_FAIL                        	((uint32_t)0x80000000)
#define CLOCK_HSE_FAIL_MASK               		((uint32_t)0x80000000)
#define CLOCK_HSE_FAIL_SHIFT               		((uint32_t)31)
#define CLOCK_HSE_SELECT_STATUS               	((uint32_t)0x40000000)
#define CLOCK_HSE_SELECT_STATUS_MASK            ((uint32_t)0x40000000)
#define CLOCK_HSE_SELECT_STATUS_SHIFT           ((uint32_t)30)
#define CLOCK_LSE_FAIL                        	((uint32_t)0x20000000)
#define CLOCK_LSE_FAIL_MASK               		((uint32_t)0x20000000)
#define CLOCK_LSE_FAIL_SHIFT               		((uint32_t)29)
#define CLOCK_LSE_SELECT_STATUS               	((uint32_t)0x10000000)
#define CLOCK_LSE_SELECT_STATUS_MASK            ((uint32_t)0x10000000)
#define CLOCK_LSE_SELECT_STATUS_SHIFT           ((uint32_t)28)

#define IS_CLOCK_FLAG(FLAG) (((FLAG) == CLOCK_HSE_FAIL) || ((FLAG) == CLOCK_LSE_SELECT_STATUS) \
							 ((FLAG) == CLOCK_HSE_SELECT_STATUS) || ((FLAG) == CLOCK_LSE_FAIL))

/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define CLOCK_OSCILLATORTYPE_NONE            (0x00000000U)
#define CLOCK_OSCILLATORTYPE_HSE             (0x00000001U)
#define CLOCK_OSCILLATORTYPE_HSI             (0x00000002U)
#define CLOCK_OSCILLATORTYPE_LSE             (0x00000004U)
#define CLOCK_OSCILLATORTYPE_LSI             (0x00000008U)
#define IS_CLOCK_OSCILLATOR_TYPE(TYPE) (((TYPE) == CLOCK_OSCILLATORTYPE_HSE) || ((TYPE) == CLOCK_OSCILLATORTYPE_HSI)||\
										((TYPE) == CLOCK_OSCILLATORTYPE_LSE) || ((TYPE) == CLOCK_OSCILLATORTYPE_LSI)||\
										((TYPE) == CLOCK_OSCILLATORTYPE_NONE))





typedef struct
{
	  uint32_t OscillatorType;        /* The oscillators to be configured.
	                                       This parameter can be a value of @ref RCC_Oscillator_Type */

	  uint32_t HSEState;              /*  The new state of the HSE.
	                                       This parameter can be a value of @ref RCC_HSE_Config */

	  uint32_t ClkHSDiv;       		 /*   The HSE measure predivision factor value.
	                                       This parameter can be a value of  CLOCK_MEASURE_HSE_DIV */

	  uint32_t LSEState;              /*  The new state of the LSE.
	                                       This parameter can be a value of @ref RCC_LSE_Config */
	  uint32_t CalibrationResNum;   /*  The HSE calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
	                                       This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x1FU */
	  uint32_t LSISpeed;              /*  The speed of the LSI.
	                                       This parameter can be a value of @ref RCC_LSI_Config */
	  uint32_t StartClkHS;			  /*   the delay time before external clock start work*/

}CLOCK_InitTypeDef;

typedef struct
{
	uint32 begin;
	uint32 end;
}TIMER_COUNT;

//typedef struct
//{
 //   uint32_t	TimeStart;
  //  uint32_t	TimeInter;
//
//} tsTimeType;

extern uint32 inte8m;
extern uint32 inte32K;
void CLOCK_StructInit(CLOCK_InitTypeDef  *CLOCK_InitStruct);
ErrorStatus CLOCK_Init(CLOCK_InitTypeDef  *CLOCK_InitStruct);

ErrorStatus CLOCK_HSEConfig(uint32_t CLOCK_HSE);
ErrorStatus CLOCK_LSEConfig(uint32_t CLOCK_LSE);

uint32_t CLOCK_GetClocksFreq(void);
FlagStatus CLOCK_GetFlagStatus(uint32_t CLOCK_FLAG);

void CLOCK_EnableSysTick(void);
void CLOCK_DisableSysTick(void);


void CLOCK_ClearCpuTimerIT(void);
void CLOCK_SetCpuTimer(uint32 timer);
void CLOCK_StopCpuTimer(void);


uint32 CLOCK_GetPmuCount(void);
/* 获取初始时间 */
void CLOCK_SetStartTimerCount(uint32_t *start_time);
//获取时间间隔
uint32 CLOCK_GetTimerCountInterval(uint32_t start_time);
void CLOCK_DelayUs(uint32 x);	//us单位
void CLOCK_DelayMs(uint32 x);  	//ms单位
void CLOCK_DelayS(uint32 x);  	//s单位

#endif
