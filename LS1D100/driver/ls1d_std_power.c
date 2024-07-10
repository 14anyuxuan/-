/********************************************************************
* 文件名:   ls1d6_std_power.c
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.09.30
* 说明:    Power驱动函数
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#include "../include/ls1d_std_power.h"

/******************************************************************************
 *Function Name：	 POWER_ClockFastModeConfig
 *Brief：wheather config clock fast speed .
 *
 *Param：
 * 		 FlagStatus : the clock statue .
 *			 		  RESET: normal mode
 *			 		  SET: fast mode
 *Return value：
 *       none
 *Remarks：
 *		only use for inner clock source,when enable the clock freq from 8M to 11M
 *		when disable ,clock freq form 11M to 8M in the next wake up.
 ******************************************************************************/
void POWER_ClockFastModeConfig(FlagStatus FLAG)
{

    (FLAG != RESET)? (SET_BIT(CHIPCTRL,POWER_CLOCK_SPEED_FAST_MASK)):(CLEAR_BIT(CHIPCTRL,POWER_CLOCK_SPEED_FAST_MASK));
}



/******************************************************************************
 *Function Name：	 POWER_CPUTurboModeConfig
 *Brief：wheather config cpu Turbo mode .
 *
 *Param：
 * 		 FlagStatus : the cpu module statue .
 *			 		  RESET: normal mode
 *			 		  SET: fast mode
 *Return value：
 *       none
 *Remarks：
 *		only use for inner clock source,when enable the Turbo mode cpu became 32M.
 *
 ******************************************************************************/
void POWER_CPUTurboModeConfig(FlagStatus FLAG)
{
    (FLAG != RESET)? (SET_BIT(CHIPCTRL,POWER_CPU_TURBO_MASK)):(CLEAR_BIT(CHIPCTRL,POWER_CPU_TURBO_MASK));
}



/******************************************************************************
 *Function Name：	 POWER_RamOffConfig
 *Brief：wheather config ram0 low power mode .
 *
 *Param：
 * 		 FlagStatus : the ram0 module statue .
 *			 		  RESET:RAM's power is always on;
 *			 		  SET: RAM0's power synchronous with CPU'power.
 *Return value：
 *       none
 *Remarks：
 *
 *
 ******************************************************************************/
void POWER_RamOffConfig(FlagStatus FLAG)
{

    (FLAG != RESET)? (SET_BIT(CHIPCTRL,POWER_RAM0_OFF_MASK)):(CLEAR_BIT(CHIPCTRL,POWER_RAM0_OFF_MASK));

}


/******************************************************************************
 *Function Name：	 POWER_SonarOffConfig
 *Brief：wheather config sonar low power mode .
 *
 *Param：
 * 		 FlagStatus : the sonar module statue .
 *			 		  RESET:sonar's power is always on;
 *			 		  SET: sonar's power auto off and on .
 *Return value：
 *       none
 *Remarks：
 *
 *
 ******************************************************************************/
void POWER_SonarOffConfig(FlagStatus FLAG)
{
	(FLAG != RESET)? (SET_BIT(CHIPCTRL,POWER_SONAR_OFF_MASK)):(CLEAR_BIT(CHIPCTRL,POWER_SONAR_OFF_MASK));
}


/******************************************************************************
 *Function Name：	 POWER_MbusOffConfig
 *Brief：wheather config mbus low power mode .
 *
 *Param：
 * 		 FlagStatus : the mbus module statue .
 *			 		  RESET:mbus's power is always on;
 *			 		  SET: mbus's power is always off  .
 *Return value：
 *       none
 *Remarks：
 *
 *
 ******************************************************************************/
void POWER_MbusOffConfig(FlagStatus FLAG)
{
	(FLAG != RESET)? (SET_BIT(CHIPCTRL,POWER_MBUS_OFF_MASK)):(CLEAR_BIT(CHIPCTRL,POWER_MBUS_OFF_MASK));
}

void POWER_KeyModeConfig(uint32 mode)
{
	(mode != POWER_KEY_MODE_UP_DOWN)? (SET_BIT(CHIPCTRL,POWER_KEY_MODE_MASK)):(CLEAR_BIT(CHIPCTRL,POWER_KEY_MODE_MASK));
}



/******************************************************************************
 *Function Name：	 POWER_SpiLPOffConfig
 *Brief：wheather close spi flash low power  mode .
 *
 *Param：
 * 		 FlagStatus : the clock statue .
 *			 		  RESET:mbus's power is always on;
 *			 		  SET: mbus's power is always off  .
 *Return value：
 *       none
 *Remarks：
 *
 *
 ******************************************************************************/
void POWER_SpiLPOffConfig(FlagStatus FLAG)
{
	(FLAG != RESET)? (SET_BIT(CHIPCTRL,POWER_SPI_LOW_OFF_MASK)):(CLEAR_BIT(CHIPCTRL,POWER_SPI_LOW_OFF_MASK));
}

