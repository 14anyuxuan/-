/*
 * UserMeasure.c
 *
 *  Created on: 2021骞�10鏈�18鏃�
 *      Author: lixin
 */

#include "UserMeasure.h"
#include "UserLcd.h"
#include "GlobalDef.h"
uint8_t resvalid_flag = 0;

pMeasureData MeasureRecord;

void MeasureSonarInit(void)
{
	Measure_InitTypeDef Measure;
	MEASURE_StructInit(&Measure);
	MEASURE_ClockInit(&(Measure.Clock));
	MEASURE_PulseInit(&(Measure.Pulse));
	MEASURE_ControlInit(&(Measure.Control));
	MEASURE_CalibrationInit(&(Measure.Calibration));
	MEASURE_AfeInit(&(Measure.Afe));
	MEASURE_GateWindowInit();
	//MEASURE_DefaultInit();

}

void floatcalc(void)
{
	float a = 1.2;
	float b = 2;
	int c = 0;

	b = a*b;
	c = (int)b;
}
/* amc 宄板�奸噰闆� */
void MeasureAmcTask()
{
	int i,vref = 0;
	int fwd_adc[16],bwd_adc[16];

	MeasureGate_InitTypeDef gate = {1,  7*8,  0,   1, 0, 0};

	MEASURE_DefaultInit();
	vref = GetVrefValue();
	printf("forward vref = %d\n",i,vref);
	MEASURE_SetAfeVtestSel(MEASURE_AFECTRL_VTEST_SEL_DAC_AMC);
	MEASURE_SetAfeVtestDual(ENABLE);
	MEASURE_SetAfeVtest(ENABLE);
	MEASURE_SetAfeVtestOut(MEASURE_AFECTRL_VTEST_OUT_VAMC);
	MEASURE_SetAfeVRefOut(DISABLE);
	MEASURE_SetPulseWavePeakMode(ENABLE);

    for(;;)
    {
		MEASURE_ClearADCPtrReg();
    	for(i=0;i<16;i++)
    	{
    		gate.DelayValCycle = (i + 1)*8;
    		MEASURE_TdcSetWindow(&gate);
    		MEASURE_SetTaskToStart(MEASURE_MOP_ONCE_TOF);
    		MEASURE_SuspendTask();
    		fwd_adc[i] = (MEASURE_GetAmcValue(ForwardDirction) - vref);
    	}
    	MEASURE_SetMannualDirectionReverse();
    	MEASURE_ClearADCPtrReg();

    	for(i=0;i<16;i++)
    	{
    		gate.DelayValCycle = (i + 1)*8;
    		MEASURE_TdcSetWindow(&gate);
    		MEASURE_SetTaskToStart(MEASURE_MOP_ONCE_TOF);
    		MEASURE_SuspendTask();
    		bwd_adc[i] = (MEASURE_GetAmcValue(BackwardDirction) - vref);
    	}

    	for(i = 0;i <16;i++)
    	{
    		printf("fwd-amc[%d] = %4d  ,vol=%4d mV ",i,fwd_adc[i],fwd_adc[i]*3300/4096);
    		printf("bwd-amc[%d] = %4d ,vol=%4d mV\r\n",i,bwd_adc[i],bwd_adc[i]*3300/4096);
    	}
    	MEASURE_SetMannualDirectionReverse();

//    	if(BreakKey())
//    	{
//    		printf("exit AMC-Task\n");
//    		break;
//    	}
    	//CLOCK_DelayMs(1000);
    }
}

