
/********************************************************************
* 文件名:	ls1d6_std_interrupt.c
* 版本：		V1.0
* 作者:		李鑫
* 日期:		2021.11.31
* 说明:		本文件包含interrupt的所有接口函数及宏定义
* 版权:		龙芯中科（太原）技术有限公司
********************************************************************/

#include "../include/ls1d_std_cslreg.h"
#include "../include/ls1d_std_rtc.h"
#include "../include/ls1d_std_timer.h"
#include"Main.h"


uint8 g_Uart1Cnt=0;
uint8 g_Rx1Buf[100]={0};

void (* const Ext_IrqHandle[32])(void);
extern uint32_t key_mode;
__attribute__((weak)) void Soft0_IRQHandler(void)
{
}
__attribute__((weak)) void Soft1_IRQHandler(void)
{
}

void Wake_IRQHandler(void)
{
	MEASURE_ClearIT(MEASURE_INT_WAKE);
	MEASURE_ITConfig(MEASURE_INT_WAKE,DISABLE);
}

__attribute__((weak)) void ResValid_IRQHandler(void)
{
	//resvalid_flag = 1;
	MEASURE_ClearResITAndReadFlag();
}

__attribute__((weak)) void BatFail_IRQHandler(void)
{

	MEASURE_ClearIT(MEASURE_INT_BAT_FAIL);
}

__attribute__((weak)) void C32kFail_IRQHandler(void)
{
	BEBUG_IRQ();
	MEASURE_ClearIT(MEASURE_INT_C32K_FAIL);
}

__attribute__((weak)) void C8mFail_IRQHandler(void)
{
	BEBUG_IRQ();
	MEASURE_ClearIT(MEASURE_INT_C8M_FAIL);
}


__attribute__((weak)) void Key_IRQHandler(void)
{
		/* 清除key中断标志位 	*/
	MEASURE_ClearIT(MEASURE_INT_KEY);
}



__attribute__((weak)) void Ring_IRQHandler(void)
{
	//TODO
	//BEBUG_IRQ();

	MEASURE_ClearIT(MEASURE_INT_RING);
}


__attribute__((weak)) void Rtc_IRQHandler(void)
{
//	BEBUG_IRQ();
//	 RTC_time g_time;
//	//RTC_GetDateTime(&g_time);
//	RTC_GetDate(&g_time);
//	system_date.year = g_time.year;
//	system_date.mon = g_time.mon;
//	system_date.day = g_time.day;

	MEASURE_ClearIT(MEASURE_INT_RTC);
}

//int timetick = 0;
//extern int mutex_test;

__attribute__((weak)) void TIMER_IRQHandler(void)
{
	//BEBUG_IRQ();
 	 //systick++;
//	Open_Mutex(&mutex_test);
//	timetick++;
////	Release_Mutex(&mutex_test);
//	printf("T:%d\r\n",timetick);


	TIM_ClearIT(TIMER,TIM_FLAG_Trigger);
}


__attribute__((weak)) void CpuTimer_IRQHandler(void)
{
	CLOCK_ClearCpuTimerIT();
//    printf("Core Timer clear interrupt..\n");
}

__attribute__((weak)) void I2C_IRQHandler(void)
{
#if 0
	STS=1;
	I2C_ClearIT(I2C);
#endif

}


__attribute__((weak)) void UART1_IRQHandler(void)
{
	//TODO
	//BEBUG_IRQ();
	if(UART_GetITStatus(UART1,UART_IT_RXOT) || UART_GetITStatus(UART1,UART_IT_RXNE))
	{
		while(UART_GetFlagStatus(UART1,UART_LSR_FLAG_RXNE))
		{
			g_Rx1Buf[g_Uart1Cnt++] = UART1->DAT_DL_L;
		}


	}

	UART_ClearIT(UART1);

}

__attribute__((weak)) void UART0_IRQHandler(void)
{
	uint8 dat_recv;
 	if(UART_GetITStatus(UART0,UART_IT_RXOT) || UART_GetITStatus(UART0,UART_IT_RXNE))
	{
		while(UART_GetFlagStatus(UART0,UART_LSR_FLAG_RXNE))
		{
			 printf("recv data:%c\r\n",UART0->DAT_DL_L) ;
		}
// 		printf("tty2\r\n");
	}

	UART_ClearIT(UART0);
}

