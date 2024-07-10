/********************************************************************
* 文件名:  ls1d6_std_rtc.c
* 版本：	  V1.0
* 作者:   王永芳
* 日期:    2021.10.30
* 说明:    本文件包含rtc的所有接口函数及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#include "../include/ls1d_std_Interrupt.h"
#include "../include/ls1d_std_printf.h"
#include "../include/ls1d_std_rtc.h"

/**
  * @brief  Fills each RTC_InitStruct member with its default value.
  * @param  RTC_InitStruct: pointer to an RTC_InitTypeDef structure which will be initialized.
  * @retval None
  */

void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct)
{
  /* RTC_InitStruct members default value */
	RTC_InitStruct->Freq = (32768 >> 4) -1;  /* 输入时钟/16-1，用来得到分频系数/32768 */
	/* 日期时间设置  */
	RTC_InitStruct->usec = 3;
	RTC_InitStruct->sec = 1;
	RTC_InitStruct->min = 0;
	RTC_InitStruct->hour = 9;
	RTC_InitStruct->day = 26 ;
	RTC_InitStruct->mon = 4;
	RTC_InitStruct->year = 22;
}

/**
  * @brief    Initializes the RTC peripheral according to the specified
  * 		   parameters in the RTC_InitStruct .
  * @param  RTC_InitStruct:  pointer to an RTC_InitTypeDef structure
  *         		that contains the configuration information for the specified RTC peripheral.
  * @retval None
  */
void RTC_Init(RTC_InitTypeDef* RTC_InitStruct)
{
	RTC_time write_time;
	RTC->FREQ = (RTC_InitStruct->Freq << 16) | 0x1;	/* 内部需要产生1/16秒的事件，通过设置Freq得到16Hz时钟 */
	write_time.year = RTC_InitStruct->	year;
	write_time.mon  = RTC_InitStruct->	mon;
	write_time.day	= RTC_InitStruct->	day;
	write_time.hour	= RTC_InitStruct->	hour;
	write_time.min	= RTC_InitStruct->	min;
	write_time.sec	= RTC_InitStruct->	sec;
	write_time.usec = RTC_InitStruct->	usec;
	RTC_SetDateTime(&write_time);

}
/**
  * @brief  Gets the RTC date and time value.
  * @param  *Rtime A structure that holds dates and times.
  * @retval None.
  */
void RTC_GetDateTime(RTC_time *Rtime)
{
	uint32 Rtc_time1 = 0;
	uint32 Rtc_time2 = 0;

	Rtc_time1 = RTC->RTC1;
	Rtc_time2 = RTC->RTC0;

	Rtime->year = (Rtc_time1&0xFE00)>>9;
	Rtime->mon =  (Rtc_time1&0x1E0)>>5;
	Rtime->day =  (Rtc_time1&0x1F);
	Rtime->hour = (Rtc_time2&0x1F0000)>>16;
	Rtime->min =  (Rtc_time2&0xFC00)>>10;
	Rtime->sec =  (Rtc_time2&0x3F0)>>4;

//	RTC_GetDate(Rtime);
//	RTC_GetTime(Rtime);
}


/**
  * @brief  Sets the RTC date and time value.
  * @param  *Rtime A structure that holds dates and times.
  * @retval None.
  */
void RTC_SetDateTime(RTC_time *Wtime)
{
    uint32 settime = 0;
    uint32 settimecp = 0;
	if(((Wtime->mon) > 12)||((Wtime->mon) <= 0))
		Wtime->mon = 1;
	if(((Wtime->day) > 31)||((Wtime->day) <= 0))
		Wtime->day = 1;
	settime= (((Wtime->hour)%24)<<16) | (((Wtime->min)%60)<<10) | (((Wtime->sec)%60)<<4) | (((Wtime->usec)%15)<<0);
	settimecp = ((Wtime->year)<<9) | (((Wtime->mon)%13)<<5) | (((Wtime->day)%32)<<0);

	WRITE_REG(RTC->RTC0,settime);
	WRITE_REG(RTC->RTC1,settimecp);
	WRITE_REG(RTC->CFG,RTC_SET);

//	RTC_SetTime(Rtime);
//	RTC_SetDate(Rtime);

}

