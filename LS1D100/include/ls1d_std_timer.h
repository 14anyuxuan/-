/********************************************************************
* 文件名:   ls1d6_std_timer.h
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.09.30
* 说明:    本文件包含定时器timer的底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_


#include "ls1d.h"
#include "ls1d_std_cslreg.h"

//CFG
#define TIM_INT_FLAG		0x100
#define TIM_PERIODIC_FLAG	0x04
//#define TIM_INT_EN     		0x02
#define TIM_START   		0x01

#define IRQ_TIMER       	  1

typedef struct
{
  uint32_t Clock_Freq;

  uint32_t TIME_CMP;            /* This member configures the UART communication baud rate.
                                        The baud rate is computed using the following formula:
                                        - IntegerDivider = ((PCLKx) / (16 * (UART_InitStruct->UART_BaudRate)))*/

  uint32_t TIME_STP; 					/* Specifies uart clock freq*/

  uint32_t TIME_CNT;

  uint32_t TIME_PERIODIC;          /* Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UART_Word_Length */

  uint32_t TIME_INTEN;            /* Specifies the number of stop bits transmitted.
                                       This parameter can be a value of @ref UART_Stop_Bits */

  uint32_t TIME_START;              /* Specifies the parity mode whether Enable or disable */

} TIM_InitTypeDef;

typedef enum
{
	TIM_CLOCK_8M = 8000000,
	TIM_CLOCK_11M = 11000000
}TIMClock_TypeDef;

#define IS_TIM_CLOCK(CLOCK) (((CLOCK) == TIM_CLOCK_8M) || ((CLOCK) == TIM_CLOCK_11M))
#define IS_TIM_ALL_PERIPH(PERIPH) ((PERIPH) == TIMER)

#define TIME_START_0                     ((uint32_t)0x00)
#define TIME_START_1                     ((uint32_t)0x01)
#define IS_TIM_START(TIME_START) (((TIME_START) == TIME_START_0) || \
                                     ((TIME_START) == TIME_START_1))

#define TIME_INTEN_0                     ((uint32_t)0x00)
#define TIME_INTEN_1                    ((uint32_t)0x02)
#define IS_TIM_INTEN(TIME_INTEN) (((TIME_INTEN) == TIME_INTEN_0) || \
                                     ((TIME_INTEN) == TIME_INTEN_1))

#define TIME_PERIODIC_0                     ((uint32_t)0x00)
#define TIME_PERIODIC_1                     ((uint32_t)0x04)
#define IS_TIM_PERIODIC(TIME_PERIODIC) (((TIME_PERIODIC) == TIME_PERIODIC_0) || \
                                     ((TIME_PERIODIC) == TIME_PERIODIC_1))

#define TIM_FLAG_INT                   ((uint32_t)0x0100)
#define TIM_FLAG_Trigger                   ((uint32_t)0x0100)
#define IS_TIM_GET_FLAG(FLAG) 		((FLAG) == TIM_FLAG_INT)

#define IS_TIM_CLEAR_FLAG(FLAG)		((FLAG) == TIM_FLAG_INT)

void TIM_StructInit(TIM_InitTypeDef* TIMER_InitStruct);
void TIM_Init(TIM_TypeDef* TIMx, TIM_InitTypeDef* TIM_InitStruct);

void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter);
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx);
void TIM_SetCompare(TIM_TypeDef* TIMx, uint32_t Compare);
uint32_t TIM_GetCompare(TIM_TypeDef* TIMx);

FlagStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint32_t TIM_FLAG);
void TIM_ClearIT(TIM_TypeDef* TIMx, uint32_t TIM_FLAG);

#endif /* INCLUDE_TIMER_H_ */
