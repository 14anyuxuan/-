/********************************************************************
* �ļ���:  ls1d6_std_printf.c
* �汾��	  V1.0
* ����:    ����
* ����:    2021.08.31
* ˵��:    ���ļ�����printf��ӡ�����нӿں������궨��
* ��Ȩ:    ��о�пƣ�̫ԭ���������޹�˾
********************************************************************/
#include "../include/ls1d_std_printf.h"


void printBuf(uint8 *buf,uint32 len)
{
    int i;
    for (i = 0; i < len; i++) 
    {
         ///if (i % 32 == 0) 
         {
         //    printf("[%4x]:", i);
         }
         printf("%x ", buf[i]);
    }
    printf("\r\n");
}

/*************************************************
��������:         myputchar
�������:

�������:         ��
��������ֵ˵��:   ��
ʹ�õ���Դ:
*************************************************/
void myputchar(unsigned char chr)
{
//     while(!(Uart0_LSR & 0x20)) ;
//     Uart0_TxData = chr;
//     while(!(Uart0_LSR & 0x20)) ;

 	while (!(READ_BIT(UART0->LSR,UART_LSR_FLAG_TFE)));
 	UART_SendData(UART0, chr);

}

/*************************************************
��������:         printbase
�������:

�������:         ��
��������ֵ˵��:   ��
ʹ�õ���Դ:
*************************************************/
int printbase(long v,int w,int base,int sign)
{
    int i,j;
    int c;
    char buf[72];
    unsigned long value;
    if(sign && v<0)
    {
    	value = -v;
    	myputchar('-');
    }
    else
    	value=v;

    for(i=0;value;i++)
    {
    	buf[i]=value%base;
    	value=value/base;
    }
    for(j=max(w,i);j>0;j--)
    {
        c=j>i?0:buf[j-1];
        myputchar((c<=9)?c+'0':c-0xa+'a');
    }
    return 0;
}

/*************************************************
��������:         puts
�������:

�������:         ��
��������ֵ˵��:   ��
ʹ�õ���Դ:
*************************************************/
int puts(char *s)
{
	char c;
	while((c=*s))
	{
		if(c == '\n') myputchar('\r');
		myputchar(c);
		s++;
	}

	return 0;
}

/*************************************************
��������:         printf
�������:

�������:         ��
��������ֵ˵��:   ��
ʹ�õ���Դ:
*************************************************/
int myprintf(char *fmt,...)
{
	int i;
	char c;
	void **arg;
	void *ap;
	int w;

	__builtin_va_start(ap,fmt);
	arg=ap;
#if UART0_IR_MODE
    GPIO_WriteBit(GPIOA_BIT, GPIO_Pin_14, Bit_RESET);
    UART_ClearITFifo(UART0);
	UART_ITConfig(UART0,UART_IT_IRE,DISABLE);
#endif

	for(i=0;fmt[i];i++)
	{
		c=fmt[i];
	    if(c=='%')
		{
			w=1;
again:
        switch(fmt[i+1])
        {
            case 's':
                puts(*arg);
                arg++;
                i++;
                break;
            case 'c':
                myputchar((long)*arg);
                arg++;
                i++;
                break;
            case 'u':
                printbase((long)*arg,w,10,0);
                arg++;
                i++;
                break;
            case 'd':
                printbase((long)*arg,w,10,1);
                arg++;
                i++;
                break;
            case 'o':
                printbase((long)*arg,w,8,0);
                arg++;
                i++;
                break;
            case 'b':
                printbase((long)*arg,w,2,0);
                arg++;
                i++;
                break;
            case 'p':
            case 'x':
                printbase((long)*arg,w,16,0);
                arg++;
                i++;
                break;
            case '%':
                myputchar('%');
                i++;
                break;
            case '0':
                i++;
                for(w=0;fmt[i+1]>'0' && fmt[i+1]<='9';i++)
                 w=w*10+(fmt[i+1]-'0');
                goto again;
                 break;
            case '1' ... '9':
                for(w=0;fmt[i+1]>'0' && fmt[i+1]<='9';i++)
                 w=w*10+(fmt[i+1]-'0');
                goto again;
                 break;

            default:
                myputchar('%');
                break;
        }

    }
    else{
        if(c=='\n') myputchar('\r');
        myputchar(c);
    }
}

#if UART0_IR_MODE
 	UART_ClearITFifo(UART0);
 	UART_ITConfig(UART0,UART_IT_IRE,ENABLE);
 	GPIO_WriteBit(GPIOA_BIT, GPIO_Pin_14, Bit_SET);
#endif

    return 0;

}






