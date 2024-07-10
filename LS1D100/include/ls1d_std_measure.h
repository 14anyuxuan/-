
/********************************************************************
* 文件名:   ls1d6_std_measure.h
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.09.30
* 说明:    本文件包含时差测量底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/

#ifndef INCLUDE_MEASURE_H_
#define INCLUDE_MEASURE_H_

#include "ls1d.h"
#include "ls1d_std_clock.h"



#define TDC_RES_DEFAULT      ((int)900000)
#define TDC_CAL_DEFAULT      ((int)0x0fffffff)
/****************************************************************************************
 *   										测量相关的寄存器定义 								*
 ****************************************************************************************/

/*
 *	时序控制寄存器宏定义
 */

/*  时序控制寄存器定义  */
typedef union {
        struct {
                uint32 clkhsdiv		: 2;
                uint32 startclkhs	: 3;
                uint32 hz60			: 1;
                uint32 calresnum	: 2;
                uint32 cycletof		: 2;
                uint32 cycletemp	: 2;
                uint32 cruisetof	: 2;
                uint32 cruisetemp	: 2;
                uint32 cruisex		: 1;
                uint32 cyclezero	: 1;
                uint32 cruautodir	: 1;
                uint32 crudir		: 1;
                uint32 c32ktrim		: 4;
                uint32 c32kspeed	: 1;
                uint32 c32ksel		: 1;
                uint32 osc8men		: 1;
                uint32 c8msel		: 1;
                uint32 c32ksts		: 1;
                uint32 c32kfail		: 1;
                uint32 c8msts		: 1;
                uint32 c8mfail		: 1;
        };
        uint32 reg;
} MeasureTiming_TypeDef;

/*  测量的8M是否使能 */
#define MEASURE_CRUISE_OSC8M_DISABLE	    				((uint32_t)0)
#define MEASURE_CRUISE_OSC8M_ENABLE	    					((uint32_t)1)
#define MEASURE_CRUISE_OSC8M_SHIFT	   						((uint32_t)26)
#define MEASURE_CRUISE_OSC8M_MASK	   						((uint32_t)0x04000000)

/* 巡航模式下方向对调状态读取 */
#define MEASURE_CRUISE_DIR_SHIFT	   							((uint32_t)19)
#define MEASURE_CRUISE_DIR_MASK	   								((uint32_t)0x00080000)

/* 巡航模式下方向自动对调 */
#define MEASURE_CRUISE_AUTO_DIR_DISABLE	    					((uint32_t)0)
#define MEASURE_CRUISE_AUTO_DIR_ENABLE	    					((uint32_t)1)
#define MEASURE_CRUISE_AUTO_DIR_SHIFT	   						((uint32_t)18)
#define MEASURE_CRUISE_AUTO_DIR_MASK	   						((uint32_t)0x00040000)


/* 两次的测量时间间隔置零 */
#define MEASURE_CYCLE_ZERO_DISABLE	    						((uint32_t)0)
#define MEASURE_CYCLE_ZERO_ENABLE	    						((uint32_t)1)
#define MEASURE_CYCLE_ZERO_SHIFT	   							((uint32_t)17)
#define MEASURE_CYCLE_ZERO_MASK	   								((uint32_t)0x00020000)


/* 快速巡航模式 */
#define MEASURE_CRUISE_X_DISABLE    						((uint32_t)0)
#define MEASURE_CRUISE_X_ENABLE	    					((uint32_t)1)
#define MEASURE_CRUISE_X_SHIFT	   						((uint32_t)16)
#define MEASURE_CRUISE_X_MASK	   							((uint32_t)0x00010000)

/*巡航模式下两次温度测量的间隔*/
#define MEASURE_CRUISE_TEMP_2s	    							((uint32_t)0)
#define MEASURE_CRUISE_TEMP_8s	    							((uint32_t)1)
#define MEASURE_CRUISE_TEMP_32s	    							((uint32_t)2)
#define MEASURE_CRUISE_TEMP_128s	    						((uint32_t)3)
#define MEASURE_CRUISE_TEMP_SHIFT	   							((uint32_t)14)
#define MEASURE_CRUISE_TEMP_MASK	   							((uint32_t)0x0000C000)

/*巡航模式下两次时差测量的间隔*/
#define MEASURE_CRUISE_TOF_0dot25s	    						((uint32_t)0)
#define MEASURE_CRUISE_TOF_0dot5s	    						((uint32_t)1)
#define MEASURE_CRUISE_TOF_1s	    							((uint32_t)2)
#define MEASURE_CRUISE_TOF_2s	    							((uint32_t)3)
#define MEASURE_CRUISE_TOF_SHIFT	   							((uint32_t)12)
#define MEASURE_CRUISE_TOF_MASK	   								((uint32_t)0x00003000)

/**
 * @说明 判断是否为巡航模式下的时差测量
 */
#define IS_MEASURE_CRUISE_TOF(TOF) (((TOF) == MEASURE_CRUISE_TOF_0dot25s) || ((TOF) == MEASURE_CRUISE_TOF_0dot5s)||\
 	 	 	 	 	 	     ((TOF) == MEASURE_CRUISE_TOF_1s)||((TOF) == MEASURE_CRUISE_TOF_2s))


/*普通模式下两次温度测量的间隔(50/60HZ的整数倍)*/
#define MEASURE_CYCLE_TEMP_1	    							((uint32_t)0)
#define MEASURE_CYCLE_TEMP_1dot5	    						((uint32_t)1)
#define MEASURE_CYCLE_TEMP_2	    							((uint32_t)2)
#define MEASURE_CYCLE_TEMP_2dot5	    						((uint32_t)3)
#define MEASURE_CYCLE_TEMP_SHIFT	   							((uint32_t)10)
#define MEASURE_CYCLE_TEMP_MASK	   								((uint32_t)0x00000C00)

/*巡航模式下两次时差测量的间隔(50/60HZ的整数倍)*/
#define MEASURE_CYCLE_TOF_1	    								((uint32_t)0)
#define MEASURE_CYCLE_TOF_1dot5									((uint32_t)1)
#define MEASURE_CYCLE_TOF_2										((uint32_t)2)
#define MEASURE_CYCLE_TOF_2dot5	    							((uint32_t)3)
#define MEASURE_CYCLE_TOF_SHIFT	   								((uint32_t)8)
#define MEASURE_CYCLE_TOF_MASK	   								((uint32_t)0x00000300)

/*校准陶瓷晶振的32k 时钟周期数		 */
#define MEASURE_CAL_RES_NUM_2	    							((uint32_t)0)
#define MEASURE_CAL_RES_NUM_4									((uint32_t)1)
#define MEASURE_CAL_RES_NUM_8									((uint32_t)2)
#define MEASURE_CAL_RES_NUM_16	    							((uint32_t)3)
#define MEASURE_CAL_RES_NUM_SHIFT	   							((uint32_t)6)
#define MEASURE_CAL_RES_NUM_MASK	   							((uint32_t)0x000000C0)

/*市电频率选择		 */
#define MEASURE_POWER_FREQ_HZ_50	    						((uint32_t)0)
#define MEASURE_POWER_FREQ_HZ_60								((uint32_t)1)
#define MEASURE_POWER_FREQ_HZ_SHIFT	   							((uint32_t)5)
#define MEASURE_POWER_FREQ_HZ_MASK	   							((uint32_t)0x00000020)

/*高速晶振开启到开始测量的延迟	 */
#define MEASURE_START_CLK_HS_120us	    						((uint32_t)0)
#define MEASURE_START_CLK_HS_240us								((uint32_t)1)
#define MEASURE_START_CLK_HS_480us								((uint32_t)2)
#define MEASURE_START_CLK_HS_1460us	    						((uint32_t)3)
#define MEASURE_START_CLK_HS_2440us	    						((uint32_t)4)
#define MEASURE_START_CLK_HS_5140us	    						((uint32_t)5)
#define MEASURE_START_CLK_HS_SHIFT	   							((uint32_t)2)
#define MEASURE_START_CLK_HS_MASK	   							((uint32_t)0x0000001C)

/* 参考时钟分频	 */
#define MEASURE_CLK_HS_DIV_1	    							((uint32_t)0)
#define MEASURE_CLK_HS_DIV_2									((uint32_t)1)
#define MEASURE_CLK_HS_DIV_3									((uint32_t)2)
#define MEASURE_CLK_HS_DIV_4	    							((uint32_t)3)
#define MEASURE_CLK_HS_DIV_SHIFT	   							((uint32_t)0)
#define MEASURE_CLK_HS_DIV_MASK	   								((uint32_t)0x00000003)


/*
 *	测量命令寄存器宏定义
 */
typedef union {
        struct {
                uint32 sleep		: 1;
                uint32 startop		: 1;
                uint32 mop			: 3;
                uint32 watchen		: 1;
                uint32 cruisemode	: 2;
                uint32 inten		: 8;
                uint32 intsrc		: 9;
                uint32 extinten		: 1;
                uint32 rstsrc		: 2;
                uint32 reserved		: 3;
                uint32 resread		: 1;
        };
        uint32 reg;
} MeasureCmd_TypeDef;




/* 结果读取标志(WO)	 */
#define MEASURE_RES_READ_DISABLE	    						((uint32_t)0)
#define MEASURE_RES_READ_ENABLE									((uint32_t)1)
#define MEASURE_RES_READ_SHIFT	   								((uint32_t)31)
#define MEASURE_RES_READ_MASK	   								((uint32_t)0x80000000)

/* 复位来源	(RO) */
#define MEASURE_RST_SRC_EXTERNAL	    						((uint32_t)0)
#define MEASURE_RST_SRC_WATCH_DOG0								((uint32_t)1)
#define MEASURE_RST_SRC_WATCH_DOG1	    						((uint32_t)2)
#define MEASURE_RST_SRC_WAKE_UP									((uint32_t)3)
#define MEASURE_RST_SRC_SHIFT	   								((uint32_t)26)
#define MEASURE_RST_SRC_MASK	   								((uint32_t)0x0C000000)

/* 外部中断唤醒使能 */
#define MEASURE_EXT_INT_DISABLE	    							((uint32_t)0)
#define MEASURE_EXT_INT_ENABLE									((uint32_t)1)
#define MEASURE_EXT_INT_SHIFT	   								((uint32_t)25)
#define MEASURE_EXT_INT_MASK	   								((uint32_t)0x02000000)



/* 中断使能(8bit)*/
#define MEASURE_INT_WAKE	    								((uint32_t)1)
#define MEASURE_INT_RES_READ									((uint32_t)2)
#define MEASURE_INT_BAT_FAIL	    							((uint32_t)4)
#define MEASURE_INT_C32K_FAIL									((uint32_t)8)
#define MEASURE_INT_C8M_FAIL	    							((uint32_t)16)
#define MEASURE_INT_KEY											((uint32_t)32)
#define MEASURE_INT_RING	    								((uint32_t)64)
#define MEASURE_INT_RTC											((uint32_t)128)
#define MEASURE_INT_EXINT										((uint32_t)256)

