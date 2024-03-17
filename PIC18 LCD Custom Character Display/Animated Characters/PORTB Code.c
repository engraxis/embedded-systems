//	LCD CUSTOM CHARACTER DISPLAY

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18F452.h>
#include<string.h>


#define ldata PORTC

#define rs PORTBbits.RB0
#define rw PORTBbits.RB1
#define en PORTBbits.RB2
#define busy PORTCbits.RC7

void lcdcmd(unsigned char);
void lcddata(unsigned char);
void delay(unsigned char);
void lcdready(void);
void cs(unsigned char, unsigned char,unsigned char, unsigned char, unsigned char,unsigned char,unsigned char, unsigned char, unsigned char,unsigned char);
void cscustom(unsigned char);
unsigned char i,j,k;

void main(void)
{	
	TRISD=TRISB=0x00;
	PORTD=PORTB=0X00;
////////////////////
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
///////////////////
	cscustom(0x80);
	cscustom(0xc6);
///////////////////
	while(1)
	{
		lcdcmd(0x18);
		delay(200);
	}
}
void cs(unsigned char base, unsigned char display, unsigned char location,unsigned char a,unsigned char b,unsigned char c,unsigned char d,unsigned char e,unsigned char f,unsigned char g)
{
	lcdcmd(base);
	lcddata(a);
	lcddata(b);
	lcddata(c);
	lcddata(d);
	lcddata(e);
	lcddata(f);
	lcddata(g);
	lcdcmd(location);
	lcddata(display);
	return;
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
	TRISC=0xFF;
	rs=0;
	rw=1;
	do
	{
		en=1;
		delay(10);
		en=0;
	}	
	while(busy==1);
	TRISC=0x00;
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
void cscustom(unsigned char location)
{
	cs(120,7,location,0x00,0X00,0x00,0X00,0x00,0X00,0x1F);
	location++;
	cs(112,6,location,0x00,0X00,0x00,0X00,0x00,0X1F,0x1F);
	location++;
	cs(104,5,location,0x00,0X00,0x00,0X00,0x1F,0X1F,0x1F);
	location++;
	cs(96,4,location,0x00,0X00,0x00,0X1F,0x1F,0X1F,0x1F);
	location++;	
	cs(88,3,location,0x00,0X00,0x1F,0X1F,0x1F,0X1F,0x1F);
	location++;
	cs(80,2,location,0x00,0x1F,0X1F,0x1F,0x1F,0X1F,0x1F);
	location++;
	cs(72,1,location,0x1F,0x1F,0X1F,0x1F,0x1F,0X1F,0x1F);
}