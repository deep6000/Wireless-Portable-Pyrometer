#define SPI_CLK PORTAbits.RA0
#define SPI_CS PORTFbits.RF7
#define SPI_MISO PORTAbits.RA2
#define SPI_MOSI PORTAbits.RA3

extern INT8U SPI_Rx_Tx(INT8U txbyte);