#define MEASURE_INT_WAKE_SHIFT	    							((uint32_t)16)
#define MEASURE_INT_WAKE_MASK	    							((uint32_t)0x10000)
#define MEASURE_INT_RES_READ_SHIFT								((uint32_t)17)
#define MEASURE_INT_RES_READ_MASK	    						((uint32_t)0x20000)
#define MEASURE_INT_BAT_FAIL_SHIFT	    						((uint32_t)18)
#define MEASURE_INT_BAT_FAIL_MASK	    						((uint32_t)0x40000)
#define MEASURE_INT_C32K_FAIL_SHIFT								((uint32_t)19)
#define MEASURE_INT_C32K_FAIL_MASK	    						((uint32_t)0x80000)
#define MEASURE_INT_C8M_FAIL_SHIFT	    						((uint32_t)20)
#define MEASURE_INT_C8M_FAIL_MASK	    						((uint32_t)0x100000)
#define MEASURE_INT_KEY_SHIFT									((uint32_t)21)
#define MEASURE_INT_KEY_MASK	    							((uint32_t)0x200000)
#define MEASURE_INT_RING_SHIFT	    							((uint32_t)22)
#define MEASURE_INT_RING_MASK	    							((uint32_t)0x400000)
#define MEASURE_INT_RTC_SHIFT									((uint32_t)23)
#define MEASURE_INT_RTC_MASK	    							((uint32_t)0x800000)
#define MEASURE_INT_EXINT_SHIFT									((uint32_t)24)
#define MEASURE_INT_EXINT_MASK	    							((uint32_t)0x1000000)

#define MEASURE_INT_EN_SHIFT	   								((uint32_t)8)
#define MEASURE_INT_EN_MASK	   									((uint32_t)0x0000FF00)
#define MEASURE_INT_CLR_SHIFT	   								((uint32_t)16)
#define MEASURE_INT_CLR_MASK	   								((uint32_t)0x01FF0000)
/**
 * @说明 判断是否为中断模式
 */
#define IS_MEASURE_INT_EN_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFF00) == 0x0000) && ((IT) != 0x0000))

/**
 * @说明 判断是否为中断模式
 */
#define IS_MEASURE_INT_SRC_FLAG(FLAG) (((FLAG) == MEASURE_INT_WAKE) || ((FLAG) == MEASURE_INT_RES_READ)||\
 	 	 	 	 	 	     ((FLAG) == MEASURE_INT_BAT_FAIL)||((FLAG) == MEASURE_INT_C32K_FAIL)||\
						     ((FLAG) == MEASURE_INT_C8M_FAIL)||((FLAG) == MEASURE_INT_KEY)||\
						     ((FLAG) == MEASURE_INT_RING)||((FLAG) == MEASURE_INT_RTC)\
							 ||((FLAG) == MEASURE_INT_EXINT))

///* 中断状态(RO) */
//#define MEASURE_INT_SRC_WAKE	    							((uint32_t)1)
//#define MEASURE_INT_SRC_RES_READ								((uint32_t)2)
//#define MEASURE_INT_SRC_BAT_FAIL	    						((uint32_t)4)
//#define MEASURE_INT_SRC_C32K_FAIL								((uint32_t)8)
//#define MEASURE_INT_SRC_C8M_FAIL	    						((uint32_t)16)
//#define MEASURE_INT_SRC_KEY									((uint32_t)32)
//#define MEASURE_INT_SRC_RING	    							((uint32_t)64)
//#define MEASURE_INT_SRC_RTC									((uint32_t)128)

//#define MEASURE_INT_EN_EXINT									((uint32_t)256)
///* 中断使能对应的移位*/
//#define MEASURE_INT_EN_WAKE_SHIFT	    						((uint32_t)8)
//#define MEASURE_INT_EN_RES_READ_SHIFT							((uint32_t)9)
//#define MEASURE_INT_EN_BAT_FAIL_SHIFT	    					((uint32_t)10)
//#define MEASURE_INT_EN_C32K_FAIL_SHIFT							((uint32_t)11)
//#define MEASURE_INT_EN_C8M_FAIL_SHIFT	    					((uint32_t)12)
//#define MEASURE_INT_EN_KEY_SHIFT								((uint32_t)13)
//#define MEASURE_INT_EN_RING_SHIFT	    						((uint32_t)14)
//#define MEASURE_INT_EN_RTC_SHIFT								((uint32_t)15)
//#define MEASURE_INT_EN_SHIFT	   								((uint32_t)8)
//#define MEASURE_INT_EN_MASK	   									((uint32_t)0x0000FF00)

/* 巡航模式选择 */
#define MEASURE_CRUISE_MODE_CLOSE	    						((uint32_t)0)
#define MEASURE_CRUISE_MODE_TOF									((uint32_t)1)
#define MEASURE_CRUISE_MODE_TEMP	    						((uint32_t)2)
#define MEASURE_CRUISE_MODE_TOF_TEMP							((uint32_t)3)
#define MEASURE_CRUISE_MODE_SHIFT	   							((uint32_t)6)
#define MEASURE_CRUISE_MODE_MASK	   							((uint32_t)0x000000C0)

/* 巡航模式看门狗使能 */
#define MEASURE_CRUISE_WATCH_DOG_DISABLE	    				((uint32_t)0)
#define MEASURE_CRUISE_WATCH_DOG_ENABLE							((uint32_t)1)
#define MEASURE_CRUISE_WATCH_DOG_SHIFT	   						((uint32_t)5)
#define MEASURE_CRUISE_WATCH_DOG_MASK	   						((uint32_t)0x00000020)

/* 操作码(读出为当前操作的操作码,巡航模式操作码由硬件自动设置) */
#define MEASURE_MOP_ONCE_TOF	    							((uint32_t)0)
#define MEASURE_MOP_ONCE_TEMP									((uint32_t)1)
#define MEASURE_MOP_TWICE_TOF	    							((uint32_t)2)
#define MEASURE_MOP_TWICE_TEMP									((uint32_t)3)
#define MEASURE_MOP_TDC											((uint32_t)4)
#define MEASURE_MOP_HSE_CAL										((uint32_t)5)
#define MEASURE_MOP_TRANSDUCERS									((uint32_t)6)
#define MEASURE_MOP_SHIFT	   									((uint32_t)2)
#define MEASURE_MOP_MASK	   									((uint32_t)0x0000001C)
/**
 * @说明 判断是否为MOP工作模式
 */
#define IS_MEASURE_MOP(MODE) (((MODE) == MEASURE_MOP_ONCE_TOF) || ((MODE) == MEASURE_MOP_ONCE_TEMP)||\
 	 	 	 	 	 	     ((MODE) == MEASURE_MOP_TWICE_TOF)||((MODE) == MEASURE_MOP_TWICE_TEMP)||\
						     ((MODE) == MEASURE_MOP_TDC)||((MODE) == MEASURE_MOP_HSE_CAL)||\
						     ((MODE) == MEASURE_MOP_TRANSDUCERS))

/* 启动测量操作 */
#define MEASURE_START_OP_DISABLE	    						((uint32_t)0)
#define MEASURE_START_OP_ENABLE									((uint32_t)1)
#define MEASURE_START_OP_SHIFT	   								((uint32_t)1)
#define MEASURE_START_OP_MASK	   								((uint32_t)0x00000002)

/* 启动睡眠操作 */
#define MEASURE_SLEEP_DISABLE	    							((uint32_t)0)
#define MEASURE_SLEEP_ENABLE									((uint32_t)1)
#define MEASURE_SLEEP_SHIFT	   									((uint32_t)0)
#define MEASURE_SLEEP_MASK	   									((uint32_t)0x00000001)
/*
 *	片级控制器寄存器宏定义
 */

/*  片级控制器寄存器定义  */
typedef union {
        struct {
                uint32 i2cgpio		: 1;
                uint32 adc0ien		: 1;
                uint32 adc1gpio		: 1;
                uint32 uart1gpio	: 1;
                uint32 uart0gpio	: 1;
                uint32 empigpio		: 1;
                uint32 keyigpio		: 1;
                uint32 pt34gpio		: 1;
                uint32 pt12gpio		: 1;
                uint32 spigpio		: 1;
                uint32 lcdhigpio	: 4;
                uint32 lcdallgpio	: 1;
                uint32 gpio01uart0	: 1;
                uint32 empipd		: 1;
                uint32 empipu		: 1;
                uint32 spifastup	: 1;
                uint32 spilpen		: 1;
                uint32 keyoneint	: 1;
                uint32 debugout		: 1;
                uint32 sonarout		: 1;
                uint32 batdetsel	: 2;
                uint32 pulse1carr	: 1;
                uint32 mbusoff		: 1;
                uint32 sonaroff		: 1;
                uint32 ram0off		: 1;
                uint32 fasten		: 1;
                uint32 turboen		: 1;
                uint32 pttest		: 1;
        };
        uint32 reg;
} MeasureChipCtrl_TypeDef;


/*
 *	芯片自动计算寄存器宏定义
 */

/*  自动计算寄存器定义  */
typedef union{
	struct {
		uint32 calcen           : 1;
		uint32 beggoram         : 1;
		uint32 endgoram         : 1;
		uint32 ramboot          : 1;
		uint32 fltrate          : 2;
		uint32 calc_nouse1      : 2;
		uint32 hitnum           : 5;
		uint32 calc_nouse2      : 3;
		uint32 ramentry         : 13;
		uint32 calc_nouse3      : 3;
	};
	uint32 reg;
}MeasureAutoCalc_TypeDef;
/* RAM 程序入口 */
#define MEASURE_RAM_ENTRY_SHIFT	   								((uint32_t)16)
#define MEASURE_RAM_ENTRY_MASK	   								((uint32_t)0x1FFF0000)

/* 计算的结果数目（sonarCtrl.hitIn -1） */
#define MEASURE_HIT_NUM_0	    								((uint32_t)0)
#define MEASURE_HIT_NUM_1	    								((uint32_t)1)
#define MEASURE_HIT_NUM_2	    								((uint32_t)2)
#define MEASURE_HIT_NUM_3	    								((uint32_t)3)
#define MEASURE_HIT_NUM_4	    								((uint32_t)4)
#define MEASURE_HIT_NUM_5	    								((uint32_t)5)
#define MEASURE_HIT_NUM_6	    								((uint32_t)6)
#define MEASURE_HIT_NUM_7	    								((uint32_t)7)
#define MEASURE_HIT_NUM_8	    								((uint32_t)8)
#define MEASURE_HIT_NUM_9	    								((uint32_t)9)
#define MEASURE_HIT_NUM_10	    								((uint32_t)10)
#define MEASURE_HIT_NUM_11	    								((uint32_t)11)
#define MEASURE_HIT_NUM_12	    								((uint32_t)12)
#define MEASURE_HIT_NUM_13	    								((uint32_t)13)
#define MEASURE_HIT_NUM_14	    								((uint32_t)14)
#define MEASURE_HIT_NUM_15	    								((uint32_t)15)
#define MEASURE_HIT_NUM_16	    								((uint32_t)16)
#define MEASURE_HIT_NUM_17	    								((uint32_t)17)
#define MEASURE_HIT_NUM_18	    								((uint32_t)18)
#define MEASURE_HIT_NUM_19	    								((uint32_t)19)
#define MEASURE_HIT_NUM_20	    								((uint32_t)20)
#define MEASURE_HIT_NUM_21	    								((uint32_t)21)
#define MEASURE_HIT_NUM_22	    								((uint32_t)22)
#define MEASURE_HIT_NUM_23	    								((uint32_t)23)
#define MEASURE_HIT_NUM_24	    								((uint32_t)24)
#define MEASURE_HIT_NUM_25	    								((uint32_t)25)
#define MEASURE_HIT_NUM_26	    								((uint32_t)26)
#define MEASURE_HIT_NUM_27	    								((uint32_t)27)
#define MEASURE_HIT_NUM_28	    								((uint32_t)28)
#define MEASURE_HIT_NUM_29	    								((uint32_t)29)
#define MEASURE_HIT_NUM_30	    								((uint32_t)30)
#define MEASURE_HIT_NUM_31	    								((uint32_t)31)
#define MEASURE_HIT_NUM_SHIFT	   								((uint32_t)8)
#define MEASURE_HIT_NUM_MASK	   								((uint32_t)0x00001F00)

