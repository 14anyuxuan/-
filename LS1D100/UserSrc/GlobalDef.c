/*
 * GlobalDef.c
 *
 *  Created on: 2021年1月4日
 *      Author: LX
 */

#include "GlobalDef.h"


//TaskWorkMode taskmode;
void (*MainTask)(void);
void (*LastTask)(void);

static short  ErrorLog;
/*************************************************************
 * 函数名： SetSystemErrorLogInfo
 * 函数描述：设置错误日志代码
 * 输入参数： short info ：错误代码
 *
 * 输出参数：
 * 备注：
 ************************************************************/
void SetSystemErrorLogInfo(short info)
{
	ErrorLog = info;
}
/*************************************************************
 * 函数名： ResetSystemErrorLogInfo
 * 函数描述：复位错误日志
 * 输入参数：
 *
 * 输出参数：
 * 备注：
 ************************************************************/
void ResetSystemErrorLogInfo(void)
{
	ErrorLog = RunOk;
}

/*************************************************************
 * 函数名： GetSystemErrorLogInfo
 * 函数描述：获取系统错误日志信息
 * 输入参数：
 *
 * 输出参数：
 * 备注：
 ************************************************************/
short GetSystemErrorLogInfo(void)
{
	return ErrorLog;
}



