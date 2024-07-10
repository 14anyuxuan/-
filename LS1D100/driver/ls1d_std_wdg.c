/********************************************************************
* �ļ���:   ls1d6_std_wdg.c
* �汾��	  V1.0
* ����:    ����
* ����:    2021.11.5
* ˵��:    ���Ź�����
* ��Ȩ:    ��о�пƣ�̫ԭ���������޹�˾
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
