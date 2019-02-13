
#include <htc.h>
//#include<p18f65k90.h>
#include "def.h"
#include "spi.h"
#include "adc.h"	
/*
extern void _startup (void);

#pragma code _RESET_INTERRUPT_VECTOR = 0x1000
void _reset (void)
{
	_asm goto _startup _endasm

}
#pragma code //The program execution comes to this point when a 	timer interrupt is generated
#pragma code _HIGH_INTERRUPT_VECTOR = 0x1008
void high_ISR (void)
{
	
}
#pragma code

#pragma code _LOW_INTERRUPT_VECTOR = 0x1018
 void low_ISR (void)
{
}
#pragma code  // This function is executed as soon as the timer interrupt is generated due to timer overflow
#pragma interrupt T0_ISR
*/
void T0_ISR(void)
{ 
	if(	INTCONbits.TMR0IF == 1)
	{
		T0CONbits.TMR0ON=0;	
		TMR0H = 0x3C; // Reset the Timer0 to 0x3CAF to get a delay of 100 msec
  		TMR0L = 0xAF;
		// Check if MISO is high
		T0CONbits.TMR0ON=1;
		INTCONbits.TMR0IF = 0; //Reset the timer overflow interrupt flag
		while(SPI_MISO == 1);		
		AdcCount = Read_adc();			
	}
}

void Timer_Init(void)
{	
	TMR0H = 0x3C; // Reset the Timer0 to 0x3CAF to get a delay of 100 msec
  	TMR0L = 0xAF;
	INTCONbits.TMR0IF = 0;
	INTCONbits.TMR0IE = 1;    // TMR0 interrupt enabled
	T0CON = 0x80;    
      // Clear Timer0 overflow flag
	   // Start and set the timer to 16-bit mode, internal instruction cycle clock (Fosc/4), 1:2 prescale value	  		
}
