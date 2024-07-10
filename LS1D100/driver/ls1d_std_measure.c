/********************************************************************
* 文件名:   ls1d6_std_measure.c
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.09.30
* 说明:    本文件包含SONAR超声波时差测量的所有接口函数及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#include "../include/ls1d_std_cslreg.h"
#include "../include/ls1d_std_measure.h"
#include "../include/ls1d_std_printf.h"


extern uint32_t tdc2time(uint32_t *,uint32_t);
extern uint32_t cal_C(uint32_t,uint32_t);
extern uint32_t readw(uint32_t);
extern void fltr(void);
extern int sfa(uint32_t,uint32_t);
extern int dtofcalc(uint32_t,uint32_t);
extern int tdc1517_2ps(uint32_t,uint32_t);
extern void cpu_wait(void);

#if 0
/******************************************************************************
 *Function Name：	 MEASURE_ClockInit
 *Brief： Initializes the measure clock according to the specified
 * 		 parameters in the MeasureClock_InitTypeDef.
 *Param：
 * 		 clock: pointer to a MeasureClock_InitTypeDef structure that
 * 		 contains the pulse clock configuration information for the specified measure pulse.
 *Return value：
 *       None
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_ClockInit(MeasureClock_InitTypeDef *clock)
{
	uint32_t reg = 0;

	reg = READ_REG(PMU->TIMING);
	LS_RINS(reg,MEASURE_CLK_HS_DIV,clock->Clk_HS_Div);
	LS_RINS(reg,MEASURE_CYCLE_ZERO,clock->Cycle_Zero);
	LS_RINS(reg,MEASURE_CRUISE_TEMP,clock->Cruise_Temp);
	LS_RINS(reg,MEASURE_CRUISE_TOF,clock->Cruise_TOF);
	LS_RINS(reg,MEASURE_CYCLE_TEMP,clock->Cycle_Temp);
	LS_RINS(reg,MEASURE_CYCLE_TOF,clock->Cycle_TOF);
	LS_RINS(reg,MEASURE_CAL_RES_NUM,clock->Cal_Res_Num);
	LS_RINS(reg,MEASURE_POWER_FREQ_HZ,clock->Power_Hz_Sel);
	LS_RINS(reg,MEASURE_START_CLK_HS,clock->Start_Clk_HS);
	WRITE_REG(PMU->TIMING,reg);
}

/******************************************************************************
 *Function Name：	 MEASURE_PulseInit
 *Brief： Initializes the sonar pulse according to the specified
 * 		 parameters in the MeasurePulse_InitTypeDef.
 *Param：
 * 		 sonar : pointer to SONAR_TypeDef structure that defined reference ls1d6.h
 * 		 MEASURE_PulseInit: pointer to a MEASURE_PulseInit structure that
 * 		 contains the configuration information for the specified measure pulse.
 *Return value：
 *       None
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_PulseInit(MeasurePulse_InitTypeDef *pulse)
{
	uint32_t reg = 0;

	reg = READ_REG(SONAR->PULSE_DEF);
	LS_RINS(reg,MEASURE_FIRE_INV,pulse->Fire_Div);
	LS_RINS(reg,MEASURE_FIRE_INV,pulse->Fire_Inv);
	LS_RINS(reg,MEASURE_FIRE_PHASE,pulse->Fire_Phase);
	LS_RINS(reg,MEASURE_FIRE_SEL,pulse->Fire_Sel);
	LS_RINS(reg,MEASURE_STOP_SEL,pulse->Stop_Sel);
	LS_RINS(reg,MEASURE_FIRE_INV,pulse->Fire_Num);
	WRITE_REG(SONAR->PULSE_DEF,reg);

	reg = READ_REG(SONAR->SONAR_CTRL);
	LS_RINS(reg,MEASURE_HIT_IN,pulse->Hit_Num);
	LS_RINS(reg,MEASURE_TAIL_END,pulse->Tail_End);
	LS_RINS(reg,MEASURE_WAIT_END,pulse->Wait_End);
	LS_RINS(reg,MEASURE_HIT_IGN,pulse->Hit_Ign_Num);
	LS_RINS(reg,MEASURE_NEG_STOP,pulse->Neg_Stop);
	WRITE_REG(SONAR->SONAR_CTRL,reg);

	reg = READ_REG(SONAR->FWAVE_CTRL);
	LS_RINS(reg,MEASURE_FWAVECTRL_FHL,pulse->FHL);
	WRITE_REG(SONAR->FWAVE_CTRL,reg);

}

/******************************************************************************
 *Function Name：	 MEASURE_ControlInit
 *Brief： Initializes the measure control command according to the specified
 * 		 parameters in the MeasureControl_InitTypeDef.
 *Param：
 * 		 MeasureControl_InitTypeDef: pointer to a MeasureControl_InitTypeDef structure that
 * 		 contains the control command information for the specified measure pulse.
 *Return value：
 *       None
 *Remarks：初始化部分 line：1211，1238，1375
 *
 *
 ******************************************************************************/
void MEASURE_ControlInit(MeasureControl_InitTypeDef *control)
{
	uint32_t reg = 0;

	reg = READ_REG(SONAR->SONAR_CTRL);
	LS_RINS(reg,MEASURE_TIME_OUT_SEL,control->Time_Out_Sel);
	LS_RINS(reg,MEASURE_TREF_CHARGE,control->Time_Ref_Chrg);
	LS_RINS(reg,MEASURE_WATCH_FIRE,control->Watch_Fire);
	WRITE_REG(SONAR->SONAR_CTRL,reg);

//	reg = READ_REG(SONAR->PULSE_DEF);
//	LS_RINS(reg,MEASURE_FIRE_CURR,control->Fire_Curr);
//	WRITE_REG(SONAR->PULSE_DEF,reg);


	reg = READ_REG(SONAR->FWAVE_CTRL);
	LS_RINS(reg,MEASURE_FWAVECTRL_WAVEP,control->WaveP_En);
	LS_RINS(reg,MEASURE_FWAVECTRL_WAVEW,control->WaveW_En);
	LS_RINS(reg,MEASURE_FWAVECTRL_AUTOFW,control->Auto_FW);
	WRITE_REG(SONAR->FWAVE_CTRL,reg);

	reg = READ_REG(SONAR->TDC_CTRL1);
	LS_RINS(reg,MEASURE_TDC_OPT,control->Opt);
	WRITE_REG(SONAR->TDC_CTRL1,reg);


	reg = READ_REG(SONAR->TDC_CTRL2);
	LS_RINS(reg,MEASURE_TDC_PRE_DLY_VAL,control->Pre_Dly_Val);
	WRITE_REG(SONAR->TDC_CTRL2,reg);

	reg = READ_REG(PMU->TIMING);
	LS_RINS(reg,MEASURE_CRUISE_AUTO_DIR,control->Cru_Auto_Dir);
	LS_RINS(reg,MEASURE_CRUISE_X,control->Cruise_X);
	WRITE_REG(PMU->TIMING,reg);
}

/******************************************************************************
 *Function Name：	 MEASURE_CalibrationInit
 *Brief： Initializes the CalibrationInit according to the specified
 * 		 parameters in the MeasureCalibration_InitTypeDef.
 *Param：
 * 		 MeasureCalibration_InitTypeDef: pointer to a MeasureCalibration_InitTypeDef structure that
 * 		 contains the Calibration configuration information for the specified measure pulse.
 *Return value：
 *       None
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_CalibrationInit(MeasureCalibration_InitTypeDef *calibration)
{
	uint32_t reg = 0;

	reg = READ_REG(SONAR->SONAR_CTRL);
	LS_RINS(reg,MEASURE_AUTO_CAL_PST,calibration->Auto_Cal_Pst);
	LS_RINS(reg,MEASURE_AUTO_CAL_PRE,calibration->Auto_Cal_Pre);
	LS_RINS(reg,MEASURE_CAL_NEG_EDGE,calibration->Cal_Neg_Edge);
	WRITE_REG(SONAR->SONAR_CTRL,reg);

	reg = READ_REG(SONAR->CALIB_CTRL);
	LS_RINS(reg,MEASURE_CALIBCTRL_CALBYPASS,calibration->Cal_Bypass);
	LS_RINS(reg,MEASURE_CALIBCTRL_CALMETHOD,calibration->cal_Method);
	LS_RINS(reg,MEASURE_CALIBCTRL_CALZERO,calibration->Cal_Zero);
	LS_RINS(reg,MEASURE_CALIBCTRL_CALZERO,calibration->Cal_Delay);

	WRITE_REG(SONAR->CALIB_CTRL,reg);
}

/******************************************************************************
 *Function Name：	 MEASURE_AfeInit
 *Brief： Initializes the measure afe module according to the specified
 * 		 parameters in the MeasureAfe_InitTypeDef.
 *Param：
 * 		 afe   : pointer to a MeasureAfe_InitTypeDef structure that
 * 		 contains the afe information for the specified measure pulse.
 *Return value：
 *       None
 *Remarks：初始化部分 line：1211，1238，1375
 *
 *
 ******************************************************************************/
void MEASURE_AfeInit(MeasureAfe_InitTypeDef *afe)
{
	uint32_t reg = 0;

	reg = READ_REG(SONAR->AFE_CTRL);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST_SEL,afe->V_Test_Sel);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST_OUT,afe->V_Test_Out);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST,afe->V_Test_En);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST_DUAL,afe->V_Test_Dual);

	LS_RINS(reg,MEASURE_AFECTRL_VREF_SEL,afe->V_Ref_Sel);
	LS_RINS(reg,MEASURE_AFECTRL_VREF_OUT,afe->V_Ref_Out);
	LS_RINS(reg,MEASURE_AFECTRL_VREF,afe->V_Ref_En);
	LS_RINS(reg,MEASURE_AFECTRL_VREF_DRV,afe->V_Ref_Drv);

	LS_RINS(reg,MEASURE_AFECTRL_COMP,afe->VCMP_En);
	LS_RINS(reg,MEASURE_AFECTRL_TX,afe->Tx_Drive);
	LS_RINS(reg,MEASURE_AFECTRL_STOP_TERM0,afe->Stop_Term0);
	LS_RINS(reg,MEASURE_AFECTRL_RX_PULL_DOWN,afe->Rx_Pull_Down);
	LS_RINS(reg,MEASURE_AFECTRL_RX,afe->Rx_En);
	LS_RINS(reg,MEASURE_AFECTRL_MANMODE,afe->Man_Mode);
	LS_RINS(reg,MEASURE_AFECTRL_LNA_ENC,afe->Lna_Enc);
	LS_RINS(reg,MEASURE_AFECTRL_LNA,afe->Lna_En);
	LS_RINS(reg, MEASURE_AFECTRL_LDREF,afe->Ld_Ref);
	LS_RINS(reg,MEASURE_AFECTRL_EOPI,afe->EOPI_En);
	LS_RINS(reg, MEASURE_AFECTRL_DAC_UG,afe->Dac_Ug_En);
	LS_RINS(reg,MEASURE_AFECTRL_DAC_RANGE,afe->Dac_Range);
	LS_RINS(reg,MEASURE_AFECTRL_DAC,afe->Dac_En);

	LS_RINS(reg,MEASURE_AFECTRL_COMP_SEL,afe->Comp_Sel);
	LS_RINS(reg,MEASURE_AFECTRL_COMP,afe->Comp_En);
	WRITE_REG(SONAR->AFE_CTRL,reg);
}

