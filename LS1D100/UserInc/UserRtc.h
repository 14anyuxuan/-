/*
 * UserRtc.h
 *
 *  Created on: 2022Äê2ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef USERINC_USERRTC_H_
#define USERINC_USERRTC_H_

#include "../include/ls1d_std_printf.h"
#include "../include/ls1d_std_rtc.h"
void RTCInit(void);

extern RTC_time real_time,store_time,rtc_time,alarm_time,rtc_time_cal;
extern RTC_time SoftRtcUpdate(int modifier_time);
#endif /* USERINC_USERRTC_H_ */
