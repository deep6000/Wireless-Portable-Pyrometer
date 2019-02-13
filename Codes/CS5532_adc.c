
#define	ADCCMDSYNC1		0xFF
#define	ADCCMDSYNC0		0xFE

#define OFFSETREG1					0x01
#define GAINREG1						0x02
#define	ADCCONFIGREG					0x03
#define	CMDSETUP12					0x05
#define OFFSETREG2					0x11
#define GAINREG2						0x12
#define	CMDSETUP34					0x15
#define	CMDSETUP56					0x25
#define	CMDSETUP78					0x35
#define CMDCONVERT0					0x80	// SETUP1
#define CMD_SETUP1_OFFSET_SELFCAL	0x81
#define CMD_SETUP1_GAIN_SELFCAL		0x82
#define CMD_SETUP1_OFFSET_SYSCAL	0x85
#define CMD_SETUP1_GAIN_SYSCAL		0x86
#define CMDCONVERT1					0x88	// SETUP2
#define CMD_SETUP2_OFFSET_SELFCAL	0x89
#define CMD_SETUP2_GAIN_SELFCAL		0x8A
#define CMD_SETUP2_OFFSET_SYSCAL	0x8D
#define CMD_SETUP2_GAIN_SYSCAL		0x8E
#define CMDCONVERT2					0x90	// SETUP3
#define CMDCONVERT3					0xB0	// SETUP4

/*********** CSR bits ****************/
#define	ADCCHAN1		0L
#define	ADCCHAN2		1L
#ifdef ADC_4CHAN
#define	ADCCHAN3		2L
#define	ADCCHAN4		3L
#endif

#define GAIN_1			0L
#define GAIN_2			1L
#define GAIN_4			2L
#define GAIN_8			3L
#define GAIN_16			4L
#define GAIN_32			5L
#define GAIN_64			6L

#define FRS1_OWR_25		2L
#define FRS1_OWR_12_5	3L
#define FRS1_OWR_6_25	4L

#define UNIPOLAR		1L
#define BIPOLAR			0L

#define IMMEDIATE_CONV	0L
#define DELAYED_CONV	1L

#define USE_CH1_OG_REG	0L
#define USE_CH2_OG_REG	1L
#define USE_CH3_OG_REG	2L
#define USE_CH4_OG_REG	3L

/**************************************/

/************* CONFIG bits *************/

#define IP_NORMAL	0L
#define IP_SHORT	1L

#define VREF_1_25	1L
#define VREF_25_VA	0L

#define USE_CS_OG	0L
#define USE_OG_OG	1L

#define NO_FRS	0L
#define USE_FRS	1L

/**************************************/
#define	ADCREADREG		0x08
#define	ADCWRITEREG		0x00

#define SINGLE			0x00
#define CONTINUOUS		0x40

#define OFFSET	0x01
#define GAIN	0x02

#define REG1	0x00
#define REG2	0x10

#define NORMAL	0
#define SHORT	1

#define INPUT_NORMAL	0x08000000
#define INPUT_SHORT	0xF7FFFFFF

/************************* Config bits *****************************/
#define	ADCRESET			0x20000000
#define	ADCRESETVALID		0x10000000
//#define	ADCINPUTSHORT		0x08000000
#define	ADCVREF2V5ORLESS	0x02000000
//#define	ADCUSEALTCALREG		0x00100000
//#define	ADCUSE5BY6FILT		0x00080000
#define	ADCRESETCLEAR		0x00000000

/************************* Channel Setup bits *****************************/

#define CMDRDDATA	0x00

//#define ADC_4CHAN
#define USE_ADC2
#define USE_ADC3

#define ADC1	0
#define ADC2	1
#define ADC3	2

#define ADC1CS_HI		PortC |= 0x0002 ; PORTC = PortC ;		//RC1
#define ADC1CS_LO	PortC &= 0xFFFD ; PORTC = PortC ;		//RC1
#define ADC2CS_HI		PortC |= 0x0004 ; PORTC = PortC ;		//RC2
#define ADC2CS_LO	PortC &= 0xFFFB ; PORTC = PortC ;		//RC2
#define ADC3CS_HI		PortC |= 0x0008 ; PORTC = PortC ;		//RC3
#define ADC3CS_LO	PortC &= 0xFFF7 ; PORTC = PortC ;		//RC3

#define CSA1BUFFLEN	16
#define CSA2BUFFLEN	16
#define PTLBUFFLEN	16
#define ROOMTEMPBUFFLEN	8

volatile INT8U ADCInit = 0, SPIBusy  = 0;

INT32U ADC1Config_Bits = 0, ADC2Config_Bits = 0, ADC3Config_Bits = 0, ADC1Setup12_Bits = 0, ADC2Setup12_Bits = 0, ADC3Setup12_Bits  = 0;
INT32U ADC1Offset_Bits = 0, ADC2Offset_Bits = 0, ADC3Offset_Bits  = 0;
INT32U ADC1Gain_Bits = 0, ADC2Gain_Bits = 0, ADC3Gain_Bits  = 0;
INT32U FourthCount  = 0;
//volatile INT16U ADC1Tim, ADC2Tim, ADC3Tim, ADC1Cnt, ADC2Cnt, ADC3Cnt ;
volatile INT16U *CSA1BuffSetPtr, *CSA2BuffSetPtr, *PTLBuffSetPtr/*, *RoomTempBuffSetPtr*/ ;
volatile INT16U *CSA1BuffGetPtr, *CSA2BuffGetPtr, *PTLBuffGetPtr/*, *RoomTempBuffGetPtr*/ ;
volatile INT16U CSA1Buff[CSA1BUFFLEN], CSA2Buff[CSA2BUFFLEN], PTLBuff[PTLBUFFLEN]/*, RoomTempBuff[ROOMTEMPBUFFLEN]*/ ;

//INT8U AdcntErr = 0 ;

void SelectADC( INT8U ADCNo )
{
	if( ADCNo == ADC1 )		{ ADC1CS_LO }
	else if( ADCNo == ADC2 )	{ ADC2CS_LO }
	else if( ADCNo == ADC3 )	{ ADC3CS_LO }
}

