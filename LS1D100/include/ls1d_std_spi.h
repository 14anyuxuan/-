
/********************************************************************
* 文件名:   ls1d6_std_spi.h
* 版本：	  V1.0
* 作者:   白一方
* 日期:    2021.09.30
* 说明:    本文件包含spi接口函数、变量声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef     __SPI__H
#define     __SPI__H

#include "ls1d.h"

#define  UserSPI
#ifdef UserSPI

#if 0

// #define SPI_TRANST_1BYTE 0<<6
// #define SPI_TRANST_2BYTE 1<<6
// #define SPI_TRANST_3BYTE 2<<6
// #define SPI_TRANST_4BYTE 3<<6

#define SPI_TXEMPTY (SPI->SPSR & 0x04)
#define SPI_RXEMPTY (SPI->SPSR & 0x01)
#define SPI_TXFULL  (SPI->SPSR & 0x08)
#define SPI_RXFULL  (SPI->SPSR & 0x02)

#define SPI_CHIP_ENABLE (CHIPCTRL &= ~(1<<9))       //SPI 芯片使能

#define SPI_INT_ENABLE      (SPI->SPCR |=0x80)          //SPI 控制器使能
#define SPI_INT_DISABLE     (SPI->SPCR &=~(0x80))       //SPI 控制器停止



#define SPI_ENABLE      (SPI->SPCR |=0x40)          //SPI 控制器使能
#define SPI_DISABLE     (SPI->SPCR &=~(0x40))       //SPI 控制器停止

#define SPI_MODE_MASTER     (SPI->SPCR |=0x10)
#define SPI_MODE_SLAVE      (SPI->SPCR &=~(0x10))

#define SPI_CPOL_HIGH     (SPI->SPCR |=0x08)
#define SPI_CPOL_LOW      (SPI->SPCR &=~(0x08))

#define SPI_CPHA_SAME     (SPI->SPCR |=0x04)
#define SPI_CPHA_REV      (SPI->SPCR &=~(0x04))

#define SPI_CLR_SPSR    (SPI->SPSR = 0xC0)          //SPI 重置SPI状态寄存器


#define SPI_MODE_COMPATIBILIY     	(SPI->SPER |=0x04)
#define SPI_MODE_STAND      		(SPI->SPER &=~(0x04))

#define SPI_TRANST_1BYTE 			(SPI->SPER &=0x3F)
#define SPI_TRANST_2BYTE 			(SPI->SPER |=(1<<6))
#define SPI_TRANST_3BYTE 			(SPI->SPER |=(2<<6))
#define SPI_TRANST_4BYTE			(SPI->SPER |=(3<<6))

// #define SPI_ENABLE_CS(n)     {SPI->SOFTCS |=(1<<n); SPI->SOFTCS &=~(1<<(n+4)); }
// #define SPI_DISABLE_CS(n)    {SPI->SOFTCS &=~(1<<n); SPI->SOFTCS |=(1<<(n+4)) }
#define SPI_ENABLE_CS(n)     	( SPI->SOFTCS |=(1<<n) )
#define SPI_DISABLE_CS(n)    	( SPI->SOFTCS &=~(1<<n) )
#define SPI_LOW_CS(n)     		(SPI->SOFTCS &=~(1<<(n+4)))
#define SPI_HIGH_CS(n)    		(SPI->SOFTCS |=(1<<(n+4)) )



void Spi_Init(uint8 spr);

void Spi_Write_Read_1to4(uint8_t* buf, int n);

void Spi_Write_Read_N(uint8_t* buf, int n);

void Spi_Cs_Down(void);

void Spi_Cs_Up(void);

void Spi_Send(uint8_t* buf, int n);



/************SPI FLASH*********************/
void Spiflash_Wait_Wip_Zero(void);

void Spiflash_Wait_Wip_Zero(void);

void Spiflash_Wren(void);

void Spiflash_Wrsr(uint8_t st);

uint8_t Spiflash_Rdsr2(void);

uint8_t Spiflash_Rdsr3(void);

uint16_t Spiflash_Rdid(void);

void Spiflash_Sector_Erase(uint32_t addr);

void Spiflash_Block64k_Erase(uint32_t addr);

void Spiflash_Page_Program(uint32_t addr, uint8_t* data_256);

void Spiflash_Read_Bytes(uint32_t addr, uint8_t* data, int n);


#endif




/**
  * @brief  SPI Init structure definition
  */

typedef struct
{
  uint8_t SPI_MemoryMode;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_data_direction */

  uint8_t SPI_Mode;                /*!< Specifies the SPI operating mode.
                                         This parameter can be a value of @ref SPI_mode */

  uint8_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

  uint8_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

  uint8_t SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler.
                                         @note The communication clock is derived from the master
                                         clock. The slave clock does not need to be set. */
  uint8_t SPI_DataSizeIT;            /*!< Specifies the SPI IT after data size .
                                           This parameter can be a value of @ref SPI_data_sizeIT */
  uint8_t SPI_CS;                 /*!< Specifies which cs been selected  to use. only 0 ,1 can been use for 1d6   */

  uint8_t SPI_InvalidTime;                 /*!< Specifies the  Invalid Time for spi flash'cs  */
}SPI_InitTypeDef;


