
#include"Main.h"
//#include <stdlib.h>
//#include <time.h>

uint32 inte8m;
uint32_t key_mode;

int data_test = 3;
extern void FlashTestTask(void);
uint32 debugflag;	//����״̬���

uint32_t TotalCubicData[100] = {
	12.1, 8.9, 14.5, 6.3, 10.2, 9.4, 11.7, 7.2, 13.8, 15.3, 
	5.6, 16.6, 9.6, 11.1, 13.7, 8.3, 10.9, 12.2, 7.8, 14.1, 
	11.2, 7.5, 13.4, 5.8, 9.9, 10.5, 15.2, 12.3, 6.9, 8.7, 
	14.8, 16.4, 9.3, 13.2, 11.5, 7.1, 10.8, 8.6, 12.6, 15.7, 
	5.4, 16.1, 9.7, 14.3, 13.1, 6.7, 11.6, 7.9, 10.3, 15.6, 
	12.9, 8.2, 16.8, 5.7, 9.1, 14.7, 13.5, 6.5, 11.4, 7.3, 
	10.6, 15.1, 16.3, 9.5, 13.3, 11.9, 8.4, 10.4, 12.7, 7.7, 
	14.6, 5.5, 16.5, 9.8, 14.2, 13.0, 6.1, 11.0, 7.8, 12.4, 
	15.4, 8.0, 16.0, 9.0, 14.9, 13.6, 6.4, 11.3, 7.0, 10.7, 
	11.8, 12.8, 8.8, 15.0, 11.7, 6.2, 12.0, 7.6, 13.9, 10.1
};

int main(void)
{
	int i = 0;
 	SPI_InitTypeDef SPI_InitStruct;

	uint32 reset_source = POWER_GetResetSource();

	WDG_SetWatchDog(0x80007fff);//���ÿ��Ź�Ϊ�ʱ��

	/*����ȫ�ֱ�����ʼ��*/
	SystemClock();	//ʱ������
	GPIOInit();		/* GPIO ��ʼ�� */
	UartInit(115200,9600);
	LCD_Init(32);
	//MEASURE_DefaultInit();

	//LCD_Dis_Init();

	printf("reset,%x\r\n",reset_source);
	printf("\r\ninte8m: %d,osc32K:%x,timing:%x\r\n",inte8m,inte32K,*(uint32_t *)0x1feb0000);

	if(CLOCK_GetFlagStatus(CLOCK_HSE_FAIL) != RESET)
	{
		printf(" ext8m fail\r\n");
	}
	if(CLOCK_GetFlagStatus(CLOCK_HSE_SELECT_STATUS) == RESET)
	{
		printf(" ext8m not select\r\n");
	}
	if(CLOCK_GetFlagStatus(CLOCK_LSE_FAIL) != RESET)
	{
		printf("ext32K fail\r\n");
	}
	if(CLOCK_GetFlagStatus(CLOCK_LSE_SELECT_STATUS) == RESET)
	{
		printf("ext32K not select,try restart!\r\n");
		CLOCK_DelayS(20);
	}

	/*ʹ��ȫ���ж�*/
	EXTI_EnableInt();

// 	SPI_StructInit(&SPI_InitStruct);
// 	SPI_Init(SPI,&SPI_InitStruct);
//	printf("debug = %d\r\n",debugflag);

	StandardMeasureInit();
//	MainTask = FlashTestTask;
	uint32 inter_freq;
	i = 0;
	while(1)
	{
//	    MainTask();
		//srand(time(NULL));
		
		//TotalCubicData += (uint32_t)rand() % 10;

		printf("\r\n1D Start Success\r\n");
		//printf("\r\n%d\r\n", MEASURE_GetAmcValue());
		MeasureDataProcess();
		if(i <= 100){
			Screen_TotalCubic(TotalCubicData[i] * 100);
		}
		else{
			i = 0;			
		}
		i++;
		CLOCK_DelayS(1);
		WDG_DogFeed();			//喂狗
	}
	return 0;
}









