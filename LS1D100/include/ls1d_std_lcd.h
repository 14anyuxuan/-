/********************************************************************
* 文件名:  ls1d_std_lcd.h
* 版本：	  V1.0
* 作者:    白一方、李鑫
* 日期:    2021.12.18
* 说明:    本文件包含lcd的底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef INCLUDE_LCD_H_
#define INCLUDE_LCD_H_


#include "ls1d.h"
#include "ls1d_std_cslreg.h"
#include "ls1d_std_printf.h"

#define  LCD_SET(A) (g_FBn_Buff[(A>>3)] |= (1<<(A&0x7)))
#define  LCD_CLR(A) (g_FBn_Buff[(A>>3)] &= ~(1<<(A&0x7)))

#define  LCD_SEG7_NUMS         8   //7段码的个数
#define  LCD_POSITIVE_MAX_NUM    99999999   //可显示最大整数
#define  LCD_NEGATIVE_MAX_NUM    9999999   //可显示最大整数  LCD_SET(LCD_Cubic);
#define  LCD_DOT_NUMS          7   //小数位数
#define  DOT_NUM_TURBOLIULIANG      5   //流量、累积等小数点位数
#define  DOT_NUM_LIULIANG      3   //流量、累积等小数点位数
#define  NO_DOT_NUM      	   0   //流量、累积等小数点位数
#define  DOT_NUM_FACTOR        4   //流量、累积等小数点位数
#define  DOT_NUM_TEMP      	   1   //温度小数点位数
/*7段码led各led对应位定义
*A:顶部“-”；B:右上“|”；C:右下“|”；D:底部"-";
*E:左下“|”；F:左上“|”；G:中间“-”；
*/
typedef struct SEG7
{
    uint8_t A;/* 8段码中A的位置，单位bit */
    uint8_t B;/* 8段码中B的位置，单位bit */
    uint8_t C;/* 8段码中C的位置，单位bit */
    uint8_t D;/* 8段码中D的位置，单位bit */
    uint8_t E;/* 8段码中E的位置，单位bit */
    uint8_t F;/* 8段码中F的位置，单位bit */
    uint8_t G;/* 8段码中G的位置，单位bit */
//    uint8_t RESERVED0;/* 8段码中dot的位置，保留位 */
}seg7;

#ifdef OLD_LCD
/*段码屏其他固定显示对应位置*/
#define LCD_SHIJIAN     0      //"时间"
#define LCD_FENDUAN     16      //"分段"来代替流速的识别码
#define LCD_GUZHANG     17      //"故障"
#define LCD_KAI         18      //"开"
#define LCD_GUAN        19      //"关"

#define LCD_QINGCHONGZHI    52      //"请充值"
#define LCD_LEIJI           53      //"累积"
#define LCD_QUEDIAN         54      //缺电图标
#define LCD_YICHONGZHI      55      //"已充值"

#define LCD_YUAN        64      //"元"

#define LCD_BENQI     72     //"本期"
#define LCD_SHENGYU   73      //"剩余"
#define LCD_DANJIA    74      //"单价"
#define LCD_LIFANGMI  75      //"m³

#else

/*段码屏其他固定显示对应位置*/

//#define LCD_Alarm     		86      //"报警"
//#define LCD_Verification    83      //"检定"
//#define LCD_Total       	67      //"累积"
//#define LCD_Current     	64      //"流量"
////#define LCD_Transducer  	72    //"换能器"
//#define LCD_Time     		87      //"时间"
//#define LCD_LowPower        79      //缺电图标
//#define LCD_Degree        	74      //"℃"
//#define LCD_Cubic   		72      //"m³
//#define LCD_QuaqueHour  	76      // /h
//#define LCD_Spot 			78      //  。
//#define LCD_Hour  			77      //  H
//#define LCD_KW  			63      //  KW
//#define LCD_GJ  			73      //  GJ
//#define LCD_K  				75      //  K
//#define LCD_Power  			71      //  功率
//#define LCD_Temperature   	70      //  温度
//#define LCD_BackwardWater   69	    //  回水
//#define LCD_ForwardWater   	68      //  进水
//#define LCD_ColdTotal   	65      //  进水
//#define LCD_HotTotal   	    66      //  进水
//#define LCD_CloseValve   	85      //  进水
//#define LCD_OpenValve   	84      //  进水
//#define LCD_Charge  	    80      //  进水
//#define LCD_Residual 	    81      //  进水
//#define LCD_Purchase  	    82      //  买入


#define LCD_Alarm     		85      //"报警"
#define LCD_Verification    80      //"检定"
#define LCD_Total       	64      //"累积"
#define LCD_Current     	67      //"流量"
//#define LCD_Transducer  	72    //"换能器"
#define LCD_Time     		84      //"时间"