void MeasureVrefTask(void)
{
	uint32_t reg = 0,reg_bk = 0,i = 0;
	int fwd_vref = 0,bwd_vref = 0,vref = 0;
	MEASURE_DefaultInit();
	reg = READ_REG(SONAR->AFE_CTRL);
	reg_bk = reg;
	LS_RINS(reg,MEASURE_AFECTRL_VTEST_SEL,MEASURE_AFECTRL_VTEST_SEL_VREF);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST_SEL,MEASURE_AFECTRL_VTEST_DUAL_ENABLE);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST,MEASURE_AFECTRL_VTEST_ENABLE);
	LS_RINS(reg,MEASURE_AFECTRL_VTEST_OUT,MEASURE_AFECTRL_VTEST_OUT_OTHER);
	LS_RINS(reg,MEASURE_AFECTRL_VREF_OUT,MEASURE_AFECTRL_VREF_OUT_ENABLE);

	WRITE_REG(SONAR->AFE_CTRL,reg);

	LS_RINS(reg,MEASURE_FWAVECTRL_WAVEP,MEASURE_FWAVECTRL_WAVEP_ENABLE);

	MEASURE_ClearADCPtrReg();

	for(;;)
	{
		for(;i<2;i++)
		{
			MEASURE_SetTaskToStart(MEASURE_MOP_TWICE_TOF);
			MEASURE_SuspendTask();
			fwd_vref += MEASURE_GetAmcValue(ForwardDirction);
			bwd_vref += MEASURE_GetAmcValue(BackwardDirction);
		}
		//MEASURE_StopTask();
		//MEASURE_ExitCruiseTask();
		vref = (fwd_vref + bwd_vref) >> 2;
		printf("vref = %4d , vol=%4d mV\r\n",vref,vref*3300/4096);
		printf("fwd-vref = %4d , vol=%4d mV ",fwd_vref,fwd_vref*3300/4096);
		printf("bwd-vref = %4d , vol=%4d mV\r\n",bwd_vref,bwd_vref*3300/4096);

		MEASURE_ClearADCPtrReg();

//    	if(BreakKey())
//    	{
//    		printf("exit VREF-Task\n");
//    		break;
//    	}
	}

	WRITE_REG(SONAR->AFE_CTRL,reg_bk);

}

void PrintfSonarRegister(void)
{

	int i;
	if (POWER_GetSonarOffMode() == SET) //SonarOff
	{
		printf("\r\nWarning: sonaroff, unable to readreg !!");
	}
	for(i=0; i<12; i++)
	{
		if((i%4) == 0)
		{
			printf("\n0x%08x:", 0x5a00+i*4);
		}
		printf(" %08x", readw((0x5a00+i*4)));
		//printf(" %08x", *(volatile unsigned int*)(0x5a00+i*4));
	}

	printf("\n timing is %x" ,*(uint32_t *)(0x00005800));
	printf("\n command is %x" ,*(uint32_t *)(0x00005804));
	printf("\n chip is %x" ,*(uint32_t *)(0x00005810));
	printf("\n autocalc is %x" ,*(uint32_t *)(0x00005814));
	printf("\n commandW is %x" ,*(uint32_t *)(0x0000583c));
}

float GetfValue(float  bArray, float MeanData)
{

     float sum = bArray;
//    int j = (int)MeanData;
   sum = sum / MeanData;
    return  sum;
}


