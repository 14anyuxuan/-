/*
 * UserTimer.c
 *
 *  Created on: 2021��11��11��
 *      Author: Administrator
 */


#include "UserTimer.h"
void TimerInit(void)
{
	TIM_InitTypeDef TIM_InitStruct;
	TIM_StructInit(&TIM_InitStruct);
	TIM_InitStruct.TIME_CMP =7999;//��ʼֵ1ms�жϴ���
	TIM_InitStruct.TIME_STP =8000 * 100;//����100ms
	TIM_Init(TIMER,&TIM_InitStruct);
	TIM_ITConfig(TIMER,ENABLE);
	TIM_Cmd(TIMER,ENABLE);
}


