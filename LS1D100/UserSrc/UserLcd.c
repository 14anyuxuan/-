/*
 * UserLcd.c
 *
 *  Created on: 2021��11��29��
 *      Author: Administrator
 */

#include "UserLcd.h"


//#define LCD_ON()		   {GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_0,Bit_SET);\
//							GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_1,Bit_SET);\
//							GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_2,Bit_SET);\
//							CLOCK_DelayMs(1);\
//							CLEAR_BIT(CHIPCTRL, PMU_CHIPCTRL_LCDGPIO);\
//							WRITE_REG(LCD->RFR, 5);}
//
//#define LCD_OFF()	       {LCD_Dis_Cls();\
//							CLOCK_DelayMs(1);\
//							GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_0,Bit_RESET);\
//							GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_1,Bit_RESET);\
//							GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_2,Bit_RESET);}

void LCD_Init(uint32_t refresh_rate)
{


    CLEAR_BIT(CHIPCTRL, PMU_CHIPCTRL_LCDGPIO);
    WRITE_REG(LCD->RFR, refresh_rate);

    LCD_Dis_Init();
    CLOCK_DelayMs(1000);

    LCD_Dis_Cls();
    CLOCK_DelayMs(100);

}




#ifdef OLD_LCD
/**
 * @Description: ��������
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param {uint32_t} num ����ֵ��ʵ��ֵ��1000���������ʾת��Ϊ��3λС�������֣�
 */
void Screen_LiuLiang(uint32_t num)
{
    LCD_Dis_Cls();

    Num2LcdNum(num,DOT_NUM_LIULIANG);

#ifdef OLD_LCD
    LCD_SET(LCD_LIFANGMI);
    LCD_SET(LCD_FENDUAN);
#else
    LCD_SET(LCD_Current);
    LCD_SET(LCD_CubicHour);
#endif
    LCD_Disp();
}
#endif


/**
 * @Description: �ۻ���������
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param {uint32_t} num �ۻ�����ֵ��ʵ��ֵ��1000���������ʾת��Ϊ��3λС�������֣�
 */
void Screen_TotalCubic(uint32_t num)
{
    LCD_Dis_Cls();
    Num2LcdNum(num,DOT_NUM_LIULIANG);

#ifdef OLD_LCD
    LCD_SET(LCD_LIFANGMI);
    LCD_SET(LCD_LEIJI);
#else
    LCD_SET(LCD_Total);
    LCD_SET(LCD_Cubic);
#endif

    LCD_Disp();
}


#ifdef OLD_LCD
/**
 * @Description: ʣ����������
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param {uint32_t} num ʣ������ֵ��ʵ��ֵ��1000���������ʾת��Ϊ��3λС�������֣�
 */
void Screen_ShengYu(uint32_t num)
{


	LCD_Dis_Cls();

    Num2LcdNum(num,DOT_NUM_LIULIANG);

    LCD_SET(LCD_LIFANGMI);
    LCD_SET(LCD_SHENGYU);

    LCD_Disp();


}

#endif
/**
 * @Description: ��Ž���
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param {uint32_t} num  ��ʾ��ĺ���
 */
void Screen_MeterNummber(uint8_t *buf)
{
//    LCD_Dis_Cls();
//    Num2LcdNum(num,NO_DOT_NUM);
//    LCD_SET(LCD_MeterNumber);
//    LCD_Disp();

    uint8_t tmp=0;
    int i  = 0;
    LCD_Dis_Cls();
    for(i=0;i < 8;i++)
    {
    	 tmp = buf[i]%10;
    	 LCD_Conver_Num(tmp,&g_seg_num[7 - i]);   //�������ʾ����
    }
//    LCD_SET(LCD_MeterNumber);

    LCD_Disp();
}

/**
 * @Description: �źŽ���
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param {uint32_t} num  ��ʾ�ź�������
 */
void Screen_Signal(uint32_t num)
{
    LCD_Dis_Cls();

//    LCD_SET(LCD_Signal);
    if(1)
    {
    	LCD_Conver_Symbol('O',&g_seg_num[0]);
    	LCD_Conver_Symbol('F',&g_seg_num[1]);
    	LCD_Conver_Symbol('F',&g_seg_num[2]);
    	Num2LcdNum(99,NO_DOT_NUM);
    }else{
    	LCD_Conver_Symbol('O',&g_seg_num[0]);
    	LCD_Conver_Symbol('N',&g_seg_num[1]);
    	Num2LcdNum(num,NO_DOT_NUM);
    }
    LCD_Disp();
}