void MeasureCuriseTask(void)
{
	uint32 fire_num = 32;
	uint32_t Threshold = 780;
	uint8_t hit_num = 12;
	uint8_t flter_num = 3;

	MeasureGate_InitTypeDef gate1 = {0, 57*8, 0, 12*8, 0, 0};	//considering the fastest speed of sound
	MeasureGate_InitTypeDef gate2 = {1,  7*8-1, 0,   1, 0, 1};

	MeasureTdcCal_StateTypeDef tdc_cal;
	//MedianFilterStructData filter;
	uint32_t sum_DTOF,avr_DTOF,time_DTOF;
	uint32_t manual_avrDTof,manual_timeDTof;
//     float a = 120.4f;
// 	  float c = 2.1f;
//	 int b =   cal_fq(a,c);
	uint32_t tof_start_f = 0, tof_start_b = 0,tof_f = 0,tof_b = 0;
	//printf("in task\n");
	MEASURE_DefaultInit();
	POWER_SonarOffConfig(RESET);
	MEASURE_SetPulseWaveFireNum(fire_num);
	MEASURE_SetPulseWaveHitNum(hit_num);
	MEASURE_SetPulseFirstWaveThreshold(Threshold);
	MEASURE_SetAutoCalculateMode(DISABLE);
	MEASURE_SetAutoCalculateHitNum(hit_num - 1);
	MEASURE_SetAutoCalculateFltRate(flter_num);
	MEASURE_SetPulseWaveTailEnd(fire_num + 1);
	MEASURE_SetPulseWaveWaitEnd(fire_num + 6);
	MEASURE_TdcSetWindow(&gate1);
	MEASURE_TdcSetWindow(&gate2);
	MEASURE_SetTdcAutoCalPre(DISABLE);
	MEASURE_SetTdcAutoCalPst(ENABLE);
	MEASURE_SetPulseWaveWideMode(DISABLE);
	MEASURE_SetFirstPulseWaveMode(ENABLE);
	MEASURE_SetPulseWaveHitIgnNum(0);
	MEASURE_ClearTdcResReg();
	MEASURE_ClearTdcCalReg();
	MEASURE_ITConfig(MEASURE_INT_RES_READ,ENABLE);
	MEASURE_ClearResITAndReadFlag();
	//MEASURE_SetResReadFlag();
	//MEASURE_ClearIT((MEASURE_INT_WAKE|MEASURE_INT_RES_READ|MEASURE_INT_BAT_FAIL|MEASURE_INT_C32K_FAIL|MEASURE_INT_C8M_FAIL|MEASURE_INT_KEY|MEASURE_INT_RING|MEASURE_INT_RTC));
	MEASURE_SetWatchDog(ENABLE);
	//MEASURE_SetTaskToStart(MEASURE_MOP_TWICE_TOF); //闈炲贰鑸ā寮忎笅鐨勫惎鍔ㄤ换鍔★紝宸¤埅妯″紡涓嬬敱鑺墖鍐呴儴鑷繁璁剧疆
	MEASURE_SetCruiseMode(MEASURE_CRUISE_MODE_TOF);
	//InitMedianFilter(&filter);
	for(;;)
	{
		//PrintfSonarRegister();
		//printf("resvalid_flag = %d\r\n",resvalid_flag);
		if(resvalid_flag) /* 鏀跺埌鏁版嵁  */
		{
			resvalid_flag=0;
			if(MEASURE_ExpectResPtr() == ERROR)
			{
				printf("resptr is error \n");
			}
			if(MEASURE_GetTdcCal(&tdc_cal) != SUCCESS)
 			{
 				printf("tdc cad get error \n");
 			}

			 MEASURE_WriteTdcCalToReg(&tdc_cal);

			 tof_start_f =  MEASURE_GetStartTime(&tdc_cal,ForwardDirction);
			 tof_start_b =  MEASURE_GetStartTime(&tdc_cal,BackwardDirction);
			 tof_f = MEASURE_GetResData(&tdc_cal,0,ForwardDirction) - tof_start_f;
			 tof_b = MEASURE_GetResData(&tdc_cal,0,BackwardDirction) - tof_start_b;
			 tof_f = MEASURE_GetDtofConvertPsValue(tof_f,125000);
			 tof_b = MEASURE_GetDtofConvertPsValue(tof_b,125000);
			 //avr_DTOF = MEASURE_GetAutoDtofValue(hit_num,flter_num);
			 //time_DTOF = MEASURE_GetDtofConvertPsValue(avr_DTOF,125000);

			 manual_avrDTof = MEASURE_GetManualDtofValue(&tdc_cal,hit_num,flter_num);
 			 manual_timeDTof = MEASURE_GetDtofConvertPsValue(manual_avrDTof,125000);
			// printf("\r\nDTOF = %d ,time = %d\n",avr_DTOF,time_DTOF);
			//printf("\r\nAVG=%d\n---------", time_DTOF);
			 printf("\r\nmDTOF=%d , Mtime = %d \n", manual_avrDTof,manual_timeDTof);
//			 b = GetfValue(a,b);
//			 printf("\r\nb =%d  \n",b );
			 printf("\r\ntof_f =%d , tof_b =%d\n",tof_f,tof_b);
			 //LcdDisplay(DisplayCapacityMode);
			 //LcdDisplay(NormalMode);



		}
		CLOCK_DelayMs(5);
		WDG_DogFeed();			//閸犲倻瀚�
	}
}

