
/********************************************************************
* 文件名:  ls1d6_std_clock.c
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.08.31
* 说明:    本文件包含clock的所有接口函数及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#include "../include/ls1d_std_clock.h"
#include "../include/ls1d_std_printf.h"
uint32 inte8m;
uint32 inte32K;
#define StableCount
/**
  * @brief  Waits for HSE start-up.
  * @param  None
  * @retval An ErrorStatus enumuration value:
  * - SUCCESS: HSE oscillator is  to be use
  * - ERROR: HSE oscillator not yet ready
  */
ErrorStatus CLOCK_WaitForHSEStartUp()
{
  uint32_t  StartUpCounter = 0;
  uint32_t  tmp = 0;
  ErrorStatus status = ERROR;
  /* Wait till HSE is ready and if Time out is reached exit */
  tmp = (PMU->TIMING) & CLOCK_HSE_SELECT_STATUS;

  while(1)
  {
	  PMU->TIMING &= (uint32_t)~CLOCK_SYSCLK_HSE_SELECT;
	  asm volatile("nop;\n");
	  PMU->TIMING |= (CLOCK_SYSCLK_HSE_SELECT|CLOCK_MEASURE_HSE_ENABLE);
	  asm volatile("nop;nop;nop;nop;nop;nop;\n");
	  tmp = (PMU->TIMING) & CLOCK_HSE_SELECT_STATUS;
	  StartUpCounter++;
	  if(tmp == CLOCK_HSE_SELECT_STATUS)
	  {
		   return SUCCESS;
	  }
	  if(StartUpCounter >= HSE_STARTUP_TIMEOUT)
	  {
		  return ERROR;
	  }
  }
#if 0
   do
   {
	  PMU->TIMING &= (uint32_t)~CLOCK_SYSCLK_HSE_SELECT;
	  asm volatile("nop;\n");
	  PMU->TIMING |= (CLOCK_SYSCLK_HSE_SELECT|CLOCK_MEASURE_HSE_ENABLE);
	  asm volatile("nop;nop;nop;nop;nop;nop;\n");
	  tmp = (PMU->TIMING) & CLOCK_HSE_SELECT_STATUS;
	  StartUpCounter++;
   } while((StartUpCounter < HSE_STARTUP_TIMEOUT) && (tmp != CLOCK_HSE_SELECT_STATUS));
   asm volatile("nop;nop;nop;nop;nop;nop;\n");
#endif
}

ErrorStatus CLOCK_WaitForLSEStartUp(void)
{
   uint32_t tmp = 0;
  ErrorStatus status = ERROR;
  uint32_t  StartUpCounter = 0;
  /* Wait till HSE is ready and if Time out is reached exit */
   while(1)
   {
	  PMU->TIMING |= CLOCK_LSE_SELECT;
	  asm volatile("nop;nop;\n");
 	  StartUpCounter++;
 	  if(LS_REXT(PMU->TIMING,CLOCK_LSE_SELECT_STATUS) == SET)
 	  {
 		  inte32K = 1;
 		  return SUCCESS;
 	  }
 	  asm volatile("nop;\n");
 	  PMU->TIMING &= ~(CLOCK_LSE_SELECT);

 	  if(StartUpCounter >= HSE_STARTUP_TIMEOUT)
 	  {
 		 inte32K = 2;
 		 return ERROR;
 	  }
 	  asm volatile("nop;nop;\n");
   }
}
/******************************************************************************
 *Function Name：	 CLOCK_HSEConfig
 *Brief：Configures the External High Speed oscillator (HSE).
 *
 *Param：
 * 		 RCC_HSE: specifies the new state of the HSE.
 * 		 RCC_HSE_OFF: HSE oscillator OFF,system use internal 8M clock;
 * 		 RCC_HSE_ON: HSE oscillator ON,system use external 8M clock;
 *Return value：
 *       the state of function;
 *Remarks：
 *
 *
 ******************************************************************************/
