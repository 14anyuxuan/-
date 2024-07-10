/********************************************************************
* 文件名:  ls1d6_std_str_other.c
* 版本：	  V1.0
* 作者:    Administrator
* 日期:    2021.10.30
* 说明:    本文件包含字符处理的的所有接口函数及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#include "../include/ls1d_std_printf.h"
#include "../include/ls1d_std_str_other.h"
int memcmp(const void * cs,const void * ct,int count)
{
	const unsigned char *su1, *su2;

	for( su1 = cs, su2 = ct;count > 0; ++su1, ++su2, --count)
	{
		if (*su1 != *su2)
		{
			return 1;
		}
	}
	return 0;
}

void *memcpy(void *s1, const void *s2, int n)
{
	const unsigned char *psrc = s2;
	volatile unsigned char *pdst = s1;

	while (n-- > 0)
		*pdst++ = *psrc++;
	return s1;
}

void *memset(void * s,int c, int count)
{
	unsigned char *xs = (unsigned char *) s;

	while (count--)
		*xs++ = c;

	return s;
}
#if 0
#undef DEBUG

unsigned char my_strstr(const unsigned char *str, const unsigned char *sub_str,unsigned char num)
{
	unsigned char cont = 0;
	const unsigned char *p,*q;

	cont = 0;
	p    = str;
	q    = sub_str;

#ifdef DEBUG
	Uart0Send("\r\n my_strstr \r\n");
	Uart0Send(str);
#endif

	while(*p != '\0')
	{
		if(*p == *q)
		{
#ifdef DEBUG
	printf("\n\r str = %d sub = %d\n\r",p,q);
#endif
			while(*p && *q && *p == *q)
			{
				p++;
				q++;
				cont++;
				if(cont == num)
					return (p-str);
			}
		}
		p++;
	}
	return 0;
}

//char* strstr(char* str,char* sub){
//    int n;
//    if(*s != '\0'){
//        while(*str){
//            for(n=0;*(str + n) == *(sub + n);n++){
//                if(!*(sub + n + 1) == '\0'){
//                    return (char*) str;
//                }
//            }
//            str++;
//        }
//        return NULL;
//
//    }
//    else{
//        return (char*) str;
//    }
//}



int atoi(char *pstr)
{
	int Ret_Integer = 0;
	int Integer_sign = 1;
	if(pstr == NULL)
	{
		return 0;
	}

	if(*pstr == '-')
	{
		Integer_sign = -1;
	}
	if(*pstr == '-' || *pstr == '+')
	{
		pstr++;
	}

	while(*pstr >= '0' && *pstr <= '9')
	{
		Ret_Integer = Ret_Integer * 10 + *pstr - '0';
		pstr++;
	}
	Ret_Integer = Integer_sign * Ret_Integer;

	return Ret_Integer;
}


char *strcat(char *dst, const char *src)
{
	char *d;

	if (!dst || !src)
		return (dst);

	d = dst;
	for (; *d; d++);
	for (; *src; src++)
		*d++ = *src;
	*d = 0;
	return (dst);
}
int strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(const unsigned char *)s1 - *(const unsigned char *)--s2);
}


#endif

char * strcpy(char *dest, const char *src)
{
	char* r=dest;
	while((*dest++ = *src++)!='\0');
	return r;
}

char * strstr(const char * str, const char * substr)
{

    const char * psub = substr;
    const char * pstr = str;

    while (*pstr)
    {
//      if (*pstr != *psub)
//          continue;
        const char * tmp = pstr;
        do{
            if (*psub == '\0')
              return (char*) pstr;

         }while (*tmp++ == *psub++);
        psub = substr;
        pstr++;
    }
    return NULL;
}

char *strchr(char*s,char c)
{
	while(*s != '\0'&& *s != c)
	{
		++s;
	}
	return *s==c?s:NULL;
}





char* itoa(int num,char* str,int radix)
{/*索引表*/
    char index[]="0123456789ABCDEF";


    unsigned unum;/*中间变量*/
    int i=0,j,k;
    /*确定unum的值*/
    if(radix==10&&num<0)/*十进制负数*/
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else unum=(unsigned)num;/*其他情况*/
    /*转换*/
    do{
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;
       }while(unum);
    str[i]='\0';
    /*逆序*/
    if(str[0]=='-')
        k=1;/*十进制负数*/
    else
        k=0;

    for(j=k;j<=(i-1)/2;j++)
    {       char temp;
        temp=str[j];
        str[j]=str[i-1+k-j];
        str[i-1+k-j]=temp;
    }
    return str;
}