void DeSelectADC( INT8U ADCNo )
{
	if( ADCNo == ADC1 )		{ ADC1CS_HI }
	else if( ADCNo == ADC2 )	{ ADC2CS_HI }
	else if( ADCNo == ADC3 )	{ ADC3CS_HI }
}
	
INT8U ADCComm( INT8U TxChar )
{
	INT8U i, RxChar = 0 ;
	
	for( i = 0 ; i < 8 ; i++ )
	{
		MOSI = ( TxChar & 0x80 ) ? 1 : 0 ;
		TxChar <<= 1 ;
		SCK = 1 ;
		RxChar <<= 1 ;
		RxChar |= MISO ? 1 : 0 ;
		SCK = 0 ;
	}	
	return( RxChar ) ;
}
//9881478230
void WriteReg( INT8U ADCNo, INT8U Reg, INT32U Data )
{
	INT8U i ;
	
	SPIBusy = TRUE ;
	SelectADC( ADCNo ) ;
	
	ADCComm( Reg ) ;
	for( i = 0 ; i < 4 ; i++ )
	{
		ADCComm( ( Data >> 24 ) & 0xFF ) ;
		Data <<= 8 ;
	}
	
	DeSelectADC( ADCNo ) ;
	SPIBusy = FALSE ;
}

INT32S ReadReg( INT8U ADCNo, INT8U Reg )
{
	INT8U i ;
	INT32S Data = 0 ;
	
	SPIBusy = TRUE ;
	SelectADC( ADCNo ) ;
	
	ADCComm( Reg | ADCREADREG ) ;
	for( i = 0 ; i < 4 ; i++ )
	{
		Data <<= 8 ;
		Data |= ADCComm( 0 ) ;
	}
	
	DeSelectADC( ADCNo ) ;
	SPIBusy = FALSE ;
	
	return( Data ) ;
}

INT8U UARTReadChar( void ) ;
void InitADCPins( void )
{
	AD1PCFGHbits.PCFG16 = 1 ;			// use digital function of the pin RC1(AN16)
	TRISCbits.TRISC1 = 0 ;			// ADC1 CS
	AD1PCFGHbits.PCFG17 = 1 ;			// use digital function of the pin RC2(AN17)
	TRISCbits.TRISC2 = 0 ;			// ADC2 CS
	AD1PCFGHbits.PCFG18 = 1 ;			// use digital function of the pin RC3(AN18)
	TRISCbits.TRISC3 = 0 ;			// ADC3 CS

	ADC1CS_HI ;
	ADC2CS_HI ;
	ADC3CS_HI ;
}

void InitADC_CommandMode( INT8U ADCNo )
{
	INT8U i ;
	
	if( ADCNo == ADC1 ) 		{ ADC1CS_LO }
	else if( ADCNo == ADC2 )	{ ADC2CS_LO }
	else if( ADCNo == ADC3 )	{ ADC3CS_LO }
	
	for( i = 0; i < 15; i++ )
		ADCComm( ADCCMDSYNC1 ) ;
	
/*	if( ADCNo == ADC1 )		{ ADC1CS_HI }
	else if( ADCNo == ADC2 )	{ ADC2CS_HI }
	else if( ADCNo == ADC3 )	{ ADC3CS_HI }
	
	if( ADCNo == ADC1 )		{ ADC1CS_LO }
	else if( ADCNo == ADC2 )	{ ADC2CS_LO }
	else if( ADCNo == ADC3 )	{ ADC3CS_LO }
*/	
	ADCComm( ADCCMDSYNC0 ) ;
	
	if( ADCNo == ADC1 )		{ ADC1CS_HI }
	else if( ADCNo == ADC2 )	{ ADC2CS_HI }
	else if( ADCNo == ADC3 )	{ ADC3CS_HI }
}	

#ifndef ADC_RESET_REVISION
void ResetADC( void )
{
	INT16U i ;
	INT32U Data ;
	
	SPIBusy = TRUE ;
	Data = ADCRESET ;
	
	{ ADC1CS_LO }
	{ ADC2CS_LO }
	{ ADC3CS_LO }
	
	ADCComm( ADCCONFIGREG ) ;
	
	for( i = 0 ; i < 4 ; i++ )
	{
		ADCComm( ( Data >> 24 ) & 0xFF ) ;
		Data <<= 8 ;
	}
	
	{ ADC1CS_HI }
	{ ADC2CS_HI }
	{ ADC3CS_HI }
	
	for( i = 0; i < 1000; i++ ) ;
	
	Data = ADCRESETCLEAR ;
	
	{ ADC1CS_LO }
	{ ADC2CS_LO }
	{ ADC3CS_LO }
	
	ADCComm( ADCCONFIGREG ) ;
	
	for( i = 0 ; i < 4 ; i++ )
	{
		ADCComm( ( Data >> 24 ) & 0xFF ) ;
		Data <<= 8 ;
	}
	
	{ ADC1CS_HI }
	{ ADC2CS_HI }
	{ ADC3CS_HI }
	
	SPIBusy = FALSE ;
}

INT8U CheckReset( INT8U ADCNo )
{
	INT32U Reg ;
	
	Reg = ReadReg( ADCNo, ADCCONFIGREG ) ;					// check RV bit
	return( ( Reg & ADCRESETVALID ) ? 0 : 1 ) ;
}
#endif
void SetADCConfig( void )
{
//	INT32U Reg ;
//	char str[64] ;
	
	WriteReg( ADC1, ADCCONFIGREG, ADC1Config_Bits ) ;
//	printUART( "\nw1" ) ;
//	printHEX( ADC1Config_Bits, str, 32 ) ;
	WriteReg( ADC2, ADCCONFIGREG, ADC2Config_Bits ) ;
//	printUART( "\nw2" ) ;
//	printHEX( ADC2Config_Bits, str, 32 ) ;
	WriteReg( ADC3, ADCCONFIGREG, ADC3Config_Bits ) ;
//	printUART( "\nw3" ) ;
//	printHEX( ADC3Config_Bits, str, 32 ) ;
	
//	Reg = ReadReg( ADC1, ADCCONFIGREG ) ;					// check RV bit
//	printUART( "\nr1" ) ;
//	printHEX( Reg, str, 32 ) ;
//	Reg = ReadReg( ADC2, ADCCONFIGREG ) ;					// check RV bit
//	printUART( "\nr2" ) ;
//	printHEX( Reg, str, 32 ) ;
//	Reg = ReadReg( ADC3, ADCCONFIGREG ) ;					// check RV bit
//	printUART( "\nr3" ) ;
//	printHEX( Reg, str, 32 ) ;
}