/******************************************************************************
 *Function Name：	 POWER_SpiLowPowerOffTimeConfig
 *Brief：config exit spi flash low power mode time .
 *
 *Param：
 * 		 uint32 time : the time use for spi flash exit low power mode  .

 *Return value：
 *       none
 *Remarks：
 *
 *
 ******************************************************************************/
void POWER_SpiLowPowerOffTimeConfig(SPILowPowerCfgTime time)
{
	assert_param(IS_SPI_LOW_POWER_TIME(time));
	(time == SPI_FLASH_8us)? (SET_BIT(CHIPCTRL,SPI_FLASH_8us)):(CLEAR_BIT(CHIPCTRL,SPI_FLASH_8us));

}


/******************************************************************************
 *Function Name：	 POWER_Vr1OffConfig
 *Brief：config powercfg vr1 power off or not .
 *
 *Param：
 * 		 FlagStatus : the FLAG  .
 *			 		  RESET:mbus's power is always on;
 *			 		  SET: mbus's power is always off  .
 *Return value：
 *       none
 *Remarks：
 *
 *
 ******************************************************************************/
void POWER_Vr1OffConfig(FlagStatus FLAG)
{
	(FLAG != RESET)? (SET_BIT(POWERCfg,POWER_VR1_OFF_MASK)):(CLEAR_BIT(CHIPCTRL,POWER_VR1_OFF_MASK));
}

/******************************************************************************
 *Function Name：	 POWER_Vr1ActiveConfig
 *Brief：config powercfg vr1 active mode .
 *
 *Param：
 * 		 FlagStatus : the FLAG  .
 *			 		  RESET:VR1 standby mode, the current is 2uA;
 *			 		  SET: VR1 active mode ,the current is 20uA .
 *Return value：
 *       none
 *Remarks：
 *
 *
 ******************************************************************************/
void POWER_Vr1ActiveConfig(FlagStatus FLAG)
{
	(FLAG != RESET)? (SET_BIT(POWERCfg,POWER_VR1_MODE_MASK)):(CLEAR_BIT(CHIPCTRL,POWER_VR1_MODE_MASK));
}

/******************************************************************************
 *Function Name：	 POWER_Vr0SonarStandbyConfig
 *Brief：config powercfg vr0 standby mode .
 *
 *Param：
 * 		 FlagStatus : the FLAG  .
 *			 		  RESET:VR0 standby mode when sonar is working, the current is 2mA;
 *			 		  SET: VR0 active mode when sonar is working ,the current is 20mA .
 *Return value：
 *       none
 *Remarks：
 *
 *
 ******************************************************************************/
void POWER_Vr0SonarStandbyConfig(FlagStatus FLAG)
{
	(FLAG != RESET)? (SET_BIT(POWERCfg,POWER_VR0_MODE_MASK)):(CLEAR_BIT(CHIPCTRL,POWER_VR0_MODE_MASK));
}



/******************************************************************************
 *Function Name：	 POWER_GetClockFastMode
 *Brief： get clock mode whether work in  fast speed .
 *
 *Param：
 * 		 FlagStatus : the clock statue .
 *			 		  RESET: normal mode
 *			 		  SET: fast mode
 *Return value：
 *       SET:   11MHz
 *       RESET: 8MHz
 *Remarks：
 *		only use for inner clock source,when enable the clock freq from 8M to 11M
 *		when disable ,clock freq form 11M to 8M in the next wake up.
 ******************************************************************************/
FlagStatus  POWER_GetClockFastMode(void)
{
	FlagStatus state = RESET;
	uint32_t tmp = 0;
	tmp = READ_REG(CHIPCTRL);
	state = LS_REXT(tmp,POWER_CLOCK_SPEED_FAST);
	return state;
}



/******************************************************************************
 *Function Name：	 POWER_GetCPUTurboMode
 *Brief：get cpu whether work in Turbo mode .
 *
 *Param：
 * 		 none
 *Return value：
 *       the cpu module statue .
 *			 		  RESET: normal mode
 *			 		  SET: fast mode
 *Remarks：
 *		only use for inner clock source,when enable the Turbo mode cpu became 32M.
 *
 ******************************************************************************/
FlagStatus POWER_GetCPUTurboMode(void)
{
	FlagStatus state = RESET;
	uint32_t tmp = 0;
	tmp = READ_REG(CHIPCTRL);
	state = LS_REXT(tmp,POWER_CPU_TURBO);
	return state;
}



/******************************************************************************
 *Function Name：	 POWER_GetRamOffMode
 *Brief：get whether  ram0 work in low power mode .
 *
 *Param：
 *		none
 *Return value：
 * 		 FlagStatus : the ram0 module statue .
 *			 		  RESET:RAM's power is always on;
 *			 		  SET: RAM0's power synchronous with CPU'power.
 *Remarks：
 *
 *
 ******************************************************************************/
