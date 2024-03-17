////////////////////////////////////////////////////////////////////
//////////// Robotic Arm Control v1 09-09-13 by abxLabs ////////////
////////////////////////////////////////////////////////////////////
#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18f452.h>

unsigned char i;
void Delay_100ms(unsigned char);
////////////////////////////////////////////////////////////////////	
void main(void)
{
	TRISB = 0x00;
	PORTB = 0x00;

	TBLPTR = (short long) 2400;
	TABLAT = 0x0F;
	_asm TBLWTPOSTINC _endasm
	TABLAT = 0xF0;
	_asm TBLWTPOSTINC _endasm
	
	TBLPTR = (short long) 2400;
	EECON1bits.EEPGD = 1;
	EECON1bits.CFGS = 0;
	EECON1bits.WREN = 1;
	INTCONbits.GIE = 0;
	EECON2 = 0x55;
	EECON2 = 0xAA;
	EECON1bits.WR = 1;
	_asm NOP _endasm
	INTCONbits.GIE = 1;
	EECON1bits.WREN = 0;

	for(i=1;i<=5;i++)
	{
		TBLPTR = (short long) 2400;
	
		_asm TBLRDPOSTINC _endasm
		PORTB = TABLAT;
		Delay_100ms(10);

		_asm TBLRDPOSTINC _endasm
		PORTB = TABLAT;
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