#define LCD_LowPower        76      //缺电图标
#define LCD_Degree        	73      //"℃"
#define LCD_Cubic   		75      //"m³
#define LCD_QuaqueHour  	79      // /h
#define LCD_Spot 			77      //  。
#define LCD_Hour  			78      //  H
#define LCD_KW  			60      //  KW
#define LCD_GJ  			74      //  GJ
#define LCD_K  				72      //  K
#define LCD_Power  			68      //  功率
#define LCD_Temperature   	69      //  温度
#define LCD_BackwardWater   70	    //  回水
#define LCD_ForwardWater   	71      //  进水
#define LCD_ColdTotal   	66      //  进水
#define LCD_HotTotal   	    65      //  进水
#define LCD_CloseValve   	86      //  进水
#define LCD_OpenValve   	87      //  进水
#define LCD_Charge  	    83      //  进水
#define LCD_Residual 	    82      //  进水
#define LCD_Purchase  	    81      //  买入

#endif


//#define  LCD_DOT_NUMS          5   //小数位数
//#define LCD_Alarm     		0      //"报警"
//#define LCD_Verification    4      //"检定"
//#define LCD_Total       	12      //"累积"
//#define LCD_Current     	20      //"瞬时"
//#define LCD_Transducer  	1    //"换能器"
//
//#define LCD_Time     		52      //"时间"
//#define LCD_MeterNumber     53      //"表号"
//#define LCD_Signal      	54      //"信号"
//#define LCD_EmptyPipe    	2      //"空管"
//#define LCD_NotFullPipe  	3      //"非满管"
//#define LCD_LowPower        72      //缺电图标
//#define LCD_Degree        	73      //"℃"
//#define LCD_Cubic   		74      //"m³
//#define LCD_CubicHour  		75      //"m³/h



/**
 * @说明  段码显示设置宏定义
 */
#if 0

#define LCD0    (1<<0)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<2)
#define LCD1    (1<<0)|(1<<2)
#define LCD2    (1<<4)|(1<<0)|(1<<1)|(1<<6)|(1<<7)
#define LCD3    (1<<4)|(1<<0)|(1<<1)|(1<<2)|(1<<7)
#define LCD4    (1<<5)|(1<<1)|(1<<0)|(1<<2)
#define LCD5    (1<<4)|(1<<5)|(1<<1)|(1<<2)|(1<<7)
#define LCD6    (1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<2)|(1<<1)
#define LCD7    (1<<4)|(1<<0)|(1<<2)
#define LCD8    (1<<0)|(1<<4)|(1<<5)|(1<<1)|(1<<2)|(1<<7)|(1<<6)
#define LCD9    (1<<0)|(1<<4)|(1<<5)|(1<<1)|(1<<2)|(1<<7)
#define LCDp    (1<<3)

#define LCDA    (1<<6)|(1<<5)|(1<<4)|(1<<0)|(1<<1)|(1<<2)   //119
#define LCDB    (1<<5)|(1<<6)|(1<<1)|(1<<2)|(1<<7)
// #define LCDC    (1<<1)|(1<<6)|(1<<7)
#define LCDC    240
// #define LCDD    (1<<0)|(1<<2)|(1<<1)|(1<<6)|(1<<7)
#define LCDD    (1<<0)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<2)
#define LCDE    (1<<4)|(1<<5)|(1<<1)|(1<<6)|(1<<7)
#define LCDF    (1<<4)|(1<<5)|(1<<6)|(1<<1)
#define LCDG    (1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<2)
#define LCDH    (1<<5)|(1<<6)|(1<<1)|(1<<0)|(1<<2)
#define LCDI    (1<<2)
#define LCDJ    (1<<0)|(1<<2)|(1<<7)
#define LCDL    (1<<5)|(1<<6)|(1<<7)
#define LCDN    (1<<6)|(1<<1)|(1<<2)
#define LCDO    (1<<1)|(1<<6)|(1<<7)|(1<<2)
#define LCDP    (1<<5)|(1<<6)|(1<<4)|(1<<0)|(1<<1)
#define LCDQ    (1<<4)|(1<<5)|(1<<1)|(1<<0)|(1<<2)
#define LCDR    (1<<6)|(1<<1)
#define LCDS    (1<<4)|(1<<5)|(1<<1)|(1<<7)
#define LCDT    (1<<5)|(1<<6)|(1<<7)|(1<<1)
#define LCDU    (1<<6)|(1<<7)|(1<<2)
#define LCDX    (1<<4)|(1<<1)|(1<<7)
#define LCDY    (1<<5)|(1<<1)|(1<<0)|(1<<2)|(1<<7)
#define LCDMINUS   (1<<1)
#define LCDDOT     (1<<3)

