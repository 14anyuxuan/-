
/********************************************************************
* 文件名:  ls1d6_std_exti.h
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.12.18
* 说明:    本文件包中断控制器exti的底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef INCLUDE_EXTI_H_
#define INCLUDE_EXTI_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "ls1d.h"

typedef enum
{
  EXTI_Mode_Level = 0x00,	//电平模式
  EXTI_Mode_Edge = 0x01		//边沿模式
}EXTIMode_TypeDef;

#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Level) || ((MODE) == EXTI_Mode_Edge))

/**
  * @brief  EXTI Trigger enumeration
  */

typedef enum
{
  EXTI_Trigger_Rising_High = 0x01,
  EXTI_Trigger_Falling_Low = 0x00
}EXTITrigger_TypeDef;

#define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising_High) || \
                                  ((TRIGGER) == EXTI_Trigger_Falling_Low))
/**
  * @brief  EXTI Init Structure definition
  */

typedef struct
{
  uint32_t EXTI_GPIO;               /*!< Specifies the EXTI lines to be enabled or disabled.
                                         This parameter can be any combination of @ref EXTI_GPIOs */

  EXTIMode_TypeDef EXTI_Mode;       /*!< Specifies the mode for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

  EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

  FunctionalState EXTI_GpioCmd;     /*!< Specifies the new state of the selected EXTI lines.
                                         This parameter can be set either to ENABLE or DISABLE */
}EXTI_InitTypeDef;

/**
  * @}
  */

/** @defgroup EXTI_Exported_Constants
  * @{
  */

/** @defgroup EXTI_GPIOs
  * @{
  */
#define EXTI_GPIONONE    ((uint32_t)0x00000)  /* No interrupt selected */
#define EXTI_GPIOALL    ((uint32_t)0xFFFFFFFF)  /* No interrupt selected */
#define EXTI_GPIO0       ((uint32_t)0x00000001)  /*!< External interrupt line 0 */
#define EXTI_GPIO1       ((uint32_t)0x00000002)  /*!< External interrupt line 1 */
#define EXTI_GPIO2       ((uint32_t)0x00000004)  /*!< External interrupt line 2 */
#define EXTI_GPIO3       ((uint32_t)0x00000008)  /*!< External interrupt line 3 */
#define EXTI_GPIO4       ((uint32_t)0x00000010)  /*!< External interrupt line 4 */
#define EXTI_GPIO5       ((uint32_t)0x00000020)  /*!< External interrupt line 5 */
#define EXTI_GPIO6       ((uint32_t)0x00000040)  /*!< External interrupt line 6 */
#define EXTI_GPIO7       ((uint32_t)0x00000080)  /*!< External interrupt line 7 */
#define EXTI_GPIO8       ((uint32_t)0x00000100)  /*!< External interrupt line 8 */
#define EXTI_GPIO9       ((uint32_t)0x00000200)  /*!< External interrupt line 9 */
#define EXTI_GPIO10      ((uint32_t)0x00000400)  /*!< External interrupt line 10 */
#define EXTI_GPIO11      ((uint32_t)0x00000800)  /*!< External interrupt line 11 */
#define EXTI_GPIO12      ((uint32_t)0x00001000)  /*!< External interrupt line 12 */
#define EXTI_GPIO13      ((uint32_t)0x00002000)  /*!< External interrupt line 13 */
#define EXTI_GPIO14      ((uint32_t)0x00004000)  /*!< External interrupt line 14 */
#define EXTI_GPIO15      ((uint32_t)0x00008000)  /*!< External interrupt line 15 */
#define EXTI_GPIO16      ((uint32_t)0x00010000)  /*!< External interrupt line 16 */
#define EXTI_GPIO17      ((uint32_t)0x00020000)  /*!< External interrupt line 17 */
#define EXTI_GPIO18      ((uint32_t)0x00040000)  /*!< External interrupt line 18 */
#define EXTI_GPIO19      ((uint32_t)0x00080000)  /*!< External interrupt line 19 */
#define EXTI_GPIO20      ((uint32_t)0x00100000)  /*!< External interrupt line 20 */
#define EXTI_GPIO21      ((uint32_t)0x00200000)  /*!< External interrupt line 21 */
#define EXTI_GPIO22      ((uint32_t)0x00400000)  /*!< External interrupt line 22 */
#define EXTI_GPIO23      ((uint32_t)0x00800000)  /*!< External interrupt line 23 */
#define EXTI_GPIO24      ((uint32_t)0x01000000)  /*!< External interrupt line 24 */
#define EXTI_GPIO25      ((uint32_t)0x02000000)  /*!< External interrupt line 25 */
#define EXTI_GPIO26      ((uint32_t)0x04000000)  /*!< External interrupt line 26 */
#define EXTI_GPIO27      ((uint32_t)0x08000000)  /*!< External interrupt line 27 */
#define EXTI_GPIO28      ((uint32_t)0x10000000)  /*!< External interrupt line 28 */
#define EXTI_GPIO29      ((uint32_t)0x20000000)  /*!< External interrupt line 29 */
#define EXTI_GPIO30      ((uint32_t)0x40000000)  /*!< External interrupt line 30 */
#define EXTI_GPIO31      ((uint32_t)0x80000000)  /*!< External interrupt line 31 */



