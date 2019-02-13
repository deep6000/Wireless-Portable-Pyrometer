//#include<p18f65k90.h>
#include<stdio.h>
#include<htc.h>
#include "def.h"
#include "I2C.h"
#include "stdlib.h"
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
#pragma code  // 
#pragma interrupt I2C_ISR
*/
void interrupt I2C_ISR(void)
{
if( PIE2bits.SSP2IE && PIR2bits.SSP2IF )    //to check if I2C interrupt is generated
{
PIR2bits.SSP2IF=0;
	switch( I2C_state)     //different states for different actions
	{
		case 0:
		{
					//	TXREG = '0' ;
						while( !TXSTA1bits.TRMT ) ;
			if(SSP2CON2bits.SEN==0)
			{
				SSP2BUF=arr[0] & 0xFE;	/*to send the address of write action (A0/A2/20) to buffer and blocking A1,A3,71 thus &ing A1/A3/71 with 11111110 will always give A0/A2/20(required for dummy write operation in receive mode*/
					{
						I2C_state=1;		// go to next state
						idx=1;	//increment count index for arr[0] to go to arr[1]
							
					}
				
			}
		}
		break;
		case 1:
		{				
					//	TXREG = '1' ;
						while( !TXSTA1bits.TRMT ) ;
			 if(SSP2CON2bits.ACKSTAT==1)			//when NACK condition occurs
			{
				SSP2CON2bits.PEN=1;	//stop condition
				I2C_state=2;		//change state
				I2Cerror=1;
			}
			else if (idx<=I2Ctxlen)			//to keep a different count for accessing arr[ ] for read and write byte functions
			{
				SSP2BUF=arr[idx++];	//go to the next address, first word, second word, data address (in case of write operation)
			}	
			else if(arr[0] & 0x01)	//if arr[0] contains address for reading a byte (&ing A1/A3 with 1 will give an output 1 and make the if condition true, thus blocking A0 and A2)
			{
				
					
					SSP2CON2bits.RSEN=1;		//generate a repeated start condition 
					I2C_state= 3;			//change the state to get the device address


			}
			else
			{
				SSP2CON2bits.PEN=1;		//stop condition
				I2C_state=2;			//change state
					I2Cerror=1;
			}
					
		}	
		break;
		
		case 2:
			{
			//	TXREG = '2' ;
				while( !TXSTA1bits.TRMT ) ;
			I2C_state=0;			//to restart the whole operation
			}
		break;
		case 3:
			{
			//	TXREG = '3' ;
				while( !TXSTA1bits.TRMT ) ;
				SSP2BUF=arr[0];		//to set the device address for read action after a repeated start was called (A1/A3/21)
				I2C_state=4 ;		//go to fetch the data to be read
			}
		break;
		case 4:
			{
					//	TXREG = '4' ;
						while( !TXSTA1bits.TRMT ) ;
				if(SSP2CON2bits.ACKSTAT==1)		//if NACK occurs
				{
					SSP2CON2bits.PEN=1;		//stop condition 
					I2C_state=2;
					I2Cerror=1;
				}
				else			
				{
					SSP2CON2bits.RCEN=1;	//enables receive mode for I2C master 
					SSP2CON2bits.ACKDT=1;		//master sends a NACK (this allows a SINGLE byte read operation for EEPROM and)
					I2C_state=5;		//go to next state
					idx=0;
				}
				
			
			}
		break;
		case 5:
			{
			//	TXREG = '5' ;
				while( !TXSTA1bits.TRMT ) ;
			//	if(arr[0]=0xA1)
				{
				//	I2Crbyte=SSP2BUF;			//save the newly received contents of buffer in a global variable for receive action
					arr[idx+3]=SSP2BUF;
					idx++;
					if(idx==I2Crxlen)
						{
							SSP2CON2bits.PEN=1;		//generate stop action
							I2C_state=2;		
							I2CRx=1;				//set a flag for reception of single byte was complete
						}
				}
			/*	else
				{
					seconds = SSP2BUF&0x7F;  		// Read seconds byte
					minutes =SSP2BUF&0x7F;  		// Read minutes byte
					hours = SSP2BUF&0x3F;   		 // Read hours byte
					day = SSP2BUF&0x3F;      		// Read year/day byte
  					weekday = SSP2BUF&0x07;  		// Read weekday/month byte
					month=SSP2BUF&0x1F;  	   	 // Read months
					year=SSP2BUF;           		 // Read year
					SSP2CON2bits.PEN=1;		//generate stop action
					I2C_state=2;		
					I2CRx=1;				//set a flag for reception of single byte was complete	
				}*/

			}
		break;
	}
}
}