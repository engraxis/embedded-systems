# MPLAB IDE generated this makefile for use with GNU make.
# Project: General Toggle Test.mcp
# Date: Fri Nov 23 22:38:35 2012

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

General\ Toggle\ Test.cof : Code.o
	$(LD) /p18F452 /l"C:\Program Files\Microchip\mplabc18\v3.40\lib" "Code.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"General Toggle Test.cof" /M"General Toggle Test.map" /W

Code.o : Code.c ../../../../Program\ Files/Microchip/mplabc18/v3.40/h/P18F458.h
	$(CC) -p=18F452 "Code.c" -fo="Code.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "Code.o" "General Toggle Test.cof" "General Toggle Test.hex"

