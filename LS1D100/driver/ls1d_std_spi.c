
/********************************************************************
* 文件名:  ls1d6_std_spi.c
* 版本：	  V1.0
* 作者:   白一方、李鑫
* 日期:    2021.10.30
* 说明:    本文件包含spi 总线接口的所有接口函数及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#include "../include/ls1d_std_printf.h"
#include "../include/ls1d_std_spi.h"

#ifdef UserSPI
/**
 * @Description: SPI 分频系数配置 分别配置到控制寄存器、外部寄存器、参数控制寄存器
 * @Input: 分频系数
 * @Output: 无
 * @return {*}无
 * @param {uint8} spr 分频系数
 */
void Spi_FreqDiv(uint8 spr)
{
    
    SPI->SPCR &=0xFC;
    SPI->SPER &=0xFC;

    SPI->SPCR |=(spr & 0x03);
    SPI->SPER |=((spr>>2) & 0x03);
	
	SPI->PARAM &= 0x02;
	SPI->PARAM |=((spr<<4) & 0xF0);
//	 printf("\r\n0 SPI->PARAM:%x H \r\n",SPI->PARAM);
    //printf("\r\n SPI->SPCR:%2x H SPI->SPER:%2x H spr:%2x H",SPI->SPCR,SPI->SPER,spr);
}

#if 0

// void Spi_Init(uint8 spr)
// {
//     CLEAR_BIT(CHIPCTRL, (uint32)(1<<9));//SPI 芯片控制使能
// 	// CHIPCTRL &= ~(1<<9);	//SPI 芯片控制使能
	
// 	SPI->SPCR |=0x40;	//停止SPI控制器工作；
// 	SPI->SPSR =0xC0;	//重置状态寄存器；

//     Spi_SetDiv(spr);    //设置分频系数

// 	// SPI->SPSR =0xC0;	//重置状态寄存器；
// 	// SPI->SPER =0x41;	//设置外部寄存器；
// 	SPI->SPER =0x00;	//设置外部寄存器；
// 	SPI->SPCR =0x12;	//设置外部寄存器；
// 	SPI->SPCR |=0xC0;	//设置外部寄存器；

// 	INT->INT_EN |=SPI_INT_EN;

// }

/**
 * @Description: spi init
 * @Input: spi 分频系数
 * SPI_DIV_2 SPI_DIV_4 SPI_DIV_16  SPI_DIV_32  SPI_DIV_8 SPI_DIV_64  SPI_DIV_128 
 * SPI_DIV_256 SPI_DIV_512 SPI_DIV_1024 SPI_DIV_2048 SPI_DIV_4096
 * @Output: 无
 * @return {*}
 * @param {uint8} spr 分频系数 固定为以上的宏定义
 */
void Spi_Init(uint8 spr)
{
    // SPI->SPCR = 0x50; 
    // SPI->SPER = 0;
    // while(!SPI_TXEMPTY)         ; 
    // while(!SPI_RXEMPTY) SPI->DATA; 

	SPI_CHIP_ENABLE;

	SPI_DISABLE;
	SPI_CLR_SPSR;

	SPI_MODE_MASTER;

	SPI_MODE_STAND;
	SPI_TRANST_1BYTE;
	Spi_FreqDiv(spr);    //设置分频系数

	// SPI_INT_ENABLE;
	SPI_ENABLE;

	while(!SPI_TXEMPTY)         ; 
    while(!SPI_RXEMPTY) SPI->DATA; 

	printf("\r\n SPI->SPCR:%2x H SPI->SPER:%2x H SPI->SPSR:%2x H",SPI->SPCR,SPI->SPER,SPI->SPSR);
}

/**
 * @Description: spi 读、写 1~4字节
 * @Input: 	数据缓冲，读、写数量
 * @Output: 无
 * @return {*}
 * @param {uint8_t*} buf 数据缓冲
 * @param {int} n		读写数据字节数
 */
