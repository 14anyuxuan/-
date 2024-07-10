
/********************************************************************
* 文件名:  ls1d6_std_flash.c
* 版本：	  V1.0
* 作者:    王永芳
* 日期:    2021.08.31
* 说明:    本文件包含片上flash的所有接口函数及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#include "../include/ls1d_std_flash.h"
#include "../include/ls1d_std_printf.h"
/**
  * @brief  Erases a specified FLASH page.
  * @param  Page_Address: The page address to be erased.
  * @retval None
  */
uint32_t Flash_pe;

void FLASH_ErasePage(uint32 Page_Address)  //erase a flash page, FLASH_PAGE_SIZE
{
	uint8 err_code;
	////////////////   ///////////////
	assert_param(IS_FLASH_ADDRESS(Page_Address));
 	FLASH->PET = 0x10;    // erase time, 2.5ms
	FLASH->CMD = FLASH_ERASE_CMD | (Page_Address & FLASH_CMD_ADDR_MASK);
	err_code=FLASH_WaitForPeEnd(EraseTimeout);
//	FLASH_ClearIT();
}

/**
  * @brief  Erases all User FLASH pages.
  * @param  Page_Address: The page address to be erased.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
void FLASH_EraseUserFlash(uint32 Page_Address)
{
	uint32 i=0;
	assert_param(IS_FLASH_ADDRESS(Page_Address));
	Page_Address |= LS1D_FLASH_ADDR;
	uint32 start_addr = Page_Address;                //LS1D_FLASH_ADDR片上Flash的起始地址
	uint32 page = ((LS1D_FLASH_ADDR|LS1D_FLASH_TOTAL)  - start_addr)/FLASH_PAGE_SIZE;   //0xbf01ffff片上Flash的上线，计算多少页
	for(i=0; i<page; i++)
	{
		FLASH_ErasePage(start_addr+i*FLASH_PAGE_SIZE);
		CLOCK_DelayUs(10);
	}
}

/**
  * @brief  Read FLASH data.
  * @param  Page_Address: The page address to be erased.
  * @param  *data: The data pointer to the readed data.
  * @param  num: The number of the readed data.
  * @retval The number of the readed data.
  */
int32 FLASH_ReadPage(uint32 Page_Address, uint8 *data, uint32 num)
{
	int i = 0;
	uint8 *ptr;

	if (Page_Address + num > LS1D_FLASH_TOTAL)    //LS1D_FLASH_TOTAL:flash大小
		return -1;

	Page_Address |= LS1D_FLASH_ADDR;
	assert_param(IS_FLASH_ADDRESS(Page_Address));
	ptr = (uint8 *)Page_Address;

	for(i = 0; i < num; i++)
	{
		*data++ = *ptr++;
	}

	return num;
}

/**
  * @brief  Write words at a specified address.
  * @param  Page_Address: specifies the address to be programmed.
  * @param  *data: specifies the data to be programmed.
  * @param  num: specifies the number of data to be programmed.
  * @retval FLASH Status: The returned value can be: verif_correct,
  *         verif_end, pe_end,FLASH_TIMEOUTor no_permission.
  */

