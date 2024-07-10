/********************************************************************
* 文件名:   ls1d6.h
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.08.31
* 说明:    1D6芯片寄存器全局定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef _LS1D6_H_
#define _LS1D6_H_

#include "ls1d_std_cslreg.h"

#ifdef __cplusplus
 extern "C" {
#endif

//#define USE_FULL_ASSERT

#ifdef __cplusplus
  #define     __I     volatile                /*!< defines 'read only' permissions      */
#else
  #define     __I     volatile const          /*!< defines 'read only' permissions      */
#endif
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */


 /* Exported macro ------------------------------------------------------------*/
 #ifdef  USE_FULL_ASSERT
 /**
   * @brief  The assert_param macro is used for function's parameters check.
   * @param  expr: If expr is false, it calls assert_failed function which reports
   *         the name of the source file and the source line number of the call
   *         that failed. If expr is true, it returns no value.
   * @retval None
   */
   #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
 /* Exported functions ------------------------------------------------------- */
   void assert_failed(uint8_t* file, uint32_t line);
 #else
   #define assert_param(expr) ((void)0)
 #endif /* USE_FULL_ASSERT */

 /**
  * @brief In the following line adjust the External High Speed oscillator (HSE) Startup
  * Timeout value
  */
#define HSE_STARTUP_TIMEOUT   ((uint32_t)0x40000) /*!< Time out for HSE start up */
#define HSI_VALUE    ((uint32_t)8000000) /*!< Value of the Internal oscillator in Hz*/

 /**
  * @说明：自定义的常用数据宏定义
  *
  */
typedef unsigned char       	uint8;
typedef signed char				int8;
typedef unsigned short      	uint16;
typedef signed short        	int16;
typedef unsigned int         	uint32;
typedef signed int           	int32;
typedef unsigned long       	uint64;
typedef signed long         	int64;
typedef unsigned char 		    BOOL;

typedef unsigned long         	uint64_t;
typedef unsigned int            uint32_t;
typedef unsigned char           uint8_t;
typedef unsigned short   		uint16_t;
typedef signed long         	int64_t;
typedef int 					int32_t;
typedef short   				int16_t;
typedef char   					int8_t;


/**
 * IO definitions
 *
 * define access restrictions to peripheral registers
 */

#define false      1
#define true       0
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))



/**
 * @说明：串口外设接口宏定义
 *
 */
typedef struct
{
  volatile uint8_t DAT_DL_L ;			/* 发送数据寄存器 或 分频值低字节寄存器 */
  volatile uint8_t IER_DL_H;			/* 中断使能寄存器 或 分频值高字节寄存器 */
  volatile uint8_t IIR_FCR_DL_D;		/* 中断状态寄存（只读） FIFO控制寄存器 （只写）  或   分频值小数寄存器  */
  volatile uint8_t LCR;					/* 线路控制寄存器  */
  volatile uint8_t MCR_SCR;				/* MODEM控制寄存器  */
  volatile uint8_t LSR;					/* 线路状态寄存器  */
  volatile uint8_t MSR;					/* 线路状态寄存器  */
} UART_TypeDef;

/**
 * @说明：定时器接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t CFG ;			/* 配置寄存器 */
  volatile uint32_t CNT;			/* 计数值寄存器 */
  volatile uint32_t CMP;		    /* 比较值寄存器  */
  volatile uint32_t STP;			/* 步进值寄存器  */

} TIM_TypeDef;

/**
 * @说明：实时时钟接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t FREQ ;			/*  分频值寄存器[27:6] */
  volatile uint32_t CFG;			/* 配置寄存器 */
  volatile uint32_t RTC0;			/* 时间值寄存器0  */
  volatile uint32_t RTC1;			/* 时间值寄存器0  */

} RTC_TypeDef;


/**
 * @说明：看门狗接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t WDT_CFG;		/* 配置寄存器 */
  volatile uint32_t WDT_FEED;		/* 重置寄存器  */
} WWDG_TypeDef;


/**
 * @说明：SPI接口宏定义
 *
 */
