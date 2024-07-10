/********************************************************************
* 文件名:  ls1d6_std_flash.h
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.12.18
* 说明:    本文件包含片上flash的底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef _FLASH_H_
#define _FLASH_H_


#include "ls1d.h"
#include "ls1d_std_cslreg.h"
#include"Main.h"


#define FLASH_KEY_UPDATE		         0xF0000000
#define FLASH_WRITE_CMD			         0xE0000000
#define FLASH_SLEEPMODE			         0xC0000000
#define FLASH_ERASE_CMD			         0xA0000000
#define FLASH_PROTECTAREA_UPDATE	     0x90000000
#define FLASH_PAGE_LATCH_CLEAR	         0x40000000
#define FLASH_INT_CLEAR				     0x30000000
#define FLASH_DATA_VERIFY			     0x10000000

#define FLASH_CMD_ADDR_MASK			         0x3ff80//0x7ffff80

#define FLASH_Command_Daddr_OFFSET		 0
#define FLASH_Command_Daddr_MASK		 0xffff
#define FLASH_Command_Cmd_OFFSET		 28
#define FLASH_Command_Cmd_MASK			 0xf

#define FLASH_Command_erase_page		 (0xa<<FLASH_Command_Cmd_OFFSET)
#define FLASH_Command_prog_page			 (0xe<<FLASH_Command_Cmd_OFFSET)
#define FLASH_Command_clr_page_latch	 (0x4<<FLASH_Command_Cmd_OFFSET)
#define FLASH_Command_check_page		 (0x1<<FLASH_Command_Cmd_OFFSET)
#define FLASH_Command_update_key		 (0xf<<FLASH_Command_Cmd_OFFSET)
#define FLASH_Command_update_bound		 (0x9<<FLASH_Command_Cmd_OFFSET)
#define FLASH_Command_clr_int			 (0x3<<FLASH_Command_Cmd_OFFSET)

#define	LS1D_FLASH_ADDR			       	 FLASH_BASE
#define	LS1D_FLASH_TOTAL		         0x0001ffff		//128KB
#define FLASH_PAGE_SIZE			         128
#define	WORD_WIDTH				         4			//every time for wirte is word width.
#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= 0x1f000000) && ((ADDRESS) < 0x1f01FFFF))

#define FLASH_PE_FAILURE_IT                 ((uint32_t)0x020000)/* ��дʧ�� */
#define FLASH_PE_IT                        	((uint32_t)0x010000)/* ��д����*/
#define IRQ_FLASH       					((uint8_t)0x10)
#define IS_FLASH_CONFIG_IT(IT) (((IT) == FLASH_PE_IT) || ((IT) == FLASH_PE_FAILURE_IT))

#define FLASH_FLAG_VERIFCORRECT				((uint32_t)0x00000001)  /*!< FLASH Verify Correct flag */
#define FLASH_FLAG_VERIFEND					((uint32_t)0x00000002)  /*!< FLASH Verify End flag */
#define FLASH_FLAG_PEEND					((uint32_t)0x00000004)  /*!< FLASH Erase End flag */
#define FLASH_FLAG_NOPERMISSION				((uint32_t)0x00000008)  /*!< FLASH No Permission flag */

#define IS_FLASH_GET_FLAG(FLAG)  (((FLAG) == FLASH_FLAG_NOPERMISSION) || ((FLAG) == FLASH_FLAG_PEEND) || \
                                  ((FLAG) == FLASH_FLAG_VERIFEND) || ((FLAG) == FLASH_FLAG_VERIFCORRECT))


#define EraseTimeout          ((uint32_t)0x00002000)
#define ProgramTimeout        ((uint32_t)0x00001000)
//#define EraseTimeout          ((uint32_t)0x000B0000)
//#define ProgramTimeout        ((uint32_t)0x20000000)

typedef enum
{
	verif_correct = 1,
	verif_end = 2,
	pe_end = 4,
	no_permission = 8,
	FLASH_TIMEOUT = 16
}FLASH_Status;


void FLASH_ErasePage(uint32 addr);									//FLASH页擦除
void FLASH_EraseUserFlash(uint32 addr);								//FLASH擦除用户区
int32 FLASH_ReadPage(uint32 addr, uint8 *data, uint32 num);			//FLASH页读取
uint8 FLASH_WritePage(uint32 addr, uint8 *data, uint32 num);	//FLASH页编程
void Flash_WriteBuffer(uint32_t WriteAddr,uint8_t *pBuffer,uint32_t len);
uint8 FLASH_WaitForPeEnd(uint32_t Timeout);					//FLASH等待编程结束
uint8 FLASH_GetStatus(void);										//FLASH当前状态获取
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);				//FLASH状态查询
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);	//FLASH中断设置
void FLASH_ITCmd(FunctionalState NewState);	//FLASH中断设置
void FLASH_ClearIT(void);											//FLASH中断标志清除

 void FLASH_WiteTest(uint32 Page_Address,uint8 Page_data);			//FLASH写测试
 void FLASH_ReadTest(uint32 addr);									//FLASH读测试

#endif