#define SPI_BaudRatePrescaler_2       	((uint8_t)0)
#define SPI_BaudRatePrescaler_4       	((uint8_t)1)
#define SPI_BaudRatePrescaler_8       	((uint8_t)4)
#define SPI_BaudRatePrescaler_16      	((uint8_t)2)
#define SPI_BaudRatePrescaler_32      	((uint8_t)3)
#define SPI_BaudRatePrescaler_64      	((uint8_t)5)
#define SPI_BaudRatePrescaler_128     	((uint8_t)6)
#define SPI_BaudRatePrescaler_256     	((uint8_t)7)
#define SPI_BaudRatePrescaler_512    	((uint8_t)8)
#define SPI_BaudRatePrescaler_1024   	((uint8_t)9)
#define SPI_BaudRatePrescaler_2048    	((uint8_t)10)
#define SPI_BaudRatePrescaler_4096    	((uint8_t)11)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_256)||\
											  ((PRESCALER) == SPI_BaudRatePrescaler_512) || \
											  ((PRESCALER) == SPI_BaudRatePrescaler_1024) || \
											  ((PRESCALER) == SPI_BaudRatePrescaler_2048) || \
											  ((PRESCALER) == SPI_BaudRatePrescaler_4096))


/** @defgroup SPI_mode
  * @{
  */

#define SPI_Mode_Master                 ((uint8_t)0x01)
#define SPI_Mode_Slave                  ((uint8_t)0x00)
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))

/** @defgroup SPI_Clock_Polarity
  * @{
  */

#define SPI_CPOL_Low                    ((uint8_t)0x00)
#define SPI_CPOL_High                   ((uint8_t)0x01)
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))


/** @defgroup SPI_Clock_Phase
  * @{
  */

#define SPI_CPHA_Same              ((uint8_t)0x00)
#define SPI_CPHA_Opposite          ((uint8_t)0x01)
#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_Same) || \
                           ((CPHA) == SPI_CPHA_Opposite))



/** @defgroup SPI_data_direction
  * @{
  */

#define SPI_Memory_FullDuplex   ((uint8_t)0x00)
#define SPI_Memory_ReadOnly     ((uint8_t)0x01)
#define IS_SPI_MEMORY_MODE(MODE) (((MODE) == SPI_Memory_FullDuplex) || \
                                     ((MODE) == SPI_Memory_ReadOnly))

/** @defgroup SPI_data_sizeIT
  * @{
  */

#define SPI_CsInvalidTime_8T                ((uint8_t)0x03)
#define SPI_CsInvalidTime_4T                ((uint8_t)0x02)
#define SPI_CsInvalidTime_2T                ((uint8_t)0x01)
#define SPI_CsInvalidTime_1T                ((uint8_t)0x00)
#define IS_SPI_CS_INVALIDTIME(TIME) (((TIME) == SPI_CsInvalidTime_8T) || \
									((TIME) == SPI_CsInvalidTime_4T) || \
									((TIME) == SPI_CsInvalidTime_1T) || \
                                    ((TIME) == SPI_CsInvalidTime_1T))


/** @defgroup SPI_data_sizeIT
  * @{
  */

#define SPI_DataSizeIT_4Byte                ((uint16_t)0x0003)
#define SPI_DataSizeIT_3Byte                ((uint16_t)0x0002)
#define SPI_DataSizeIT_2Byte                ((uint16_t)0x0001)
#define SPI_DataSizeIT_1Byte                ((uint16_t)0x0000)
#define IS_SPI_IT_DATASIZE(DATASIZE) (((DATASIZE) == SPI_DataSizeIT_1Byte) || \
									((DATASIZE) == SPI_DataSizeIT_2Byte) || \
									((DATASIZE) == SPI_DataSizeIT_3Byte) || \
                                    ((DATASIZE) == SPI_DataSizeIT_4Byte))


/** @defgroup SPI_data_sizeIT
  * @{
  */

#define SPI_CS_1                ((uint16_t)0x0002)
#define SPI_CS_0                ((uint16_t)0x0001)
#define IS_SPI_CS(CS) (((CS) == SPI_CS_0) ||((CS) == SPI_DataSizeIT_4Byte))


#define IRQ_SPI       			((uint8_t)32)
#define IS_SPI_ALL_PERIPH(PERIPH) ((PERIPH) == SPI)

#define  SPI_STATUS_FLAG_SPIF 			((uint8_t)0x80)	// 中断标志位
#define  SPI_STATUS_FLAG_WCOL			((uint8_t)0x40) // 写寄存器溢出标志位
#define  SPI_STATUS_FLAG_BUSY			((uint8_t)0x10) // 控制器忙标志位
#define  SPI_STATUS_FLAG_WFFULL			((uint8_t)0x08)	// 写寄存器满标志位
#define  SPI_STATUS_FLAG_WFEMPTY		((uint8_t)0x04) // 写寄存器空标志位
#define  SPI_STATUS_FLAG_RFFULL			((uint8_t)0x02) // 读寄存器满标志
#define  SPI_STATUS_FLAG_RFEMPTY		((uint8_t)0x01) // 读寄存器空标志


#define IS_SPI_STATUS_FLAGS(FLAGS)  (((FLAGS) == SPI_STATUS_FLAG_SPIF) || \
        							((FLAGS) == SPI_STATUS_FLAG_WCOL) || \
									((FLAGS) == SPI_STATUS_FLAG_BUSY) || \
									((FLAGS) == SPI_STATUS_FLAG_WFFULL) || \
									((FLAGS) == SPI_STATUS_FLAG_WFEMPTY) || \
									((FLAGS) == SPI_STATUS_FLAG_RFFULL) || \
									((FLAGS) == SPI_STATUS_FLAG_RFEMPTY))







void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint8_t SPI_FLAG);
void SPI_ITCmd(FunctionalState NewState);
void SPI_ITConfig(SPI_TypeDef* SPIx, FunctionalState NewState);
FlagStatus SPI_GetITStatus(SPI_TypeDef* SPIx);
void SPI_ClearIT(SPI_TypeDef* SPIx);
uint8_t SPI_TransByte(uint8_t byte);




#endif

#endif