#if 0
uint8 FLASH_WritePage(uint32 Page_Address, uint8 *data, uint32 num)
{
	uint32 temp_flash_buf;
	uint8 status;
	uint8 *temp_data = data;

	Page_Address |= LS1D_FLASH_ADDR;									//addr加上LS1D_FLASH_ADDR（0xbf000000）基地址
	assert_param(IS_FLASH_ADDRESS(Page_Address));

	FLASH->CMD = FLASH_PAGE_LATCH_CLEAR;     				//FLASH_CMD_REG=0x40000000
	uint32 flash_block_mask = FLASH_PAGE_SIZE - 1;  			//flash_block_mask=127（0x0000007F）
	uint32 *page_data = (uint32 *)(Page_Address & ~flash_block_mask) ;	//*page_data指针指向addr地址的页地址
	uint32 *old_data = (uint32 *)(Page_Address & ~flash_block_mask) ;	//*old_data指针指向addr地址的页地址
	uint32 i, j, k, offset;

	j = 0;
	uint32 count = num;
	uint32 num_left = 0;
	uint32 num_right = 0;
	uint32 addr_left_align = 0xffffffff;
	uint32 addr_right_align = 0xffffffff;
	uint32 word_mask = WORD_WIDTH - 1;		//word_mask=3
	num = 0;

	num_left = Page_Address & word_mask;   			//addr=124928(0x1E800),word_mask=3(0x00003),addr& word_mask=0
	if (num_left) 							//假如num_left=3
	{
		num_left = WORD_WIDTH - num_left;   //num_left=1
		num++;								//num=1
		addr_left_align = (Page_Address & flash_block_mask) >> 2; //addr_left_align更改为操作地址低8位区0右移2位
	}
	j = count - num_left;   //j=操作起始地址

	num_right = (j & word_mask);
	if (num_right)
	{
		num++;
		addr_right_align = Page_Address + count - num_right;
		addr_right_align = (addr_right_align & flash_block_mask) >> 2;
	}
	j = count - num_left - num_right;
	j = j >> 2;
	num += j;

	offset = ((Page_Address & flash_block_mask)>>2);

	for(j=0, i=0; i<(FLASH_PAGE_SIZE/4); i++)
	{
		if( (offset <= i)  && (j < num) )
		{
			if (i == addr_left_align)
			{
				int m = 0;
				temp_flash_buf = old_data[i];
				k = 1 << ((WORD_WIDTH - num_left) * 8);
				temp_flash_buf &= (k - 1);
				for (m = 0; m < num_left; m++)
				{
					temp_flash_buf |= temp_data[m] << (WORD_WIDTH - num_left + m)*8;
				}
				temp_data = temp_data + num_left;	//address change to be logic 0 again.
				page_data[i] = temp_flash_buf;
				num--;                           	//because j don't add 1, num has to sub 1.
			}
			else if (i == addr_right_align)
			{
				temp_flash_buf = old_data[i];
				k = 1 << (num_right * 8);
				temp_flash_buf &= ~(k - 1);
				for (k = 0; k < num_right; k++)
				{
					temp_flash_buf |= temp_data[j*4+k] << k*8;
				}
				j++;
				page_data[i] = temp_flash_buf;
			}
			else
			{
				temp_flash_buf = 0;
				for (k = 0; k < WORD_WIDTH; k++)
				{
					temp_flash_buf |= temp_data[j*4+k] << k*8;
				}
				j++;
				page_data[i] = temp_flash_buf;
			}
		}
		else
		{
			temp_flash_buf = 0;
			for (k = 0; k < WORD_WIDTH; k++)
			{
				temp_flash_buf |= old_data[i] & (0xFF<< k*8);
			}
			page_data[i] = temp_flash_buf;
		}
	}
	Flash_pe=0;
	FLASH_ErasePage(Page_Address);  //erase a flash page, FLASH_PAGE_SIZE

	FLASH->CMD = FLASH_WRITE_CMD | (Page_Address & FLASH_ADDR_MASK) ;
	status=FLASH_WaitForPeEnd(ProgramTimeout);
	return status;
}


#endif


