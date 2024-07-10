/*
 * w25q16.c
 *
 *  Created on: 2021��1��18��
 *      Author: LX
 */
#include "w25q16.h"

#include "../include/ls1d_std_printf.h"
#include "../include/ls1d_std_str_other.h"


#ifdef Spi_W25Q16


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
uint8_t W25Q16ReadSR(void)
{
	uint8_t byte=0;
	FlashCsEnable();                        //ʹ������
	SPI_TransByte(W25X_ReadStatusReg); //���Ͷ�ȡ״̬�Ĵ�������
	byte=SPI_TransByte(0xFF);          //��ȡһ���ֽ�
	FlashCsDisable();                       //ȡ��Ƭѡ
	return byte;
}

/******************************************************************************
 * �������� W25Q16ReadSR
 * ���ܣ� ͨ��SPIдW25QXX״̬�Ĵ���
 * ���������
 * ����ֵ��
 *       byte��״̬�Ĵ�����ֵ
 * ��ע��
 *   ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
 ******************************************************************************/
void W25Q16WriteSR(uint8_t data)
{
	FlashCsEnable();                            //ʹ������
	SPI_TransByte(W25X_WriteStatusReg);	//����дȡ״̬�Ĵ�������
	SPI_TransByte(data);               	//д��һ���ֽ�
	FlashCsDisable();                           //ȡ��Ƭѡ
}

/******************************************************************************
 * �������� W25Q16WriteEnable
 * ���ܣ� ͨ��SPIдW25QXXдʹ��(��WEL��λ)
 * ���������none
 * ����ֵ��
 *      none
 * ��ע��
 *
 ******************************************************************************/
void W25Q16WriteEnable(void)
{
	W25Q16WaitBusy();
	FlashCsEnable();                          	//ʹ������
	SPI_TransByte(W25X_WriteEnable); 		    //����дʹ��
    FlashCsDisable();                          	//ȡ��Ƭѡ
}

/******************************************************************************
 * �������� W25Q16WriteDisable
 * ���ܣ� ͨ��SPIдW25Q16д��ֹ(��WEL����)
 * ���������none
 * ����ֵ��
 *      none
 * ��ע��
 *  none
 ******************************************************************************/
void W25Q16WriteDisable(void)
{
	FlashCsEnable();                          	//ʹ������
	SPI_TransByte(W25X_WriteEnable); 		//����дʹ��
    FlashCsDisable();                          	//ȡ��Ƭѡ
}

//�ȴ�����
void W25Q16WaitBusy(void)
{
	 while((W25Q16ReadSR()&SR1_BUSY)==0x01)   		// �ȴ�BUSYλ���
	 {
		 CLOCK_DelayUs(1);
	 }
}

/******************************************************************************
 * �������� W25Q16PowerDown
 * ���ܣ��������ģʽ
 * ���������
 * 		  none
 * ����ֵ��
 *
 * ��ע�������Զ���ҳ����
 ******************************************************************************/
void W25Q16PowerDown(void)
{
	FlashCsEnable();                           	 	//ʹ������
	SPI_TransByte(W25X_PowerDown);        //���͵�������
    FlashCsDisable();                            	//ȡ��Ƭѡ
    CLOCK_DelayUs(3);                               //�ȴ�TPD
}
/******************************************************************************
 * �������� W25Q16PowerDown
 * ���ܣ�����
 * ���������
 * 		  none
 * ����ֵ��
 *
 * ��ע�������Զ���ҳ����
 ******************************************************************************/
void W25Q16WakeUp(void)
{
	FlashCsEnable();                            	//ʹ������
	SPI_TransByte(W25X_ReleasePowerDown);	//  send W25X_PowerDown command 0xAB
    FlashCsDisable();                            	//ȡ��Ƭѡ
    CLOCK_DelayUs(3);                            	//�ȴ�TRES1
}

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
uint8_t W25Q16FlashRead(uint32_t Address,uint8_t *data,uint16_t len)
{
	int i = 0;
	FlashCsEnable();

	SPI_TransByte(W25X_ReadData);         		//���Ͷ�ȡ����
	SPI_TransByte((uint8_t)((Address)>>16));  	//����24bit��ַ
	SPI_TransByte((uint8_t)((Address)>>8));
	SPI_TransByte((uint8_t)Address);

	for(;i<len;i++)
	{
		data[i] = SPI_TransByte(0xFF);
	}

	FlashCsDisable();
	return 0;
}

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
uint8_t W25Q16FlashWrite(uint32_t address,uint8_t *data,uint16_t len)
{
	int i = 0;
	W25Q16WriteEnable();                  	//SET WEL

	FlashCsEnable();
	SPI_TransByte(W25X_PageProgram);      	     //����дҳ����
	SPI_TransByte((address & 0x00ff0000u) >> 16u);//����24bit��ַ
	SPI_TransByte((address & 0x0000ff00u) >> 8u);
	SPI_TransByte(address & 0x000000ffu);

	for(;i<len;i++)
	{
		SPI_TransByte(data[i]);
	}
	FlashCsDisable();
	W25Q16WaitBusy();					   		//�ȴ�д�����
	return 0;
}


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
uint16_t W25Q16ReadID(void)
{
	uint16_t Temp = 0;
	FlashCsEnable();

	SPI_TransByte(0x90);//���Ͷ�ȡID����
	SPI_TransByte(0x00);
	SPI_TransByte(0x00);
	SPI_TransByte(0x00);
	Temp|=SPI_TransByte(0xFF)<<8;
	Temp|=SPI_TransByte(0xFF);

	FlashCsDisable();
	return Temp;
}

