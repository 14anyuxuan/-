/*
 * UserGpio.c
 *
 *  Created on: 2021年11月5日
 *      Author: lixin
 */
#include "GlobalDef.h"
#include "UserGpio.h"

#define	 LCD_GPIO_PIN 				GPIO_Pin_2
#define	 LCD_GPIO_PIN_PORT 			GPIOA_BIT

#define	 MODULE_GPIO_PIN 			GPIO_Pin_1
#define	 MODULE_GPIO_PIN_PORT 		GPIOA_BIT

//#define	 VBATFANG_GPIO_PIN 			GPIO_Pin_5
//#define	 VBATFANG_GPIO_PIN_PORT 	GPIOA_BIT

//#define	 LED_GPIO_PIN 				GPIO_Pin_3
//#define	 LED_GPIO_PIN_PORT 			GPIOA_BIT

#define	 VBAT_GPIO_PIN 				GPIO_Pin_3
#define	 VBAT_GPIO_PIN_PORT 		GPIOA_BIT

#define	 EEPROM_GPIO_PIN 			GPIO_Pin_0
#define	 EEPROM_GPIO_PIN_PORT 		GPIOA_BIT

#define	 NB_GPIO_PIN 				GPIO_Pin_12	//27
#define	 NB_GPIO_PIN_PORT 			GPIOA_BIT

#define	 NTC_GPIO_PIN 				GPIO_Pin_23	//27
#define	 NTC_GPIO_PIN_PORT 			GPIOA_BIT


void GPIOInit(void)
{

	GPIO_PinRemapConfig((GPIO_Remap_UART0 & GPIO_Remap_UART1 & GPIO_Remap_SPI), ENABLE);

}

void GPIO_LowPower()
{
  	GPIO_InitTypeDef GPIO_InitStruct;

 	//GPIO_PinRemapConfig(GPIO_Remap_ADC0& GPIO_Remap_ADC1,DISABLE);
  	//GPIO_PinRemapConfig((GPIO_Remap_ADC1&GPIO_Remap_ADC0), DISABLE);
	POWER_RamOffConfig(SET);
 	/*设置sonar模块掉电，mbus模块掉电 */
 	POWER_SonarOffConfig(SET);
 	POWER_MbusOffConfig(SET);
#if 0
 	GPIO_PinRemapConfig((GPIO_Remap_LCD_ALL & GPIO_Remap_LCD_H23 & GPIO_Remap_LCD_H22 & GPIO_Remap_LCD_H21 & GPIO_Remap_LCD_H20), DISABLE);
 	/* LCD gpio low */
 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_28|GPIO_Pin_29|GPIO_Pin_30| GPIO_Pin_31;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_28,RESET);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_29,RESET);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_30,RESET);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_31,RESET);

 	/*LCD */
 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2| GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5| GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8| GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_5| GPIO_Pin_6;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
 	GPIO_BitInit(GPIOB_BIT, &GPIO_InitStruct);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_0,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_1,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_2,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_3,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_4,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_5,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_6,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_7,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_8,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_9,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_10,RESET);



#if 0
 	/*jtag gpio   */
// 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_11,RESET);
//	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_12,RESET);
// 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_13,RESET);
// 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_14,SET);
// 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_15,RESET);
#endif

 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_16,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_17,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_18,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_19,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_20,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_21,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_22,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_23,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_24,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_25,RESET);
 	GPIO_WriteBit(GPIOB_BIT,GPIO_Pin_26,RESET);

#if 0
 	/* ADC gpio low */
 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_21|GPIO_Pin_22;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_21,SET);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_22,SET);
#endif

#endif

#if 0
 	/* uart1 gpio low */
 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_10,RESET);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_11,SET);

 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_8,RESET);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_9,SET);
#endif

 	/* uart1 gpio low */
// 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
// 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
// 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
// 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
// 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_10,SET);//reset
// 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_11,SET);


 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
// 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_8,SET);//reset
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_9,SET);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_11,SET);


 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_IN;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
 	GPIO_PinRemapConfig((GPIO_Remap_UART0 & GPIO_Remap_UART1), DISABLE);


}

/* GPIO LCD模式恢复  */
void GPIO_LCDResume()
{
//  GPIO_InitTypeDef GPIO_InitStruct;
 	GPIO_PinRemapConfig((GPIO_Remap_LCD_ALL & GPIO_Remap_LCD_H23 & \
 			GPIO_Remap_LCD_H22 & GPIO_Remap_LCD_H21 & GPIO_Remap_LCD_H20), ENABLE);
// 	/* LCD  */
// 	GPIO_InitStruct.GPIO_Pin = LCD_GPIO_PIN;
// 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
// 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
// 	GPIO_BitInit(LCD_GPIO_PIN_PORT, &GPIO_InitStruct);
// 	GPIO_WriteBit(LCD_GPIO_PIN_PORT,GPIO_InitStruct.GPIO_Pin,SET);
}

