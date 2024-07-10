
/********************************************************************
* 文件名:   ls1d6_std_gpio.h
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.08.31
* 说明:    本文件包含GPIO的底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef _GPIO_H_
#define _GPIO_H_

#include "ls1d.h"


/**
 * @说明 判断是否为GPIO外设
 */
#define IS_GPIO(PERIPH) (((PERIPH) == GPIOA) || ((PERIPH) == GPIOB))


/**
 * @说明 枚举GPIO类型
 * @备注: UART0_Remap_GPIO01 与其他 Remap 项共用时，需要与其先与，其余是相或
 * @例如:(GPIO_RemapLCD_ALL | GPIO_Remap_LCD_H23 & GPIO_Remap_UART01)
 *
 */
typedef enum
{
	GPIO_MAIN 				= 0,
 	UART0_Remap_GPIO01 		= 0x7FFF,
	LCD_Remap_GPIO 			= 0x4000,
	LCD_H23_Remap_GPIO 		= 0x2000,
	LCD_H22_Remap_GPIO 		= 0x1000,
	LCD_H21_Remap_GPIO 		= 0x0800,
	LCD_H20_Remap_GPIO 		= 0x0400,
	SPI_Remap_GPIO 			= 0x0200,
	PT12_Remap_GPIO	 		= 0x0100,
	PT34_Remap_GPIO 		= 0x0080,
	KEY_Remap_GPIO 			= 0x0040,
	EMP_Remap_GPIO 			= 0x0020,
	UART0_Remap_GPIO 		= 0x0010,
	UART1_Remap_GPIO 		= 0x0008,
	ADC1_Remap_GPIO 		= 0x0004,
	ADC0_Remap_GPIO 		= 0x0002,
	I2C_Remap_GPIO 			= 0x0001
}GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_MAIN) || ((MODE) == UART0_Remap_GPIO01)\
							((MODE) == LCD_Remap_GPIO) || ((MODE) == LCD_H23_Remap_GPIO)\
							((MODE) == LCD_H22_Remap_GPIO) || ((MODE) == LCD_H21_Remap_GPIO)\
							((MODE) == LCD_H20_Remap_GPIO) || ((MODE) == SPI_Remap_GPIO)\
							((MODE) == PT12_Remap_GPIO) || ((MODE) == PT34_Remap_GPIO)\
							((MODE) == KEY_Remap_GPIO) || ((MODE) == EMP_Remap_GPIO)\
							((MODE) == UART0_Remap_GPIO) || ((MODE) == UART1_Remap_GPIO)\
							((MODE) == ADC1_Remap_GPIO) || ((MODE) == I2C_Remap_GPIO))

/**
 * @说明  GPIO 方向定义
 */
typedef enum
{
	GPIO_Mode_IN = 0x0,
	GPIO_Mode_Out = 0x2
}GPIODirection_TypeDef;

#define IS_GPIO_DIRECTION(DIRECTION) (((DIRECTION) == GPIO_Mode_IN) || ((DIRECTION) == GPIO_Mode_Out))


/**
 * @说明  GPIO 初始化定义
 */

typedef struct
{
  uint32_t GPIO_Pin;             				/* 指定GPIO配置的管脚 */
  GPIODirection_TypeDef GPIO_Direction;		    /* 指定GPIO管脚的方向 */
  GPIOMode_TypeDef GPIO_Mode;    				/*指定GPIO 工作模式  */
}GPIO_InitTypeDef;

/**
  * @说明   管脚状态枚举
  */
typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;
#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))

//typedef enum
//{
//	GPIO_Pin_0 = 0,
//	GPIO_Pin_1,
//	GPIO_Pin_2,
//	GPIO_Pin_3,
//	GPIO_Pin_4,
//	GPIO_Pin_5,
//	GPIO_Pin_6,
//	GPIO_Pin_7,
//	GPIO_Pin_8,
//	GPIO_Pin_9,
//	GPIO_Pin_10,
//	GPIO_Pin_11,
//	GPIO_Pin_12,
//	GPIO_Pin_13,
//	GPIO_Pin_14,
//	GPIO_Pin_15,
//	GPIO_Pin_16,
//	GPIO_Pin_17,
//	GPIO_Pin_18,
//	GPIO_Pin_19,
//	GPIO_Pin_20,
//	GPIO_Pin_21,
//	GPIO_Pin_22,
//	GPIO_Pin_23,
//	GPIO_Pin_24,
//	GPIO_Pin_25,
//	GPIO_Pin_26,
//	GPIO_Pin_27,
//	GPIO_Pin_28,
//	GPIO_Pin_29,
//	GPIO_Pin_30,
//	GPIO_Pin_31
//}GPIO_PIN;