/* 滤波配置  */
#define MEASURE_FLT_RATE_0	    								((uint32_t)0)
#define MEASURE_FLT_RATE_1	    								((uint32_t)1)
#define MEASURE_FLT_RATE_2	    								((uint32_t)2)
#define MEASURE_FLT_RATE_3	    								((uint32_t)3)
#define MEASURE_FLT_RATE_SHIFT	   								((uint32_t)4)
#define MEASURE_FLT_RATE_MASK	   								((uint32_t)0x00000030)

/* RAM 启动  */
#define MEASURE_RAM_BOOT_DISABLE	    						((uint32_t)0)
#define MEASURE_RAM_BOOT_ENABLE	    							((uint32_t)1)
#define MEASURE_RAM_BOOT_SHIFT	   								((uint32_t)3)
#define MEASURE_RAM_BOOT_MASK	   								((uint32_t)0x00000008)

/* 计算结束后跳转RAM入口  */
#define MEASURE_END_GO_RAM_DISABLE	    						((uint32_t)0)
#define MEASURE_END_GO_RAM_ENABLE	    						((uint32_t)1)
#define MEASURE_END_GO_RAM_SHIFT	   							((uint32_t)2)
#define MEASURE_END_GO_RAM_MASK	   								((uint32_t)0x00000004)

/* 计算结束前跳转RAM入口（不再进行自动计算）  */
#define MEASURE_BEG_GO_RAM_DISABLE	    						((uint32_t)0)
#define MEASURE_BEG_GO_RAM_ENABLE	    						((uint32_t)1)
#define MEASURE_BEG_GO_RAM_SHIFT	   							((uint32_t)1)
#define MEASURE_BEG_GO_RAM_MASK	   								((uint32_t)0x00000002)

/* 自动计算使能  */
#define MEASURE_CALC_DISABLE	    							((uint32_t)0)
#define MEASURE_CALC_ENABLE	    								((uint32_t)1)
#define MEASURE_CALC_SHIFT	   									((uint32_t)0)
#define MEASURE_CALC_MASK	   									((uint32_t)0x00000001)

/*
 *	命令写端口寄存器宏定义
 */

/* 命令写端口寄存器定义  */
typedef union{
    struct {
            uint32 sleep		: 1;/* 休眠状态以及睡眠使能 */
            uint32 startop		: 1;/* 启动测量操作 */
            uint32 reserved0	: 14;
            uint32 intclr		: 8;/* 中断清除 */
            uint32 reserved1	: 7;
            uint32 resread		: 1;/* 结果读出标志 */
    };
    uint32 reg;
}MeasureCMDW_TypeDef;

/* 结果读取标志(WO)	 */
#define MEASURE_RES_READW_DISABLE    							((uint32_t)0)
#define MEASURE_RES_READW_ENABLE								((uint32_t)1)
#define MEASURE_RES_READW_SHIFT	   								((uint32_t)31)
#define MEASURE_RES_READW_MASK	   								((uint32_t)0x80000000)

///* 中断使能(8bit)*/
//#define MEASURE_INT_CLR_WAKE	    							((uint32_t)1)
//#define MEASURE_INT_CLR_RES_READ								((uint32_t)2)
//#define MEASURE_INT_CLR_BAT_FAIL	    						((uint32_t)4)
//#define MEASURE_INT_CLR_C32K_FAIL								((uint32_t)8)
//#define MEASURE_INT_CLR_C8M_FAIL	    						((uint32_t)16)
//#define MEASURE_INT_CLR_KEY										((uint32_t)32)
//#define MEASURE_INT_CLR_RING	    							((uint32_t)64)
//#define MEASURE_INT_CLR_RTC										((uint32_t)128)
///* 中断使能对应的移位*/
//#define MEASURE_INT_CLR_WAKE_SHIFT	    						((uint32_t)16)
//#define MEASURE_INT_CLR_RES_READ_SHIFT							((uint32_t)17)
//#define MEASURE_INT_CLR_BAT_FAIL_SHIFT	    					((uint32_t)18)
//#define MEASURE_INT_CLR_C32K_FAIL_SHIFT							((uint32_t)19)
//#define MEASURE_INT_CLR_C8M_FAIL_SHIFT	    					((uint32_t)20)
//#define MEASURE_INT_CLR_KEY_SHIFT								((uint32_t)21)
//#define MEASURE_INT_CLR_RING_SHIFT	    						((uint32_t)22)
//#define MEASURE_INT_CLR_RTC_SHIFT								((uint32_t)23)
#define IS_MEASURE_INT_CLR_FLAG(FLAG) (((FLAG) == MEASURE_INT_WAKE) ||((FLAG) == MEASURE_INT_RES_READ)||\
 	 	 	 	 	 	     ((FLAG) == MEASURE_INT_BAT_FAIL)||((FLAG) == MEASURE_INT_C32K_FAIL)||\
						     ((FLAG) == MEASURE_INT_C8M_FAIL)||((FLAG) == MEASURE_INT_KEY)||\
						     ((FLAG) == MEASURE_INT_RING)||((FLAG) == MEASURE_INT_RTC))


/* 启动测量操作 */
#define MEASURE_START_OPW_DISABLE	    						((uint32_t)0)
#define MEASURE_START_OPW_ENABLE								((uint32_t)1)
#define MEASURE_START_OPW_SHIFT	   								((uint32_t)1)
#define MEASURE_START_OPW_MASK	   								((uint32_t)0x00000002)


/* 启动睡眠操作 */
#define MEASURE_SLEEPW_DISABLE	    							((uint32_t)0)
#define MEASURE_SLEEPW_ENABLE									((uint32_t)1)
#define MEASURE_SLEEPW_SHIFT	   								((uint32_t)0)
#define MEASURE_SLEEPW_MASK	   									((uint32_t)0x00000001)

/*
 *	脉冲定义寄存器宏定义
 */

/* 脉冲寄存器定义  */
typedef union {
        struct {
                uint32 firenum		: 7;/* 通过Fire端口发射的脉冲个数 */
                uint32 firediv		: 7;/* 发送脉冲分频数 +  FireCurr 形成> 64 的分频 */
                uint32 firesel		: 1;/* fire 输出选择 */
                uint32 stopsel		: 1;/* 要计算的结果数 */
                uint32 firephase	: 15;/* fire 脉冲相位向量，16~30bit 每位对应1~15脉冲相位 */
                uint32 fireinv		: 1;/* fire 时钟取反 */
        };
        uint32 reg;
}MeasurePulse_TypeDef;

/* FIRE时钟取反 */
#define MEASURE_FIRE_INV_DISABLE  							((uint32_t)0)
#define MEASURE_FIRE_INV_ENABLE	    						((uint32_t)1)
#define MEASURE_FIRE_INV_SHIFT	   							((uint32_t)31)
#define MEASURE_FIRE_INV_MASK	   							((uint32_t)0x80000000)
/* FIRE脉冲向量先高后低还是先低后高  */
#define MEASURE_FIRE_PHASE_HL	    						((uint32_t)0)
#define MEASURE_FIRE_PHASE_LH	    						((uint32_t)1)
#define MEASURE_FIRE_PHASE_SHIFT	   						((uint32_t)16)
#define MEASURE_FIRE_PHASE_MASK	   							((uint32_t)0x7FFF0000)

/* STOP输入选择  */
#define MEASURE_STOP_SEL_1	    							((uint32_t)0)
#define MEASURE_STOP_SEL_2	    							((uint32_t)1)
#define MEASURE_STOP_SEL_SHIFT	   							((uint32_t)15)
#define MEASURE_STOP_SEL_MASK	   							((uint32_t)0x00008000)
/* FIRE输出选择  */
#define MEASURE_FIRE_SEL_1	    							((uint32_t)0)
#define MEASURE_FIRE_SEL_2	    							((uint32_t)1)
#define MEASURE_FIRE_SEL_SHIFT	   							((uint32_t)14)
#define MEASURE_FIRE_SEL_MASK	   							((uint32_t)0x00004000)
/* FIRE端口驱动能力  */
#define MEASURE_FIRE_CURR_16MA	    						((uint32_t)0)
#define MEASURE_FIRE_CURR_32MA	    						((uint32_t)1)
#define MEASURE_FIRE_CURR_SHIFT	   							((uint32_t)13)
#define MEASURE_FIRE_CURR_MASK	   							((uint32_t)0x00002000)
/* FIRE发送脉冲分频系数  */
#define MEASURE_FIRE_DIV_SHIFT	   							((uint32_t)7)
#define MEASURE_FIRE_DIV_MASK	   							((uint32_t)0x00003F80)

/* FIRE发送脉冲数  */
#define MEASURE_FIRE_NUM_SHIFT	   							((uint32_t)0)
#define MEASURE_FIRE_NUM_MASK	   							((uint32_t)0x0000007F)


/*
 *	时差测量控制寄存器宏定义
 */

/* 时差测量控制寄存器定义  */
typedef union {
        struct {
                uint32 waitend		: 8;/* 等待阶段结束时间 */
                uint32 tailend		: 7;/* 拉零阶段结束时间 */
                uint32 negstop		: 1;/* stop通道反相 */
                uint32 autocalpre	: 1;/* TDC自动前校准 */
                uint32 autocalpst	: 1;/* TDC自动后校准 */
                uint32 calnegedge	: 1;/* 负沿校准*/
                uint32 watchfire	: 1;/* fire 发波期间测量回波 */
                uint32 hitin		: 6;/* 预期的stop脉冲数 */
                uint32 hitign		: 2;/* 忽略的stop个数  */
                uint32 trefchrg		: 2;/* 将stop 输入充电到参考电压的时间  */
                uint32 timeoutsel	: 2;/* 溢出时间选择 */
        };
        uint32 reg;
}MeasureSonarCtrl_TypeDef;
/* 溢出时间选择 */
#define MEASURE_TIME_OUT_SEL_64US  							((uint32_t)0)
#define MEASURE_TIME_OUT_SEL_256US	    					((uint32_t)1)
#define MEASURE_TIME_OUT_SEL_1024US  						((uint32_t)2)
#define MEASURE_TIME_OUT_SEL_4096US	    					((uint32_t)3)
#define MEASURE_TIME_OUT_SEL_SHIFT	   						((uint32_t)30)
#define MEASURE_TIME_OUT_SEL_MASK	   						((uint32_t)0xC0000000)


