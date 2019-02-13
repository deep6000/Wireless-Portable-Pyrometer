#include <htc.h>
//#include<p18f65k90.h>
#include<stdio.h>
#include "def.h"
#include "spi.h"		
#include "adc.h"
#include "uart.h"	
		
void ADC_Init(void)
{	
	INT8U val,val1,i;
	
	ANCON0 = 0x00;     //Configuring the PORT A pins as digitalI/O

	TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA2 = 1;
	TRISAbits.TRISA3 = 0;
	TRISFbits.TRISF7 = 0;

	ADC_RST = 0;
	DelayMs(200);
	ADC_RST = 1;
	DelayMs(200);
	SPI_CS= LOW;

	SPI_Rx_Tx(0x06); //RESET

	SPI_CS= HIGH;
	SPI_CS= LOW;
	 
	SPI_Rx_Tx(0x42);
	SPI_Rx_Tx(0x00);
	SPI_Rx_Tx(0x30);	

	SPI_CS= HIGH;
	SPI_CS= LOW;

	SPI_Rx_Tx(0x22);
	SPI_Rx_Tx(0x00);
	val = SPI_Rx_Tx(0xFF);

	SPI_CS= HIGH;	
	SPI_CS= LOW;

	sprintf( PrintStr, "\n%u",val ) ;
	Print_UART( PrintStr );
    

	SPI_Rx_Tx(0x43);
	SPI_Rx_Tx(0x00);
	SPI_Rx_Tx(0x60); // 10SPS

	SPI_CS= HIGH;
	SPI_CS= LOW;

	SPI_Rx_Tx(0x23);
	SPI_Rx_Tx(0x00);
	val1 = SPI_Rx_Tx(0xFF);

	SPI_CS= HIGH;
	SPI_CS= LOW;

	SPI_Rx_Tx(0x4A);
	SPI_Rx_Tx(0x00);
	SPI_Rx_Tx(0x08);
	SPI_CS= HIGH;
	SPI_CS= LOW;

	SPI_Rx_Tx(0x12);
	SPI_CS= HIGH;
	sprintf( PrintStr, "\n%u",val1 ) ;
	Print_UART( PrintStr );


}

INT16U Read_adc(void)
{
	INT16U data;
	
	SPI_CS= LOW;
	while(SPI_MISO)
	{
	}
	data = SPI_Rx_Tx(0xFF);
	data <<= 8;
	data |= SPI_Rx_Tx(0xFF);
	SPI_Rx_Tx(0x12);
	SPI_CS= HIGH;
   	return data;
}