void SetADCSetup( void )
{
//	INT32U Reg ;
//	char str[64] ;
	
	WriteReg( ADC1, CMDSETUP12, ADC1Setup12_Bits ) ;
//	printUART( "\nw1" ) ;
//	printHEX( ADC1Setup12_Bits, str, 32 ) ;
	WriteReg( ADC2, CMDSETUP12, ADC2Setup12_Bits ) ;
//	printUART( "\nw2" ) ;
//	printHEX( ADC2Setup12_Bits, str, 32 ) ;
	WriteReg( ADC3, CMDSETUP12, ADC3Setup12_Bits ) ;
//	printUART( "\nw3" ) ;
//	printHEX( ADC3Setup12_Bits, str, 32 ) ;
	
//	Reg = ReadReg( ADC1, CMDSETUP12 ) ;					// check RV bit
//	printUART( "\nr1" ) ;
//	printHEX( Reg, str, 32 ) ;
//	Reg = ReadReg( ADC2, CMDSETUP12 ) ;					// check RV bit
//	printUART( "\nr2" ) ;
//	printHEX( Reg, str, 32 ) ;
//	Reg = ReadReg( ADC3, CMDSETUP12 ) ;					// check RV bit
//	printUART( "\nr3" ) ;
//	printHEX( Reg, str, 32 ) ;
}

void ResetCSA1Buff( void )
{
	CSA1BuffGetPtr = CSA1BuffSetPtr = CSA1Buff + CSA1BUFFLEN - 1 ;
//	CSA1BuffCnt = 0 ;
}

void ResetCSA2Buff( void )
{
	CSA2BuffGetPtr = CSA2BuffSetPtr = CSA2Buff + CSA2BUFFLEN - 1 ;
//	CSA2BuffCnt = 0 ;
}

void ResetPTLBuff( void )
{
	PTLBuffGetPtr = PTLBuffSetPtr = PTLBuff + PTLBUFFLEN - 1 ;
//	PtlBuffCnt = 0 ;
}

void FlushAll( void )
{
	ResetCSA1Buff() ;
	ResetCSA2Buff() ;
	ResetPTLBuff() ;
}	
#ifndef ADC_RESET_REVISION
void ADC1_Periodic_Reset( void )
{
	InitADC_CommandMode( ADC1 ) ;
	WriteReg( ADC1, ADCCONFIGREG, ADC1Config_Bits ) ;
	WriteReg( ADC1, CMDSETUP12, ADC1Setup12_Bits ) ;
	
	SelectADC( ADC1 ) ;
	ADCComm( CMDCONVERT0 | CONTINUOUS ) ;
	DeSelectADC( ADC1 ) ;
	
	ResetCSA1Buff() ;
	//UARTputChar( 'R' ) ;
	//UARTputChar( 'S' ) ;
	//UARTputChar( 'T' ) ;
	//UARTputChar( '1' ) ;
}

void ADC2_Periodic_Reset( void )
{
	InitADC_CommandMode( ADC2 ) ;
	WriteReg( ADC2, ADCCONFIGREG, ADC2Config_Bits ) ;
	WriteReg( ADC2, CMDSETUP12, ADC2Setup12_Bits ) ;
	
	SelectADC( ADC2 ) ;
	ADCComm( CMDCONVERT0 | CONTINUOUS ) ;
	DeSelectADC( ADC2 ) ;
	
	ResetCSA2Buff() ;
//	UARTputChar( 'R' ) ;
//	UARTputChar( 'S' ) ;
//	UARTputChar( 'T' ) ;
//	UARTputChar( '2' ) ;
}

void ADC3_Periodic_Reset( void )
{
	InitADC_CommandMode( ADC3 ) ;
	WriteReg( ADC3, ADCCONFIGREG, ADC3Config_Bits ) ;
	WriteReg( ADC3, CMDSETUP12, ADC3Setup12_Bits ) ;
	
	SelectADC( ADC3 ) ;
	ADCComm( CMDCONVERT0 | CONTINUOUS ) ;
	DeSelectADC( ADC3 ) ;
	
	ResetPTLBuff() ;
	//UARTputChar( 'R' ) ;
	//UARTputChar( 'S' ) ;
	//UARTputChar( 'T' ) ;
	//UARTputChar( '3' ) ;
}
#endif
#ifdef ADC_RESET_REVISION
INT8U ResetADC_Revised( void )
{
	INT16U i ;
	INT32U Data ;
	INT8U err = 0 ;
		
	SPIBusy = TRUE ;

	Data = ADCRESET ;
	
	{ ADC1CS_LO }
	{ ADC2CS_LO }
	{ ADC3CS_LO }
	
	ADCComm( ADCCONFIGREG ) ;
	
	for( i = 0 ; i < 4 ; i++ )
	{
		ADCComm( ( Data >> 24 ) & 0xFF ) ;
		Data <<= 8 ;
	}
	
	{ ADC1CS_HI }
	{ ADC2CS_HI }
	{ ADC3CS_HI }
	
	for( i = 0; i < 1000; i++ ) ;
	
	{ ADC1CS_LO }
	Data = ReadReg( ADC1, ADCCONFIGREG ) ;					// check RV bit
	{ ADC1CS_HI }
	if( ( Data & ADCRESETVALID ) == 0 )
		err++ ;
		
	{ ADC2CS_LO }
	Data = ReadReg( ADC2, ADCCONFIGREG ) ;					// check RV bit
	{ ADC2CS_HI }
	if( ( Data & ADCRESETVALID ) == 0 )
		err++ ;
	
	{ ADC3CS_LO }
	Data = ReadReg( ADC3, ADCCONFIGREG ) ;					// check RV bit
	{ ADC3CS_HI }
	if( ( Data & ADCRESETVALID ) == 0 )
		err++ ;
		
	Data = ADCRESETCLEAR ;
	
	{ ADC1CS_LO }
	{ ADC2CS_LO }
	{ ADC3CS_LO }
	
	ADCComm( ADCCONFIGREG ) ;
	
	for( i = 0 ; i < 4 ; i++ )
	{
		ADCComm( ( Data >> 24 ) & 0xFF ) ;
		Data <<= 8 ;
	}
	
	{ ADC1CS_HI }
	{ ADC2CS_HI }
	{ ADC3CS_HI }
	
	{ ADC1CS_LO }
	Data = ReadReg( ADC1, ADCCONFIGREG ) ;					// check RV bit
	{ ADC1CS_HI }
	if( ( Data & ADCRESETVALID ) != 0 )
		err++ ;
		
	{ ADC2CS_LO }
	Data = ReadReg( ADC2, ADCCONFIGREG ) ;					// check RV bit
	{ ADC2CS_HI }
	if( ( Data & ADCRESETVALID ) != 0 )
		err++ ;
	
	{ ADC3CS_LO }
	Data = ReadReg( ADC3, ADCCONFIGREG ) ;					// check RV bit
	{ ADC3CS_HI }
	if( ( Data & ADCRESETVALID ) != 0 )
		err++ ;
	
	SPIBusy = FALSE ;
	
	return err ;
}	