/**
  * @brief  Enables or disables the specified RTC interrupts.
  * @param  NewState: new state of the TIM interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_ITConfig(FunctionalState NewState)
{
	/* Check the parameters */
    (NewState != DISABLE)? (SET_BIT(PMU->COMMAND,IRQ_RTC)) : (CLEAR_BIT(PMU->COMMAND,IRQ_RTC));

}


/**
  * @brief  Sets the RTC timing value.
  * @param  *Rtime A structure that holds dates and times.
  * @retval None.
  */
#if 1
void RTC_SetAlarm(RTC_time *Wtime)
{
    uint32 settime = 0;

    if(((Wtime->mon) > 12)||((Wtime->mon) <= 0))
		Wtime->mon = 1;
	if(((Wtime->day) > 31)||((Wtime->day) <= 0))
		Wtime->day = 1;


    settime= RTC_Timer_En | (((Wtime->mon)%13)<<26)  | (((Wtime->day)%32)<<21) |(((Wtime->hour)%24)<<16) | (((Wtime->min)%60)<<10) | (((Wtime->sec)%60)<<4) | (((Wtime->usec)%15)<<0);

    WRITE_REG(RTC->CFG,settime);
    RTC_ITConfig(ENABLE);

}

#endif
#if 0
void RTC_SetAlarm(RTC_time *Wtime)
{
    uint32 settime = 0;
    RTC_time tmp;
//    if(((Wtime->mon) > 12)||((Wtime->mon) <= 0))
//		Wtime->mon = 1;
//	if(((Wtime->day) > 31)||((Wtime->day) <= 0))
//		Wtime->day = 1;

   if(Wtime->sec >= 60)
   {
	   tmp.sec = Wtime->sec%60;
	   tmp.min = Wtime->min + 1;
	   if(tmp.min >= 60 )
	   {
		   tmp.min = 0;
		   tmp.hour = Wtime->hour + 1;
		   if(tmp.hour >= 24)
		   {
			   tmp.hour = 0;
			   tmp.day = Wtime->day + 1;
		   }else{
			   tmp.day = Wtime->day;
		   }

	   }else{

		   if(Wtime->hour >= 24)
		   {
			   tmp.hour = Wtime->hour%24;
			   tmp.day = Wtime->day + 1;
		   }else
		   {
			   tmp.hour = Wtime->hour;
			   tmp.day = Wtime->day;
		   }

	   }

   }else
   {
	   tmp.sec = Wtime->sec;
	   if(Wtime->min >= 60 )
	   {
		   tmp.min = Wtime->min%60;
		   tmp.hour = Wtime->hour + 1;
		   if(tmp.hour >= 24)
		   {
			   tmp.hour = 0;
			   tmp.day = Wtime->day + 1;
		   }else{
			   tmp.day = Wtime->day;
		   }
	   }else
	   {
		   tmp.min = Wtime->min;
		   if(Wtime->hour >= 24)
		   {
			   tmp.hour = Wtime->hour%24;
			   tmp.day = Wtime->day + 1;
		   }else
		   {
			   tmp.hour = Wtime->hour;
			   tmp.day = Wtime->day;
		   }
	   }
   }

DateJudge:

    if(Wtime->mon == 2)                          //如果是2月
    {
        if ((Wtime->year % 4 == 0)&& (Wtime->year != 100) &&(Wtime->year != 200))
        {
        	//闰年判断  2000~2225年中 只要能被4整除的年份(除2100 2200年外)都是闰年
        	if (tmp.day >= 30)                  //闰年,2月有29天
            {
            	tmp.day = tmp.day%30 + 1;
                tmp.mon = Wtime->mon + 1;
                if (tmp.mon >= 13)
                {
                	tmp.mon = 1;
                	tmp.year= Wtime->year + 1;
                }else{
                	tmp.year= Wtime->year;
                }
            }
            else
            {
				tmp.mon = Wtime->mon;
				tmp.year = Wtime->year;
            }
        }
        else
        {
            if (tmp.day >= 29)                  //非闰年,2月只有28天
            {
            	tmp.day = tmp.day%29 + 1;
            	tmp.mon = Wtime->mon + 1;
                if (tmp.mon >= 13)
                {
                	tmp.mon = 1;
                	tmp.year = Wtime->year + 1;
                }else
                {
                	tmp.year = Wtime->year;
                }
            }
            else
            {
            	tmp.mon = Wtime->mon;
            	tmp.year = Wtime->year;
            }
        }
    }//月大有31天
    else if ((Wtime->mon == 1) || (Wtime->mon == 3) || (Wtime->mon == 5 ) ||
                 (Wtime->mon == 7) || (Wtime->mon == 8) || (Wtime->mon == 10) ||
                 (Wtime->mon == 12) )
     {
         if (tmp.day >= 32)
         {
             tmp.day = tmp.day%32 + 1;
             tmp.mon = Wtime->mon +1;
             if (tmp.mon >= 13)
             {
            	 tmp.mon = 1;
            	 tmp.year = Wtime->year +1;
             }else{

            	 tmp.year = Wtime->year;
             }

         }else
         {
         	tmp.mon = Wtime->mon;
         	tmp.year = Wtime->year;
         }
     }
     else if (   (Wtime->mon == 4) || (Wtime->mon == 6) || (Wtime->mon == 9) ||
                 (Wtime->mon == 11) )
                                                 //月小有30天
     {
         if (tmp.day >= 31)
         {
             tmp.day = tmp.day%31 + 1;
             tmp.mon = Wtime->mon + 1;
             if (tmp.mon >= 13)
             {
            	 tmp.mon = 1;
            	 tmp.year = Wtime->year + 1;
             }else{
            	 tmp.year = Wtime->year;
             }
         }else
         {
          	 tmp.mon = Wtime->mon;
          	 tmp.year = Wtime->year;
         }
     }else{
    	 if(Wtime->mon >= 13)
    	 {
    		 Wtime->mon = Wtime->mon%13 + 1;
    		 Wtime->year++;
    		 goto DateJudge;
    	 }else{
    		 Wtime->mon= 12;
    		 Wtime->year--;
    		 goto DateJudge;
    	 }
     }

    settime= RTC_Timer_En | (((tmp.mon)%13)<<26)  | (((tmp.day)%32)<<21) |(((tmp.hour)%24)<<16) | (((tmp.min)%60)<<10) | (((tmp.sec)%60)<<4) | (((tmp.usec)%15)<<0);

    WRITE_REG(RTC->CFG,settime);
    RTC_ITConfig(ENABLE);
}

