/********************************************************************
* 文件名:  ls1d6_std_lcd.c
* 版本：	  V1.0
* 作者:    白一方、李鑫
* 日期:    2021.08.31
* 说明:    本文件包含lcd的所有接口函数及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#include "../include/ls1d_std_lcd.h"

/*段码屏中7段码数字对应位置*/
# if 1



const seg7 g_seg_num[8]={
    {7, 6, 5, 0, 1, 3, 2},        //1A 1B 1C 1D 1E 1F 1G
    {15,14,13,8,9,11,10},        //2A 2B 2C 2D 2E 2F 2G
    {23,22,21,16,17,19,18},       //3A 3B 3C 3D 3E 3F 3G
    {31,30,29,24,25,27,26},       //4A 4B 4C 4D 4E 4F 4G
    {39,38,37,32,33,35,34},       //5A 5B 5C 5D 5E 5F 5G
    {47,46,45,40,41,43,42},       //6A 6B 6C 6D 6E 6F 6G
    {55,54,53,48,49,51,50},       //7A 7B 7C 7D 7E 7F 7G
    {63,62,61,56,57,59,58}        //8A 8B 8C 8D 8E 8F 8G
};

/*段码屏中各小数点对应位置*/
const uint8_t g_seg_dot[7]={
	52,     //DP7
	44,     //DP6
	36,     //DP5
    28,     //DP4
    20,     //DP3
    12,     //DP2
    4     //DP1
    };
#else

const seg7 g_seg_num[8]={
    {8, 9, 10,11, 7, 5, 6},       //1A 1B 1C 1D 1E 1F 1G null
    {16,17,18,19,15,13,14},       //2A 2B 2C 2D 2E 2F 2G null
    {24,25,26,27,23,21,22},       //3A 3B 3C 3D 3E 3F 3G DP1
    {32,33,34,35,31,29,30},       //4A 4B 4C 4D 4E 4F 4G DP2
    {40,41,42,43,39,37,38},       //5A 5B 5C 5D 5E 5F 5G DP3
    {48,49,50,51,47,45,46},       //6A 6B 6C 6D 6E 6F 6G DP4
    {60,61,62,63,59,57,58},       //7A 7B 7C 7D 7E 7F 7G DP5
    {68,69,70,71,67,65,66}        //8A 8B 8C 8D 8E 8F 8G null
};

/*段码屏中各小数点对应位置*/
const uint8_t g_seg_dot[5]={
    64,     //DP5
    56,     //DP4
    44,     //DP3
    36,     //DP2
    28     //DP1
    };
#endif
/**
 * @Description: 全局变量定义
 **/
uint8_t g_FBn_Buff[12];


/**
 * @Description: 段码位置清屏
 * @Input: 段码位置
 * @Output: 无
 * @return {*}
 * @param {seg7*} lcd7 段码位置
 */
void LCD_NumCls(const seg7* lcd7)
{
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);    
}

