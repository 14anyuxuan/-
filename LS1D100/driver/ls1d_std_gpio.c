
/********************************************************************
* 文件名:  ls1d6_std_gpio.c
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.08.31
* 说明:    本文件包含GPIO外设的所有接口函数及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/

#include "../include/ls1d_std_gpio.h"
#include "../include/ls1d_std_printf.h"
/******************************************************************************
 *Function Name：	 GPIO_Init
 *Brief： Initializes the GPIOx peripheral according to the specified
 * 		 parameters in the GPIO_InitStruct.
 *Param：
 * 		 GPIOx: where x can be (A.B) to select the GPIO peripheral.
 * 		 GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
 * 		 contains the configuration information for the specified GPIO peripheral.
 *Return value：
 *       None
 *Remarks：
 *     UART0_Remap_GPIO01 与其他 Remap 项共用时，需要与其先与，其余是相或
 *    eg::(LCD_Remap_GPIO | LCD_H23_Remap_GPIO | LCD_H22_Remap_GPIO & GPIO_Remap_UART01)
 *
 ******************************************************************************/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
	uint32_t currentmode = 0x00;

	/* Check the parameters */
	assert_param(IS_GPIO(GPIOx));
	assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
	assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
	assert_param(IS_GPIO_DIRECTION(GPIO_InitStruct->GPIO_Direction));
	currentmode = GPIO_InitStruct->GPIO_Mode;

	if(currentmode != GPIO_MAIN)
	{
		if(currentmode != UART0_Remap_GPIO01 )
		{
			CHIPCTRL |= currentmode;
		}
		else
		{
			CHIPCTRL &= currentmode;
		}
	}

	/*---------------------------- GPIO direction Configuration -----------------------*/

	if(GPIO_InitStruct->GPIO_Direction == GPIO_Mode_IN)
	{
		/* reset input port*/
		GPIOx->GPIO_I  &= ~(GPIO_InitStruct->GPIO_Pin);
		GPIOx->GPIO_OE &= ~(GPIO_InitStruct->GPIO_Pin);
	}
	else
	{
		/* reset output port*/
		GPIOx->GPIO_O  &= ~(GPIO_InitStruct->GPIO_Pin);

		GPIOx->GPIO_OE |= (GPIO_InitStruct->GPIO_Pin);
	}

}

/******************************************************************************
 *Function Name：	 GPIO_Bit_Init
 *Brief： Initializes the GPIOx peripheral according to the specified
 * 		 parameters in the GPIO_InitStruct.
 *Param：
 * 		 GPIOx: where x can be (A.B) to select the GPIO peripheral.
 * 		 GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
 * 		 contains the configuration information for the specified GPIO peripheral.
 *Return value：
 *       None
 *Remarks：
 *     UART0_Remap_GPIO01 与其他外设项共用时，需要与其先与，其余是相或
 *     eg:(LCD_Remap_GPIO | LCD_H23_Remap_GPIO & GPIO_Remap_UART01)
 ******************************************************************************/
void GPIO_BitInit(BITIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
	uint32_t currentmode = 0x00,pos = 0,pinpos = 0;
	uint32_t currentpin = 0x00;
	/* Check the parameters */
	assert_param(IS_GPIO(GPIOx));
	assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
	assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
	assert_param(IS_GPIO_DIRECTION(GPIO_InitStruct->GPIO_Direction));

	currentmode = GPIO_InitStruct->GPIO_Mode;

	if(currentmode != GPIO_MAIN)
	{
		if(currentmode != UART0_Remap_GPIO01 )
		{
			CHIPCTRL |= currentmode;
		}
		else
		{
			CHIPCTRL &= currentmode;
		}
	}
	/*---------------------------- GPIO direction Configuration -----------------------*/

	for(pos = 0;pos<31;pos++)
	{
		pinpos = (0x01 << pos);

		currentpin = GPIO_InitStruct->GPIO_Pin & pinpos;

		if(currentpin == pinpos)
		{
			if(GPIO_InitStruct->GPIO_Direction == GPIO_Mode_IN)
			{
				((BITIO_TypeDef *)(GPIOx + pos))->data  = GPIO_Mode_IN;

			}
			else
			{
				((BITIO_TypeDef *)(GPIOx + pos))->data  = GPIO_Mode_Out;


			}
		}


	}


}


/******************************************************************************
 *Function Name：	 GPIO_Bit_Init
 *Brief： Reads the specified input port pin.
 *Param：
 * 		 GPIOx: where x can be (A.B) to select the GPIO peripheral.
 * 		 GPIO_Pin:  specifies the port(0:31) bit to read.
 *
 *Return value：
 *       The input port pin value.
 *Remarks：
 *
 *
 ******************************************************************************/
uint8_t GPIO_ReadInputDataBit(BITIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
	uint8_t bitstatus = 0x00;

	/* Check the parameters */
	assert_param(IS_GPIO(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));
	int pos = 0,pinpos = 0;
	for(pos = 0;pos<=31;pos++)
	{
		if(GPIO_Pin == (0x01 << pos))
		{
			pinpos = pos;
			break;
		}
	}
	bitstatus = ((BITIO_TypeDef *)(GPIOx + pinpos))->GPIO_IO;
	return bitstatus;
}

/******************************************************************************
 *Function Name：	 GPIO_ReadInputData
 *Brief： Reads the specified input data port.
 *Param：
 * 		 GPIOx: where x can be (A.B) to select the GPIO peripheral.
 *
 *
 *Return value：
 *       The input data port value.
 *Remarks：
 *
 *
 ******************************************************************************/