void Spi_Write_Read_1to4(uint8_t* buf, int n)
{
    // int i;
    // for (i=0; i<n; i++) SPI->DATA = buf[i];
    // while(!SPI_TXEMPTY) ; 
    // for (i=0; i<n-1; i++) buf[i] = SPI->DATA; 
    // while(SPI_RXEMPTY) ;
    // buf[n-1] = SPI->DATA;

	uint32 i;
    for (i=0; i<n; i++) SPI->DATA = buf[i];
    while(!SPI_TXEMPTY) ; 
    for (i=0; i<n-1; i++) buf[i] = SPI->DATA; 
    while(SPI_RXEMPTY) ;
    buf[n-1] = SPI->DATA;
}

/**
 * @Description: spi 读 写 N字节
 * @Input: 数据缓冲，读写字节数
 * @Output: 无
 * @return {*}
 * @param {uint8_t*} buf 数据缓冲
 * @param {int} n	读写字节数
 */
void Spi_Write_Read_N(uint8_t* buf, int n)
{
    // int i, j;
    // for (i=0; i<4; i++) SPI->DATA = buf[i];
    // for (j=0; i<n; i++, j++) {
    //     while(SPI_RXEMPTY) ;
    //     buf[j] =  SPI->DATA;
    //     SPI->DATA = buf[i];
    // }
    // for (; j<n; j++) {
    //     while(SPI_RXEMPTY) ;
    //     buf[j] = SPI->DATA; 
    // }

	uint32 i, j;
    for (i=0; i<4; i++) SPI->DATA = buf[i];
    for (j=0; i<n; i++, j++) 
	{
        while(SPI_RXEMPTY) ;
        buf[j] =  SPI->DATA;
        SPI->DATA = buf[i];
    }
    for (; j<n; j++) 
	{
        while(SPI_RXEMPTY) ;
        buf[j] = SPI->DATA; 
    }
}

/**
 * @Description: SPI 片选信号0 使能并拉低
 * @Input: 无
 * @Output: 无
 * @return {*}
 */
void Spi_Cs_Down(void)
{
    // SPI->SOFTCS = 0xef;

	SPI_ENABLE_CS(0); 
	SPI_LOW_CS(0); 
}
/**
 * @Description: SPI 片选信号0 使能并拉高
 * @Input: 无
 * @Output: 无
 * @return {*}
 */
void Spi_Cs_Up(void)
{
    // SPI->SOFTCS = 0xff;

	SPI_ENABLE_CS(0); 
	SPI_HIGH_CS(0);
}

/**
 * @Description: SPI 发送数据
 * @Input: 数据缓冲；数据数量
 * @Output: 无
 * @return {*}
 * @param {uint8_t*} buf 数据缓冲
 * @param {int} n		数据量
 */
void Spi_Send(uint8_t* buf, int n)
{
	Spi_Cs_Down();
    Spi_Write_Read_1to4(buf, n);
    Spi_Cs_Up();
}

/**
 * @Description: 
 * @Input: 
 * @Output: 
 * @return {*}
 */
uint8_t Spiflash_Rdsr(void)
{
    uint8_t buf[4] = {0x05};
    Spi_Cs_Down();
    Spi_Write_Read_1to4(buf, 2);
    Spi_Cs_Up();
    return buf[1];
}

/**
 * @Description: 等待置0
 * @Input: 无
 * @Output:无
 * @return {*}
 */
void Spiflash_Wait_Wip_Zero(void)
{
    while (Spiflash_Rdsr() & 0x01) {}
}

/**
 * @Description: spi flash 写
 * @Input: 
 * @Output: 
 * @return {*}
 */
void Spiflash_Wren(void)
{
    uint8_t buf[4] = {0x06};
    
	Spiflash_Wait_Wip_Zero();
    Spi_Cs_Down();
    Spi_Write_Read_1to4(buf, 1);
    Spi_Cs_Up();
}

/**
 * @Description: spi flash 写寄存器
 * @Input: 状态
 * @Output: 无
 * @return {*}
 * @param {uint8_t} st 状态
 */