/**
 * @Description: 段码位置显示 0
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_Num0(const seg7* lcd7)
{
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);
    
    LCD_SET(lcd7->A);
    LCD_SET(lcd7->B);
    LCD_SET(lcd7->C);
    LCD_SET(lcd7->D);
    LCD_SET(lcd7->E);
    LCD_SET(lcd7->F);
    // LCD_SET(lcd7->G);
}

/**
 * @Description: 段码位置显示 1
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_Num1(const seg7* lcd7)
{
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);

    // LCD_SET(lcd7->E);
    // LCD_SET(lcd7->F);

    LCD_SET(lcd7->B);
    LCD_SET(lcd7->C);
}

/**
 * @Description: 段码位置显示 2
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_Num2(const seg7* lcd7)
{
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);
    
    LCD_SET(lcd7->A);
    LCD_SET(lcd7->B);
    // LCD_SET(lcd7->C);
    LCD_SET(lcd7->D);
    LCD_SET(lcd7->E);
    // LCD_SET(lcd7->F);
    LCD_SET(lcd7->G);
}

/**
 * @Description: 段码位置显示 3
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_Num3(const seg7* lcd7)
{
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);
    
    LCD_SET(lcd7->A);
    LCD_SET(lcd7->B);
    LCD_SET(lcd7->C);
    LCD_SET(lcd7->D);
    // LCD_SET(lcd7->E);
    // LCD_SET(lcd7->F);
    LCD_SET(lcd7->G);
}

/**
 * @Description: 段码位置显示 4
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_Num4(const seg7* lcd7)
{
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);
    
    // LCD_SET(lcd7->A);
    LCD_SET(lcd7->B);
    LCD_SET(lcd7->C);
    // LCD_SET(lcd7->D);
    // LCD_SET(lcd7->E);
    LCD_SET(lcd7->F);
    LCD_SET(lcd7->G);
}

/**
 * @Description: 段码位置显示 5
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_Num5(const seg7* lcd7)
{
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);
    
    LCD_SET(lcd7->A);
    // LCD_SET(lcd7->B);
    LCD_SET(lcd7->C);
    LCD_SET(lcd7->D);
    // LCD_SET(lcd7->E);
    LCD_SET(lcd7->F);
    LCD_SET(lcd7->G);
}

/**
 * @Description: 段码位置显示 6
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_Num6(const seg7* lcd7)
{
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);
    
    LCD_SET(lcd7->A);
    // LCD_SET(lcd7->B);
    LCD_SET(lcd7->C);
    LCD_SET(lcd7->D);
    LCD_SET(lcd7->E);
    LCD_SET(lcd7->F);
    LCD_SET(lcd7->G);
}

/**
 * @Description: 段码位置显示 7
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_Num7(const seg7* lcd7)
{
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);
    
    LCD_SET(lcd7->A);
    LCD_SET(lcd7->B);
    LCD_SET(lcd7->C);
    // LCD_SET(lcd7->D);
    // LCD_SET(lcd7->E);
    // LCD_SET(lcd7->F);
    // LCD_SET(lcd7->G);
}

/**
 * @Description: 段码位置显示 8
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_Num8(const seg7* lcd7)
{
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);
    
    LCD_SET(lcd7->A);
    LCD_SET(lcd7->B);
    LCD_SET(lcd7->C);
    LCD_SET(lcd7->D);
    LCD_SET(lcd7->E);
    LCD_SET(lcd7->F);
    LCD_SET(lcd7->G);
}

/**
 * @Description: 段码位置显示 9
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_Num9(const seg7* lcd7)
{
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);
    
    LCD_SET(lcd7->A);
    LCD_SET(lcd7->B);
    LCD_SET(lcd7->C);
    LCD_SET(lcd7->D);
    // LCD_SET(lcd7->E);
    LCD_SET(lcd7->F);
    LCD_SET(lcd7->G);
}

#if 0
void LCD_StrC(const seg7* lcd7)
{
	/*7段码led各led对应位定义
	*A:顶部“-”；B:右上“|”；C:右下“|”；D:底部"-";
	*E:左下“|”；F:左上“|”；G:中间“-”；
	*/
    LCD_CLR(lcd7->A);
    LCD_CLR(lcd7->B);
    LCD_CLR(lcd7->C);
    LCD_CLR(lcd7->D);
    LCD_CLR(lcd7->E);
    LCD_CLR(lcd7->F);
    LCD_CLR(lcd7->G);

    LCD_SET(lcd7->A);
    LCD_SET(lcd7->D);
    LCD_SET(lcd7->E);
    // LCD_SET(lcd7->B);
    // LCD_SET(lcd7->C);
    LCD_SET(lcd7->F);
    //LCD_SET(lcd7->G);
}
#endif

void LCD_StrO(const seg7* lcd7)
{
    LCD_SET(lcd7->A);
	LCD_SET(lcd7->B);
	LCD_SET(lcd7->C);
	LCD_SET(lcd7->D);
	LCD_SET(lcd7->E);
	LCD_SET(lcd7->F);
}
void LCD_StrN(const seg7* lcd7)
{
	LCD_SET(lcd7->A);
	LCD_SET(lcd7->B);
	LCD_SET(lcd7->C);
	LCD_SET(lcd7->E);
	LCD_SET(lcd7->F);
}

void LCD_StrF(const seg7* lcd7)
{
	LCD_SET(lcd7->A);
	LCD_SET(lcd7->F);
	LCD_SET(lcd7->E);
	LCD_SET(lcd7->G);
}
void LCD_StrE(const seg7* lcd7)
{
    LCD_SET(lcd7->A);
    LCD_SET(lcd7->D);
    LCD_SET(lcd7->E);
    // LCD_SET(lcd7->B);
    // LCD_SET(lcd7->C);
    LCD_SET(lcd7->F);
    LCD_SET(lcd7->G);
}

void LCD_StrH(const seg7* lcd7)
{
	LCD_SET(lcd7->B);
	LCD_SET(lcd7->C);
	LCD_SET(lcd7->E);
	LCD_SET(lcd7->F);
	LCD_SET(lcd7->G);
}
void LCD_StrS(const seg7* lcd7)
{
	LCD_SET(lcd7->A);
	LCD_SET(lcd7->C);
	LCD_SET(lcd7->D);
	LCD_SET(lcd7->F);
	LCD_SET(lcd7->G);
}
void LCD_StrP(const seg7* lcd7)
{
	LCD_SET(lcd7->A);
	LCD_SET(lcd7->B);
	LCD_SET(lcd7->G);
	LCD_SET(lcd7->F);
	LCD_SET(lcd7->E);
}
void LCD_StrB(const seg7* lcd7)
{
	LCD_SET(lcd7->A);
	LCD_SET(lcd7->B);
	LCD_SET(lcd7->G);
	LCD_SET(lcd7->F);
	LCD_SET(lcd7->E);
	LCD_SET(lcd7->C);
	LCD_SET(lcd7->D);
}
void LCD_StrR(const seg7* lcd7)
{
	LCD_SET(lcd7->A);
	LCD_SET(lcd7->B);
	LCD_SET(lcd7->G);
	LCD_SET(lcd7->F);
	LCD_SET(lcd7->E);
	LCD_SET(lcd7->C);
}
void LCD_StrU(const seg7* lcd7)
{
	LCD_SET(lcd7->B);
	LCD_SET(lcd7->F);
	LCD_SET(lcd7->E);
	LCD_SET(lcd7->C);
	LCD_SET(lcd7->D);
}