__attribute__((weak)) void FLASH_IRQHandler(void)
{
	//TODO
	BEBUG_IRQ();
#if 0
	if( FLASH->STS & 0x04 )
	{
		Flash_pe=1;
//		printf("\r\n FLASH pe_end \r\n ");
//		printf("\r\n FLASH 0x000100:%8x H\r\n ",*(volatile unsigned int *)(0xbf000100));
	}
	else if( FLASH->STS & 0x08 )
	{
		Flash_pe=2;
//		printf("\r\n FLASH no_permission \r\n");
	}
#endif

	// FLASH->CMD &=0x0FFFFFFF;
	FLASH_ClearIT();
}

__attribute__((weak)) void SPI_IRQHandler(void)
{
	//TODO
 	BEBUG_IRQ();
#if 0
	printf("\r\n 0 SPI IRQ SPI->SPCR:%x H \r\n",SPI->SPCR);
	while((SPI->SPCR & 0x10)){CLOCK_DelayMs(100);}
	if(SPI->SPCR & 0x04)
	{
		printf("\r\n SPI IRQ Tx OK \r\n");
	}
	else if(SPI->SPCR & 0x02)
	{
		printf("\r\n SPI IRQ Rx need read: %x \r\n",SPI->DATA);
		// data = SPI->DATA;
	}
	else if(SPI->SPCR & 0x01)
	{
		printf("\r\n SPI IRQ Rx OK \r\n");
	}
	SPI->SPCR |=0x80;	//清除控制器中断申请

	SET_BIT(INT->INT_CLR,1<<IRQ_SPI);	//清除中断标记位

	printf("\r\n 1 SPI IRQ SPI->SPCR:%x H \r\n",SPI->SPCR);
	printf("\r\n<< Exit %s >>\r\n INT->INT_OUT :%x h\r\n",__FUNCTION__, INT->INT_OUT);
#endif

#ifdef UserSPI
	SPI_ClearIT(SPI);
#else
	SPI->SPCR |=0x80;	//清除控制器中断申请
	SET_BIT(INT->INT_CLR,1<<5);	//清除中断标记位
#endif	
}

__attribute__((weak)) void ADC_IRQHandler(void)
{
	//TODO
	//BEBUG_IRQ();
	// printf("\r\n adc int ok int_out:%x h\r\n", intreg);
	g_adc_data = (ADC->ADC_DATA) & 0x0FFF;
	//printf("\r\n adc :%d mV\r\n", ADC_Mv(g_adc_data)); //测量结果，取12位有效数据

	// SET_BIT(INT->INT_CLR, IRQ_ADC); //清除中断标记位
	SET_BIT(INT->INT_CLR, IRQ_ADC); //清除中断标记位
	// SET_BIT(INT->INT_CLR, ADC_INT_CLR); //清除中断标记位
	// INT->INT_CLR |= ADC_INT_CLR;	//清除中断标记位
	//printf("\r\n Exit %s \r\n INT->INT_OUT :%x h\r\n",__FUNCTION__, INT->INT_OUT);
}

__attribute__((weak)) void Exint_IRQHandler(void)
{
	uint32 regsrc;// = EXTI->EXINT_SRC;
	uint32 regen;// = EXTI->EXINT_SRC;
	uint32 irq_no = 0;
	//BEBUG_IRQ();
	regsrc = EXTI->EXINT_SRC;
	regen = EXTI->EXINT_EN;
	regsrc = (regsrc & regen);
	asm("nop");
	//printf("\r\n EXTI->EXINT_SRC:%8x h\r\n",EXTI->EXINT_SRC);

	for(irq_no = 0; irq_no < 32; irq_no++)
    {
    	if((regsrc>>irq_no) & 0x1)
    	{
    	 	//printf("\r\n TRQ_ irq_no:%x h\r\n",(irq_no));
			Ext_IrqHandle[irq_no]();//进入中断处理程序
    	}
    }
	  /* 参考北京的程序 */
	MEASURE_ClearIT(MEASURE_INT_EXINT);
}

