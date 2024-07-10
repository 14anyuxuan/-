/*
 * UserTimer.c
 *
 *  Created on: 2021年11月11日
 *      Author: Administrator
 */


#include "UserTimer.h"
void TimerInit(void)
{
	TIM_InitTypeDef TIM_InitStruct;
	TIM_StructInit(&TIM_InitStruct);
	TIM_InitStruct.TIME_CMP =7999;//初始值1ms中断触发
	TIM_InitStruct.TIME_STP =8000 * 100;//步进100ms
	TIM_Init(TIMER,&TIM_InitStruct);
	TIM_ITConfig(TIMER,ENABLE);
	TIM_Cmd(TIMER,ENABLE);
}