void LCD_StrT(const seg7* lcd7)
{
	LCD_SET(lcd7->A);
	LCD_SET(lcd7->B);
	LCD_SET(lcd7->C);
}
void LCD_StrL(const seg7* lcd7)
{
	LCD_SET(lcd7->F);
	LCD_SET(lcd7->E);
	LCD_SET(lcd7->D);
}


/**
 * @Description: 显示小数点
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint8_t} dot
 */
void LCD_Dot(uint8_t dot)
{
    LCD_SET(dot);
}

/**
 * @Description: 显示冒号 ：
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_MaoHao(const seg7* lcd7)
{
    LCD_SET(lcd7->D);
    LCD_SET(lcd7->G);
    // LCD_SET(lcd7->E);
    // LCD_SET(lcd7->F);    
}

/**
 * @Description: 显示减号 -
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_JianHao(const seg7* lcd7)
{
    LCD_SET(lcd7->G);     
}

/**
 * @Description: 显示左中括号
 * @Input:
 * @Output:
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_LeftBrace(const seg7* lcd7)
{
    LCD_SET(lcd7->A);
    LCD_SET(lcd7->F);
    LCD_SET(lcd7->E);
    LCD_SET(lcd7->D);
}

/**
 * @Description: 显示右中括号
 * @Input:
 * @Output:
 * @return {*}
 * @param {seg7*} lcd7
 */
void LCD_RightBrace(const seg7* lcd7)
{
    LCD_SET(lcd7->A);
    LCD_SET(lcd7->B);
    LCD_SET(lcd7->C);
    LCD_SET(lcd7->D);
}

/**
 * @Description: 在LCD屏幕显示相应数字的设置值,转化对应数字成为相应的LCD设置值，返回设置值。
 * @Input: 要显示的数字（1位）；有无小数点；
 * @Output: 0：数据有误；其他：对应的设置数据；
 * @return {*}
 * @param {uint8_t} num     高4位 =1 有小数点   低4位：范围 0~9，超过此范围数据无效。
 * */
#if 0
uint8_t LCD_Conver_Num(uint8_t num)
{
    uint8_t dot;
    
    dot = (num>>4);
    num = num & 0x0F;

    if (num > 9)
    {
        myprintf(" %c range err\r\n",__FILE__);
        return 0; //display nothing
    }    
    dot = ((dot&0x1)<<3) & LCDp;
    switch (num)
    {
        case 0: return (LCD0|dot); 
        case 1: return (LCD1|dot); 
        case 2: return (LCD2|dot); 
        case 3: return (LCD3|dot); 
        case 4: return (LCD4|dot); 
        case 5: return (LCD5|dot); 
        case 6: return (LCD6|dot); 
        case 7: return (LCD7|dot); 
        case 8: return (LCD8|dot); 
        case 9: return (LCD9|dot); 
        default: return 0;
    }
    return 1;
}
#endif

/**
 * @Description: 数字转化为对应的显示字符
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint8_t} num
 * @param {seg7*} lcd7
 */
void LCD_Conver_Num(uint8_t num,const seg7* lcd7)
{
    //myprintf(" num:%d \r\n",num);

    if (num > 9)
    {
       myprintf(" %c range err %d\r\n",__FILE__,__LINE__);
        return; //display nothing
    }    
    switch (num)
    {
        case 0: LCD_Num0(lcd7); break;
        case 1: LCD_Num1(lcd7); break;
        case 2: LCD_Num2(lcd7); break;
        case 3: LCD_Num3(lcd7); break;
        case 4: LCD_Num4(lcd7); break;
        case 5: LCD_Num5(lcd7); break;
        case 6: LCD_Num6(lcd7); break;
        case 7: LCD_Num7(lcd7); break;
        case 8: LCD_Num8(lcd7); break;
        case 9: LCD_Num9(lcd7); break;
        default: break;
    }
}

/**
 * @Description: 符号转化为对应的显示符号
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint8_t} num
 * @param {seg7*} lcd7
 */
