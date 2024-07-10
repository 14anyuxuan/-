/*
 * Filter.h
 *
 *  Created on: 2018��7��7��
 *      Author: LX
 */
#ifndef SRC_FILTER1_H_
#define SRC_FILTER1_H_

#include "ls1d.h"
#include "ls1d_std_str_other.h"
#include "ls1d_std_printf.h"
#define IIR_SHIFT         8

#define M_PI_F (float)3.14159265

typedef struct {

	uint32 *Addr;
	short count;
	short FilterDepth;
	int   Average;  /* ��ֵ*/
	int   MiddleValue;
	int   LinearFilterValue;/* �����˲�ֵ*/
	unsigned char Flag;

}FilterStructData;




typedef struct {

   uint32  *RawDataAddr;
   uint32  *MedianDataAddr;
   short count;
   short FilterDepth;
   float   Average;
   float   MiddleValue;
   float   LinearFilterValue;/* �����˲�ֵ*/
   unsigned char Flag;
   unsigned char IsFilterFull;
}MedianFilterStructData;

/************************************************************************
* ��������  InitRectWindowFilter
* ���������� �������ھ����˲�
*
* ���������
*     none
*
* ���������
*     none��
*
* ���أ�
*
* ��ע
**************************************************************************/
extern short InitRectWindowFilter(FilterStructData *data);


extern short InitMedianFilter(MedianFilterStructData *data);


extern short RectWindowFilter(FilterStructData *FilterData,int data);


extern short MedianFilter(MedianFilterStructData *FilterData,uint32_t data,float *MedianData,float *MeanData);

extern short GetMeanValue(float * bArray, int iFilterLen,float *MeanData);
#endif /* SRC_FILTER1_H_ */










