
/********************************************************************
* 文件名:  ls1d6_std_exti.c
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.11.31
* 说明:    本文件包含中断的所有接口函数及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#include "../include/ls1d_std_exti.h"



/******************************************************************************
 *Function Name：	 EXTI_EnableInt
 *Brief：检测中断是否打开
 *
 *Param：
 * 		None
 *
 *Return value：
 *     1 全局中断打开    0 全局中断关闭
 *Remarks：
 *
 *
 ******************************************************************************/
uint8 EXTI_IsGlobalIntOpen(void)
{
    unsigned int val = 0;
    asm volatile("csrrd  %0, 0x0":"=r" (val));

    return val & 0x4;
}

/******************************************************************************
 *Function Name：	 EXTI_EnableInt
 *Brief：关闭总中断函数
 *
 *Param：
 * 		None
 *
 *Return value：
 *      None
 *Remarks：
 *
 *
 ******************************************************************************/
void EXTI_DisableInt(void)
{
    asm volatile(					\
                "li.w $r12, 0x4;\n"\
                "csrxchg $r0, $r12, 0x0;\n"\
		        :::"$r12"
                );
}

/******************************************************************************
 *Function Name：	 EXTI_EnableInt
 *Brief：打开总中断函数
 *
 *Param：
 * 		None
 *
 *Return value：
 *      None
 *Remarks：
 *
 *
 ******************************************************************************/
void EXTI_EnableInt(void)
{
    asm volatile(					\
                "li.w $r12, 0x4;\n"\
                "csrxchg $r12, $r12, 0x0;\n"\
		        :::"$r12"
                );
}
/******************************************************************************
 *Function Name：	 EXTI_DeInit
 *Brief：Deinitializes the EXTI peripheral registers to their default reset values.
 *
 *Param：
 * 		None
 *
 *Return value：
 *      None
 *Remarks：
 *
 *
 ******************************************************************************/
void EXTI_DeInit(void)
{
  EXTI->EXINT_SRC = 0x00000000;
  EXTI->EXINT_EDGE = 0x00000000;
  EXTI->EXINT_POL = 0x00000000;
  EXTI->EXINT_EN = 0x00000000;
}

/******************************************************************************
 *Function Name：	 EXTI_Init
 *Brief： Initializes the EXTI peripheral according to the specified parameters in
 *		 the EXTI_InitStruct.
 *
 *Param：
 * 		EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure
 * 		that contains the configuration information for the EXTI peripheral.
 *
 *Return value：
 *      None
 *Remarks：
 *		GPIOA[0:15]  ->  0:15
 *		GPIOB[0:15]  ->  16:31
 *
 ******************************************************************************/
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
  assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
  assert_param(IS_EXTI_GPIO(EXTI_InitStruct->EXTI_GPIO));
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));

  if (EXTI_InitStruct->EXTI_GpioCmd != DISABLE)
  {

	  /* enable external interrupt wake cpu */
	 PMU->COMMAND &=~((uint32)(1<<25));
	 PMU->COMMAND |=(uint32)(1<<25);

	 if(EXTI_InitStruct->EXTI_Mode == EXTI_Mode_Level)
	 {
		  CLEAR_BIT(EXTI->EXINT_EDGE,EXTI_InitStruct->EXTI_GPIO);
	 }
	 else
	 {
		  SET_BIT(EXTI->EXINT_EDGE,EXTI_InitStruct->EXTI_GPIO);
	 }

	 SET_BIT(EXTI->EXINT_EN,EXTI_InitStruct->EXTI_GPIO);

     /* Clear exint pol configuration */
     EXTI->EXINT_POL &= ~EXTI_InitStruct->EXTI_GPIO;
     /* Select the trigger for the selected external interrupts */
     if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_High)
     {
    	SET_BIT(EXTI->EXINT_POL,EXTI_InitStruct->EXTI_GPIO);
     }
     else
     {
        CLEAR_BIT(EXTI->EXINT_POL,EXTI_InitStruct->EXTI_GPIO);
     }

     SET_BIT(EXTI->EXINT_SRC,EXTI_InitStruct->EXTI_GPIO);
  }
  else
  {
	  CLEAR_BIT(EXTI->EXINT_EN,EXTI_InitStruct->EXTI_GPIO);
  }
}

/******************************************************************************
 *Function Name：  EXTI_StructInit
 *Brief： Fills each EXTI_InitStruct member with its reset value.
 *
 *Param：
 *		 EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure which will
 *       be initialized.
 *
 *Return value：
 *      None
 *Remarks：
 *
 *		GPIOA[0:15]  ->  0:15
 *		GPIOA[0:15]  ->  16:31
 ******************************************************************************/
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_GPIO = EXTI_GPIONONE;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Edge;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Rising_High;
  EXTI_InitStruct->EXTI_GpioCmd = DISABLE;
}

