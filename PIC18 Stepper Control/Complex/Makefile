# MPLAB IDE generated this makefile for use with GNU make.
# Project: Stepper Motor Complete.mcp
# Date: Tue Dec 02 00:55:13 2003

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

Stepper\ Motor\ Complete.cof : Stepper.o
	$(LD) /p18F452 /l"C:\Program Files\Microchip\mplabc18\v3.40\lib" "Stepper.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"Stepper Motor Complete.cof" /M"Stepper Motor Complete.map" /W

Stepper.o : Stepper.c ../../../../../Program\ Files/Microchip/mplabc18/v3.40/h/P18F458.h
	$(CC) -p=18F452 "Stepper.c" -fo="Stepper.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "Stepper.o" "Stepper Motor Complete.cof" "Stepper Motor Complete.hex"

