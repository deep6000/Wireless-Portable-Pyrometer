#include <htc.h>
//#include<p18f65k90.h>
#include "def.h"
#include "spi.h"

INT8U SPI_Rx_Tx(INT8U txbyte)
{
	INT8U rxbyte = 0, bitcount = 0;
	INT8U mask = 0x80;
		for ( bitcount = 0; bitcount < 8; bitcount++ )
		{
			if(txbyte & mask)
					SPI_MOSI = HIGH;
			else
					SPI_MOSI = LOW;
			SPI_CLK = HIGH;
			rxbyte <<= 1;
			if ( SPI_MISO )  rxbyte |= 1;
 			SPI_CLK = LOW;
			mask >>= 1;

		}	
	return rxbyte; 		
} 
	

			
