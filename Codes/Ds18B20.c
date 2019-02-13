#include<htc.h>
#include <stdio.h>
#include "def.h"
#include "uart.h"
#include "adc.h"
#include "DS18B20.h"


 INT16U ScratchPad[8]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


void DQ_Init( void )
{
	DQ_MODE = 1;
}

INT8U DQ_Reset(void)
{
	INT8U valid = 0;
 	DQ_MODE = 0;// set as output;
	DQ = LOW; // Drive DQ low
	Delay_us_500(); // minimum 500us
//	DQ = HIGH;
	DQ_MODE= 1;// set as input;
	Delay_us_50();
	if ( DQ == 0 )
   {
		Delay_us_50();
		if ( DQ == 0 )
		{
			valid = 1;
		}
		else
		{
			valid=0;
		}
	/*	Delay_us_50();
		if ( DQ == 0 )
		{
			valid = 0;
		}/*/

	}
		return valid; 
}

void DQ_WriteByte( INT8U byte )
{
	INT8U j, mask ;
	for ( mask=0x01; mask!=0; mask<<=1 )
	{
		DQ_MODE=0;
		asm("NOP");
		if(byte & mask)
		{
			DQ=0;
			asm("NOP");  // trec
			DQ=1;
		}
		else
		{
			DQ=0;
			asm("NOP");	 //trec
			DQ=0;
		}
		Delay_us_60();
		DQ_MODE=1;
		asm("NOP");	
	}		
	DQ_MODE=1;
	asm("NOP");			
}


void DQ_ReadByte(void)
{
	INT8U valid ;
	INT8U FamilyCode=0;
	INT8U i, j, byte = 0, rbit = 0 ;
	INTCONbits.GIE = 0;
	valid=DQ_Reset();
		
	if( !valid )
	{
	INTCONbits.GIE = 1;
		return   ;
	}
	asm("NOP");
	asm("NOP");
	DQ_WriteByte(0x33); 
	while(rbit < 8)	
	{
    byte >>= 1 ;
	DQ_MODE=0;
	DQ=0;
	asm("NOP");
	DQ_MODE=1;
	asm("NOP");	
	//Delay_us_15();
	if(DQ)
		byte |= 0x80 ;

	rbit++ ;
	if( rbit == 8 )
	{
	byte= FamilyCode;
	}	

	Delay_us_60();
	asm("NOP");
}
	INTCONbits.GIE = 1;
	sprintf( PrintStr, "\nFamily Code") ;
	Print_UART( PrintStr ) ;
	sprintf( PrintStr, "%u",FamilyCode) ;
	Print_UART( PrintStr ) ;
	}


void WaitBusy( void )
{
	INT8U i, j, byte = 0 ;

	//RoomTErr = 0 ;
//	Timeout1820 = 0 ;
	
	while( byte != 0xFF )								// 480
	{
		DQ_MODE=0; 
		asm( "NOP" ) ;
		DQ = 0 ;
		/******* 1us *******/
		asm( "NOP" ) ;
		DQ_MODE=1 ;
		Delay_us_10();					
		if( DQ )
		{
			byte <<= 1 ;
			byte |= 1 ;
		}
		Delay_us_40();
		
		asm( "NOP" ) ;

/*		//printf( "\n\rTimeoutcntr2 = %d", Timeoutcntr ) ;
		if( Timeout1820++ >= RTTIMEOUT )
		{
			Timeout1820 = 0 ;
			RoomTErr = 1 ;
			return ;
		}*/
	}
}	

void ReadScratchPad(void)
{
	INT8U i;
	INT8U j;
 	INT8U byte = 0, NumBytes = 0, rbit = 0 ;
	
//	RoomTErr = 0 ;
//	Timeout1820 = 0 ;	
	while( NumBytes != 9 )							// 540
	{
		byte >>= 1 ;
		DQ_MODE=0;
		//asm( "NOP" ) ;
		DQ=0 ;
		asm( "NOP" ) ;
		DQ_MODE=1 ;
		asm("NOP");
	//	Delay_us_15();
		if( DQ )
			byte |= 0x80 ;
		rbit++ ;
		if( rbit == 8 )
		{
			ScratchPad[ NumBytes++ ] = byte ;
			rbit = 0 ;
			byte = 0 ;
		}
		Delay_us_60();
		asm( "NOP" ) ;
		//printf( "\n\rTimeoutcntr1 = %d", Timeoutcntr ) ;
	}
}