#endif
INT8U InitADC( void )
{
#ifndef ADC_RESET_REVISION
INT8U i ;
#endif
	INT8U ADC_Error = 0 ;
		
	InitADCPins() ;
	
	InitADC_CommandMode( ADC1 ) ;
	InitADC_CommandMode( ADC2 ) ;
	InitADC_CommandMode( ADC3 ) ;

#ifdef ADC_RESET_REVISION
	ADC_Error = ResetADC_Revised() ;
#else		
	ResetADC() ;
	
	for( i = ADC1 ; i <= ADC3 ; i++ )
		ADC_Error |= CheckReset( i ) << i ;
#endif		
	if( ADC_Error )
		return ADC_Error ;
	
	ADC1Config_Bits = ( IP_NORMAL << 27 ) | ( VREF_1_25 << 25 ) | ( USE_CS_OG << 20 ) | ( USE_FRS << 19 ) ;	// input not internally
	ADC2Config_Bits = ( IP_NORMAL << 27 ) | ( VREF_1_25 << 25 ) | ( USE_CS_OG << 20 ) | ( USE_FRS << 19 ) ;
	ADC3Config_Bits = ( IP_NORMAL << 27 ) | ( VREF_1_25 << 25 ) | ( USE_CS_OG << 20 ) | ( USE_FRS << 19 ) ;
	
	/*
	ADC1Setup12_Bits = ( ADCCHAN1 << 30 ) | ( GAIN_16 << 27 ) | ( FRS1_OWR_6_25 << 23 ) | ( BIPOLAR << 22 ) | ( IMMEDIATE_CONV << 19 ) | ( USE_CH1_OG_REG << 16 ) | ( ADCCHAN1 << 14 ) | ( GAIN_1 << 11 ) | ( FRS1_OWR_6_25 << 7 ) | ( BIPOLAR << 6 ) | ( IMMEDIATE_CONV << 3 ) | USE_CH1_OG_REG ;
	ADC2Setup12_Bits = ( ADCCHAN1 << 30 ) | ( GAIN_16 << 27 ) | ( FRS1_OWR_6_25 << 23 ) | ( BIPOLAR << 22 ) | ( IMMEDIATE_CONV << 19 ) | ( USE_CH1_OG_REG << 16 ) | ( ADCCHAN1 << 14 ) | ( GAIN_1 << 11 ) | ( FRS1_OWR_6_25 << 7 ) | ( BIPOLAR << 6 ) | ( IMMEDIATE_CONV << 3 ) | USE_CH1_OG_REG ;
	ADC3Setup12_Bits = ( ADCCHAN1 << 30 ) | ( GAIN_32 << 27 ) | ( FRS1_OWR_6_25 << 23 ) | ( BIPOLAR << 22 ) | ( IMMEDIATE_CONV << 19 ) | ( USE_CH1_OG_REG << 16 ) | ( ADCCHAN2 << 14 ) | ( GAIN_1 << 11 ) | ( FRS1_OWR_6_25 << 7 ) | ( BIPOLAR << 6 ) | ( IMMEDIATE_CONV << 3 ) | USE_CH2_OG_REG ;
	*/
	
	ADC1Setup12_Bits = ( ADCCHAN1 << 30 ) | ( GAIN_16 << 27 ) | ( FRS1_OWR_25 << 23 ) | ( BIPOLAR << 22 ) | ( IMMEDIATE_CONV << 19 ) | ( USE_CH1_OG_REG << 16 ) | ( ADCCHAN1 << 14 ) | ( GAIN_1 << 11 ) | ( FRS1_OWR_6_25 << 7 ) | ( BIPOLAR << 6 ) | ( IMMEDIATE_CONV << 3 ) | USE_CH1_OG_REG ;
	ADC2Setup12_Bits = ( ADCCHAN1 << 30 ) | ( GAIN_16 << 27 ) | ( FRS1_OWR_25 << 23 ) | ( BIPOLAR << 22 ) | ( IMMEDIATE_CONV << 19 ) | ( USE_CH1_OG_REG << 16 ) | ( ADCCHAN1 << 14 ) | ( GAIN_1 << 11 ) | ( FRS1_OWR_6_25 << 7 ) | ( BIPOLAR << 6 ) | ( IMMEDIATE_CONV << 3 ) | USE_CH1_OG_REG ;
	ADC3Setup12_Bits = ( ADCCHAN1 << 30 ) | ( GAIN_32 << 27 ) | ( FRS1_OWR_25 << 23 ) | ( BIPOLAR << 22 ) | ( IMMEDIATE_CONV << 19 ) | ( USE_CH1_OG_REG << 16 ) | ( ADCCHAN2 << 14 ) | ( GAIN_1 << 11 ) | ( FRS1_OWR_6_25 << 7 ) | ( BIPOLAR << 6 ) | ( IMMEDIATE_CONV << 3 ) | USE_CH2_OG_REG ;
		
	SetADCConfig() ;
	
	SetADCSetup() ;
	
	FlushAll() ;
	
	SPIBusy = TRUE ;
	
	#ifdef USE_AD590
	
//	printUART( "\npress key" ) ;
//	UARTReadChar() ;
	
	SelectADC( ADC1 ) ;
	SelectADC( ADC2 ) ;
	ADCComm( CMDCONVERT0 | CONTINUOUS ) ;
	DeSelectADC( ADC1 ) ;
	DeSelectADC( ADC2 ) ;
	
	SelectADC( ADC3 ) ;
	ADCComm( CMDCONVERT1 | CONTINUOUS ) ;
	DeSelectADC( ADC3 ) ;
	
	#endif
	
	#ifdef USE_DS1821
	
	SelectADC( ADC1 ) ;
	SelectADC( ADC2 ) ;
	SelectADC( ADC3 ) ;
	ADCComm( CMDCONVERT0 | CONTINUOUS ) ;
	DeSelectADC( ADC1 ) ;
	DeSelectADC( ADC2 ) ;
	DeSelectADC( ADC3 ) ;
	
	#endif
	
	SPIBusy = FALSE ;
	
	if( !ADC_Error )
		ADCInit = TRUE ;
	
	return ADC_Error ;
}

