#include <htc.h>
//#include<p18f65k90.h>
#include <stdio.h>
#include "def.h"

void Print_UART( INT8S *buffer )
{

	while( *buffer != '\0' )
	{
		while( !TXSTA1bits.TRMT ){}
		if( *buffer == '\n' )
		{
			TXREG1 = '\r' ;
			while( !TXSTA1bits.TRMT ) ;
		}
		TXREG1 = *buffer++ ;
	}
}

void UART_Init( INT32U baudrate)
	{
	INT32U x ;
   
	x=4000000;
	x/=16;
	x/=baudrate;
	x-=1;
//(4000000/16/baudrate)-1;
	BAUDCON1bits.BRG16=0;
	SPBRG1=x;
	TRISCbits.TRISC6=0; //transmitter output
	TRISCbits.TRISC7=1; // receiver input
	TXSTA1bits.SYNC=0;// Asynchronous mode
	RCSTA1bits.SPEN=1;// serial port is enabled
	TXSTA1bits.BRGH=1;// high speed
	
	TXSTA1bits.TXEN=1; // transmitter is enabled
	RCSTA1bits.CREN=1;// receiver enabled
	sprintf( PrintStr, "UART INIT") ;
	Print_UART( PrintStr ) ;
}


