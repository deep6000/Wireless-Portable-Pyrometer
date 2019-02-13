#include "def.h"

INT8S PrintStr[64] ;
INT16U AdcCount;
INT16U Temperature;
INT16U mV;
//INT8U FamilyCode;
INT16U ZCnt = 2, SCnt = 19276 ;
INT16U RxChar;
	
INT8U I2Crbyte;
//INT8U txrxlen;
INT8U idx;
INT8U I2C_state;
INT8U I2CRx;
INT8U I2Cerror;
INT8U I2Ctxlen;
INT8U I2Crxlen;
INT8U bcd;
INT8U bin;

 INT8U arr[20];
 INT8U I2Crbyte;
 INT8U seconds;	
 INT8U minutes;
 INT8U hours;
 INT8U day;
 INT8U weekday;
 INT8U month;
 INT8U year;


INT8U Bcd2Bin(INT8U bcd)
{
return (((bcd>>4)*10)+(bcd&0x0F));
}

INT8U Bin2bcd(INT8U bin)
{
return ((bin/10<<4)+(bin%10));
}

void DelayMs(INT16U time)
  {
      INT16U i,j;
         for(i=0;i<time;i++)
            { 
                for(j=0;j<93;j++)
                  {
                  }
            }
  }
void Delay_us_10(void)
{
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
}
void Delay_us_15(void)
{
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP");  
}
void Delay_us_20(void)
{
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
}

void Delay_us_40(void)
{
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
}
void Delay_us_50(void)
{
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP");  
}

void Delay_us_60(void)
{
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
}


void Delay_us_70(void)
{
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
}


void Delay_us_100(void)
{
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
}

void Delay_us_500(void)
{
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
	asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");	asm("NOP"); 
}
