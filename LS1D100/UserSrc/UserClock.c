/*
 * UserClock.c
 *
 *  Created on: 2021Äê9ÔÂ26ÈÕ
 *      Author: lixin
 */

#include "../include/ls1d_std_clock.h"





/**
  * @brief System Clock
  * @retval None
  */
void SystemClock(void)
{
	CLOCK_InitTypeDef  CLOCK_InitStruct = {0};

	CLOCK_StructInit(&CLOCK_InitStruct);

 	if(CLOCK_Init(&CLOCK_InitStruct) != SUCCESS)
 	{
 		 //debugflag =10;
 	}

}