/******************************************************************************
 *Function Name：	 MEASURE_StructInit
 *Brief： Initializes the Measure_InitStruct structure according to the specified default
 * 		 parameters.
 *Param：
 *
 * 		 Measure_InitStruct: pointer to a Measure_InitTypeDef structure that
 * 		 contains the configuration information for the specified measure structure.
 *Return value：
 *       None
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_StructInit(Measure_InitTypeDef *Measure_InitStruct)
{
	/* pulse 信号配置  */
	Measure_InitStruct->Pulse.Fire_Num = 32; /* 发送脉冲数 */
	Measure_InitStruct->Pulse.Hit_Num = MEASURE_HIT_IN_16;
	Measure_InitStruct->Pulse.Tail_End = MEASURE_HIT_IN_16 + 3;
	Measure_InitStruct->Pulse.Wait_End = MEASURE_HIT_IN_16 + 3 + 5;/* 时钟长度为fireCLK*/
	Measure_InitStruct->Pulse.Fire_Sel = MEASURE_FIRE_SEL_1;
	Measure_InitStruct->Pulse.Stop_Sel = MEASURE_STOP_SEL_2;
	Measure_InitStruct->Pulse.Fire_Phase = MEASURE_FIRE_PHASE_HL;
	Measure_InitStruct->Pulse.Fire_Inv = MEASURE_FIRE_INV_DISABLE;
	Measure_InitStruct->Pulse.Fire_Div = 4;	/* 8分频  HSE*/
	Measure_InitStruct->Pulse.FHL = 512;  /* 首波检测门限值 */
	Measure_InitStruct->Pulse.Hit_Ign_Num = MEASURE_HIT_IGN_0;
	Measure_InitStruct->Pulse.Neg_Stop = MEASURE_NEG_STOP_DISABLE;

	/* timing 信号配置  */
	Measure_InitStruct->Clock.Start_Clk_HS = MEASURE_START_CLK_HS_5140us;
	Measure_InitStruct->Clock.Power_Hz_Sel = MEASURE_POWER_FREQ_HZ_50;
	Measure_InitStruct->Clock.Cycle_Zero = MEASURE_CYCLE_ZERO_DISABLE;
	Measure_InitStruct->Clock.Cycle_Temp = MEASURE_CYCLE_TEMP_2;
	Measure_InitStruct->Clock.Cycle_TOF = MEASURE_CYCLE_TOF_1;
	Measure_InitStruct->Clock.Cruise_Temp = MEASURE_CRUISE_TEMP_32s;
	Measure_InitStruct->Clock.Cruise_TOF = MEASURE_CRUISE_TOF_1s;
	Measure_InitStruct->Clock.Clk_HS_Div = MEASURE_CLK_HS_DIV_1; /* 参考时钟 0 分频 */
	Measure_InitStruct->Clock.Cal_Res_Num = MEASURE_CAL_RES_NUM_16;

	Measure_InitStruct->Control.Auto_FW = MEASURE_FWAVECTRL_AUTOFW_ENABLE;
	Measure_InitStruct->Control.Cru_Auto_Dir = MEASURE_CRUISE_AUTO_DIR_ENABLE;
	Measure_InitStruct->Control.Cruise_X = MEASURE_CRUISE_X_DISABLE;

	Measure_InitStruct->Control.Opt = MEASURE_TDC_OPT_PDEN|MEASURE_TDC_OPT_PDAUTO;
	Measure_InitStruct->Control.Pre_Dly_Val = 0;

	Measure_InitStruct->Control.Time_Out_Sel = MEASURE_TIME_OUT_SEL_256US;
	Measure_InitStruct->Control.Time_Ref_Chrg = MEASURE_TREF_CHARGE_150US;
	Measure_InitStruct->Control.Watch_Fire = MEASURE_CRUISE_WATCH_DOG_DISABLE;
	Measure_InitStruct->Control.WaveP_En = MEASURE_FWAVECTRL_WAVEP_DISABLE;
	Measure_InitStruct->Control.WaveW_En = MEASURE_FWAVECTRL_WAVEW_DISABLE;

	Measure_InitStruct->Control.Dl_Cal_En = MEASURE_DLINECTRL_DL_CAL_ENABLE;
	Measure_InitStruct->Control.Dl_Cal_Byp = MEASURE_DLINECTRL_DL_CAL_BPY_DISABLE;

	/*注意：：旁路校准建议，先使能旁路自动校准并将零点值设置为0，然后根据读出来的校准零点值初始化初始零点值，
	 * 再将自动校准关闭。
	 * */
	Measure_InitStruct->Calibration.Auto_Cal_Pre = MEASURE_AUTO_CAL_PRE_DISABLE;
	Measure_InitStruct->Calibration.Auto_Cal_Pst = MEASURE_AUTO_CAL_PST_ENABLE;
	Measure_InitStruct->Calibration.Cal_Bypass = MEASURE_CALIBCTRL_CALBYPASS_ENABLE;
	Measure_InitStruct->Calibration.Cal_Delay = MEASURE_CALIBCTRL_CALDELAY5;
	Measure_InitStruct->Calibration.cal_Method = MEASURE_CALIBCTRL_CALMETHOD_BISECTION;
	Measure_InitStruct->Calibration.Cal_Neg_Edge = MEASURE_CAL_NEG_EDGE_ENABLE;
	Measure_InitStruct->Calibration.Cal_Zero = 0;

	Measure_InitStruct->Afe.V_Test_Sel = MEASURE_AFECTRL_VTEST_SEL_VREF;
	Measure_InitStruct->Afe.V_Test_Dual = MEASURE_AFECTRL_VTEST_DUAL_ENABLE;
	Measure_InitStruct->Afe.V_Test_En = MEASURE_AFECTRL_VTEST_DISABLE;
	Measure_InitStruct->Afe.Man_Mode = MEASURE_AFECTRL_MANMODE_DISABLE;
	Measure_InitStruct->Afe.Ld_Ref = MEASURE_AFECTRL_LDREF_HIGH_IMPEDENCE;
	Measure_InitStruct->Afe.Rx_En = MEASURE_AFECTRL_RX_ENABLE;
	Measure_InitStruct->Afe.Tx_Drive = MEASURE_AFECTRL_TX_24MA;
	Measure_InitStruct->Afe.Rx_Pull_Down = MEASURE_AFECTRL_RX_PULL_DOWN_TAIL;
	Measure_InitStruct->Afe.Stop_Term0 = MEASURE_AFECTRL_STOP_TERM0_VREF;
	Measure_InitStruct->Afe.EOPI_En = MEASURE_AFECTRL_EOPI_DISABLE;
	Measure_InitStruct->Afe.VCMP_En = MEASURE_AFECTRL_VCMP_DISABLE;
	Measure_InitStruct->Afe.V_Test_Out = MEASURE_AFECTRL_VTEST_OUT_CLOSE;
	Measure_InitStruct->Afe.V_Ref_Out = MEASURE_AFECTRL_VREF_OUT_DISABLE;
	Measure_InitStruct->Afe.Comp_Sel = MEASURE_AFECTRL_COMP_SEL_LNA;
	Measure_InitStruct->Afe.Comp_En = MEASURE_AFECTRL_COMP_ENABLE;
	Measure_InitStruct->Afe.Lna_En =  MEASURE_AFECTRL_LNA_ENABLE;
	Measure_InitStruct->Afe.Lna_Enc = MEASURE_AFECTRL_LNA_ENC_DISABLE;
	Measure_InitStruct->Afe.V_Ref_Drv = MEASURE_AFECTRL_VREF_DRV_100OHM;
	Measure_InitStruct->Afe.V_Ref_En = MEASURE_AFECTRL_VREF_ENABLE;
	Measure_InitStruct->Afe.V_Ref_Sel = MEASURE_AFECTRL_VREF_SEL_1dot07V;
	Measure_InitStruct->Afe.Dac_Ug_En = MEASURE_AFECTRL_DAC_UG_ENABLE;
	Measure_InitStruct->Afe.Dac_Range = MEASURE_AFECTRL_DAC_RANGE_0dot6_1dot3;
	Measure_InitStruct->Afe.Dac_En = MEASURE_AFECTRL_DAC_ENABLE;

	Measure_InitStruct->Win1.WinID = 1;
	Measure_InitStruct->Win1.DelayValCycle  = 57* 8; /* 参考时钟 为CLKHS */
	Measure_InitStruct->Win1.DelayValFrac = 0;
	Measure_InitStruct->Win1.GateLen = 100;
	Measure_InitStruct->Win1.One_Shot = MEASURE_GATE_ONE_SHOT_DISABLE;
	Measure_InitStruct->Win1.Gate_Keep = MEASURE_GATE_KEPP_OPEN_DISABLE;

	/* 一个hit值的窗口设计 */
	Measure_InitStruct->Win2.WinID = 2;
	Measure_InitStruct->Win2.DelayValCycle  = 7* 8;
	Measure_InitStruct->Win2.DelayValFrac = 0;
	Measure_InitStruct->Win2.GateLen = 1;
	Measure_InitStruct->Win2.One_Shot = MEASURE_GATE_ONE_SHOT_DISABLE;
	Measure_InitStruct->Win2.Gate_Keep = MEASURE_GATE_KEPP_OPEN_ENABLE;

}

#endif

/******************************************************************************
 *Function Name：	 MEASURE_GateWindowInit
 *Brief： Initializes the measure gate window  according to default
 * 		 parameters .
 *Param：
 *
 *	none
 *Return value：
 *       None
 *Remarks：
 *
 ******************************************************************************/
void MEASURE_GateWindowInit(void)
{
	uint32_t reg = 0;
	MeasureGate_InitTypeDef gate1 = {0, 54*8, 0, 240, 1, 0};	//considering the fastest speed of sound
	MeasureGate_InitTypeDef gate2 = {1,  7*8, 0,   1, 0, 1};

	// DLine
	LS_RINS(reg, MEASURE_DLINECTRL_DL_CAL,  MEASURE_DLINECTRL_DL_CAL_DISABLE);//g
	LS_RINS(reg, MEASURE_DLINECTRL_DL_CAL_BPY,  MEASURE_DLINECTRL_DL_CAL_BPY_DISABLE);
	WRITE_REG(SONAR->DLINE_CTRL,reg);
	// Windows

	MEASURE_TdcSetWindow(&gate1);
	MEASURE_TdcSetWindow(&gate2);
}

/******************************************************************************
 *Function Name：	 MEASURE_DefaultInit
 *Brief： Initializes the measure reg according to the default
 * 		 parameters .
 *Param：
 * 		 none
 *Return value：
 *       None
 *Remarks：
 *		    初始化部分 line：1211，1238，1375
 *
 ******************************************************************************/
void MEASURE_DefaultInit(void)
{

	uint32_t reg = 0;
	reg = READ_REG(PMU->TIMING);
	LS_RINS(reg,MEASURE_START_CLK_HS,MEASURE_START_CLK_HS_5140us);
	LS_RINS(reg,MEASURE_CLK_HS_DIV,MEASURE_CLK_HS_DIV_1);
	LS_RINS(reg,MEASURE_CAL_RES_NUM,MEASURE_CAL_RES_NUM_2);//g
//	LS_RINS(reg,MEASURE_CRUISE_OSC8M,MEASURE_CRUISE_OSC8M_DISABLE);//g new debug
	LS_RINS(reg,MEASURE_CRUISE_AUTO_DIR,MEASURE_CRUISE_AUTO_DIR_ENABLE);
	LS_RINS(reg,MEASURE_CYCLE_ZERO,MEASURE_CYCLE_ZERO_DISABLE);
	LS_RINS(reg,MEASURE_CRUISE_X,MEASURE_CRUISE_X_DISABLE);
	LS_RINS(reg,MEASURE_CRUISE_TOF,MEASURE_CRUISE_TOF_0dot25s);//g
	LS_RINS(reg,MEASURE_CYCLE_TOF,MEASURE_CYCLE_TOF_1);
	LS_RINS(reg,MEASURE_CRUISE_TEMP,MEASURE_CRUISE_TEMP_8s);//g
	LS_RINS(reg,MEASURE_CYCLE_TEMP,MEASURE_CYCLE_TEMP_1);
	LS_RINS(reg,MEASURE_POWER_FREQ_HZ,MEASURE_POWER_FREQ_HZ_50);//g
	WRITE_REG(PMU->TIMING,reg);

	reg = 0;
	LS_RINS(reg,MEASURE_FIRE_NUM,30);//g发波数
	LS_RINS(reg,MEASURE_FIRE_SEL,MEASURE_FIRE_SEL_1);
	LS_RINS(reg,MEASURE_FIRE_DIV,4);
	LS_RINS(reg,MEASURE_FIRE_INV,MEASURE_FIRE_INV_DISABLE);
	LS_RINS(reg,MEASURE_STOP_SEL,MEASURE_STOP_SEL_2);

	//LS_RINS(reg,MEASURE_FIRE_PHASE,MEASURE_FIRE_PHASE_HL);//g
	WRITE_REG(SONAR->PULSE_DEF,reg);

	reg = 0;
	LS_RINS(reg,MEASURE_TIME_OUT_SEL,MEASURE_TIME_OUT_SEL_256US);
	LS_RINS(reg,MEASURE_TREF_CHARGE,MEASURE_TREF_CHARGE_150US);
	LS_RINS(reg,MEASURE_WATCH_FIRE,MEASURE_WATCH_FIRE_DISABLE);
	LS_RINS(reg,MEASURE_HIT_IN,MEASURE_HIT_IN_15);	//g31 hit_num
	LS_RINS(reg,MEASURE_TAIL_END,55);				//g31 fire_num < TailEnd
	LS_RINS(reg,MEASURE_WAIT_END,55);				//g31 fire_num < WaitEnd < win1_DelayVal
	LS_RINS(reg,MEASURE_HIT_IGN,MEASURE_HIT_IGN_0);
	LS_RINS(reg,MEASURE_NEG_STOP,MEASURE_NEG_STOP_DISABLE);
	LS_RINS(reg,MEASURE_CAL_NEG_EDGE,MEASURE_CAL_NEG_EDGE_ENABLE);
	LS_RINS(reg,MEASURE_AUTO_CAL_PST,MEASURE_AUTO_CAL_PST_ENABLE);
	//LS_RINS(reg,MEASURE_AUTO_CAL_PRE,MEASURE_AUTO_CAL_PRE_DISABLE);
	WRITE_REG(SONAR->SONAR_CTRL,reg);

	reg = 0;
	//reg = READ_REG(SONAR->TDC_CTRL1);
	LS_RINS(reg,MEASURE_TDC_OPT, MEASURE_TDC_OPT_PDEN|MEASURE_TDC_OPT_PDAUTO);
	WRITE_REG(SONAR->TDC_CTRL1,reg);

	reg = 0;
	LS_RINS(reg,MEASURE_TDC_PRE_DLY_VAL,0);
	LS_RINS(reg,MEASURE_TDC_PRE_DLY_INC,MEASURE_TDC_PRE_DLY_INC1);	//g
	WRITE_REG(SONAR->TDC_CTRL2,reg);

	reg = 0;
	LS_RINS(reg,MEASURE_CALIBCTRL_CALBYPASS,MEASURE_CALIBCTRL_CALBYPASS_ENABLE);
	LS_RINS(reg,MEASURE_CALIBCTRL_CALMETHOD,MEASURE_CALIBCTRL_CALMETHOD_BISECTION);
	LS_RINS(reg,MEASURE_CALIBCTRL_CALZERO,0);
	LS_RINS(reg,MEASURE_CALIBCTRL_CALDELAY,MEASURE_CALIBCTRL_CALDELAY5 );
	WRITE_REG(SONAR->CALIB_CTRL,reg);

	reg = 0;
	LS_RINS(reg,MEASURE_FWAVECTRL_FHL,900);
	LS_RINS(reg,MEASURE_FWAVECTRL_WAVEP,MEASURE_FWAVECTRL_WAVEP_DISABLE);
//	LS_RINS(reg,MEASURE_FWAVECTRL_WAVEW,MEASURE_FWAVECTRL_WAVEW_DISABLE);	//g
	LS_RINS(reg,MEASURE_FWAVECTRL_AUTOFW,MEASURE_FWAVECTRL_AUTOFW_ENABLE);
	WRITE_REG(SONAR->FWAVE_CTRL,reg);

	reg = 0;

	LS_RINS(reg,MEASURE_AFECTRL_VREF,MEASURE_AFECTRL_VREF_ENABLE);
	LS_RINS(reg,MEASURE_AFECTRL_VREF_SEL,MEASURE_AFECTRL_VREF_SEL_1dot07V);
	LS_RINS(reg,MEASURE_AFECTRL_VREF_DRV,MEASURE_AFECTRL_VREF_DRV_1000OHM);//g
	LS_RINS(reg,MEASURE_AFECTRL_VREF_OUT,MEASURE_AFECTRL_VREF_OUT_DISABLE);

	LS_RINS(reg,MEASURE_AFECTRL_TX,MEASURE_AFECTRL_TX_24MA);
	LS_RINS(reg,MEASURE_AFECTRL_RX_PULL_DOWN,MEASURE_AFECTRL_RX_PULL_DOWN_TAIL);
	LS_RINS(reg,MEASURE_AFECTRL_RX,MEASURE_AFECTRL_RX_ENABLE);
	LS_RINS(reg,MEASURE_AFECTRL_STOP_TERM0,MEASURE_AFECTRL_STOP_TERM0_VREF);

	//LS_RINS(reg,MEASURE_AFECTRL_MANMODE,MEASURE_AFECTRL_MANMODE_DISABLE);//g


	LS_RINS(reg,MEASURE_AFECTRL_DAC,MEASURE_AFECTRL_DAC_ENABLE);
	LS_RINS(reg,MEASURE_AFECTRL_DAC_RANGE,MEASURE_AFECTRL_DAC_RANGE_0dot6_1dot3);
	LS_RINS(reg,MEASURE_AFECTRL_DAC_UG,MEASURE_AFECTRL_DAC_UG_ENABLE);

	LS_RINS(reg,MEASURE_AFECTRL_VTEST_SEL,MEASURE_AFECTRL_VTEST_SEL_VREF);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST_OUT,MEASURE_AFECTRL_VTEST_OUT_CLOSE);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST,MEASURE_AFECTRL_VTEST_DISABLE);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST_DUAL,MEASURE_AFECTRL_VTEST_DUAL_DISABLE);//g

	//LS_RINS(reg,MEASURE_AFECTRL_VCMP,MEASURE_AFECTRL_VCMP_ENABLE);//g-debug
	LS_RINS(reg,MEASURE_AFECTRL_VCMP,MEASURE_AFECTRL_VCMP_ENABLE);//g-debug
	LS_RINS(reg,MEASURE_AFECTRL_LDREF,MEASURE_AFECTRL_LDREF_HIGH_IMPEDENCE);
	LS_RINS(reg,MEASURE_AFECTRL_EOPI,MEASURE_AFECTRL_EOPI_DISABLE);
	LS_RINS(reg,MEASURE_AFECTRL_LNA,MEASURE_AFECTRL_LNA_ENABLE);
	LS_RINS(reg,MEASURE_AFECTRL_LNA_ENC,MEASURE_AFECTRL_LNA_ENC_DISABLE);
	LS_RINS(reg,MEASURE_AFECTRL_COMP_SEL,MEASURE_AFECTRL_COMP_SEL_LNA);
	LS_RINS(reg,MEASURE_AFECTRL_COMP,MEASURE_AFECTRL_COMP_ENABLE);
	WRITE_REG(SONAR->AFE_CTRL,reg);

	reg = 0;

	MEASURE_GateWindowInit();

}
#if 0
/******************************************************************************
 *Function Name：	 MEASURE_DefaultInit
 *Brief： Initializes the measure reg according to the default
 * 		 parameters .
 *Param：
 * 		 none
 *Return value：
 *       None
 *Remarks：
 *		    初始化部分 line：1211，1238，1375
 *
 ******************************************************************************/
