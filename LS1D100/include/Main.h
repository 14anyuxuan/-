/********************************************************************
* �ļ���:   main.h
* �汾��   V1.0
* ����:    ����
* ����:    2021.09.30
* ˵��:    ���ļ�����main�ļ��ĺ����������궨��
* ��Ȩ:    ��о�пƣ�̫ԭ���������޹�˾
********************************************************************/
#ifndef MAIN_H_
#define MAIN_H_

#define NO_INIT 				volatile
//====================================driver include file======================//
#include"ls1d.h"
#include"ls1d_std_Interrupt.h"
#include"ls1d_std_gpio.h"
#include"ls1d_std_uart.h"
#include"ls1d_std_wdg.h"
#include"ls1d_std_clock.h"
#include"ls1d_std_printf.h"
#include"ls1d_std_str_other.h"
#include"start.h"
#include "ls1d_std_exti.h"
#include"ls1d_std_timer.h"
#include"ls1d_std_spi.h"
#include"ls1d_std_i2c.h"
#include"ls1d_std_flash.h"
#include"ls1d_std_rtc.h"
#include"ls1d_std_adc.h"
#include"ls1d_std_lcd.h"
#include"ls1d_std_measure.h"
//====================================user test include file======================//
#include "UserClock.h"
#include "UserUart.h"
#include "UserTimer.h"
#include "UserLcd.h"
#include "UserRtc.h"
#include "UserGpio.h"
#include "GlobalDef.h"

#define FALSE				   -1
#define TRUE				   0



//extern void Open_Mutex(uint32_t *addr);
//extern void Release_Mutex(uint32_t *addr);

// EXT void	 (* const SYS_IrqHandle[])(void);


#endif