void LCD_Conver_Symbol(uint8_t num,const seg7* lcd7)
{
    //printf(" num:%c \r\n",num);
    LCD_NumCls(lcd7);
    switch (num)
    {
        case '-':
        	LCD_JianHao(lcd7);
        	break;
        case '[':
        	LCD_LeftBrace(lcd7);
         	break;
        case ']':
        	LCD_RightBrace(lcd7);
         	break;
        case ':':
        	LCD_MaoHao(lcd7);
        	break;
        case 'O':
        	LCD_StrO(lcd7);
        	break;
        case 'E':
        	LCD_StrE(lcd7);
        	break;
        case 'F':
        	LCD_StrF(lcd7);
        	break;
        case 'N':
			LCD_StrN(lcd7);
			break;
        case 'H':
			LCD_StrH(lcd7);
			break;
        case 'S':
			LCD_StrS(lcd7);
			break;
        case 'P':
			LCD_StrP(lcd7);
			break;
        case 'B':
			LCD_StrB(lcd7);
			break;
        case 'R':
			LCD_StrR(lcd7);
			break;
        case 'U':
        	LCD_StrU(lcd7);
			break;
        case 'T':
        	LCD_StrT(lcd7);
			break;
        case 'L':
        	LCD_StrL(lcd7);
			break;
        default:
        	printf("No Symbol \r\n");
        break;
    }
}

/**
 * @Description: 整数、小数转换为对应的屏幕显示
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint32_t} num
 * @param {uint8_t} dotnum
 */
void Num2LcdNum(int num,uint8_t dotnum)
{
    uint8_t i=0;
    uint8_t sizen=0;
    uint8_t sign = 0;
    uint8_t lcd_seg_nums = 0;
    uint8_t tmpbuf[LCD_SEG7_NUMS]= {0};

    if(num < 0){
    	num = 0- num;
    	sign = 1;
    	lcd_seg_nums = LCD_SEG7_NUMS -1;
		num = (num>LCD_NEGATIVE_MAX_NUM)? LCD_NEGATIVE_MAX_NUM : num;

    }else{
    	sign = 0;
    	num = (num>LCD_POSITIVE_MAX_NUM)? LCD_POSITIVE_MAX_NUM : num;
    	lcd_seg_nums = LCD_SEG7_NUMS;
    }

    if ( dotnum > LCD_DOT_NUMS)  
    {
        dotnum = LCD_DOT_NUMS;
    }

	for(i=0;i<lcd_seg_nums;i++)
	{
		tmpbuf[i] = num % 10;
		num = num / 10;
		if(num == 0)
		{
			sizen = i+1;
			break;
		}
	}

	if(sizen <= dotnum)
	{
		sizen = dotnum + 1;
	}
	for(i=0;i<sizen;i++)
	{
		LCD_Conver_Num(tmpbuf[i],&g_seg_num[LCD_SEG7_NUMS-i-1]);
	}

	if(sign){
		LCD_Conver_Symbol('-',&g_seg_num[0]);
	}

	if(dotnum){
		LCD_Dot(g_seg_dot[dotnum-1]);
	}
}


#if 0

/**
 * @Description: 在LCD屏幕显示相应ASC的设置值,转化对应ASC字符成为相应的LCD设置值，返回设置值。
 * @Input: 待打印显示的asc字符，一个字符
 * @Output: 程序运行结果
 * @return {*}  0：数据有误；其他：对应的设置数据；
 * @param {uint8_t} chr  待打印显示的asc字符
 */
uint8_t LCD_Conver_Asc(uint8_t chr)
{
    
    if(chr > 0x60 && chr < 0x7B)   chr = chr -0x20;    //"a~z" 
    
    switch (chr)
    {
        case 0x2d: return (LCDMINUS);   //"-"
        case 0x2e: return (LCDDOT);     //"."
        
        case 0x30: return (LCD0);
        case 0x31: return (LCD1);
        case 0x32: return (LCD2);
        case 0x33: return (LCD3);
        case 0x34: return (LCD4);
        case 0x35: return (LCD5);
        case 0x36: return (LCD6);
        case 0x37: return (LCD7);
        case 0x38: return (LCD8);
        case 0x39: return (LCD9);

        case 0x41: return (LCDA);
        case 0x42: return (LCDB);
        case 0x43: return (LCDC);
        case 0x44: return (LCDD);
        case 0x45: return (LCDE);
        case 0x46: return (LCDF);
        case 0x47: return (LCDG);
        case 0x48: return (LCDH);
        case 0x49: return (LCDI);
        case 0x4a: return (LCDJ);
        case 0x4c: return (LCDL);
        case 0x4e: return (LCDN);
        case 0x4f: return (LCDO);
        case 0x50: return (LCDP);
        case 0x51: return (LCDQ);
        case 0x52: return (LCDR);
        case 0x53: return (LCDS);
        case 0x54: return (LCDT);
        case 0x55: return (LCDU);
        case 0x58: return (LCDX);
        case 0x59: return (LCDY);

        default: myprintf("range err\r\n"); return 0;
    }
}
/**
 * @Description: 整数转化为对应的显示数字
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint32_t} num
 * @param {uint8_t} *buf
 * @param {uint8_t} start_n
 * @param {uint8_t} max_n
 */