#endif



/**
  * @brief  Clears the RTC's interrupt pending bits.
  * @retval None
  */
void RTC_ClearIT(void)
{
  SET_BIT(PMU->COMMAND_W,IRQ_RTC_CLR);
}


#if 0

void rtc_timer_count(uint32_t settime,uint32_t systime)
{
	volatile uint32 time = 0;

	time = (PMU->COMMAND & 0xfffff);

	if(time < systime)
	{
		time += 0x100000;
	}

	if((time - systime) > (256*settime))  			//RTCÊ±¼ä¼ÆÊýÆ÷Ã¿1/256s¼ÓÒ»´Î
	{
//		printf("-------timer handle-------\n");
//		get_current_timer = (PMU->COMMAND & 0xfffff);  //ÖØÐÂ¿ªËø¶¨Ê±
	}
	else
	{
//		printf("-------sys running-------\n");
		CLOCK_DelayS(1);
	}
}

/*
 * ¸Ã¶¨Ê±Æ÷ÄÜ¹»ÔÚË¯ÃßÏÂ¼ÌÐø¹¤×÷
 * time:¶¨Ê±Ê±¼ä,ÔÚ¸ÃÊ±¼äÊ±²úÉúÖÐ¶Ï
 */
void rtc_wake_set(uint32 time)
{
	if(time != 0)
	{
		uint32 compare = 0;
		compare = (PMU->COUNT & 0xfffff) + (time*256);
		PMU->COMPARE  = compare;                 //µ±PMU_Count¼ÆÊýÖµÓë¸Ã¼Ä´æÆ÷ÖÐµÄÖµÏàÍ¬Ê±,²úÉú
		PMU->COMMAND |= (1<<7)|(1<<8);            //´ò¿ª¶¨Ê±»½ÐÑÊ¹ÄÜ£¬ÖÐ¶ÏÊ¹ÄÜ»½ÐÑÏµÍ³ÖÐ¶Ï
	}
	else
	{
		PMU->COMMAND &=  ~((1<<7)|(1<<8));        //½ûÖ¹Ê¹ÄÜ
	}
}

#endif

