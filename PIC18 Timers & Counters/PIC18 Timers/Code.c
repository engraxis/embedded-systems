///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//				      PIC18F452 TIMERS
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF
///////////////////////////////////////////////////////////
#include<P18F452.h>
///////////////////////////////////////////////////////////
void timer0_basic_5ms_16bit(unsigned char); 
//NOTE: Without Prescalar Fosc/4
//		with Prescalar Fosc/4/prescalar
///////////////////////////////////////////////////////////
void timer0_basic_5ms_8bit(unsigned char);
//NOTE: 8 bit mode is not supported by Timer1
///////////////////////////////////////////////////////////
void timer1_basic_10ms(unsigned char);
//NOTE: Can not be used as counter
///////////////////////////////////////////////////////////
void timer2_basic_10ms(unsigned char);
//NOTE: Value to be loaded in PR2(pulses) = Desired time / (Fosc/4/prescalar/postscalar)
///////////////////////////////////////////////////////////
void timer3_basic_20ms(unsigned char);
//NOTE: Can not be used as 8 bit mode
//		Mostly used as CCP Module
///////////////////////////////////////////////////////////
unsigned char z;	//looping
///////////////////////////////////////////////////////////
void main (void)
{
	TRISA=TRISB=TRISC=TRISD=TRISE=0X00;
	while(1)
	{
		PORTA=0x00;
		timer0_basic_5ms_16bit(1);
		PORTA=0XAA;
		
		PORTB=0x00;
		timer1_basic_10ms(1);
		PORTB=0XAA;
		
		PORTC=0x00;
		timer2_basic_10ms(1);
		PORTC=0XAA;
		
		PORTD=0x00;
		timer3_basic_20ms(1);
		PORTD=0XAA;
		
		PORTE=0x00;
		timer0_basic_5ms_8bit(1);
		PORTE=0XAA;
	}
}
///////////////////////////////////////////////////////////
void timer0_basic_5ms_16bit(unsigned char a)
{
	for(z=1;z<=a;z++)
	{
		T0CON=0X08;
		TMR0H=0XCF;
		TMR0L=0X2C;
		T0CONbits.TMR0ON=1;
		while(INTCONbits.TMR0IF==0);
		T0CONbits.TMR0ON=0;
		INTCONbits.TMR0IF=0;
	}
	return;
}
///////////////////////////////////////////////////////////
void timer0_basic_5ms_8bit(unsigned char a)
{
	for(z=1;z<=a;z++)
	{
		T0CON=0X45;
		TMR0L=0X3D;
		T0CONbits.TMR0ON=1;
		while(INTCONbits.TMR0IF==0);
		T0CONbits.TMR0ON=0;
		INTCONbits.TMR0IF=0;
	}
	return;
}
///////////////////////////////////////////////////////////
void timer1_basic_10ms(unsigned char a)
{
	for(z=1;z<=a;z++)
	{	
		T1CON=0x30;
		TMR1H=0xF3;
		TMR1L=0xCB;
		T1CONbits.TMR1ON=1;
		while(PIR1bits.TMR1IF==0);
		T1CONbits.TMR1ON=0;
		PIR1bits.TMR1IF=0;
	}	
	return;
}	
///////////////////////////////////////////////////////////
void timer2_basic_10ms(unsigned char a)
{
	for(z=1;z<=a;z++)
	{
		T2CON=0x4A;
		TMR2=0X00;
		PR2=0x9C;
		T2CONbits.TMR2ON=1;
		while(PIR1bits.TMR2IF==0);
		T2CONbits.TMR2ON=0;
		PIR1bits.TMR2IF=0;
	}
	return;
}
///////////////////////////////////////////////////////////
void timer3_basic_20ms(unsigned char a)
{
	for(z=1;z<=a;z++)
	{
		T3CON=0x00;
		TMR3H=0x3C;
		TMR3L=0xB0;
		T3CONbits.TMR3ON=1;
		while(PIR2bits.TMR3IF==0);
		T3CONbits.TMR3ON=0;
		PIR2bits.TMR3IF=0;
	}
	return;
}