void Num2LcdNum(uint32_t num,uint8_t *buf,uint8_t start_n,uint8_t max_n)
{
    uint8_t i=0;
    uint8_t sizen=0;
    uint8_t tmpbuf[12]= {0};

    if( (start_n>11) || (start_n+max_n>12)) 
    {
        myprintf("Num2LcdNum set range err  start_n=%d  max_n=%d\r\n",start_n,max_n);
        
        start_n =0;
        max_n = 12;

    }
    for(i=0;i<12;i++)
    {
        tmpbuf[i] = num % 10;
        num = num / 10;
        if(num == 0)
        {
            sizen = i+1;
            break;
        }
    }

    // printf("\r\n jisuan tmpbuf[i]: ");for(i=0;i<12;i++) printf("\r\n tmpbuf[i]: %x ",tmpbuf[i]);printf("\r\n");

    for(i=0;i<sizen;i++)
    {
        tmpbuf[i] = LCD_Conver_Num(tmpbuf[i]);
    }

    // printf("\r\n zhuanhuan tmpbuf[i]: ");for(i=0;i<12;i++) printf("\r\n tmpbuf[i]: %x ",tmpbuf[i]);printf("\r\n");

    if(sizen>max_n) sizen = max_n;
    for(i=0;i<sizen;i++)
    {
        buf[start_n+max_n-1-i] = tmpbuf[sizen-1-i];
    }

    // printf("\r\n fuzhi buf[i]: ");for(i=0;i<12;i++) printf("\r\n buf[i]: %x ",buf[i]);printf("\r\n");

}
/**
 * @Description: 浮点数转化为对应的显示小数
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint32_t} num
 * @param {uint32_t} frac
 * @param {uint8_t} *buf
 * @param {uint8_t} start_n
 * @param {uint8_t} max_n
 */
void Float2LcdNum (uint32_t num,uint32_t frac,uint8_t *buf,uint8_t start_n,uint8_t max_n)
{
    uint8_t i=0;
    uint8_t sizen=0;
    uint8_t tmpbuf[12]={0};
    
    if ( frac > 11)  
    {
        myprintf("dot range err\r\n");
        return;
    }
    
    if(11<start_n || 11<max_n )
    {
        myprintf("set range err\r\n");
        return;
    }

    // printf("\r\n float num: %d \r\n",num);

    for(i=0;i<12;i++)
    {
        tmpbuf[i] = num % 10;
        num = num / 10;
        if(num == 0)
        {
            sizen = i+1;
            break;
        }
    }
   
    if(frac)    tmpbuf[frac] |= 0x10;

    // printf("\r\n float tmpbuf[i]: ");for(i=0;i<12;i++) printf(" %x ",tmpbuf[i]);printf("\r\n");

    for(i=0;i<sizen;i++)
    {
        tmpbuf[i] = LCD_Conver_Num(tmpbuf[i]);
    }
    
    if(sizen > max_n)   sizen = max_n;
    for(i=start_n;i<sizen;i++)//从高位往下取数据
    {
        buf[i] = tmpbuf[i];
    }

    
}
/**
 * @Description: asc字符转化为对应的显示字符进行显示
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint8_t} datc
 * @param {uint8_t} disbn
 * @param {uint8_t} *buf
 */
void Asc2LcdAsc(uint8_t datc,uint8_t disbn,uint8_t *buf)
{
    if(disbn>11)
    {
        myprintf("display range err\r\n");
        return;
    }

    buf[disbn] = LCD_Conver_Asc(datc);
}


/**
 * @Description: 将对应的数字缓冲数据转化为对应的显示字符进行显示
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint32_t} *datbuf
 * @param {uint8_t} size_n
 * @param {uint8_t} start_n
 * @param {uint8_t} max_n
 */
void LCD_Dis_Nums(uint32_t *datbuf,uint8_t size_n,uint8_t start_n,uint8_t max_n)
{
    uint8_t i=0;
    
    for(i=0;i<size_n;i++)
    {
        // printf("\r\n datbuf[i]: %d  \r\n",datbuf[i] );
        
        Num2LcdNum(datbuf[i],g_FBn_Buff,start_n,max_n);

        // printf("\r\n g_FBn_Buff: %x %x %x %x   \r\n",g_FBn_Buff[0],g_FBn_Buff[1], g_FBn_Buff[2], g_FBn_Buff[3]  );
        LCD_Disp();
        CLOCK_DelayMs(DELAY_TIME);
    }   
}
/**
 * @Description: 将对应的浮点数缓冲转化为对应的浮点数进行显示
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint32_t} *datbuf
 * @param {uint8_t} size_n
 * @param {uint32_t} frac
 * @param {uint8_t} start_n
 * @param {uint8_t} max_n
 */
void LCD_Dis_Floats(uint32_t *datbuf,uint8_t size_n,uint32_t frac,uint8_t start_n,uint8_t max_n)
{
    uint8_t i=0;
    
    for(i=0;i<size_n;i++)
    {
        Float2LcdNum(datbuf[i],frac,g_FBn_Buff,start_n,max_n);
        LCD_Disp();
        CLOCK_DelayMs(DELAY_TIME);
    }   
}
/**
 * @Description: 将对应的asc缓冲转化为对应的显示字符串进行显示
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint8_t} *datbuf
 * @param {uint8_t} size_n
 * @param {uint8_t} start_n
 * @param {uint8_t} end_n
 */
