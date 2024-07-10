/********************************************************************
* 文件名:  ls1d6_std_adc.c
* 版本：	  V1.0
* 作者:   白一方、 李鑫
* 日期:    2021.08.31
* 说明:    本文件包含adc的所有接口函数及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/

#include "../include/ls1d_std_adc.h"
// #include"lcd.h"

int16_t g_adc_data;		//ADC数据最终值
int16_t g_adc_diff;		//ADC临时变量

int16_t MaxAdc,MinAdc,MidAdc,MaxDiff;	//ADC临时变量

/**
 * @Description: ADC_Init(void)，ADC配置初始化
 * @Input: 
 * @Output:无
 * @return {*}无
 */
void ADC_Init(void)
{
	g_adc_data = 0;
	g_adc_diff = 0;

	MaxAdc = 0;
	MaxDiff = 0;
	MinAdc = 0xFFFF;
	MidAdc = 0;

    (PMU->CHIP_CTRL) &= ~(ADC0_IEN|ADC1_IEN);   //一般上电复位默认为0；adc0、adc1作为模拟电压测量
    //(PMU->CHIP_CTRL) &= ~ADC1_IEN;   //一般上电复位默认为0；adc0、adc1作为模拟电压测量
//	(ADC->ADC_CTRL) |= 0x80		;              //SnrChn =1 使用sel指定的通道，=0 根据AfeCtrl控制自动选择
	(ADC->ADC_CTRL) &= 0x7F		;
	// (ADC->ADC_CTRL) |= ADC_DIV_2;              //二分频
	(ADC->ADC_CTRL) |= ADC_DIV_4;              //二分频

	//printf("\r ADC_CTRL  =%x \r\n",ADC->ADC_CTRL);
	//printf("\r PMU->CHIP_CTRL  =%x \r\n",PMU->CHIP_CTRL);

	/************ ADC 中断使能**************************/
	// INT->INT_EN |=ADC_INT_EN;
	CLOCK_DelayMs(1);  	//ms单位
}

/**
 * @Description: ADC 启动转化函数
 * @Input: 转化通道
 * @Output: 无
 * @return {*}
 * @param {uint32_t} channel 转化通道
 */
void ADC_Start(uint32_t channel)
{
	//asm("nop;\n");
	//printf("\r\n %s %s %d \r\n",__FILE__,__FUNCTION__,__LINE__ );
	
	// printf("\r SET ADC_CTRL  =%x \r\n",(ADC->ADC_CTRL));
	// printf("\r\n adc int ok int_out:%x \r\n",INT->INT_OUT);
	
	(ADC->ADC_CTRL) &= 0x80; 		//保持初始化设置
	asm("nop");
	(ADC->ADC_CTRL) |= ADC_DIV_4;              //时钟8分频
	(ADC->ADC_CTRL) |= channel;                //设置ADC转化通道
	(ADC->ADC_CTRL) |= ADC_RUN;                //开始AD转化

	// printf("\r SET ADC_CTRL  =%x \r\n",(ADC->ADC_CTRL));

}

/**
 * @Description: 数据采集控制
 * @Input: 采集通道号
 * @Output: AD数据采样值
 * @return {*}
 * @param {volatile char} channel
 */
uint16_t ADC_Measure(uint32_t channel)
{
	uint16_t result = ADC->ADC_DATA;
	uint32_t	tmp=0;
	uint16_t	ct =0; 
 	
	result = ADC->ADC_DATA;
	result = 0;
	 
	ADC_Start(channel);
	
	do{
		CLOCK_DelayUs(20);
		tmp = ADC->ADC_CTRL;
		
		if(ct++>100)
		{
			//printf("\r ADC_CTRL  =%x \r\n",tmp);
			break;
		}
	}
	while( tmp & ADC_RUN);
	
	result = (ADC->ADC_DATA) & 0x0FFF;         //测量结果，取12位有效数据
	
	// printf("\r QUIT ADC_CTRL  =%x \r\n",(ADC->ADC_CTRL));
//	printf("\r\nresult:=%d",result);
	return result;
}

/**
 * @Description: adc采样值转化为实际电压值，单位mv
 * @Input: adc采样数
 * @Output: 实际转化后的数据
 * @return {*}
 * @param {uint32_t} adval
 */
uint16_t ADC_Mv(uint16_t adval)
{
	return ( adval * VDD_VALUE_MV / 4096 );
}

