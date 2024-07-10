/*
 * UserUart.h
 *
 *  Created on: 2021Äê11ÔÂ5ÈÕ
 *      Author: lixin
 */

#ifndef USERINC_USERUART_H_
#define USERINC_USERUART_H_

#include "../include/ls1d_std_clock.h"
#include "../include/ls1d_std_gpio.h"
#include "../include/ls1d_std_printf.h"
#include "../include/ls1d_std_uart.h"


extern void UartInit(uint32_t uart0_baud,uint32_t uart1_baud);
extern void Uart0_Init(uint32_t uart0_baud);
extern void Uart1_Init(uint32_t uart1_baud);

#define InputDataWriteCheck(x,y)	{if(((uint32_t)x) != ((uint32_t)y)) goto ExceptWrite;}


#endif /* USERINC_USERUART_H_ */