void LCD_Dis_Ascs(uint8_t *datbuf,uint8_t size_n,uint8_t start_n,uint8_t end_n)
{
    uint8_t i=0;
    uint8_t j=0;
    
    if(start_n>11 || end_n>11) return;
    if(start_n >= end_n) return;
    // printf("\r\n datbuf[i]: ");for(i=0;i<size_n;i++) printf(" %c ",datbuf[i] );printf("\r\n" );
    for(i=0;i<size_n;)
    {
        for(j=end_n;j>=start_n;j--)
        {
            Asc2LcdAsc(datbuf[i++],(j),g_FBn_Buff);   
            // printf("\r\n j:%d \r\n",j );      
        }
        LCD_Disp();
        CLOCK_DelayMs(DELAY_TIME);
        
    }   
}

#if 0
/**
 * @Description: LCD 1位数字显示
 * @Input: 
 * @Output: 无
 * @return {*}
 * @param {char} num    待显示数字
 * @param {uint8_t} FBbn  数字在帧缓冲器中的位置，0，1，2，3，...,11
 * @param {uint8_t} size_n
 */
void LCD_Disp_Num(uint8_t num,uint8_t *buf,uint8_t distype,uint8_t disbn)
{
    uint32_t lcdtmp=0;

    if(disbn>12) return;

    // if(distype == DIS_MUL)
    // {
    //     lcdtmp = READ_REG(LCD->FB2);
    //     buf[11] = lcdtmp>>(24);
    //     buf[10] = lcdtmp>>(16) & 0xFF;
    //     buf[9] = lcdtmp>>(8) & 0xFF;
    //     buf[8] = lcdtmp>>(0) & 0xFF;

    //     lcdtmp = READ_REG(LCD->FB1);
    //     buf[7] = lcdtmp>>(24);
    //     buf[6] = lcdtmp>>(16) & 0xFF;
    //     buf[5] = lcdtmp>>(8) & 0xFF;
    //     buf[4] = lcdtmp>>(0) & 0xFF;

    //     lcdtmp = READ_REG(LCD->FB0);
    //     buf[3] = lcdtmp>>(24);
    //     buf[2] = lcdtmp>>(16) & 0xFF;
    //     buf[1] = lcdtmp>>(8) & 0xFF;
    //     buf[0] = lcdtmp>>(0) & 0xFF;
    // }

    buf[disbn] = LCD_Conver_Num(num,0);

    
    
    // lcdtmp = lcdtmp << (24-8*FBbn);

    // if(FBn==0)  WRITE_REG(LCD->FB0, lcdtmp);
    // else if(FBn==1) WRITE_REG(LCD->FB1, lcdtmp);
    // else WRITE_REG(LCD->FB2, lcdtmp);
    
//     lcdtmp = (lcdtmp<<24)|(lcdtmp<<16)|(lcdtmp<<8)|(lcdtmp<<0);
//     WRITE_REG(LCD->FB0, lcdtmp);
//     WRITE_REG(LCD->FB1, lcdtmp);
//     WRITE_REG(LCD->FB2, lcdtmp);
}
#endif

#if 0
/**
 * @Description: 打包LCD显示数据
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint8_t} dat
 * @param {uint8_t} *buf
 * @param {uint8_t} distype
 * @param {uint8_t} disbn
 */
void LCD_Package_Dat(uint8_t dat,uint8_t *buf,uint8_t distype,uint8_t disbn)
{
    uint8_t lcddat=0;

    if(disbn>12) 
    {
        myprintf("range err\r\n");
        return;
    }

    if(distype == DIS_NUM)  Num2LcdNum(dat,buf);
    else if(distype == DIS_ASC) 
    {
        lcddat = LCD_Conver_Asc(dat);
        buf[disbn] = lcddat;
    }
    else if(distype == DIS_INIT)
    {
        lcddat = 0xFF;
        for(i=0;i<12;i++)   buf[i] = lcddat;
    } 
    else
    {
        lcddat = 0;
        for(i=0;i<12;i++)   buf[i] = lcddat;
    }
}

#endif


#if 0
/**
 * @Description: LCD 指定帧缓冲的指定位置显示数据，使用指定缓冲
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {char*} numbuf    数据缓冲
 * @param {uint32_t} FBn    指定帧缓冲 0，1，2；
 * @param {uint8_t} FBbn    指定帧缓冲位置 0，1，2，3
 * @param {uint8_t} size_n  数据缓冲大小
 */
int LCD_Disp_Nums_S(uint8_t* numbuf,uint32_t FBn,uint8_t FBbn,uint8_t size_n)
{
    int i; 

    for (i=0;i<size_n;i++)
    {
        CLOCK_DelayMs(30);
        LCD_Disp_Num(numbuf[i],FBn,FBbn);
    }
    return 0;
}

#endif


#if 0

/**
 * @Description: LCD 显示数据缓冲中的数据，使用全部缓冲
 * @Input: 
 * @Output: 无
 * @return {*}
 * @param {char*} numbuf 数据缓冲 缓冲中是数字
 * @param {uint8_t} size_n 缓冲大小
 */