uint8 FLASH_WritePage(uint32 Page_Address, uint8 *data, uint32 num)
{
	uint32 temp_flash_buf;
	uint8 status;
	uint8 *temp_data = data;
	Page_Address |= LS1D_FLASH_ADDR;									//addr加上LS1D_FLASH_ADDR（0xbf000000）基地址
	assert_param(IS_FLASH_ADDRESS(Page_Address));
	FLASH->CMD = FLASH_PAGE_LATCH_CLEAR;     							//FLASH_CMD_REG=0x40000000
	uint32 flash_block_mask = FLASH_PAGE_SIZE - 1;  					//flash_block_mask=127（0x0000007F）
//	uint32 *page_data = (volatile uint32 *)(Page_Address & ~flash_block_mask);	//*page_data指针指向addr地址的页首地址
	uint32 *old_data = (volatile uint32 *)(Page_Address & ~flash_block_mask);	//*old_data指针指向addr地址的页首地址
	uint32 page_data[32] = {0};

	uint32 i, j = 0, k, offset;
	uint32 count = num;
	uint32 num_left = 0,left_count = 0;
	uint32 num_right = 0;
	uint32 addr_left_align = 0xffffffff;
	uint32 addr_right_align = 0xffffffff;
	uint32 word_mask = WORD_WIDTH - 1;		//word_mask=3

	num = 0;
	num_left = Page_Address & word_mask;   	//addr=0x1E853,word_mask=3(0x00003),addr& word_mask= 1
	if (num_left) 							//假如num_left=1
	{
		num_left = WORD_WIDTH - num_left;   //num_left=3
		num++;								//num=1
		addr_left_align = (Page_Address & flash_block_mask) >> 2; //addr_left_align更改为以4字节对齐的，左对齐起始地址 14
	}
#if 0
	j = count - num_left;   //j=操作起始地址

	num_right = (j & word_mask);
	if (num_right)
	{
		num++;
		addr_right_align = Page_Address + count - num_right;
		addr_right_align = (addr_right_align & flash_block_mask) >> 2;
	}
	j = count - num_left - num_right;
	j = j >> 2;
	num += j;

#endif

	if (num_left<count)
	{
		 j = count - num_left;   //j=操作起始地址10-3=7；=-1=       2-1=1
		 num_right = (j & word_mask); //num_right=4			   num_ringht=1
		 if (num_right)
		 {
			  num++;  //2
			  addr_right_align = Page_Address + count - num_right;//e8
			  addr_right_align = (addr_right_align & flash_block_mask) >> 2;
		 }
		 j = count - num_left - num_right;//j=10-3-3=6,294,967,292   = 0
		 j = j >> 2; //j=1；1,073,741,823
		 num += j;//num=3,073,741,825
		 left_count = num_left;
	}
	else
	{
		left_count = count;
		num = 1;//num=3,073,741,825
	}
	offset = ((Page_Address & flash_block_mask)>>2);  // = 14

	for(j=0, i=0; i<(FLASH_PAGE_SIZE/4); i++)     //共32个字
	{
//		page_data[i] = old_data[i];
		if( (offset <= i)  && (j < num))
		{
			if (i == addr_left_align)
			{
				int m = 0;
				temp_flash_buf = old_data[i];
				k = 1 << ((WORD_WIDTH - num_left) * 8);
				temp_flash_buf &= (k - 1);

				for (m = 0; m < left_count; m++)
				{
					temp_flash_buf |= temp_data[m] << (WORD_WIDTH - num_left + m)*8;
				}
				temp_data = temp_data + left_count;	//address change to be logic 0 again.
				page_data[i] = temp_flash_buf;
				num--;                           	//because j don't add 1, num has to sub 1.
			}
			else if (i == addr_right_align)
			{
				temp_flash_buf = old_data[i];
				k = 1 << (num_right * 8);
				temp_flash_buf &= ~(k - 1);
				for (k = 0; k < num_right; k++)
				{
					temp_flash_buf |= temp_data[j*4+k] << k*8;
				}
				j++;
				page_data[i] = temp_flash_buf;
			}
			else
			{
				temp_flash_buf = 0;
				for (k = 0; k < WORD_WIDTH; k++)
				{
					temp_flash_buf |= temp_data[j*4+k] << k*8;
				}
				j++;
				page_data[i] = temp_flash_buf;
			}
		}
		else
		{
			temp_flash_buf = 0;
			for (k = 0; k < WORD_WIDTH; k++)
			{
				temp_flash_buf |= old_data[i] & (0xFF<< k*8);
			}
			page_data[i] = temp_flash_buf;
		}
	}
	Flash_pe=0;
	FLASH_ErasePage(Page_Address);  //erase a flash page, FLASH_PAGE_SIZE
	for(i=0; i<FLASH_PAGE_SIZE/4; i++)
	{
		old_data[i] = page_data[i];
	}

	FLASH->CMD = FLASH_WRITE_CMD | (Page_Address & FLASH_CMD_ADDR_MASK) ;
//	FLASH->CMD = FLASH_WRITE_CMD | (Page_Address & 0x3ffff) ;
	status=FLASH_WaitForPeEnd(ProgramTimeout);
	return status;
}






/******************************************************************************
 * 函数名： FlashWriteBuffer
 * 功能： 进行写数据自动翻页
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：具有自动换页功能
 ******************************************************************************/
