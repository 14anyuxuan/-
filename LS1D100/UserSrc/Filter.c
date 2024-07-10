/*
 * Filter.c
 *   �˲����ܺ���
 *  Created on: 2018��7��7��
 *      Author: LX
 *  more info:http://v.youku.com/v_show/id_XMjg4ODI1MzQ4MA==.html·���滮
 */

#include "Filter.h"

/* �������ھ����˲� */
#define FilterLength   7
uint32_t firdata[FilterLength];
uint32_t rawdata[FilterLength];


short InitRectWindowFilter(FilterStructData *data)
{

	data->Addr = rawdata;
	data->Average = 0;
	data->MiddleValue = 0;
	data->LinearFilterValue = 0;
	data->FilterDepth = FilterLength;
	data->Flag = 0;
	data->count = 0;
	return SUCCESS;
}

/* ��ֵƽ���˲� */
/************************************************************************
* ��������  InitMedianFilter
* ���������� ��ֵƽ���˲�
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
short InitMedianFilter(MedianFilterStructData *data)
{

	data->RawDataAddr =  rawdata;
	data->MedianDataAddr = firdata;
	data->Average = 0;
	data->MiddleValue = 0;
	data->LinearFilterValue = 0;
	data->FilterDepth = FilterLength;
	data->Flag = 0;
	data->count = 0;
	return 1;
}

/* �������ھ����˲� */
short FreeFilter(FilterStructData *data)
{
	if(data->Addr != NULL)
	{
		//free(data->Addr);
		data->Addr = 0;
		data->Average = 0;
		data->MiddleValue = 0;
		data->LinearFilterValue = 0;
		data->Flag = 0;
		data->count = 0;
		data->FilterDepth = 0;
	}

	return 1;
}

/************************************************************************
* ��������  RectWindowFilter
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
short RectWindowFilter(FilterStructData *FilterData,int data)
{
	int  sum=0;
	int i = 0;
	int  linear_sum = 0;
//	if(FilterData == NULL)
//	{
//		SetSystemErrorLogInfo(SystemInPutParameterPointerIsNull);
//		return RunError;
//	}

	for(i=1; i< FilterData->FilterDepth ;i++)
	{
		FilterData->Addr[i-1] = FilterData->Addr[i];
	}

	FilterData->Addr[FilterData->FilterDepth - 1] = data; //���µ����ݷ��õ� ���ݵ������

	for(i=0;i<FilterData->FilterDepth;i++)
	{
		linear_sum += FilterData->Addr[i];
	}

	FilterData->LinearFilterValue =linear_sum/FilterData->FilterDepth;

	if(++FilterData->count == FilterData->FilterDepth)
	{

		for(i=0;i< FilterData->FilterDepth ;i++)
		{
			 //��ǰ����ĺϣ���ȡƽ��ֵ
			 sum+= FilterData->Addr[i];
		}
		FilterData->Average = sum / (FilterData->FilterDepth);
		FilterData->Flag = 1;

		FilterData->count = 0;
	}
	else
	{
		FilterData->Flag = 0;
	}
	return 1;
}



/************************************************************************
* ��������  GetMedianValue
* ����������
*
* ���������
*     none
*
* ���������
*     none��
*
* ���أ�
*
* ��ע��
**************************************************************************/
static short GetMedianValue(const float * bArray, int iFilterLen,float *MedianData)
{

    float bTemp;
    int i,j;
    float sum = 0;
    float SeqenceArray[32];

    for(i= 0;i < iFilterLen;i++)
    {
    	SeqenceArray[i] = bArray[i];
    }
#if 0
    /*ð�ݷ� ��Ч�ʵͣ�*/
    for ( j = 0; j < iFilterLen - 1; j ++)
    {
        for ( i = 0; i < iFilterLen - j - 1; i ++)
    	{
			if (SeqenceArray[i] > SeqenceArray[i + 1]){
				bTemp = SeqenceArray[i];
				SeqenceArray[i] = SeqenceArray[i + 1];
				SeqenceArray[i + 1] = bTemp;
			}
    	}
    }
#endif
    /*���뷨����Ӧ��С��������<4K��*/
    for( i = 1; i< iFilterLen;++i)
    {
    	bTemp = SeqenceArray[i];
    	j = i - 1;
    	while((SeqenceArray[j] - bTemp > 0)&&(j>= 0))
    	{
    		SeqenceArray[j+1] = SeqenceArray[j];
    		--j;
    	}
//    	for(int j = i - 1; j>= 0; --j)
//    	{
//            if(SeqenceArray[j] > bTemp)
//            	SeqenceArray[j+1] = SeqenceArray[j];
//            else
//                break;
//    	}
    	SeqenceArray[j+1] = bTemp;
    }

    if ((iFilterLen & 1) > 0){
    	 bTemp = SeqenceArray[(iFilterLen + 1) / 2];
    }else{
    	 bTemp = (SeqenceArray[iFilterLen / 2] + SeqenceArray[iFilterLen / 2 + 1]) / 2;
    }
    *MedianData = bTemp;

    return 1;
}

