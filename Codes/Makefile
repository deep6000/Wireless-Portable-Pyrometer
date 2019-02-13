# MPLAB IDE generated this makefile for use with GNU make.
# Project: pyrometer.mcp
# Date: Mon Mar 19 16:54:18 2018

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

pyrometer.cof : main.o uart.o def.o adc.o spi.o timer_isr.o lcd.o
	$(LD) /p18F65K90 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.45\lib" "main.o" "uart.o" "def.o" "adc.o" "spi.o" "timer_isr.o" "lcd.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"pyrometer.cof" /M"pyrometer.map" /W

main.o : main.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stdio.h def.h uart.h spi.h lcd.h main.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/p18f65k90.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stdarg.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stddef.h adc.h timer_isr.h
	$(CC) -p=18F65K90 "main.c" -fo="main.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

uart.o : uart.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stdio.h def.h uart.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/p18f65k90.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stdarg.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stddef.h
	$(CC) -p=18F65K90 "uart.c" -fo="uart.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

def.o : def.c def.h def.c
	$(CC) -p=18F65K90 "def.c" -fo="def.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

adc.o : adc.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stdio.h def.h spi.h uart.h adc.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/p18f65k90.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stdarg.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stddef.h adc.h
	$(CC) -p=18F65K90 "adc.c" -fo="adc.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

spi.o : spi.c def.h spi.h spi.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/p18f65k90.h
	$(CC) -p=18F65K90 "spi.c" -fo="spi.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

timer_isr.o : timer_isr.c def.h spi.h timer_isr.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/p18f65k90.h adc.h
	$(CC) -p=18F65K90 "timer_isr.c" -fo="timer_isr.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

lcd.o : lcd.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stdio.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/string.h def.h lcd.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/p18f65k90.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stdarg.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.45/h/stddef.h
	$(CC) -p=18F65K90 "lcd.c" -fo="lcd.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "main.o" "uart.o" "def.o" "adc.o" "spi.o" "timer_isr.o" "lcd.o" "pyrometer.cof" "pyrometer.hex"

