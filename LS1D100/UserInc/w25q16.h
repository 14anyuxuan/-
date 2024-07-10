/*
 * w25q16.h
 *
 *  Created on: 2021年1月18日
 *      Author: Administrator
 */

#ifndef INCLUDE_W25Q16_H_
#define INCLUDE_W25Q16_H_

#include "../include/ls1d_std_clock.h"
#include "../include/ls1d_std_spi.h"
#include "GlobalDef.h"
#define  Spi_W25Q16

#ifdef Spi_W25Q16
//W25X系列/Q系列芯片列表
//#define W25Q80 	0XEF13
//#define W25Q16 	0XEF14
//#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
//#define W25Q128	0XEF17

extern uint16_t W25QXX_TYPE;					//定义W25QXX芯片型号

//#define	W25QXX_CS 		PBout(12)  		//W25QXX的片选信号

////////////////////////////////////////////////////////////////////////////

//指令表
#define PAGE_SIZE           256u
#define SECTOR_SIZE         (256u * 16u)
#define BLOCK32_SIZE        (256u * 16u * 8u)
#define BLOCK64_SIZE        (256u * 16u * 16u)

#define W25X_WriteEnable		0x06
#define W25X_WriteDisable		0x04
#define W25X_ReadStatusReg		0x05
#define W25X_WriteStatusReg		0x01
#define W25X_ReadData			0x03
#define W25X_FastReadData		0x0B
#define W25X_FastReadDual		0x3B
#define W25X_PageProgram		0x02
#define W25X_BlockErase			0xD8
#define W25X_Block32Erase   	0x52
#define W25X_Block64Erase   	0xD8
#define W25X_SectorErase		0x20
#define W25X_ChipErase			0xC7
#define W25X_PowerDown			0xB9
#define W25X_ReleasePowerDown	0xAB
#define W25X_DeviceID			0xAB
#define W25X_ManufactDeviceID	0x90
#define W25X_JedecDeviceID		0x9F


/* Status Registers 1 (s7~s0) */
#define SR1_BUSY            0x01u
#define SR1_WEL             0x02u
#define SR1_BP0             0x04u
#define SR1_BP1             0x08u
#define SR1_BP2             0x10u
#define SR1_TB              0x20u
#define SR1_SEC             0x40u
#define SR1_SRP             0x80u

#define FlashCsEnable()     SpiFlashCsn0Enable()
#define FlashCsDisable()	SpiFlashCsn0Disable()
#define DUMMY				0xFF





/******************************************************************************
 * 函数名： W25Q16ReadSR
 * 功能： 通过SPI读W25Q16状态寄存器
 * 输入参数：
 * 返回值：
 *       byte：状态寄存器的值
 * 备注：
 *    BIT7  6   5   4   3   2   1   0
 *    SPR   RV  TB BP2 BP1 BP0 WEL BUSY
 *    SPR:默认0,状态寄存器保护位,配合WP使用，TB,BP2,BP1,BP0:FLASH区域写保护设置
 *    WEL:写使能锁定，BUSY:忙标记位(1,忙;0,空闲)
 *    默认:0x00
 ******************************************************************************/
extern uint8_t W25Q16ReadSR(void);

/******************************************************************************
 * 函数名： W25Q16ReadSR
 * 功能： 通过SPI写W25QXX状态寄存器
 * 输入参数：
 * 返回值：
 *       byte：状态寄存器的值
 * 备注：
 *   只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
 ******************************************************************************/
extern void W25Q16WriteSR(uint8_t data);
/******************************************************************************
 * 函数名： W25Q16WriteEnable
 * 功能： 通过SPI写W25QXX写使能(将WEL置位)
 * 输入参数：none
 * 返回值：
 *      none
 * 备注：
 *
 ******************************************************************************/
extern void W25Q16WriteEnable(void);

/******************************************************************************
 * 函数名： W25Q16WriteDisable
 * 功能： 通过SPI写W25Q16写禁止(将WEL清零)
 * 输入参数：none
 * 返回值：
 *      none
 * 备注：
 *  none
 ******************************************************************************/
