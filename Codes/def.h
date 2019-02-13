#define INT8U	unsigned char
#define INT8S	signed char
#define INT16U	unsigned short int
#define INT16S	signed short int
#define INT32U	unsigned long int
#define INT32S	signed long int
#define HIGH 1
#define LOW 0

extern INT8S PrintStr[];
extern void DelayMs(INT16U time);
extern void Delay_us_10(void);
extern void Delay_us_20(void);
extern void Delay_us_40(void);
extern void Delay_us_15(void);
extern void Delay_us_60(void);
extern void Delay_us_50(void);
extern void Delay_us_70(void);
extern void Delay_us_100(void);
extern void Delay_us_500(void);

extern INT16U AdcCount;
extern INT16U mV;
extern INT16U Temperature;
//extern const INT16U RType[ 1024];
//extern INT8U FamilyCode;
extern INT16U RxChar;
extern INT16U ZCnt , SCnt ;
//extern INT8U txrxlen;
extern INT8U idx;
extern INT8U I2C_state;
extern INT8U I2CRx;
extern INT8U I2Cerror;
extern INT8U Bcd2Bin(INT8U bcd);
extern INT8U Bin2bcd(INT8U bin);
extern INT8U I2Ctxlen;
extern INT8U I2Crxlen;
extern INT8U bcd;
extern INT8U bin;
extern INT8U arr[20];
extern INT8U I2Crbyte;
extern INT8U seconds;	
extern INT8U minutes;
extern INT8U hours;
extern INT8U day;
extern INT8U weekday;
extern INT8U month;
extern INT8U year;