typedef struct
{
  volatile uint8_t SPCR;			/* 控制寄存器 */
  volatile uint8_t SPSR;			/* 状态寄存器 */
  volatile uint8_t DATA;			/* 数据寄存器 */
  volatile uint8_t SPER;			/* 外部寄存器 */
  volatile uint8_t PARAM;			/* 参数控制寄存器 */
  volatile uint8_t SOFTCS;			/* 片选控制寄存器 */
  volatile uint8_t TIMING;			/* 时序控制寄存器 */
} SPI_TypeDef;

/**
 * @说明：I2C接口宏定义
 *
 */
typedef struct
{
  volatile uint8_t PRERL;			/* 分频值低字节寄存器 */
  volatile uint8_t PRERH;			/* 分频值高字节寄存器 */
  volatile uint8_t CTR;				/* 控制寄存器 */
  volatile uint8_t DR;				/* 数据寄存器 */
  volatile uint8_t CR_SR;			/* 命令寄存器 兼 状态寄存器 */
  volatile uint8_t BLTOP;			/* 总线死锁时间寄存器 */
  volatile uint8_t RESERVED0;		/* 保留字节  */
  volatile uint8_t SADDR;			/* 从模式地址寄存器 */
} I2C_TypeDef;

/**
 * @说明：MBUS接口宏定义
 *
 */
typedef struct
{
  volatile uint8_t DAT_DL_L ;			/* 发送数据寄存器 或 分频值低字节寄存器 */
  volatile uint8_t IER_DL_H;			/* 中断使能寄存器 或 分频值高字节寄存器 */
  volatile uint8_t IIR_FCR_DL_D;		/* 中断状态寄存（只读） FIFO控制寄存器 （只写）  或   分频值小数寄存器  */
  volatile uint8_t LCR;					/* 线路控制寄存器  */

  volatile uint8_t SAMPLE_CTRL;			/* bit窗口划分和采用控制寄存器  */
  volatile uint8_t LSR;					/* 线路状态寄存器  */
  volatile uint8_t TFCNT;				/* 发送队列数据存量寄存器  */
  volatile uint8_t STATUS;				/* 状态寄存器  */

  volatile uint8_t FSM_CTRL0;			/* 帧过滤控制寄寄存器0寄存器  */
  volatile uint8_t FSM_CHAR;			/* 帧过滤前导字符值寄存器  */
  volatile uint8_t FSM_CTRL1;			/* 帧过滤控制寄寄存器1  */
  volatile uint8_t BR_MASK;				/* 帧过滤广播地址掩码寄存器  */

  volatile uint8_t FSM_MASKL;			/* 帧过滤掩码低8位寄存器  */
  volatile uint8_t FSM_MASKH;			/* 帧过滤掩码高8位寄存器  */
  volatile uint8_t BR_CTRL;				/* 帧过滤广播地址参数寄存器  */
  volatile uint8_t BUF_CNT;				/* 帧过滤环形缓冲区数据量寄存器  */

  volatile uint32_t FSM_Table0;			/* 帧过滤比较字节表寄存器  */
  volatile uint32_t FSM_Table1;			/* 帧过滤比较字节表寄存器  */
  volatile uint32_t FSM_Table2;			/* 帧过滤比较字节表寄存器  */
  volatile uint32_t FSM_Table3;			/* 帧过滤比较字节表寄存器  */

  volatile uint32_t BR_Table0;			/* 帧过滤广播地址表寄存器  */
  volatile uint32_t BR_Table1;			/* 帧过滤广播地址表寄存器  */

  volatile uint8_t FTIMEOUTL;			/* 帧超时技术比较的低32位值寄存器  */
  volatile uint8_t FTIMEOUTH;			/* 帧超时技术比较的高32位值寄存器  */
  volatile uint8_t BUF_RPTR;			/* 帧过滤环形缓冲区的读指针寄存器  */
  uint8_t RESERVED0;					/* 保留  */
  uint32_t RESERVED1;					/* 保留  */
  volatile uint32_t FSM_BUF0;			/* 帧过滤环形缓冲区数据直接读取空间寄存器  */
  volatile uint32_t FSM_BUF1;			/* 帧过滤环形缓冲区数据直接读取空间寄存器  */
  volatile uint32_t FSM_BUF2;			/* 帧过滤环形缓冲区数据直接读取空间寄存器  */
  volatile uint32_t FSM_BUF3;			/* 帧过滤环形缓冲区数据直接读取空间寄存器  */
} MBUS_TypeDef;