INT16U GetADCCounts( void )
{
	INT8U i ;
	INT32U Data = 0 ;

	ADCComm( 0 ) ;
	for( i = 0 ; i < 4 ; i++ )
	{
		Data <<= 8 ;
		Data |= ADCComm( 0 ) ;
	}
	
	Data >>= 16 ;
	
	//if( ( Data == 0xFFFF ) || ( Data == 0 ) )
	//{
	//	AdcntErr++ ;
	//}	 
	
	return( (INT16U)(Data) + 400 ) ;
}

INT16U ReadADC1( void )
{
	INT16U Counts ;
	
	SPIBusy = TRUE ;
	
	{ ADC1CS_LO }
	
	Counts = GetADCCounts() ;
	
	{ ADC1CS_HI }
	
	SPIBusy = FALSE ;
	
	//if( ( Counts == 0 ) || ( Counts == 0xFFFF ) )
	//	DispNum_7Seg( Counts, 0, 3, 4, FORMAT, UPDATE_NOW ) ;
	
	return Counts ;
}

INT16U ReadADC2( void )
{
	INT16U Counts ;
	
	SPIBusy = TRUE ;
	
	{ ADC2CS_LO }
	
	Counts = GetADCCounts() ;
			
	{ ADC2CS_HI }
		
	SPIBusy = FALSE ;
	
	//if( ( Counts == 0 ) || ( Counts == 0xFFFF ) )
	//	DispNum_7Seg( Counts, 4, 7, 8, FORMAT, UPDATE_NOW ) ;
	
	return Counts ;
}

#ifdef USE_AD590

void EndContinuousConv( void )
{
	INT8U i ;
	INT32S Data ;
	
	ADCComm( 0xFF ) ;
	for( i = 0 ; i < 4 ; i++ )
	{
		Data <<= 8 ;
		Data |= ADCComm( 0 ) ;
	}	
}
/*
INT32U ReadADC3( void )
{
	INT32U Counts = 0 ;
	
	SPIBusy = TRUE ;
	
	{ ADC3CS_LO }
	
	Counts = GetADCCounts() ;
			
	{ ADC3CS_HI }
		
	SPIBusy = FALSE ;
	
	return Counts ;
}
*/

INT32U ReadADC3( void )
{
	INT16U Counts ;
	
	SPIBusy = TRUE ;
	
	{ ADC3CS_LO }
	
	Counts = GetADCCounts() ;
	
	{ ADC3CS_HI }
	
	if( !CalMode && Init )
	{	
		
		if( PTLSampCntr )
		{
		//	printUART("\n PTL SAMPLE");	
			PTLSampCntr++ ;
			if( PTLSampCntr <= 4 )
				Counts |= 0x10000000 ;
			
		}
		else
		{
			if( ( CSA1State != MEASURE ) && ( CSA2State != MEASURE ) )
			//if( ( CSAState[CUP1] != MEASURE ) && ( CSAState[CUP2] != MEASURE ) )
				RTSampCntr++ ;
			if( RTSampCntr >= 8 )
			{	
					
				{ ADC3CS_LO }
				EndContinuousConv() ;
				{ ADC3CS_HI }
				{ ADC3CS_LO }
				ADCComm( CMDCONVERT0 | CONTINUOUS ) ;		// convert PTL
				{ ADC3CS_HI }
				//printUART("\n convert to ptl");
				RTSampCntr = 0 ;
				PTLSampCntr = 1 ;
				Counts |= 0x80000000 ;

			}
			else
			{
				//	Counts |= 0x80000000 ;
					Counts |= 0x90000000 ;
			}
		}
		
		if( PTLSampCntr >= 65 )
		{
			if( !PTLBusy )
			{
				
				
				{ ADC3CS_LO }
				EndContinuousConv() ;
				{ ADC3CS_HI }
				{ ADC3CS_LO }
				ADCComm( CMDCONVERT1 | CONTINUOUS ) ;	// convert RoomT
				{ ADC3CS_HI }
			//	printUART("\n convert to ROOM");
				RTSampCntr = 0 ;
				PTLSampCntr = 0 ;
			
				
			}
			else
				{
					PTLSampCntr = 64 ;
				//	Counts |= 0x10000000 ;
				}
		}
	}
	else
	{
		if( RoomTCalib || !Init )
		{
			RTSampCntr++ ;
			if( RTSampCntr >= 4 )
				RTSampCntr = 4 ;
			Counts |= 0x80000000 ;
		}
	}		
	
	SPIBusy = FALSE ;
	
	return Counts ;
}

