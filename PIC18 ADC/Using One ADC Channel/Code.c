//		ANALOGUE TO DIGITAL CONVERSION

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18F452.h>

#define ldata PORTD
#define rs PORTBbits.RB0
#define rw PORTBbits.RB1
#define en PORTBbits.RB2
#define busy PORTDbits.RD7

void lcdcmd(unsigned char);
void lcddata(unsigned char);
void delay(unsigned char);
void lcdready(void);

unsigned char i,j,k,dec,d1,d2,d3;
unsigned double a;

void main (void)
{
	TRISB=TRISD=0X00;	
	TRISAbits.TRISA0=0;
	ADCON0=0X81;
	ADCON1=0X4E;	
	
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x83);

	for(a=1;a<=200;a++);
	ADCON0bits.GO=1;
	while(ADCON0bits.DONE==1);
	for(a=1;a<=400;a++);

	///////////////Binary to ASCII Conversion
	
	dec=ADRESH/10;
	d1=ADRESH%10;
	d2=dec%10;
	d3=dec/10;
	d1=d1|0x30;
	d2=d2|0x30;
	d3=d3|0x30;
	lcddata(d3);
	lcddata(d2);
	lcddata(d1);
	while(1);
}

void lcddata(unsigned char value)
{
	lcdready();	 
	ldata=value;
	rs=1;
	rw=0;
	en=1;
	delay(10);
	en=0;
	return;
}

void lcdready(void)
{
	TRISD=0xFF;
	rs=0;
	rw=1;
	do
	{
		en=1;
		delay(10);
		en=0;
	}	
	while(busy==1);
	TRISD=0x00;
	return;
}

void lcdcmd(unsigned char value)
{
	lcdready();
	ldata=value;
	rs=0;
	rw=0;
	en=1;
	delay(10);
	en=0;
	return;
}	
void delay(unsigned char a)
{
	for(j=1;j<=a;j++)
		for(k=1;k<=100;k++);
	return;
}