void Spiflash_Wrsr(uint8_t st)
{
    uint8_t buf[4] = {0x01};
    
	Spiflash_Wren();
    buf[1] = st;
    Spi_Cs_Down();
    Spi_Write_Read_1to4(buf, 2);
    Spi_Cs_Up();
}

/**
 * @Description: spi flash 读寄存器2
 * @Input: 无
 * @Output: 返回寄存器读取数据
 * @return {*}
 */
uint8_t Spiflash_Rdsr2(void)
{
    uint8_t buf[4] = {0x35};

    Spi_Cs_Down();
    Spi_Write_Read_1to4(buf, 2);
    Spi_Cs_Up();

    return buf[1];
}

/**
 * @Description: spi flash 读寄存器3
 * @Input: 无
 * @Output: 返回读取的值
 * @return {*}
 */
uint8_t Spiflash_Rdsr3(void)
{
    uint8_t buf[4] = {0x15};

    Spi_Cs_Down();
    Spi_Write_Read_1to4(buf, 2);
    Spi_Cs_Up();

    return buf[1];
}

/**
 * @Description: SPI flash 读 ID
 * @Input: 无
 * @Output: 返回id
 * @return {*}
 */
uint16_t Spiflash_Rdid(void)
{
    uint8_t buf[4] = {0x90, 0, 0, 0};

    Spi_Cs_Down();
    Spi_Write_Read_1to4(buf, 4);
    Spi_Write_Read_1to4(buf, 2);
    Spi_Cs_Up();

    return *((uint16_t*)buf);
}

/**
 * @Description: SPI flash 扇区擦除
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint32_t} addr
 */
void Spiflash_Sector_Erase(uint32_t addr)
{
    uint8_t buf[4] = {0x20};

    buf[3] = addr & 0xff; addr >>= 8;
    buf[2] = addr & 0xff; addr >>= 8;
    buf[1] = addr & 0xff;
    
	Spiflash_Wren();

    Spi_Cs_Down();
    Spi_Write_Read_1to4(buf, 4);
    Spi_Cs_Up();
    Spiflash_Wait_Wip_Zero();
}


/**
 * @Description: SPI flash 64k 块擦除
 * @Input: 地址
 * @Output: 无
 * @return {*}
 * @param {uint32_t} addr
 */
void Spiflash_Block64k_Erase(uint32_t addr)
{
    uint8_t buf[4] = {0xd8};

    buf[3] = addr & 0xff; addr >>= 8;
    buf[2] = addr & 0xff; addr >>= 8;
    buf[1] = addr & 0xff;

	Spiflash_Wren();

    Spi_Cs_Down();
    Spi_Write_Read_1to4(buf, 4);
    Spi_Cs_Up();
    Spiflash_Wait_Wip_Zero();
}

/**
 * @Description: SPI flash 页编程
 * @Input: 页地址；数据；
 * @Output: 无
 * @return {*}
 * @param {uint32_t} addr	页地址
 * @param {uint8_t*} data_256	数据缓冲指针
 */
void Spiflash_Page_Program(uint32_t addr, uint8_t* data_256)
{
    uint8_t buf[4] = {0x02};

    buf[3] = addr & 0xff; addr >>= 8;
    buf[2] = addr & 0xff; addr >>= 8;
    buf[1] = addr & 0xff;

	Spiflash_Wren();
    
    Spi_Cs_Down();
    Spi_Write_Read_1to4(buf, 4);
    Spi_Write_Read_N(data_256, 256);
    Spi_Cs_Up();
    Spiflash_Wait_Wip_Zero();
}

/**
 * @Description: spi flash 读数据
 * @Input: 地址；数据缓冲；数据量；
 * @Output: 无
 * @return {*}
 * @param {uint32_t} addr
 * @param {uint8_t*} data
 * @param {int} n
 */
