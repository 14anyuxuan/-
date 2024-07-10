/********************************************************************
* 文件名:   ls1d6_std_rtc.h
* 版本：	  V1.0
* 作者:    王永芳
* 日期:    2021.09.30
* 说明:    本文件包含rtc实时时钟的底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef _RTC_H_
#define _RTC_H_

#include "ls1d.h"

typedef struct {
  uint8_t usec;					/* 1/16 秒 */
  uint8_t sec ;					/* 秒 */
  uint8_t min;					/* 分 */
  uint8_t hour;					/* 时  */
  uint8_t day;					/* 日  */
  uint8_t mon;					/* 月  */
  uint8_t year;					/* 年  */
  uint8_t RESERVED0;			/* 保留位*/
}RTC_time;

typedef struct
{
  uint32_t Freq;           		/* 系统时钟  */
  uint8_t usec;					/* 周  */
  uint8_t sec ;					/* 秒 */
  uint8_t min;					/* 分 */
  uint8_t hour;					/* 时  */
  uint8_t day;					/* 日  */
  uint8_t mon;					/* 月  */
  uint8_t year;					/* 年  */
} RTC_InitTypeDef;

#define RTC_Timer_En		0x40000000
#define RTC_SET				0x80000000
#define IRQ_RTC				((uint32)(1<<15))
#define IRQ_RTC_CLR			((uint32)(1<<23))
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct);	//RTC结构体初始化
void RTC_Init(RTC_InitTypeDef* RTC_InitStruct);			//RTC初始化
void RTC_SetDateTime(RTC_time *Wtime);			//设置0 0R0TC日期时间
void RTC_GetDateTime(RTC_time *Wtime);			//获取RTC日期时间
//void RTC_SetTime(RTC_time *Wtime);				//设置RTC时间
//void RTC_SetDate(RTC_time *Wtime);				//设置RTC日期
//void RTC_GetTime(RTC_time *Rtime);				//获取RTC时间
//void RTC_GetDate(RTC_time *Wtime);				//获取RTC日期
void RTC_SetAlarm(RTC_time *Wtime);				//设置闹钟时间(按星期闹铃,24小时制)
void RTC_ITConfig(FunctionalState NewState);			//设置RTC中断
void RTC_ClearIT(void);									//清除RTC中断标志


#endif