void MeasureWaveWideTask(void)
{
	uint32 fire_num = 32;
	uint32_t Threshold = 512;
	uint8_t hit_num = 12;
	uint8_t flter_num = 3;
	MeasureGate_InitTypeDef gate1 = {0, 57*8, 0, 12*8, 0, 0};	//considering the fastest speed of sound
	MeasureGate_InitTypeDef gate2 = {1,  7*8-1, 0,   1, 0, 1};
	MeasureTdcCal_StateTypeDef tdc_cal;
	MeasurePulseWidth_StateTypeDef wave_width;
	uint32_t sum_DTOF,avr_DTOF,time_DTOF;
	//printf("in task\n");
	MEASURE_DefaultInit();
	POWER_SonarOffConfig(RESET);
	MEASURE_SetPulseWaveFireNum(fire_num);
	MEASURE_SetPulseWaveHitNum(hit_num);
	MEASURE_SetPulseFirstWaveThreshold(Threshold);
	MEASURE_SetAutoCalculateFltRate(flter_num);
	MEASURE_SetPulseWaveTailEnd(fire_num + 1);
	MEASURE_SetPulseWaveWaitEnd(fire_num + 6);
	MEASURE_TdcSetWindow(&gate1);
	MEASURE_TdcSetWindow(&gate2);
	MEASURE_SetTdcAutoCalPre(DISABLE);
	MEASURE_SetTdcAutoCalPst(ENABLE);
	MEASURE_SetPulseWaveWideMode(ENABLE);
	MEASURE_SetFirstPulseWaveMode(ENABLE);
	MEASURE_SetPulseWaveHitIgnNum(0);
	MEASURE_ClearTdcResReg();
	MEASURE_ClearTdcCalReg();
	MEASURE_ClearResPtrReg();
	MEASURE_ITConfig(MEASURE_INT_RES_READ,ENABLE);
	MEASURE_ClearResITAndReadFlag();
	//MEASURE_SetResReadFlag();
	//MEASURE_ClearIT((MEASURE_INT_WAKE|MEASURE_INT_RES_READ|MEASURE_INT_BAT_FAIL|MEASURE_INT_C32K_FAIL|\
				MEASURE_INT_C8M_FAIL|MEASURE_INT_KEY|MEASURE_INT_RING|MEASURE_INT_RTC));
	MEASURE_SetWatchDog(ENABLE);
	//MEASURE_SetTaskToStart(MEASURE_MOP_TWICE_TOF); 闈炲贰鑸ā寮忎笅鐨勫惎鍔ㄤ换鍔★紝宸¤埅妯″紡涓嬬敱鑺墖鍐呴儴鑷繁璁剧疆
	MEASURE_SetCruiseMode(MEASURE_CRUISE_MODE_TOF);

	for(;;)
	{

		//printf("wait\n");
		MEASURE_SuspendTask();

		//printf("resvalid_flag = %d\r\n",resvalid_flag);
		if(resvalid_flag) /* 鏀跺埌鏁版嵁 */
		{
			if(MEASURE_ExpectResPtr() == ERROR)
			{
				printf("resptr is error \n");
			}
			if(MEASURE_GetTdcCal(&tdc_cal) != SUCCESS)
			{
				printf("tdc cal get error \n");
			}
			MEASURE_ClearResPtrReg();
			MEASURE_WriteTdcCalToReg(&tdc_cal);
			MEASURE_GetPulseWidth(&wave_width);

			printf("\r\nWidth1=%d ", wave_width.PrePulse1Width);
			printf("\r\nWidth2=%d ", wave_width.PrePulse2Width);
			printf("\r\nfwd width_ratio =%d\n", (wave_width.PrePulse1Width*100)/wave_width.PrePulse2Width);
			printf("\r\nWidth1=%d ", wave_width.PstPulse1Width);
			printf("\r\nWidth2=%d ", wave_width.PstPulse2Width);
			printf("\r\nbwd width_ratio =%d\n", (wave_width.PstPulse1Width*100)/wave_width.PstPulse2Width);
			avr_DTOF  = MEASURE_GetManualDtofValue(tdc_cal.ForwardCal_C,hit_num,flter_num);
			time_DTOF = MEASURE_GetDtofConvertPsValue(avr_DTOF,125000);
			//printf("DTOF = %d ,time = %d\n",avr_DTOF,time_DTOF);
			printf("\r\nAVG=%d\n----------------", time_DTOF);
			//LcdDisplay(DisplayCapacityMode);
			//floatcalc();
		}

	}
}


