
/********************************************************************
* 文件名:	ls1d6_std_str_uart.c
* 版本：	V1.0
* 作者:		李鑫
* 日期:		2021.11.24
* 说明:		本文件包含串口的所有接口函数及宏定义
* 版权:		龙芯中科（太原）技术有限公司
********************************************************************/

#include "../include/ls1d_std_uart.h"

#define OS_CLOCK_FREQ           8000000
#define EXIT_32K_CLOCK          32768

/**
  * @brief    Initializes the USARTx peripheral according to the specified
  * 		   parameters in the USART_InitStruct .
  * @param
  *         UARTx: Select the UART or the UART peripheral.
  *   			    This parameter can be one of the following values:
  *                 UART0, UART1
  *         UART_InitStruct: pointer to a UART_InitTypeDef structure
  *         		that contains the configuration information for the specified UART peripheral.
  *
  * @retval None
  *
  * remark：uart1 clock freq is 32k;
  */
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{

    uint8 data = 0;
    uint32 div = 0;
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_UART_WORD_LENGTH(UART_InitStruct->UART_WordLength));
    assert_param(IS_UART_STOPBITS(UART_InitStruct->UART_StopBits));
    assert_param(IS_UART_PARITY(UART_InitStruct->UART_Parity));
    assert_param(IS_UART_CLOCK(UART_InitStruct->Clock_Freq));
    assert_param(IS_UART_FIFO_TRIGGER(UART_InitStruct->UART_Triger));


    /* 复位LCR寄存器  */
    UARTx->LCR = 0x03;

    if(UARTx != UART0)
    {

    	UART_InitStruct->Clock_Freq = 32768;   //32768的时候9600会有%3的误码率

    	div = (UART_InitStruct->Clock_Freq << 8);

    	switch(UART_InitStruct->UART_BaudRate)
    	{
    		case 1200:
    			UART1->MCR_SCR = 0x4a;//32768/10/1200 = 2.7306667;
    			 div = (div / 10);
				break;
    		case 2400:
    			UART1->MCR_SCR = 0x38;//32768/8/2400 = 1.70666667;
    			div = (div / 8);
    			break;
    		case 4800:
    			UART1->MCR_SCR = 0x36; //32768/6/4800 = 1.1377778;
    			div = (div / 6);
    			break;
    		default:
    			UART1->MCR_SCR = 0x23;////32768/3/9600 = 1.1377778 ;
    			div = (div / 3);
    			break;
    	}
    	//
        //printf("uart1 freq now value is %x\n",UART_InitStruct->Clock_Freq);

    }
    else
    {
    	div = (UART_InitStruct->Clock_Freq << 8);
        div = (div >> 4);
    }
    div =  div / (UART_InitStruct->UART_BaudRate);      //[23:16] DL_H  [15: 8] DL_L  [ 7: 0] DL_D
    SET_BIT(UARTx->LCR,UART_Lab_En);

    UARTx->IIR_FCR_DL_D = div & 0xff;
    div >>= 8;
    UARTx->DAT_DL_L = div & 0xff;
    div >>= 8;
    UARTx->IER_DL_H = div & 0xff;

    CLEAR_BIT(UARTx->LCR,UART_Lab_En);

//    asm volatile("nop;nop;nop;nop;\n");
    UARTx->IER_DL_H = 0x00;

    UARTx->IIR_FCR_DL_D = UART_InitStruct->UART_Triger |  UART_FIFO_TX_RST | UART_FIFO_RX_RST;

    SET_BIT(UARTx->LCR,UART_InitStruct->UART_WordLength);

    SET_BIT(UARTx->LCR,UART_InitStruct->UART_Parity);

    SET_BIT(UARTx->LCR,UART_InitStruct->UART_Parity_Bid_Control);

    SET_BIT(UARTx->LCR,UART_InitStruct->UART_StopBits);

    SET_BIT(UARTx->LCR,UART_InitStruct->UART_Break_Control);

    SET_BIT(UARTx->LCR,UART_InitStruct->UART_Parity_Control);

	data = UARTx->DAT_DL_L;

	//CLOCK_DelayUs(200);

}



