/*
 * UserUart.c
 *
 *  Created on: 2021 Äê11ÔÂ 5
 *      Author: lixin
 */

#include "UserUart.h"
//#include "tasks.h"

void Uart1_Init(uint32_t uart1_baud)
{
	UART_InitTypeDef UART_InitStruct;
	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.UART_BaudRate = uart1_baud;
	UART_Init(UART1,&UART_InitStruct);
	CLOCK_DelayUs(200);
	UART_ITConfig(UART1,UART_IT_IRE,ENABLE);
	UART_ITCmd(UART1,ENABLE);
}

void Uart0_Init(uint32_t uart0_baud)
{
	UART_InitTypeDef UART_InitStruct;
	UART_StructInit(&UART_InitStruct);

	if(CLOCK_GetFlagStatus(CLOCK_HSE_SELECT_STATUS) == RESET)
	{
		UART_InitStruct.Clock_Freq = CLOCK_GetClocksFreq();
		inte8m =  UART_InitStruct.Clock_Freq/1000;
	}
#if UART0_IR_MODE

	UART_InitStruct.UART_BaudRate = 2400;
#if IR_CarrierWave_MODE

	UART_IrInit(&UART_InitStruct);
#else
	UART_Init(UART0,&UART_InitStruct);
	GPIO_WriteBit(GPIOA_BIT, GPIO_Pin_14, Bit_SET);
#endif

#else
	UART_InitStruct.UART_BaudRate = uart0_baud;
	UART_Init(UART0,&UART_InitStruct);
#endif

	CLOCK_DelayUs(200);

	UART_ClearITFifo(UART0);
	UART_ITConfig(UART0,UART_IT_IRE,ENABLE);
	UART_ITCmd(UART0,ENABLE);

}

#if 0
int ir_send(void)
{

    GPIO_WriteBit(GPIOA_BIT, GPIO_Pin_14, Bit_RESET);
    UART0->IIR_FCR_DL_D = 0x6;
    UART0->IER_DL_H = 0x0;
    int i;
    uint8_t *chr ="fefefe123";
    for (i = 0; i < 30; i++)
    {
        if (chr[i] != '\0')
        {
//            myputchar_u0(chr);
            UART_IrSendData(chr);
        }
    }
    CLOCK_DelayMs(100);
    GPIO_WriteBit(GPIOA_BIT, GPIO_Pin_14, Bit_SET);
    UART0->IIR_FCR_DL_D = 0x6;
    UART0->IER_DL_H = 0x1;

    return 0;
}

#endif


void UartInit(uint32_t uart0_baud,uint32_t uart1_baud)
{

	UART_InitTypeDef UART_InitStruct;
	UART_StructInit(&UART_InitStruct);

	if(CLOCK_GetFlagStatus(CLOCK_HSE_SELECT_STATUS) == RESET)
	{
		UART_InitStruct.Clock_Freq = CLOCK_GetClocksFreq();
	}

#if UART0_IR_MODE

	UART_InitStruct.UART_BaudRate = 2400;
#if IR_CarrierWave_MODE

	UART_IrInit(&UART_InitStruct);
#else
	UART_Init(UART0,&UART_InitStruct);
	GPIO_WriteBit(GPIOA_BIT, GPIO_Pin_14, Bit_SET);
#endif

#else
	UART_InitStruct.UART_BaudRate = uart0_baud;
	UART_Init(UART0,&UART_InitStruct);
#endif

	CLOCK_DelayMs(10);
	UART_ClearITFifo(UART0);
	UART_ITConfig(UART0,UART_IT_IRE,ENABLE);
	UART_ITCmd(UART0,ENABLE);

	UART_InitStruct.UART_BaudRate = uart1_baud;
	UART_Init(UART1,&UART_InitStruct);

	CLOCK_DelayMs(10);
	UART_ClearITFifo(UART0);
	UART_ITConfig(UART1,UART_IT_IRE,ENABLE);
	UART_ITCmd(UART1,ENABLE);

}


int UartIrSend(const char *buf)
{
	int i;
    GPIO_WriteBit(GPIOA_BIT, GPIO_Pin_14, Bit_RESET);
    UART_ClearITFifo(UART0);
    UART_ITConfig(UART0,UART_IT_IRE,DISABLE);
	for(i=0; buf[i]!='\0'; i++)
	{
		UART_IrSendData(buf[i]);
	}
// 	CLOCK_DelayMs(100);
    GPIO_WriteBit(GPIOA_BIT, GPIO_Pin_14, Bit_SET);
    UART_ClearITFifo(UART0);
    UART_ITConfig(UART0,UART_IT_IRE,ENABLE);
    return 0;
}



