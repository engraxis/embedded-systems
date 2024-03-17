//////////////////////////Interrupts: INT1 &3 TMR1
/*
Instructions:
1:	Garbage values may cause error in the project
2:	Also clear FLAG BITS in main function 
3:	Do not write ; while writing #pragma
4:	Do not write the prototype of those functions which are defined by #pragma
5: 	Clear respective flag
6:	Sequence
	a.	Configuration Registers
	b.	Header Files
	c.	Functions Prototype
	d.	#pragma interrupt
				if-else conditions
	e.	#pragma code
				use assembler directive to jump to check which caused interrupt
	f.	void main (void)
*/
#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18F452.h>

void extern_intt(void);
void timer1(void);

unsigned long a;

#pragma interrupt check_intt
void check_intt(void)
{
	if(INTCON3bits.INT1IF==1)
		extern_intt();
	if(PIR1bits.TMR1IF==1)
		timer1();
}
#pragma code HPI = 0x08
void HPI(void)
{
	_asm
	GOTO check_intt
	_endasm
}
#pragma code
void main(void)
{
	TRISD=TRISC=TRISA=0X00;
	PORTD=PORTC=PORTA=0;
	TRISBbits.TRISB1=1;
	T1CON=0X00;
	TMR1H=0X00;
	TMR1L=0X00;
	PIE1bits.TMR1IE=1;
	INTCON3bits.INT1IE=1;
	INTCON2bits.INTEDG1=0;		//Comment it for rising edge
	INTCONbits.PEIE=1;
	INTCONbits.GIE=1;
	T1CONbits.TMR1ON=1;
	while(1)
	{	
		PORTD++;
		for(a=1;a<=10000;a++);
	}
}
void extern_intt (void)
{
	unsigned long a;
	PORTA=0X55;
	for(a=1;a<=10000;a++);
	PORTA=0XAA;
	INTCON3bits.INT1IF=0;	
	return;
}
void timer1(void)
{
	PORTC++;
	TMR1H=0X00;
	TMR1L=0X00;
	PIR1bits.TMR1IF=0;
	return;
}