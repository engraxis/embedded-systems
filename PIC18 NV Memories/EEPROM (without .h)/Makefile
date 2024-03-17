# MPLAB IDE generated this makefile for use with GNU make.
# Project: RoboticArmEmbedded.mcp
# Date: Sun Oct 06 09:32:02 2013

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

RoboticArmEmbedded.cof : Code.o
	$(LD) /p18F452 /l"C:\Program Files\Microchip\mplabc18\v3.40\lib" "Code.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"RoboticArmEmbedded.cof" /M"RoboticArmEmbedded.map" /W

Code.o : Code.c ../../../../Program\ Files/Microchip/mplabc18/v3.40/h/string.h Code.c ../../../../Program\ Files/Microchip/mplabc18/v3.40/h/P18f452.h ../../../../Program\ Files/Microchip/mplabc18/v3.40/h/stddef.h
	$(CC) -p=18F452 "Code.c" -fo="Code.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "Code.o" "RoboticArmEmbedded.cof" "RoboticArmEmbedded.hex"