/**
  * @brief  Generates a Software interrupt.
  * @param  EXTI_GPIO: specifies the EXTI lines to be enabled or disabled.
  *   This parameter can be any combination of EXTI_GPIOx where x can be (0..19).
  * @retval None
  */

/******************************************************************************
 *Function Name：  EXTI_SoftInterruptStart
 *Brief：start a Software interrupt.
 *
 *Param：
 *		 none
 *
 *Return value：
 *      None
 *Remarks：
 *
 *
 ******************************************************************************/
void EXTI_SoftInterruptStart(void)
{
    asm volatile(					\
                "li.w $r12, 0x1;\n"\
                "csrxchg $r12, $r12, 0x4;\n"\
		        :::"$r12"
                );
}


/******************************************************************************
 *Function Name：  EXTI_SoftInterruptStop
 *Brief：stop a Software interrupt.
 *
 *Param：
 *		 none
 *
 *Return value：
 *      None
 *Remarks：
 *
 *
 ******************************************************************************/
void EXTI_SoftInterruptStop(void)
{
    asm volatile(				\
                "li.w $r12, 0x1;\n"\
                "csrxchg $r0, $r12, 0x4;\n"\
		        :::"$r12"
                );
}


/******************************************************************************
 *Function Name：  EXTI_GetFlagStatus
 *Brief：Checks whether the specified EXTI gpio flag is set or not.
 *
 *Param：
 *		EXTI_GPIO: specifies the EXTI gpio flag to check.
  *   This parameter can be:
  *      EXTI_GPIOx: External interrupt gpio x where x(0..31)
 *
 *Return value：
 *      None
 *Remarks：
 *
 *		GPIOA[0:15]  ->  0:15
 *		GPIOA[0:15]  ->  16:31
 ******************************************************************************/
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_GPIO)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_EXTI_GPIO(EXTI_GPIO));

  if ((EXTI->EXINT_SRC & EXTI_GPIO) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/******************************************************************************
 *Function Name：  EXTI_ClearFlag
 *Brief：Clears the EXTI's gpio pending flags.
 *
 *Param：
 *		specifies the EXTI lines flags to clear.
 *   	This parameter can be any combination of EXTI_GPIOx where x can be (0..31).
 *
 *Return value：
 *      None
 *Remarks：
 *
 *		GPIOA[0:15]  ->  0:15
 *		GPIOA[0:15]  ->  16:31
 ******************************************************************************/
void EXTI_ClearFlag(uint32_t EXTI_GPIO)
{
  /* Check the parameters */
  assert_param(IS_EXTI_GPIO(EXTI_GPIO));

  EXTI->EXINT_SRC |= EXTI_GPIO;

  COMMANDW = (1 << 24);


}


/******************************************************************************
 *Function Name：  EXTI_GetITStatus
 *Brief：  specifies the EXTI gpio to check.
 *
 *Param：
 *		specifies the EXTI lines flags to check.
 *   	This parameter can be any combination of EXTI_GPIOx where x can be (0..31).
 *
 *Return value：
 *      The new state of EXTI_GPIO (SET or RESET).
 *Remarks：
 *
 *		GPIOA[0:15]  ->  0:15
 *		GPIOA[0:15]  ->  16:31
 ******************************************************************************/
ITStatus EXTI_GetITStatus(uint32_t EXTI_GPIO)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  /* Check the parameters */
  assert_param(IS_EXTI_GPIO(EXTI_GPIO));

  enablestatus =  EXTI->EXINT_EN & EXTI_GPIO;

  if (((EXTI->EXINT_SRC & EXTI_GPIO) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/******************************************************************************
 *Function Name：  EXTI_GetITStatus
 *Brief：Clears the EXTI's gpio pending bits.
 *
 *Param：
 *		EXTI_GPIO: specifies the EXTI lines to clear.
 *   	This parameter can be any combination of EXTI_GPIOx where x can be (0..31).
 *
 *Return value：
 *      none
 *Remarks：
 *
 *		GPIOA[0:15]  ->  0:15
 *		GPIOA[0:15]  ->  16:31
 ******************************************************************************/
void EXTI_ClearITPendingBit(uint32_t EXTI_GPIO)
{
  /* Check the parameters */
  assert_param(IS_EXTI_GPIO(EXTI_GPIO));

  EXTI->EXINT_SRC |= EXTI_GPIO;

}