uint32_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
	/* Check the parameters */
	assert_param(IS_GPIO(GPIOx));
	return GPIOx->GPIO_I;
}




/******************************************************************************
 *Function Name：	 GPIO_ReadOutputDataBit
 *Brief： Reads the specified input data port bit.
 *Param：
 * 		 GPIOx: where x can be (A.B) to select the GPIO peripheral.
 *		 GPIO_Pin:  specifies the port bit to read.
 *
 *Return value：
 *       The output data port value.
 *Remarks：
 *
  ******************************************************************************/
uint32_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
	/* Check the parameters */
	assert_param(IS_GPIO(GPIOx));
	return  GPIOx->GPIO_O;
}



/******************************************************************************
 *Function Name：	 GPIO_WriteBit
 *Brief：Sets or clears the selected data port bit.
 *Param：
 * 		 GPIOx: where x can be (A.B) to select the GPIO peripheral.
 *		 GPIO_Pin:  specifies the port bit to be written.
 *		 Value: specifies the value to be written to the selected bit.
 *
 *
 *Return value：
 *       none
 *Remarks：
 *		Bit_RESET: to clear the port pin
 *		Bit_SET: to set the port pin
 *
 ******************************************************************************/
void GPIO_WriteBit(BITIO_TypeDef* GPIOx, uint32_t GPIO_Pin, BitAction Value)
{

	 assert_param(IS_GPIO(GPIOx));
	 assert_param(IS_GPIO_PIN(GPIO_Pin));
	 assert_param(IS_GPIO_BIT_ACTION(Value));
	 int pos = 0,pinpos = 0;
	 for(pos = 0;pos<= 31;pos++)
	 {
		 if(GPIO_Pin == (0x01 << pos))
		 {
			pinpos = pos;
			break;
		 }
	 }
	 if(Bit_RESET == Value)
	 {
		 ((BITIO_TypeDef *)(GPIOx + pinpos))->data = 0x2;
	 }
	 else
	 {
		 ((BITIO_TypeDef *)(GPIOx + pinpos))->data = 0x3;
	 }
}

/******************************************************************************
 *Function Name：	 GPIO_WriteData
 *Brief：Writes data to the specified GPIO data port.
 *Param：
 * 		 GPIOx: where x can be (A.B) to select the GPIO peripheral.
 *		 NewState: specifies the value to be written to the port output data register.
 *Return value：
 *       none
 *Remarks：
 *
 ******************************************************************************/
void GPIO_WriteData(GPIO_TypeDef* GPIOx, uint32_t Value)
{
	/* Check the parameters */
	assert_param(IS_GPIO(GPIOx));

	GPIOx->GPIO_O = Value;
}

/******************************************************************************
 *Function Name：	 GPIO_PinRemapConfig
 *Brief： Changes the mapping of the specified pin.
 *Param：
 * 		 GPIO_Remap: selects the pin to remap
 *		 State: new state of the port pin remapping.
 *Return value：
 *       none
 *Remarks：
 *		 GPIO_Remap:
 *		 	GPIO01_Remap_UART0 			 	;	UART0 Alternate GPIO01 Function mapping
 *  	   	GPIO_Remap_LCD_H23 				;	LCD[23] Alternate Function mapping
 *			GPIO_Remap_LCD_H22 			 	;	LCD[22] Function mapping
 *			GPIO_Remap_LCD_H21 			 	;	LCD[21] Alternate Function mapping
 *			GPIO_Remap_LCD_H20 			 	;	LCD[20] Alternate Function mapping
 *			GPIO_Remap_SPI 				 	;	SPI Alternate Function mapping
 *			GPIO_Remap_PT12 			 	;	PT12 LoadT SenseT Alternate Function mapping
 *			GPIO_Remap_PT34 			 	;	PT34 Alternate Function mapping
 *			GPIO_Remap_KEY 				 	;	KEY_I Alternate Function mapping
 *			GPIO_Remap_EMP 				 	;	EMP_I Alternate Function mapping
 *			GPIO_Remap_UART0 			    ;	UART0 Alternate Function mapping
 *			GPIO_Remap_UART1 			 	;	UART1 Alternate Function mapping
 *			GPIO_Remap_ADC1 			 	;	ADC1 Alternate Function mapping
 *			GPIO_Remap_I2C  			 	;	I2C Alternate Function mapping
 *
 *			State:
 *				 ENABLE: GPIO remap to Peripheral
 *				 DISABLE: Peripheral remap to GPIO
 ******************************************************************************/
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState State)
{
	uint32_t currentmode = 0x00;
	/* Check the parameters */
	assert_param(IS_GPIO_REMAP(GPIO_Remap));
	assert_param(IS_FUNCTIONAL_STATE(State));
	currentmode = GPIO_Remap;

	if(currentmode != GPIO01_Remap_UART0)
	{
		if(State != DISABLE)
		{
			CHIPCTRL &= currentmode;//置0为功能IO
		}
		else
		{
			CHIPCTRL |= ~currentmode;//置1为普通IO
		}
	}
	else
	{
		if(State != DISABLE)
		{
			CHIPCTRL |= currentmode;//置1为功能IO
		}
		else
		{
			CHIPCTRL &= ~currentmode;//置0为普通IO
		}
	}
}