ErrorStatus CLOCK_HSEConfig(uint32_t CLOCK_HSE)
{
	  uint32_t mode = 0,i = 0,clock = CLOCK_HSE;
	  ErrorStatus status = ERROR;
	  /* Check the parameters */
	  assert_param(IS_CLOCK_HSE(CLOCK_HSE));

	  /* reset the HSE bit  */
	  PMU->TIMING &= (uint32_t)~clock;
	  asm volatile("nop;\n");
	  /* measure clock enable   */
	  PMU->TIMING |= CLOCK_MEASURE_HSE_ENABLE;

#if 0
	  for(i = 40000; i > 1;i--)
	  {
		  asm volatile("nop;\n");
	  }; //延时4cycle is 1us，wait 10ms；
#endif

	  if(clock == CLOCK_SYSCLK_HSE_SELECT)
	  {
		  status =  CLOCK_WaitForHSEStartUp();
		  if(status == SUCCESS)
		  {
			  inte8m = 8000;
		  }else{
			  PMU->TIMING &= ~CLOCK_SYSCLK_HSE_SELECT;
			  inte8m =  CLOCK_GetClocksFreq()/1000;
			  status = SUCCESS;
		  }
	  }
	  else
	  {
		  PMU->TIMING &= ~CLOCK_SYSCLK_HSE_SELECT;
		  inte8m =  CLOCK_GetClocksFreq()/1000;
		  status = SUCCESS;
	  }

	  return status;
}


/******************************************************************************
 *Function Name：	 CLOCK_LSEConfig
 *Brief：Configures the External Low Speed oscillator (LSE 32K).
 *
 *Param：
 * 		 RCC_LSE: specifies the new state of the HSE.
 * 		 RCC_LSE_OFF: HSE oscillator OFF,system use internal 8M clock;
 * 		 RCC_LSE_ON: HSE oscillator ON,system use external 8M clock;
 *Return value：
 *		 the state of function;
 *Remarks：
 *
 *
 ******************************************************************************/
ErrorStatus CLOCK_LSEConfig(uint32_t CLOCK_LSE)
{
	  ErrorStatus status = ERROR;
	  /* Check the parameters */
	  assert_param(IS_CLOCK_LSE(CLOCK_LSE));

	  if(CLOCK_LSE == CLOCK_LSE_SELECT)
	  {
		  if(CLOCK_WaitForLSEStartUp() != SUCCESS)
		  {
			  PMU->TIMING &= ~CLOCK_LSE_SELECT;
			  status = SUCCESS;
		  }
	  }
	  else
	  {
		  PMU->TIMING &= (uint32_t)~CLOCK_LSE_SELECT;
		  status = SUCCESS;
	  }

	  return status;
}


/******************************************************************************
 *Function Name：	 CLOCK_StructInit
 *Brief：Fills each CLOCK_InitStruct member with its default value.
 *
 *Param：
 * 		 CLOCK_InitStruct: pointer to a CLOCK_InitTypeDef structurewhich will be initialized.
 *
 *Return value：
 *       None
 *Remarks：
 *
 ******************************************************************************/
void CLOCK_StructInit(CLOCK_InitTypeDef  *CLOCK_InitStruct)
{

	CLOCK_InitStruct->OscillatorType =CLOCK_OSCILLATORTYPE_HSE|CLOCK_OSCILLATORTYPE_HSI|CLOCK_OSCILLATORTYPE_LSE|CLOCK_OSCILLATORTYPE_LSI;
	CLOCK_InitStruct->HSEState = CLOCK_HSE_ON;
	CLOCK_InitStruct->LSEState = CLOCK_LSE_ON;
	CLOCK_InitStruct->ClkHSDiv = CLOCK_MEASURE_HSE_DIV1;
	CLOCK_InitStruct->CalibrationResNum = CLOCK_MEASURE_CAL_RES_NUM_2;
	CLOCK_InitStruct->LSISpeed = CLOCK_LSI_SPEED_32K;
	CLOCK_InitStruct->StartClkHS = CLOCK_START_CLK_HS_5140US;

}

/******************************************************************************
 *Function Name：	 CLOCK_Init
 *Brief：Fills each CLOCK_InitStruct member with its default value.
 *
 *Param：
 * 		 CLOCK_InitStruct: pointer to a CLOCK_InitTypeDef structure which was initialized.
 *
 *Return value：
 *       the state of function;
 *Remarks：
 *		  内含时钟分频的、时钟源的配置，必须放在主函数首要位置
 ******************************************************************************/