void Spiflash_Read_Bytes(uint32_t addr, uint8_t* data, int n)
{
    uint8_t buf[4] = {0x03};

    buf[3] = addr & 0xff; addr >>= 8;
    buf[2] = addr & 0xff; addr >>= 8;
    buf[1] = addr & 0xff;
    
	Spi_Cs_Down();
    Spi_Write_Read_1to4(buf, 4);
    Spi_Write_Read_N(data, n);
    Spi_Cs_Up();
}

#endif


//===========================

void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
	  uint16_t tmpreg = 0;

	  /* Check the SPI parameters */
	  assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_MemoryMode));
	  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
	  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
	  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
	  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));

	  SPIx->SPCR = 0x00;  //暂停SPI模式，清零
	  //SPI->SPCR &=~(0x40);
	  SPIx->SPSR = 0xc0;  //清中断
	  (SPI_InitStruct->SPI_Mode == SPI_Mode_Master)? (SPIx->SPCR |= 0x10) : (SPIx->SPCR &= 0xEF);//设置工作模式
	  //(SPIx->SPCR |= 0x10);
	  Spi_FreqDiv(SPI_InitStruct->SPI_BaudRatePrescaler);    //设置分频系数

	  if(SPI_InitStruct->SPI_MemoryMode == SPI_Memory_FullDuplex)
	  {
		  SPIx->PARAM |= 0x02;
		  //printf("\r\n1 SPI->PARAM:%x H \r\n",SPI->PARAM);
	  }
	  else
	  {
		  //SPIx->PARAM &= 0xFE;
		  SPIx->PARAM |= SPI_Memory_ReadOnly;
		  //printf("\r\n2 SPI->PARAM:%x H \r\n",SPI->PARAM);
	  }

	  //设置时钟极性
	  CLEAR_BIT(SPI->SPCR,0x08);
	  SPIx->SPCR |=  ((SPI_InitStruct->SPI_CPOL << 3) & 0x08);
	  /* 读采样上升沿，间隔一个SPI周期 */
	  //SPIx->TIMING |= 0x00;
	  //设置时钟相位
	  CLEAR_BIT(SPI->SPCR,0x04);
	  SPIx->SPCR |= ((SPI_InitStruct->SPI_CPHA << 2) & 0x04);
	  /*使能片选0 flash，设置片选为高电平（低电平选通）*/
	  //SPIx->SOFTCS = 0x11;
	  CLEAR_BIT(SPI->SOFTCS,0x0F);
	  SPIx->SOFTCS |= ((SPI_InitStruct->SPI_CS) & 0x0F);;
	  //采样与擦送时间错开半个周期
	  SPIx->SPER |= 0x04;
	  /*设置片选无效时间 */
	  CLEAR_BIT(SPI->TIMING,0x03);
	  SPIx->TIMING  |= (SPI_InitStruct->SPI_InvalidTime & 0x03);
	  /*设置中断传输字节数*/
	  CLEAR_BIT(SPI->SPER,0xC0);
      SPIx->SPER |= ((SPI_InitStruct->SPI_DataSizeIT & 0x03) << 6);

      //使能工作
      SPIx->SPCR |= 0x40;

      CLOCK_DelayMs(1);

//	 printf("\r\n SPI->SPCR:%x H SPI->SPER:%x H SPI->SPSR:%x H",SPI->SPCR,SPI->SPER,SPI->SPSR);
//	 printf("\r\n SPI->PARAM:%x H SPI->SOFTCS:%x H SPI->TIMING:%2x H \r\n",SPI->PARAM,SPI->SOFTCS,SPI->TIMING);

}