/**
  * @brief  Fills each USART_InitStruct member with its default value.
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  * remark:
  * 		uart1 clock freq is 32k;
  */
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
  /* USART_InitStruct members default value */
	UART_InitStruct->UART_BaudRate = 2400;
	UART_InitStruct->Clock_Freq = 8000000;
	UART_InitStruct->UART_WordLength = UART_Word_Length_8b;
	UART_InitStruct->UART_StopBits = UART_StopBits_1;
	UART_InitStruct->UART_Parity = UART_Parity_Odd ;
	UART_InitStruct->UART_Parity_Control = UART_Parity_No;
	UART_InitStruct->UART_Break_Control = UART_Break_Control_NEn;
	UART_InitStruct->UART_Parity_Bid_Control = UART_Parity_No_Bid;
	UART_InitStruct->UART_Triger = UART_FIFO_TRIGGER_1;

}
/**
 * brief：  Enables or disables the specified USART interrupts.
 * param：  USARTx: Select the USART or the UART peripheral.
 *   				 This parameter can be one of the following values:
 *   				    USART0, USART1
 * param：  USART_IT: specifies the UART interrupt sources to be enabled or disabled.
 *   	    		  This parameter can be one of the following values:
 *      				UART_IT_IME:  保留的 Modem中断使能
 *       				UART_IT_ILE:  线路状态中断使能
 *      				UART_IT_ITE:  发送状态中断使能
 *       				UART_IT_IRE:  接收状态中断使能
 * param：  NewState: new state of the specified USARTx interrupts.
 *   				  This parameter can be: ENABLE or DISABLE.
 * retval： None
 */
void UART_ITConfig(UART_TypeDef* UARTx, uint8_t UART_IT, FunctionalState NewState)
{
	/* Check the parameters */
	uint8_t uartdata = 0x00;
	assert_param(IS_UART_PERIPH(UARTx));
	assert_param(IS_UART_CONFIG_IT(USART_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
    (NewState != DISABLE)? (SET_BIT(UARTx->IER_DL_H,UART_IT)) : (CLEAR_BIT(UARTx->IER_DL_H,UART_IT));
	/* clear data reg*/
	uartdata = UARTx->DAT_DL_L;
}

/**
 * brief： Enables or disables the specified UART interrupts.
 * @param  USARTx: Select the USART or the UART peripheral.
 *   This parameter can be one of the following values:
 *   USART0, USART1
 * @param  NewState: new state of the specified USARTx interrupt.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void UART_ITCmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
	uint8_t uartdata = 0x00;

	assert_param(IS_UART_PERIPH(USARTx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(UARTx != UART1)
	{
		/* 设置uart0中断为 高电平触发 */
//		INT->INT_POL |= 0x08;
		(NewState != DISABLE)? (INT->INT_EN  |= ((uint8_t)0x08)) : (INT->INT_EN  &= ((uint8_t)0xF7));
	}
	else
	{
		/* 设置uart1中断为 高电平触发 */
//		INT->INT_POL |= 0x04;
		(NewState != DISABLE)? (INT->INT_EN  |= ((uint8_t)0x04)) : (INT->INT_EN  &= ((uint8_t)0xFB));
	}
	/* clear data reg*/
	uartdata = UARTx->DAT_DL_L;

}



/**
 * brief:  Transmits single data through the USARTx peripheral.
 * param:  USARTx: Select the USART or the UART peripheral.
 *   	   This parameter can be one of the following values:
 *   	   USART0, USART1
 * param:  Data: the data to transmit.
 * retval: None
 */
void UART_SendData(UART_TypeDef* UARTx, uint8_t Data)
{
	assert_param(IS_UART_PERIPH(USARTx));

	//while (!READ_BIT(UARTx->LSR,UART_LSR_FLAG_TFE));
	UARTx->DAT_DL_L = Data;
}