#if 0

void MeasureTemperatureTask(void)
{
	uint32 res_data0 = 0, res_data1 = 0 ,res_data2 = 0,res_data3 = 0;

	MeasureGate_InitTypeDef gate1 = {0, 57*8, 0, 12*8, 0, 0};	//considering the fastest speed of sound
	MeasureGate_InitTypeDef gate2 = {1,  7*8-1, 0,   1, 0, 1};
	MeasureTdcCal_StateTypeDef tdc_cal;

	uint32_t sum_DTOF,avr_DTOF,time_DTOF;
	//printf("in task\n");
	MEASURE_DefaultInit();
	POWER_SonarOffConfig(RESET);


#if 0
	MEASURE_SetPulseWaveFireNum(fire_num);
	MEASURE_SetPulseWaveHitNum(hit_num);
	MEASURE_SetPulseFirstWaveThreshold(Threshold);
	MEASURE_SetAutoCalculateFltRate(flter_num);
	MEASURE_SetPulseWaveTailEnd(fire_num + 1);
	MEASURE_SetPulseWaveWaitEnd(fire_num + 6);
	MEASURE_TdcSetWindow(&gate1);
	MEASURE_TdcSetWindow(&gate2);
	MEASURE_SetTdcAutoCalPre(DISABLE);

	MEASURE_SetPulseWaveWideMode(ENABLE);
	MEASURE_SetFirstPulseWaveMode(ENABLE);
	MEASURE_SetPulseWaveHitIgnNum(0);
	MEASURE_ClearTdcResReg();
	MEASURE_ClearTdcCalReg();
	MEASURE_ClearResPtrReg();
	MEASURE_ITConfig(MEASURE_INT_RES_READ,ENABLE);
	MEASURE_ClearResITAndReadFlag();
	//MEASURE_SetResReadFlag();
	//MEASURE_ClearIT((MEASURE_INT_WAKE|MEASURE_INT_RES_READ|MEASURE_INT_BAT_FAIL|MEASURE_INT_C32K_FAIL|\
				MEASURE_INT_C8M_FAIL|MEASURE_INT_KEY|MEASURE_INT_RING|MEASURE_INT_RTC));
	MEASURE_SetWatchDog(ENABLE);
	//MEASURE_SetTaskToStart(MEASURE_MOP_TWICE_TOF); 闈炲贰鑸ā寮忎笅鐨勫惎鍔ㄤ换鍔★紝宸¤埅妯″紡涓嬬敱鑺墖鍐呴儴鑷繁璁剧疆
	MEASURE_SetCruiseMode(MEASURE_CRUISE_MODE_TOF);
