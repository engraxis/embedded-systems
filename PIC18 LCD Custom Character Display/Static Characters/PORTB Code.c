//	LCD CUSTOM CHARACTER DISPLAY

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18F452.h>
#include<string.h>


#define ldata PORTD

#define rs   PORTCbits.RC0
#define rw   PORTCbits.RC1
#define en   PORTCbits.RC3
#define busy PORTDbits.RD7

void lcdcmd(unsigned char);
void lcddata(unsigned char);
void delay(unsigned char);
void lcdready(void);
void cs(unsigned char, unsigned char,unsigned char, unsigned char, unsigned char,unsigned char,unsigned char, unsigned char, unsigned char,unsigned char);
unsigned char i,j;
unsigned int k;

void main(void)
{	
	unsigned char abz[]="ABDULLAH TAHIR";
	TRISD=TRISC=0x00;
	PORTD=PORTC=0X00;
////////////////////
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x81);
///////////////////
	for(i=0;i<=(strlen(abz)-1);i++)
	{	
		lcddata(abz[i]);
	}
	cs(120,7,0xCE,0x00,0X0A,0x15,0X11,0x0A,0X04,0x00);
	cs(112,6,0xCC,0x00,0X0A,0x00,0X04,0x04,0X11,0x0E);
	cs(104,5,0xCA,0x00,0X11,0x0A,0X11,0x00,0X0E,0x11);
	cs(96,4,0xC8,0x15,0X0A,0x15,0X0A,0x15,0X0A,0x15);
	cs(88,3,0xC6,0x1F,0X1E,0x1D,0X1B,0x17,0X0F,0x1F);
	cs(80,2,0xC4,0x04,0x0A,0X04,0x00,0x04,0X0A,0x04);
	cs(72,1,0xC2,0x11,0x04,0X11,0x04,0x11,0X04,0x11);
//	cs(64,0,0xC0,0x00,0x03,0X05,0x05,0x05,0X05,0x00);
///////////////////
	while(1);
	delay(250);delay(250);delay(250);
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
		for(k=1;k<=2500;k++);
	return;
}