void CheckADC( void )
{
	INT16S temp ;
//	char str[64] ;
	
	//U1TXREG = '@' ;
	
	*CSA1BuffSetPtr = ReadADC1() ;
	if( CSA1BuffSetPtr == CSA1Buff )			
		CSA1BuffSetPtr += CSA1BUFFLEN - 1 ;
	else
		CSA1BuffSetPtr-- ;
//	CSA1BuffCnt++ ;
	
	*CSA2BuffSetPtr = ReadADC2() ;
	if( CSA2BuffSetPtr == CSA2Buff )			
		CSA2BuffSetPtr += CSA2BUFFLEN - 1 ;
	else
		CSA2BuffSetPtr-- ;
//	CSA2BuffCnt++ ;
	
	temp = ReadADC3() ;
	
	if( temp & 0x80000000 )
	{
		if( ( temp & 0x10000000 ) == 0 )
		{	
			RoomTCnts = (INT16U)( temp & 0x0000FFFF ) ;
		
			/*
			*RoomTempBuffSetPtr = (INT16U)( temp & 0x0000FFFF ) ;
			if( RoomTempBuffSetPtr == RoomTempBuff )			
				RoomTempBuffSetPtr += ROOMTEMPBUFFLEN - 1 ;
			else
				RoomTempBuffSetPtr-- ;
			*/
		}
	}	
	else if( ( temp & 0x10000000 ) == 0 )
	{
		*PTLBuffSetPtr = (INT16U)( temp & 0x0000FFFF ) ;
		if( PTLBuffSetPtr == PTLBuff )			
			PTLBuffSetPtr += PTLBUFFLEN - 1 ;
		else
			PTLBuffSetPtr-- ;
//		PtlBuffCnt++ ;
	}
}

#endif

#ifdef USE_DS1821

INT16U ReadADC3( void )
{
	INT16U Counts ;

	SPIBusy = TRUE ;
	
	{ ADC3CS_LO }
	
	Counts = GetADCCounts() ;
			
	{ ADC3CS_HI }

	SPIBusy = FALSE ;
	
	//if( ( Counts == 0 ) || ( Counts == 0xFFFF ) )
	//	DispNum_7Seg( Counts, 8, 11, 12, FORMAT, UPDATE_NOW ) ;
	
	// 18.84 16828
	// 16.00 14351
	// 20.00 17832
	
	//if( CalMode )
	//{
	//	if( ( Counts < 14351 ) || ( Counts > 17832 ) )
	//		DispNum_7Seg( Counts, 8, 11, 12, FORMAT, UPDATE_NOW ) ;
	//}	
	
	return Counts ;
}

void _1WireWrite( INT8U byte )
{
	INT8U j, mask ;
	
	for( mask = 0x01 ; mask != 0 ; mask <<= 1 )			// 62
	{
		DS_IO_OUT ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		if( byte & mask )
		{
			DS_IO_LOW ;
			// 1us 
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;						
			asm( "NOP" ) ;
		asm( "NOP" ) ;
			DS_IO_HIGH ;
		}
		else
		{
			DS_IO_LOW ;
			// 1us 
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
			asm( "NOP" ) ;
		asm( "NOP" ) ;
			DS_IO_LOW ;
		}
		for( j = 0 ; j < 140 ; j++ )			// 60 us
			asm( "NOP" ) ;
		DS_IO_IN ;
		// 1us 
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
	}
	
	DS_IO_IN ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
}

void WaitBusy( void )
{
	INT8U i, j, byte = 0 ;

	RoomTErr = FALSE ;
	Timeout1820 = 0 ;
	
	while( byte != 0xFF )								// 480
	{
		DS_IO_OUT ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		DS_IO_LOW ;
		/******* 1us *******/
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		/*********************/
		DS_IO_IN ;
		for( i = 0 ; i < 35 ; i++ )			// 15 us
			asm( "NOP" ) ;						
		if( DS_IO )
		{
			byte <<= 1 ;
			byte |= 1 ;
		}
		for( j = 0 ; j < 105 ; j++ )			// 45 us
			asm( "NOP" ) ;
		
		/******* 1us *******/
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		/*********************/
		//printf( "\n\rTimeoutcntr2 = %d", Timeoutcntr ) ;
		if( Timeout1820++ >= RTTIMEOUT )
		{
			Timeout1820 = 0 ;
			RoomTErr = TRUE ;
			return ;
		}
	}
}

void ReadScratchPad( void )  /* 4.5 ms */
{
	INT8U i, j, byte = 0, NumBytes = 0, rbit = 0 ;
	
	RoomTErr = FALSE ;
	Timeout1820 = 0 ;	
	while( NumBytes != 9 )							// 540
	{
		DS_IO_OUT ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		DS_IO_LOW ;
		/******* 1us *******/
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		/*********************/
		DS_IO_IN ;
		for( i = 0 ; i < 35 ; i++ )	//	15 us
			asm( "NOP" ) ;
		byte >>= 1 ;
		if( DS_IO )
			byte |= 0x80 ;
		rbit++ ;
		if( rbit == 8 )
		{
			ScratchPad[ NumBytes++ ] = byte ;
			rbit = 0 ;
			byte = 0 ;
		}
		for( j = 0 ; j < 105 ; j++ )			// 45 us
			asm( "NOP" ) ;
		
		/******* 1us *******/
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		/*********************/
		//printf( "\n\rTimeoutcntr1 = %d", Timeoutcntr ) ;
		if( Timeout1820++ >= RTTIMEOUT )
		{
			Timeout1820 = 0 ;
			RoomTErr = TRUE ;
			break ;
		}
	}
}