/* GPIO ADC 模式恢复  */
void GPIO_AdcResume()
{
//  GPIO_InitTypeDef GPIO_InitStruct;
  	//GPIO_PinRemapConfig((GPIO_Remap_ADC1&GPIO_Remap_ADC0), ENABLE);
	GPIO_PinRemapConfig((GPIO_Remap_ADC0), ENABLE);

// 	GPIO_InitStruct.GPIO_Pin = VBAT_GPIO_PIN;
// 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
// 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
// 	GPIO_BitInit(VBAT_GPIO_PIN_PORT, &GPIO_InitStruct);
// 	GPIO_WriteBit(VBAT_GPIO_PIN_PORT,GPIO_InitStruct.GPIO_Pin,SET);
//  ADC_Init();

}
/* GPIO 串口去默认初始化  */
void GPIO_Uart1ReInit()
{
	POWER_MbusOffConfig(RESET);
	CLOCK_DelayUs(300);
 	GPIO_PinRemapConfig(GPIO_Remap_UART1, ENABLE);
 	Uart1_Init(9600);
}
/* GPIO 串口0初始化  */
void GPIO_Uart0Resume()
{
 	GPIO_PinRemapConfig(GPIO_Remap_UART0, ENABLE);
	CLOCK_DelayUs(200);
// 	Uart0_Init(115200,ir_flag);
#if UART0_IR_MODE
	Uart0_Init(2400);
#else
	Uart0_Init(115200);
#endif

}



/* GPIO 串口1初始化  */
void GPIO_Uart1Resume()
{

	POWER_MbusOffConfig(RESET);
	CLOCK_DelayUs(300);
 	GPIO_PinRemapConfig(GPIO_Remap_UART1, ENABLE);
	//GPIO_PinRemapConfig((GPIO_Remap_UART0), ENABLE);
 	//UartInit(115200,9600);
 	Uart1_Init(4800);
}

void Uart0_LowPower()
{
//	POWER_RamOffConfig(SET);
#if 0
  	GPIO_InitTypeDef GPIO_InitStruct;
 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_14;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
// 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_8,SET);//reset
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_9,SET);
	GPIO_WriteBit(GPIOA_BIT, GPIO_Pin_14, Bit_SET);
 	GPIO_PinRemapConfig((GPIO_Remap_UART0), DISABLE);
// 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
// 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
// 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_IN;
// 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);

 	EXTI_InitTypeDef  EXTI_InitStruct = {0};
//  EXTI_StructInit(&EXTI_InitStruct);
  	EXTI_InitStruct.EXTI_GPIO = GPIO_Pin_8;
  	EXTI_InitStruct.EXTI_GpioCmd = ENABLE;
  	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_High;
  	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Edge;
  	EXTI_ClearITPendingBit(IRQ_GPIO_ALL);
    EXTI_Init(&EXTI_InitStruct);
#else

  	GPIO_InitTypeDef GPIO_InitStruct;
 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_14;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
// 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_8,SET);//reset
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_9,SET);
 	GPIO_WriteBit(GPIOA_BIT, GPIO_Pin_14, Bit_RESET);
 	GPIO_PinRemapConfig((GPIO_Remap_UART0), DISABLE);

 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_IN;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
#endif

}
void Uart1_LowPower()
{
 	POWER_MbusOffConfig(SET);
//	POWER_RamOffConfig(SET);
  	GPIO_InitTypeDef GPIO_InitStruct;
 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_11,SET);

 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_IN;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);

 	GPIO_PinRemapConfig((GPIO_Remap_UART1), DISABLE);
}

void I2C_LowPower()
{

	EEPROM_OFF();
	GPIO_PinRemapConfig(GPIO_Remap_I2C, DISABLE);
//	FLASH_OFF();
  	GPIO_InitTypeDef GPIO_InitStruct;
 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_4,SET);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_5,SET);

}


void GPIO_I2cResume()
{
	I2C_InitTypeDef  I2C_InitStruct_Data = {0};
 	GPIO_PinRemapConfig(GPIO_Remap_I2C, ENABLE);
	I2C_StructInit(&I2C_InitStruct_Data);
	I2C_Init(I2C,&I2C_InitStruct_Data);
	EEPROM_ON();
//	CLOCK_DelayUs(200);
}



void SPI_LowPower()
{
#ifdef Spi_W25Q16
	GPIO_PinRemapConfig(GPIO_Remap_SPI, DISABLE);
	FLASH_OFF();
  	GPIO_InitTypeDef GPIO_InitStruct;
 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_23|GPIO_Pin_24|GPIO_Pin_25| GPIO_Pin_26;
 	GPIO_InitStruct.GPIO_Mode = GPIO_MAIN;
 	GPIO_InitStruct.GPIO_Direction = GPIO_Mode_Out;
 	GPIO_BitInit(GPIOA_BIT, &GPIO_InitStruct);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_23,RESET);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_24,RESET);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_25,RESET);
 	GPIO_WriteBit(GPIOA_BIT,GPIO_Pin_26,RESET);
#endif
}

void GPIO_SpiResume()
{
#ifdef Spi_W25Q16
	SPI_InitTypeDef SPI_InitStruct_Data = {0};
	FLASH_ON();
 	GPIO_PinRemapConfig(GPIO_Remap_SPI, ENABLE);
	SPI_StructInit(&SPI_InitStruct_Data);
 	SPI_Init(SPI,&SPI_InitStruct_Data);
//	CLOCK_DelayUs(200);
#endif
}