extern void W25Q16WriteDisable(void);
/******************************************************************************
 * 函数名： W25Q16WaitBusy
 * 功能： 等待空闲
 * 输入参数：none
 * 返回值：
 *      none
 * 备注：
 *  none
 ******************************************************************************/
extern void W25Q16WaitBusy(void);
/******************************************************************************
 * 函数名： W25Q16PowerDown
 * 功能：进入掉电模式
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：
 ******************************************************************************/
extern void W25Q16PowerDown(void);
/******************************************************************************
 * 函数名： W25Q16PowerDown
 * 功能：唤醒
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：
 ******************************************************************************/
extern void W25Q16WakeUp(void);

/******************************************************************************
 * 函数名： W25Q16FlashRead
 * 功能： 读flash数据
 * 输入参数：
 * 		  address：读数据的首地址
 * 		  *data:代读取地址
 * 		  len：读取数据长度
 * 返回值：
 *      none
 * 备注：无
 ******************************************************************************/
extern uint8_t W25Q16FlashRead(uint32_t Address,uint8_t *data,uint16_t len);
/******************************************************************************
 * 函数名： W25Q16FlashWrite
 * 功能： 通过SPI接口传输写字节
 * 输入参数：
 * 		  address：写数据的首地址（24bit）
 * 		  *data:开始写的数据
 * 		  len：读取数据长度(最大256)
 * 返回值：
 *      none
 * 备注： SPI在一页(0~65535)内写入少于256个字节的数据，在指定地址开始写入最大256字节的数据
 * 		要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!
 ******************************************************************************/
extern uint8_t W25Q16FlashWrite(uint32_t address,uint8_t *data,uint16_t len);

/******************************************************************************
 * 函数名： W25Q16ReadID
 * 功能： 读取芯片ID
 * 输入参数：none
 * 返回值：
 *      ID
 * 备注：
 *  0XEF13,表示芯片型号为W25Q80
 *	0XEF14,表示芯片型号为W25Q16
 *	0XEF15,表示芯片型号为W25Q32
 *	0XEF16,表示芯片型号为W25Q64
 *	0XEF17,表示芯片型号为W25Q128
 ******************************************************************************/
extern uint16_t W25Q16ReadID(void);

extern void W25Q16ReadChipID(uint8_t *rbuf);

/******************************************************************************
 * 函数名： W25Q16SectorErase
 * 功能： 擦除一扇字节
 * 输入参数：
 * 		  address：写数据的首地址（24bit）
 * 返回值：
 *
 * 备注：  擦除一个山区的最少时间:150ms
 ******************************************************************************/
extern void W25Q16SectorErase(uint32_t addr);
extern void W25Q16Block32Erase(uint32_t addr);
extern void W25Q16Block64Erase(uint32_t addr);
/******************************************************************************
 * 函数名： W25Q16ChipErase
 * 功能： 擦除整个芯片的字节
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：  等待时间超长...
 ******************************************************************************/
extern void W25Q16ChipErase(void);

/******************************************************************************
 * 函数名： W25Q16WriteBuffer
 * 功能： 进行写数据自动翻页
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：具有自动换页功能
 ******************************************************************************/
extern void W25Q16WriteBuffer(uint32_t WriteAddr,uint8_t *pBuffer,uint16_t len);

#if 0
/******************************************************************************
 * 函数名： W25Q16WriteBufferWithErase
 * 功能： 进行写数据自动翻页带数据校验和扇擦除
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：写前读出数据判断非0XFF,先擦除再写数据
 ******************************************************************************/
extern void W25Q16WriteBufferWithErase(uint32_t WriteAddr,uint8_t *pBuffer,uint16_t len);
#endif
/******************************************************************************
 * 函数名： sFlash_SectorAlignedProgram
 * 功能： 对齐扇进行写数据
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：写数据整页的写
 ******************************************************************************/
extern void sFlash_PageAlignedProgram(uint32_t addr, uint8_t *wbuf, uint32_t length);
extern void sFlash_SectorAlignedProgram(uint32_t addr, uint8_t *wbuf, uint32_t length);
extern void sFlash_AnywhereProgram(uint32_t addr, uint8_t *wbuf, uint32_t length);
extern void FlashTestTask(void);



#endif

#endif /* INCLUDE_W25Q16_H_ */