void CalcRoomT( void )
{
	INT16U temp, temp2 ;
	
#ifdef ADC_RESET_REVISION
	static INT16U oldrtcnts = 300 ;
#endif
	//char str[32];

//	printUART( "\nScratchPad[1] = " ) ;
//	printUART( NumToStr(ScratchPad[1], 0, 2, 3, str,0 ) ) ;
//printUART( "\nScratchPad[0] = " ) ;
//	printUART( NumToStr(ScratchPad[0], 0, 2, 3, str,0 ) ) ;
//printUART( "\nScratchPad[7] = " ) ;
//	printUART( NumToStr(ScratchPad[7], 0, 2, 3, str,0 ) ) ;
//printUART( "\nScratchPad[6] = " ) ;
//	printUART( NumToStr(ScratchPad[6], 0, 2, 3, str,0 ) ) ;

	//sprintf( str, "\nSP[0] = %d", ScratchPad[0] ) ; printUART( str ) ;
	//sprintf( str, "\nSP[1] = %d", ScratchPad[1] ) ; printUART( str ) ;
	//sprintf( str, "\nSP[6] = %d", ScratchPad[6] ) ; printUART( str ) ;
	//sprintf( str, "\nSP[7] = %d", ScratchPad[7] ) ; printUART( str ) ;

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
	//if( temp < 5000 )
	
#ifdef 	ADC_RESET_REVISION
	if( temp > oldrtcnts )
	{
		if(  ( temp - oldrtcnts ) > 100 )
			temp = oldrtcnts ;
	}
	else
	{
		if(  ( oldrtcnts - temp ) > 100 )
			temp = oldrtcnts ;
	}
	oldrtcnts = temp ;
#endif
		RoomTCnts = (INT16S)temp ;
//	printUART( "\nroomtcnt = " ) ;
	//printUART( NumToStr(RoomTCnts, 0, 3, 4, str,0 ) ) ;
	//sprintf( str, "\n%d", RoomTCnts ) ;
	//printUART( str ) ;

}	


INT8U ResetDS1820( void )
{
	INT8U valid = FALSE ;
	INT16U j ;
/*
DS_IO_OUT ;
while(1)
{
	for( j = 0 ; j < 1225 ; j++ )		// 500 us
		asm( "NOP" ) ;
DS_IO_LOW ;
	for( j = 0 ; j < 1225 ; j++ )		// 500 us
		asm( "NOP" ) ;
DS_IO_HIGH ;
}
*/	for( j = 0 ; j < 1000 ; j++ )		// 
		asm( "NOP" ) ;
	DS_IO_OUT ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
	asm( "NOP" ) ;
	DS_IO_LOW ;
		
	for( j = 0 ; j < 1225 ; j++ )		// 500 us
		asm( "NOP" ) ;
	
	DS_IO_IN ;
	
	for( j = 0 ; j < 140 ; j++ )		// 60 us
		asm( "NOP" ) ;
	
	if( DS_IO == LOW )
	{
		for( j = 0 ; j < 140 ; j++ )	// 60 us
			asm( "NOP" ) ;
		
		if( DS_IO == LOW )
		{
			valid = TRUE ;
		}
		else
		{
			valid = FALSE ;
		}
		
		for( j = 0 ; j < 1225 ; j++ )		// 500 us
			asm( "NOP" ) ;
		
		if( DS_IO == LOW )		valid = FALSE ;
	}
	
	return valid ;
}	

void Read_DS1820_Family( void )
{
	INT8U valid ;
 	INT8U i, j, byte = 0, rbit = 0 ;

	IEC0bits.T1IE = 0 ;
	IEC1bits.T4IE = 0 ;
	
	valid = ResetDS1820() ;
	
	if( !valid )
	{
		IEC0bits.T1IE = 1 ;
		IEC1bits.T4IE = 1 ;
		return ;
	}
	
	_1WireWrite( READ_ROM ) ;	//0x33 ) ;		// read rom
		
	while( rbit < 8 )							// 540
	{
		DS_IO_OUT ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		DS_IO_LOW ;
		/******* 1us *******/
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		/*********************/
		DS_IO_IN ;
		for( i = 0 ; i < 35 ; i++ )	//	15 us
			asm( "NOP" ) ;
		byte >>= 1 ;
		if( DS_IO )
			byte |= 0x80 ;
		rbit++ ;
		if( rbit == 8 )
		{
			FamilyCode = byte ;
		}
		for( j = 0 ; j < 105 ; j++ )			// 45 us
			asm( "NOP" ) ;
		
		/******* 1us *******/
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		asm( "NOP" ) ;
		/*********************/
	}	
	IEC0bits.T1IE = 1 ;
	IEC1bits.T4IE = 1 ;
}	

INT8U Read_RoomT_Fun1( void )		// 10 ms
{
	INT8U valid ;
//	printUART("\n READ ROOMT");
	IEC0bits.T1IE = 0 ;
	IEC1bits.T4IE = 0 ;
//	#ifdef USE_ONLINE
//	IEC1bits.U2RXIE = 0 ;
//	#endif
	valid = ResetDS1820() ;
	
	if( !valid )
	{
		IEC0bits.T1IE = 1 ;
		IEC1bits.T4IE = 1 ;
	//	#ifdef USE_ONLINE
	//	IEC1bits.U2RXIE = 1 ;
	//	#endif
		return valid ;
	}	
//	printUART("\n STEP1");
	_1WireWrite( SKIP_ROM ) ;	//0xCC ) ;		// skip rom
	_1WireWrite( WRITE_SCRATCHPAD ) ;	//0x4E ) ;		// write scratchpad
	_1WireWrite( 0x03 ) ;
	_1WireWrite( 0x06 ) ;
	
	valid = ResetDS1820() ;
	
	if( !valid )
	{
		IEC0bits.T1IE = 1 ;
		IEC1bits.T4IE = 1 ;
	//	#ifdef USE_ONLINE
	//	IEC1bits.U2RXIE = 1 ;
	//	#endif
		return valid ;
	}
//	printUART("\n STEP2");
	_1WireWrite( SKIP_ROM ) ;		// skip rom
	_1WireWrite( _1WIRE_SOC ) ;	//0x44 ) ;		// start of conversion 01000100
	
	IEC0bits.T1IE = 1 ;
	IEC1bits.T4IE = 1 ;
	
	return valid ;
}