ErrorStatus CLOCK_Init(CLOCK_InitTypeDef  *CLOCK_InitStruct)
{
	ErrorStatus status = ERROR;
	PMU->TIMING = 0;
	/* set HSE start delay time  */
	//CLEAR_BIT(PMU->TIMING,CLOCK_START_CLK_HS_MASK);
	SET_BIT(PMU->TIMING,CLOCK_InitStruct->StartClkHS);

	/* set measure HSE div parameters*/
	//CLEAR_BIT(PMU->TIMING,CLOCK_MEASURE_HSE_DIV_MASK);
	SET_BIT(PMU->TIMING,CLOCK_InitStruct->ClkHSDiv);

	/* set measure Calibration HSE parameters*/
	//CLEAR_BIT(PMU->TIMING,CLOCK_MEASURE_CAL_RES_NUM_MASK);
	SET_BIT(PMU->TIMING,CLOCK_InitStruct->CalibrationResNum);

 	 /* set LSISpeed parameters*/
	//CLEAR_BIT(PMU->TIMING,CLOCK_LSI_SPEED_MASK);
 	SET_BIT(PMU->TIMING,CLOCK_InitStruct->LSISpeed);

	/**Initializes the HSE */
 	if (CLOCK_HSEConfig(CLOCK_InitStruct->HSEState) != SUCCESS)
 	{
 	  return status;
 	}
	/**Initializes the LSE */
 	if (CLOCK_LSEConfig(CLOCK_InitStruct->LSEState) != SUCCESS)
 	{
 	  return status;
 	}

	status = SUCCESS;
	return status;
}

/******************************************************************************
 *Function Name：	 CLOCK_GetFlagStatus
 *Brief：Checks which Clock is set or not.
 *
 *Param： CLCOK_FLAG: specifies the flag to check.
 * 		 CLOCK_FLAG_HSERDY: HSE oscillator clock ready
 *       CLOCK_FLAG_HSEFAIL: HSE oscillator clock fail
 *		 CLOCK_FLAG_LSERDY: LSE oscillator clock ready
 *		 CLOCK_FLAG_LSEFAIL: LSE oscillator clock fail
 *
 *Return value：
 *       The new state of CLCOK_FLAG (SET or RESET).
 *Remarks：
 *
 ******************************************************************************/
FlagStatus CLOCK_GetFlagStatus(uint32_t CLCOK_FLAG)
{
	FlagStatus status = RESET;
	assert_param(IS_CLOCK_FLAG(CLCOK_FLAG));
//	status = (PMU->TIMING & CLCOK_FLAG);
	switch(CLCOK_FLAG)
	{
	case CLOCK_HSE_FAIL:
		status = LS_REXT(PMU->TIMING,CLOCK_HSE_FAIL);
		break;
	case CLOCK_LSE_SELECT_STATUS:
		status = LS_REXT(PMU->TIMING,CLOCK_LSE_SELECT_STATUS);
			break;
	case CLOCK_HSE_SELECT_STATUS:
		status = LS_REXT(PMU->TIMING,CLOCK_HSE_SELECT_STATUS);
			break;
	case CLOCK_LSE_FAIL:
		status = LS_REXT(PMU->TIMING,CLOCK_LSE_FAIL);
			break;
	default:
		break;
	}
	return status;
}

/******************************************************************************
 *Function Name：	 CLOCK_GetClocksFreq
 *Brief：get the inner clock frequency  value.
 *
 *Param：
 * 		 Clocks : the inner clock frequency  value .
 *
 *Return value：
 *       none
 *Remarks：
 *
 ******************************************************************************/
uint32_t CLOCK_GetClocksFreq(void)
{
#if 0
	   uint32_t tmp = 0;
	    asm volatile(					\
	       /* "nop;nop;nop;\n"			\ */
			"li		$8, 0x5800;\n"		\
			"li 	$9, 0x6800;\n"		\
			"sw 	$0, 0x00($9);\n"	\
			"sw 	$0, 0x04($9);\n"	\
			"li 	$10, 0x01;\n"		\
			"li 	$11, 0xfffff;\n"	\
			"lw 	$12, 0x08($8);\n"	\
			"sw 	$10, 0x00($9);\n"	\
			"addiu 	$12, $12, 0x40;\n"	\
			"and 	$11, $11, $12;\n"	\
			"1: \n"						\
			"lw 	$10, 0x08($8);\n"	\
			"bne 	$10, $11, 1b ;\n"	\
			"nop;\n"					\
			"lw 	$2, 0x04($9);\n"	\
			"li 	$10, 0x02;\n"		\
			"sll 	$2, $2, $10;\n"		\
			"move 	%0, $2;\n"			\
			"sw 	$0, 0x00($9);\n"	\
			"sw 	$0, 0x04($9);\n"	\
			/*"nop;\n" */
	        :"=r"(tmp)	\
			::"$2","$8","$9","$10","$11","$12"	\
	        );
	    return tmp;
#endif

	   CLOCK_EnableSysTick();
	   uint32_t tmp = 0;
		asm volatile(					\
		   /* "nop;nop;nop;\n"			\ */
			"li.w	$r13, %1;\n"		\
			"li.w 	$r16, 0xfffff;\n"	\
			"rdtimel.w $r14, $r0;\n"	\
			"ld.w 	$r17, $r13, 0x08;\n"	\
			"addi.w $r17, $r17, 0x40;\n"	\
			"and 	$r16, $r16, $r17;\n"	\
			"1: \n"						\
			"ld.w 	$r15, $r13, 0x08;\n"	\
			"bne 	$r15, $r16, 1b ;\n"	\
			"nop;\n"					\
			"rdtimel.w $r18, $r0;\n"	\
			"sub.w $r18, $r18, $r14;\n"	\
			"slli.w %0, $r18, 0x02;\n"		\
			/*"nop;\n" */
			:"=r"(tmp)	\
			:"i"(PMU_BASE)	\
			:"$r18","$r13","$r14","$r15","$r16","$r17"	\
			);
		 CLOCK_DisableSysTick();
		 return tmp;
}