/**
 * brief:  Receive single data through the USARTx peripheral.
 * param:  USARTx: Select the USART or the UART peripheral.
 *   	   This parameter can be one of the following values:
 *   	   USART0, USART1
 * param:
 * retval:  the data receive.
 */
uint8_t UART_ReceiveData(UART_TypeDef* UARTx)
{
	uint8_t data = 0;
	assert_param(IS_UART_PERIPH(USARTx));

	data = UARTx->DAT_DL_L ;
	return data;
}

/**
  * @brief  Checks whether the specified USART flag is set or not.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     	 UART_LSR_FLAG_ERR:  Error flag
  *     	 UART_LSR_FLAG_TE:   Transmit data register empty flag
  *     	 UART_LSR_FLAG_TFE:  Transmit fifo register empty flag
  *    		 UART_LSR_FLAG_BI:   break flag
  *     	 UART_LSR_FLAG_FE:   Framing Error flag
  *     	 UART_LSR_FLAG_PE:   Parity Error flag
  *     	 UART_LSR_FLAG_OE:   OverRun Error flag
  *     	 UART_LSR_FLAG_RXNE:   Receive data register not empty flag
  * @retval The new state of USART_FLAG (SET or RESET).
  */

FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, uint8_t UART_FLAG)
{
	FlagStatus bitstatus = RESET;
	assert_param(IS_UART_PERIPH(USARTx));
	assert_param(IS_UART_LSR_FLAGS(UART_FLAG));

	if((UARTx->LSR & UART_FLAG) != (uint8_t)RESET)
	{
		bitstatus = SET;
	}
	else
	{
		bitstatus = RESET;
	}
	return bitstatus;
}

/**
 *@说明： Checks whether the specified UART interrupt has occurred or not.
 *param：  USARTx: Select the USART or the UART peripheral.
 *				 This parameter can be one of the following values:
 *				 USART0、 USART1
 *
 *param  USART_IT: specifies the USART interrupt source to check.
 *				   This parameter can be one of the following values:
 *				   UART_IT_RXOT： 接收超时，有数据有效且后续4个字符时间内无操作
 *				   UART_IT_IL：	 奇偶 、 溢出 或 帧错误、 或打断中断
 *				   UART_IT_RXNE：接收寄存器非空中断
 *				   UART_IT_TXE：  发送fifo空中断
 *				   UART_IT_MDM： 保留的 Modem寄存器，两线串口实现无此中断源
 *				   UART_IT_INTPn 是否存在未处理的中断
 *retval: None
 *
 *		由于中断位有重叠，所以查询时，一次只允许查询一个中断标志；不可以同时将多个中断标志取位或后，去查询；
 */
ITStatus UART_GetITStatus(UART_TypeDef* UARTx, uint8_t UART_IT_FLAG)
{
	FlagStatus bitstatus = RESET;
	assert_param(IS_UART_PERIPH(USARTx));

	if((UARTx->IIR_FCR_DL_D & UART_IT_FLAG) == UART_IT_FLAG)
	{
		bitstatus = SET;
	}
	else
	{
		bitstatus = RESET;
	}
	return bitstatus;
}
/**
 *@brief  Clears the USARTx's interrupt pending bits.
 *param：  USARTx: Select the USART or the UART peripheral.
 *		 		 USART0, USART1
 *
 *retval None
 */

