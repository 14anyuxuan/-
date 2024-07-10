/*
 * GlobalDef.c
 *
 *  Created on: 2021��1��4��
 *      Author: LX
 */

#include "GlobalDef.h"


//TaskWorkMode taskmode;
void (*MainTask)(void);
void (*LastTask)(void);

static short  ErrorLog;
/*************************************************************
 * �������� SetSystemErrorLogInfo
 * �������������ô�����־����
 * ��������� short info ���������
 *
 * ���������
 * ��ע��
 ************************************************************/
void SetSystemErrorLogInfo(short info)
{
	ErrorLog = info;
}
/*************************************************************
 * �������� ResetSystemErrorLogInfo
 * ������������λ������־
 * ���������
 *
 * ���������
 * ��ע��
 ************************************************************/
void ResetSystemErrorLogInfo(void)
{
	ErrorLog = RunOk;
}

/*************************************************************
 * �������� GetSystemErrorLogInfo
 * ������������ȡϵͳ������־��Ϣ
 * ���������
 *
 * ���������
 * ��ע��
 ************************************************************/
short GetSystemErrorLogInfo(void)
{
	return ErrorLog;
}