#define GPIO_Pin_0                 ((uint32_t)0x00000001)  /*!< Pin 0 selected */
#define GPIO_Pin_1                 ((uint32_t)0x00000002)  /*!< Pin 1 selected */
#define GPIO_Pin_2                 ((uint32_t)0x00000004)  /*!< Pin 2 selected */
#define GPIO_Pin_3                 ((uint32_t)0x00000008)  /*!< Pin 3 selected */
#define GPIO_Pin_4                 ((uint32_t)0x00000010)  /*!< Pin 4 selected */
#define GPIO_Pin_5                 ((uint32_t)0x00000020)  /*!< Pin 5 selected */
#define GPIO_Pin_6                 ((uint32_t)0x00000040)  /*!< Pin 6 selected */
#define GPIO_Pin_7                 ((uint32_t)0x00000080)  /*!< Pin 7 selected */
#define GPIO_Pin_8                 ((uint32_t)0x00000100)  /*!< Pin 8 selected */
#define GPIO_Pin_9                 ((uint32_t)0x00000200)  /*!< Pin 9 selected */
#define GPIO_Pin_10                ((uint32_t)0x00000400)  /*!< Pin 10 selected */
#define GPIO_Pin_11                ((uint32_t)0x00000800)  /*!< Pin 11 selected */
#define GPIO_Pin_12                ((uint32_t)0x00001000)  /*!< Pin 12 selected */
#define GPIO_Pin_13                ((uint32_t)0x00002000)  /*!< Pin 13 selected */
#define GPIO_Pin_14                ((uint32_t)0x00004000)  /*!< Pin 14 selected */
#define GPIO_Pin_15                ((uint32_t)0x00008000)  /*!< Pin 15 selected */
#define GPIO_Pin_16                ((uint32_t)0x00010000)  /*!< Pin 16 selected */
#define GPIO_Pin_17                ((uint32_t)0x00020000)  /*!< Pin 17 selected */
#define GPIO_Pin_18                ((uint32_t)0x00040000)  /*!< Pin 18 selected */
#define GPIO_Pin_19                ((uint32_t)0x00080000)  /*!< Pin 19 selected */
#define GPIO_Pin_20                ((uint32_t)0x00100000)  /*!< Pin 20 selected */
#define GPIO_Pin_21                ((uint32_t)0x00200000)  /*!< Pin 21 selected */
#define GPIO_Pin_22                ((uint32_t)0x00400000)  /*!< Pin 22 selected */
#define GPIO_Pin_23                ((uint32_t)0x00800000)  /*!< Pin 23 selected */
#define GPIO_Pin_24                ((uint32_t)0x01000000)  /*!< Pin 24 selected */
#define GPIO_Pin_25                ((uint32_t)0x02000000)  /*!< Pin 25 selected */
#define GPIO_Pin_26                ((uint32_t)0x04000000)  /*!< Pin 26 selected */
#define GPIO_Pin_27                ((uint32_t)0x08000000)  /*!< Pin 27 selected */
#define GPIO_Pin_28                ((uint32_t)0x10000000)  /*!< Pin 28 selected */
#define GPIO_Pin_29                ((uint32_t)0x20000000)  /*!< Pin 29 selected */
#define GPIO_Pin_30                ((uint32_t)0x40000000)  /*!< Pin 30 selected */
#define GPIO_Pin_31                ((uint32_t)0x80000000)  /*!< Pin 31 selected */
#define GPIO_Pin_All               ((uint16_t)0xFFFFFFFF)  /*!< All pins selected */
#define IS_GPIO_PIN(PIN)		(((PIN) == GPIO_Pin_0) || \
        						 ((PIN) == GPIO_Pin_1) || \
								 ((PIN) == GPIO_Pin_2) || \
								 ((PIN) == GPIO_Pin_3) || \
								 ((PIN) == GPIO_Pin_4) || \
								 ((PIN) == GPIO_Pin_5) || \
								 ((PIN) == GPIO_Pin_6) || \
								 ((PIN) == GPIO_Pin_7) || \
								 ((PIN) == GPIO_Pin_8) || \
								 ((PIN) == GPIO_Pin_9) || \
								 ((PIN) == GPIO_Pin_10) || \
								 ((PIN) == GPIO_Pin_11) || \
								 ((PIN) == GPIO_Pin_12) || \
								 ((PIN) == GPIO_Pin_13) || \
								 ((PIN) == GPIO_Pin_14) || \
								 ((PIN) == GPIO_Pin_15)	|| \
								 ((PIN) == GPIO_Pin_16) || \
        						 ((PIN) == GPIO_Pin_17) || \
								 ((PIN) == GPIO_Pin_18) || \
								 ((PIN) == GPIO_Pin_19) || \
								 ((PIN) == GPIO_Pin_20) || \
								 ((PIN) == GPIO_Pin_21) || \
								 ((PIN) == GPIO_Pin_22) || \
								 ((PIN) == GPIO_Pin_23) || \
								 ((PIN) == GPIO_Pin_24) || \
								 ((PIN) == GPIO_Pin_25) || \
								 ((PIN) == GPIO_Pin_26) || \
								 ((PIN) == GPIO_Pin_27) || \
								 ((PIN) == GPIO_Pin_28) || \
								 ((PIN) == GPIO_Pin_29) || \
								 ((PIN) == GPIO_Pin_30) || \
								 ((PIN) == GPIO_Pin_31))

