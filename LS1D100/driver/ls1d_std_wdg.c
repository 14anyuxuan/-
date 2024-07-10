/********************************************************************
* 文件名:   ls1d6_std_wdg.c
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.11.5
* 说明:    看门狗函数
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/

#include "../include/ls1d_std_wdg.h"


void WDG_SetWatchDog(uint32_t time)
{

	WWDG->WDT_CFG = (((~time)<<16) | time);
	WWDG->WDT_FEED = 0xa55a55aa;

}

void WDG_DogFeed(void)
{
	WWDG->WDT_FEED = 0xa55a55aa;
}