/**
 * @说明：ADC接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t ADC_CTRL;				/* ADC配置寄存器 */
  volatile uint32_t ADC_DATA;				/* ADC数据寄存器 */
} ADC_TypeDef;

/**
 * @说明：FLASH接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t CMD;				/* 命令寄存器 */
  volatile uint32_t CAH;				/* 加密地址上界寄存器 */
  volatile uint32_t CAL;				/* 加密地址下界寄存器 */
  volatile uint32_t RESERVED0;			/* 保留字节  */
  volatile uint32_t VRF;				/* 数据校验寄存器 */
  volatile uint32_t STS;				/* 状态寄存器 */
  volatile uint32_t PET;				/* 擦写时间寄存器 */
} FLASH_TypeDef;


/**
 * @说明：LCD接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t FB0;				/* 帧缓冲0寄存器 */
  volatile uint32_t FB1;				/* 帧缓冲1寄存器寄存器 */
  volatile uint32_t FB2;				/* 帧缓冲2寄存器寄存器 */
  volatile uint32_t RFR;				/* 刷新率寄存器 */

} LCD_TypeDef;

/**
 * @说明：THSENS接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t THSENS_CTRL;				/* 温度控制寄存器 */

} THSENS_TypeDef;

/**
 * @说明：SONAR接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t PULSE_DEF;				/* 脉冲定义 */
  volatile uint32_t SONAR_CTRL;				/* 时差测量控制寄存器 */
  volatile uint32_t TDC_CTRL1;				/* TDC控制1寄存器 */
  volatile uint32_t TDC_CTRL2;				/* TDC控制2寄存器 */
  volatile uint32_t CALIB_CTRL;				/* 校准控制寄存器 */
  volatile uint32_t FWAVE_CTRL;				/* 首波控制寄存器 */
  volatile uint32_t AFE_CTRL;				/* 模拟前端控制寄存器 */
  volatile uint32_t DLINE_CTRL;				/* 擦窗口延迟链配置寄存器 */
  volatile uint32_t GATE_DEF1;				/* 窗口配置1寄存器 */
  volatile uint32_t GATE_DEF2;				/* 窗口配置2寄存器 */
  volatile uint32_t GATE_DEF3;				/* 窗口配置3寄存器 */
  volatile uint32_t RES_PTR;				/* 结构指针寄存器 */
} SONAR_TypeDef;

/**
 * @说明：GPIO_TypeDef接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t GPIO_OE;			/* GPIO输出使能寄存器 */
  volatile uint32_t GPIO_O;				/* GPIO输出电平寄存器 */
  volatile uint32_t GPIO_I;				/* GPIO输入电平寄存器 */
} GPIO_TypeDef;

/**
 * @说明：BITIO_TypeDef接口宏定义
 *
 */

typedef union
{
  volatile uint8_t data;
  struct
  {
	  volatile uint8_t GPIO_IO	:1;				/* GPIO输入输出电平寄存器 */
	  volatile uint8_t GPIO_OE	:1;				/* GPIO输出使能寄存器 */
  };
}BITIO_TypeDef;

