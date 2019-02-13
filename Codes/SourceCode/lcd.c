#include <htc.h>
//#include<p18f65k90.h>
#include<stdio.h>
#include<string.h>
#include "def.h"

void LCD_Init( void )
{
	LCDCONbits.SLPEN = 1; //sleep mode inactive
	LCDCONbits.LMUX1 = 0;
	LCDCONbits.LMUX0 = 0;
	LCDPSbits.BIASMD = 0; //Bias mode static
	LCDREF = 0X98;        //internal ladder activ ,min constrast	
	LCDRL = 0XF0;         //internal ladder high power mode
	LCDSE0 = 0X9F;        // seg0-seg4, seg7
	LCDSE1 = 0XFF;        // seg8-seg12 seg14-15
	LCDSE2 = 0XFF;        // seg 16-23
 	LCDSE3 = 0XE1;        //seg 24, seg 29-31
	LCDSE4 = 0X01;        // seg 32
	LCDCONbits.LCDEN = 1; // lcd enable

		LCDDATA0 &= ~0X9F;    // clear lcd 

		LCDDATA1 &= ~0XDF; 

		LCDDATA2 &= ~0XFF;

		LCDDATA3 &= ~0XE1;

		LCDDATA4 &= ~0X01;

}

void Update_LCD( INT16U digit, INT8U x, INT8U dp )
  {
	
	INT16U Seg_code[51] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,
     				       //0,   1,  2,   3,   4,   5,   6,    7,   8,  9
					  	   0x77,0x7C,0x39,0x5E,0x79,0x71,0x00,0x00,0x00,0x00,
						   //A,   b,   C,   d,   E,  F,   extra symbols
						   0x00,0x00,0x00,0x6F,0x76,0x30,0x0E,0x70,0x38,0x1D,
     					   //extra symbols, g,  H,   i,   j,   k,   L,   M
			               0x1C,0x5C,0x73,0x63,0x50,0x6D,0x78,0X3E,0X1C,0X55,0X76,0X6E,0X5B};	
						   //N,  O,   P,   Q,   r,    S,   t,   U,   v,   W,   X , Y,  Z

	 switch(digit)
  	  {
   		case 0:
//			while(LCDPSbits.WA==0){}
			if( x == '1' )
				LCDDATA1 |= 0x40 ;
			else
				LCDDATA1 &= ~0x40 ;
//			while(LCDPSbits.WA==0){}
 			if( dp )
				LCDDATA1 |= 0x80 ;
			else
				LCDDATA1 &= ~0x80 ;

  		case 1:
//		
			LCDDATA2 = 0X00; // clear seg 1 before updating
			LCDDATA2 = Seg_code[x - '0'];
			if( dp )
				LCDDATA2 |= 0x80 ;
			else
				LCDDATA2 &= ~0x80 ;

  		case 2:

			//LCDDATA0 |= ~LCDDATA0 & 0X0F;//clearing seg0-4(2a 2b 2c 2d) before update

			LCDDATA0 &= 0xF0 ;
			LCDDATA3 &= 0x1F ;

			//LCDDATA3 |= ~LCDDATA3 & 0XE0;//clearing 29-31(2e 2f 2g) before update 
//			while(LCDPSbits.WA==0){}
 			if( dp )
				LCDDATA4 |= 0x01 ;
			else
				{
				LCDDATA4 &= ~0x01 ;
//	   			while(LCDPSbits.WA==0)
				LCDDATA0 |= Seg_code[x-'0'] & 0x0F; // updating seg 2a- 2d
  // 				while(LCDPSbits.WA==0){}
				LCDDATA3 |= ( Seg_code[x-'0'] << 1 ) & 0xE0; // updating seg 2e - 2g
				//a <<= 1;
				//	LCDDATA3 |= a;
				}

  		case 3:
	//			while(LCDPSbits.WA==0){}
				LCDDATA0 &= 0x6F ;
	//			while(LCDPSbits.WA==0){}
    			LCDDATA1 &= 0xE0 ;
				//LCDDATA1 |= z; */
				LCDDATA0 |= ( Seg_code[x-'0'] << 4 ) & 0x10;
				LCDDATA0 |= ( Seg_code[x-'0'] << 6 ) & 0x80;
				LCDDATA1 |= ( Seg_code[x-'0'] >> 2 ) & 0x1F;

	  }		
  }

void Clr_LCD(void)
	{

	
		LCDDATA0 &= ~0X9F; // clear lcd seg 0
		LCDDATA1 &= ~0XFF;
		LCDDATA2 &= ~0XFF;
		LCDDATA3 &= ~0XE1;
		LCDDATA4 &= ~0X01;

	}

void Print_Num_LCD(INT8S *str)
    {
		INT16U  i;
	for(i=0;str[i]!='\0';i++)
		{
	    	Update_LCD(i,str[i],0);		
	    }
	
}

void Print_Str_LCD(INT8S *str)
    {
		INT16U  i;
	for(i=1;str[i-1]!='\0';i++)
		{
	    	Update_LCD(i,str[i-1],0);		
	    }
	
}



