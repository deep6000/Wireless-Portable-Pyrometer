#define DQ_MODE TRISGbits.TRISG4
#define DQ PORTGbits.RG4

extern void DQ_Init( void );
extern INT8U DQ_Reset(void);
//extern INT16U DQ_Presence(void);
//extern void DQ_SendBit( INT8U Bit );
//extern INT8U DQ_GetBit(void );
extern void DQ_WriteByte( INT8U Byte );
extern void DQ_ReadByte(void);
//extern void Read_RoomTemp(void);
extern void WaitBusy( void );
extern void ReadScratchPad( void );
extern void CalcRoomT( void );
extern INT8U Read_RoomT_Fun1( void );
extern INT8U Read_RoomT_Fun2( void );
extern INT8U Read_RoomT_Fun3( void );