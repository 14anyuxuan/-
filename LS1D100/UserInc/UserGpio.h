/*
 * UserGpio.h
 *
 *  Created on: 2021��11��5��
 *      Author: lixin
 */

#ifndef USERINC_USERGPIO_H_
#define USERINC_USERGPIO_H_

#include "../include/ls1d_std_clock.h"
#include "../include/ls1d_std_gpio.h"
#include "../include/ls1d_std_lcd.h"
#include "../include/ls1d_std_printf.h"
#include "../include/ls1d_std_spi.h"
#include "../include/ls1d_std_i2c.h"
void GPIOInit(void);
void GPIO_LowPower();
void GPIO_Uart1ReInit();
void GPIO_Uart1Resume();
void GPIO_Uart0Resume();
void GPIO_SpiResume();
void Uart0_LowPower();
void Uart1_LowPower();
void SPI_LowPower();
void I2C_LowPower();
void GPIO_I2cResume();

#endif /* USERINC_USERGPIO_H_ */