/******************************************************************************
 *Function Name：	 CLOCK_EnableSysTickIT
 *Brief：系统协处理时钟计数器和比较器的中断打开
 *
 *Param：
 * 		none
 *
 *Return value：
 *       none
 *Remarks：
 *
 ******************************************************************************/
void CLOCK_EnableSysTick(void)
{
#if 0
	asm volatile(					\
		"nop;nop;nop;\n"			\
		"mfc0	$8, $9;\n"			\
		"li		$9, 0x1;\n"			\
		"sub	$9, $8, $9;\n"		\
		"mtc0	$9, $11;\n"			\
		"mfc0	$8, $13;\n"			\
		"li		$9, 0xf7ffffff;\n" 	\
		"and	$9, $8, $9;\n"		\
		"mtc0	$9, $13;\n"   		\
	    "nop;nop;nop;\n"			\
		:::"$8","$9"		  		\
		);

#endif
	asm volatile("li.w $r12, 0x10; csrxchg $r0, $r12, 0xaf;":::"$r12");
}


/******************************************************************************
 *Function Name：	 CLOCK_DisableSysTickIT
 *Brief： 关闭永恒的systick
 *
 *Param：
 * 		 none
 *
 *Return value：
 *       none
 *Remarks：
 *
 ******************************************************************************/
void CLOCK_DisableSysTick(void)
{
#if 0
	asm volatile(					\
		"nop;nop;nop;\n"			\
		"mfc0	$8,  $13;\n"		\
		"li		$9,  0x8000000;\n"	\
		"or 	$10, $8, $9;\n"		\
		"mtc0	$10, $13;\n"		\
	    "nop;nop;nop;\n"			\
		:::"$8","$9","$10"			\
		);
#endif

    asm volatile("li.w $r12, 0x10; csrxchg $r12, $r12, 0xaf;":::"$r12");
}



/******************************************************************************
 *Function Name：	 CLOCK_ClearSysTickIntertupt
 *Brief：Timer中断清除
 *
 *Param：
 * 		 none
 *
 *Return value：
 *       none
 *Remarks：
 *
 ******************************************************************************/
void CLOCK_ClearCpuTimerIT(void)
{
#if 0
	asm volatile(					\
		"nop;nop;nop;\n"			\
		"mfc0	$8, $9;\n"			\
		"li		$9, 0x1;\n" 		\
		"subu	$9, $8, $9;\n"		\
		"mtc0	$9, $11;\n"   		/* write cp0_compare */\
	    "nop;nop;nop;\n"			\
		:::"$8","$9"		  		\
		);
#endif
    asm volatile (\
                  "li.w $r12, 0x1;\n" \
                  "csrwr $r12, 0x44;\n" \
		          :::"$r12"
                );
}

/******************************************************************************
 *Function Name：	 CLOCK_SetCpuTimer
 *Brief：定时函数timer 代表定时 time ，time后产生TIMER_8M中断
 *
 *Param：
 * 		 none
 *
 *Return value：
 *       none
 *Remarks：
 *
 ******************************************************************************/
void CLOCK_SetCpuTimer(uint32 timer)
{
#if 0
	asm volatile(					\
		"nop;nop;nop;\n"			\
		"mfc0	$8, $9;\n"			\
		"move	$9, %0;\n"			\
		"addu	$9, $8, $9;\n"		\
		"mtc0	$9, $11;\n"   		/* write cp0_compare */\
	    "nop;nop;nop;\n"			\
		::"r"(timer):"$8","$9"		\
		);
#endif

    asm volatile (\
                  "csrrd    $r12, 0x41;"\
                  "ori      $r12, %0, 0x3;"\
                  "csrwr    $r12, 0x41;"\
                  :
		          :"r"(timer)
		          :"$r12"
                  );
}