/******************************************************************************
 *Function Name：	 SPI_StructInit
 *Brief：init the spi structure .
 *
 *Param：
 * 		 SPI_InitStruct: a structure that defined bySPI_InitTypeDef.
 *
 *Return value：
 *       none
 *Remarks：
 *
 ******************************************************************************/
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
  /* Set the default configuration */
	SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;	//spi分频
	SPI_InitStruct->SPI_CPHA = SPI_CPHA_Same;							//启动定时器
	SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low  ;							//中断使能
	SPI_InitStruct->SPI_CS = SPI_CS_0 ;   								//周期触发
	SPI_InitStruct->SPI_DataSizeIT  =SPI_DataSizeIT_1Byte ;				//首次5秒触发
	SPI_InitStruct->SPI_InvalidTime = SPI_CsInvalidTime_2T ;			//步进值5秒触发
	SPI_InitStruct->SPI_MemoryMode = SPI_Memory_FullDuplex;				//计数器初始值设为0
	SPI_InitStruct->SPI_Mode = SPI_Mode_Master;							//主模式
}


/******************************************************************************
 *Function Name：	 SPI_GetFlagStatus
 *Brief：get spi statue according the input flag.
 *
 *Param：
 * 		 SPIx: a structure that defined SPI_TypeDef.it can be
 * 		 SPI.
 *		 SPI_FLAG : the spi flag that you can reference following:
 *     	 SPI_STATUS_FLAG_SPIF:  中断标志位
 *     	 SPI_STATUS_FLAG_WCOL:  写寄存器溢出标志位
 *     	 SPI_STATUS_FLAG_BUSY:  控制器忙标志位
 *    		 SPI_STATUS_FLAG_WFFULL: 写寄存器满标志位
 *     	 SPI_STATUS_FLAG_WFEMPTY:  写寄存器空标志位
 *     	 SPI_STATUS_FLAG_RFFULL:   读寄存器满标志
 *     	 SPI_STATUS_FLAG_RFEMPTY:  读寄存器空标志
 *Return value：
 *       none
 *Remarks：
 *
 ******************************************************************************/
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint8_t SPI_FLAG)
{
	FlagStatus bitstatus = RESET;
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_STATUS_FLAGS(SPI_FLAG));

	if(SPIx->SPSR & SPI_FLAG != (uint8_t)RESET)
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
 *Function Name：	 SPI_ITCmd
 *Brief：make the spi interrupt can been happen or not.
 *
 *Param：
 * 		 NewState: a state that defined by FunctionalState.that reference follows:
 * 		 ENABLE
 * 		 DISABLE
 *

 *Return value：
 *       none
 *Remarks：
 *
 ******************************************************************************/
void SPI_ITCmd(FunctionalState NewState)
{

	  /* Check the parameters */
	  assert_param(IS_FUNCTIONAL_STATE(NewState));
	  if (NewState != DISABLE)
	  {
	    /* Enable the Interrupt sources */
	    SET_BIT(INT->INT_EN,IRQ_SPI);
	  }
	  else
	  {
	    /* Disable the Interrupt sources */
	    CLEAR_BIT(INT->INT_EN,IRQ_SPI);
	  }
}

/******************************************************************************
 *Function Name：	 SPI_ITConfig
 *Brief：configure the spi interrupt which one to  happen or not.
 *	    SPI只有一个中断
 *Param：
 * 		 NewState: a state that defined by FunctionalState.that reference follows:
 * 		 ENABLE
 * 		 DISABLE
 *

 *Return value：
 *       none
 *Remarks：
 *
 ******************************************************************************/
void SPI_ITConfig(SPI_TypeDef* SPIx, FunctionalState NewState)
{
	  /* Check the parameters */
	  assert_param(IS_SPI_ALL_PERIPH(SPIx));
	  assert_param(IS_FUNCTIONAL_STATE(NewState));
	  if (NewState != DISABLE)
	  {
		  SPIx->SPCR |= 0x80;
	  }
	  else
	  {
		  SPIx->SPCR &= 0x7F;
	  }
}

/******************************************************************************
 *Function Name：	 SPI_GetITStatus
 *Brief：get the spi interrupt whether happen or not.
 *
 *Param：
 * 		 SPIx: a structure that defined by SPI_TypeDef.that reference follows:
 * 		 SPI
 *
 *

 *Return value：
 *       FlagStatus :
 *       SET: a interrupt happen
 *       RESET:   a interrupt not happen
 *Remarks：
 *
 ******************************************************************************/
