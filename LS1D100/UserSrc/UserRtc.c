/*
 * UserRtc.c
 *
 *  Created on: 2021年11月11日
 *      Author: Administrator
 */

#include "UserRtc.h"

void RTCInit(void)
{
	RTC_InitTypeDef RTC_InitStruct;
	RTC_InitStruct.Freq = (32768 >> 4) -1;  /* 输入时钟/16-1，用来得到分频系数/32768 */
	/* 日期时间设置  */
	RTC_InitStruct.usec = 3;
	RTC_InitStruct.sec = 1;
	RTC_InitStruct.min = 5;
	RTC_InitStruct.hour = 9;
	RTC_InitStruct.day = 26;
	RTC_InitStruct.mon = 4;
	RTC_InitStruct.year = 23;
	//RTC_StructInit(&RTC_InitStruct);
	RTC_Init(&RTC_InitStruct);
	RTC_ITConfig(DISABLE);
}