#endif
/**
 * @说明  PMU寄存器中LCD相关寄存器设置位定义
 */
#define PMU_CHIPCTRL_LCDGPIO    (0x1F<<10)

/**
 * @说明  显示类型定义
 */
// #define  DIS_NUM    0       //数字类类显示
// #define  DIS_ASC    1       //字符类类显示
// #define  DIS_INIT   2       //初始化显示
// #define  DIS_CLS    3       //清屏显示


// #define  DIS_BIT0    0 
// #define  DIS_BIT1    1 
// #define  DIS_BIT2    2 
// #define  DIS_BIT3    3 
// #define  DIS_BIT4    4 
// #define  DIS_BIT5    5 
// #define  DIS_BIT6    6
// #define  DIS_BIT7    7
// #define  DIS_BIT8    8
// #define  DIS_BIT9    9 
// #define  DIS_BIT10   10 
// #define  DIS_BIT11   11 


#define  DELAY_TIME  50
/**
 * LCD 变量声明
 */
extern uint8_t g_FBn_Buff[12];
/*段码屏中7段码数字对应位置*/
extern const seg7 g_seg_num[8];
/*段码屏中各小数点对应位置*/
extern const uint8_t g_seg_dot[7];



#if 0
uint8_t LCD_Conver_Num(uint8_t num, uint8_t dot);
void LCD_Disp_Num(char num,uint32_t FBn,uint8_t FBbn);
int LCD_Disp_Nums_S(uint8_t* numbuf,uint32_t FBn,uint8_t FBbn,uint8_t size_n);
void LCD_Disp_Nums_A(uint8_t* numbuf,uint8_t size_n);

uint8_t LCD_Conver_Asc(uint8_t chr);
void LCD_Disp_Asc(char num,uint32_t FBn,uint8_t FBbn);
int LCD_Disp_Ascs_S(uint8_t* numbuf,uint32_t FBn,uint8_t FBbn,uint8_t size_n);
void LCD_Disp_Ascs_A(uint8_t* numbuf,uint8_t size_n);

int LCD_Disp_Float (uint32_t FBn, uint32_t num, uint32_t frac);

void LCD_Package_Dat(uint8_t dat,uint8_t *buf,uint8_t distype,uint8_t disbn);
void LCD_Disp(uint8_t *buf);
#endif

#if 0
uint8_t LCD_Conver_Num(uint8_t num);
uint8_t LCD_Conver_Asc(uint8_t chr);

void Num2LcdNum(uint32_t num,uint8_t *buf,uint8_t start_n,uint8_t max_n);
void Asc2LcdAsc(uint8_t datc,uint8_t disbn,uint8_t *buf);


void LCD_Dis_Nums(uint32_t *datbuf,uint8_t size_n,uint8_t start_n,uint8_t max_n);
void LCD_Dis_Floats(uint32_t *datbuf,uint8_t size_n,uint32_t frac,uint8_t start_n,uint8_t max_n);

void LCD_Dis_Ascs(uint8_t *datbuf,uint8_t size_n,uint8_t start_n,uint8_t end_n);
#endif

//===============================================//
void LCD_NumCls(const seg7* lcd7);
void LCD_Num0(const seg7* lcd7);
void LCD_Num1(const seg7* lcd7);
void LCD_Num2(const seg7* lcd7);
void LCD_Num3(const seg7* lcd7);
void LCD_Num4(const seg7* lcd7);
void LCD_Num5(const seg7* lcd7);
void LCD_Num6(const seg7* lcd7);
void LCD_Num7(const seg7* lcd7);
void LCD_Num8(const seg7* lcd7);
void LCD_Num9(const seg7* lcd7);

//void LCD_StrC(const seg7* lcd7);
void LCD_StrE(const seg7* lcd7);
void LCD_StrO(const seg7* lcd7);
void LCD_StrF(const seg7* lcd7);
void LCD_StrN(const seg7* lcd7);
void LCD_StrH(const seg7* lcd7);

void LCD_MaoHao(const seg7* lcd7);
void LCD_JianHao(const seg7* lcd7);

void LCD_Dot(uint8_t dot);
void LCD_Conver_Num(uint8_t num,const seg7* lcd7);
void LCD_Conver_Symbol(uint8_t num,const seg7* lcd7);
void Num2LcdNum(int num,uint8_t dotnum);

void LCD_Disp(void);
void LCD_Dis_Init(void);
void LCD_Dis_Cls(void);
void LCD_Init(uint32_t refresh_rate);


#endif
