//#include<p18f65k90.h>

#include<htc.h>
#include "def.h"
#include "I2C.h"

//Foreground

void I2C_Init (void)
{
	TRISDbits.TRISD6=1;       	//Set SCL pin as input
	TRISDbits.TRISD5=1;    	//Set SDA pin as input
  	SSP2CON1 = 0x08;		//to enable the master mode
	SSP2ADD = 0x13 ;		/* 50kHz @ 4Mhz Fosc, SSP2ADD = (FOSC/(4*c))-1*/
  	SSP2STAT = 0;		//choose default condition
	PIE2bits.SSP2IE=1;			//enabe the I2C peripheral interrupt
	SSP2CON1bits.SSPEN=1; 	 //enable I2C 
//	INTCONbits.GIE=1;		//enable global interrupt
//	INTCONbits.PEIE=1;
	
}


void WriteEE_byte ( INT8U addr, INT8U  data)
{
	arr[0]=0xA0;			//device address for write byte-10100000
	arr[1]=addr>>8;		//word address- LSB 
	arr[2]=addr&0xFF;		//"& 0xFF” effectively masks the variable so it leaves only the value in the last 8 bits, and ignores all the rest of the bits- MSB
	arr[3]=data;		//send the data to be written
	//txrxlen=3;			//count to access arr[]
I2Ctxlen=3;
	I2Crxlen=0;
	SSP2CON2bits.SEN=1;            //generating start condition	
}


INT8U ReadEE_byte ( INT8U addr)		//random read a byte
{
	arr[0]=0xA1;		//device address for read byte-10100001
	arr[1]=addr>>8;
	arr[2]=addr&0xFF;
//	txrxlen=2;
	I2CRx=0;
	I2Cerror=0;
	I2Ctxlen=2;
	I2Crxlen=1;
	SSP2CON2bits.SEN=1;	
	while(!I2CRx||!I2Cerror);
	I2Crbyte=arr[3];
	return(I2Crbyte);
}


void WriteRTC_time ( INT8U addr, INT8U data)
{
	arr[0]=0xA2;			//device address for write byte-10100010
	arr[1]=addr;		//send register address
	arr[2]=Bin2Bcd(data);		//send the data to be written
	I2Ctxlen=6;			//count to access arr[]
	I2Crxlen=0;
	SSP2CON2bits.SEN=1;
}


INT8U ReadRTC_time ( INT8U addr)
{
	arr[0]=0xA3;			//device address for read byte-10100011
	arr[1]=addr;		//send register address		
//	txrxlen=1;			//count to access arr[]
	I2CRx=0;
	I2Cerror=0;
	I2Ctxlen=1;
	I2Crxlen=7;
	SSP2CON2bits.SEN=1;	
	while(!I2CRx||!I2Cerror);

	seconds = Bcd2Bin(arr[3]&0x7F);  		// Read seconds byte
	minutes =Bcd2Bin(arr[4]&0x7F);  		// Read minutes byte
	hours = Bcd2Bin(arr[5]&0x3F);   		 // Read hours byte
	day = Bcd2Bin(arr[6]&0x3F);      		// Read year/day byte
  	weekday = Bcd2Bin(arr[7]&0x07);  		// Read weekday/month byte
	month=Bcd2Bin(arr[8]&0x1F);  	   	 // Read months
	year=Bcd2Bin(arr[9]);           		 // Read year


}

void Write_IO ( INT8U addr, INT8U data)
{
	//TXREG = 'I' ;
	while( !TXSTA1bits.TRMT ) ;
	arr[0]=0x70;			//device address for write byte-01000000		
	arr[1]=data;		//send the data to be written
	//txrxlen=1;			//count to access arr[]
	I2Ctxlen=1;
	I2Crxlen=0;
	SSP2CON2bits.SEN=1;
	
}