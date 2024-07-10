/*
 * UserI2c.c
 *
 *  Created on: 2021Äê11ÔÂ11ÈÕ
 *      Author: Administrator
 */

#include "UserI2c.h"
#if 0
void I2cInit(void)
{
	I2C_InitTypeDef I2C_InitStruct;
	I2C_StructInit(&I2C_InitStruct);
	I2C_Init(I2C,&I2C_InitStruct);
}
void I2cIntint(void)
{
	I2C_InitTypeDef I2C_InitStruct;
	I2C_StructInit(&I2C_InitStruct);
	I2C_Init(I2C,&I2C_InitStruct);
	I2C_ITConfig(I2C,ENABLE);
	I2C_ITCmd(I2C,ENABLE);
}

#endif