void LCD_Disp_Nums_A(uint8_t* numbuf,uint8_t size_n)
{
    uint32_t i,j,k; 
    uint32_t a0,a1,a2,m,n;
    uint8_t b[12];

    m = size_n % 12;
    n = size_n / 12;
    
    if(m)
    {
        k = n;
        n = m+1;
    }

    for( j=0;j<n;j++)
    {
        CLOCK_DelayMs(30);
        
        if(j<k)
        {
            for(i=0;i<12;i++)   b[i] = numbuf[i+12*j];
        }
        else
        {
            for(i=0;i<12;i++)   b[i] = 0;
            for(i=0;i<m;i++)   b[i] = numbuf[i+12*n];
        }
        i = 0;
        a2|=(LCD_Conver_Num(b[i++],0)<<(24)); 
        a2|=(LCD_Conver_Num(b[i++],0)<<(16)); 
        a2|=(LCD_Conver_Num(b[i++],0)<<(8)); 
        a2|=(LCD_Conver_Num(b[i++],0)<<(0)); 
        WRITE_REG(LCD->FB2, a2);

        a1|=(LCD_Conver_Num(b[i++],0)<<(24)); 
        a1|=(LCD_Conver_Num(b[i++],0)<<(16)); 
        a1|=(LCD_Conver_Num(b[i++],0)<<(8)); 
        a1|=(LCD_Conver_Num(b[i++],0)<<(0)); 
        WRITE_REG(LCD->FB1, a1);

        a0|=(LCD_Conver_Num(b[i++],0)<<(24)); 
        a0|=(LCD_Conver_Num(b[i++],0)<<(16)); 
        a0|=(LCD_Conver_Num(b[i++],0)<<(8)); 
        a0|=(LCD_Conver_Num(b[i++],0)<<(0));
        WRITE_REG(LCD->FB0, a0);

    }

}

#endif

#if 0

/**
 * @Description: LCD 1位数字显示
 * @Input: 
 * @Output: 无
 * @return {*}
 * @param {char} num    待显示数字
 * @param {uint32_t} FBn 帧缓冲器选择，0，1，2
 * @param {uint8_t} FBbn  数字在帧缓冲器中的位置，0，1，2，3
 * @param {uint8_t} size_n
 */
// void LCD_Disp_Asc(char num,uint32_t FBn,uint8_t FBbn)
// {
//     uint32_t lcdtmp=0;
    
//     lcdtmp = LCD_Conver_Asc(num);
//     lcdtmp = lcdtmp << (24-8*FBbn);

//     if(FBn==0)  WRITE_REG(LCD->FB0, lcdtmp);
//     else if(FBn==1) WRITE_REG(LCD->FB1, lcdtmp);
//     else WRITE_REG(LCD->FB2, lcdtmp);
// }

/**
 * @Description: LCD 指定帧缓冲的指定位置显示数据，使用指定缓冲
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {char*} numbuf    数据缓冲
 * @param {uint32_t} FBn    指定帧缓冲 0，1，2；
 * @param {uint8_t} FBbn    指定帧缓冲位置 0，1，2，3
 * @param {uint8_t} size_n  数据缓冲大小
 */
// int LCD_Disp_Ascs_S(uint8_t* numbuf,uint32_t FBn,uint8_t FBbn,uint8_t size_n)
// {
//     int i; 

//     for (i=0;i<size_n;i++)
//     {
//         CLOCK_DelayMs(30);
//         LCD_Disp_Asc(numbuf[i],FBn,FBbn);
//     }
//     return 0;
// }
/**
 * @Description: LCD 显示数据缓冲中的数据，使用全部缓冲
 * @Input: 
 * @Output: 无
 * @return {*}
 * @param {char*} numbuf 数据缓冲 缓冲中是数字
 * @param {uint8_t} size_n 缓冲大小
 */
void LCD_Disp_Ascs_A(uint8_t* numbuf,uint8_t size_n)
{
    uint32_t i,j,k; 
    uint32_t a0,a1,a2,m,n;
    uint8_t b[12];

    m = size_n % 12;
    n = size_n / 12;
    
    if(m)
    {
        k = n;
        n = m+1;
    }

    for( j=0;j<n;j++)
    {
        CLOCK_DelayMs(30);
        
        if(j<k)
        {
            for(i=0;i<12;i++)   b[i] = numbuf[i+12*j];
        }
        else
        {
            for(i=0;i<12;i++)   b[i] = 0;
            for(i=0;i<m;i++)   b[i] = numbuf[i+12*n];
        }
        i = 0;
        a2|=(LCD_Conver_Asc(b[i++])<<(24)); 
        a2|=(LCD_Conver_Asc(b[i++])<<(16)); 
        a2|=(LCD_Conver_Asc(b[i++])<<(8)); 
        a2|=(LCD_Conver_Asc(b[i++])<<(0)); 
        WRITE_REG(LCD->FB2, a2);

        a1|=(LCD_Conver_Asc(b[i++])<<(24)); 
        a1|=(LCD_Conver_Asc(b[i++])<<(16)); 
        a1|=(LCD_Conver_Asc(b[i++])<<(8)); 
        a1|=(LCD_Conver_Asc(b[i++])<<(0)); 
        WRITE_REG(LCD->FB1, a1);

        a0|=(LCD_Conver_Asc(b[i++])<<(24)); 
        a0|=(LCD_Conver_Asc(b[i++])<<(16)); 
        a0|=(LCD_Conver_Asc(b[i++])<<(8)); 
        a0|=(LCD_Conver_Asc(b[i++])<<(0));
        WRITE_REG(LCD->FB0, a0);
    }

}