void W25Q16ReadChipID(uint8_t *rbuf)
{
	FlashCsEnable();

	SPI_TransByte(0x9F);

	rbuf[0] = SPI_TransByte(DUMMY);
	rbuf[1] = SPI_TransByte(DUMMY);
	rbuf[2] = SPI_TransByte(DUMMY);

	FlashCsDisable();
}

/******************************************************************************
 * �������� W25Q16SectorErase
 * ���ܣ� ����һ���ֽ�
 * ���������
 * 		  address��д���ݵ��׵�ַ��24bit��
 * ����ֵ��
 *
 * ��ע��  ����һ��ɽ��������ʱ��:150ms
 ******************************************************************************/
void W25Q16SectorErase(uint32_t addr)
{
	W25Q16WriteEnable();

	W25Q16WaitBusy();

	FlashCsEnable();

	SPI_TransByte(W25X_SectorErase);
	SPI_TransByte((addr & 0x00ff0000u) >> 16u);
	SPI_TransByte((addr & 0x0000ff00u) >> 8u);
	SPI_TransByte(addr & 0x000000ffu);

	FlashCsDisable();

	W25Q16WaitBusy();
}



void W25Q16Block32Erase(uint32_t addr)
{
	W25Q16WaitBusy();
	W25Q16WriteEnable();
	FlashCsEnable();

	SPI_TransByte(W25X_Block32Erase);
	SPI_TransByte((addr & 0x00ff0000u) >> 16u);
	SPI_TransByte((addr & 0x0000ff00u) >> 8u);
	SPI_TransByte(addr & 0x000000ffu);

	FlashCsDisable();

	W25Q16WaitBusy();
}

void W25Q16Block64Erase(uint32_t addr)
{

	W25Q16WaitBusy();
	W25Q16WriteEnable();

	FlashCsEnable();

	SPI_TransByte(W25X_Block64Erase);
	SPI_TransByte((addr & 0x00ff0000u) >> 16u);
	SPI_TransByte((addr & 0x0000ff00u) >> 8u);
	SPI_TransByte(addr & 0x000000ffu);

	FlashCsDisable();

	W25Q16WaitBusy();

}
/******************************************************************************
 * �������� W25Q16ChipErase
 * ���ܣ� ��������оƬ���ֽ�
 * ���������
 * 		  none
 * ����ֵ��
 *
 * ��ע��  �ȴ�ʱ�䳬��...
 ******************************************************************************/
void W25Q16ChipErase(void)
{
	W25Q16WaitBusy();
	W25Q16WriteEnable();
    FlashCsEnable();                            //ʹ������
    SPI_TransByte(W25X_ChipErase);        	    //����Ƭ��������
    FlashCsDisable();                           //ȡ��Ƭѡ
    W25Q16WaitBusy();   				   		//�ȴ�оƬ��������
}



/******************************************************************************
 * �������� W25Q16WriteBuffer
 * ���ܣ� ����д�����Զ���ҳ
 * ���������
 * 		  none
 * ����ֵ��
 *
 * ��ע�������Զ���ҳ����
 ******************************************************************************/
void W25Q16WriteBuffer(uint32_t WriteAddr,uint8_t *pBuffer,uint16_t len)
{

	uint16_t pageremain;
	pageremain = 256- WriteAddr%256; //��ҳʣ����ֽ���
	if(len<=pageremain)
		pageremain = len;//������256���ֽ�
	while(1)
	{
		W25Q16FlashWrite(WriteAddr,pBuffer,pageremain);
		if(len <= pageremain)
		{
			break;//д�������
		}else //len>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;

			len-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(len >256)pageremain=256;   //һ�ο���д��256���ֽ�
			else pageremain=len; 	      //����256���ֽ���
		}
	};
}
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
//uint8_t W25QXX_BUFFER[4096];
void W25Q16WriteBufferWithErase(uint32_t WriteAddr,uint8_t *pBuffer,uint16_t len)
{
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;
 	uint16_t i;
	uint8_t W25QXX_BUFFER[4096];
	uint8_t * W25QXX_BUF;
   	W25QXX_BUF=W25QXX_BUFFER;
 	secpos=WriteAddr/4096;//������ַ
	secoff=WriteAddr%4096;//�������ڵ�ƫ��
	secremain=4096-secoff;//����ʣ��ռ��С
 	//IR_printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//������
 	if(len<=secremain)secremain=len;//������4096���ֽ�
 	memset(W25QXX_BUF,0,4096);

	while(1)
	{
		W25Q16FlashRead(secpos*4096,W25QXX_BUF,4096);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(W25QXX_BUF[secoff+i]!=0XFF)break;//��Ҫ����
		}
		if(i<secremain)//��Ҫ����
		{
			W25Q16SectorErase(secpos);		//�����������
			for(i=0;i<secremain;i++)	   		//����
			{
				W25QXX_BUF[i+secoff]=pBuffer[i];
			}
			W25Q16WriteBuffer(secpos*4096,W25QXX_BUF,4096);//д����������

		}else W25Q16WriteBuffer(WriteAddr,pBuffer,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������.
		if(len==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;//������ַ��1
			secoff=0;//ƫ��λ��Ϊ0

		   	pBuffer+=secremain;  				//ָ��ƫ��
			WriteAddr+=secremain;				//д��ַƫ��
		   	len-=secremain;						//�ֽ����ݼ�
			if(len > 4096)secremain=4096;//��һ����������д����
			else secremain = len;		//��һ����������д����
		}
	};
}

