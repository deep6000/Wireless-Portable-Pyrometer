#include <htc.h>
//#include<p18f65k90.h>
#include <stdio.h>
#include "def.h"
#include "uart.h"

void Print_UART2( INT8S *buffer )
{

	while( *buffer != '\0' )
	{
		while( !TXSTA2bits.TRMT ){}
		if( *buffer == '\n' )
		{
			TXREG2 = '\r' ;
			while( !TXSTA2bits.TRMT ) ;
		}
		TXREG2 = *buffer++ ;
	}
}

void UART2_Init( INT32U baudrate)
	{
	TRISGbits.TRISG0=0;
	PORTGbits.RG0 =1;
	INT32U x ;
   
	x=4000000;
	x/=16;
	x/=baudrate;
	x-=1;
//(4000000/16/baudrate)-1;
	BAUDCON2bits.BRG16=0;
	SPBRG2=x;
	TRISGbits.TRISG1=0; //transmitter output
	TRISGbits.TRISG2=1; // receiver input
	TXSTA2bits.SYNC=0;// Asynchronous mode
	RCSTA2bits.SPEN=1;// serial port is enabled
	TXSTA2bits.BRGH=1;// high speed
	
	TXSTA2bits.TXEN=1; // transmitter is enabled
	RCSTA2bits.CREN=1;// receiver enabled
	sprintf( PrintStr, "\nUART2 INIT");
	Print_UART( PrintStr ) ;
}
void Uart2_Write(INT8U data)
{ 	
 	while(!TXSTA1bits.TRMT);
  	TXREG2 = data;
}

void Uart2_Temp( INT16U data)
{
	Uart2_Write(data & 0xFF);
	Uart2_Write((data>>8)&0xFF);	
}