FlagStatus POWER_GetRamOffMode(void)
{
	FlagStatus state = RESET;
	uint32_t tmp = 0;
	tmp = READ_REG(CHIPCTRL);
	state = LS_REXT(tmp,POWER_RAM0_OFF);
	return state;
}


/******************************************************************************
 *Function Name：	 POWER_GetSonarOffMode
 *Brief：get sonar whether work in low power mode .
 *
 *Param：
 *		none
 *Return value：
 * 		 FlagStatus : the sonar module statue .
 *			 		  RESET:sonar's power is always on;
 *			 		  SET: sonar's power auto off and on .
 *Remarks：
 *
 *
 ******************************************************************************/
FlagStatus POWER_GetSonarOffMode(void)
{
	FlagStatus state = RESET;
	uint32_t tmp = 0;
	tmp = READ_REG(CHIPCTRL);
	state = LS_REXT(tmp,POWER_SONAR_OFF);
	return state;
}

/******************************************************************************
 *Function Name：	 POWER_GetMbusOffMode
 *Brief： get mbus whether work in low power mode .
 *
 *Param：
 *	  none
 *Return value：
 * 		 FlagStatus : the mbus module statue .
 *			 		  RESET:mbus's power is always on;
 *			 		  SET: mbus's power is always off  .
 *Remarks：
 *
 ******************************************************************************/
FlagStatus POWER_GetMbusOffMode(void)
{
	FlagStatus state = RESET;
	uint32_t tmp = 0;
	tmp = READ_REG(CHIPCTRL);
	state = LS_REXT(tmp,POWER_MBUS_OFF);
	return state;
}

/******************************************************************************
 *Function Name：	 POWER_GetSpiLPOffMode
 *Brief： get spi flash whether work in low power  mode .
 *
 *Param：
 *
 *Return value：
 * 		 FlagStatus : the clock statue .
 *			 		  RESET:mbus's power is always on;
 *			 		  SET: mbus's power is always off  .
 *Remarks：
 *
 ******************************************************************************/
FlagStatus POWER_GetSpiLPOffMode(void)
{
	FlagStatus state = RESET;
	uint32_t tmp = 0;
	tmp = READ_REG(CHIPCTRL);
	state = LS_REXT(tmp,POWER_SPI_LOW_OFF);
	return state;
}

/******************************************************************************
 *Function Name：	 POWER_GetVr1OffMode
 *Brief：get  powercfg vr1 power whether work in off or not .
 *
 *Param：
 *		none
 *Return value：
 * 		 FlagStatus : the FLAG  .
 *			 		  RESET:vr1's power is always on;
 *			 		  SET: vr1's power is always off  .
 *Remarks：
 *
 *
 ******************************************************************************/
FlagStatus POWER_GetVr1OffMode(void)
{
	FlagStatus state = RESET;
	uint32_t tmp = 0;
	tmp = READ_REG(POWERCfg);
	state = LS_REXT(tmp,POWER_VR1_OFF);
	return state;
}

/******************************************************************************
 *Function Name：	 POWER_GetVr1Mode
 *Brief：get powercfg vr1 whether work in active mode .
 *
 *Param：
 *		none
 *Return value：
 * 		 FlagStatus : the FLAG  .
 *			 		  RESET:VR1 standby mode, the current is 2uA;
 *			 		  SET: VR1 active mode ,the current is 20uA .
 *Remarks：
 *
 *
 ******************************************************************************/
FlagStatus POWER_GetVr1Mode(void)
{
	FlagStatus state = RESET;
	uint32_t tmp = 0;
	tmp = READ_REG(POWERCfg);
	state = LS_REXT(tmp,POWER_VR1_MODE);
	return state;
}

/******************************************************************************
 *Function Name：	 POWER_GetVr0Mode
 *Brief：get powercfg vr0 whether work in standby mode .
 *
 *Param：
 *		none
 *Return value：
 * 		 FlagStatus : the FLAG  .
 *			 		  RESET:VR0 standby mode when sonar is working, the current is 2mA;
 *			 		  SET: VR0 active mode when sonar is working ,the current is 20mA .
 *Remarks：
 *
 *
 ******************************************************************************/
FlagStatus POWER_GetVr0Mode(void)
{
	FlagStatus state = RESET;
	uint32_t tmp = 0;
	tmp = READ_REG(POWERCfg);
	state = LS_REXT(tmp,POWER_VR0_MODE);
	return state;
}


uint8_t  POWER_GetResetSource(void)
{
	uint8_t state = 0;
	uint32_t tmp = 0;
	tmp = READ_REG(PMU->COMMAND);
	state = LS_REXT(tmp,POWER_RESET_SOURCE);
	return state;
}

void POWER_SleepCPU(void)
{
	uint32_t tmp = 1;
	WRITE_REG(PMU->COMMAND_W,tmp);
}


