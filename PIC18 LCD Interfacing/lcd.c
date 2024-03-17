#include "lcd.h"

#define LCDDATA PORTD
#define LCDTRIS TRISD
#define BUSY	PORTDbits.RD7
#define RS		PORTEbits.RE0
#define RW		PORTEbits.RE1
#define EN		PORTEbits.RE2

void setupLCD(void)
{
	LCDTRIS = 0x00;
	LCDDATA = 0x00;
	ADCON1 = ADCON1 & 0xF0;
	ADCON1 = ADCON1 | 0x0C;
	TRISE = 0x00;
	PORTE = 0x00;
	
	//TODO: Add LCD codes here
	lcdCmd(0x38);
	lcdCmd(0x0C);
	lcdCmd(0x01);
	lcdCmd(0x06);
}

void lcdData(unsigned char arg)
{
	lcdReady();	 
	LCDDATA = arg;
	RS = 1;
	RW = 0;
	EN = 1;
	msDelay(2);
	EN = 0;
}

void lcdCmd(unsigned char arg)
{
    lcdReady();
	LCDDATA = arg;
	RS = 0;
	RW = 0;
	EN = 1;
	msDelay(2);
	EN=0;
}

void lcdReady(void)
{
	LCDTRIS = 0xFF;
	RS = 0;
	RW = 1;
	do
	{
		EN = 1;
		msDelay(2);
		EN = 0;
	}	
	while(BUSY == 1);
	LCDTRIS = 0x00;
}