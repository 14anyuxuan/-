
/********************************************************************
* �ļ���:  ls1d6_std_timer.c
* �汾��	  V1.0
* ����:     ����
* ����:    2021.10.30
* ˵��:    ���ļ�������ʱ��timer���нӿں������궨��
* ��Ȩ:    ��о�пƣ�̫ԭ���������޹�˾
********************************************************************/
#include "../include/ls1d_std_timer.h"
#include"Main.h"

/**
  * @brief  Deinitializes the TIMER peripheral registers to their default reset values..
  * @param  TIMx: select the TIMER peripheral.
  *   This parameter can be TIMER.
  * @param  TIM_InitStruct: Timer parameter structure.
  *   This parameter Contains parameters for TIMER initialization.
  * @retval None
  */
void TIM_Init(TIM_TypeDef* TIMx, TIM_InitTypeDef* TIM_InitStruct)
{
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_CLOCK(TIM_InitStruct->Clock_Freq));
    assert_param(IS_TIM_PERIODIC(TIM_InitStruct->TIME_PERIODIC));
    assert_param(IS_TIM_INTEN(TIM_InitStruct->TIME_INTEN));
    assert_param(IS_TIM_START(TIM_InitStruct->TIME_START));

    TIMx->CFG=0x00;
    TIMx->CNT=0x00;
    TIMx->CMP=TIM_InitStruct->TIME_CMP;
    TIMx->STP=TIM_InitStruct->TIME_STP;
    SET_BIT(TIMx->CFG,TIM_InitStruct->TIME_INTEN);
    if (TIM_InitStruct->TIME_INTEN)
    {
    	SET_BIT(INT->INT_EN,IRQ_TIMER);
    }
    SET_BIT(TIMx->CFG,TIM_InitStruct->TIME_PERIODIC);
    SET_BIT(TIMx->CFG,TIM_InitStruct->TIME_START);


}

/**
  * @brief  Fills each TIMER_InitStruct member with its default value.
  * @param  TIM_InitStruct: pointer to a TIM_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void TIM_StructInit(TIM_InitTypeDef* TIM_InitStruct)
{
  /* Set the default configuration */
	TIM_InitStruct->Clock_Freq = 8000000;						//ϵͳʱ��
	TIM_InitStruct->TIME_START = 0x01;							//������ʱ��
	TIM_InitStruct->TIME_INTEN = 0x01 <<1;						//�ж�ʹ��
	TIM_InitStruct->TIME_PERIODIC = 0x01 << 2;   				//���ڴ���
	TIM_InitStruct->TIME_CMP =7999;//��ʼֵ1ms�жϴ���
	TIM_InitStruct->TIME_STP =8000 * 10;//����10ms
	TIM_InitStruct->TIME_CNT = 0;								//��������ʼֵ��Ϊ0
}

/**
  * @brief  Enables or disables the specified TIM peripheral.
  * @param  TIMx: select the TIMER peripheral.
  *   This parameter can be TIMER.
  * @param  NewState: new state of the TIMx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{

	  /* Check the parameters */
	  assert_param(IS_TIM_ALL_PERIPH(TIMx));
	  assert_param(IS_FUNCTIONAL_STATE(NewState));

	  if (NewState != DISABLE)
	  {
	    /* Enable the TIM Counter */
	    TIMx->CFG |= 0x01;
	  }
	  else
	  {
	    /* Disable the TIM Counter */
	    TIMx->CFG &= 0xFE;
	  }
}

void TIM_ITConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
	  /* Check the parameters */
	  assert_param(IS_TIM_ALL_PERIPH(TIMx));
	  assert_param(IS_FUNCTIONAL_STATE(NewState));

	  if (NewState != DISABLE)
	  {
	    /* Enable the Interrupt sources */
	    TIMx->CFG |= 0x02;
	    SET_BIT(INT->INT_EN,IRQ_TIMER);
	  }
	  else
	  {
	    /* Disable the Interrupt sources */
	    TIMx->CFG &= 0xFD;
	    CLEAR_BIT(INT->INT_EN,IRQ_TIMER);
	  }
}

/**
  * @brief  Gets the TIMx Counter value.
  * @param  TIMx: select the TIMER peripheral.
  *   This parameter can be TIMER.
  * @retval Counter Register value.
  */
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx)
{
	uint32_t data = 0;
	  /* Check the parameters */
	  assert_param(IS_TIM_ALL_PERIPH(TIMx));

	  data = TIMx->CNT ;

	  return data;


}

/**
  * @brief  Sets the TIMx Counter Register value
  * @param  TIMx: select the TIMER peripheral.
  *   This parameter can be TIMER.
  * @param  Counter: specifies the Counter register new value.
  * @retval None
  */
void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* Set the Counter Register value */
  TIMx->CNT = Counter;
}


/**
  * @brief  Sets the TIMx Capture Compare Register value
  * @param  TIMx: select the TIMER peripheral.
  *   This parameter can be TIMER.
  * @param  Compare: specifies the Capture Compare register new value.
  * @retval None
  */
void TIM_SetCompare(TIM_TypeDef* TIMx, uint32_t Compare)
{
	  /* Check the parameters */
	  assert_param(IS_TIM_ALL_PERIPH(TIMx));
	  /* Set the Capture Compare1 Register value */
	  TIMx->CMP = Compare;
}


/**
  * @brief  Gets the TIMx Capture Compare Register value
  * @param  TIMx: select the TIMER peripheral.
  *   This parameter can be TIMER.
  * @retval Compare register value.
  */
uint32_t TIM_GetCompare(TIM_TypeDef* TIMx)
{
	uint32_t data = 0;
	  /* Check the parameters */
	  assert_param(IS_TIM_ALL_PERIPH(TIMx));

	  data = TIMx->CMP ;

	  return data;

}


/**
  * @brief  Checks whether the TIM interrupt has occurred or not.
  * @param  TIMx: select the TIMER peripheral.
  *   This parameter can be TIMER.
  * @param  TIM_FLAG: specifies the TIM interrupt source to check.
  *   This parameter can be TIM_FLAG_Trigger
  * @note
  * @retval The new state of the TIM_IT(SET or RESET).
  */
FlagStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint32_t TIM_FLAG)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_GET_FLAG(TIM_FLAG));

  if ((TIMx->CFG & TIM_FLAG) != (uint32_t)RESET)
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
  * @brief  Clears the TIMx's interrupt pending bits.
  * @param  TIMx: select the TIMER peripheral.
  *   This parameter can be TIMER.
  * @param  TIM_FLAG: specifies the TIM interrupt source to check.
  *   This parameter can be  TIM_FLAG_Trigger
  * @retval None
  */
void TIM_ClearIT(TIM_TypeDef* TIMx, uint32_t TIM_FLAG)
{
	  /* Check the parameters */
	  assert_param(IS_TIM_ALL_PERIPH(TIMx));
	  assert_param(IS_TIM_CLEAR_FLAG(TIM_FLAG));

	  /* Clear the flags */
	  TIMx->CFG |= TIM_FLAG;
	  //TIMx->CFG = TIMx->CFG;
	  INT->INT_CLR |= IRQ_TIMER;
}