FlagStatus SPI_GetITStatus(SPI_TypeDef* SPIx)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  if ((SPIx->SPSR & 0x80) != (uint32_t)RESET)
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
 *Function Name：	 SPI_ClearIT
 *Brief：clear the spi interrupt flag.
 *
 *Param：
 * 		 SPIx: a structure that defined by SPI_TypeDef.that reference follows:
 * 		 SPI
 *

 *Return value：
 *       FlagStatus :
 *       SET: a interrupt happen
 *       RESET:   a interrupt not happen
 *Remarks：
 *
 ******************************************************************************/
void SPI_ClearIT(SPI_TypeDef* SPIx)
{
	  /* Check the parameters */
	  assert_param(IS_SPI_ALL_PERIPH(SPIx));

	  /* Clear the flags */
	  SPIx->SPSR |= 0x80;
	  INT->INT_CLR |= IRQ_SPI;
}



#if 0

/******************************************************************************
 * 函数名： SpiInit
 * 功能： spi初始化模式
 * 输入参数：
 * 		  byte：写入字节
 * 返回值：
 *      none
 * 备注：无
 ******************************************************************************/
SpiInit(void)
{
//	SpiGpioInit();

	SPI->SPCR = 0x00;  //暂停SPI模式，清零
	SPI->SPSR = 0xc0;  //清中断

	/*master模式，设置分频 = 2 分频,flash 编程模式*/
	SPI->SPCR = 0x10;
	SPI->SPER = 0x00;
	SPI->PARAM = 0x02;

	//4分频
//	SPI_SPCR = 0x01;
//	SPI_SPER = 0x00;
//	SPI_SFC_PARAM = 0x11;
	//16分频
//	SPI_SPCR = 0x02;
//	SPI_SPER = 0x00;
//	SPI_SFC_PARAM = 0x21;

	/*使能片选0 flash，设置片选为高电平（低电平选通）*/
	SPI->SOFTCS = 0x11;
	//SPI_SFC_SOFTCS = 0xF1;
	/*片选无效时间2T，读采样上升沿，间隔一个SPI周期*/
	SPI->TIMING = 0x05;
	//工作使能
	SPI->SPCR  |= 0x50; //设置为master 并启动spi工作

	CLOCK_DelayMs(1);
}


#endif


/******************************************************************************
 * 函数名： SpiTransByte
 * 功能： 通过SPI接口传输一个字节
 * 输入参数：
 * 		  byte：写入字节
 * 返回值：
 *      none
 * 备注：无
 ******************************************************************************/
uint8_t SPI_TransByte(uint8_t byte)
{
	uint8_t ucResult=0;
	uint8_t retry=0;
	/*清除中断和溢出标志位*/
	SPI->SPSR = 0xc0;

	//判断写寄存器是否为空
	while(!(SPI->SPSR & 0x04))
	{
		retry++;
		if(retry > 200){
			printf("spi no data send\r\n");
			return 0;
		}
	}
	retry = 0;
	SPI->DATA = byte;
	while(SPI->SPSR & 0x01)
	{
		retry++;
		if(retry > 200){
			printf("spi no data receive\r\n");
			return 0;
		}
	}
	ucResult = SPI->DATA;


	return ucResult;
}

/******************************************************************************
 * 函数名： SpiFlashCsn0Enable
 * 功能： spi flash csn0 使能
 * 输入参数：
 * 		none
 * 返回值：
 *      none
 * 备注：无
 ******************************************************************************/
void SpiFlashCsn0Enable()
{
	/*使能片选信号CSN0*/
	SPI->SOFTCS = 0xE1;//E1
}

/******************************************************************************
 * 函数名： SpiFlashCsn0Disable
 * 功能： spi flash csn0 不使能
 * 输入参数：
 * 		 none
 * 返回值：
 *      none
 * 备注：无
 ******************************************************************************/
void SpiFlashCsn0Disable()
{
	/*使能片选信号CSN0*/
	SPI->SOFTCS = 0xF1;
}




#endif


