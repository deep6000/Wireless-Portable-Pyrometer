extern void I2C_Init(void ) ;
extern void WriteEE_byte ( INT8U addr, INT8U  data);
extern  INT8U ReadEE_byte ( INT8U addr) ;
extern void WriteRTC_time ( INT8U addr, INT8U data);
extern INT8U ReadRTC_time ( INT8U addr);
extern void Write_IO ( INT8U addr, INT8U data);

