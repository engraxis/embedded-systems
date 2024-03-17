//////////////////////////RECEIVING DATA from 8051

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

void tx_data(void);
void delay(void);
#include<P18F452.h>
void main(void)
{
	tx_data();
}
void tx_data(void)
{
	unsigned char a;
	TXSTA=0x20;
	RCSTA=0x90;
	TRISCbits.TRISC6=0;
	TRISCbits.TRISC7=1;
	SPBRG=15;
	while(1)
	{	
		delay();
		TXREG='3';
		while(PIR1bits.TXIF==0);
		PIR1bits.TXIF=0;
		delay();
		TXREG='9';
		while(PIR1bits.TXIF==0);
		PIR1bits.TXIF=0;
	}
}
void delay(void)
{
	T0CON=0X08;
	TMR0H=0X00;
	TMR0L=0X00;
	T0CONbits.TMR0ON=1;
	while(INTCONbits.TMR0IF==0);
	T0CONbits.TMR0ON=0;
	INTCONbits.TMR0IF=0;
	return;
}