#endif

	MEASURE_SetTdcAutoCalPst(ENABLE);
	MEASURE_SetTemperatureFakeNum(0);
	MEASURE_SetTemperaturePortNum(0);
	MEASURE_SetTemperaturePortDirection(RESET);
	MEASURE_SetTemperatureTimeLoad(0);
	MEASURE_SetTemperatureTimeUnload(0);
	MEASURE_ClearTdcResReg();
	MEASURE_ClearTdcCalReg();
	MEASURE_ClearResPtrReg();
	MEASURE_ITConfig(MEASURE_INT_RES_READ,ENABLE);
	MEASURE_ClearResITAndReadFlag();

	MEASURE_SetTaskToStart(MEASURE_MOP_ONCE_TEMP); //闈炲贰鑸ā寮忎笅鐨勫惎鍔ㄤ换鍔★紝宸¤埅妯″紡涓嬬敱鑺墖鍐呴儴鑷繁璁剧疆
//	MEASURE_SetCruiseMode(MEASURE_CRUISE_MODE_TEMP);
	for(;;)
	{

		//printf("wait\n");
		MEASURE_SuspendTask();

		//printf("resvalid_flag = %d\r\n",resvalid_flag);
		if(resvalid_flag) /* 鏀跺埌鏁版嵁  */
		{
			//if(MEASURE_ExpectResPtr() == ERROR)
			//{
			//	printf("resptr is error \n");
			//}
			tdc_cal.BackwardCal_C = cal_C(StsFwd+4, StsFwd+8);
			printf("pstcal1 = %x\n",*(uint32_t *)(StsFwd));
			printf("pstcal2 = %x\n",*(uint32_t *)(StsFwd+4));
			printf("calC = %d\n",tdc_cal.BackwardCal_C);
			//if(MEASURE_GetTdcCal(&tdc_cal) != SUCCESS)
			//{
			//	printf("tdc cal get error \n");
			//}
			//MEASURE_ClearResPtrReg();
			 MEASURE_WriteTdcCalToReg(&tdc_cal);
			//MEASURE_GetPulseWidth(&wave_width);
			MEASURE_GetResData(ResData0,ForwardDirction);
			printf("\r\nWidth1=%d ", wave_width.PrePulse1Width);
			printf("\r\nWidth2=%d ", wave_width.PrePulse2Width);
			printf("\r\nfwd width_ratio =%d\n", (wave_width.PrePulse1Width*100)/wave_width.PrePulse2Width);
			printf("\r\nWidth1=%d ", wave_width.PstPulse1Width);
			printf("\r\nWidth2=%d ", wave_width.PstPulse2Width);
			printf("\r\nbwd width_ratio =%d\n", (wave_width.PstPulse1Width*100)/wave_width.PstPulse2Width);
			avr_DTOF = MEASURE_GetAutoDtofValue(hit_num,flter_num);
			time_DTOF = MEASURE_GetDtofConvertPsValue(avr_DTOF,125000);
			//printf("DTOF = %d ,time = %d\n",avr_DTOF,time_DTOF);
			printf("\r\nAVG=%d\n----------------", time_DTOF);

			//floatcalc();
		}

	}
}


#endif





const uint8_t hit_num = 12;
const uint8_t flter_num = 3;