/**
 * @说明：PMU_TypeDef接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t TIMING;					/* 测量时序控制 */
  volatile uint32_t COMMAND;				/*测量命令、配置寄存器 */

  volatile uint32_t COUNT;					/* 时间计数器寄存器 */
  volatile uint32_t COMPARE;				/* 唤醒时间配置寄存器 */

  volatile uint32_t CHIP_CTRL;				/* 芯片全局控制寄存器 */

  volatile uint32_t AUTO_CALC;				/* 自动计算寄存器 */

  volatile uint32_t ADC_CTRL;				/* ADC配置寄存器 */
  volatile uint32_t ADC_DATA;				/* ADC数据寄存器 */

  volatile uint32_t EXINT_EN;				/* 外部中断使能寄存器 */
  volatile uint32_t EXINT_POL;				/* 外部中断极性寄存器 */
  volatile uint32_t EXINT_EDGE;				/* 外部中断边沿寄存器 */
  volatile uint32_t EXINT_SRC;				/* 外部中断状态寄存器 */

  volatile uint32_t WDT_CFG;				/* 看门狗配置寄存器 */
  volatile uint32_t WDT_FEED;				/* 看门狗重置寄存器 */

  volatile uint32_t POWER_CFG;				/* 电源配置寄存器 */
  volatile uint32_t COMMAND_W;				/* 命令写寄存器 */

  volatile uint32_t GPIOA_OE;				/* GPIOA输出使能寄存器 */
  volatile uint32_t GPIOA_O;				/* GPIOA输出电平寄存器 */
  volatile uint32_t GPIOA_I;				/* GPIOA输入电平寄存器 */
  volatile uint32_t reserved0;				/* 备用0 */
  volatile uint32_t GPIOB_OE;				/* GPIOB输出使能寄存器*/
  volatile uint32_t GPIOB_O;				/* GPIOB输出电平寄存器 */
  volatile uint32_t GPIOB_I;				/* GPIOB输入电平寄存器 */
  volatile uint32_t reserved1;				/* 备用1 */

  volatile uint32_t PULSE0;					/* 脉冲输出配置寄存器0 */
  volatile uint32_t PULSE1;					/* 脉冲输出配置寄存器1 */

  volatile uint32_t USER_DAT;				/* 用户数据寄存器 */

  volatile uint32_t GPIOBIT;				/* GPIO位访问寄存器 */

} PMU_TypeDef;


/**
 * @说明：外部中断接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t EXINT_EN;				/* 外部中断使能寄存器 */
  volatile uint32_t EXINT_POL;				/* 外部中断极性寄存器 */
  volatile uint32_t EXINT_EDGE;				/* 外部中断边沿寄存器 */
  volatile uint32_t EXINT_SRC;				/* 外部中断状态寄存器 */
} EXTI_TypeDef;

/**
 * @说明：接口中断接口宏定义
 *
 */
typedef struct
{
  volatile uint8_t INT_EN;					/* 中断使能寄存器 */
  volatile uint8_t INT_EDGE;				/* 中断边沿寄存器 */
  volatile uint8_t INT_POL;					/* 中断极性寄存器 */
  volatile uint8_t INT_CLR;					/* 中断清除寄存器 */
  volatile uint8_t INT_SET;					/* 中断置位寄存器 */
  volatile uint8_t INT_OUT;					/* 中断输出寄存器 */
  volatile uint8_t SRPRPT;					/* 运行状态及保护寄存器 */
} INT_TypeDef;



/**
 * @说明：脉冲接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t PULSE0;					/* 脉冲输出配置寄存器 */
  volatile uint32_t PULSE1;					/* 脉冲输出配置寄存器 */
} PULSE_TypeDef;

/**
 * @说明：测量接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t TIMING;					/* 测量时序控制 */
  volatile uint32_t COMMAND;				/*测量命令、配置寄存器 */
  volatile uint32_t RESERVED;
  volatile uint32_t RESERVED1;
  volatile uint32_t RESERVED2;
  volatile uint32_t AUTOCALC;				/* 自动计算  */
} MEASURE_TypeDef;


#if 1
/**
 * @说明：RCC接口宏定义
 *
 */
typedef struct
{
  volatile uint32_t COUNT;					/* 时间计数器寄存器 */
  volatile uint32_t COMPARE;				/* 唤醒时间配置寄存器 */
}RCC_TypeDef;

#endif
//=========================================================================================

#define BIG_MEM
#ifdef BIG_MEM