INT8U Read_RoomT_Fun2( void )		// 10 ms
{
	INT8U valid ;
	
	IEC0bits.T1IE = 0 ;
	IEC1bits.T4IE = 0 ;
	
	WaitBusy() ;
	//printf( "\nafter wait" ) ;
	
	valid = ResetDS1820() ;
	//printf( "\nafter reset" ) ;

	if( !valid )
	{
		IEC0bits.T1IE = 1 ;
		IEC1bits.T4IE = 1 ;
	//	#ifdef USE_ONLINE
	//	IEC1bits.U2RXIE = 1 ;
	//	#endif
		return valid ;
	}
//	printUART("\n STEP3");	
	_1WireWrite( SKIP_ROM ) ;		// skip rom
	_1WireWrite( READ_SCRATCHPAD ) ;	//0xBE ) ;		// read scratch pad			
	
	ReadScratchPad() ;
	
	valid = ResetDS1820() ;
	
	IEC0bits.T1IE = 1 ;
	IEC1bits.T4IE = 1 ;
//	#ifdef USE_ONLINE
//	IEC1bits.U2RXIE = 1 ;
//	#endif
	//101101110
	if( !valid )	return( valid & !RoomTErr ) ;
	//printUART("\n STEP4");	
	CalcRoomT() ;	
	
	return valid ;
}

void CheckADC( void )
{
	
	static INT8U _320msec = 0 ;

	if( !_320msec )	_320msec = 1 ;
	else			_320msec = 0 ;
	
	if( _320msec || Cup2_CE_Cup )
	{
		*CSA1BuffSetPtr = ReadADC1() ;
		if( CSA1BuffSetPtr == CSA1Buff )			
			CSA1BuffSetPtr += CSA1BUFFLEN - 1 ;
		else
			CSA1BuffSetPtr-- ;
	}		
//	CSA1BuffCnt++ ;

	if( _320msec || !Cup2_CE_Cup )
	{
		*CSA2BuffSetPtr = ReadADC2() ;
		if( CSA2BuffSetPtr == CSA2Buff )			
			CSA2BuffSetPtr += CSA2BUFFLEN - 1 ;
		else
			CSA2BuffSetPtr-- ;
//		CSA2BuffCnt++ ;
	}
	
	*PTLBuffSetPtr = ReadADC3() ;
	if( PTLBuffSetPtr == PTLBuff )			
		PTLBuffSetPtr += PTLBUFFLEN - 1 ;
	else
		PTLBuffSetPtr-- ;
//	PtlBuffCnt++ ;
}

#endif

INT32U GetCSA1Count( void )
{
	INT32U temp = 0 ;
	
	if( CSA1BuffGetPtr == CSA1BuffSetPtr )
		temp = 0x80000000 ;
	else
	{
		temp = *CSA1BuffGetPtr ;
		if( CSA1BuffGetPtr == CSA1Buff )
			CSA1BuffGetPtr += CSA1BUFFLEN - 1 ;
		else
			CSA1BuffGetPtr-- ;
//		CSA1BuffCnt-- ;	
	}	
	
	return temp ;	
}

INT32U GetCSA2Count( void )
{
	INT32U temp = 0 ;
	
	if( CSA2BuffGetPtr == CSA2BuffSetPtr )
		temp = 0x80000000 ;
	else
	{
		temp = *CSA2BuffGetPtr ;
		if( CSA2BuffGetPtr == CSA2Buff )
			CSA2BuffGetPtr += CSA2BUFFLEN - 1 ;
		else
			CSA2BuffGetPtr-- ;
//		CSA2BuffCnt-- ;
	}	

	return temp ;	
}

INT32U GetPTLCount( void )
{
	INT32U temp = 0 ;
	
	if( PTLBuffGetPtr == PTLBuffSetPtr )
		temp = 0x80000000 ;
	else
	{
		temp = *PTLBuffGetPtr ;
		if( PTLBuffGetPtr == PTLBuff )
			PTLBuffGetPtr += PTLBUFFLEN - 1 ;
		else
			PTLBuffGetPtr-- ;
//		PtlBuffCnt-- ;
	}	
	
	return temp ;	
}

void Get_CSA_PTL_Counts( void )
{
	/*
	INT32U temp ;
	
	temp = GetCSA1Count() ;
	if( ( temp & 0x80000000 ) == 0 )
	{
		if( temp > 32765 ) temp = 32767 ;
		Csa1Cnts = (INT16U)temp ;
	}	
	temp = GetCSA2Count() ;
	if( ( temp & 0x80000000 ) == 0 )
	{
		if( temp > 32765 ) temp = 32767 ;
		Csa2Cnts = (INT16U)temp ;
	}
	temp = GetPTLCount() ;
	if( ( temp & 0x80000000 ) == 0 )
	{
		if( temp > 32765 ) temp = 32767 ;
		PtlCnts = (INT16U)temp ;
	}
	*/
	
	INT32U cnt_ch1, cnt_ch2, cnt_ch3 ;
		
	cnt_ch1 = GetCSA1Count() ;
	cnt_ch2 = GetCSA2Count() ;
	cnt_ch3 = GetPTLCount() ;
	
	if( ( cnt_ch1 & 0x80000000 ) == 0 )
	{
		if( cnt_ch1 > 32765 ) 	cnt_ch1 = 32767 ;
		if( Cup2_CE_Cup )	Csa1Cnts = (INT16U)cnt_ch1 ;
		else				Csa2Cnts = (INT16U)cnt_ch1 ;
	}	
	
	if( ( cnt_ch2 & 0x80000000 ) == 0 )
	{
		if( cnt_ch2 > 32765 ) cnt_ch2 = 32767 ;
		if( Cup2_CE_Cup )	Csa2Cnts = (INT16U)cnt_ch2 ;
		else				Csa1Cnts = (INT16U)cnt_ch2 ;
	}
	
	if( ( cnt_ch3 & 0x80000000 ) == 0 )
	{
		if( cnt_ch3 > 32765 ) cnt_ch3 = 32767 ;
		PtlCnts = (INT16U)cnt_ch3 ;
	}
}