#define IS_EXTI_GPIO(GPIO) (((GPIO) == EXTI_GPIO0) || ((GPIO) == EXTI_GPIO1) || \
                            ((GPIO) == EXTI_GPIO2) || ((GPIO) == EXTI_GPIO3) || \
                            ((GPIO) == EXTI_GPIO4) || ((GPIO) == EXTI_GPIO5) || \
                            ((GPIO) == EXTI_GPIO6) || ((GPIO) == EXTI_GPIO7) || \
                            ((GPIO) == EXTI_GPIO8) || ((GPIO) == EXTI_GPIO9) || \
                            ((GPIO) == EXTI_GPIO10) || ((GPIO) == EXTI_GPIO11) || \
                            ((GPIO) == EXTI_GPIO12) || ((GPIO) == EXTI_GPIO13) || \
                            ((GPIO) == EXTI_GPIO14) || ((GPIO) == EXTI_GPIO15) || \
                            ((GPIO) == EXTI_GPIO16) || ((GPIO) == EXTI_GPIO17) || \
                            ((GPIO) == EXTI_GPIO18) || ((GPIO) == EXTI_GPIO19) ||\
							((GPIO) == EXTI_GPIO20) || ((GPIO) == EXTI_GPIO21) || \
							((GPIO) == EXTI_GPIO22) || ((GPIO) == EXTI_GPIO23) || \
							((GPIO) == EXTI_GPIO24) || ((GPIO) == EXTI_GPIO25) || \
							((GPIO) == EXTI_GPIO26) || ((GPIO) == EXTI_GPIO27) || \
							((GPIO) == EXTI_GPIO28) || ((GPIO) == EXTI_GPIO29) || \
							((GPIO) == EXTI_GPIO30) || ((GPIO) == EXTI_GPIO31))




/** @defgroup EXTI_Exported_Functions
  * @{
  */
uint8 EXTI_IsGlobalIntOpen(void);
void EXTI_DisableInt(void);
void EXTI_EnableInt(void);
void EXTI_DeInit(void);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_SoftInterruptStart(void);
void EXTI_SoftInterruptStop(void);
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_GPIO);
void EXTI_ClearFlag(uint32_t EXTI_GPIO);
ITStatus EXTI_GetITStatus(uint32_t EXTI_GPIO);
void EXTI_ClearITPendingBit(uint32_t EXTI_GPIO);

#ifdef __cplusplus
}
#endif


#endif /* INCLUDE_EXTI_H_ */