/* 将stop输入充电到参考电压的时间(时间应当小于startclkhs的值)  */
#define MEASURE_TREF_CHARGE_90US  							((uint32_t)0)
#define MEASURE_TREF_CHARGE_120US	    					((uint32_t)1)
#define MEASURE_TREF_CHARGE_150US  							((uint32_t)2)
#define MEASURE_TREF_CHARGE_300US	    					((uint32_t)3)
#define MEASURE_TREF_CHARGE_SHIFT	   						((uint32_t)28)
#define MEASURE_TREF_CHARGE_MASK	   						((uint32_t)0x30000000)
/* 忽略的stop个数  */
#define MEASURE_HIT_IGN_0  									((uint32_t)0)
#define MEASURE_HIT_IGN_1	    							((uint32_t)1)
#define MEASURE_HIT_IGN_2  									((uint32_t)2)
#define MEASURE_HIT_IGN_3	    							((uint32_t)3)
#define MEASURE_HIT_IGN_SHIFT	   							((uint32_t)26)
#define MEASURE_HIT_IGN_MASK	   							((uint32_t)0x0C000000)
/* 预期的stop个数  */
#define MEASURE_HIT_IN_0  									((uint32_t)0)
#define MEASURE_HIT_IN_1	    							((uint32_t)1)
#define MEASURE_HIT_IN_2  									((uint32_t)2)
#define MEASURE_HIT_IN_3	    							((uint32_t)3)
#define MEASURE_HIT_IN_4  									((uint32_t)4)
#define MEASURE_HIT_IN_5	    							((uint32_t)5)
#define MEASURE_HIT_IN_6  									((uint32_t)6)
#define MEASURE_HIT_IN_7	    							((uint32_t)7)
#define MEASURE_HIT_IN_8  									((uint32_t)8)
#define MEASURE_HIT_IN_9	    							((uint32_t)9)
#define MEASURE_HIT_IN_10  									((uint32_t)10)
#define MEASURE_HIT_IN_11	    							((uint32_t)11)
#define MEASURE_HIT_IN_12  									((uint32_t)12)
#define MEASURE_HIT_IN_13	    							((uint32_t)13)
#define MEASURE_HIT_IN_14  									((uint32_t)14)
#define MEASURE_HIT_IN_15	    							((uint32_t)15)
#define MEASURE_HIT_IN_16  									((uint32_t)16)
#define MEASURE_HIT_IN_17	    							((uint32_t)17)
#define MEASURE_HIT_IN_18  									((uint32_t)18)
#define MEASURE_HIT_IN_19	    							((uint32_t)19)
#define MEASURE_HIT_IN_20  									((uint32_t)20)
#define MEASURE_HIT_IN_21	    							((uint32_t)21)
#define MEASURE_HIT_IN_22  									((uint32_t)22)
#define MEASURE_HIT_IN_23	    							((uint32_t)23)
#define MEASURE_HIT_IN_24  									((uint32_t)24)
#define MEASURE_HIT_IN_25	    							((uint32_t)25)
#define MEASURE_HIT_IN_26  									((uint32_t)26)
#define MEASURE_HIT_IN_27	    							((uint32_t)27)
#define MEASURE_HIT_IN_28  									((uint32_t)28)
#define MEASURE_HIT_IN_29	    							((uint32_t)29)
#define MEASURE_HIT_IN_30  									((uint32_t)30)
#define MEASURE_HIT_IN_31	    							((uint32_t)31)
#define MEASURE_HIT_IN_32	    							((uint32_t)32)
#define MEASURE_HIT_IN_SHIFT	   							((uint32_t)20)
#define MEASURE_HIT_IN_MASK	   								((uint32_t)0x03F00000)
/* FIRE发波期间测量回波与否  */
#define MEASURE_WATCH_FIRE_DISABLE	    					((uint32_t)0)
#define MEASURE_WATCH_FIRE_ENABLE	    					((uint32_t)1)
#define MEASURE_WATCH_FIRE_SHIFT	   						((uint32_t)19)
#define MEASURE_WATCH_FIRE_MASK	   							((uint32_t)0x00080000)

/* 负沿校准   */
#define MEASURE_CAL_NEG_EDGE_DISABLE	    				((uint32_t)0)
#define MEASURE_CAL_NEG_EDGE_ENABLE	    					((uint32_t)1)
#define MEASURE_CAL_NEG_EDGE_SHIFT	   						((uint32_t)18)
#define MEASURE_CAL_NEG_EDGE_MASK	   						((uint32_t)0x00040000)

/* 自动后校准使能  */
#define MEASURE_AUTO_CAL_PST_DISABLE	    				((uint32_t)0)
#define MEASURE_AUTO_CAL_PST_ENABLE	    					((uint32_t)1)
#define MEASURE_AUTO_CAL_PST_SHIFT	   						((uint32_t)17)
#define MEASURE_AUTO_CAL_PST_MASK	   						((uint32_t)0x00020000)

/* 自动前校准使能  */
#define MEASURE_AUTO_CAL_PRE_DISABLE	    				((uint32_t)0)
#define MEASURE_AUTO_CAL_PRE_ENABLE	    					((uint32_t)1)
#define MEASURE_AUTO_CAL_PRE_SHIFT	   						((uint32_t)16)
#define MEASURE_AUTO_CAL_PRE_MASK	   						((uint32_t)0x00010000)
/* STOP 通道反相  */
#define MEASURE_NEG_STOP_DISABLE	    					((uint32_t)0)
#define MEASURE_NEG_STOP_ENABLE	    						((uint32_t)1)
#define MEASURE_NEG_STOP_SHIFT	   							((uint32_t)15)
#define MEASURE_NEG_STOP_MASK	   							((uint32_t)0x00008000)

/* 拉零阶段结束时间  */
#define MEASURE_TAIL_END_SHIFT	   							((uint32_t)8)
#define MEASURE_TAIL_END_MASK	   							((uint32_t)0x00007F00)

/* 等待阶段结束时间  */
#define MEASURE_WAIT_END_SHIFT	   							((uint32_t)0)
#define MEASURE_WAIT_END_MASK	   							((uint32_t)0x0000007F)

/*
 *	TDC1寄存器宏定义
 */

/*  TDC1寄存器定义  */
typedef union {
        struct {
                uint32 dres			: 1;/* TDC参数选择 */
                uint32 dsmp			: 1;
                uint32 dstype		: 1;
                uint32 reserved0	: 1;
                uint32 pden			: 1;
                uint32 pdauto		: 1;
                uint32 cpden		: 1;
                uint32 cpdsame		: 1;
                uint32 calres		: 1;
                uint32 calsmp		: 1;
                uint32 caltype		: 1;
                uint32 calmr1		: 1;
                uint32 calonehit	: 1;
                uint32 calhitsel	: 1;
                uint32 corrsub		: 1;
                uint32 dlytune		: 4;
                uint32 ringfix		: 1;
                uint32 reserved1	: 4;
                uint32 dbg0sel		: 2;/* 调试输出DBG1选择  */
                uint32 dbg1sel		: 2;/* 调试输出DBG1选择 */
                uint32 reserved2	: 4;/* 溢出时间选择 */
        };
        uint32 reg;
}MeasureTDCCtrl1_TypeDef;


/* 自动前校准使能  */
#define MEASURE_DBG_REMAP_DISABLE	    						((uint32_t)0)
#define MEASURE_DBG_REMAP_ENABLE	    						((uint32_t)1)
#define MEASURE_DBG_REMAP_SHIFT	   								((uint32_t)21)
#define MEASURE_DBG_REMAP_MASK	   								((uint32_t)0x00200000)

/* 调试输出DBG1 选择 */
#define MEASURE_DBG1_SEL_STOP	 		   						((uint32_t)0)
#define MEASURE_DBG1_SEL_COMPARE	    						((uint32_t)1)
#define MEASURE_DBG1_SEL_TDC	    							((uint32_t)2)
#define MEASURE_DBG1_SEL_LDSENSET	    						((uint32_t)3)
#define MEASURE_DBG1_SEL_SHIFT	   								((uint32_t)26)
#define MEASURE_DBG1_SEL_MASK	   								((uint32_t)0x0C000000)

/* 调试输出DBG0 选择 */
#define MEASURE_DBG0_SEL_START	 		   						((uint32_t)0)
#define MEASURE_DBG0_SEL_STOP	    							((uint32_t)1)
#define MEASURE_DBG0_SEL_COMPARE	    						((uint32_t)2)
#define MEASURE_DBG0_SEL_TDC	    							((uint32_t)3)
#define MEASURE_DBG0_SEL_SHIFT	   								((uint32_t)24)
#define MEASURE_DBG0_SEL_MASK	   								((uint32_t)0x03000000)

/* TDC 参数选项 选 */
#define MEASURE_TDC_OPT_DRES			 		   				((uint32_t)0x00000001)
#define MEASURE_TDC_OPT_DSMP	    							((uint32_t)0x00000002)
#define MEASURE_TDC_OPT_DSTYPE	    							((uint32_t)0x00000004)//缺少第三位的变量
#define MEASURE_TDC_OPT_PDEN	    							((uint32_t)0x00000010)
#define MEASURE_TDC_OPT_PDAUTO	    							((uint32_t)0x00000020)
#define MEASURE_TDC_OPT_CPDEN	    							((uint32_t)0x00000040)
#define MEASURE_TDC_OPT_CPDSAME	    							((uint32_t)0x00000080)
#define MEASURE_TDC_OPT_CALRES	    							((uint32_t)0x00000100)
#define MEASURE_TDC_OPT_CALSMP	    							((uint32_t)0x00000200)
#define MEASURE_TDC_OPT_CALTYPE	    							((uint32_t)0x00000400)
#define MEASURE_TDC_OPT_CALMR1	    							((uint32_t)0x00000800)
#define MEASURE_TDC_OPT_CALONEHIT	    						((uint32_t)0x00001000)
#define MEASURE_TDC_OPT_CALHITSEL	    						((uint32_t)0x00002000)
#define MEASURE_TDC_OPT_CORRSUB	    							((uint32_t)0x00004000)