void MEASURE_DefaultPmuInit(void)
{

//	const MeasureTiming_TypeDef 	*pmu_timing = PMU->TIMING;
//	const MeasureCmd_TypeDef 		*pmu_command = PMU->COMMAND;
//	const MeasureChipCtrl_TypeDef *pmu_chipctrl = PMU->CHIP_CTRL;
//	const MeasureCMDW_TypeDef 	*pmu_commandw = PMU->COMMAND_W;
//	const MeasureAutoCalc_TypeDef *pmu_autocalc = PMU->AUTO_CALC;


}
void MEASURE_DefaultRegInit(void)
{
//	const Measure_RegInitTypeDef *sonar_ctrl = *SONAR;
}
#endif

/******************************************************************************
 *Function Name：	 MEASURE_TdcSetWindow
 *Brief： Initializes the tdc gate window reg according to the specified
 * 		 parameters in the MeasureGate_InitTypeDef.
 *Param：
 *       gate: pointer to a MeasureGate_InitTypeDef structure that
 * 		 contains the window configuration information for the specified measure pulse.
 *
 *Return value：
 *       None
 *Remarks：设置TDC窗口值
 *
 *
 ******************************************************************************/
void MEASURE_TdcSetWindow(MeasureGate_InitTypeDef *gate)
{
	uint32_t reg = 0;

	switch(gate->WinID)
	{
	case 1:
		reg = READ_REG(SONAR->GATE_DEF2);
		LS_RINS(reg, MEASURE_GATE_DELAY_VAL, (((gate->DelayValCycle)<<5) | ((gate->DelayValFrac)&0x1f)));
		LS_RINS(reg, MEASURE_GATE_LEN , gate->GateLen);
		LS_RINS(reg, MEASURE_GATE_ONE_SHOT, gate->One_Shot);
		LS_RINS(reg, MEASURE_GATE_KEPP_OPEN, gate->Gate_Keep);
	    WRITE_REG(SONAR->GATE_DEF2,reg);
		break;
	case 2:
		reg = READ_REG(SONAR->GATE_DEF3);
		LS_RINS(reg, MEASURE_GATE_DELAY_VAL, (((gate->DelayValCycle)<<5) | ((gate->DelayValFrac)&0x1f)));
		LS_RINS(reg, MEASURE_GATE_LEN , gate->GateLen);
		LS_RINS(reg, MEASURE_GATE_ONE_SHOT, gate->One_Shot);
		LS_RINS(reg, MEASURE_GATE_KEPP_OPEN, gate->Gate_Keep);
	    WRITE_REG(SONAR->GATE_DEF3,reg);
		break;
	default:
		reg = READ_REG(SONAR->GATE_DEF1);
		LS_RINS(reg, MEASURE_GATE_DELAY_VAL, (((gate->DelayValCycle)<<5) | ((gate->DelayValFrac)&0x1f)));
		LS_RINS(reg, MEASURE_GATE_LEN , gate->GateLen);
		LS_RINS(reg, MEASURE_GATE_ONE_SHOT, gate->One_Shot);
		LS_RINS(reg, MEASURE_GATE_KEPP_OPEN, gate->Gate_Keep);
	    WRITE_REG(SONAR->GATE_DEF1,reg);
		break;
	}
}



/******************************************************************************
 *Function Name：	 MEASURE_GetPulseWidth
 *Brief： get pulse width value from data result state reg.
 *Param：
 *       pulse_width: pointer to a MeasurePulseWidth_StateTypeDef structure that
 * 		 contains the result of state information for the specified measure pulse.
 *
 *Return value：
 *       the state of function;
 *Remarks：设置TDC窗口值
 *
 *
 ******************************************************************************/
ErrorStatus MEASURE_GetPulseWidth(MeasurePulseWidth_StateTypeDef *pulse_width)
{
	ErrorStatus status = ERROR;
	uint32_t tmp = LS_REXT(MEASURE->COMMAND, MEASURE_MOP);
	uint32_t cal_pre = LS_REXT(SONAR->SONAR_CTRL,MEASURE_AUTO_CAL_PRE);
	uint32_t wave_w = LS_REXT(SONAR->FWAVE_CTRL,MEASURE_FWAVECTRL_WAVEW);
	/* 判断是否使能脉冲宽度测量 */
	if(wave_w != 1)
	{
		printf("not wave width set \n");
		return status;
	}
	/* 判断是否使能tdc前校准  */
	if(cal_pre)
	{
		/* 判断测量模式时单向时差测量还是双向时差测量  */
		if(tmp == MEASURE_MOP_ONCE_TOF)
		{
			pulse_width->PrePulse1Width = (readw(StsFwd+12) & 0x1ffff) >> 5;
			pulse_width->PrePulse2Width = (readw(StsFwd+16) & 0x1ffff) >> 5;
			pulse_width->PstPulse1Width = 0;
			pulse_width->PstPulse2Width = 0;
			status = SUCCESS;
		}
		else if(tmp == MEASURE_MOP_TWICE_TOF)
		{
			pulse_width->PrePulse1Width = (readw(StsFwd+12) & 0x1ffff) >> 5;
			pulse_width->PrePulse2Width = (readw(StsFwd+16) & 0x1ffff) >> 5;
			pulse_width->PstPulse1Width = (readw(StsBwd+12) & 0x1ffff) >> 5;
			pulse_width->PstPulse2Width = (readw(StsBwd+16) & 0x1ffff) >> 5;
			status = SUCCESS;
		}

	}else {

		if(tmp == MEASURE_MOP_ONCE_TOF)
		{
			pulse_width->PrePulse1Width = (readw(StsFwd+4) & 0x1ffff) >> 5;
			pulse_width->PrePulse2Width = (readw(StsFwd+8) & 0x1ffff) >> 5;
			pulse_width->PstPulse1Width = 0;
			pulse_width->PstPulse2Width = 0;
			status = SUCCESS;
		}
		else if(tmp == MEASURE_MOP_TWICE_TOF)
		{
			pulse_width->PrePulse1Width = (readw(StsFwd+4) & 0x1ffff) >> 5;
			pulse_width->PrePulse2Width = (readw(StsFwd+8) & 0x1ffff) >> 5;
			pulse_width->PstPulse1Width = (readw(StsBwd+4) & 0x1ffff) >> 5;
			pulse_width->PstPulse2Width = (readw(StsBwd+8) & 0x1ffff) >> 5;
			status = SUCCESS;
		}
	}

	return status;
}

/******************************************************************************
 *Function Name：	 MEASURE_GetTdcCal
 *Brief： get tdc  calibration value from data result state register.
 *Param：
 *       cal: pointer to a MeasureTdcCal_StateTypeDef structure that
 * 		 contains the result of tdc calibration information for the specified
 * 		 measure pulse.
 *
 *Return value：
 *       the state of function;
 *Remarks：设置TDC窗口值
 *
 ******************************************************************************/
ErrorStatus MEASURE_GetTdcCal(MeasureTdcCal_StateTypeDef *cal)
{
	ErrorStatus status = ERROR;
	uint32_t cal_pre = LS_REXT(SONAR->SONAR_CTRL,MEASURE_AUTO_CAL_PRE);
	uint32_t cal_pst = LS_REXT(SONAR->SONAR_CTRL,MEASURE_AUTO_CAL_PST);
	uint32_t tmp = LS_REXT(MEASURE->COMMAND, MEASURE_MOP);
	uint32_t wave_w = LS_REXT(SONAR->FWAVE_CTRL,MEASURE_FWAVECTRL_WAVEW);
	uint32_t C_f1=0, C_f2=0, C_b1=0, C_b2=0;

	if((cal_pre != 1)&&(cal_pst != 1))
	{
		//printf("not tdc cal set \n");
		return status;

	}

	if(tmp == MEASURE_MOP_TWICE_TOF)
	{

		if(cal_pre)
		{
			C_f1 = cal_C(StsFwd+4, StsFwd+8);
			C_b1 = cal_C(StsBwd+4, StsBwd+8);

			if(wave_w)
			{
				if(cal_pst)
				{
					C_f2 = cal_C(StsFwd+20, StsFwd+24);
					C_b2 = cal_C(StsBwd+20, StsBwd+24);
					cal->ForwardCal_C = (C_f1 + C_f2) >> 1;
					cal->BackwardCal_C = (C_b1 + C_b2) >> 1;
				}
				else
				{
					cal->ForwardCal_C = C_f1;
					cal->BackwardCal_C = C_b1;
				}
				status = SUCCESS;
			}else if(cal_pst){

				C_f2 = cal_C(StsFwd+12, StsFwd+16);
				C_b2 = cal_C(StsBwd+12, StsBwd+16);
				cal->ForwardCal_C = (C_f1 + C_f2) >> 1;
				cal->BackwardCal_C = (C_b1 + C_b2) >> 1;

			}else{
				cal->ForwardCal_C = C_f1;
				cal->BackwardCal_C = C_b1;
			}
			status = SUCCESS;
		}else{

			if(wave_w)
			{
				if(cal_pst)
				{
					C_f2 = cal_C(StsFwd+12, StsFwd+16);
					C_b2 = cal_C(StsBwd+12, StsBwd+16);
				}else{
					C_f2 = 0;
					C_b2 = 0;
				}

			}else if(cal_pst){

				  C_f2 = cal_C(StsFwd+4, StsFwd+8);
				  C_b2 = cal_C(StsBwd+4, StsBwd+8);
			}

			cal->ForwardCal_C = C_f2;
			cal->BackwardCal_C = C_b2;
			status = SUCCESS;
		}

	}else if(tmp == MEASURE_MOP_ONCE_TOF)
	{
		if(cal_pre)
		{
			C_f1 = cal_C(StsFwd+4, StsFwd+8);

			if(wave_w)
			{
				C_f2 = cal_C(StsFwd+20, StsFwd+24);
				cal->ForwardCal_C = (C_f1 + C_f2) >> 1;
			}else if(cal_pst){

				C_f2 = cal_C(StsFwd+12, StsFwd+16);
				cal->ForwardCal_C = (C_f1 + C_f2) >> 1;

			}else{
				cal->ForwardCal_C = C_f1;

			}
			status = SUCCESS;
		}else{

			if(wave_w)
			{
				C_f2 = cal_C(StsFwd+12, StsFwd+16);

			}else if(cal_pst){

				C_f2 = cal_C(StsFwd+4, StsFwd+8);

			}
			cal->ForwardCal_C = C_f2;
			status = SUCCESS;
		}
	}else if((tmp == MEASURE_MOP_TDC)||(tmp == MEASURE_MOP_HSE_CAL)||\
			(tmp == MEASURE_MOP_TRANSDUCERS))
	{
		cal->ForwardCal_C = cal_C(StsFwd, StsFwd+4);
		status = SUCCESS;
	}
	else if(tmp == MEASURE_MOP_TWICE_TEMP)
	{
		cal->ForwardCal_C = cal_C(StsFwd, StsFwd+4);
		cal->BackwardCal_C = cal_C(StsBwd, StsFwd+4);
	}
	else if((tmp == MEASURE_MOP_ONCE_TEMP))
	{
		if (MEASURE_GetTemperaturePortDirection())
		{
			cal->ForwardCal_C = cal_C(StsFwd, StsFwd+4);
		}else
		{
			cal->BackwardCal_C = cal_C(StsBwd, StsFwd+4);
		}
	}
	return status;
}

/******************************************************************************
 *Function Name：	 MEASURE_WriteTdcCalToReg
 *Brief： set tdc  calibration value to data result state register 0x1ebc.
 *Param：
 *       cal: pointer to a MeasureTdcCal_StateTypeDef structure that
 * 		 contains the result of tdc calibration information for the specified
 * 		 measure pulse.
 *
 *Return value：
 *       the state of function;
 *Remarks：设置TDC窗口值
 *
 ******************************************************************************/
ErrorStatus MEASURE_WriteTdcCalToReg(const MeasureTdcCal_StateTypeDef *cal)
{
	ErrorStatus status = ERROR;
	uint32_t tmp = 0;
	tmp = LS_REXT(MEASURE->COMMAND, MEASURE_MOP);

	if((tmp == MEASURE_MOP_ONCE_TOF)||(tmp == MEASURE_MOP_TRANSDUCERS)||\
			(tmp == MEASURE_MOP_TDC)||(tmp == MEASURE_MOP_HSE_CAL))
	{
		LS_WREG(cal->ForwardCal_C,CMem_RAM,TdcCal);

		status = SUCCESS;

	}else if((tmp == MEASURE_MOP_TWICE_TOF)||(tmp == MEASURE_MOP_TWICE_TEMP)) \
	{

		LS_WREG(((cal->ForwardCal_C + cal->BackwardCal_C) >> 1),CMem_RAM,TdcCal);

		status = SUCCESS;
	}
	else if((tmp == MEASURE_MOP_ONCE_TEMP))
	{
		if (MEASURE_GetTemperaturePortDirection())
		{
			LS_WREG(cal->ForwardCal_C,CMem_RAM,TdcCal);
		}else
		{
			LS_WREG(cal->BackwardCal_C,CMem_RAM,TdcCal);
		}
		status = SUCCESS;
	}

	return status;
}


/******************************************************************************
 *Function Name：	 MEASURE_GetStartTime
 *Brief： get start time value from data result state register.
 *Param：
 *       cal: pointer to a MeasureTdcCal_StateTypeDef structure that
 * 		 contains the result of tdc calibration information for the specified
 * 		 measure pulse.
 *		 FLAG:a flag of measure direction that contains forward and backward two state;
 *Return value：
 *       the value of start time that data structure is (15.17);
 *Remarks：
 *
 ******************************************************************************/
uint32_t MEASURE_GetStartTime(const MeasureTdcCal_StateTypeDef *cal,MeasureDirection_StateTypeDef FLAG)
{
	uint32_t data = 0;
	uint32_t tmp = 0;

	tmp = LS_REXT(MEASURE->COMMAND, MEASURE_MOP);

	if(tmp == MEASURE_MOP_ONCE_TEMP)
	{
		data = (FLAG ==ForwardDirction)? tdc2time(StsFwd,cal->ForwardCal_C) : tdc2time(StsBwd,cal->BackwardCal_C);

	}else if(tmp == MEASURE_MOP_TWICE_TOF){

		data = (FLAG ==ForwardDirction)? tdc2time(StsFwd,cal->ForwardCal_C) : tdc2time(StsBwd,cal->BackwardCal_C);
	}
	return data;
}