#endif
void sFlash_PageAlignedProgram(uint32_t addr, uint8_t *wbuf, uint32_t length)
{
	uint32_t num_of_page, num_of_single;

	num_of_page = length / PAGE_SIZE;

	if(num_of_page == 0)
	{
		W25Q16FlashWrite(addr, wbuf, length);
	}
	else
	{
		num_of_single = length % PAGE_SIZE;

		while(num_of_page--)
		{
			W25Q16FlashWrite(addr, wbuf, PAGE_SIZE);
			addr +=  PAGE_SIZE;
			wbuf +=  PAGE_SIZE;
		}

		W25Q16FlashWrite(addr, wbuf, num_of_single);
	}
}

/******************************************************************************
 * �������� sFlash_SectorAlignedProgram
 * ���ܣ� �����Ƚ���д����
 * ���������
 * 		  none
 * ����ֵ��
 *
 * ��ע�������Զ���ҳ����
 ******************************************************************************/
void sFlash_SectorAlignedProgram(uint32_t addr, uint8_t *wbuf, uint32_t length)
{
	uint32_t num_of_page, num_of_single;

	if( (addr&0x00000fffu) != 0)
	{
		return;
	}

	num_of_page = length / PAGE_SIZE;

	if(num_of_page == 0)
	{
		W25Q16FlashWrite(addr, wbuf, length);
	}
	else
	{
		num_of_single = length % PAGE_SIZE;

		while(num_of_page--)
		{
			W25Q16FlashWrite(addr, wbuf, PAGE_SIZE);
			addr +=  PAGE_SIZE;
			wbuf +=  PAGE_SIZE;
		}

		W25Q16FlashWrite(addr, wbuf, num_of_single);
	}
}

void sFlash_AnywhereProgram(uint32_t addr, uint8_t *wbuf, uint32_t length)
{
	uint8_t  byte_addr_inpage = 0, byte_num_inpage = 0;

  byte_addr_inpage = addr % PAGE_SIZE;

  if(byte_addr_inpage == 0)
  {
    sFlash_PageAlignedProgram(addr, wbuf, length);
  }
  else
  {
		byte_num_inpage = PAGE_SIZE - byte_addr_inpage;

		W25Q16FlashWrite(addr, wbuf, byte_num_inpage);

		sFlash_PageAlignedProgram(addr + byte_num_inpage, wbuf + byte_num_inpage, length - byte_num_inpage);
  }
}

#endif




#define SFLASH_SYSPARA_ADDR        (volatile unsigned int *)(0xBE000000)
uint16_t devieID;
void FlashTestTask(void)
{
	printf("== <flash test  start> == \r\n");
	uint8_t writebuf[256]={0};
	uint8_t readbuf[256]={0};
	int j = 0,k = 0;
	for(;j<128;j++)
	{
		writebuf[j] = j;
		readbuf[j] = 128 -j;
	}
	devieID =  W25Q16ReadID();
	printf("devieID == %x !\r\n",devieID);
	devieID =  W25Q16ReadSR();
	printf("reg == %x !\r\n",devieID);

	printf("==flash start erase== !\r\n");
	W25Q16SectorErase(SFLASH_SYSPARA_ADDR);
	CLOCK_DelayMs(10);
	printf("flash  erase  finish,next write data into flash!\r\n");

	W25Q16WriteBuffer(SFLASH_SYSPARA_ADDR,writebuf,128);
	printf("flash data is write over!\r\n");
	CLOCK_DelayMs(10);

	W25Q16FlashRead(SFLASH_SYSPARA_ADDR,readbuf,128);
	printf("flash data is read over!\r\n");
	CLOCK_DelayMs(10);

	printf("flash data comparing ... !\r\n");

	for(;k<128;k++)
	{
		if( writebuf[k] != readbuf[k])
		{
			printf("flash data is wrong!!!\r\n");
			printf("wrong data write =  %d ,read = %d, position = %d. \r\n",writebuf[k],readbuf[k],k);
			break;
		}
		else{
			printf("right data write =  %d ,read = %d, position = %d. \r\n",writebuf[k],readbuf[k],k);

		}
		if(k == 127)
			printf(" flash test is success! ~o~ \r\n");
	}

}


















