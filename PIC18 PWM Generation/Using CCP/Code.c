// PWM Generation by CCP1


#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18F458.h>
void delay(void);
void main (void)
{
	TRISCbits.TRISC2=0x00;
	CCP1CON=0x00;	
	PR2=0xFF;					// Frequency, it will remain constant throughout the program
	CCPR1L=0xBF;				// Change this for complete low, complete high and in between
	CCP1CON=0x2C;
	T2CON=0x03;
	T2CONbits.TMR2ON=1;
	while(1);
}