void UART_ClearIT(UART_TypeDef* UARTx)
{
	uint8_t uartdata = 0x00;

	assert_param(IS_UART_PERIPH(USARTx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* clear data reg*/
 	uartdata = UARTx->DAT_DL_L;

	if(UARTx != UART1)
	{
		INT->INT_CLR |= 0x08;
	}
	else
	{
		INT->INT_CLR |= 0x04;

	}

}

/**
 *@说明： Clears the USARTx's interrupt pending bits.
 *param：  USARTx: Select the USART or the UART peripheral.
 *				 This parameter can be one of the following values:
 *				 USART0、 USART1
 *
 *param  USART_IT: specifies the USART interrupt source to check.
 *				   This parameter can be one of the following values:
 *				   UART_IT_RXOT： 接收超时，有数据有效且后续4个字符时间内无操作
 *				   UART_IT_IL：	 奇偶 、 溢出 或 帧错误、 或打断中断
 *				   UART_IT_RXNE：接收寄存器非空中断
 *				   UART_IT_TXE：  发送fifo空中断
 *				   UART_IT_MDM： 保留的 Modem寄存器，两线串口实现无此中断源
 *retval None
 *remark：
 *			 UART_IT_RXOT： 	读数据寄存器即可复位中断标志位
 *			 UART_IT_IL：       	读LSR寄存器即可复位中断标志位
 *			 UART_IT_RXNE: 	读数据寄存器即可复位中断标志位
 *			 UART_IT_TXE:  	写数据寄存器或读中断寄存器即可复位中断标志位
 *			 UART_IT_MDM:  	读Modem寄存器即可复位中断标志位
 *			 一般不用刻意清除，有上述操作，中断标志位即自动清除，不影响下次响应；若无则需该函数清楚相应中断寄存器；
 */
void UART_ClearITPendingBit(UART_TypeDef* UARTx, uint16_t UART_IT)
{
	uint8_t data = 0;
	assert_param(IS_UART_PERIPH(USARTx));
	assert_param(IS_UART_GET_IT(UART_IT_FLAG));
	switch(UART_IT)
	{
	case UART_IT_RXOT:
		data = UARTx->DAT_DL_L;
		break;
	case UART_IT_IL:
		data = UARTx->LSR;
		break;
	case UART_IT_RXNE:
		data = UARTx->DAT_DL_L;
		break;
	case UART_IT_TXE:
		data = UARTx->IIR_FCR_DL_D;
		break;
	case UART_IT_MDM:
		data = UARTx->MSR;
		break;
	default:
		break;
	}

}


void UART_ClearITFifo(UART_TypeDef* UARTx)
{
	uint8_t uartdata = 0x00;

	assert_param(IS_UART_PERIPH(USARTx));

	/* clear data reg*/
	UARTx->IIR_FCR_DL_D = 0x06;

}

void UART_IrInit(UART_InitTypeDef* UART_InitStruct)
{

	uint32_t ir_prescale = 0,tmp = 0;

	UART_Init(UART0,UART_InitStruct);

	ir_prescale = UART_InitStruct->Clock_Freq / 38000;

    tmp = READ_REG(PMU->CHIP_CTRL);
    LS_RINS(tmp, POWER_PULSE1_CARR, POWER_PULSE1_CARR_ENABLE);
    WRITE_REG(PMU->CHIP_CTRL, tmp);

    tmp = 0;
    LS_RINS(tmp, POWER_PULSE_CLKSEL, 0x1);
    LS_RINS(tmp, POWER_PULSE_DIV, ir_prescale & 0xffff);
    LS_RINS(tmp, POWER_PULSE_ENABLE, 0x1);
    WRITE_REG(PULSE->PULSE1, tmp);

    UART0->MCR_SCR = 0x80;
    GPIO_WriteBit(GPIOA_BIT, GPIO_Pin_14, Bit_SET);


}



/**
 * brief:  Transmits single data through the USARTx IR peripheral.
 * param:  USARTx: Select the USART or the UART peripheral.
 *   	   This parameter can be one of the following values:
 *   	   USART0, USART1
 * param:  Data: the data to transmit.
 * retval: None
 */
void UART_IrSendData(uint8_t Data)
{
    while (!(READ_BIT(UART0->LSR, UART_LSR_FLAG_TFE)));
    UART_SendData(UART0, Data);
}

uint8_t UART_IrReceiveData(void)
{
	uint8_t data = 0;
	assert_param(IS_UART_PERIPH(USARTx));
	data = UART0->DAT_DL_L ;
	return data;
}


//串口发送函数
void UART_SendChar(UART_TypeDef* UARTx ,uint8 str)
{
	while (!READ_BIT(UARTx->LSR,UART_LSR_FLAG_TFE));
	UART_SendData(UARTx, str);
}