#define UNCACHED_MEMORY_ADDR 	0x00000000
#define UNCACHED_TO_PHYS(x)     ((x) & 0x1fffffff)
#define PHYS_TO_UNCACHED(x)     ((x) | UNCACHED_MEMORY_ADDR)
#define SPI_FLASH_BASE		PHYS_TO_UNCACHED(0x1e000000)            //spi-flash
#define FLASH_BASE			PHYS_TO_UNCACHED(0x1f000000)            //on-chip flash
#define FLASH_REG_BASE		PHYS_TO_UNCACHED(0x1fe60000)            //flash regs
#define SPI_REG_BASE		PHYS_TO_UNCACHED(0x1fe70000)            //spi regs
#define UART0_BASE  		PHYS_TO_UNCACHED(0x1fe80000)            //uart0
#define UART1_BASE			PHYS_TO_UNCACHED(0x1fe88000)            //uart1
#define MBUS_BASE    		PHYS_TO_UNCACHED(0x1fe88000)            //mbus
#define I2C_BASE			PHYS_TO_UNCACHED(0x1fe90000)            //i2c
#define INT_BASE			PHYS_TO_UNCACHED(0x1fea0000)            //Interrupt_Regs_Baseadd
#define PMU_BASE			PHYS_TO_UNCACHED(0x1feb0000)            //PMU
#define SONAR_BASE			PHYS_TO_UNCACHED(0x1feb4000)            //SONAR
#define THSENS_BASE			PHYS_TO_UNCACHED(0x1feb4080)            //THSENS
#define RTC_BASE			PHYS_TO_UNCACHED(0x1feb8000)            //rtc
#define LCD_BASE            PHYS_TO_UNCACHED(0x1febc000)
#define HPET_BASE		    PHYS_TO_UNCACHED(0x1fed0000)            //timer
#define RESULT_BASE     	PHYS_TO_UNCACHED(0x1feb4040)
#define RAM_BASE            0x10000000
#define RAM0_BASE           0x10000000
#define RAM1_BASE           0x10001000
#define MEASURE_BASE    	(PMU_BASE + 0x00)
#define RCC_BASE			(PMU_BASE + 0x08)
#define ADC_BASE    		(PMU_BASE + 0x18)
#define EXTI_BASE    		(PMU_BASE + 0x20)
#define WWDG_BASE    		(PMU_BASE + 0x30)
#define GPIOA_BASE   		(PMU_BASE + 0x40)
#define GPIOB_BASE   		(PMU_BASE + 0x50)
#define PULSE_BASE 			(PMU_BASE + 0x60)


#define GPIOA_BIT_BASE   		(PMU_BASE + 0x80)
#define GPIOB_BIT_BASE   		(PMU_BASE + 0x80 + 0x20)

#else
#define MEM_BASEADDR		0x00000000
#define IRAM_BASE    		(MEM_BASEADDR + 0x0000)
#define DRAM_BASE    		(MEM_BASEADDR + 0x1000)
#define SPI_FLASH_BASE  	0xbe000000
#define FLASH_BASE   		0xbf000000
#define BOOT_BASE     		0xbfc00000
#define FLASH_REG_BASE   	(MEM_BASEADDR + 0x3000)
#define SPI_REG_BASE  		(MEM_BASEADDR + 0x3800)
#define UART0_BASE  		(MEM_BASEADDR + 0x4000)
#define UART1_BASE   		(MEM_BASEADDR + 0x4400)
#define MBUS_BASE    		(MEM_BASEADDR + 0x4400)
#define I2C_BASE     		(MEM_BASEADDR + 0x4800)
#define INT_BASE     		(MEM_BASEADDR + 0x5000)
#define PMU_BASE     		(MEM_BASEADDR + 0x5800)
#define SONAR_BASE   		(MEM_BASEADDR + 0x5a00)
#define THSENS_BASE  		(MEM_BASEADDR + 0x5a80)
#define RTC_BASE    	 	(MEM_BASEADDR + 0x5c00)
#define LCD_BASE    		(MEM_BASEADDR + 0x5e00)
#define HPET_BASE    		(MEM_BASEADDR + 0x6800)

#define MEASURE_BASE    	(PMU_BASE + 0x00)
#define RCC_BASE			(PMU_BASE + 0x08)
#define ADC_BASE    		(PMU_BASE + 0x18)
#define EXTI_BASE    		(PMU_BASE + 0x20)
#define WWDG_BASE    		(PMU_BASE + 0x30)
#define GPIOA_BASE   		(PMU_BASE + 0x40)    //GPIOA
#define GPIOB_BASE   		(PMU_BASE + 0x50)    //命令写端口
#define PULSE_BASE 			(PMU_BASE + 0x60)

#define GPIOA_BIT_BASE   		(PMU_BASE + 0x80)    //GPIO 位访问端口
#define GPIOB_BIT_BASE   		(PMU_BASE + 0x80 + 0x20)    //GPIO 位访问端口
#endif

