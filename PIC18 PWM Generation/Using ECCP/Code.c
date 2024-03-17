// PWM Generation by CCP1


#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18F458.h>

void main (void)
{
	TRISD=0x00;
	ECCP1CON=0x4F;	
	PR2=0xFF;					// Frequency, it will remain constant throughout the program
	ECCPR1L=0xBF;				// Change this for complete low, complete high and in between
	CCP1CON=0x2C;
	T2CON=0x03;
	T2CONbits.TMR2ON=1;
	while(1);
}