#define MEASURE_TDC_OPT_DLYTUNE0	    						((uint32_t)0x00000000)
#define MEASURE_TDC_OPT_DLYTUNE1	    						((uint32_t)0x00008000)
#define MEASURE_TDC_OPT_DLYTUNE2	    						((uint32_t)0x00010000)
#define MEASURE_TDC_OPT_DLYTUNE3	    						((uint32_t)0x00018000)
#define MEASURE_TDC_OPT_DLYTUNE4	    						((uint32_t)0x00020000)
#define MEASURE_TDC_OPT_DLYTUNE5	    						((uint32_t)0x00028000)
#define MEASURE_TDC_OPT_DLYTUNE6	    						((uint32_t)0x00030000)
#define MEASURE_TDC_OPT_DLYTUNE7	    						((uint32_t)0x00038000)
#define MEASURE_TDC_OPT_RINGFIX	    							((uint32_t)0x00080000)
#define MEASURE_TDC_OPT_SHIFT	   								((uint32_t)0)
#define MEASURE_TDC_OPT_MASK	   								((uint32_t)0x0000FFFF)
/*
 *	TDC2寄存器宏定义
 *	（预延迟量较多，尚未编写）
 */

/* TDC2寄存器定义  */
typedef union {
        struct {
                uint32 predlyval	: 10;/* 预延迟量*/
                uint32 reserved0	: 2;/* 保留 */
                uint32 predlyinc	: 2;/* 预延迟量增量 */
                uint32 reserved1	: 2;/* 预期的stop脉冲数 */
                uint32 pdauto		: 10;/* 自动维护的预延迟量  */
                uint32 reserved2	: 5;/* 将stop 输入充电到参考电压的时间  */
                uint32 pdend		: 1;/* 当前预延迟量达到极值的标志（RO）*/
        };
        uint32 reg;
}MeasureTDCCtrl2_TypeDef;

/* 当前的预延迟量到达极限值的标识(RO) */
#define MEASURE_TDC_PD_END_SHIFT	   							((uint32_t)31)
#define MEASURE_TDC_PD_END_MASK	   								((uint32_t)0x80000000)

/* 当前的预延迟量到达极限值的标识(RO) */
#define MEASURE_TDC_PD_AUTO_SHIFT	   							((uint32_t)16)
#define MEASURE_TDC_PD_AUTO_MASK	   							((uint32_t)0x03FF0000)

/* 自动维护时预延迟的增量   */
#define MEASURE_TDC_PRE_DLY_INC1	    						((uint32_t)0)
#define MEASURE_TDC_PRE_DLY_INC2	    						((uint32_t)1)
#define MEASURE_TDC_PRE_DLY_INC3	    						((uint32_t)2)
#define MEASURE_TDC_PRE_DLY_INC4	    						((uint32_t)3)
#define MEASURE_TDC_PRE_DLY_INC_SHIFT	   						((uint32_t)12)
#define MEASURE_TDC_PRE_DLY_INC_MASK	   						((uint32_t)0x00003000)

/* 预延迟量 (RW)  */
#define MEASURE_TDC_PRE_DLY_VAL_SHIFT	   						((uint32_t)0)
#define MEASURE_TDC_PRE_DLY_VAL_MASK	   						((uint32_t)0x000003FF)





/*
 *	校准控制寄存器宏定义
 *
 */

/*  校准控制寄存器定义  */
typedef union {
        struct {
                uint32 calzero		: 10;/* 软件设置的零点 */
                uint32 calmethod	: 1;/* 校准算法 */
                uint32 calbypass	: 1;/* 关闭自动校准 */
                uint32 caldelay		: 3;/* 校准环路延迟时间 */
                uint32 reserved0	: 1;/* 保留 */
                uint32 zerolevel	: 10;/* 校准得到的零点值（RO） */
                uint32 reserved1	: 6;/* 保留 */
        };
        uint32 reg;

}MeasureCalibCtrl_TypeDef;

/* 校准得到的零点值 范围0~1024*/
#define MEASURE_CALIBCTRL_ZEROLEVEL_SHIFT	   				((uint32_t)16)
#define MEASURE_CALIBCTRL_ZEROLEVEL_MASK	   				((uint32_t)0x03FF0000)


/* 校准环路延迟 */
#define MEASURE_CALIBCTRL_CALDELAY0	   						((uint32_t)0)
#define MEASURE_CALIBCTRL_CALDELAY1	   						((uint32_t)1)
#define MEASURE_CALIBCTRL_CALDELAY2	   						((uint32_t)2)
#define MEASURE_CALIBCTRL_CALDELAY3	   						((uint32_t)3)
#define MEASURE_CALIBCTRL_CALDELAY4	   						((uint32_t)4)
#define MEASURE_CALIBCTRL_CALDELAY5	   						((uint32_t)5)
#define MEASURE_CALIBCTRL_CALDELAY6	   						((uint32_t)6)
#define MEASURE_CALIBCTRL_CALDELAY7	   						((uint32_t)7)
#define MEASURE_CALIBCTRL_CALDELAY_SHIFT	   				((uint32_t)12)
#define MEASURE_CALIBCTRL_CALDELAY_MASK	   					((uint32_t)0x00007000)

/* 关闭自动校准 */
#define MEASURE_CALIBCTRL_CALBYPASS_ENABLE	 		   		((uint32_t)0)
#define MEASURE_CALIBCTRL_CALBYPASS_DISABLE	 		   		((uint32_t)1)
#define MEASURE_CALIBCTRL_CALBYPASS_SHIFT	   				((uint32_t)11)
#define MEASURE_CALIBCTRL_CALBYPASS_MASK	   				((uint32_t)0x00000800)


/* 校准算法 */
#define MEASURE_CALIBCTRL_CALMETHOD_LINEAR	 		   		((uint32_t)0)
#define MEASURE_CALIBCTRL_CALMETHOD_BISECTION	 		   	((uint32_t)1)
#define MEASURE_CALIBCTRL_CALMETHOD_SHIFT	   				((uint32_t)10)
#define MEASURE_CALIBCTRL_CALMETHOD_MASK	   				((uint32_t)0x00000400)
/* 软件设置的零点(0 ~ 1024)*/
#define MEASURE_CALIBCTRL_CALZERO_SHIFT	   				((uint32_t)0)
#define MEASURE_CALIBCTRL_CALZERO_MASK	   				((uint32_t)0x000003FF)


/*
 *	首波控制寄存器宏定义
 *
 */

/* 首波控制寄存器定义  */
typedef union {
        struct {
                uint32 autofw		: 1;/* 首波模式自动使能 */
                uint32 wavewen		: 1;/* 波形宽度测量使能 */
                uint32 reserved0	: 2;/* 校准环路延迟时间 */
                uint32 fhl			: 10;/* 首波阈值 */
                uint32 reserved1	: 2;/* 保留 */
                uint32 wavepen		: 1;/* 波峰测量模式使能 */
                uint32 reserved2	: 15;/* 保留 */
        };
        uint32 reg;
}MeasureFWaveCtrl_TypeDef;

/* 波峰测量模式使能 */
#define MEASURE_FWAVECTRL_WAVEP_DISABLE	   					((uint32_t)0)
#define MEASURE_FWAVECTRL_WAVEP_ENABLE	   					((uint32_t)1)
#define MEASURE_FWAVECTRL_WAVEP_SHIFT	   					((uint32_t)16)
#define MEASURE_FWAVECTRL_WAVEP_MASK	   					((uint32_t)0x00010000)


/* 首波阈值(0~1024  ) */
#define MEASURE_FWAVECTRL_FHL_SHIFT	   						((uint32_t)4)
#define MEASURE_FWAVECTRL_FHL_MASK	   						((uint32_t)0x00003FF0)

/* 波宽测量使能 */
#define MEASURE_FWAVECTRL_WAVEW_DISABLE	   					((uint32_t)0)
#define MEASURE_FWAVECTRL_WAVEW_ENABLE	   					((uint32_t)1)
#define MEASURE_FWAVECTRL_WAVEW_SHIFT	   					((uint32_t)1)
#define MEASURE_FWAVECTRL_WAVEW_MASK	   					((uint32_t)0x00000002)
/* 首波模式使能 */
#define MEASURE_FWAVECTRL_AUTOFW_DISABLE	   				((uint32_t)0)
#define MEASURE_FWAVECTRL_AUTOFW_ENABLE	   					((uint32_t)1)
#define MEASURE_FWAVECTRL_AUTOFW_SHIFT	   					((uint32_t)0)
#define MEASURE_FWAVECTRL_AUTOFW_MASK	   					((uint32_t)0x00000001)

/*
 *	模拟前端控制寄存器宏定义
 *
 */
/*  模拟前端控制寄存器定义  */
typedef union {
        struct {
                uint32 dacen		: 1;/* DAC 使能  */
                uint32 dacrange		: 1;/* DAC 范围 */
                uint32 dacugen		: 1;/* DAC 单位增益放大器使能  */
                uint32 vrefsel		: 1;/* VREF选择 */
                uint32 vrefen		: 1;/* VREF使能  */
                uint32 vrefdrv		: 2;/* VREF驱动能力控制 */
                uint32 lnaen		: 1;/* LNA使能  */
                uint32 lnaenc		: 1;/* LNA电容反馈  */
                uint32 compen		: 1;/* 比较器使能 */
                uint32 compsel		: 3;/* 比较器控制 */
                uint32 vrefout		: 1;/* 模拟电压1输出控制 */
                uint32 vtestout		: 3;/* 模拟电压1输出控制 */
                uint32 vcmpen		: 1;/* VCMP输出使能 */
                uint32 eopien		: 1;/* EOPI输出使能  */
                uint32 stopterm0	: 1;/* 接收端拉0 */
                uint32 rxpulldown	: 2;/* 使用发波端的RX在发波后强制下拉  */
                uint32 txdrive		: 2;/* 发波驱动能力控制 */
                uint32 rxen			: 1;/* 接收使能 */
                uint32 ldref		: 2;/* LNA输入前端控制 */
                uint32 manmode		: 1;/* AFE内部模块手动控制 */
                uint32 reserved		: 1;/* 保留 */
                uint32 vtesten		: 1;/* AD测量使能 */
                uint32 vtestdual	: 1;/* 双向测量操作都启动AD */
                uint32 vtestsel		: 1;/* AD测量通道选择 */
        };
        uint32 reg;

}MeasureAfeCtrl_TypeDef;

/* AD测量通道选择 */
#define MEASURE_AFECTRL_VTEST_SEL_VREF	   					((uint32_t)0)
#define MEASURE_AFECTRL_VTEST_SEL_DAC_AMC	   				((uint32_t)1)
#define MEASURE_AFECTRL_VTEST_SEL_SHIFT	   					((uint32_t)31)
#define MEASURE_AFECTRL_VTEST_SEL_MASK	   					((uint32_t)0x80000000)


/* 双向时差测量操作都启动AD */
#define MEASURE_AFECTRL_VTEST_DUAL_DISABLE	   				((uint32_t)0)
#define MEASURE_AFECTRL_VTEST_DUAL_ENABLE	   				((uint32_t)1)
#define MEASURE_AFECTRL_VTEST_DUAL_SHIFT	   				((uint32_t)30)
#define MEASURE_AFECTRL_VTEST_DUAL_MASK	   					((uint32_t)0x40000000)

