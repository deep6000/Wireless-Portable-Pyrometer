//#include<p18f65k90.h>
#include <htc.h>
#include <stdio.h>
#include "def.h"
#include "uart.h"
#include "uart2.h"
#include "spi.h"
#include "adc.h"
#include "lcd.h"
#include "temp.h"
#include "DS18B20.h"
#include "I2C.h"


void main()
{
	ANCON0=0;
	ANCON1=0;
	ANCON2=0;
	INT8S state=0;
	INT8U i;
	INT16U max;
		
	UART_Init(9600);  

	ADC_Init();
	sprintf( PrintStr, "\nADC INIT") ;
	Print_UART( PrintStr ) ;

	LCD_Init();
	sprintf( PrintStr, "\nLCD INIT") ;
	Print_UART( PrintStr ) ;

	I2C_Init ();
	sprintf( PrintStr, "\nI2C INIT") ;
	Print_UART( PrintStr ) ;                                                                                                                 
	
	UART2_Init(9600);

	INTCONbits.PEIE = 1; 
	INTCONbits.GIE = 1;
	PORTCbits.RC0=0;

	sprintf( PrintStr, "PYR") ;
	Print_Str_LCD( PrintStr ) ; 
	

	while(1)
	{	



		//while(SPI_MISO == 1);		
		AdcCount = Read_adc();
		sprintf( PrintStr, "\n AdcCount");	
		Print_UART( PrintStr ) ;
		Temp_Calc();
		sprintf( PrintStr,"\n%u",AdcCount) ;
		Print_UART( PrintStr);
		switch(state)
		{
			case 0:                             // state open
			{

				sprintf( PrintStr, "\ncase 0") ;
				Print_UART( PrintStr ) ;       
				Write_IO(0x70,0XEE);			//open on
				if(AdcCount < 21052)
				{
				state=1;					
				}	
			}
			break;

			case 1:                              // state ready
			{
				Write_IO(0x70,0XEF);
				sprintf( PrintStr, "\ncase 1") ;
				Print_UART( PrintStr ) ;       
				if(Temperature > 1000)
				{
					
					state = 2;
					
				}
				else
				{
					state = 1;
				}
			}
			break;
		
			case 2:
			{	
				Write_IO(0x70,0XED);
				sprintf( PrintStr, "\ncase 2") ;
				Print_UART( PrintStr ) ; 
				Temp_Calc();
				for(i=0;i<150;i++)
				{
					if( Temperature > 1000 && Temperature < 1700)
					{
						if(Temperature > max)
						 	max=Temperature;
						state=3;
						DelayMs(1);	
					}	
					else
					{
						Write_IO(0x70,0XEF);	
						state=4;
					}
				}
				Temperature=max;
				DelayMs(2500);
			}	
			break;
			case 3:
			{	
			    
				Write_IO(0x70,0XEF);
				Write_IO(0x70,0XE7);
				sprintf( PrintStr, "\ncase 3") ;
				Print_UART( PrintStr ) ;   
				sprintf( PrintStr,"%u",Temperature) ;
				Print_Num_LCD( PrintStr);
				Uart2_Temp(Temperature);
				DelayMs(13000);
				Write_IO(0x70,0XEF);
				if(AdcCount>3000)
				{
				state=0;
			
				}
			}
			break;
			case 4:
			{
				
				sprintf( PrintStr, "\ncase4 ") ;
				Print_UART( PrintStr ) ;       
				sprintf( PrintStr, "err") ;
				Print_Str_LCD( PrintStr ) ; 
				if(AdcCount>3000)
				{
					state=0;
					Clr_LCD();
				}
			}
			break;
		}		
	}
}