/**
 * @说明：定义了GPIO复用外设
 * @备注: GPIO_Remap_UART01 与其他 Remap 项共用时，需要与其先或，其余是相与
 * @例如：(GPIO_RemapLCD_ALL & GPIO_Remap_LCD_H23 | GPIO_Remap_UART01)
 * */
#define GPIO01_Remap_UART0 			((uint32)0x00008000)	/* UART0 Alternate GPIO01 Function mapping */
#define GPIO_Remap_LCD_ALL 			((uint32)0xFFFFBFFF)	/* LCD[23] Alternate Function mapping */
#define GPIO_Remap_LCD_H23 			((uint32)0xFFFFDFFF)	/* LCD[23] Alternate Function mapping */
#define GPIO_Remap_LCD_H22 			((uint32)0xFFFFEFFF)	/* LCD[22] Function mapping */
#define GPIO_Remap_LCD_H21 			((uint32)0xFFFFF7FF)	/* LCD[21] Alternate Function mapping */
#define GPIO_Remap_LCD_H20 			((uint32)0xFFFFFBFF)	/* LCD[20] Alternate Function mapping */
#define GPIO_Remap_SPI 				((uint32)0xFFFFFDFF)	/* SPI Alternate Function mapping */
#define GPIO_Remap_PT12 			((uint32)0xFFFFFEFF)	/* PT12 LoadT SenseT Alternate Function mapping */
#define GPIO_Remap_PT34 			((uint32)0xFFFFFF7F)	/* PT34 Alternate Function mapping */
#define GPIO_Remap_KEY 				((uint32)0xFFFFFFBF)	/* KEY_I Alternate Function mapping */
#define GPIO_Remap_EMP 				((uint32)0xFFFFFFDF)	/* EMP_I Alternate Function mapping */
#define GPIO_Remap_UART1 			((uint32)0xFFFFFFEF)    /* UART0 Alternate Function mapping */
#define GPIO_Remap_UART0 			((uint32)0xFFFFFFF7)	/* UART1 Alternate Function mapping */
#define	GPIO_Remap_ADC1	 			((uint32)0xFFFFFFFB)	/* ADC1 Alternate Function mapping */
#define	GPIO_Remap_ADC0 			((uint32)0xFFFFFFFD)	/* ADC0 Alternate Function mapping ad mode to get voltage  */
#define	GPIO_Remap_I2C  			((uint32)0xFFFFFFFE)	/* I2C Alternate Function mapping */

#define IS_GPIO_REMAP(REMAP) (((REMAP) == GPIO_Remap_UART01) || ((REMAP) == GPIO_RemapLCD_ALL) || \
                              ((REMAP) == GPIO_Remap_LCD_H23) || ((REMAP) == GPIO_Remap_LCD_H22) || \
                              ((REMAP) == GPIO_Remap_LCD_H21) || ((REMAP) == GPIO_Remap_LCD_H20) || \
                              ((REMAP) == GPIO_Remap_SPI) || ((REMAP) == GPIO_Remap_PT12) || \
                              ((REMAP) == GPIO_Remap_PT34) || ((REMAP) == GPIO_Remap_KEY) || \
                              ((REMAP) == GPIO_Remap_EMP) || ((REMAP) == GPIO_Remap_UART0) || \
                              ((REMAP) == GPIO_Remap_UART1) || ((REMAP) == GPIO_Remap_ADC1) || \
                              ((REMAP) == GPIO_Remap_I2C))



void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_BitInit(BITIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(BITIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
uint32_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(BITIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
uint32_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_WriteBit(BITIO_TypeDef* GPIOx, uint32_t GPIO_Pin, BitAction Value);
void GPIO_WriteData(GPIO_TypeDef* GPIOx, uint32_t Value);
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);





#endif