/* AD测量使能 */
#define MEASURE_AFECTRL_VTEST_DISABLE	   					((uint32_t)0)
#define MEASURE_AFECTRL_VTEST_ENABLE	   					((uint32_t)1)
#define MEASURE_AFECTRL_VTEST_SHIFT	   						((uint32_t)29)
#define MEASURE_AFECTRL_VTEST_MASK	   						((uint32_t)0x20000000)

/* AFE内部模块手工控制  */
#define MEASURE_AFECTRL_MANMODE_DISABLE	   					((uint32_t)0)
#define MEASURE_AFECTRL_MANMODE_ENABLE	   					((uint32_t)1)
#define MEASURE_AFECTRL_MANMODE_SHIFT	   				    ((uint32_t)27)
#define MEASURE_AFECTRL_MANMODE_MASK	   					((uint32_t)0x08000000)


/* LNA输入端驱动控制  */
#define MEASURE_AFECTRL_LDREF_HIGH_IMPEDENCE	   			((uint32_t)0)
#define MEASURE_AFECTRL_LDREF_VREF_HIGH_IMPEDENCE			((uint32_t)1)
#define MEASURE_AFECTRL_LDREF_PLUSE_VREF					((uint32_t)2)
#define MEASURE_AFECTRL_LDREF_VREF							((uint32_t)3)
#define MEASURE_AFECTRL_LDREF_SHIFT	   				    	((uint32_t)25)
#define MEASURE_AFECTRL_LDREF_MASK	   						((uint32_t)0x06000000)


/* RX接收使能  */
#define MEASURE_AFECTRL_RX_DISABLE	   						((uint32_t)0)
#define MEASURE_AFECTRL_RX_ENABLE	   						((uint32_t)1)
#define MEASURE_AFECTRL_RX_SHIFT	   				    	((uint32_t)24)
#define MEASURE_AFECTRL_RX_MASK	   							((uint32_t)0x01000000)


/* TX驱动能力  */
#define MEASURE_AFECTRL_TX_16MA								((uint32_t)1)
#define MEASURE_AFECTRL_TX_8MA								((uint32_t)2)
#define MEASURE_AFECTRL_TX_24MA								((uint32_t)3)
#define MEASURE_AFECTRL_TX_SHIFT	   				    	((uint32_t)22)
#define MEASURE_AFECTRL_TX_MASK	   							((uint32_t)0x00C00000)

/* 使用发波端的RX在发波后强下拉  */
#define MEASURE_AFECTRL_RX_NOT_PULL_DOWN					((uint32_t)0)
#define MEASURE_AFECTRL_RX_PULL_DOWN_TAIL					((uint32_t)1)
#define MEASURE_AFECTRL_RX_PULL_DOWN_ALWAYS					((uint32_t)3)
#define MEASURE_AFECTRL_RX_PULL_DOWN_SHIFT	   				((uint32_t)20)
#define MEASURE_AFECTRL_RX_PULL_DOWN_MASK	   				((uint32_t)0x00300000)


/* 接收端拉零  */
#define MEASURE_AFECTRL_STOP_TERM0_VREF					((uint32_t)0)
#define MEASURE_AFECTRL_STOP_TERM0_ZERO					((uint32_t)1)
#define MEASURE_AFECTRL_STOP_TERM0_SHIFT	   			((uint32_t)19)
#define MEASURE_AFECTRL_STOP_TERM0_MASK	   				((uint32_t)0x00080000)


/* EOPI 输出使能  */
#define MEASURE_AFECTRL_EOPI_DISABLE					((uint32_t)0)
#define MEASURE_AFECTRL_EOPI_ENABLE						((uint32_t)1)
#define MEASURE_AFECTRL_EOPI_SHIFT	   					((uint32_t)18)
#define MEASURE_AFECTRL_EOPI_MASK	   					((uint32_t)0x00040000)


/* VCMP 输出使能  */
#define MEASURE_AFECTRL_VCMP_DISABLE					((uint32_t)0)
#define MEASURE_AFECTRL_VCMP_ENABLE						((uint32_t)1)
#define MEASURE_AFECTRL_VCMP_SHIFT	   					((uint32_t)17)
#define MEASURE_AFECTRL_VCMP_MASK	   					((uint32_t)0x00020000)
/* 模拟电压输出控制  */
#define MEASURE_AFECTRL_VTEST_OUT_CLOSE					((uint32_t)0)
#define MEASURE_AFECTRL_VTEST_OUT_VCMP					((uint32_t)3)
#define MEASURE_AFECTRL_VTEST_OUT_VAMC					((uint32_t)5)
#define MEASURE_AFECTRL_VTEST_OUT_OTHER					((uint32_t)7)
#define MEASURE_AFECTRL_VTEST_OUT_SHIFT	   				((uint32_t)14)
#define MEASURE_AFECTRL_VTEST_OUT_MASK	   				((uint32_t)0x0001C000)

/* 模拟电压1输出控制  */
#define MEASURE_AFECTRL_VREF_OUT_DISABLE					((uint32_t)0)
#define MEASURE_AFECTRL_VREF_OUT_ENABLE					((uint32_t)1)
#define MEASURE_AFECTRL_VREF_OUT_SHIFT	   				((uint32_t)13)
#define MEASURE_AFECTRL_VREF_OUT_MASK	   				((uint32_t)0x00002000)


/* 比较器控制选择  */
#define MEASURE_AFECTRL_COMP_SEL_LNA_BYPASS				((uint32_t)1)
#define MEASURE_AFECTRL_COMP_SEL_LNA					((uint32_t)2)
#define MEASURE_AFECTRL_COMP_SEL_LNA_EOPO				((uint32_t)6)
#define MEASURE_AFECTRL_COMP_SEL_EOPO					((uint32_t)4)
#define MEASURE_AFECTRL_COMP_SEL_SHIFT	   				((uint32_t)10)
#define MEASURE_AFECTRL_COMP_SEL_MASK	   				((uint32_t)0x00001C00)


/* 比较器输出使能  */
#define MEASURE_AFECTRL_COMP_DISABLE					((uint32_t)0)
#define MEASURE_AFECTRL_COMP_ENABLE						((uint32_t)1)
#define MEASURE_AFECTRL_COMP_SHIFT	   					((uint32_t)9)
#define MEASURE_AFECTRL_COMP_MASK	   					((uint32_t)0x00000200)



/* LNA电容反馈使能  */
#define MEASURE_AFECTRL_LNA_ENC_DISABLE					((uint32_t)0)
#define MEASURE_AFECTRL_LNA_ENC_ENABLE					((uint32_t)1)
#define MEASURE_AFECTRL_LNA_ENC_SHIFT	   				((uint32_t)8)
#define MEASURE_AFECTRL_LNA_ENC_MASK	   				((uint32_t)0x00000100)


/* LNA使能  */
#define MEASURE_AFECTRL_LNA_DISABLE						((uint32_t)0)
#define MEASURE_AFECTRL_LNA_ENABLE						((uint32_t)1)
#define MEASURE_AFECTRL_LNA_SHIFT	   					((uint32_t)7)
#define MEASURE_AFECTRL_LNA_MASK	   					((uint32_t)0x00000080)


/* VREF驱动能力控制   */
#define MEASURE_AFECTRL_VREF_DRV_33OHM					((uint32_t)0)
#define MEASURE_AFECTRL_VREF_DRV_50OHM					((uint32_t)1)
#define MEASURE_AFECTRL_VREF_DRV_100OHM					((uint32_t)2)
#define MEASURE_AFECTRL_VREF_DRV_1000OHM				((uint32_t)3)
#define MEASURE_AFECTRL_VREF_DRV_SHIFT	   				((uint32_t)5)
#define MEASURE_AFECTRL_VREF_DRV_MASK	   				((uint32_t)0x00000060)


/* VREF使能   */
#define MEASURE_AFECTRL_VREF_DISABLE					((uint32_t)0)
#define MEASURE_AFECTRL_VREF_ENABLE						((uint32_t)1)
#define MEASURE_AFECTRL_VREF_SHIFT	   					((uint32_t)4)
#define MEASURE_AFECTRL_VREF_MASK	   					((uint32_t)0x00000010)

/* VREF选择   */
#define MEASURE_AFECTRL_VREF_SEL_0dot86V				((uint32_t)0)
#define MEASURE_AFECTRL_VREF_SEL_1dot07V				((uint32_t)1)
#define MEASURE_AFECTRL_VREF_SEL_SHIFT	   				((uint32_t)3)
#define MEASURE_AFECTRL_VREF_SEL_MASK	   				((uint32_t)0x00000008)


/* DAC单位增益放大使能   */
#define MEASURE_AFECTRL_DAC_UG_DISABLE					((uint32_t)0)
#define MEASURE_AFECTRL_DAC_UG_ENABLE					((uint32_t)1)
#define MEASURE_AFECTRL_DAC_UG_SHIFT	   				((uint32_t)2)
#define MEASURE_AFECTRL_DAC_UG_MASK	   					((uint32_t)0x00000004)


/* DAC范围   */
#define MEASURE_AFECTRL_DAC_RANGE_0_0dot8				((uint32_t)0)
#define MEASURE_AFECTRL_DAC_RANGE_0dot6_1dot3			((uint32_t)1)
#define MEASURE_AFECTRL_DAC_RANGE_SHIFT	   				((uint32_t)1)
#define MEASURE_AFECTRL_DAC_RANGE_MASK	   				((uint32_t)0x00000002)


/* DAC使能  */
#define MEASURE_AFECTRL_DAC_DISABLE						((uint32_t)0)
#define MEASURE_AFECTRL_DAC_ENABLE						((uint32_t)1)
#define MEASURE_AFECTRL_DAC_SHIFT	   					((uint32_t)0)
#define MEASURE_AFECTRL_DAC_MASK	   					((uint32_t)0x00000001)


/*
 *	窗口延迟链配置寄存器宏定义
 *
 */

/*  窗口延迟链寄存器定义  */
typedef union {
        struct {
                uint32 dlcalen		: 1;/* 延迟校准值使能 */
                uint32 dlcalbyp		: 1;/* 延迟校准值旁路 */
                uint32 reserved0	: 6;/* 保留 */
                uint32 dlinelen		: 7;/* 校准结果（ro） */
                uint32 reserved1	: 17;/* 保留 */
        };
        uint32 reg;
}MeasureDLineCtrl_TypeDef;

/* 校准结果(RO) */
#define MEASURE_DLINECTRL_DLINE_LEN_SHIFT	   			((uint32_t)8)
#define MEASURE_DLINECTRL_DLINE_LEN_MASK	   			((uint32_t)0x00007F00)

/* 延迟链校准值旁路使能 */
#define MEASURE_DLINECTRL_DL_CAL_BPY_DISABLE	   		((uint32_t)0)
#define MEASURE_DLINECTRL_DL_CAL_BPY_ENABLE	   			((uint32_t)1)
#define MEASURE_DLINECTRL_DL_CAL_BPY_SHIFT	   			((uint32_t)1)
#define MEASURE_DLINECTRL_DL_CAL_BPY_MASK	   			((uint32_t)0x00000002)