/******************************************************************************
 *Function Name：	 MEASURE_GetResData
 *Brief： get hit stop value from data result state register.
 *Param：
 *       index: pointer to the number that you want get form result register(0x1f80,0x1f00)
 *
 *		 FLAG:a flag that define by MeasureDirection_StateTypeDef structure.
 *		 that contains forward and backward two state;
 *Return value：
 *
 *       the value of start time that data structure is (15.17);
 *
 *Remarks：
 *		 index < 32 ;rang from 0 to 31
 ******************************************************************************/
uint32_t MEASURE_GetResData(const MeasureTdcCal_StateTypeDef *cal,MeasureResIndex_StateTypedef index,MeasureDirection_StateTypeDef FLAG)
{
	uint32_t data = 0;

	assert_param(IS_MEASURE_DIRCTION(FLAG));
	assert_param(IS_MEASURE_RES_INDEX(index));

	//data = (FLAG == ForwardDirction)? *(uint32_t*)(ResFwd + index * 4) : *(uint32_t*)(ResBwd + index * 4);
	//tdc2time();
	 data = (FLAG == ForwardDirction)? tdc2time((ResFwd + index*4),cal->ForwardCal_C):\
			 tdc2time((ResBwd + index*4),cal->BackwardCal_C);
	return data;
}


/******************************************************************************
 *Function Name：	 MEASURE_ClearResPtrReg
 *Brief： clear  data result state register indicator.
 *Param：
 *
 *Return value：
 *		none
 *Remarks：
 *
 ******************************************************************************/
void MEASURE_ClearResPtrReg(void)
{
	uint32_t tmp = 0;
	/* clear resptr reg */
	LS_WREG(tmp, CMem_RAM, ResPtr);
}



/******************************************************************************
 *Function Name：	 MEASURE_ClearADCPtrReg
 *Brief： clear  adc data result register indicator.
 *Param：
 *		none
 *Return value：
 *
 *		none
 *Remarks：
 *		 ADC value is in the address 0x1edc.
 ******************************************************************************/
void MEASURE_ClearADCPtrReg(void)
{
	uint32_t tmp = 0;
	/* clear resptr reg */
	LS_WREG(tmp, CMem_RAM, AdcVal);
}

/******************************************************************************
 *Function Name：	 MEASURE_ClearTdcResReg
 *Brief： clear  tdc data result register indicator.
 *Param：
 *		none
 *Return value：
 *
 *		none
 *Remarks：
 *		 tdc result value is in the address 0x1eb8.
 ******************************************************************************/
void MEASURE_ClearTdcResReg(void)
{
	uint32_t tmp = 0x0fffffff;
	/* clear tdc result register */
	LS_WREG(tmp, CMem_RAM, TdcRes);
}

/******************************************************************************
 *Function Name：	 MEASURE_GetTdcResReg
 *Brief： get  tdc data result register indicator.
 *Param：
 *		none
 *Return value：
 *
 *		the auto tdc reseult data.
 *Remarks：
 *		 tdc result value is in the address 0x1eb8.
 ******************************************************************************/
ErrorStatus MEASURE_GetTdcResReg(int *result)
{
	ErrorStatus status = ERROR;
	int tmp = 0;
	/* read resptr reg */
	LS_RREG(tmp, CMem_RAM, TdcRes);

	if(tmp != TDC_RES_DEFAULT)
	{
		*result = tmp;
		status = SUCCESS;
	}else{
		*result = 0;
	}
	return status;
}


/******************************************************************************
 *Function Name：	 MEASURE_ClearTdcCalReg
 *Brief： clear  tdc data result register indicator.
 *Param：
 *		none
 *Return value：
 *
 *		none
 *Remarks：
 *		 ADC value is in the address 0x1ebc.
 ******************************************************************************/
void MEASURE_ClearTdcCalReg(void)
{
	uint32_t tmp = 0;
	/* clear tdc result register */
	LS_WREG(tmp, CMem_RAM, TdcCal);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetResReadFlag
 *Brief： set result data has been read flag state register.
 *Param：
 *
 *Return value：
 *		none
 *Remarks：
 *
 ******************************************************************************/
void  MEASURE_SetResReadFlag(void)
{
	SET_BIT(COMMANDW,(MEASURE_RES_READW_ENABLE << MEASURE_RES_READW_SHIFT));
	//uint32_t tmp = READ_REG(PMU->COMMAND_W);
	//LS_RINS(tmp,MEASURE_RES_READW,MEASURE_RES_READW_ENABLE);
	//WRITE_REG(PMU->COMMAND_W,tmp);
}



/******************************************************************************
 *Function Name：	 MEASURE_GetResPtrReg
 *Brief：get data result register indicator data.
 *Param：
 *		none
 *Return value：
 *
 *		the data that indicate the number of result register.
 *Remarks：
 *		 the value which return  is same with 0x5a2c data.
 ******************************************************************************/
uint32_t MEASURE_GetResPtrReg(void)
{
	uint32_t tmp = 0;
	/* read resptr reg */
	LS_RREG(tmp, CMem_RAM, ResPtr);
	return tmp;
}

/******************************************************************************
 *Function Name：	 GetVrefValue
 *Brief：get sonar adc reference voltage.
 *Param：
 *		 FLAG:a flag that define by MeasureDirection_StateTypeDef structure.
 *		 that contains forward and backward two state;
 *Return value：
 *
 *		the  reference voltage.
 *Remarks：
 *		用于计算获芯片内容测量时，使用的内部参考电压值
 ******************************************************************************/
int GetVrefValue(void)
{
	uint32_t tmp = 0,reg = 0,reg_bk = 0,i = 0;
	int verf = 0;
	reg = READ_REG(SONAR->AFE_CTRL);
	reg_bk = reg;
	LS_RINS(reg,MEASURE_AFECTRL_VTEST_SEL,MEASURE_AFECTRL_VTEST_SEL_VREF);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST_SEL,MEASURE_AFECTRL_VTEST_DUAL_DISABLE);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST,MEASURE_AFECTRL_VTEST_ENABLE);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST_OUT,MEASURE_AFECTRL_VTEST_OUT_OTHER);
	LS_RINS(reg,MEASURE_AFECTRL_VREF_OUT,MEASURE_AFECTRL_VREF_OUT_ENABLE);

	WRITE_REG(SONAR->AFE_CTRL,reg);

	LS_RINS(reg,MEASURE_FWAVECTRL_WAVEP,MEASURE_FWAVECTRL_WAVEP_ENABLE);

	MEASURE_ClearADCPtrReg();

	for(;i<2;i++)
	{
		MEASURE_SetTaskToStart(MEASURE_MOP_TWICE_TOF);
		MEASURE_SuspendTask();
		verf += MEASURE_GetAmcValue(ForwardDirction);
	}
	verf = verf >> 1;

	WRITE_REG(SONAR->AFE_CTRL,reg_bk);

	return verf;
}


/******************************************************************************
 *Function Name：	 MEASURE_GetAmcValue
 *Brief：get amc result register  data.
 *Param：
 *		 FLAG:a flag that define by MeasureDirection_StateTypeDef structure.
 *		 that contains forward and backward two state;
 *Return value：
 *
 *		the data that indicate the number of result register.
 *Remarks：
 *		 the low 16bit is forward direction value,the high 16bit data is backward direction value.
 ******************************************************************************/
uint32_t MEASURE_GetAmcValue(MeasureDirection_StateTypeDef FLAG)
{
	uint32_t tmp = *(volatile unsigned int*) AdcVal;
	uint32_t data = 0;

	data = (FLAG == ForwardDirction)? (tmp& 0xffff): ((tmp >> 16) & 0xffff);

	return data;
}

/******************************************************************************
 *Function Name：	 MEASURE_GetAutoCalculateFirRate
 *Brief：get the filter rate value that store in auto-calculate register .
 *Param：
 *		 none;
 *Return value：
 *
 *		the filter rate value between 0 and 3.
 *Remarks：
 *
 ******************************************************************************/
uint32_t MEASURE_GetAutoCalculateFirRate(void)
{
	uint32_t tmp = 0,reg = 0;
	tmp = READ_REG(PMU->AUTO_CALC);
	reg = LS_REXT(tmp,MEASURE_FLT_RATE);
	return reg;
}

/******************************************************************************
 *Function Name：	 MEASURE_GetAutoDtofValue
 *Brief：get dtof value that produced by chip inner hardware structure .
 *Param：
 *		 hit_count:the number of hit stop.
 *		 filter_count: the number for filter to reduce abnormal data reference
 *		 autocalc register's fltRate ;
 *Return value：
 *
 *		the average difference between forward time and backward time.
 *Remarks：
 *		使用前确保tdc校准值有进行更新，自动计算需使用前一组数据的tdc校准值
 ******************************************************************************/
uint32_t MEASURE_GetAutoDtofValue(const MeasureTdcCal_StateTypeDef *cal,uint32_t hit_count,uint32_t filter_count)
{
	uint32_t end_f,end_b,tof_f,tof_b;
	int sum_soft = 0,dtof = 0,sum_f,sum_b;//sum = 0;
	uint32_t tmp = 0,reg = 0;
	tmp = READ_REG(PMU->AUTO_CALC);
	reg = LS_REXT(tmp,MEASURE_CALC);
	if(reg)
	{
		sum_soft = readw(TdcRes);
		LS_WREG(0x0,CMem_RAM,TdcRes);//reset
		if(sum_soft != 0x0)
		{
			dtof  =  sum_soft/(hit_count  - 2*filter_count );
		}
		return dtof;
	}else{
		return dtofcalc(hit_count, filter_count);

	}
}

/******************************************************************************
 *Function Name：	 MEASURE_GetDtofConvertPsValue
 *Brief：get dtof  ps value that unit is ps .
 *Param：
 *		 avg_dtof: dtof of ultrasonic.
 *		 time_Unit: time unit ;
 *Return value：
 *
 *		the time that actually ultrasonic fly through pipe.
 *Remarks：
 *		 输入的前后方向的超声波飞行时间差值
 ******************************************************************************/
uint32_t MEASURE_GetDtofConvertPsValue(uint32_t avg_dtof,uint32_t time_Unit)
{
	return tdc1517_2ps(avg_dtof, time_Unit);
}

/******************************************************************************
 *Function Name：	 MEASURE_GetManualDtofValue
 *Brief：get dtof value that product by user calculate .
 *Param：
 *		 hit_count:the number of hit stop.
 *		 filter_count: the number for filter to reduce abnormal data reference
 *		 autocalc register's fltRate ;
 *Return value：
 *
 *		the average difference between forward time and backward time.
 *Remarks：
 *
 ******************************************************************************/
int MEASURE_GetManualDtofValue(const MeasureTdcCal_StateTypeDef *tdc_cal,uint32_t hit_count,uint32_t filter_count)
{
#if 0  //初始版本
	MeasureTdcCal_StateTypeDef cal;
	int hit_filter = (hit_count - 2 * filter_count);

	if(MEASURE_GetTdcCal(&cal) != SUCCESS)
	{
		printf("tdc cal get error \n");
	}
	MEASURE_WriteTdcCalToReg(&cal);
	uint32_t start_f = tdc2time(StsFwd, cal.ForwardCal_C);
	uint32_t start_b = tdc2time(StsBwd, cal.BackwardCal_C);
	uint32_t end_f,end_b,tof_f,tof_b;
	int tmp,sum_soft = 0,dtof,sum_f,sum_b;//sum = 0;
	fltr();/* 进行滤波  */
	for(tmp = 0;tmp < hit_count;tmp++)
	{
		 end_f = tdc2time((ResFwd + tmp*4),cal.ForwardCal_C);
		 end_b = tdc2time((ResBwd + tmp*4),cal.BackwardCal_C);
		 tof_f = end_f - start_f;
		 tof_b = end_b - start_b;
		 dtof = tof_b - tof_f;
		if (iabs(dtof) > 0xaae60)
		{
			printf("first wave is error. \r\n");
			return ERROR;
		}
		//printf("\r\ndtof[%d]=%d", tmp+1, dtof);
		//sum_soft += dtof;
		sum_soft = sfa(tof_b, tof_f);
	}
	tmp = sum_soft/hit_filter;
	//tmp = sum_soft/hit_filter;
#endif

#if	0   //葛博士算法升级前版本
	uint32_t tdc_avg_c =  (cal->ForwardCal_C + cal->BackwardCal_C)>>1;
	uint32_t end_f,end_b;
	int tmp,sum_soft = 0;
	fltr();/* 进行滤波  */
	for(tmp = 0;tmp < hit_count;tmp++)
	{
		 end_f = tdc2time((ResFwd + tmp*4),tdc_avg_c);
		 end_b = tdc2time((ResBwd + tmp*4),tdc_avg_c);
		 sum_soft = sfa(end_b, end_f);
		// printf("\r\n[%d]=%d", tmp+1, tdc1517_2ps((end_b-end_f),125000) );
	}
	//tmp = (hit_count - 2*filter_count);
	//sum_soft /= tmp;
	sum_soft >>=3;
	//printf("\r\dtof=%d",sum_soft);
//	asm volatile("nop;\n");

#endif


	uint32_t end_f,end_b,start_f,start_b;
	int tmp,sum_soft = 0;

	fltr();/* 进行滤波  */
	start_f = tdc2time(StsFwd, tdc_cal->ForwardCal_C);
	start_b = tdc2time(StsBwd, tdc_cal->BackwardCal_C);

	for(tmp = 0;tmp < hit_count;tmp++)
	{
		 end_f = tdc2time((ResFwd + tmp*4),tdc_cal->ForwardCal_C);
		 end_b = tdc2time((ResBwd + tmp*4),tdc_cal->BackwardCal_C);
		 end_f = end_f - start_f;                 //tof_f
		 end_b = end_b - start_b;                 //tof_b
		 sum_soft = sfa(end_b, end_f);
		// printf("\r\n[%d]=%d", tmp+1, tdc1517_2ps((end_b-end_f),125000) );
	}
	//tmp = (hit_count - 2*filter_count);
	//sum_soft /= tmp;
	sum_soft >>=3;
	//printf("\r\dtof=%d",sum_soft);
//	asm volatile("nop;\n");

	return sum_soft;
}

/******************************************************************************
 *Function Name：	 MEASURE_ExpectResPtr
 *Brief： checkout the data which product by chip whether right.
 *Param：
 *		 res_fwd: forward data  result register.
 *		 res_bwd: backward data result register.
 *		 sts_fwd: forward state  result register.
 *		 sts_bwd: backward state result register.
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *		此函数只能应用于sonar模块不自动掉电模式，自动掉电模式不适用
 ******************************************************************************/