int strlen(const char * p)
{
    int len=0;
    while(*p++)
        len++;
    return len;
}

/*lowercase letters transform to capital letter*/
char lowtocap(char c)
{
       if((c >= 'a') && (c <= 'z'))
       {
              c = c - 32;       // 或者c = c + ('a' - 'A');
       }
       return c;
}

/*ascii string transform to 16 jinzhi Hex*/
int AsciiToHex(unsigned char *dst,char *src,int len)
{
    int length = 0;;   // 16进制的高4位和低4位
    char str[2];  //字符串的高位和低位
    int i,j;
    if((src == NULL) || (dst == NULL))
    {
       //printf("src or dest is NULL\n");
       return 0;
    }
    //个数为奇数
    if(len&0x01)
    {
    	do
    	{
        	str[0] = *src++;
            if((str[0] <= 'F') &&(str[0] >= 'A'))
            {
            	   str[0]= str[0] - 'A' + 10;

            }else if((str[0] <= 'f') &&(str[0] >= 'a'))
        	{
            	   str[0] = str[0] - 'a' + 10;

        	}else if((str[0] <= '9') &&(str[0] >= '0'))
        	{
        		   str[0] = str[0] - '0';
        	}
            length++;
            if(length & 0x01){
            	*dst = str[0];
//            	printf("a half char %d\r\n",*dst);
            }else{
            	*dst = ((*dst<<4)&0xF0)+str[0];
//            	printf("a char %d:%d\r\n",*dst,str[0]);
            	dst++;
            }
    	}while(length < len);

    }else{

        length = len >>1;
        for(i = 0; i <length;i++)
        {
           str[0] = *src++;
           str[1] = *src++;
           for(j= 0;j<2;j++)
           {
               if((str[j] <= 'F') &&(str[j] >= 'A'))
               {
            	   str[j]= str[j] - 'A' + 10;

               }else if((str[j] <= 'f') &&(str[j] >= 'a'))
        	   {
            	   str[j] = str[j] - 'a' + 10;

        	   }else if((str[j] <= '9') &&(str[j] >= '0'))
        	   {
        		   str[j] = str[j] - '0';
        	   }
           }

    //       printf("str0:= %d,str1:= %d\r\n",str[0],str[1]);
           dst[i] = ((str[0]<<4)&0xF0)+str[1];
    //       printf("i:= %d,dst:= %d\r\n",i,dst[i]);
        }
    }

    return length;
}

/*16 jinzhi Hex transform to ascii string*/
int HexToAscii(char *dst,unsigned char *src,int len,char flag)
{
       char dh,dl;  //字符串的高位和低位
       int i;
       if((src == NULL) || (dst == NULL))
       {
           //printf("src or dest is NULL\n");
           return 0;
       }
       if(len < 1)
       {
          //printf("length is NULL\n");
          return 0;
       }
       for(i = 0; i < len; i++)
       {
              dh =  (src[i] &0xF0)>>4;
              dl =  (src[i]&0x0F);

              if(dh < 10)
              {
                     dh += 0x30;
              }else{

            	  if(dh < 16)
            	  {
            		  dh = dh - 10 + 'A';
            	  }
              }

              if(dl < 10)
			  {
            	  dl += 0x30;
			  }else{

				  if(dl < 16)
				  {
					  dl = dl - 10 + 'A';
				  }
			 }
              *dst++ = dh;
              *dst++ = dl;
       }
       if(flag != 0)
       {
    	   *dst++ = '\0';
    	   return (len*2+1);
       }else
       {
    	   return (len*2);
       }
}