/********************************PERIPH********************************/

#define UART0              ((UART_TypeDef *) UART0_BASE)
#define UART1              ((UART_TypeDef *) UART1_BASE)
#define TIMER               ((TIM_TypeDef *) HPET_BASE)
#define RTC                 ((RTC_TypeDef *) RTC_BASE)
#define WWDG                ((WWDG_TypeDef *) WWDG_BASE)
#define SPI                 ((SPI_TypeDef *) SPI_REG_BASE)
#define I2C                 ((I2C_TypeDef *) I2C_BASE)
#define MBUS                ((MBUS_TypeDef *) MBUS_BASE)
#define ADC              	((ADC_TypeDef *) ADC_BASE)
#define FLASH               ((FLASH_TypeDef *) FLASH_REG_BASE)
#define LCD                 ((LCD_TypeDef *) LCD_BASE)

#define THSENS              ((THSENS_TypeDef *) THSENS_BASE)

#define SONAR               ((SONAR_TypeDef *) SONAR_BASE)


#define PMU                 ((PMU_TypeDef *) PMU_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define INT					((INT_TypeDef *) INT_BASE)
#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)
#define PULSE               ((PULSE_TypeDef *) PULSE_BASE)
#define MEASURE      		((MEASURE_TypeDef *) MEASURE_BASE)
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define GPIOA_BIT        	((BITIO_TypeDef *) GPIOA_BIT_BASE)
#define GPIOB_BIT        	((BITIO_TypeDef *) GPIOB_BIT_BASE)

#define PMU_CMDSTS			*(volatile uint32_t *)(PMU_BASE + 0x04)
#define PMU_COUNT			*(volatile uint32_t *)(PMU_BASE + 0x08)
#define PMU_COMPARE        	*(volatile uint32_t *)(PMU_BASE + 0x0c)
#define CHIPCTRL  	       	*(volatile uint32_t *)(PMU_BASE + 0x10)     	//芯片全局配置
#define AUTOCALC  	       	*(volatile uint32_t *)(PMU_BASE  +0x14)     	//自动计算配置
#define POWERCfg   			*(volatile uint32_t *)(PMU_BASE + 0x38)   		//电源配置
#define COMMANDW   			*(volatile uint32_t *)(PMU_BASE + 0x3C)   		//命令写端口
#define USERDAT   			*(volatile uint32_t *)(PMU_BASE + 0x68)    		//用户数据配置
#define GPIOBit(i) 	       	*(volatile uint32_t *)(PMU_BASE + 0x80 + i)   	//GPIO位访问

//#define CEC                 ((CEC_TypeDef *) CEC_BASE)
//#define CRC                 ((CRC_TypeDef *) CRC_BASE)
//#define DBGMCU              ((DBGMCU_TypeDef *) DBGMCU_BASE)
//


/*****************************RTC REGS**********************************/
#define RTC_FREQ   	           *(volatile unsigned int *)(RTC_BASE+0x00)    //分频值寄存器
#define RTC_CFG   	           *(volatile unsigned int *)(RTC_BASE+0x04)    //配置寄存器
#define RTC_RTC0   	           *(volatile unsigned int *)(RTC_BASE+0x08)    //时间值寄存器0
#define RTC_RTC1   	           *(volatile unsigned int *)(RTC_BASE+0x0c)    //时间值寄存器1


#define FLASH_CMD_REG	       *(volatile unsigned int *)(FLASH_REG_BASE+0x00)   //命令寄存器
#define FLASH_CAH_REG		   *(volatile unsigned int *)(FLASH_REG_BASE+0x04)   //加密地址上界寄存器
#define FLASH_CAL_REG		   *(volatile unsigned int *)(FLASH_REG_BASE+0x08)   //加密地址下界寄存器
#define FLASH_VRF_REG		   *(volatile unsigned int *)(FLASH_REG_BASE+0x10)   //数据效验寄存器
#define FLASH_STS_REG		   *(volatile unsigned int *)(FLASH_REG_BASE+0x14)   //状态寄存器
#define FLASH_PET_REG		   *(volatile unsigned int *)(FLASH_REG_BASE+0x18)   //擦写时间寄存器







#ifdef __cplusplus
}
#endif

#endif