ErrorStatus MEASURE_ExpectResPtr(void)
{

	uint32_t tmp = MEASURE_GetResPtrReg();
	uint32_t hit_number = MEASURE_GetPulseWaveHitNum();
	uint32_t state_number = 1;

	if (tmp >> 31){
        //printf("timeout %x\n",tmp);
        return ERROR;
    }
	if(MEASURE_GetTdcAutoCalPre() == SET)
	{
		state_number +=2;
//		printf("tdc calpre\r\n");
		if(MEASURE_GetPulseWaveWideMode() == SET )
		{
			state_number+=2;
//			printf("tdc pulse wide\r\n");
			if(MEASURE_GetTdcAutoCalPst() == SET)
			{
//				printf("tdc cal pst\r\n");
				state_number += 2;
			}
		}
	}else if(MEASURE_GetPulseWaveWideMode() == SET )
	{
		state_number+=2;
//		printf("tdc pulse wide\r\n");
		if(MEASURE_GetTdcAutoCalPst() == SET)
		{
//			printf("tdc cal pst\r\n");
			state_number += 2;
		}
	}else if(MEASURE_GetTdcAutoCalPst() == SET)
	{
//		printf("tdc cal pst\r\n");
		state_number += 2;
	}


    if ((tmp& 0xFF) == hit_number &&
    	((tmp >> 8)& 0xFF) == hit_number &&
		((tmp >> 16)& 0xFF) == state_number &&
		((tmp >> 24)& 0xFF) == state_number){

    	return SUCCESS;

    }else {
        printf("resptr = %x\n", tmp);
        printf("expect   %x\n", (state_number<<24)|(state_number<<16)|(hit_number<<8)|hit_number);
        return ERROR;
    }

}

/******************************************************************************
 *Function Name：	 MEASURE_SetCruiseMode
 *Brief： set sonar measure cruise mode type .
 *Param：
 *		 mode  :the mode of cruise to measure;
 *		        the value reference  as follow remarks.
 *Return value：
 *		 none
 *Remarks：
 *	     MEASURE_CRUISE_MODE_CLOSE  		： 0
 *	     MEASURE_CRUISE_MODE_TOF   			： 1
 *	     MEASURE_CRUISE_MODE_TEMP		 	: 2
 *		 MEASURE_CRUISE_MODE_TOF_TEMP 		: 3
 ******************************************************************************/
void MEASURE_SetCruiseMode(uint32_t mode)
{
	uint32_t tmp = READ_REG(PMU->COMMAND);
	LS_RINS(tmp,MEASURE_CRUISE_MODE,mode);
	WRITE_REG(PMU->COMMAND,tmp);
}
/******************************************************************************
 *Function Name：	 MEASURE_SetWatchDog
 *Brief： set sonar watch dog to work or not.
 *Param：
 *		 state: a flag that defined by FunctionalState structure.
 *Return value：
 *
 *		none
 *Remarks：
 *	     enable  ：测量期间使能看门狗
 *	     disable ：测量期间不使能看门狗
 ******************************************************************************/
