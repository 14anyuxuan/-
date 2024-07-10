/*
 * globalDef.h
 *
 *  Created on: 2021年1月4日
 *      Author: LX
 */

#ifndef INCLUDE_GLOBALDEF_H_
#define INCLUDE_GLOBALDEF_H_
#include "../include/ls1d.h"

#define false      1
#define true       0

//#define Spi_W25Q16
#define NBWorkMode
#define KeDaWorkMode
//#define NBTestMode

#define DN20  2
//#define DN25	3

//#define DN15	1			//默认插片
//#define DN15_Bracket	1

#define NTC_ADC1	 1

#define	BEBUG_INFO()		printf("\r\n <line: %d func:%s >\r\n",__LINE__,__FUNCTION__)



extern void (*MainTask)(void);
extern void (*LastTask)(void);
/*================================函数返回状态========================================*/

#define RunOk   						  		  	(short)0
#define RunError 								  	(short)1
#define RunNull        						      	(short)2
#define RunFinish 		          					(short)3
#define SystemInPutParameterIsOutOfRange		 	(short)4
#define SystemFunctionInitFail		  			  	(short)5
#define SystemUseUninitParameter		  		  	(short)6
#define SystemUseSemaphoreParameterInitFail			(short)7
#define SystemUseSemaphoreNotCatch		  		  	(short)8
#define SystemUseTaskNotCreated		  		      	(short)9



#endif /* INCLUDE_GLOBALDEF_H_ */