void CLOCK_StopCpuTimer(void)
{
    asm volatile ("nop;nop;nop;nop;csrwr $r0, 0x41;nop;nop;nop;nop;");
}

/***********************************************************************
函数功能:         定时函数
输入参数:         time 等于0时，表示关闭定时
			    time 不等于0是，代表定时 time/16 秒，time/16秒后产生TIMER_WAKE中断
输出参数:         无
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
void Wake_Set(uint32 sec)
{
    if(sec != 0)
    {
        uint32_t time = sec * 256;
        uint32_t compare = 0;
        compare = (PMU_COUNT & 0xfffff) + time;
        PMU_COMPARE  = compare;
        PMU_CMDSTS |=  (1 << 8);
    }
    else
    {
        PMU_CMDSTS &=  ~(1 << 8);
    }
}


static uint32 get_count(void)
{
    // 获取计数器中的值
    uint32_t tem_count = 0;
#ifdef StableCount
     asm volatile("rdtimel.w	%0, $r0":"=r" (tem_count));
#else
    asm volatile("csrrd	%0, 0X42":"=r" (tem_count));
#endif
    return tem_count;
}

//计数开始
static void start_count(TIMER_COUNT *timer_count)
{
	timer_count->begin = 0;
	timer_count->end = 0;
	//将计数初始值放到start中
	timer_count->begin = get_count();
}

//计数结束,将两次计数的差值保存在count中
static uint32 stop_count(TIMER_COUNT *timer_count)
{
	//将计数结束的值放到end中
	timer_count->end = get_count();
#ifdef StableCount
	if(timer_count->end >= timer_count->begin)
	{
		return (timer_count->end - timer_count->begin);
	}
	else
	{
		uint32 end = 0xffffffff;
		return ((end  - timer_count->begin) + timer_count->end);
	}
#else

	if(timer_count->begin >= timer_count->end)
	{
		return (timer_count->begin - timer_count->end);
	}
	else
	{
 		uint32 end = 0xfffffffC;
		return ((end  - timer_count->end) + timer_count->begin);
	}
#endif
}

static void delay_cycle(uint32 num)
{
#if 1

	uint32 count = 0;
	TIMER_COUNT timer_count = {0, 0};
// 	CLOCK_SetCpuTimer(0xffffffff);
	CLOCK_EnableSysTick();
	start_count(&timer_count);
// 	printf("start = %d\r\n",timer_count.begin);
	while (count < num)
	{
		count = stop_count(&timer_count);
	}
// 	CLOCK_StopCpuTimer();
// 	printf("end = %d\r\n",timer_count.end);
	CLOCK_DisableSysTick();
#endif
}

void CLOCK_DelayUs(uint32 x)	    //us单位
{
	//delay_cycle(x*(inte8m >> 10));//x * 8  >>10
	delay_cycle(x*8);
}

void CLOCK_DelayMs(uint32 x)  	//ms单位
{
	delay_cycle(x * inte8m);//x * 8000

}

void CLOCK_DelayS(uint32 x)  	//s单位
{
	delay_cycle(x * inte8m *1000 );//x * 8000*1000
}

uint32 CLOCK_GetPmuCount(void)
{
	// 获取pmu计数器中的值
	return (PMU->COUNT);
}

//计数开始
void CLOCK_SetStartTimerCount(uint32_t *start_time)
{
	//将计数初始值放到start中
	//CLOCK_EnableSysTick();
	//*start_time = get_count();
	*start_time = CLOCK_GetPmuCount();
}

//计数结束,将两次计数的差值保存在count中
uint32 CLOCK_GetTimerCountInterval(uint32_t start_time)
{
	uint32_t end_time = 0;
	//将计数结束的值放到end中
	 end_time = CLOCK_GetPmuCount();

	 //end_time = get_count();
	if(end_time >= start_time)
	{
		return (end_time - start_time);
	}
	else
	{
		//uint32 end = -1;
		uint32 end = 0xfffff;
		return (end - start_time + end_time);
	}
}

void Wake_256sec_Set(uint32_t p256sec)
{
    if(p256sec != 0)
    {
        uint32_t time = p256sec ;
        uint32_t compare = 0;
        compare = (PMU_COUNT & 0xfffff) + time;
        PMU_COMPARE  = compare;
        PMU_CMDSTS |= (1 << 8);
    }
    else
    {
        PMU_CMDSTS &=  ~(1 << 8);
    }
}