void MEASURE_SetWatchDog(FunctionalState state)
{
	uint32_t tmp = READ_REG(PMU->COMMAND);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_CRUISE_WATCH_DOG,MEASURE_CRUISE_WATCH_DOG_ENABLE):\
			LS_RINS(tmp,MEASURE_CRUISE_WATCH_DOG,MEASURE_CRUISE_WATCH_DOG_DISABLE);

	WRITE_REG(PMU->COMMAND,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetCruiseXMode
 *Brief： set sonar measure to use super speed mode or not.
 *Param：
 *		 state: a flag that defined by FunctionalState structure.
 *Return value：
 *
 *		none
 *Remarks：
 *	     enable  ：测量快速模式使能
 *	     disable ：测量快速模式不使能
 ******************************************************************************/
void MEASURE_SetCruiseXMode(FunctionalState state)
{
	uint32_t tmp = READ_REG(PMU->TIMING);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_CRUISE_X,MEASURE_CRUISE_X_ENABLE):\
			LS_RINS(tmp,MEASURE_CRUISE_X,MEASURE_CRUISE_X_DISABLE);

	WRITE_REG(PMU->TIMING,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetCruiseTOF
 *Brief： set sonar measure cruise tof value .
 *Param：
 *		 time  :the time between first forward(forward) and  second forward(backward);
 *		        the value reference  as follow remarks.
 *Return value：
 *		 none
 *Remarks：
 *	     MEASURE_CRUISE_TOF_0dot25s  ： 0.25s
 *	     MEASURE_CRUISE_TOF_0dot5s   ：0.5s
 *	     MEASURE_CRUISE_TOF_1s		 :1s
 *		 MEASURE_CRUISE_TOF_2s 		 :2s
 ******************************************************************************/
void MEASURE_SetCruiseTOF(uint32_t time)
{
	uint32_t tmp = READ_REG(PMU->TIMING);
	assert_param(IS_MEASURE_CRUISE_TOF(time));
	LS_RINS(tmp,MEASURE_CRUISE_TOF,time);
	WRITE_REG(PMU->TIMING,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetCruiseAutoDirection
 *Brief： set sonar measure  direction is automatically tuned or not.
 *Param：
 *		 state: a flag that defined by FunctionalState structure.
 *Return value：
 *
 *		none
 *Remarks：
 *	     enable  ：测量模式下使能自动对调方向
 *	     disable ：测量模式下不使能自动对调方向
 ******************************************************************************/
void MEASURE_SetCruiseAutoDirection(FunctionalState state)
{
	uint32_t tmp = READ_REG(PMU->TIMING);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_CRUISE_AUTO_DIR,MEASURE_CRUISE_AUTO_DIR_ENABLE):\
			LS_RINS(tmp,MEASURE_CRUISE_AUTO_DIR,MEASURE_CRUISE_AUTO_DIR_DISABLE);
	WRITE_REG(PMU->TIMING,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetFireSel
 *Brief：Set the  fire  channel；
 *Param：
 *		 channel： fire1 or fire2
 *Return value：
 *
 *		none
 *Remarks：
 *	    用于设置fire输入的选择通道设置
 ******************************************************************************/
void  MEASURE_SetFireSel(uint32_t channal)
{
	uint32_t tmp = READ_REG(SONAR->PULSE_DEF);

	LS_RINS(tmp,MEASURE_FIRE_SEL,channal);

	WRITE_REG(SONAR->PULSE_DEF,tmp);

}

/******************************************************************************
 *Function Name：	 MEASURE_SetPulseWaveFireNum
 *Brief：Set the fire waveform  number.
 *Param：
 *		 count: a value that use for to appoint the number of pulse to transmit .
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     count ：门限值范围1~127
 ******************************************************************************/
ErrorStatus  MEASURE_SetPulseWaveFireNum(uint32_t count)
{
	if(count > 127){

		//printf("hit num is beyond range 32!\r\n");
		return ERROR;
	}

	uint32_t tmp = READ_REG(SONAR->PULSE_DEF);

	LS_RINS(tmp,MEASURE_FIRE_NUM,count);

	WRITE_REG(SONAR->PULSE_DEF,tmp);

	return SUCCESS;
}
/******************************************************************************
 *Function Name：	 MEASURE_SetStopSel
 *Brief：Set the  stop  channel；
 *Param：
 *		 channel： stop1 or stop2
 *Return value：
 *
 *		none
 *Remarks：
 *	    用于设置stop输入的选择通道设置
 ******************************************************************************/
void  MEASURE_SetStopSel(uint32_t channel)
{
	uint32_t tmp = READ_REG(SONAR->PULSE_DEF);

	LS_RINS(tmp,MEASURE_STOP_SEL,channel);

	WRITE_REG(SONAR->PULSE_DEF,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetMannualDirectionReverse
 *Brief：Set the fire and stop  channel reverse to make sonar direction reverse.
 *Param：
 *		 none
 *Return value：
 *
 *		none
 *Remarks：
 *	     手动将发送和接收的方向调转主要用于非巡航模式下的信号方向逆转
 ******************************************************************************/
void  MEASURE_SetMannualDirectionReverse(void)
{
	uint32_t tmp = READ_REG(SONAR->PULSE_DEF);

	uint8_t fire_select = LS_REXT(tmp,MEASURE_FIRE_SEL);
	uint8_t stop_select = LS_REXT(tmp,MEASURE_STOP_SEL);

	LS_RINS(tmp,MEASURE_FIRE_SEL,(1 - fire_select));
	LS_RINS(tmp,MEASURE_FIRE_SEL,(1 - stop_select));

	WRITE_REG(SONAR->PULSE_DEF,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetPulseWavePeakMode
 *Brief：Set the waveform pulse peak measurement mode or not
 *Param：
 *		 state: a flag that defined by FunctionalState structure.
 *Return value：
 *
 *		none
 *Remarks：
 *	     enable  ：设置波形脉冲峰值测量模式
 *	     disable ：不设置波形脉冲峰值测量模式
 ******************************************************************************/
void MEASURE_SetPulseWavePeakMode(FunctionalState state)
{
	uint32_t tmp = READ_REG(SONAR->FWAVE_CTRL);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_FWAVECTRL_WAVEP,MEASURE_FWAVECTRL_WAVEP_ENABLE):\
			LS_RINS(tmp,MEASURE_FWAVECTRL_WAVEP,MEASURE_FWAVECTRL_WAVEP_DISABLE);
	WRITE_REG(SONAR->FWAVE_CTRL,tmp);

}

/******************************************************************************
 *Function Name：	 MEASURE_GetPulseWavePeakMode
 *Brief：Get the waveform pulse peak measurement mode
 *Param：
 *		 none
 *Return value：
 *		state: a flag that defined by FlagStatus structure reference remarks.
 *
 *Remarks：
 *	     set  ：设置波形脉冲峰值测量模式
 *	     reset ：不设置波形脉冲峰值测量模式
 ******************************************************************************/
FlagStatus MEASURE_GetPulseWavePeakMode(void)
{
	FlagStatus state = RESET;
	uint32_t reg =0;
	reg = READ_REG(SONAR->FWAVE_CTRL);
	reg = LS_REXT(reg,MEASURE_FWAVECTRL_WAVEP);
	state = (reg != 0)? SET : RESET;
	return state;
}

/******************************************************************************
 *Function Name：	 MEASURE_SetPulseWaveWideMode
 *Brief：Set the waveform pulse width measurement mode or not
 *Param：
 *		 state: a flag that defined by FunctionalState structure.
 *Return value：
 *
 *		none
 *Remarks：
 *	     enable  ：设置波形脉冲宽度测量模式
 *	     disable ：不设置波形脉冲宽度测量模式
 ******************************************************************************/
void MEASURE_SetPulseWaveWideMode(FunctionalState state)
{
	uint32_t tmp = READ_REG(SONAR->FWAVE_CTRL);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_FWAVECTRL_WAVEW,MEASURE_FWAVECTRL_WAVEW_ENABLE):\
			LS_RINS(tmp,MEASURE_FWAVECTRL_WAVEW,MEASURE_FWAVECTRL_WAVEW_DISABLE);
	WRITE_REG(SONAR->FWAVE_CTRL,tmp);

}

/******************************************************************************
 *Function Name：	 MEASURE_GetPulseWaveWideMode
 *Brief：Get the waveform pulse width measurement mode
 *Param：
 *		 none
 *Return value：
 *		state: a flag that defined by FlagStatus structure by reference remarks.
 *
 *Remarks：
 *	     set  ：设置波形脉冲宽度测量模式
 *	     reset ：不设置波形脉冲宽度测量模式
 ******************************************************************************/
FlagStatus MEASURE_GetPulseWaveWideMode(void)
{
	FlagStatus state = RESET;
	uint32_t reg =0;
	reg = READ_REG(SONAR->FWAVE_CTRL);
	reg = LS_REXT(reg,MEASURE_FWAVECTRL_WAVEW);
	state = (reg != 0)? SET : RESET;
	return state;
}

/******************************************************************************
 *Function Name：	 MEASURE_SetPulseWaveWideMode
 *Brief：Set the waveform wave measurement first wave mode or not
 *Param：
 *		 state: a flag that defined by FunctionalState structure.
 *Return value：
 *
 *		none
 *Remarks：
 *	     enable  ：设置波形脉冲测量首波模式
 *	     disable ：不设置波形脉冲测量首波模式
 ******************************************************************************/
void MEASURE_SetFirstPulseWaveMode(FunctionalState state)
{
	uint32_t tmp = READ_REG(SONAR->FWAVE_CTRL);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_FWAVECTRL_AUTOFW,MEASURE_FWAVECTRL_AUTOFW_ENABLE):\
			LS_RINS(tmp,MEASURE_FWAVECTRL_AUTOFW,MEASURE_FWAVECTRL_AUTOFW_DISABLE);
	WRITE_REG(SONAR->FWAVE_CTRL,tmp);
}


/******************************************************************************
 *Function Name：	 MEASURE_SetPulseFirstWaveThreshold
 *Brief：Set the waveform pulse first-wave measurement threshold
 *Param：
 *		 threshold: a value that use for to detect first-wave.
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     threshold ：门限值范围0~1024
 ******************************************************************************/
ErrorStatus  MEASURE_SetPulseFirstWaveThreshold(uint32_t threshold)
{

	if(threshold > 1023){

		//printf("threshold is beyond range 1023!\r\n");
		return ERROR;
	}

	uint32_t tmp = READ_REG(SONAR->FWAVE_CTRL);

	LS_RINS(tmp,MEASURE_FWAVECTRL_FHL,threshold);

	WRITE_REG(SONAR->FWAVE_CTRL,tmp);

	return SUCCESS;
}


/******************************************************************************
 *Function Name：	 MEASURE_SetPulseWaveHitNum
 *Brief：Set the received waveform hit value
 *Param：
 *		 count: a value that use for to appoint the number of pulse to receive .
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     count ：门限值范围1~32
 ******************************************************************************/
ErrorStatus  MEASURE_SetPulseWaveHitNum(uint32_t count)
{
	if(count > 32){

		//printf("hit num is beyond range 32!\r\n");
		return ERROR;
	}

	uint32_t tmp = READ_REG(SONAR->SONAR_CTRL);

	LS_RINS(tmp,MEASURE_HIT_IN,count);

	WRITE_REG(SONAR->SONAR_CTRL,tmp);

	return SUCCESS;
}

uint32_t MEASURE_GetPulseWaveHitNum(void)
{

	uint32_t reg =0;
	reg = READ_REG(SONAR->SONAR_CTRL);
	reg = LS_REXT(reg,MEASURE_HIT_IN);

	return reg;
}


/******************************************************************************
 *Function Name：	 MEASURE_SetPulseWaveTailEnd
 *Brief：Set the transmit waveform pull down zero time.
 *Param：
 *		 count: a value that use for to appoint the time that pull down the waveform. .
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     count ：以发波周期为单位，零点为第一个波，范围 1 ~ 127;
 *	           要求大于fire number 小于  waitend
 ******************************************************************************/
ErrorStatus  MEASURE_SetPulseWaveTailEnd(uint32_t count)
{
	if((count > 127)&&(count <1)){

		//printf("tail end time is beyond range!\r\n");
		return ERROR;
	}

	uint32_t tmp = READ_REG(SONAR->SONAR_CTRL);

	LS_RINS(tmp,MEASURE_TAIL_END,count);

	WRITE_REG(SONAR->SONAR_CTRL,tmp);

	return SUCCESS;
}

/******************************************************************************
 *Function Name：	 MEASURE_SetPulseWaveTailEnd
 *Brief：Set the transmit waveform wait to end time.
 *Param：
 *		 count: a value that use for to appoint the time that end the waveform. .
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     count ：以发波周期为单位，零点为第一个波，范围 1 ~ 256;
 *	           要求大于tail end 周期数；
 ******************************************************************************/
ErrorStatus  MEASURE_SetPulseWaveWaitEnd(uint32_t count)
{
	if((count > 256)&&(count <1)){

		//printf("tail end time is beyond range!\r\n");
		return ERROR;
	}

	uint32_t tmp = READ_REG(SONAR->SONAR_CTRL);

	LS_RINS(tmp,MEASURE_WAIT_END,count);

	WRITE_REG(SONAR->SONAR_CTRL,tmp);

	return SUCCESS;
}


/******************************************************************************
 *Function Name：	 MEASURE_SetPulseWaveHitIgnNum
 *Brief：Set the receive waveform hit ignore value
 *Param：
 *		 count: a value that use for to ignore the number of pulse to receive .
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     count ：门限值范围1~3,用于tdc处理hit值速率不足时，等间隔忽略
 ******************************************************************************/
ErrorStatus  MEASURE_SetPulseWaveHitIgnNum(uint32_t count)
{
	if(count > 3){

		//printf("hit ign num is beyond range 3!\r\n");
		return ERROR;
	}

	uint32_t tmp = READ_REG(SONAR->SONAR_CTRL);

	LS_RINS(tmp,MEASURE_HIT_IGN,count);

	WRITE_REG(SONAR->SONAR_CTRL,tmp);

	return SUCCESS;
}

/******************************************************************************
 *Function Name：	 MEASURE_SetAutoCalculateMode
 *Brief：Set the waveform wave measurement first wave mode or not
 *Param：
 *		 state: a flag that defined by FunctionalState structure.
 *Return value：
 *
 *		none
 *Remarks：
 *	     enable  ：使能自动计算模式
 *	     disable ：不使能自动计算模式
 ******************************************************************************/
void  MEASURE_SetAutoCalculateMode(FunctionalState state)
{
	uint32_t tmp = READ_REG(PMU->AUTO_CALC);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_CALC,MEASURE_CALC_ENABLE):\
			LS_RINS(tmp,MEASURE_CALC,MEASURE_CALC_DISABLE);
	WRITE_REG(PMU->AUTO_CALC,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetAutoCalculateHitNum
 *Brief：Set the auto-calculate hit value
 *Param：
 *		 count: a value that use for to appoint the number of pulse to auto-calculate .
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     count ：门限值范围1~31
 ******************************************************************************/
ErrorStatus  MEASURE_SetAutoCalculateHitNum(uint32_t count)
{
	if(count > 31){

		//printf("hit num is beyond range 32!\r\n");
		return ERROR;
	}
	uint32_t tmp = READ_REG(PMU->AUTO_CALC);

	LS_RINS(tmp,MEASURE_HIT_NUM,count);

	WRITE_REG(PMU->AUTO_CALC,tmp);

	return SUCCESS;
}

/******************************************************************************
 *Function Name：	 MEASURE_SetAutoCalculateFItRate
 *Brief：Set the auto-calculate hit value
 *Param：
 *		 count: a value that use for to appoint the number of pulse to auto-calculate .
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     count ：门限值范围0~3
 ******************************************************************************/
ErrorStatus  MEASURE_SetAutoCalculateFltRate(uint32_t count)
{
	if(count > 3){

		//printf("hit num is beyond range 32!\r\n");
		return ERROR;
	}
	uint32_t tmp = READ_REG(PMU->AUTO_CALC);

	LS_RINS(tmp,MEASURE_FLT_RATE,count);

	WRITE_REG(PMU->AUTO_CALC,tmp);

	return SUCCESS;
}

/******************************************************************************
 *Function Name：	 MEASURE_SetTdcAutoCalPre
 *Brief：Set up the tdc auto-pre-calibration
 *Param：
 *		 state: a flag that defined by FunctionalState structure.
 *Return value：
 *
 *		none
 *Remarks：
 *	     enable  ：设置tdc自动前校准
 *	     disable ：不设置tdc自动前校准
 ******************************************************************************/
void MEASURE_SetTdcAutoCalPre(FunctionalState state)
{
	uint32_t tmp = READ_REG(SONAR->SONAR_CTRL);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_AUTO_CAL_PRE,MEASURE_AUTO_CAL_PRE_ENABLE):\
			LS_RINS(tmp,MEASURE_AUTO_CAL_PRE,MEASURE_AUTO_CAL_PRE_DISABLE);
	WRITE_REG(SONAR->SONAR_CTRL,tmp);

}

/******************************************************************************
 *Function Name：	 MEASURE_SetTdcAutoCalPst
 *Brief：Set up the tdc auto-pst-calibration
 *Param：
 *		 state: a flag that defined by FunctionalState structure.
 *Return value：
 *
 *		none
 *Remarks：
 *	     enable  ：设置tdc自动后校准
 *	     disable ：不设置tdc自动后校准
 ******************************************************************************/
void MEASURE_SetTdcAutoCalPst(FunctionalState state)
{
	uint32_t tmp = READ_REG(SONAR->SONAR_CTRL);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_AUTO_CAL_PST,MEASURE_AUTO_CAL_PST_ENABLE):\
			LS_RINS(tmp,MEASURE_AUTO_CAL_PST,MEASURE_AUTO_CAL_PST_DISABLE);
	WRITE_REG(SONAR->SONAR_CTRL,tmp);
}


/******************************************************************************
 *Function Name：	 MEASURE_GetTdcAutoCalPre
 *Brief：Set up the tdc auto-pre-calibration state
 *Param：
 *		none
 *Return value：
 *		state: a flag that defined by FlagStatus structure.
 *
 *Remarks：
 *	     set  ：设置tdc自动后校准
 *	     reset ：不设置tdc自动后校准
 ******************************************************************************/
FlagStatus MEASURE_GetTdcAutoCalPre(void)
{
	FlagStatus state = RESET;
	uint32_t reg =0;
	reg = READ_REG(SONAR->SONAR_CTRL);
	reg = LS_REXT(reg,MEASURE_AUTO_CAL_PRE);
	state = (reg != 0)? SET : RESET;
	return state;
}

/******************************************************************************
 *Function Name：	 MEASURE_GetTdcAutoCalPst
 *Brief：Get the tdc auto-pst-calibration state.
 *Param：
 *		 none
 *Return value：
 *		state: a flag that defined by FlagStatus structure.
 *
 *Remarks：
 *	     SET  ：设置tdc自动后校准
 *	     RESET ：不设置tdc自动后校准
 ******************************************************************************/
FlagStatus MEASURE_GetTdcAutoCalPst(void)
{
	FlagStatus state = RESET;
	uint32_t reg =0;
	reg = READ_REG(SONAR->SONAR_CTRL);
	reg = LS_REXT(reg,MEASURE_AUTO_CAL_PST);
	state = (reg != 0)? SET : RESET;
	return state;
}

#if 0
/******************************************************************************
 *Function Name：	 MEASURE_SetTdcOpt
 *Brief：Set up the tdc configure option byte
 *Param：
 *		 option: a flag that defined for different work mode for tdc.
 *Return value：
 *
 *		none
 *Remarks：
 *
 *		时差测量默认 option = MEASURE_TDC_OPT_PDEN | MEASURE_TDC_OPT_PDAUTO;
 ******************************************************************************/
void MEASURE_SetTdcOpt(uint32_t option)
{
	uint32_t tmp = READ_REG(SONAR->TDC_CTRL1);
	LS_RINS(tmp,MEASURE_TDC_OPT,option);
	WRITE_REG(SONAR->TDC_CTRL1,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetTdcDbgRemapMode
 *Brief：Set dbg remap mode ,when enable the mode the emp_i and emp_o remap to dbg0 and dbg1;
 *Param：
 *		 state:
 *		       enable
 *		       disable
 *Return value：
 *
 *		none
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_SetTdcDbgRemapMode(FunctionalState state)
{
	uint32_t tmp = READ_REG(CHIPCTRL);
	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_DBG_REMAP,MEASURE_DBG_REMAP_ENABLE):\
			LS_RINS(tmp,MEASURE_DBG_REMAP,MEASURE_DBG_REMAP_DISABLE);
	WRITE_REG(CHIPCTRL,tmp);
}
/******************************************************************************
 *Function Name：	 MEASURE_SetTdcDbg1Mode
 *Brief：Set up the tdc dbg1  work mode
 *Param：
 *		 mode: a mode that defined for different work mode for DBG1.
 *Return value：
 *
 *		none
 *Remarks：
 *
 *		 work mode :
 *		     MEASURE_DBG1_SEL_STOP	 		   			((uint16_t)0)
 * 			 MEASURE_DBG1_SEL_COMPARE	    			((uint16_t)1)
 * 			 MEASURE_DBG1_SEL_TDC	    				((uint16_t)2)
 * 			 MEASURE_DBG1_SEL_LDSENSET	    			((uint16_t)3)
 *
 ******************************************************************************/
void MEASURE_SetTdcDbg1Mode(uint32_t mode)
{
	uint32_t tmp = READ_REG(SONAR->TDC_CTRL1);
	LS_RINS(tmp,MEASURE_DBG1_SEL,mode);
	WRITE_REG(SONAR->TDC_CTRL1,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetTdcDbg0Mode
 *Brief：Set up the tdc dbg0  work mode
 *Param：
 *		 mode: a mode that defined for different work mode for DBG0.
 *Return value：
 *
 *		none
 *Remarks：
 *		调试输出DBG0 选择work mode :
 *
 *		     MEASURE_DBG0_SEL_START	 		   			((uint16_t)0)
 * 			 MEASURE_DBG0_SEL_STOP	    				((uint16_t)1)
 * 			 MEASURE_DBG0_SEL_COMPARE	    			((uint16_t)2)
 * 			 MEASURE_DBG0_SEL_TDC	    				((uint16_t)3)
 *
 ******************************************************************************/
void MEASURE_SetTdcDbg0Mode(uint32_t mode)
{
	uint32_t tmp = READ_REG(SONAR->TDC_CTRL1);
	LS_RINS(tmp,MEASURE_DBG0_SEL,mode);
	WRITE_REG(SONAR->TDC_CTRL1,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetTdcPreDelayIncrement
 *Brief：Set the tdc pre-delay value to self-increment
 *Param：
 *		 inc: a value that use for to self-increment.
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     inc ：预延迟自增量范围0~3
 ******************************************************************************/
ErrorStatus MEASURE_SetTdcPreDelayIncrement(uint32 inc)
{
	if(inc > 3){

		//printf("PreDlyInc beyond range 3!\r\n");
		return ERROR;
	}

	uint32_t tmp = READ_REG(SONAR->TDC_CTRL2);

	LS_RINS(tmp,MEASURE_TDC_PRE_DLY_INC,inc);

	WRITE_REG(SONAR->TDC_CTRL2,tmp);

	return SUCCESS;
}

#endif
/******************************************************************************
 *Function Name：	 MEASURE_SetAfeVtestSel
 *Brief：Set the tdc pre-delay value to self-increment
 *Param：
 *		 channel: a channel that measure amc ad select.the value for example:
 *		 MEASURE_AFECTRL_VTEST_SEL_VREF
 *		 MEASURE_AFECTRL_VTEST_SEL_DAC_AMC
 *Return value：
 *
 *		none
 *Remarks：
 *
 *	     channel ：0~1
 ******************************************************************************/
void MEASURE_SetAfeVtestSel(uint32_t channel)
{
	uint32_t tmp = READ_REG(SONAR->AFE_CTRL);

	LS_RINS(tmp,MEASURE_AFECTRL_VTEST_SEL,channel);

	WRITE_REG(SONAR->AFE_CTRL,tmp);

}

/******************************************************************************
 *Function Name：	 MEASURE_SetAfeVtestDual
 *Brief：Set the afe register vtestdual enable or not.
 *Param：
 *		  state: a flag that defined by FunctionalState structure.
 *				Enable
 *				Disable
 *Return value：
 *
 *		none
 *Remarks：
 *
 ******************************************************************************/
void MEASURE_SetAfeVtestDual(FunctionalState state)
{
	uint32_t tmp = READ_REG(SONAR->AFE_CTRL);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_AFECTRL_VTEST_DUAL,MEASURE_AFECTRL_VTEST_DUAL_ENABLE):\
			LS_RINS(tmp,MEASURE_AFECTRL_VTEST_DUAL,MEASURE_AFECTRL_VTEST_DUAL_DISABLE);
	WRITE_REG(SONAR->AFE_CTRL,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetAfeVtest
 *Brief：Set the afe register vtest enable or not.
 *Param：
 *		  state: a flag that defined by FunctionalState structure.
 *				Enable
 *				Disable
 *Return value：
 *
 *		none
 *Remarks：
 *
 ******************************************************************************/
void MEASURE_SetAfeVtest(FunctionalState state)
{
	uint32_t tmp = READ_REG(SONAR->AFE_CTRL);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_AFECTRL_VTEST,MEASURE_AFECTRL_VTEST_ENABLE):\
			LS_RINS(tmp,MEASURE_AFECTRL_VTEST,MEASURE_AFECTRL_VTEST_DISABLE);
	WRITE_REG(SONAR->AFE_CTRL,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetAfeVtestOut
 *Brief：Set the afe register vtestout mode.
 *Param：
 *		 mode: a mode that vtest output select for example:
 *		 	MEASURE_AFECTRL_VTEST_OUT_CLOSE
 *		 	MEASURE_AFECTRL_VTEST_OUT_VCMP
 *		 	MEASURE_AFECTRL_VTEST_OUT_VAMC
 *		 	MEASURE_AFECTRL_VTEST_OUT_OTHER
 *Return value：
 *
 *		none
 *Remarks：
 *
 *	     channel ：0~1
 ******************************************************************************/
void MEASURE_SetAfeVtestOut(uint32_t mode)
{
	uint32_t tmp = READ_REG(SONAR->AFE_CTRL);

	LS_RINS(tmp,MEASURE_AFECTRL_VTEST_OUT,mode);

	WRITE_REG(SONAR->AFE_CTRL,tmp);

}

/******************************************************************************
 *Function Name：	 MEASURE_SetAfeVRefOut
 *Brief：Set the afe register vref output enable or not.
 *Param：
 *		 mode: a mode that vtest output select for example:
 *		 	MEASURE_AFECTRL_VREF_OUT_ZERO
 *		 	MEASURE_AFECTRL_VREF_OUT_VREF
 *Return value：
 *
 *		none
 *Remarks：
 *	    要不要将内部参考电压输出来
 ******************************************************************************/
void MEASURE_SetAfeVRefOut(FunctionalState state)
{
	uint32_t tmp = READ_REG(SONAR->AFE_CTRL);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_AFECTRL_VREF_OUT,MEASURE_AFECTRL_VREF_OUT_ENABLE):\
			LS_RINS(tmp,MEASURE_AFECTRL_VREF_OUT,MEASURE_AFECTRL_VREF_OUT_DISABLE);
	WRITE_REG(SONAR->AFE_CTRL,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetAfeVRefSel
 *Brief：Set the afe register vref output select option.
 *Param：
 *		 mode: a mode that vtest output select for example:
 *
 *		 	MEASURE_AFECTRL_VREF_SEL_0dot86V
 *		 	MEASURE_AFECTRL_VREF_SEL_1dot07V
 *Return value：
 *
 *		none
 *Remarks：
 *	    输入参数只可为0 或者 1，即：
 *	    MEASURE_AFECTRL_VREF_SEL_0dot86V -> 0
 *	    MEASURE_AFECTRL_VREF_SEL_1dot07V -> 1
 ******************************************************************************/
void MEASURE_SetAfeVRefSel(uint32_t mode)
{
	uint32_t tmp = READ_REG(SONAR->AFE_CTRL);

	LS_RINS(tmp,MEASURE_AFECTRL_VREF_SEL,mode);

	WRITE_REG(SONAR->AFE_CTRL,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetAfeVRefOut
 *Brief：Set the afe register vref output enable or not.
 *Param：
 *		 mode: a mode that vtest output select for example:
 *		 	MEASURE_AFECTRL_VREF_OUT_ZERO
 *		 	MEASURE_AFECTRL_VREF_OUT_VREF
 *Return value：
 *
 *		none
 *Remarks：
 *	    要不要将内部参考电压输出来
 ******************************************************************************/
void MEASURE_SetAfeVRef(FunctionalState state)
{
	uint32_t tmp = READ_REG(SONAR->AFE_CTRL);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_AFECTRL_VREF,MEASURE_AFECTRL_VREF_ENABLE):\
			LS_RINS(tmp,MEASURE_AFECTRL_VREF,MEASURE_AFECTRL_VREF_DISABLE);
	WRITE_REG(SONAR->AFE_CTRL,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetAfeVRefDrive
 *Brief：Set the afe register vref output drive select option.
 *Param：
 *		 mode: a mode that vtest output drive select for example:
 *
 *		 	MEASURE_AFECTRL_VREF_DRV_33OHM
 *		 	MEASURE_AFECTRL_VREF_DRV_50OHM
 *		 	MEASURE_AFECTRL_VREF_DRV_100OHM
 *Return value：
 *
 *		none
 *Remarks：
 *	    输入参数只可为0 或者 1，2 即：
 *	    MEASURE_AFECTRL_VREF_DRV_33OHM  -> 0
 *	    MEASURE_AFECTRL_VREF_DRV_50OHM  -> 1
 *	    MEASURE_AFECTRL_VREF_DRV_100OHM -> 2
 ******************************************************************************/
void MEASURE_SetAfeVRefDrive(uint32_t mode)
{
	uint32_t tmp = READ_REG(SONAR->AFE_CTRL);

	LS_RINS(tmp,MEASURE_AFECTRL_VREF_DRV,mode);

	WRITE_REG(SONAR->AFE_CTRL,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetTdcPreDelayValue
 *Brief：Set the tdc initializing pre-delay value
 *Param：
 *		 value: a value that use for to pre-delay.
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     value ：预延迟自增量范围0~1023
 ******************************************************************************/
ErrorStatus MEASURE_SetTdcPreDelayValue(uint32 value)
{
	if(value > 1023){

		//printf("PreDlyVal beyond range 1023!\r\n");
		return ERROR;
	}

	uint32_t tmp = READ_REG(SONAR->TDC_CTRL2);

	LS_RINS(tmp,MEASURE_TDC_PRE_DLY_VAL,value);

	WRITE_REG(SONAR->TDC_CTRL2,tmp);

	return SUCCESS;
}


/******************************************************************************
 *Function Name：	 MEASURE_GetCalibrationZeroValue
 *Brief：get the calibctrl reg zero-level value
 *Param：
 *		 value: a value that get from zero-level
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     value ：预延迟自增量范围0~1023
 ******************************************************************************/
uint32_t MEASURE_GetCalibrationZeroValue(void)
{

	uint32_t cal_value = 0;
	uint32_t tmp = READ_REG(SONAR->CALIB_CTRL);

	cal_value = LS_REXT(tmp,MEASURE_CALIBCTRL_ZEROLEVEL);

	return cal_value;
}


/******************************************************************************
 *Function Name：	 MEASURE_SetCalibrationZeroValue
 *Brief：Set  the calibctrl reg cal-zero value
 *Param：
 *		 value: a value that use for to  cal-zero
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     value ：预延迟自增量范围0~1023
 ******************************************************************************/
ErrorStatus MEASURE_SetCalibrationZeroValue(uint32 value)
{
	if(value > 1023){

		//printf("PreDlyVal beyond range 1023!\r\n");
		return ERROR;
	}

	uint32_t tmp = READ_REG(SONAR->CALIB_CTRL);

	LS_RINS(tmp,MEASURE_CALIBCTRL_CALZERO,value);

	WRITE_REG(SONAR->CALIB_CTRL,tmp);

	return SUCCESS;
}

/******************************************************************************
 *Function Name：	 MEASURE_SetCalBypass
 *Brief： set CalBypass to work or not.
 *Param：
 *		 state: a flag that defined by FunctionalState structure.
 *Return value：
 *
 *		none
 *Remarks：
 *	     enable  ：使能自动旁路校准
 *	     disable ：不使能自动旁路校准
 ******************************************************************************/
void  MEASURE_SetCalBypass(FunctionalState state)
{
	uint32_t tmp = READ_REG(SONAR->CALIB_CTRL);

	(state != DISABLE)?
			LS_RINS(tmp,MEASURE_CALIBCTRL_CALBYPASS,MEASURE_CALIBCTRL_CALBYPASS_ENABLE):\
			LS_RINS(tmp,MEASURE_CALIBCTRL_CALBYPASS,MEASURE_CALIBCTRL_CALBYPASS_DISABLE);

	WRITE_REG(SONAR->CALIB_CTRL,tmp);
}


/******************************************************************************
 *Function Name：	 MEASURE_SetCalibrationDelayValue
 *Brief：Set  the calibctrl reg cal-delay value
 *Param：
 *		 value: a value that use to  cal-delay
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     value ：预延迟自增量范围0~7
 ******************************************************************************/
ErrorStatus MEASURE_SetCalibrationDelayValue(uint32 value)
{
	if(value > 7){

		//printf("PreDlyVal beyond range 1023!\r\n");
		return ERROR;
	}

	uint32_t tmp = READ_REG(SONAR->CALIB_CTRL);

	LS_RINS(tmp,MEASURE_CALIBCTRL_CALDELAY,value);

	WRITE_REG(SONAR->CALIB_CTRL,tmp);

	return SUCCESS;
}

/******************************************************************************
 *Function Name：	 MEASURE_SetCalibrationMethod
 *Brief：Set  the calibctrl reg cal-Method value
 *Param：
 *		 value: a value that use to  cal-Method
 *Return value：
 *
 *		the state of function execute;
 *Remarks：
 *
 *	     value ：预延迟自增量范围0~1
 ******************************************************************************/
ErrorStatus MEASURE_SetCalibrationMethod(uint32 value)
{
	if(value > 1){

		//printf("PreDlyVal beyond range 1023!\r\n");
		return ERROR;
	}

	uint32_t tmp = READ_REG(SONAR->CALIB_CTRL);

	LS_RINS(tmp,MEASURE_CALIBCTRL_CALMETHOD,value);

	WRITE_REG(SONAR->CALIB_CTRL,tmp);

	return SUCCESS;
}

/******************************************************************************
 *Function Name：	 MEASURE_StartTask
 *Brief：Start task execution
 *Param：
 *		 none
 *Return value：
 *
 *		none
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_StartTask(void)
{
	//uint32_t tmp = 0;
	uint32_t tmp = READ_REG(PMU->COMMAND_W);

	LS_RINS(tmp,MEASURE_START_OPW,MEASURE_START_OPW_ENABLE);

	CLEAR_BIT(tmp,0X01);

	WRITE_REG(PMU->COMMAND_W,tmp);
}
/******************************************************************************
 *Function Name：	 MEASURE_SetTask
 *Brief：Set task mode
 *Param：
 *		 task:a different work mode by mop define
 *
 *Return value：
 *
 *		none
 *
 *Remarks：
 *		mop define reference egg:
 *		#define MEASURE_MOP_ONCE_TOF	    		((uint16_t)0)
 *		#define MEASURE_MOP_ONCE_TEMP				((uint16_t)1)
 *		#define MEASURE_MOP_TWICE_TOF	    		((uint16_t)2)
 *		#define MEASURE_MOP_TWICE_TEMP				((uint16_t)3)
 *		#define MEASURE_MOP_TDC						((uint16_t)4)
 *		#define MEASURE_MOP_HSE_CAL					((uint16_t)5)
 *		#define MEASURE_MOP_TRANSDUCERS				((uint16_t)6)
 *
 ******************************************************************************/
void MEASURE_SetTask(uint32_t task)
{
	uint32_t tmp = 0;
	tmp = READ_REG(PMU->COMMAND);
	LS_RINS(tmp,MEASURE_MOP,task);
	WRITE_REG(PMU->COMMAND,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetTaskToStart
 *Brief：Set task word mode and to Start it.
 *Param：
 *		  task:a different work mode by mop define,the value reference as follow:
 *		  	  MEASURE_MOP_ONCE_TOF
 *			  MEASURE_MOP_ONCE_TEMP
 *			  MEASURE_MOP_TWICE_TOF
 *			  MEASURE_MOP_TWICE_TEMP
 *			  MEASURE_MOP_TDC
 *			  MEASURE_MOP_HSE_CAL
 *			  MEASURE_MOP_TRANSDUCERS
 *Return value：
 *
 *		none
 *Remarks：
 *
 *	   这个函数集成了 MEASURE_SetTask()和 MEASURE_StartTask()两个函数的功能
 ******************************************************************************/
void MEASURE_SetTaskToStart(uint32_t task)
{
	uint32_t tmp = 0;
	assert_param(IS_MEASURE_MOP(task));

	/* clear resptr reg */
	MEASURE_ClearResPtrReg();

	/* read command data to insert task mode,then write back to command  */
	MEASURE_SetTask(task);

	/* wake up cpu to work */
	MEASURE_StartTask();

}


/******************************************************************************
 *Function Name：	 MEASURE_StopTask
 *Brief：Stop task execution
 *Param：
 *		 none
 *Return value：
 *
 *		none
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_StopTask(void)
{
	uint32_t tmp = 0;
	LS_RINS(tmp,MEASURE_START_OP,MEASURE_START_OP_DISABLE);
	WRITE_REG(PMU->COMMAND,tmp);
}


/******************************************************************************
 *Function Name：	 MEASURE_SuspendTask
 *Brief：Suspend task execution to wait
 *Param：
 *		 none
 *Return value：
 *
 *		none
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_SuspendTask(void)
{
	cpu_wait();
}

/******************************************************************************
 *Function Name：	 MEASURE_SleepTask
 *Brief：set measure mode to sleep;
 *Param：
 *		 none
 *Return value：
 *
 *		none
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_SleepTask(void)
{
	uint32_t tmp = 0;
	LS_RINS(tmp,MEASURE_SLEEPW,MEASURE_SLEEPW_ENABLE);
	WRITE_REG(PMU->COMMAND_W,tmp);
}

void MEASURE_ExitCruiseTask(void)
{
	uint32_t tmp = 0;
	LS_RINS(tmp,MEASURE_CRUISE_MODE,MEASURE_CRUISE_MODE_CLOSE);
	WRITE_REG(PMU->COMMAND,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_CanCpuSleep
 *Brief：check cpu whether can sleep?
 *Param：
 *		 none
 *Return value：
 *
 *		none
 *Remarks：
 *
 *
 ******************************************************************************/
FlagStatus MEASURE_CanCpuSleep(void)
{
	FlagStatus state = RESET;
	uint32_t tmp = 0;
	tmp = READ_REG(PMU->COMMAND_W);
	state = LS_REXT(tmp,MEASURE_SLEEPW);
	return state;
}

/******************************************************************************
 *Function Name：	 MEASURE_GetITStatus
 *Brief：check measure Interrupt whether happen?
 *Param：
 *		 MEASURE_IT_FLAG: the interrupt flag that reference:
 *						MEASURE_INT_WAKE				((uint16_t)1)
 *						MEASURE_INT_RES_READ			((uint16_t)2)
 *						MEASURE_INT_BAT_FAIL			((uint16_t)4)
 *						MEASURE_INT_C32K_FAIL			((uint16_t)8)
 *						MEASURE_INT_C8M_FAIL			((uint16_t)16)
 *						MEASURE_INT_KEY					((uint16_t)32)
 *						MEASURE_INT_RING				((uint16_t)64)
 *						MEASURE_INT_RTC					((uint16_t)128)
 *						MEASURE_INT_EXINT				((uint16_t)256)
 *
 *Return value：
 *				ITStatus :interrupt state
 *				RESET
 *				SET
 *Remarks：
 *      获取某一个中断的寄存器状态，不可将多个中断变量进行位或后再查询，只可以单独查询一个中断变量参数
 *      example：MEASURE_GetITStatus(MEASURE_INT_RES_READ);
 ******************************************************************************/
ITStatus MEASURE_GetITStatus(uint32_t MEASURE_IT_FLAG)
{
	ITStatus state = RESET ;
	uint32_t tmp = 0,reg = 0;
	assert_param(IS_MEASURE_INT_SRC_FLAG(MEASURE_IT_FLAG));
	tmp = READ_REG(PMU->COMMAND);

	switch(MEASURE_IT_FLAG)
	{
	case MEASURE_INT_WAKE:
		reg = LS_REXT(tmp,MEASURE_INT_WAKE);
		break;
	case MEASURE_INT_RES_READ:
		reg = LS_REXT(tmp,MEASURE_INT_RES_READ);
		break;
	case MEASURE_INT_BAT_FAIL:
		reg = LS_REXT(tmp,MEASURE_INT_BAT_FAIL);
		break;
	case MEASURE_INT_C32K_FAIL:
		reg = LS_REXT(tmp,MEASURE_INT_C32K_FAIL);
		break;
	case MEASURE_INT_C8M_FAIL:
		reg = LS_REXT(tmp,MEASURE_INT_C8M_FAIL);
		break;
	case MEASURE_INT_KEY:
		reg = LS_REXT(tmp,MEASURE_INT_KEY);
		break;
	case MEASURE_INT_RING:
		reg = LS_REXT(tmp,MEASURE_INT_RING);
		break;
	case MEASURE_INT_RTC:
		reg = LS_REXT(tmp,MEASURE_INT_RTC);
		break;
	case MEASURE_INT_EXINT:
		reg = LS_REXT(tmp,MEASURE_INT_EXINT);
		break;
	default:
		break;
	}
	state = (reg != 0)? SET : RESET;

	return state;
}

/******************************************************************************
 *Function Name：	 MEASURE_ITConfig
 *Brief：configure measure Interrupt Enable to happen or not.
 *Param：
 *		 MEASURE_IT_FLAG: the interrupt flag that reference:
 *						MEASURE_INT_WAKE				((uint16_t)1)
 *						MEASURE_INT_RES_READ			((uint16_t)2)
 *						MEASURE_INT_BAT_FAIL			((uint16_t)4)
 *						MEASURE_INT_C32K_FAIL			((uint16_t)8)
 *						MEASURE_INT_C8M_FAIL			((uint16_t)16)
 *						MEASURE_INT_KEY					((uint16_t)32)
 *						MEASURE_INT_RING				((uint16_t)64)
 *						MEASURE_INT_RTC					((uint16_t)128)
 *						MEASURE_INT_EXINT				((uint16_t)256)
 *
 *		FunctionalState NewState: the state for the interrupt source.
 *		                ENABLE
 *		                DISABLE
 *Return value：
 *				none
 *Remarks：
 *      对某一个或者几个不同的中断进行配置是否使能，可将多个中断变量进行位或，也可以单独对一个中断使用
 *      example：
 *      MEASURE_GetITStatus(MEASURE_INT_RES_READ,ENABLE);
 *      MEASURE_GetITStatus(MEASURE_INT_RES_READ|MEASURE_INT_WAKE,DISABLE);
 ******************************************************************************/
void MEASURE_ITConfig(uint32_t MEASURE_IT_FLAG,FunctionalState NewState)
{
	uint32_t tmp = 0;
	assert_param(IS_MEASURE_INT_EN_FLAG(MEASURE_IT_FLAG));

	tmp = READ_REG(PMU->COMMAND);

	if(NewState != DISABLE)
	{
		tmp |= LS_RMK(MEASURE_INT_EN,MEASURE_IT_FLAG);
	}
	else
	{
		tmp &= LS_RMK(MEASURE_INT_EN,(uint16_t)~MEASURE_IT_FLAG);
	}

	WRITE_REG(PMU->COMMAND,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_ClearIT
 *Brief：clear measure Interrupt state register.
 *Param：
 *		 MEASURE_IT_FLAG: the interrupt flag that reference:
 *						MEASURE_INT_WAKE				((uint16_t)1)
 *						MEASURE_INT_RES_READ			((uint16_t)2)
 *						MEASURE_INT_BAT_FAIL			((uint16_t)4)
 *						MEASURE_INT_C32K_FAIL			((uint16_t)8)
 *						MEASURE_INT_C8M_FAIL			((uint16_t)16)
 *						MEASURE_INT_KEY					((uint16_t)32)
 *						MEASURE_INT_RING				((uint16_t)64)
 *						MEASURE_INT_RTC					((uint16_t)128)
 *						MEASURE_INT_EXINT				((uint16_t)256)
 *
 *Return value：
 *				none
 *Remarks：
 *      对某一个或者几个不同的中断进行清楚状态，可将多个中断变量进行位或，也可以单独对一个中断使用
 *      example：
 *      MEASURE_ClearIT(MEASURE_INT_RES_READ,ENABLE);
 *      MEASURE_ClearIT(MEASURE_INT_RES_READ|MEASURE_INT_WAKE,DISABLE);
 ******************************************************************************/
void MEASURE_ClearIT(uint32_t MEASURE_IT_FLAG)
{
	uint32_t tmp = 0;
	assert_param(IS_MEASURE_INT_CLR_FLAG(MEASURE_IT_FLAG));
	//tmp = READ_REG(PMU->COMMAND_W);
	tmp = LS_RMK(MEASURE_INT_CLR,MEASURE_IT_FLAG);
	WRITE_REG(PMU->COMMAND_W,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_ClearITPendingBit
 *Brief：clear measure Interrupt state register bit.
 *Param：
 *		 MEASURE_IT_FLAG: the interrupt flag that reference:
 *						MEASURE_INT_WAKE				((uint16_t)1)
 *						MEASURE_INT_RES_READ			((uint16_t)2)
 *						MEASURE_INT_BAT_FAIL			((uint16_t)4)
 *						MEASURE_INT_C32K_FAIL			((uint16_t)8)
 *						MEASURE_INT_C8M_FAIL			((uint16_t)16)
 *						MEASURE_INT_KEY					((uint16_t)32)
 *						MEASURE_INT_RING				((uint16_t)64)
 *						MEASURE_INT_RTC					((uint16_t)128)
 *						MEASURE_INT_EXINT				((uint16_t)256)
 *
 *Return value：
 *				none
 *Remarks：
 *      对某一个中断状态寄存器进行清除
 *      example：
 *      MEASURE_ClearITPendingBit(MEASURE_INT_RES_READ);
 ******************************************************************************/
void MEASURE_ClearITPendingBit(uint32_t MEASURE_IT_FLAG)
{
	uint32_t tmp = 0;
	assert_param(IS_MEASURE_INT_CLR_FLAG(MEASURE_IT_FLAG));
	tmp = READ_REG(PMU->COMMAND_W);
	tmp |= LS_RMK(MEASURE_INT_CLR,MEASURE_IT_FLAG);
	WRITE_REG(PMU->COMMAND_W,tmp);
}

/******************************************************************************
 *Function Name：	 MEASURE_ClearITAndReadFlag
 *Brief：clear measure Interrupt state register and result has been read flag .
 *Param：
 *	     none
 *
 *Return value：
 *				none
 *Remarks：
 *      此函数目的为清楚测量结果中断和写读标志，之所以封装在一起是因为commandW寄存器中对应位
 *      是只读的，而且基本每次中断后，两者的复位都是要同时进行的，所以将其封装在一起；
 ******************************************************************************/
void MEASURE_ClearResITAndReadFlag(void)
{
	uint32_t tmp = 0;
	//tmp = READ_REG(PMU->COMMAND_W);
	//tmp = LS_RMK(MEASURE_RES_READW,MEASURE_RES_READW_ENABLE);
	//tmp = READ_REG(PMU->COMMAND_W);
	//tmp |= LS_RMK(MEASURE_INT_CLR,MEASURE_INT_RES_READ);
	tmp = ((MEASURE_RES_READW_ENABLE << MEASURE_RES_READW_SHIFT)|\
			(MEASURE_INT_RES_READ <<MEASURE_INT_CLR_SHIFT));
	WRITE_REG(PMU->COMMAND_W,tmp);
}


#if 0
/******************************************************************************
 *Function Name：	 MEASURE_SetTemperatureFakeNum
 *Brief：set measure temperature register fake number .
 *Param：
 *	     number: it define how many times the chip to do fake measure,input parameter
 *	     reference this:
 *		        0: twice
 *		        1: seventh
 *
 *
 *Return value：
 *				none
 *Remarks：
 *      0: 2次
 *      1： 7次
 ******************************************************************************/
void MEASURE_SetTemperatureFakeNum(uint32_t number)
{
	if(number > 1)
	{
		printf("error input range\r\n");
	}
	(number==0)? SET_BIT(THSENS->THSENS_CTRL, 0x0):\
		 SET_BIT(THSENS->THSENS_CTRL, 0x00000001);
}

/******************************************************************************
 *Function Name：	 MEASURE_GetTemperatureFakeNum
 *Brief：Get measure temperature register fake number .
 *Param：
 *	     none
 *
 *Return value：
 *				 0: twice
 *				 1: seventh
 *Remarks：
 *      0: 2次
 *      1： 7次
 ******************************************************************************/
uint32_t MEASURE_GetTemperatureFakeNum(void)
{
	return (READ_BIT(THSENS->THSENS_CTRL, 0x00000001));
}

/******************************************************************************
 *Function Name：	 MEASURE_SetTemperaturePortNum
 *Brief：set measure temperature register Port number .
 *Param：
 *	     number: it define how many ports the chip to measure,input parameter
 *	     reference this:
 *		        0: two
 *		        1: four
 *
 *
 *Return value：
 *				none
 *Remarks：
 *      0: 2 个 （PT0 和 PT1）
 *      1： 4 个（PT0 和 PT1、PT2、PT3）
 ******************************************************************************/
void MEASURE_SetTemperaturePortNum(uint32_t number)
{
	if(number > 1)
	{
		printf("error input range\r\n");
	}

	(number==0)? SET_BIT(THSENS->THSENS_CTRL, 0x0):\
		 SET_BIT(THSENS->THSENS_CTRL, 0x00000002);
}

/******************************************************************************
 *Function Name：	 MEASURE_GetTemperaturePortNum
 *Brief：Get measure temperature register port number .
 *Param：
 *	     none
 *
 *Return value：
 *				 0: two
 *				 1: four
 *Remarks：
 *      0: 2个
 *      1： 4个
 ******************************************************************************/
uint32_t MEASURE_GetTemperaturePortNum(void)
{
	return (READ_BIT(THSENS->THSENS_CTRL, 0x00000002) >> 1);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetTemperaturePortDirection
 *Brief：set measure temperature register Port Direction .
 *Param：
 *	     number: it define how order of ports  to measure,input parameter
 *	     reference this:
 *		        0: PT1->PT2->PT3->PT4
 *		        1: PT4->PT3->PT2->PT1
 *
 *
 *Return value：
 *				none
 *Remarks：
 *      0: PT1->PT2->PT3->PT4
 *      1： PT4->PT3->PT2->PT1
 ******************************************************************************/
void MEASURE_SetTemperaturePortDirection(FlagStatus flag)
{

	(flag == RESET)? SET_BIT(THSENS->THSENS_CTRL, 0x0):\
		 SET_BIT(THSENS->THSENS_CTRL, 0x00000004);
}

#endif

/******************************************************************************
 *Function Name：	 MEASURE_GetTemperaturePortDirection
 *Brief：Get measure temperature register port Direction .
 *Param：
 *	     none
 *
 *Return value：
 *				 0:  PT1->PT2->PT3->PT4
 *				 1:  PT4->PT3->PT2->PT1
 *Remarks：
 *      0:  PT1->PT2->PT3->PT4
 *      1： 	PT4->PT3->PT2->PT1
 ******************************************************************************/
uint32_t MEASURE_GetTemperaturePortDirection(void)
{
	return (READ_BIT(THSENS->THSENS_CTRL, 0x00000004) >> 2);
}

#if 0
/******************************************************************************
 *Function Name：	 MEASURE_SetTemperatureTimeLoad
 *Brief：set measure temperature register time of charge .
 *Param：
 *	     number: it define the time for charge to measure,input parameter
 *	     reference this:
 *		        0: 90us
 *		        1: 120us
 *		        2: 150us
 *		        3: 500us
 *
 *
 *Return value：
 *				none
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_SetTemperatureTimeLoad(uint32_t number)
{
	if(number > 3)
	{
		printf("error input range\r\n");
	}
	if(number == 1)
	{
		SET_BIT(THSENS->THSENS_CTRL, 0x00000010);
	}else if(number == 2)
	{
		 SET_BIT(THSENS->THSENS_CTRL,0x00000020);
	}else if(number == 3)
	{
		SET_BIT(THSENS->THSENS_CTRL, 0x00000030);
	}else
	{
		SET_BIT(THSENS->THSENS_CTRL, 0x00000000);
	}

}


/******************************************************************************
 *Function Name：	 MEASURE_GetTemperatureTimeLoad
 *Brief：Get measure temperature register port Direction .
 *Param：
 *	     none
 *
 *Return value：
 *				 0:  PT1->PT2->PT3->PT4
 *				 1:  PT4->PT3->PT2->PT1
 *Remarks：
 *      0:  PT1->PT2->PT3->PT4
 *      1： 	PT4->PT3->PT2->PT1
 ******************************************************************************/
uint32_t MEASURE_GetTemperatureTimeLoad(void)
{
	return (READ_BIT(THSENS->THSENS_CTRL, 0x00000030) >> 4);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetTemperatureTimeUnload
 *Brief：set measure temperature register time of unload .
 *Param：
 *	     number: it define the time for unload to measure,input parameter
 *	     reference this:
 *		        0: 90us
 *		        1: 120us
 *		        2: 150us
 *		        3: 500us
 *
 *
 *Return value：
 *				none
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_SetTemperatureTimeUnload(uint32_t number)
{
	if(number > 3)
	{
		printf("error input range\r\n");
	}
	if(number == 1)
	{
		SET_BIT(THSENS->THSENS_CTRL, 0x00000040);
	}else if(number == 2)
	{
		 SET_BIT(THSENS->THSENS_CTRL,0x00000080);
	}else if(number == 3)
	{
		SET_BIT(THSENS->THSENS_CTRL, 0x000000C0);
	}else
	{
		SET_BIT(THSENS->THSENS_CTRL, 0x00000000);
	}
}

/******************************************************************************
 *Function Name：	 MEASURE_GetTemperatureTimeUnload
 *Brief：Get measure temperature register time of unload .
 *Param：
 *	     none
 *
 *Return value：
 *				 0:  PT1->PT2->PT3->PT4
 *				 1:  PT4->PT3->PT2->PT1
 *Remarks：
 *      0:  PT1->PT2->PT3->PT4
 *      1： 	PT4->PT3->PT2->PT1
 ******************************************************************************/
uint32_t MEASURE_GetTemperatureTimeUnload(void)
{
	return (READ_BIT(THSENS->THSENS_CTRL, 0x00000030) >> 6);
}

/******************************************************************************
 *Function Name：	 MEASURE_SetTemperatureTimeUnload
 *Brief：set measure temperature register time of unload .
 *Param：
 *	     number: it define the time for unload to measure,input parameter
 *	     reference this:
 *		        0: 90us
 *		        1: 120us
 *		        2: 150us
 *		        3: 500us
 *
 *
 *Return value：
 *				none
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_SetTemperatureFastMode(FunctionalState state )
{
	(state == DISABLE)?SET_BIT(THSENS->THSENS_CTRL, 0x00000000):\
			SET_BIT(THSENS->THSENS_CTRL, 0x00000100);
}

/******************************************************************************
 *Function Name：	 MEASURE_GetTemperatureFastMode
 *Brief：Get measure temperature register fast mode enable or not .
 *Param：
 *	     none
 *
 *Return value：
 *
 *  	0:  放电时间由tunload决定
 *      1： 	放电完成即进入下一个周期，tunload 定超时时间
 *
 *Remarks：
 *
 ******************************************************************************/
uint32_t MEASURE_GetTemperatureFastMode(void)
{
	return (READ_BIT(THSENS->THSENS_CTRL, 0x000000100) >> 8);
}

#endif

/***tools driver***/
int iabs(int i)
{
    if (i<0) return -i;
    return i;
}

#if 0
/******************************************************************************
 *Function Name：	 MEASURE_TdcGateWindowInit
 *Brief：set measure mode to sleep;
 *Param：
 *		 none
 *Return value：
 *
 *		none
 *Remarks：
 *
 *
 ******************************************************************************/
void MEASURE_TdcGateWindowInit(int winID, int cycle, int frac, int len, int once, int keep)
{
    uint32_t tmp=0;
    LS_RINS(tmp,MEASURE_GATE_DELAY_VAL,((cycle<<5) | (frac&0x1f)));
    LS_RINS(tmp,MEASURE_GATE_LEN,len);
    LS_RINS(tmp,MEASURE_GATE_ONE_SHOT,once);
    LS_RINS(tmp,MEASURE_GATE_KEPP_OPEN,keep);
	switch(winID)
	{
	case 1:
		WRITE_REG(SONAR->GATE_DEF1,tmp);
		break;
	case 2:
		WRITE_REG(SONAR->GATE_DEF2,tmp);
		break;
	default:
		WRITE_REG(SONAR->GATE_DEF3,tmp);
		break;
	}
}
#endif


