/**
 * @Description: 插入排序
 * @Input: 
 * @Output: 
 * @return {*}
 * @param {uint32_t} num 数据缓冲
 * @param {int} n	缓冲数据大小
 */
void Insert_Sort(uint16_t *num, uint16_t n)
{
    int i,j;
	uint16_t key;
	
	for(j=1;j<n;j++)
	{
		key = num[j];
		for(i=j;i>0;i--)
		{
			if(num[i-1] > key)	
			{
				num[i] = num[i-1];
				num[i-1] = key;
			}
			else	break;
		}
	} 
	// for( t=0;t<n;t++)
	// {
	// 	for( k=t;k<n;k++)
	// 	{
	// 		if(num[k]<num[t])
	// 		{
	// 			printf("\r\n Insert_Sort ERROR BUG t=%d k=%d  num[k]=%d  num[t]=%d  \r\n",t,k,num[k],num[t]);
	// 			// for( k=0;k<n;k++) printf(" %d ",num[k]);
	// 			// printf("\r\n ");
	// 			return;
	// 		}
	// 	}
	// }
}


/**
 * @Description: AD数据预处理
 * @Input: 
 * @Output: 
 * @return {*}
 */
#if 0
uint16_t ADC_DetectPower(uint32_t channel)
{
	uint16_t  k = 0;
	uint32_t result1  = 0x00;
	uint32_t result0  = 0x00;
	uint16_t res1[10] = {0x00};
	uint16_t res0[10] = {0x00};
	
	ADC_Measure(channel);              //ADCIN
	ADC_Measure(ADC_CHANNEL_V1_0);

	for(k=0;k<10;k++)
	{
		CLOCK_DelayUs(20);//TODO
		res0[k] = ADC_Measure(channel);
		res1[k] = ADC_Measure(ADC_CHANNEL_V1_0);//2.5V
	}

	Insert_Sort(res1,10);       //将采集到的数据,从小到大排列
	Insert_Sort(res0,10);

	for(k=3;k<7;k++)            //将中间的几组数据保存
	{
		result1 += res1[k];
		result0 += res0[k];
	}
	result1 /= 4;
	result0 /= 4;

#if 1
	printf("LDO 1.0V result1:\r\n");
	for(k=0;k<10;k++)
	{
		printf("%d  ",res1[k]);
	}
	printf("\n\r");

	for(k=0;k<10;k++)
	{
		printf("%d  ",ADC_Mv(res1[k]) );
	}
	printf("\n\r");

	printf("ADC result0:");
	for(k=0;k<10;k++)
	{
		printf("%d  ",res0[k]);
	}
	printf("\n\r");

	for(k=0;k<10;k++)
	{
		printf("%d  ",ADC_Mv(res0[k]) );
	}
	printf("\n\r");

#endif
	
	uint32_t vin = REF_AD_V * result0/result1;            //计算ADC值
	
	g_adc_diff = REF_AD_V * (res0[6]-res0[3]) /result1;
	g_adc_data = vin;
	
#if 1
	// printf("result1 = %5d  result0 = %5d \n\r",result1,result0);
	printf("  result0 = %5d    \n\r",result0);

	printf("\r\n result1 = %d  result0 = %d \n\r",result1,result0);
	printf("result0/result1 = %d  \n\r",(1000*result0/result1));
	// printf("----------ADC_VIN = %5d ----------\n",VIN);
	printf("----------g_adc_data = %5d ----------\n",g_adc_data);
	printf("----------g_adc_diff = %5d ----------\n",g_adc_diff);
#endif
	
	return (uint16_t)(vin);
}
#endif

uint16_t ADC_DetectPower(uint32_t channel)
{
	uint16_t  k = 0;
	uint32_t result0  = 0x00;
	uint16_t res0[10] = {0x00};
	
//	ADC_Measure(channel);              //ADCIN

	for(k=0;k<10;k++)
	{
		CLOCK_DelayMs(2);
		res0[k] = ADC_Measure(channel);
	}

	Insert_Sort(res0,10);       //将采集到的数据,从小到大排列

	for(k=3;k<7;k++)            //将中间的几组数据保存
	{
		result0 += res0[k];
	}
	result0 /= 4;

#if 0
	printf("ADC result0:");
	for(k=0;k<10;k++)
	{
		printf("%d  ",res0[k]);
	}
	printf("\n\r");

	for(k=0;k<10;k++)
	{
		printf("%d  ",ADC_Mv(res0[k]) );
	}
	printf("\n\r");

#endif
	
	g_adc_diff = res0[6]-res0[3] ;
	g_adc_data = result0;			//计算ADC值
	
#if 0
	printf("\n\r  result0 = %5d  result0 = %5d mV  \n\r",result0,ADC_Mv(result0));
	// printf("----------g_adc_data = %5d ----------\n",g_adc_data);
	// printf("----------g_adc_diff = %5d ----------\n",g_adc_diff);
#endif
	
	return (uint16_t)result0;
}