/* 延迟链校准值使能 */
#define MEASURE_DLINECTRL_DL_CAL_DISABLE	   			((uint32_t)0)
#define MEASURE_DLINECTRL_DL_CAL_ENABLE	   				((uint32_t)1)
#define MEASURE_DLINECTRL_DL_CAL_SHIFT	   				((uint32_t)0)
#define MEASURE_DLINECTRL_DL_CAL_MASK	   				((uint32_t)0x00000001)


/*
 *	窗口配置寄存器宏定义
 *
 */

/*  窗口配置寄存器定义  */
typedef union {
        struct {
                uint32 delayval		: 20;/* 延迟量int15.frac5 */
                uint32 gatelen		: 8;/* 窗口打开长度  */
                uint32 reserved0	: 2;/* 保留 */
                uint32 oneshot		: 1;/*发生单次hit前关闭当前窗口  */
                uint32 gatekeep		: 1;/* 窗口保持打开 */
        };
        uint32 reg;
}MeasureGate_TypeDef;





/* 窗口保持使能 */
#define MEASURE_GATE_KEPP_OPEN_DISABLE	   				((uint32_t)0)
#define MEASURE_GATE_KEPP_OPEN_ENABLE	   				((uint32_t)1)
#define MEASURE_GATE_KEPP_OPEN_SHIFT	   				((uint32_t)31)
#define MEASURE_GATE_KEPP_OPEN_MASK	   					((uint32_t)0x80000000)

/* ONE shot 模式使能 */
#define MEASURE_GATE_ONE_SHOT_DISABLE	   				((uint32_t)0)
#define MEASURE_GATE_ONE_SHOT_ENABLE	   				((uint32_t)1)
#define MEASURE_GATE_ONE_SHOT_SHIFT	   					((uint32_t)30)
#define MEASURE_GATE_ONE_SHOT_MASK	   					((uint32_t)0x40000000)

/* 窗口打开长度 */
#define MEASURE_GATE_LEN_SHIFT	   						((uint32_t)20)
#define MEASURE_GATE_LEN_MASK	   						((uint32_t)0x0FF00000)

/* 窗口打开长度 */
#define MEASURE_GATE_DELAY_VAL_SHIFT	   				((uint32_t)0)
#define MEASURE_GATE_DELAY_VAL_MASK	   					((uint32_t)0x000FFFFF)

/* 结果指针寄存器定义(RO)  */
typedef union
{
	struct{
		uint8_t Res0 ;		/* 正向测量的数据指针 */
		uint8_t Res1 ;		/* 反向测量的数据指针 */
		uint8_t St0	 ;		/* 正向测量的状态指针 */
	    uint8_t St1	 ;		/* 反向测量的状态指针 */
	}byte;
	int data;
}MeasureResPtr_TypeDef;

/* 窗口打开长度 */
#define MEASURE_RESPTR_ST1_SHIFT	   				((uint32_t)24)
#define MEASURE_RESPTR_ST1_MASK	   					((uint32_t)0xFF000000)

/* 窗口打开长度 */
#define MEASURE_RESPTR_ST0_SHIFT	   				((uint32_t)16)
#define MEASURE_RESPTR_ST0_MASK	   					((uint32_t)0x00FF0000)

/* 窗口打开长度 */
#define MEASURE_RESPTR_RES1_SHIFT	   				((uint32_t)8)
#define MEASURE_RESPTR_RES1_MASK	   				((uint32_t)0x0000FF00)

/* 窗口打开长度 */
#define MEASURE_RESPTR_RES0_SHIFT	   				((uint32_t)0)
#define MEASURE_RESPTR_RES0_MASK	   				((uint32_t)0x000000FF)








/***************************************************************************************
*   								            测量相关初始化定义								   *
***************************************************************************************/

typedef struct
{
	uint32_t PrePulse1Width;
	uint32_t PrePulse2Width;
	uint32_t PstPulse1Width;
	uint32_t PstPulse2Width;

}MeasurePulseWidth_StateTypeDef;


typedef struct
{
	uint32_t ForwardCal_C;
	uint32_t BackwardCal_C;
}MeasureTdcCal_StateTypeDef;

/**
 * @说明 测量时钟初始化定义
 */
typedef struct
{
	/* 两次测量的时间间隔置零与否设置(正常与置零)  */
	uint8_t Cycle_Zero;

	/* 巡航模式下两次温度测量的时间间隔  */
	uint8_t Cruise_Temp;

	/* 巡航模式下两次时差测量的时间间隔  */
	uint8_t Cruise_TOF;

	/* 一次往返周期内的下两次温度测量的时间间隔  */
	uint8_t Cycle_Temp;

	/* 一次往返周期内的下两次时差测量的时间间隔  */
	uint8_t Cycle_TOF;

	/* 校准陶瓷晶振的32K时钟周期数  */
	uint8_t Cal_Res_Num;

	/* 市电频率选择  */
	uint8_t Power_Hz_Sel;

	/* 高速晶振开启到开始测量的延迟  */
	uint8_t Start_Clk_HS;

	/* 测量参考时钟分频  */
	uint8_t Clk_HS_Div;

}MeasureClock_InitTypeDef;

/**
 * @说明 测量脉冲初始化定义
 */
typedef struct
{
	/* fire 发送脉冲分频系数  */
	uint8_t Fire_Div;
	/* fire 脉冲数  */
	uint8_t Fire_Num;
	/* fire 脉冲时钟反相  */
	uint8_t Fire_Inv;
	/* fire 输出选择  */
	uint8_t Fire_Sel;
	/* fire 输入选择  */
	uint8_t Stop_Sel;
	/* 预期的stop脉冲数数  */
	uint8_t Hit_Num;
	/* 忽略的stop脉冲数数  */
	uint8_t Hit_Ign_Num;
	/* 脉冲拉零阶段结束时间  */
	uint8_t Tail_End;
	/* 脉冲等待阶段结束时间  */

	uint8_t Wait_End;
	/* stop通道检测反相 */
	uint8_t Neg_Stop;

	/* 首波阈值设置  */
	uint16_t FHL;
	/* fire 脉冲相位  */
	uint16_t Fire_Phase;

}MeasurePulse_InitTypeDef;
/**
 * @说明 测量校准初始化定义
 */
typedef struct
{
	/* 是否打开自动校准 */
	uint8_t Cal_Bypass;
	/* 确定校准的算法  */
	uint8_t cal_Method;
	/* 校准的零点值 */
	uint16_t Cal_Zero;
	/* 校准环路延迟  */
	uint8_t Cal_Delay;
	/* 是否打开TDC后校准 */
	uint8_t Auto_Cal_Pst;
	/* 是否打开TDC前校准 */
	uint8_t Auto_Cal_Pre;
	/* 是否打开负沿校准模模式 */
	uint8_t Cal_Neg_Edge;

}MeasureCalibration_InitTypeDef;

/**
 * @说明 测量前端初始化定义
 */
typedef struct
{
	uint8_t V_Test_Sel	;		/* AD测量通道选择 */
	uint8_t V_Test_Dual;		/* 双向测量操作都启动AD */
	uint8_t V_Test_En;	   		/* AD测量使能 */
	uint8_t Man_Mode;	    	/* AFE内部模块手动控制 */
	uint8_t Ld_Ref;				/* LNA输入前端控制 */
	uint8_t Rx_En;				/* 接收使能 */
	uint8_t Tx_Drive;			/* 发波驱动能力控制 */
	uint8_t Rx_Pull_Down;		/* 使用发波端的RX在发波后强制下拉  */
	uint8_t Stop_Term0;			/* 接收端拉0 */
	uint8_t EOPI_En;			/* EOPI输出使能  */
	uint8_t VCMP_En;			/* VCMP输出使能 */
	uint8_t V_Test_Out;	  		/* 模拟电压1输出控制 */
	uint8_t V_Ref_Out;	   		/* 模拟电压1输出控制 */
	uint8_t Comp_Sel;			/* 比较器控制 */
	uint8_t Comp_En;	    	/* 比较器使能 */
	uint8_t Lna_Enc;			/* LNA电容反馈  */
	uint8_t Lna_En;				/* LNA使能  */
	uint8_t V_Ref_Drv;			/* VREF驱动能力控制 */
	uint8_t V_Ref_En;			/* VREF使能  */
	uint8_t V_Ref_Sel;			/* VREF选择 */
	uint8_t Dac_Ug_En;			/* DAC 单位增益放大器使能  */
	uint8_t Dac_Range;			/* DAC 范围 */
	uint8_t Dac_En;				/* DAC 使能  */

}MeasureAfe_InitTypeDef;

/**
 * @说明 测量控制初始化定义
 */
typedef struct
{
	/* 测量溢出时间选择  */
	uint8_t Time_Out_Sel;
	/* 将stop 输入充电到参考电压的时间  */
	uint8_t Time_Ref_Chrg;
	uint8_t Watch_Fire;
	/* fire 驱动能力选择 */
	uint8_t Fire_Curr;
	/* 测量模式设置操作码command */
//	uint8_t MOP;
	/* 巡航模式下方式是否对调  timing  */
	uint8_t Cru_Auto_Dir;
	/* 是否快速巡航模式  timing  */
	uint8_t Cruise_X;
	/* 波峰测量模式使能  */
	uint8_t WaveP_En;
	/* 波宽测量模式使能  */
	uint8_t WaveW_En;
	/* 首波模式使能  */
	uint8_t Auto_FW;
	/* TDC预延迟使能  */
	uint8_t Opt;//pd + pdaauto
//	/* TDC自动维护预延迟使能  */
//	uint8_t Pd_Auto_En;
	/* 窗口延迟链校准使能  */
	uint8_t Dl_Cal_En;
	/* 延迟链校准值旁路   */
	uint8_t Dl_Cal_Byp;
	/* TDC预延量*/
	uint32_t Pre_Dly_Val;

}MeasureControl_InitTypeDef;

/*  窗口配置寄存器定义  */
typedef struct
{
	uint16_t WinID;
	uint16_t DelayValCycle;
	uint8_t DelayValFrac;		/* 延迟量int15.frac5 */
	uint8_t GateLen;		 	/* 窗口打开长度  */
	uint8_t One_Shot;		 	/*发生单次hit前关闭当前窗口  */
	uint8_t Gate_Keep;		 	/* 窗口保持打开 */
}MeasureGate_InitTypeDef;

/**
 * @说明 测量初始化定义
 */
typedef struct
{
	MeasureClock_InitTypeDef Clock;
	MeasurePulse_InitTypeDef Pulse;
	MeasureAfe_InitTypeDef Afe;
	MeasureCalibration_InitTypeDef Calibration;
	MeasureControl_InitTypeDef Control;
	MeasureGate_InitTypeDef Win1;
	MeasureGate_InitTypeDef Win2;
}Measure_InitTypeDef;

/**
 * @说明 测量初始化定义
 */