/**
 * @Description: ��ص�������
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param {uint32_t} num  ��ص���������
 */
void Screen_BatteryPower(uint32_t num)
{
    LCD_Dis_Cls();
    Num2LcdNum(num,NO_DOT_NUM);
    LCD_SET(LCD_LowPower);
    LCD_Disp();
}

/**
 * @Description: ��ص�������
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param {uint32_t} num  ��ص���������
 */
void Screen_Temperature(uint32_t num)
{
    LCD_Dis_Cls();
    Num2LcdNum(num,DOT_NUM_TEMP);
    LCD_SET(LCD_Degree);
    LCD_SET(LCD_Temperature);
    LCD_Disp();
}
/**
 * @Description: ʣ�����ٽ���
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param {uint32_t} num ����ֵ��ʵ��ֵ��1000���������ʾת��Ϊ��3λС�������֣�
 */
void Screen_FlowSpeed(int num)
{
    LCD_Dis_Cls();
    Num2LcdNum(num,DOT_NUM_LIULIANG);
#ifdef OLD_LCD
    LCD_SET(LCD_LIFANGMI);
    LCD_SET(LCD_FENDUAN);
#else
    LCD_SET(LCD_Current);
//    LCD_SET(LCD_CubicHour);
    LCD_SET(LCD_Cubic);
    LCD_SET(LCD_QuaqueHour);
#endif

    LCD_Disp();
}

/**
 * @Description: ʵ�ʽ��� ��ʾ��ʽ ��-��-��
 * @Input: �������ݻ��� 16�������ݸ�ʽ
 * @Output: ��
 * @return {*}��
 * @param {uint8_t} *buf �������ݻ��� �գ�buf[0];�£�buf[1];�꣺buf[2]��
 */
void Screen_Time(uint8_t *buf)
{
    uint8_t tmp=0;

    LCD_Dis_Cls();

    tmp = buf[0]%10;
    LCD_Conver_Num(tmp,&g_seg_num[7]);   //���� ��

    tmp = buf[0]/10;
    tmp = tmp>9?(tmp%10):tmp;
    LCD_Conver_Num(tmp,&g_seg_num[6]);
    LCD_Conver_Symbol('-',&g_seg_num[5]);  //"-"

    tmp = buf[1]%10;
    LCD_Conver_Num(tmp,&g_seg_num[4]);   //���� ��
    tmp = buf[1]/10;
    tmp = tmp>9?(tmp%10):tmp;
    LCD_Conver_Num(tmp,&g_seg_num[3]);
    LCD_Conver_Symbol('-',&g_seg_num[2]);  //"-"

    tmp = buf[2]%10;
    LCD_Conver_Num(tmp,&g_seg_num[1]);   //���� ��
    tmp = buf[2]/10;
    tmp = tmp>9?(tmp%10):tmp;
    LCD_Conver_Num(tmp,&g_seg_num[0]);

    LCD_SET(LCD_Time);

    LCD_Disp();
}

#ifdef OLD_LCD
/**
 * @Description: ʣ����
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param {uint32_t} num ʣ������ֵ��ʵ��ֵ��1000���������ʾת��Ϊ��3λС�������֣�
 */
void Screen_Money(uint32_t num)
{
    LCD_Dis_Cls();

    Num2LcdNum(num,DOT_NUM_LIULIANG);

    LCD_SET(LCD_YUAN);
    LCD_SET(LCD_BENQI);
    LCD_SET(LCD_SHENGYU);

    LCD_Disp();
}
#endif
/**
 * @Description: �춨ģʽ����ʾ�ۻ��������
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param {uint32_t} num �ۻ�����ֵ��ʵ��ֵ��100000���������ʾת��Ϊ��5λС�������֣�
 */
void Screen_VerificationTotalCubic(uint32_t num)
{
    LCD_Dis_Cls();
    Num2LcdNum(num,DOT_NUM_TURBOLIULIANG);

    LCD_SET(LCD_Verification);
    LCD_SET(LCD_Total);
    LCD_SET(LCD_Cubic);
    LCD_Disp();
}



/**
 * @Description:����
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param ��
 */
void Screen_ExValueOpen(void)
{
    LCD_SET(LCD_OpenValve);
    LCD_Disp();
}

/**
 * @Description: ����
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param ��
 */
void Screen_ExValueClose()
{
    LCD_SET(LCD_CloseValve);
    LCD_Disp();
}