/************************************************************************
* ��������  GetMeanValue
* ����������
*
* ���������
*     bArray:
*     iFilterLen:
* ���������
*      *MeanData��
* ���أ�
*     ״ֵ̬
* ��ע��
**************************************************************************/
short GetMeanValue(float * bArray, int iFilterLen,float *MeanData)
{
    float sum = 0.0;
    int j;
    for (j = 0; j < iFilterLen ; j++)
    {
    	sum += bArray[j];
    }
    *MeanData = sum/iFilterLen;
    return 1;
}


/************************************************************************
* ��������  GetMedianValue
* ����������
*
* ���������
*     none
*
* ���������
*     none��
*
* ���أ�
*
* ��ע��
**************************************************************************/
short MedianFilter(MedianFilterStructData *FilterData,uint32_t data,float *MedianData,float *MeanData)
{

	float  sum=0;
	printf("\r\n0");
	int i = 0;
	int j = 0;
	float  linear_sum = 0;
/*	if(FilterData == NULL)
	{
		SetSystemErrorLogInfo(SystemInPutParameterPointerIsNull);
		return RunError;
	}*/
	printf("\r\n1");
	for(i=1; i< FilterData->FilterDepth ;i++)
	{
		FilterData->RawDataAddr[i-1] = FilterData->RawDataAddr[i];
	}
	printf("\r\n2");
	FilterData->RawDataAddr[FilterData->FilterDepth - 1] = data; //���µ����ݷ��õ�ԭ���ݵ������
	printf("\r\n3");
	if(++FilterData->count >= FilterData->FilterDepth){

		FilterData->count = FilterData->FilterDepth;
		printf("\r\n4");
		GetMedianValue(((float *)(FilterData->RawDataAddr)),FilterData->FilterDepth,MedianData);

	}else{
		/*�ͺ��Դ���*/
		for(i=0;i< FilterData->FilterDepth ;i++)
		{
			 //��ǰ����ĺϣ���ȡƽ��ֵ
			 sum+= FilterData->RawDataAddr[i];
		}
		printf("\r\n5");
		*MedianData = sum / (FilterData->count);
	}

	printf("\r\n6");
	for(i = 1; i< FilterData->FilterDepth ;i++)
	{
		FilterData->MedianDataAddr[i-1] = FilterData->MedianDataAddr[i];
	}
	printf("\r\n7");
	FilterData->MedianDataAddr[FilterData->FilterDepth - 1] = *MedianData; //���µ����ݷ��õ���ֵFIFO�������


	for (j = 0; j < FilterData->FilterDepth ; j ++)
	{
		linear_sum += FilterData->MedianDataAddr[j];
	}

    *MeanData = linear_sum/FilterData->count;

	return 1;

}