/**
 * @Description: 4位浮点数在LCD转化显示
 * @Input: 待显示浮点数，帧缓冲寄存器，小数位数
 * @Output: 0：数据有误；1：正常运行结束。
 * @return {*}
 * @param {uint32_t} FBn 帧缓冲寄存器选择 0、1、2
 * @param {uint32_t} num  数据 连小数位数计算在内，数位不超过4位数
 * @param {uint32_t} frac 小数位数  0,1,2,3
 */
int LCD_Disp_Float (uint32_t FBn, uint32_t num, uint32_t frac)
{
    uint32_t m, c, x, i;    
    uint32_t dot_mask = 0;
    
    if (num > 9999 || FBn > 2 || frac > 3)  return 0;
    
    m = num /1000;
    c = (num %1000) /100;
    x = (num %100 ) /10;
    i = num %10;    
    dot_mask = 0;
    switch (frac)
    {
        case 1: dot_mask=2; break;
        case 2: dot_mask=4; break;
        case 3: dot_mask=8; break;
        default: dot_mask=0; break;
    }
    
    if ((!m) && (frac<3)) m = 0;
    else m = LCD_Conver_Num(m, (dot_mask>>3)&0x1)<<24 ;
    
    if ((!c) && (frac<2)) c = 0;
    else c = LCD_Conver_Num(c, (dot_mask>>2)&0x1)<<16 ;
    
    if ((!x) && (frac<1)) x = 0;
    else x = LCD_Conver_Num(x, (dot_mask>>1)&0x1)<<8 ;
    
    if(FBn==0)  WRITE_REG(LCD->FB0, (m | c | x | i) );
    else if(FBn==1) WRITE_REG(LCD->FB1, (m | c | x | i) );
    else WRITE_REG(LCD->FB2, (m | c | x | i) );
    
    return 1;
}

#endif

#endif
/**
 * @Description: 将缓冲数据更新到屏幕进行显示
 * @Input: 无
 * @Output: 无
 * @return {*}无
 */
void LCD_Disp(void)
{
    uint32_t lcdtmp=0;
    
    lcdtmp = (g_FBn_Buff[11]<<24)|(g_FBn_Buff[10]<<16)|(g_FBn_Buff[9]<<8)|(g_FBn_Buff[8]<<0);
    // printf("\r\n FB2:%8x  h\r\n",lcdtmp);
    WRITE_REG(LCD->FB2, lcdtmp );
    
    lcdtmp = (g_FBn_Buff[7]<<24)|(g_FBn_Buff[6]<<16)|(g_FBn_Buff[5]<<8)|(g_FBn_Buff[4]<<0);
    // printf("\r\n FB1:%8x  h\r\n",lcdtmp);
    WRITE_REG(LCD->FB1, lcdtmp);
    
    lcdtmp = (g_FBn_Buff[3]<<24)|(g_FBn_Buff[2]<<16)|(g_FBn_Buff[1]<<8)|(g_FBn_Buff[0]<<0);
    // printf("\r\n FB0:%8x  h\r\n",lcdtmp);
    WRITE_REG(LCD->FB0, lcdtmp);
    
}
/**
 * @Description: LCD 段码屏显示初始化，显示屏幕全部可显示内容
 * @Input: 无
 * @Output: 无
 * @return {*}无
 */
void LCD_Dis_Init(void)
{
    uint8_t i=0;

    for(i=0;i<12;i++)
    {
    	g_FBn_Buff[i] = 0xFF;
    }
    LCD_Disp();
}
/**
 * @Description: 清屏
 * @Input: 无
 * @Output: 无
 * @return {*}无
 */
void LCD_Dis_Cls(void)
{
    uint8_t i=0;
    
    for(i=0;i<12;i++)
    {
    	g_FBn_Buff[i] = 0;
    }

    LCD_Disp();
}

/**
 * @Description: LCD初始化，初始化芯片内部LCD配置。包括对应寄存器设置、变量初始化、显示初始化等
 * @Input: 数据刷新率
 * @Output: 
 * @return {*}
 * @param {uint32_t} refresh_rate：LCD数据刷新频率
 */

// void LCD_Init(uint32_t refresh_rate)
// {
//     CLEAR_BIT(CHIPCTRL, PMU_CHIPCTRL_LCDGPIO);  //配置芯片PMU中的LCD相关设置
//     WRITE_REG(LCD_RFR, refresh_rate);
// }