///**
// * @Description: ������
// * @Input: ��
// * @Output: ��
// * @return {*}
// * @param ��
// */
//void Screen_ExNotFullPipe()
//{
//    LCD_SET(LCD_NotFullPipe);
//    LCD_Disp();
//}


/**
 * @Description: ��ʾ�޵��־����
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param ��
 */
void Screen_ExLowPower(void)
{
    LCD_SET(LCD_LowPower);
    LCD_Disp();
}

void Screen_ForwardWater(void)
{
    LCD_SET(LCD_ForwardWater);
    LCD_Disp();
}
void Screen_BackwardWater(void)
{
    LCD_SET(LCD_BackwardWater);
    LCD_Disp();
}

void Screen_ExVerificationMode(void)
{
    LCD_SET(LCD_Verification);
    LCD_SET(LCD_Cubic);
    LCD_Disp();
}

#if OLD_LCD
/**
 * @Description: ���ֵ��ֵ
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param ��
 */
void Screen_exNeedCharge(void)
{
    LCD_SET(LCD_QINGCHONGZHI);
    LCD_Disp();
}

/**
 * @Description: ���ֵ��ֵ
 * @Input: ��
 * @Output: ��
 * @return {*}
 * @param ��
 */
void Screen_exFinishCharge(void)
{
    LCD_SET(LCD_YICHONGZHI);
    LCD_Disp();
}

#endif

void Screen_ParameterInfo(void)
{
    LCD_Dis_Cls();
	LCD_Conver_Symbol('[',&g_seg_num[2]);
	LCD_Conver_Symbol('P',&g_seg_num[4]);
	LCD_Conver_Symbol(']',&g_seg_num[6]);
	LCD_Disp();
}

void Screen_HistoryInfo(void)
{
    LCD_Dis_Cls();
	LCD_Conver_Symbol('[',&g_seg_num[2]);
	LCD_Conver_Symbol('H',&g_seg_num[4]);
	LCD_Conver_Symbol(']',&g_seg_num[6]);
	LCD_Disp();
}

void Screen_SystemStateInfo(void)
{
    LCD_Dis_Cls();
	LCD_Conver_Symbol('[',&g_seg_num[2]);
	LCD_Conver_Symbol('S',&g_seg_num[4]);
	LCD_Conver_Symbol(']',&g_seg_num[6]);
	LCD_Disp();
}
void Screen_ErrorInfo(void)
{
    LCD_Dis_Cls();
	LCD_Conver_Symbol('[',&g_seg_num[2]);
	LCD_Conver_Symbol('E',&g_seg_num[4]);
	LCD_Conver_Symbol(']',&g_seg_num[6]);
	LCD_Disp();
}

void Screen_GoBack(void)
{
    LCD_Dis_Cls();
	LCD_Conver_Symbol('[',&g_seg_num[2]);
	LCD_Conver_Symbol('B',&g_seg_num[4]);
	LCD_Conver_Symbol(']',&g_seg_num[6]);
	LCD_Disp();
}

void Screen_SoftReset(void)
{
    LCD_Dis_Cls();
	LCD_Conver_Symbol('R',&g_seg_num[1]);
	LCD_Conver_Symbol('E',&g_seg_num[2]);
	LCD_Conver_Symbol('B',&g_seg_num[3]);
	LCD_Conver_Symbol('O',&g_seg_num[4]);
	LCD_Conver_Symbol('O',&g_seg_num[5]);
	LCD_Conver_Symbol('T',&g_seg_num[6]);
	LCD_Disp();
}

void Screen_ClearCapacity(uint32_t flag)
{
    LCD_Dis_Cls();
	LCD_Conver_Symbol('[',&g_seg_num[0]);
	LCD_Conver_Symbol('L',&g_seg_num[1]);
	LCD_Conver_Symbol('R',&g_seg_num[2]);
	LCD_Conver_Symbol('-',&g_seg_num[3]);
    if(!flag)
    {
    	LCD_Conver_Symbol('O',&g_seg_num[5]);
    	LCD_Conver_Symbol('F',&g_seg_num[6]);
    	LCD_Conver_Symbol('F',&g_seg_num[7]);
    }else{
    	LCD_Conver_Symbol('O',&g_seg_num[6]);
    	LCD_Conver_Symbol('N',&g_seg_num[7]);
    }

	LCD_Disp();
}
void Screen_TotalTime(uint32_t num)
{
    LCD_Dis_Cls();
    Num2LcdNum(num,NO_DOT_NUM);
    LCD_Disp();
}
