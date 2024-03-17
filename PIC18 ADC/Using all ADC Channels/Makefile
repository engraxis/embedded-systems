# MPLAB IDE generated this makefile for use with GNU make.
# Project: x8 ADC.mcp
# Date: Sun Jul 08 01:43:16 2012

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

x8\ ADC.cof : Code.o
	$(LD) /p18F452 /l"C:\Program Files\Microchip\mplabc18\v3.40\lib" "Code.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"x8 ADC.cof" /M"x8 ADC.map" /W

Code.o : Code.c C:/Program\ Files/Microchip/mplabc18/v3.40/h/string.h Code.c C:/Program\ Files/Microchip/mplabc18/v3.40/h/P18F452.h C:/Program\ Files/Microchip/mplabc18/v3.40/h/stddef.h
	$(CC) -p=18F452 "Code.c" -fo="Code.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "Code.o" "x8 ADC.cof" "x8 ADC.hex"

