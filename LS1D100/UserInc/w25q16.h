/*
 * w25q16.h
 *
 *  Created on: 2021��1��18��
 *      Author: Administrator
 */

#ifndef INCLUDE_W25Q16_H_
#define INCLUDE_W25Q16_H_

#include "../include/ls1d_std_clock.h"
#include "../include/ls1d_std_spi.h"
#include "GlobalDef.h"
#define  Spi_W25Q16

#ifdef Spi_W25Q16
//W25Xϵ��/Qϵ��оƬ�б�
//#define W25Q80 	0XEF13
//#define W25Q16 	0XEF14
//#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
//#define W25Q128	0XEF17

extern uint16_t W25QXX_TYPE;					//����W25QXXоƬ�ͺ�

//#define	W25QXX_CS 		PBout(12)  		//W25QXX��Ƭѡ�ź�

////////////////////////////////////////////////////////////////////////////

//ָ���
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
 * �������� W25Q16ReadSR
 * ���ܣ� ͨ��SPI��W25Q16״̬�Ĵ���
 * ���������
 * ����ֵ��
 *       byte��״̬�Ĵ�����ֵ
 * ��ע��
 *    BIT7  6   5   4   3   2   1   0
 *    SPR   RV  TB BP2 BP1 BP0 WEL BUSY
 *    SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ�ã�TB,BP2,BP1,BP0:FLASH����д��������
 *    WEL:дʹ��������BUSY:æ���λ(1,æ;0,����)
 *    Ĭ��:0x00
 ******************************************************************************/
extern uint8_t W25Q16ReadSR(void);

/******************************************************************************
 * �������� W25Q16ReadSR
 * ���ܣ� ͨ��SPIдW25QXX״̬�Ĵ���
 * ���������
 * ����ֵ��
 *       byte��״̬�Ĵ�����ֵ
 * ��ע��
 *   ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
 ******************************************************************************/
extern void W25Q16WriteSR(uint8_t data);
/******************************************************************************
 * �������� W25Q16WriteEnable
 * ���ܣ� ͨ��SPIдW25QXXдʹ��(��WEL��λ)
 * ���������none
 * ����ֵ��
 *      none
 * ��ע��
 *
 ******************************************************************************/
extern void W25Q16WriteEnable(void);

/******************************************************************************
 * �������� W25Q16WriteDisable
 * ���ܣ� ͨ��SPIдW25Q16д��ֹ(��WEL����)
 * ���������none
 * ����ֵ��
 *      none
 * ��ע��
 *  none
 ******************************************************************************/
extern void W25Q16WriteDisable(void);
/******************************************************************************
 * �������� W25Q16WaitBusy
 * ���ܣ� �ȴ�����
 * ���������none
 * ����ֵ��
 *      none
 * ��ע��
 *  none
 ******************************************************************************/
extern void W25Q16WaitBusy(void);
/******************************************************************************
 * �������� W25Q16PowerDown
 * ���ܣ��������ģʽ
 * ���������
 * 		  none
 * ����ֵ��
 *
 * ��ע��
 ******************************************************************************/
extern void W25Q16PowerDown(void);
/******************************************************************************
 * �������� W25Q16PowerDown
 * ���ܣ�����
 * ���������
 * 		  none
 * ����ֵ��
 *
 * ��ע��
 ******************************************************************************/
extern void W25Q16WakeUp(void);

/******************************************************************************
 * �������� W25Q16FlashRead
 * ���ܣ� ��flash����
 * ���������
 * 		  address�������ݵ��׵�ַ
 * 		  *data:����ȡ��ַ
 * 		  len����ȡ���ݳ���
 * ����ֵ��
 *      none
 * ��ע����
 ******************************************************************************/
extern uint8_t W25Q16FlashRead(uint32_t Address,uint8_t *data,uint16_t len);
/******************************************************************************
 * �������� W25Q16FlashWrite
 * ���ܣ� ͨ��SPI�ӿڴ���д�ֽ�
 * ���������
 * 		  address��д���ݵ��׵�ַ��24bit��
 * 		  *data:��ʼд������
 * 		  len����ȡ���ݳ���(���256)
 * ����ֵ��
 *      none
 * ��ע�� SPI��һҳ(0~65535)��д������256���ֽڵ����ݣ���ָ����ַ��ʼд�����256�ֽڵ�����
 * 		Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!
 ******************************************************************************/
extern uint8_t W25Q16FlashWrite(uint32_t address,uint8_t *data,uint16_t len);

/******************************************************************************
 * �������� W25Q16ReadID
 * ���ܣ� ��ȡоƬID
 * ���������none
 * ����ֵ��
 *      ID
 * ��ע��
 *  0XEF13,��ʾоƬ�ͺ�ΪW25Q80
 *	0XEF14,��ʾоƬ�ͺ�ΪW25Q16
 *	0XEF15,��ʾоƬ�ͺ�ΪW25Q32
 *	0XEF16,��ʾоƬ�ͺ�ΪW25Q64
 *	0XEF17,��ʾоƬ�ͺ�ΪW25Q128
 ******************************************************************************/
extern uint16_t W25Q16ReadID(void);

extern void W25Q16ReadChipID(uint8_t *rbuf);

/******************************************************************************
 * �������� W25Q16SectorErase
 * ���ܣ� ����һ���ֽ�
 * ���������
 * 		  address��д���ݵ��׵�ַ��24bit��
 * ����ֵ��
 *
 * ��ע��  ����һ��ɽ��������ʱ��:150ms
 ******************************************************************************/
extern void W25Q16SectorErase(uint32_t addr);
extern void W25Q16Block32Erase(uint32_t addr);
extern void W25Q16Block64Erase(uint32_t addr);
/******************************************************************************
 * �������� W25Q16ChipErase
 * ���ܣ� ��������оƬ���ֽ�
 * ���������
 * 		  none
 * ����ֵ��
 *
 * ��ע��  �ȴ�ʱ�䳬��...
 ******************************************************************************/
extern void W25Q16ChipErase(void);

/******************************************************************************
 * �������� W25Q16WriteBuffer
 * ���ܣ� ����д�����Զ���ҳ
 * ���������
 * 		  none
 * ����ֵ��
 *
 * ��ע�������Զ���ҳ����
 ******************************************************************************/
extern void W25Q16WriteBuffer(uint32_t WriteAddr,uint8_t *pBuffer,uint16_t len);

#if 0
/******************************************************************************
 * �������� W25Q16WriteBufferWithErase
 * ���ܣ� ����д�����Զ���ҳ������У����Ȳ���
 * ���������
 * 		  none
 * ����ֵ��
 *
 * ��ע��дǰ���������жϷ�0XFF,�Ȳ�����д����
 ******************************************************************************/
extern void W25Q16WriteBufferWithErase(uint32_t WriteAddr,uint8_t *pBuffer,uint16_t len);
#endif
/******************************************************************************
 * �������� sFlash_SectorAlignedProgram
 * ���ܣ� �����Ƚ���д����
 * ���������
 * 		  none
 * ����ֵ��
 *
 * ��ע��д������ҳ��д
 ******************************************************************************/
extern void sFlash_PageAlignedProgram(uint32_t addr, uint8_t *wbuf, uint32_t length);
extern void sFlash_SectorAlignedProgram(uint32_t addr, uint8_t *wbuf, uint32_t length);
extern void sFlash_AnywhereProgram(uint32_t addr, uint8_t *wbuf, uint32_t length);
extern void FlashTestTask(void);



#endif

#endif /* INCLUDE_W25Q16_H_ */
