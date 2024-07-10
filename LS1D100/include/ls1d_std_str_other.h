
/********************************************************************
* �ļ���:  ls1d6_std_str_other.h
* �汾��   V1.0
* ����:    Administrator
* ����:    2021.10.18
* ˵��:    ���ļ��������ַ�������ĵײ������⺯���������궨��
* ��Ȩ:    ��о�пƣ�̫ԭ���������޹�˾
********************************************************************/
#ifndef _STR_OTHER_H_
#define _STR_OTHER_H_

#define  NULL   ((void *)0)
typedef unsigned int            size_t;

int 	strlen(const char * p);



char	* itoa(int num,char* str,int radix);

char 	* strcpy(char *dest, const char *src);
//int 	strcmp(const char *s1, const char *s2);
//char 	*strcat(char *dst, const char *src);
//int 	atoi(char *pstr);
//unsigned char my_strstr(const unsigned char *str, const unsigned char *sub_str,unsigned char num);

char    *strchr(char*s,char c);
char    *strstr(const char * str, const char * substr);
void 	*memset(void * s,int c, int count);
void 	*memcpy(void *s1, const void *s2, int n);
int 	memcmp(const void * cs,const void * ct,int count);
int 	AsciiToHex(unsigned char *dst,char *src,int len);
int 	HexToAscii(char *dst,unsigned char *src,int len,char flag);

#endif