void CalcRoomT( void )
{
	INT16U temp, temp2 ;

	char str[32];

	/*Print_UART( "\nScratchPad[1] = " ) ;
	Print_UART( NumToStr(ScratchPad[1], 0, 2, 3, str,0 ) ) ;
	Print_UART( "\nScratchPad[0] = " ) ;
	Print_UART( NumToStr(ScratchPad[0], 0, 2, 3, str,0 ) ) ;
 	Print_UART( "\nScratchPad[7] = " ) ;
	Print_UART( NumToStr(ScratchPad[7], 0, 2, 3, str,0 ) ) ;
	Print_UART( "\nScratchPad[6] = " ) ;
	Print_UART( NumToStr(ScratchPad[6], 0, 2, 3, str,0 ) ) ;
*/
//		sprintf( str, "\nSP[0] = %d", ScratchPad[0] ) ; Print_UART( str ) ;
//		sprintf( str, "\nSP[1] = %d", ScratchPad[1] ) ; Print_UART( str ) ;
//		sprintf( str, "\nSP[6] = %d", ScratchPad[6] ) ; Print_UART( str ) ;
//		sprintf( str, "\nSP[7] = %d", ScratchPad[7] ) ; Print_UART( str ) ;

	temp = ( ( (INT16U)ScratchPad[1] << 8 ) | (INT16U)ScratchPad[0] )  ;
	temp >>= 1 ;
	
	temp *= 100 ;
	temp -= 25 ;
	//sprintf( str, "\ntemp = %d", temp ) ; printUART( str ) ;
	temp2 = ScratchPad[7] - ScratchPad[6] ;
	temp2 *= 100 ;
	temp2 /= ScratchPad[7] ;
	//sprintf( str, "\ntemp2 = %d", temp2 ) ; printUART( str ) ;
	temp += temp2 ;
	temp /= 10 ;
    sprintf( PrintStr, "\nTemperature is") ;
	Print_UART( PrintStr ) ;
	sprintf( PrintStr, "%u",temp) ;
	Print_UART( PrintStr ) ;
}

INT8U Read_RoomT_Fun1( void )		// 10 ms
{
	INT8U valid ;
	INTCONbits.GIE = 0;
	//valid =DQ_Reset();
	
 	DQ_WriteByte( 0xCC ) ;			// skip rom
	asm("NOP");
	asm("NOP");
	DQ_WriteByte( 0x4E ) ;	//0x4E ) ;		// write scratchpad
	asm("NOP");
	asm("NOP");
	DQ_WriteByte( 0x00 ) ;
	asm("NOP");
	asm("NOP");
	DQ_WriteByte( 0x00 ) ;
	asm("NOP");
	asm("NOP");
	DQ_WriteByte( 0x1F ) ;
	asm("NOP");
	asm("NOP");
	valid = DQ_Reset();
	
	if( !valid )
	{
	INTCONbits.GIE = 1;
	return valid ;
	}
}
INT8U Read_RoomT_Fun2( void )
{
		INT8U valid ;
	INTCONbits.GIE = 0;
	valid =DQ_Reset();
	
	if( !valid )
	{
	INTCONbits.GIE = 1;
	return valid ;
	}	
	DQ_WriteByte( 0xCC ) ;			// skip rom
	asm("NOP");
	asm("NOP");
	DQ_WriteByte( 0x44 ) ;			// start of conversion 01000100
	INTCONbits.GIE = 1;	
	DelayMs(200);

	return valid ;

}

INT8U Read_RoomT_Fun3( void )		// 10 ms
{//	INT8U temp1, temp2;
//	INT16U temp;
	INT8U valid ;
	INTCONbits.GIE = 0;	
	WaitBusy() ;
	/*valid = DQ_Reset();;

	if( !valid )
	{
		INTCONbits.GIE = 1;
		return valid ;
	}	*/
	DQ_WriteByte(0xCC); //skip ROM commands
	asm("NOP");
	asm("NOP");
	DQ_WriteByte(0xBE); // Read scratchpad
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	ReadScratchPad() ;
//	temp1 = DQ_ReadByte();
//	temp2 = DQ_ReadByte();
	/*
	temp = ( ( (INT16U)temp2 << 8 ) | (INT16U)temp1 )  ;
    sprintf( PrintStr, "\nTemperature is") ;
	Print_UART( PrintStr ) ;
	sprintf( PrintStr, "%u",temp) ;
	Print_UART( PrintStr ) ; */
	valid = DQ_Reset() ;
	INTCONbits.GIE = 1;
//	if( !valid )	
//	return( valid & !RoomTErr ) ;	
	CalcRoomT() ;	
	return valid ;

}


