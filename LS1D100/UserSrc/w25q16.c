/*
 * w25q16.c
 *
 *  Created on: 2021年1月18日
 *      Author: LX
 */
#include "w25q16.h"

#include "../include/ls1d_std_printf.h"
#include "../include/ls1d_std_str_other.h"


#ifdef Spi_W25Q16


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
uint8_t W25Q16ReadSR(void)
{
	uint8_t byte=0;
	FlashCsEnable();                        //使能器件
	SPI_TransByte(W25X_ReadStatusReg); //发送读取状态寄存器命令
	byte=SPI_TransByte(0xFF);          //读取一个字节
	FlashCsDisable();                       //取消片选
	return byte;
}

/******************************************************************************
 * 函数名： W25Q16ReadSR
 * 功能： 通过SPI写W25QXX状态寄存器
 * 输入参数：
 * 返回值：
 *       byte：状态寄存器的值
 * 备注：
 *   只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
 ******************************************************************************/
void W25Q16WriteSR(uint8_t data)
{
	FlashCsEnable();                            //使能器件
	SPI_TransByte(W25X_WriteStatusReg);	//发送写取状态寄存器命令
	SPI_TransByte(data);               	//写入一个字节
	FlashCsDisable();                           //取消片选
}

/******************************************************************************
 * 函数名： W25Q16WriteEnable
 * 功能： 通过SPI写W25QXX写使能(将WEL置位)
 * 输入参数：none
 * 返回值：
 *      none
 * 备注：
 *
 ******************************************************************************/
void W25Q16WriteEnable(void)
{
	W25Q16WaitBusy();
	FlashCsEnable();                          	//使能器件
	SPI_TransByte(W25X_WriteEnable); 		    //发送写使能
    FlashCsDisable();                          	//取消片选
}

/******************************************************************************
 * 函数名： W25Q16WriteDisable
 * 功能： 通过SPI写W25Q16写禁止(将WEL清零)
 * 输入参数：none
 * 返回值：
 *      none
 * 备注：
 *  none
 ******************************************************************************/
void W25Q16WriteDisable(void)
{
	FlashCsEnable();                          	//使能器件
	SPI_TransByte(W25X_WriteEnable); 		//发送写使能
    FlashCsDisable();                          	//取消片选
}

//等待空闲
void W25Q16WaitBusy(void)
{
	 while((W25Q16ReadSR()&SR1_BUSY)==0x01)   		// 等待BUSY位清空
	 {
		 CLOCK_DelayUs(1);
	 }
}

/******************************************************************************
 * 函数名： W25Q16PowerDown
 * 功能：进入掉电模式
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：具有自动换页功能
 ******************************************************************************/
void W25Q16PowerDown(void)
{
	FlashCsEnable();                           	 	//使能器件
	SPI_TransByte(W25X_PowerDown);        //发送掉电命令
    FlashCsDisable();                            	//取消片选
    CLOCK_DelayUs(3);                               //等待TPD
}
/******************************************************************************
 * 函数名： W25Q16PowerDown
 * 功能：唤醒
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：具有自动换页功能
 ******************************************************************************/