void StandardMeasureInit()
{
	uint32 fire_num = 32;
	uint32_t Threshold = 780;
	MeasureGate_InitTypeDef gate1 = {0, 54*8, 0, 30*8, 0, 0};	//considering the fastest speed of sound
	MeasureGate_InitTypeDef gate2 = {1,  7*8-1, 0,   1, 0, 1};
	//MedianFilterStructData filter;
	//printf("in task\n");
	MEASURE_DefaultInit();
	POWER_SonarOffConfig(RESET);
	MEASURE_SetPulseWaveFireNum(fire_num);
	MEASURE_SetPulseWaveHitNum(hit_num);
	MEASURE_SetPulseFirstWaveThreshold(Threshold);
	MEASURE_SetAutoCalculateMode(DISABLE);
	MEASURE_SetAutoCalculateHitNum(hit_num - 1);
	MEASURE_SetAutoCalculateFltRate(flter_num);
	MEASURE_SetPulseWaveTailEnd(fire_num + 1);
	MEASURE_SetPulseWaveWaitEnd(fire_num + 6);
	MEASURE_TdcSetWindow(&gate1);
	MEASURE_TdcSetWindow(&gate2);
	MEASURE_SetTdcAutoCalPre(DISABLE);
	MEASURE_SetTdcAutoCalPst(ENABLE);
	MEASURE_SetPulseWaveWideMode(DISABLE);
	MEASURE_SetFirstPulseWaveMode(ENABLE);
	MEASURE_SetPulseWaveHitIgnNum(0);
	MEASURE_ClearTdcResReg();
	MEASURE_ClearTdcCalReg();
	MEASURE_ITConfig(MEASURE_INT_RES_READ,ENABLE);
	MEASURE_ClearResITAndReadFlag();
	//MEASURE_SetResReadFlag();
	//MEASURE_ClearIT((MEASURE_INT_WAKE|MEASURE_INT_RES_READ|MEASURE_INT_BAT_FAIL|MEASURE_INT_C32K_FAIL|MEASURE_INT_C8M_FAIL|MEASURE_INT_KEY|MEASURE_INT_RING|MEASURE_INT_RTC));
	MEASURE_SetWatchDog(ENABLE);
	resvalid_flag=0;
	MEASURE_SetTaskToStart(MEASURE_MOP_TWICE_TOF); //闈炲贰鑸ā寮忎笅鐨勫惎鍔ㄤ换鍔★紝宸¤埅妯″紡涓嬬敱鑺墖鍐呴儴鑷繁璁剧疆
	//MEASURE_SetCruiseMode(MEASURE_CRUISE_MODE_TOF);
	//InitMedianFilter(&filter);
	//娣诲姞鑾峰彇闈欐�佺殑鏃跺樊闆朵綅鍊肩▼搴�

}

uint32_t MeasureDataProcess(uint32_t *fwd_fly_time,uint32_t *bwd_fly_time,uint32 *dtof)
{
	uint32_t tof_start_f = 0, tof_start_b = 0,tof_f = 0,tof_b = 0;
	MeasureTdcCal_StateTypeDef tdc_cal;
	uint32_t sum_DTOF,avr_DTOF,time_DTOF;
	if(resvalid_flag) /* 鏀跺埌鏁版嵁  */
	{
		resvalid_flag=0;
		if(MEASURE_ExpectResPtr() == ERROR)
		{
			printf("resptr is error \n");
		}
		if(MEASURE_GetTdcCal(&tdc_cal) != SUCCESS)
		{
			printf("tdc cad get error \n");
		}

		MEASURE_WriteTdcCalToReg(&tdc_cal);
		tof_start_f =  MEASURE_GetStartTime(&tdc_cal,ForwardDirction);
		tof_start_b =  MEASURE_GetStartTime(&tdc_cal,BackwardDirction);
		tof_f = MEASURE_GetResData(&tdc_cal,0,ForwardDirction) - tof_start_f;
		tof_b = MEASURE_GetResData(&tdc_cal,0,BackwardDirction) - tof_start_b;
		tof_f = MEASURE_GetDtofConvertPsValue(tof_f,125000);
		tof_b = MEASURE_GetDtofConvertPsValue(tof_b,125000);
		avr_DTOF  = MEASURE_GetManualDtofValue(&tdc_cal,hit_num,flter_num);
		time_DTOF = MEASURE_GetDtofConvertPsValue(avr_DTOF,125000);

		 printf("\r\nDTOF=%d , Mtime = %d \n", avr_DTOF,time_DTOF);
		 printf("\r\ntof_f =%d , tof_b =%d\n",tof_f,tof_b);

	}

	return 1;
}

uint32_t forward_Q;
uint32_t backward_Q;




