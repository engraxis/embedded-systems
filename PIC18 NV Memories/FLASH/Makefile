# MPLAB IDE generated this makefile for use with GNU make.
# Project: RoboticArmControl.mcp
# Date: Sun Nov 17 21:36:41 2013

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

RoboticArmControl.cof : Code.o
	$(LD) /p18F452 /l"C:\Program Files\Microchip\mplabc18\v3.40\lib" "Code.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"RoboticArmControl.cof" /M"RoboticArmControl.map" /W

Code.o : Code.c C:/Program\ Files/Microchip/mplabc18/v3.40/h/P18f452.h
	$(CC) -p=18F452 "Code.c" -fo="Code.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "Code.o" "RoboticArmControl.cof" "RoboticArmControl.hex"

