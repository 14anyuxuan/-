/*
 * UserMeasure.h
 *
 *  Created on: 2021锟斤拷10锟斤拷27锟斤拷
 *      Author: lixin
 */

#ifndef USERINC_USERMEASURE_H_
#define USERINC_USERMEASURE_H_

#include "ls1d_std_measure.h"
#include "ls1d_std_printf.h"
#include "ls1d_std_power.h"
#include "Filter.h"
//#include "tasks.h"
#define MeasureResultCaculateNummber	((uint32_t)32)//80
#define MaxPulseHitInterval			((int)0x112A88) 	//1.125us
#define MinPulseHitInterval			((int)0xd59F8)		//0.875us
#define HitIntervalDownRange		((int)(0 - 0xd59F8))		//0.875us
#define HitIntervalUpRange			((int)0xd59F8)		//0.875us
#define MaxDtofRange			  	((int)0x1C9C38)	    //1.875us
#define MinDtofRange			  	((int)(0 - 0x1C9C38))	    //1.875us
#define AMC_Threshold	   			12
int temper_shift;
typedef struct
{
	uint32_t money_current;			//锟斤拷锟节癸拷锟斤拷慕锟斤拷
	uint32_t money_total;			//锟桔计斤拷锟�
	uint32_t money_residual;		//锟斤拷锟节癸拷锟斤拷慕锟斤拷
}WaterMeterMoneyData;


typedef struct{
	uint32 nb_trigger;			/*NB锟斤拷锟斤拷锟斤拷锟捷达拷锟斤拷时锟斤拷锟斤拷*/
	uint32 forward_cubage_interger;//水锟斤拷锟桔硷拷锟捷伙拷锟斤拷锟斤拷位为锟斤拷锟斤拷锟斤拷1mL锟斤拷
	uint32 backward_cubage_interger;//水锟斤拷锟桔硷拷锟捷伙拷锟斤拷锟斤拷位为锟斤拷锟斤拷锟斤拷1mL锟斤拷
	uint32_t battery_voltage;		/*锟斤拷氐锟窖�*/
	uint32 capacity_purchased;		//锟斤拷锟斤拷锟斤拷莼锟�
	uint32 forward_total_cubage;	//水锟斤拷锟桔硷拷锟捷伙拷锟斤拷锟斤拷位为锟斤拷锟斤拷1L锟斤拷
	uint32 backward_total_cubage;	//水锟斤拷锟桔硷拷锟捷伙拷锟斤拷锟斤拷位为锟斤拷锟斤拷1L锟斤拷
	uint32 residual_cubage;		//剩锟斤拷锟捷伙拷(锟斤拷位L)
	uint32_t total_run_time; 	//系统锟斤拷锟斤拷锟桔伙拷时锟斤拷(锟斤拷位h)
	int32 water_speed;			//水锟斤拷锟斤拷(锟斤拷位L)
	uint32_t upload_total;			//锟较达拷锟斤拷锟斤拷
	uint32_t upload_success_count;	//锟较达拷锟缴癸拷锟斤拷锟斤拷
	float forward_cubage_fraction;	//水锟斤拷锟桔硷拷锟捷伙拷锟斤拷锟斤拷位为锟斤拷锟斤拷锟斤拷0.000001mL锟斤拷
	float backward_cubage_fraction;//水锟斤拷锟桔硷拷锟捷伙拷锟斤拷锟斤拷位为锟斤拷锟斤拷锟斤拷0.000001mL锟斤拷
	uint16_t signal_gain;			/* 锟脚猴拷锟斤拷锟斤拷 */
	uint8_t balance_date;			/* 锟斤拷锟斤拷锟斤拷 */
	uint8_t read_meter_date;		/* 锟斤拷锟斤拷锟斤拷 */
	int negative_cubage_count;
//	WaterMeterMoneyData money;
}pMeasureData;




typedef struct
{
	int fwd_pass_time;
	int bwd_pass_time;
	int dtof_time;
}SonarRecordData;

struct ZeroPositionMeasureStructure
{
	int  standard_value;//17.15锟斤拷锟捷革拷式时锟斤拷值
	short shift_value;	//偏锟斤拷锟斤拷ps
	uint16_t step;			//锟斤拷位锟斤拷锟斤拷锟侥诧拷锟斤拷
	int count;
}zero_position;


/**
 * @说锟斤拷 锟斤拷锟斤拷锟斤拷始锟斤拷锟斤拷锟斤拷
 */
typedef struct
{
	int dtof_last;//dtof 锟斤拷一锟斤拷值
	int dtof_current;//dtof 锟斤拷前值
	int delt;		//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�1锟斤拷锟斤拷锟斤拷值
	uint16_t count;	//锟届常值锟桔硷拷
	uint16_t flag;
}DtofRepairStructure;


/**
 * @说锟斤拷 锟斤拷锟斤拷锟斤拷始锟斤拷锟斤拷锟斤拷
 */
typedef struct
{
	uint8_t precal_enable;
	uint8_t pstcal_enable;
	uint8_t wave_wide_enable;
	uint8_t Cal_Neg_Edge;
}Sonar_Calibation_Ctrl;

typedef struct
{

	uint16_t count;
	uint16_t adc_value;
	uint16_t temprature;
	uint16_t temp_low_count;
	int temp_offset;
}Ntc_Measure_Ctrl;

extern pMeasureData MeasureRecord;
extern MedianFilterStructData dtof_filter;
extern MedianFilterStructData fwd_filter;
extern MedianFilterStructData bwd_filter;
extern SonarRecordData measure_rawdata[MeasureResultCaculateNummber + 1];
extern DtofRepairStructure Dtof_Repair_Data;
extern uint32_t caculate_index;
extern uint32_t transducer_state;
extern const uint32_t Threshold_default;
extern const uint8_t hit_num  ;
extern const uint8_t flter_num  ;
extern Sonar_Calibation_Ctrl calib_ctrl;
extern Ntc_Measure_Ctrl NTC_measure;
extern uint16_t MeasureDataIRQProcess(SonarRecordData *record);
extern float WaterVolumeMoneyCalculate(uint32_t fwd_fly_time,uint32_t bwd_fly_time,int dtof,uint8 work_mode);
extern ErrorStatus SonarExpectResPtr(void);
extern ErrorStatus SonarGetTdcCal(MeasureTdcCal_StateTypeDef *cal);
ErrorStatus Dtof_Repair(DtofRepairStructure *repair_structure);
//extern void PrintfSonarRegister(void);
extern uint16_t MEASURE_GetManualTempValue(uint8 work_mode);
extern int MEASURE_GetManualTempComValue(int dtof);

#endif