typedef struct
{
	MeasurePulse_TypeDef		sonar_pulsedef;
	MeasureSonarCtrl_TypeDef	sonar_sonarctrl;
	MeasureTDCCtrl1_TypeDef		sonar_tdcctrl1;
	MeasureTDCCtrl2_TypeDef		sonar_tdcctrl2;
	MeasureCalibCtrl_TypeDef	sonar_calibctrl;
	MeasureFWaveCtrl_TypeDef	sonar_fwavectrl;
	MeasureAfeCtrl_TypeDef		sonar_afectrl;
	MeasureDLineCtrl_TypeDef	sonar_dlinectrl;
	MeasureGate_TypeDef			sonar_gate1def;
	MeasureGate_TypeDef			sonar_gate2def;
	MeasureGate_TypeDef			sonar_gate3def;
	MeasureResPtr_TypeDef		sonar_res;
}Measure_RegInitTypeDef;

typedef enum
{
	ResData0 = 0,
	ResData1 = 1,
	ResData2 = 2,
	ResData3 = 3,
	ResData4 = 4,
	ResData5 = 5,
	ResData6 = 6,
	ResData7 = 7,
	ResData8 = 8,
	ResData9 = 9,
	ResData10 = 10,
	ResData11 = 11,
	ResData12 = 12,
	ResData13 = 13,
	ResData14 = 14,
	ResData15 = 15,
	ResData16 = 16,
	ResData17 = 17,
	ResData18 = 18,
	ResData19 = 19,
	ResData20 = 20,
	ResData21 = 21,
	ResData22 = 22,
	ResData23 = 23,
	ResData24 = 24,
	ResData25 = 25,
	ResData26 = 26,
	ResData27 = 27,
	ResData28 = 28,
	ResData29 = 29,
	ResData30 = 30,
	ResData31 = 31
}MeasureResIndex_StateTypedef;

/**
 * @说明 判断是res index 范围
 */
#define IS_MEASURE_RES_INDEX(INDEX) (((INDEX) >= ResData0) && ((INDEX) <= ResData31))

typedef enum
{
	ForwardDirction = 0,
	BackwardDirction
}MeasureDirection_StateTypeDef;
/**
 * @说明 判断是Dirction 范围
 */
#define IS_MEASURE_DIRCTION(DIRCTION) (((DIRCTION) == ForwardDirction) || ((DIRCTION) == BackwardDirction))

#if 0
/* 初始化部分 line：1211，1238，1375 */
void MEASURE_ClockInit(MeasureClock_InitTypeDef *clock);
void MEASURE_PulseInit(MeasurePulse_InitTypeDef *pulse);
void MEASURE_ControlInit(MeasureControl_InitTypeDef *control);
void MEASURE_CalibrationInit(MeasureCalibration_InitTypeDef *calibration);
void MEASURE_AfeInit(MeasureAfe_InitTypeDef *afe);
void MEASURE_StructInit(Measure_InitTypeDef *Measure_InitStruct);
#endif


void MEASURE_GateWindowInit(void);
void MEASURE_DefaultInit(void);
//void MEASURE_DefaultPmuInit(void);
//void MEASURE_DefaultRegInit(void);

/* 测量处理结果数据部分 */

uint32_t MEASURE_GetStartTime(const MeasureTdcCal_StateTypeDef *cal,MeasureDirection_StateTypeDef FLAG);
uint32_t MEASURE_GetResData(const MeasureTdcCal_StateTypeDef *cal,MeasureResIndex_StateTypedef index,MeasureDirection_StateTypeDef FLAG);


ErrorStatus MEASURE_GetPulseWidth(MeasurePulseWidth_StateTypeDef *pulse_width);
ErrorStatus MEASURE_GetTdcCal(MeasureTdcCal_StateTypeDef *cal);
ErrorStatus MEASURE_GetTdcResReg(int *result);
ErrorStatus MEASURE_WriteTdcCalToReg(const MeasureTdcCal_StateTypeDef *cal);
//ErrorStatus MEASURE_ReadTdcCalToReg(MeasureTdcCal_StateTypeDef *cal);
void MEASURE_ClearTdcResReg(void);
void MEASURE_ClearTdcCalReg(void);
void MEASURE_ClearResPtrReg(void);
void MEASURE_ClearADCPtrReg(void);

/* the value return is 0x5a2c data */
uint32_t MEASURE_GetResPtrReg(void);
int GetVrefValue(void);
uint32_t MEASURE_GetAmcValue(MeasureDirection_StateTypeDef FLAG);
void MEASURE_SetResReadFlag(void);

uint32_t MEASURE_GetAutoCalculateFirRate(void);
uint32_t MEASURE_GetAutoDtofValue(const MeasureTdcCal_StateTypeDef *cal,uint32_t hit_count,uint32_t filter_count);
int MEASURE_GetManualDtofValue(const MeasureTdcCal_StateTypeDef *cal,uint32_t hit_count,uint32_t filter_count);
uint32_t MEASURE_GetDtofConvertPsValue(uint32_t avg_dtof,uint32_t time_Unit);


/* 测量状态分析控制部分 */
ErrorStatus MEASURE_ExpectResPtr(void);
void MEASURE_SetCruiseMode(uint32_t mode);
void MEASURE_SetWatchDog(FunctionalState state);
void MEASURE_SetCruiseTOF(uint32_t time);
void MEASURE_SetCruiseXMode(FunctionalState state);
void MEASURE_SetCruiseAutoDirection(FunctionalState state);
void MEASURE_SetFireSel(uint32_t channel);
void MEASURE_SetStopSel(uint32_t channel);
void MEASURE_SetMannualDirectionReverse(void);
ErrorStatus  MEASURE_SetPulseWaveFireNum(uint32_t count);
void MEASURE_SetPulseWavePeakMode(FunctionalState state);
FlagStatus MEASURE_GetPulseWavePeakMode(void);
void MEASURE_SetPulseWaveWideMode(FunctionalState state);
FlagStatus MEASURE_GetPulseWaveWideMode(void);
void MEASURE_SetFirstPulseWaveMode(FunctionalState state);
ErrorStatus  MEASURE_SetPulseFirstWaveThreshold(uint32_t threshold);
ErrorStatus  MEASURE_SetPulseWaveHitNum(uint32_t count);
uint32_t MEASURE_GetPulseWaveHitNum(void);

ErrorStatus  MEASURE_SetPulseWaveTailEnd(uint32_t count);
ErrorStatus  MEASURE_SetPulseWaveWaitEnd(uint32_t count);

ErrorStatus  MEASURE_SetPulseWaveHitIgnNum(uint32_t count);
void  MEASURE_SetAutoCalculateMode(FunctionalState state);
ErrorStatus  MEASURE_SetAutoCalculateHitNum(uint32_t count);
ErrorStatus  MEASURE_SetAutoCalculateFltRate(uint32_t count);

void MEASURE_SetTdcAutoCalPre(FunctionalState state);
FlagStatus MEASURE_GetTdcAutoCalPre(void);
void MEASURE_SetTdcAutoCalPst(FunctionalState state);
FlagStatus MEASURE_GetTdcAutoCalPst(void);

#if 0
void MEASURE_SetTdcOpt(uint32_t option);
void MEASURE_SetTdcDbgRemapMode(FunctionalState state);
void MEASURE_SetTdcDbg1Mode(uint32_t mode);
void MEASURE_SetTdcDbg0Mode(uint32_t mode);
ErrorStatus MEASURE_SetTdcPreDelayIncrement(uint32 inc);
ErrorStatus MEASURE_SetTdcPreDelayValue(uint32 value);
#endif

void MEASURE_TdcSetWindow(MeasureGate_InitTypeDef *gate);

void MEASURE_SetAfeVtestSel(uint32_t channel);
void MEASURE_SetAfeVtestDual(FunctionalState state);
void MEASURE_SetAfeVtest(FunctionalState state);
void MEASURE_SetAfeVtestOut(uint32_t mode);
void MEASURE_SetAfeVRefOut(FunctionalState state);
void MEASURE_SetAfeVRefSel(uint32_t mode);
void MEASURE_SetAfeVRef(FunctionalState state);
void MEASURE_SetAfeVRefDrive(uint32_t mode);


/* 旁路校准函数接口 */
uint32_t MEASURE_GetCalibrationZeroValue(void);
ErrorStatus MEASURE_SetCalibrationZeroValue(uint32 value);
void  MEASURE_SetCalBypass(FunctionalState state);
ErrorStatus MEASURE_SetCalibrationDelayValue(uint32 value);
ErrorStatus MEASURE_SetCalibrationMethod(uint32 value);


#if 0
void MEASURE_SetAfeCompare(FunctionalState state);
void MEASURE_SetAfeCompareSel(uint32_t mode);
void MEASURE_SetAfeLna(FunctionalState state);
void MEASURE_SetAfeLnaRef(FunctionalState state);
void MEASURE_SetAfeLnaEac(FunctionalState state);
void MEASURE_SetAfeRx(FunctionalState state);
void MEASURE_SetAfeStopTerm0(FunctionalState state);
void MEASURE_SetAfeRxPullDown(uint32_t mode);
void MEASURE_SetAfeTxDrive(uint32_t mode);
void MEASURE_SetAfeDac(FunctionalState state);
void MEASURE_SetAfeDacRange(FunctionalState state);
void MEASURE_SetAfeDacUg(uint32_t mode);
#endif


/* 启动测量部分 */
void MEASURE_StartTask(void);
void MEASURE_SetTask(uint32_t task);
void MEASURE_SetTaskToStart(uint32_t task);
/* 此函数功能待确定，北京反馈不可以	*/
void MEASURE_StopTask(void);
void MEASURE_SuspendTask(void);
void MEASURE_SleepTask(void);
void MEASURE_ExitCruiseTask(void);
FlagStatus MEASURE_CanCpuSleep(void);

/* 中断部分 */
ITStatus MEASURE_GetITStatus(uint32_t MEASURE_IT_FLAG);
void MEASURE_ITConfig(uint32_t MEASURE_IT_FLAG,FunctionalState NewState);
void MEASURE_ClearIT(uint32_t MEASURE_IT_FLAG);
void MEASURE_ClearITPendingBit(uint32_t MEASURE_IT_FLAG);
/* 此函数复合功能 */
void MEASURE_ClearResITAndReadFlag(void);

/* 温度测量的封装函数 待测 */
uint32_t MEASURE_GetTemperaturePortDirection(void);
#if 0
void MEASURE_SetTemperatureFakeNum(uint32_t number);
uint32_t MEASURE_GetTemperatureFakeNum(void);

void MEASURE_SetTemperaturePortNum(uint32_t number);
uint32_t MEASURE_GetTemperaturePortNum(void);

void MEASURE_SetTemperaturePortDirection(FlagStatus flag);
uint32_t MEASURE_GetTemperaturePortDirection(void);

void MEASURE_SetTemperatureTimeLoad(uint32_t number);
uint32_t MEASURE_GetTemperatureTimeLoad(void);

void MEASURE_SetTemperatureTimeUnload(uint32_t number);
uint32_t MEASURE_GetTemperatureTimeUnload(void);

void MEASURE_SetTemperatureFastMode(FunctionalState state );
uint32_t MEASURE_GetTemperatureFastMode(void);
#endif

int iabs(int i);
#endif /* INCLUDE_MEASURE_H_ */





