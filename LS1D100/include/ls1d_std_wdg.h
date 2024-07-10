/********************************************************************
* 文件名:   ls1d6_std_wdg.h
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.11.5
* 说明:    看门狗头文件
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/

#ifndef INCLUDE_WDG_H_
#define INCLUDE_WDG_H_

#include "ls1d.h"

void WDG_SetWatchDog(uint32_t time);
void WDG_DogFeed(void);

#endif /* INCLUDE_WDG_H_ */
