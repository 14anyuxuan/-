/*
 * UserLcd.h
 *
 *  Created on: 2021Äê11ÔÂ29ÈÕ
 *      Author: Administrator
 */

#ifndef USERINC_USERLCD_H_
#define USERINC_USERLCD_H_

#include "../include/ls1d_std_gpio.h"
#include "../include/ls1d_std_lcd.h"
#include "GlobalDef.h"
#include "Main.h"

typedef enum
{
	DisplayInitMode = 0,     			/* 初始化全显示模式  */
	DisplayDayMode = 1,  				/* 常规时间模式  */
	DisplayTimeMode = 2,  				/* 常规时间模式  */
	DisplaylCurrentVelocityMode = 3,  	/* 当前流速模式*/
	DisplayCapacityMode = 4,  			/* 显示累计容量模式  */
	DisplayCapacityTurboMode = 5,  		/* 显示累计容量检定模式显示范围大  */
	DisplayResidualCapacityMode = 6,	/* 显示剩余容量模式  */
	DisplayMeterInfoMode = 7,			/* 显示表信息模式  */
	DisplayErrorStateMode =8,  		    /* 故障异常模式(C1 电源欠压 C2换能器故障C3管道内液体非满管C4余额不足C5通信故障)  */
	DisplayBatteryLowStateMode =9,  	/* 电池亏损状态模式  */
	DisplaySignalGainMode =10,  		/* 显示信号增益模式  */
	DisplayClearMode = 11,				/* 清屏模式 */
	DisplayExitMode = 12,  				/* 退出模式（LCD低功耗变暗模式）  */
	DisplayVerificationMode = 13,  		/* 进入检定模式  */
	DisplayBatteryStateMode = 14,  		/* 电池亏损状态模式  */
	DisplayTemperatureMode = 15,  		/* 水表温度显示模式  */
	DisplaySystemVersionMode = 16,  	/* 系统版本信息显示模式  */
	DisplayConfigParaMode = 17,  		/* 系配置参数模式  */
	DisplayHistoryInfoMode = 18,  		/* 历史菜单模式  */
	DisplaySystemStateMode = 19,  		/* 系统运行显示模式  */
	DisplayErrorMode = 20,  			/* 错误模式  */
	DisplayReBackMode = 21,  			/* 返回模式  */
	DisplaySoftResetMode = 22,  		/* 软复位模式  */
	DisplayUploadMessageMode = 23,  	/* nb上传数据模式  */
	DisplayHistoryNoteMode = 24,  		/* 历史条目模式  */
	DisplayClearCapacityMode = 25,  	/* 清除计量数据模式  */
	DisplaySystemTotalTimeMode = 26, 	/* 系统运行总时间模式  */
	DisplayZeroCalibrationMode = 27, 		/* 超声波测量静态零位显示模式  */
	DisplayBackwardCapacityMode = 28, 	/* 超声波测量反向流量体积显示模式  */
	DisplayErrorSubStateMode = 29,  	/* 故障异常详情模式(C1 电源欠压 C2换能器故障C3管道内液体非满管C4余额不足C5通信故障)  */
	DisplayUploadCountMode = 30, 		 /* 超声波测量反向流量体积显示模式  */
	DisplayRestartTimeMode = 31, 		 /* 超声波测量反向流量体积显示模式  */
	DisplayRestartDateMode = 32, 		 /* 超声波测量反向流量体积显示模式  */
	DisplayCompensationFactorMode = 33,  /* 补偿系数显示模式  */
	DisplayValveStateMode = 34,  /* 显示阀门状态模式  */
}LCDWorkMode;



//void lcd_test(void);

extern void LCD_Init(uint32_t refresh_rate);

#ifdef OLD_LCD
extern void Screen_ShengYu(uint32_t num);
extern void Screen_LiuLiang(uint32_t num);
extern void Screen_Money(uint32_t num);
extern void Screen_exNeedCharge(void);
extern void Screen_exFinishCharge(void);
#endif
extern void Screen_Alarm(uint32_t Id);
extern void Screen_TotalCubic(uint32_t num);
extern void Screen_FlowSpeed(int num);
extern void Screen_MeterNummber(uint8_t *buf);
extern void Screen_Time(uint8_t *buf);
extern void Screen_VerificationTotalCubic(uint32_t num);
extern void Screen_Signal(uint32_t num);
extern void Screen_BatteryPower(uint32_t num);
extern void Screen_Temperature(uint32_t num);
/* 副画面，额外在主画面添加 */
extern void Screen_ExLowPower(void);
//extern void Screen_ExTransducer(void);
//extern void Screen_ExEmptyPipe();
//extern void Screen_ExNotFullPipe();

void Screen_ExVerificationMode(void);

extern void DisplayTask(LCDWorkMode  lcd_mode);

#endif /* USERINC_USERLCD_H_ */
