//	NEEDS TO BE MODIFIED 

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18F452.h>

unsigned long a;

void portb_interrupt(void);
//////////////////////////////////
#pragma interrupt check_cause
void check_cause(void)
{
	if(INTCONbits.RBIF==1)
		portb_interrupt();
}

#pragma code HPI=0x08
void HPI(void)
{
	_asm
	GOTO check_cause
	_endasm
}
#pragma code
//////////////////////////////////
void main (void)
{
	TRISA=TRISC=TRISD=0X00;
	TRISB=0xF0;
	PORTA=PORTC=PORTD=0x00;
	PORTB=0x80;
	INTCONbits.RBIE=1;
	INTCONbits.RBIF=0;
	INTCONbits.GIE=1;
	while(1)
	{
		PORTA++;
		for(a=1;a<=10000;a++);
	}
}

void portb_interrupt(void)
{
	PORTC=PORTD;
	PORTD++;
	for(a=1;a<=10000;a++);
	INTCONbits.RBIF=0;
}
	