void Flash_WriteBuffer(uint32_t WriteAddr,uint8_t *pBuffer,uint32_t len)
{
	uint16_t pageremain;
	uint32 flash_block_mask = FLASH_PAGE_SIZE - 1;
	uint32_t pagesize = (uint32 *)(WriteAddr & flash_block_mask);  //起始地址位于一页的那个地址
	pageremain = FLASH_PAGE_SIZE- pagesize%FLASH_PAGE_SIZE; //单页剩余的字节数

	//剩余页足够容纳要写入的数据
	if( len <= pageremain) pageremain = len;

	while(1)
	{
		FLASH_WritePage(WriteAddr,pBuffer,pageremain);

		if(len <= pageremain) {

			break;//写入结束了

		}else { 								//len>pageremain
			pBuffer += pageremain;
			WriteAddr += pageremain;
			len -= pageremain;			  		//减去已经写入了的字节数

			if(len > FLASH_PAGE_SIZE) {
				pageremain = FLASH_PAGE_SIZE;   //一次可以写入128个字节
			}else {
				pageremain=len; 	      		//不够128个字节了
			}
		}
	}
}


/**
  * @brief  Waits for a Flash operation to complete or a TIMEOUT to occur.
  * @param  Timeout: FLASH programming Timeout
  * @retval FLASH Status: The returned value can be: verif_correct,
  *         verif_end, pe_end,FLASH_TIMEOUTor no_permission.
  */
uint8 FLASH_WaitForPeEnd(uint32_t Timeout)
{
	uint8 status;

  /* Check for the Flash Status */
  /* Wait for a Flash operation to complete or a TIMEOUT to occur */
  status = FLASH_GetStatus();
 // while((Timeout != 0x00)&& ((status & 0x04)==0x00))
  while((Timeout != 0x00)&& (status != 0x04))
  {
// (status != pe_end) &&	status = FLASH_GetStatus();
	status = FLASH_GetStatus();
	//CLOCK_DelayMs(1);
	Timeout--;
  }
  if(Timeout == 0x00 )
  {
	status = FLASH_TIMEOUT;
  }
  /* Return the operation status */
  return status;
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
uint8 FLASH_GetStatus(void)
{
	uint8 status;
    status=(FLASH->STS & 0x0F);
    return status;
}
/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg FLASH_FLAG_VERIFCORRECT: Verify Correct flag
  *     @arg FLASH_FLAG_VERIFEND: Verify End flag
  *     @arg FLASH_FLAG_PEEND: Pe End flag
  *     @arg FLASH_FLAG_NOPERMISSION: No Permission flag
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
    ITStatus bitstatus = RESET;
    assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG)) ;
    if((FLASH->STS & FLASH_FLAG) != (uint32_t)RESET)
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
  * @brief  Enables or disables the specified FLASH interrupts.
  * @param  NewState: new state of the specified Flash interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FLASH_CONFIG_IT(FLASH_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

    (NewState != DISABLE)? (SET_BIT(FLASH->PET,FLASH_IT)) : (CLEAR_BIT(FLASH->PET,FLASH_IT));

}
/**
  * @brief  Enables or disables the FLASH interrupts.
  * @param  NewState: new state of the specified Flash interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_ITCmd(FunctionalState NewState)
{
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	(NewState != DISABLE)? (SET_BIT(INT->INT_EN,IRQ_FLASH)) : (CLEAR_BIT(INT->INT_EN,IRQ_FLASH));	//清除中断标记位
}
/**
  * @brief  Clears the FLASH's interrupt flag.
  * @retval None
  */
void FLASH_ClearIT(void)
{
	/* clear data reg*/
	SET_BIT(FLASH->CMD , FLASH_INT_CLEAR);
	SET_BIT(INT->INT_CLR,IRQ_FLASH);	//清除中断标记位

}

#if 0
/**
 *@brief  Example of FLASH Write.
 *retval None
 */
void FLASH_WiteTest(uint32 Page_Address,uint8 Page_data)
{
    uint8 temp[128]={0};
    uint32 USER_BEGIN = Page_Address;
	FLASH_Status status;
    int i;
    for(i=0;i<128;i++)
		temp[i] = Page_data;
	Flash_pe=0;
    status=FLASH_WritePage(USER_BEGIN, temp, FLASH_PAGE_SIZE);
}

/**
 *@brief  Example of FLASH Read.
 *retval None
 */
void FLASH_ReadTest(uint32 Page_Address)
{
    uint8 temp[128]={0};
    uint32 USER_BEGIN = Page_Address;

    int i;
    FLASH_ReadPage(USER_BEGIN,temp,FLASH_PAGE_SIZE);
	for(i=0;i<128;i++)
	{
	    if(i%9 == 0)
			printf("\r\n");
	    printf("%02x ",temp[i]);	//十六进制输出
	}
}
#endif