#if 1
/**
 * @Description: AD数据最终处理
 * @Input: 
 * @Output: 
 * @return {*}
 */
void ADC_Sample(uint32_t channel)
{
	uint16_t res3[10]={0};
	uint16_t diffres1[10]={0};
	uint32_t ct=0;
	uint8_t i,j;

	for(j=0;j<10;j++)
	{
		CLOCK_DelayMs(SAMPLE_TIME);
		ADC_DetectPower(channel);
		res3[ct%10] = g_adc_data;
		diffres1[ct%10] = g_adc_diff;
		ct++;
		if(ct%10==0)
		{
			g_adc_data = 0;
			g_adc_diff = 0;

			Insert_Sort(res3,10);
			Insert_Sort(diffres1,10);

			if(MinAdc>res3[0])	MinAdc = res3[0];
			if(MaxAdc<res3[9])	MaxAdc = res3[9];
			if(MaxDiff<diffres1[9])	MaxDiff = diffres1[9];

			for(i=3;i<7;i++)            
			{
				g_adc_data += res3[i];
				g_adc_diff += diffres1[i];
			}
			g_adc_data = g_adc_data >>2;
			g_adc_diff = g_adc_diff >>2;

			ct = 0;
			
			// printf("\r\n res:"); for(i=0;i<10;i++)	printf(" %d mV",ADC_Mv(res3[i])); printf("\r\n");
			// printf("\r\n diffres1:"); for(i=0;i<10;i++)	printf(" %d mV",ADC_Mv(diffres1[i])); printf("\r\n");

			printf("\r\n chn:%d,adc:%d,g_adc_data:%d mV  g_adc_diff:%d mV /r/n",channel,g_adc_data,ADC_Mv(g_adc_data),ADC_Mv(g_adc_diff));

			// if( (MaxAdc-MinAdc)> MAX_DELT )	
			// {
			// 	ADC_Init();
			// 	j = 0;	//重新采集循环
			// 	printf("****---(MaxAdc-MidAdc)>%d mv*************\n",MAX_DELT);
			// }
			// else
			// {
				// MidAdc = (MaxAdc + MinAdc) /2;

				// if(MidAdc < BOUNDAERY_V)	g_adc_data = MidAdc - MaxDiff/2;
				// else				g_adc_data = MidAdc;

				// // printf("****---pro2-----MaxAdc = %5d  MinAdc = %5d MaxDiff = %5d*************\n",MaxAdc,MinAdc,MaxDiff);
				// printf("****---pro-----g_adc_data = %5d *************\n",ADC_Mv(g_adc_data));
				break;
			// }
	
#if 0
			printf("****1S--------res3[] ----------\n");
			for(i=0;i<10;i++)            //将中间的几组数据打印
			{
				printf(" %5d ",res3[i]);
			}
			printf("\r\n");
			printf("****1S--------diffres1[] ----------\n");
			for(i=0;i<10;i++)            //将中间的几组数据打印
			{
				printf(" %5d ",diffres1[i]);
			}
			printf("\r\n");
// #endif

			printf("****--------g_adc_data = %5d ----g_adc_diff = %5d------\n",g_adc_data,g_adc_diff);

			g_adc_data = g_adc_data - g_adc_diff/2;
			
			printf("****---pro-----g_adc_data = %5d *************\n",g_adc_data);

			g_adc_data = (g_adc_data + 4) /10 *10;

			printf("****---pro1---4S5R--g_adc_data = %5d *************\n",g_adc_data);

			printf("****---pro2-----MaxAdc = %5d  MinAdc = %5d MaxDiff = %5d*************\n",MaxAdc,MinAdc,MaxDiff);
			MidAdc = (MaxAdc + MinAdc) /2;
			printf("****---pro2-----MidAdc = %5d *************\n",MidAdc);
#endif
		}
	}
}



void ADC_Channel0InputMode(uint32_t mode)
{
	(mode == ADC_AnalogInputMode)? (CHIPCTRL &= ~0x02) : (CHIPCTRL |= 0x02);
}

#endif

















