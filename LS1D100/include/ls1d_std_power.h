/********************************************************************
* 文件名:   ls1d6_std_power.h
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.09.30
* 说明:    本文件包含power低功耗控制的的底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef INCLUDE_POWER_H_
#define INCLUDE_POWER_H_

#include "ls1d.h"

#define POWER_CPU_TURBO_DISABLE					(uint32_t)0
#define POWER_CPU_TURBO_ENABLE					(uint32_t)1
#define POWER_CPU_TURBO_SHIFT					(uint32_t)30
#define POWER_CPU_TURBO_MASK					(uint32_t)0x40000000

#define POWER_CLOCK_SPEED_FAST_DISABLE			(uint32_t)0
#define POWER_CLOCK_SPEED_FAST_ENABLE			(uint32_t)1
#define POWER_CLOCK_SPEED_FAST_SHIFT			(uint32_t)29
#define POWER_CLOCK_SPEED_FAST_MASK				(uint32_t)0x20000000

#define POWER_RAM0_OFF_DISABLE					(uint32_t)0
#define POWER_RAM0_OFF_ENABLE					(uint32_t)1
#define POWER_RAM0_OFF_SHIFT					(uint32_t)28
#define POWER_RAM0_OFF_MASK						(uint32_t)0x10000000

#define POWER_SONAR_OFF_DISABLE					(uint32_t)0
#define POWER_SONAR_OFF_ENABLE					(uint32_t)1
#define POWER_SONAR_OFF_SHIFT					(uint32_t)27
#define POWER_SONAR_OFF_MASK					(uint32_t)0x08000000

#define POWER_MBUS_OFF_DISABLE					(uint32_t)0
#define POWER_MBUS_OFF_ENABLE					(uint32_t)1
#define POWER_MBUS_OFF_SHIFT					(uint32_t)26
#define POWER_MBUS_OFF_MASK						(uint32_t)0x04000000


#define POWER_PULSE1_CARR_DISABLE               (uint32_t)0
#define POWER_PULSE1_CARR_ENABLE                (uint32_t)1
#define POWER_PULSE1_CARR_SHIFT                 (uint32_t)25
#define POWER_PULSE1_CARR_MASK                  (uint32_t)0x02000000

#define POWER_SPI_LOW_OFF_DISABLE				(uint32_t)0
#define POWER_SPI_LOW_OFF_ENABLE				(uint32_t)1
#define POWER_SPI_LOW_OFF_SHIFT					(uint32_t)19
#define POWER_SPI_LOW_OFF_MASK					(uint32_t)0x00080000

#define POWER_VR1_OFF_DISABLE					(uint32_t)0
#define POWER_VR1_OFF_ENABLE					(uint32_t)1
#define POWER_VR1_OFF_SHIFT						(uint32_t)9
#define POWER_VR1_OFF_MASK						(uint32_t)0x00000200

#define POWER_VR1_MODE_STANDBY					(uint32_t)0
#define POWER_VR1_MODE_ACTIVE					(uint32_t)1
#define POWER_VR1_MODE_SHIFT					(uint32_t)8
#define POWER_VR1_MODE_MASK						(uint32_t)0x00000100

#define POWER_VR0_MODE_ACTIVE					(uint32_t)0
#define POWER_VR0_MODE_STANDBY					(uint32_t)1
#define POWER_VR0_MODE_SHIFT					(uint32_t)0
#define POWER_VR0_MODE_MASK						(uint32_t)0x00000001

#define POWER_VR0_STANDBY_SET			(uint32_t)0x00000001

#define POWER_RESET_SOURCE_EXTERNAL				(uint32_t)0
#define POWER_RESET_SOURCE_DOG1					(uint32_t)1
#define POWER_RESET_SOURCE_DOG2					(uint32_t)2
#define POWER_RESET_SOURCE_WAKE					(uint32_t)3
#define POWER_RESET_SOURCE_SHIFT				(uint32_t)26
#define POWER_RESET_SOURCE_MASK					(uint32_t)0x0C000000

#define POWER_BOOT_SPI_SHIFT                    (uint32_t)0
#define POWER_BOOT_SPI_MASK                     (uint32_t)0x00000001

#define POWER_BATDET_SHIFT                      (uint32_t)23
#define POWER_BATDET_MASK                       (uint32_t)0x01800000

#define POWER_PULSE_DIV_SHIFT                   (uint32_t)0
#define POWER_PULSE_DIV_MASK                    (uint32_t)0xffff
#define POWER_PULSE_CLKSEL_SHIFT                (uint32_t)16
#define POWER_PULSE_CLKSEL_MASK                 (uint32_t)0x10000
#define POWER_PULSE_ENABLE_SHIFT                (uint32_t)17
#define POWER_PULSE_ENABLE_MASK                 (uint32_t)0x20000

#define POWER_KEY_MODE_UP_DOWN				(uint32_t)0
#define POWER_KEY_MODE_DOWN					(uint32_t)1
#define POWER_KEY_MODE_SHIFT				(uint32_t)20
#define POWER_KEY_MODE_MASK					(uint32_t)0x100000


typedef enum
{
  SPI_FLASH_8us =  0x00040000,
  SPI_FLASH_256us = 0xFFFBFFFF
}SPILowPowerCfgTime;
#define IS_SPI_LOW_POWER_TIME(TIME) (((TIME) == SPI_FLASH_8us) || ((TIME) == SPI_FLASH_256us))



void POWER_CPUTurboModeConfig(FlagStatus FLAG);
void POWER_RamOffConfig(FlagStatus FLAG);
void POWER_SonarOffConfig(FlagStatus FLAG);
void POWER_MbusOffConfig(FlagStatus FLAG);

void POWER_ClockFastModeConfig(FlagStatus FLAG);
void POWER_SpiLPOffConfig(FlagStatus FLAG);
void POWER_SpiLowPowerOffTimeConfig(SPILowPowerCfgTime time);
void POWER_Vr1OffConfig(FlagStatus FLAG);
void POWER_Vr1ActiveConfig(FlagStatus FLAG);
void POWER_Vr0SonarStandbyConfig(FlagStatus FLAG);

FlagStatus POWER_GetClockFastMode(void);
FlagStatus POWER_GetCPUTurboMode(void);
FlagStatus POWER_GetRamOffMode(void);


FlagStatus POWER_GetSonarOffMode(void);
FlagStatus POWER_GetMbusOffMode(void);
FlagStatus POWER_GetSpiLPOffMode(void);
FlagStatus POWER_GetVr1OffMode(void);
FlagStatus POWER_GetVr1Mode(void);
FlagStatus POWER_GetVr0Mode(void);

uint8_t  POWER_GetResetSource(void);
void POWER_SleepCPU(void);
void POWER_KeyModeConfig(uint32 mode);


#endif /* INCLUDE_POWER_H_ */