void W25Q16WakeUp(void)
{
	FlashCsEnable();                            	//使能器件
	SPI_TransByte(W25X_ReleasePowerDown);	//  send W25X_PowerDown command 0xAB
    FlashCsDisable();                            	//取消片选
    CLOCK_DelayUs(3);                            	//等待TRES1
}

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
uint8_t W25Q16FlashRead(uint32_t Address,uint8_t *data,uint16_t len)
{
	int i = 0;
	FlashCsEnable();

	SPI_TransByte(W25X_ReadData);         		//发送读取命令
	SPI_TransByte((uint8_t)((Address)>>16));  	//发送24bit地址
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
uint8_t W25Q16FlashWrite(uint32_t address,uint8_t *data,uint16_t len)
{
	int i = 0;
	W25Q16WriteEnable();                  	//SET WEL

	FlashCsEnable();
	SPI_TransByte(W25X_PageProgram);      	     //发送写页命令
	SPI_TransByte((address & 0x00ff0000u) >> 16u);//发送24bit地址
	SPI_TransByte((address & 0x0000ff00u) >> 8u);
	SPI_TransByte(address & 0x000000ffu);

	for(;i<len;i++)
	{
		SPI_TransByte(data[i]);
	}
	FlashCsDisable();
	W25Q16WaitBusy();					   		//等待写入结束
	return 0;
}


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
uint16_t W25Q16ReadID(void)
{
	uint16_t Temp = 0;
	FlashCsEnable();

	SPI_TransByte(0x90);//发送读取ID命令
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
 * 函数名： W25Q16SectorErase
 * 功能： 擦除一扇字节
 * 输入参数：
 * 		  address：写数据的首地址（24bit）
 * 返回值：
 *
 * 备注：  擦除一个山区的最少时间:150ms
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
 * 函数名： W25Q16ChipErase
 * 功能： 擦除整个芯片的字节
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：  等待时间超长...
 ******************************************************************************/
void W25Q16ChipErase(void)
{
	W25Q16WaitBusy();
	W25Q16WriteEnable();
    FlashCsEnable();                            //使能器件
    SPI_TransByte(W25X_ChipErase);        	    //发送片擦除命令
    FlashCsDisable();                           //取消片选
    W25Q16WaitBusy();   				   		//等待芯片擦除结束
}



/******************************************************************************
 * 函数名： W25Q16WriteBuffer
 * 功能： 进行写数据自动翻页
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：具有自动换页功能
 ******************************************************************************/
void W25Q16WriteBuffer(uint32_t WriteAddr,uint8_t *pBuffer,uint16_t len)
{

	uint16_t pageremain;
	pageremain = 256- WriteAddr%256; //单页剩余的字节数
	if(len<=pageremain)
		pageremain = len;//不大于256个字节
	while(1)
	{
		W25Q16FlashWrite(WriteAddr,pBuffer,pageremain);
		if(len <= pageremain)
		{
			break;//写入结束了
		}else //len>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;

			len-=pageremain;			  //减去已经写入了的字节数
			if(len >256)pageremain=256;   //一次可以写入256个字节
			else pageremain=len; 	      //不够256个字节了
		}
	};
}
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
 	secpos=WriteAddr/4096;//扇区地址
	secoff=WriteAddr%4096;//在扇区内的偏移
	secremain=4096-secoff;//扇区剩余空间大小
 	//IR_printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//测试用
 	if(len<=secremain)secremain=len;//不大于4096个字节
 	memset(W25QXX_BUF,0,4096);

	while(1)
	{
		W25Q16FlashRead(secpos*4096,W25QXX_BUF,4096);//读出整个扇区的内容
		for(i=0;i<secremain;i++)//校验数据
		{
			if(W25QXX_BUF[secoff+i]!=0XFF)break;//需要擦除
		}
		if(i<secremain)//需要擦除
		{
			W25Q16SectorErase(secpos);		//擦除这个扇区
			for(i=0;i<secremain;i++)	   		//复制
			{
				W25QXX_BUF[i+secoff]=pBuffer[i];
			}
			W25Q16WriteBuffer(secpos*4096,W25QXX_BUF,4096);//写入整个扇区

		}else W25Q16WriteBuffer(WriteAddr,pBuffer,secremain);//写已经擦除了的,直接写入扇区剩余区间.
		if(len==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;//扇区地址增1
			secoff=0;//偏移位置为0

		   	pBuffer+=secremain;  				//指针偏移
			WriteAddr+=secremain;				//写地址偏移
		   	len-=secremain;						//字节数递减
			if(len > 4096)secremain=4096;//下一个扇区还是写不完
			else secremain = len;		//下一个扇区可以写完了
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
 * 函数名： sFlash_SectorAlignedProgram
 * 功能： 对齐扇进行写数据
 * 输入参数：
 * 		  none
 * 返回值：
 *
 * 备注：具有自动换页功能
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


