__attribute__((weak)) void ExtGpioA0_IRQHandler(void)
{
	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A0);
}
__attribute__((weak)) void ExtGpioA1_IRQHandler(void)
{
	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A1);
}
__attribute__((weak)) void ExtGpioA2_IRQHandler(void)
{
	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A2);
}
__attribute__((weak)) void ExtGpioA3_IRQHandler(void)
{
	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A3);
}
__attribute__((weak)) void ExtGpioA4_IRQHandler(void)
{
	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A4);
}
__attribute__((weak)) void ExtGpioA5_IRQHandler(void)
{
	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A5);
}
__attribute__((weak)) void ExtGpioA6_IRQHandler(void)
{
	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A6);
}
__attribute__((weak)) void ExtGpioA7_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A7);
}
__attribute__((weak)) void ExtGpioA8_IRQHandler(void)
{
//	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A8);
}
__attribute__((weak)) void ExtGpioA9_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A9);
}
__attribute__((weak)) void ExtGpioA10_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A10);
}
__attribute__((weak)) void ExtGpioA11_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A11);
}
__attribute__((weak)) void ExtGpioA12_IRQHandler(void)
{
	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A12);
}
__attribute__((weak)) void ExtGpioA13_IRQHandler(void)
{
//	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A13);
}
__attribute__((weak)) void ExtGpioA14_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A14);
}
__attribute__((weak)) void ExtGpioA15_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_A15 );
}

__attribute__((weak)) void ExtGpioB0_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B0);
}
__attribute__((weak)) void ExtGpioB1_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B1);
}
__attribute__((weak)) void ExtGpioB2_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B2);
}
__attribute__((weak)) void ExtGpioB3_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B3);
}
__attribute__((weak)) void ExtGpioB4_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B4);
}
__attribute__((weak)) void ExtGpioB5_IRQHandler(void)
{
	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B5);
}
__attribute__((weak)) void ExtGpioB6_IRQHandler(void)
{
	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B6);
}
__attribute__((weak)) void ExtGpioB7_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B7);
}
__attribute__((weak)) void ExtGpioB8_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B8);
}
__attribute__((weak)) void ExtGpioB9_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B9);
}
__attribute__((weak)) void ExtGpioB10_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B10);
}
__attribute__((weak)) void ExtGpioB11_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B11);
}
__attribute__((weak)) void ExtGpioB12_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B12);
}
__attribute__((weak)) void ExtGpioB13_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B13);
}
__attribute__((weak)) void ExtGpioB14_IRQHandler(void)
{

	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B14);
}
__attribute__((weak)) void ExtGpioB15_IRQHandler(void)
{
	BEBUG_IRQ();
	//清除中断标记位
	EXTI_ClearITPendingBit(IRQ_GPIO_B15);
}

__attribute__((weak)) void (* const Ext_IrqHandle[32])(void) = {
	ExtGpioA0_IRQHandler,
   ExtGpioA1_IRQHandler,
   ExtGpioA2_IRQHandler,
   ExtGpioA3_IRQHandler,
   ExtGpioA4_IRQHandler,
   ExtGpioA5_IRQHandler,
   ExtGpioA6_IRQHandler,
   ExtGpioA7_IRQHandler,
   ExtGpioA8_IRQHandler,
   ExtGpioA9_IRQHandler,
   ExtGpioA10_IRQHandler,
   ExtGpioA11_IRQHandler,
   ExtGpioA12_IRQHandler,
   ExtGpioA13_IRQHandler,
   ExtGpioA14_IRQHandler,
   ExtGpioA15_IRQHandler,
   ExtGpioB0_IRQHandler,
   ExtGpioB1_IRQHandler,
   ExtGpioB2_IRQHandler,
   ExtGpioB3_IRQHandler,
   ExtGpioB4_IRQHandler,
   ExtGpioB5_IRQHandler,
   ExtGpioB6_IRQHandler,
   ExtGpioB7_IRQHandler,
   ExtGpioB8_IRQHandler,
   ExtGpioB9_IRQHandler,
   ExtGpioB10_IRQHandler,
   ExtGpioB11_IRQHandler,
   ExtGpioB12_IRQHandler,
   ExtGpioB13_IRQHandler,
   ExtGpioB14_IRQHandler,
   ExtGpioB15_IRQHandler,
};

