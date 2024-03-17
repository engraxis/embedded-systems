//////////////////////////RECEIVING DATA from 8051

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

void rec_data(void);
#include<P18F452.h>
void main(void)
{
	rec_data();
}
void rec_data(void)
{
	unsigned char a;
	TXSTA=0x20;
	RCSTA=0x90;
	TRISB=0x00;
	TRISCbits.TRISC6=0;
	TRISCbits.TRISC7=1;
	SPBRG=15;
	while(1)
	{
		while(PIR1bits.RCIF==0);
		PIR1bits.RCIF=0;
		a=RCREG;
		if(a=='3')
			PORTB=0x0F;	
		else
			PORTB=0xF0;
	}
}