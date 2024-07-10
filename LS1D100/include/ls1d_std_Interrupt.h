/********************************************************************
* 文件名:  ls1d6_std_interrupt.h
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.12.18
* 说明:    本文件包中断处理接口的底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef _Interrupt_H_
#define _Interrupt_H_

#include "ls1d.h"
#include "ls1d_std_exti.h"

#define  IRQ_GPIO_A0        EXTI_GPIO0
#define  IRQ_GPIO_A1        EXTI_GPIO1
#define  IRQ_GPIO_A2        EXTI_GPIO2
#define  IRQ_GPIO_A3        EXTI_GPIO3
#define  IRQ_GPIO_A4        EXTI_GPIO4
#define  IRQ_GPIO_A5        EXTI_GPIO5
#define  IRQ_GPIO_A6        EXTI_GPIO6
#define  IRQ_GPIO_A7        EXTI_GPIO7
#define  IRQ_GPIO_A8        EXTI_GPIO8
#define  IRQ_GPIO_A9        EXTI_GPIO9
#define  IRQ_GPIO_A10       EXTI_GPIO10
#define  IRQ_GPIO_A11       EXTI_GPIO11
#define  IRQ_GPIO_A12       EXTI_GPIO12
#define  IRQ_GPIO_A13       EXTI_GPIO13
#define  IRQ_GPIO_A14       EXTI_GPIO14
#define  IRQ_GPIO_A15       EXTI_GPIO15
#define  IRQ_GPIO_B0        EXTI_GPIO16
#define  IRQ_GPIO_B1        EXTI_GPIO17
#define  IRQ_GPIO_B2        EXTI_GPIO18
#define  IRQ_GPIO_B3        EXTI_GPIO19
#define  IRQ_GPIO_B4        EXTI_GPIO20
#define  IRQ_GPIO_B5        EXTI_GPIO21
#define  IRQ_GPIO_B6        EXTI_GPIO22
#define  IRQ_GPIO_B7        EXTI_GPIO23
#define  IRQ_GPIO_B8        EXTI_GPIO24
#define  IRQ_GPIO_B9        EXTI_GPIO25
#define  IRQ_GPIO_B10       EXTI_GPIO26
#define  IRQ_GPIO_B11       EXTI_GPIO27
#define  IRQ_GPIO_B12       EXTI_GPIO28
#define  IRQ_GPIO_B13       EXTI_GPIO29
#define  IRQ_GPIO_B14       EXTI_GPIO30
#define  IRQ_GPIO_B15       EXTI_GPIO31
#define  IRQ_GPIO_ALL       EXTI_GPIOALL


void Soft0_IRQHandler(void);
void Soft1_IRQHandler(void);
void Wake_IRQHandler(void);
void ResValid_IRQHandler(void);
void BatFail_IRQHandler(void);
void C32kFail_IRQHandler(void);
void C8mFail_IRQHandler(void);
void Key_IRQHandler(void);
void Ring_IRQHandler(void);
void Rtc_IRQHandler(void);

void TIMER_IRQHandler(void);
void I2C_IRQHandler(void);
void UART0_IRQHandler(void);
void FLASH_IRQHandler(void);
void SPI_IRQHandler(void);
void ADC_IRQHandler(void);

void Exint_IRQHandler(void);
void ExtGpioA0_IRQHandler(void);
void ExtGpioA1_IRQHandler(void);
void ExtGpioA2_IRQHandler(void);
void ExtGpioA3_IRQHandler(void);
void ExtGpioA4_IRQHandler(void);
void ExtGpioA5_IRQHandler(void);
void ExtGpioA6_IRQHandler(void);
void ExtGpioA8_IRQHandler(void);
void ExtGpioA7_IRQHandler(void);
void ExtGpioA9_IRQHandler(void);
void ExtGpioA10_IRQHandler(void);
void ExtGpioA11_IRQHandler(void);
void ExtGpioA12_IRQHandler(void);
void ExtGpioA13_IRQHandler(void);
void ExtGpioA14_IRQHandler(void);
void ExtGpioA15_IRQHandler(void);

void ExtGpioB0_IRQHandler(void);
void ExtGpioB1_IRQHandler(void);
void ExtGpioB2_IRQHandler(void);
void ExtGpioB3_IRQHandler(void);
void ExtGpioB4_IRQHandler(void);
void ExtGpioB5_IRQHandler(void);
void ExtGpioB6_IRQHandler(void);
void ExtGpioB8_IRQHandler(void);
void ExtGpioB7_IRQHandler(void);
void ExtGpioB9_IRQHandler(void);
void ExtGpioB10_IRQHandler(void);
void ExtGpioB11_IRQHandler(void);
void ExtGpioB12_IRQHandler(void);
void ExtGpioB13_IRQHandler(void);
void ExtGpioB14_IRQHandler(void);
void ExtGpioB15_IRQHandler(void);


#endif
