////////////////////////////////////////////////////////////////////
//////////// Robotic Arm Control v1 09-09-13 by abxLabs ////////////
////////////////////////////////////////////////////////////////////
#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18f452.h>
#include<EEP.h>

unsigned char i;
void Delay_100ms(unsigned char);
////////////////////////////////////////////////////////////////////	
void main(void)
{
	TRISB = 0x00;
	PORTB = 0x00;
	Write_b_eep(0,0xF0);
	Busy_eep();
	Delay_100ms(1);
	Write_b_eep(1,0x0F);
	Busy_eep();
	Delay_100ms(1);
	for(i=1;i<=5;i++)
	{
		PORTB = Read_b_eep(0);
		Delay_100ms(10);
		PORTB = Read_b_eep(1);
		Delay_100ms(10);
	}

	Write_b_eep(0,0x55);
	Busy_eep();
	Delay_100ms(1);
	Write_b_eep(1,0xAA);
	Busy_eep();
	Delay_100ms(1);
	for(i=1;i<=5;i++)
	{
		PORTB = Read_b_eep(0);
		Delay_100ms(10);
		PORTB = Read_b_eep(1);
		Delay_100ms(10);
	}
	while(1);
}
////////////////////////////////////////////////////////////////////
void Delay_100ms(unsigned char DelayLoop)
{
	unsigned int Lvar;
	for(Lvar=0; Lvar<=DelayLoop; Lvar++)
	{
		T0CON=0X05;
		TMR0H=0XF0;
		TMR0L=0XBE;
		T0CONbits.TMR0ON=1;
		while(INTCONbits.TMR0IF==0);
		T0CONbits.TMR0ON=0;
		INTCONbits.TMR0IF=0;
	}
	return;
}