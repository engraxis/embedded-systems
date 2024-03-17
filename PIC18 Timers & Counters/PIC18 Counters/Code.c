///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//				      PIC18F452 Counters
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF
///////////////////////////////////////////////////////////
#include<P18F452.h>
///////////////////////////////////////////////////////////
void timer0_counter(void);
void timer1_counter(void);
void timer3_counter(void);
///////////////////////////////////////////////////////////
void main (void)
{
	TRISB=0x00;
	TRISD=0x00;
	PORTB=PORTD=0X00;
//	timer0_counter();
//	timer1_counter();		ERROR: Not Working, Specify pin RC0 
//	timer3_counter();		ERROR: Not Working, Specify pin RC0
}
///////////////////////////////////////////////////////////
void timer0_counter(void)
{
	TRISAbits.TRISA4=1;
	T0CON=0x28;
	TMR0L=TMR0H=0x00;
	T0CONbits.TMR0ON=1;
	while(INTCONbits.TMR0IF==0)
	{
		PORTB=TMR0L;
		PORTD=TMR0H;
	}
	T0CONbits.TMR0ON=0;
	INTCONbits.TMR0IF=0;	
	return;
}
///////////////////////////////////////////////////////////
void timer1_counter(void)
{
	T1CON=0x0E;
	TRISCbits.TRISC0=1;
	TMR1L=TMR1H=0X00;
	do
	{
		T1CONbits.TMR1ON=1;
		PORTB=TMR1L;
		PORTD=TMR1H;
	}
	while(PIR1bits.TMR1IF==0);
	T1CONbits.TMR1ON=0;
	PIR1bits.TMR1IF=0;
	return;
}
///////////////////////////////////////////////////////////
void timer3_counter(void)
{	
	T3CON=0x02;
	TRISCbits.TRISC0=1;
	TMR3L=TMR3H=0X00;
	do
	{
		T3CONbits.TMR3ON=1;
		PORTB=TMR3L;
		PORTD=TMR3H;
	}
	while(PIR2bits.TMR3IF==0);
	T3CONbits.TMR3ON=0;
	PIR2bits.TMR3IF=0;
	return;
}
