///////////////////////////////////////////////////////////////////////////
#include <REGX51.H>
#include <string.h>
#define lcd P0
sbit rs=P1^5;
sbit rw=P1^6;
sbit en=P1^7;
sbit lcdbusy=P0^7;
////////////////////////// LCD DISPLAY FUNCTIONS //////////////////////////
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcdready(void);
void cs(unsigned char, unsigned char,unsigned char, unsigned char, unsigned char,unsigned char,unsigned char, unsigned char, unsigned char,unsigned char);
///////////////////////////////// DELAY //////////////////////////////////
void delay(unsigned int);
//////////////////////////////// VARIABLES ///////////////////////////////
unsigned char a,b,i;						// Looping
///////////////////////////// MAIN FUNCTION //////////////////////////////
void main(void)
{		
	unsigned char abz[]="ABDULLAH TAHIR";
	P0=P1=P2=P3=0x00;
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x81);
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
}
/////////////////////////////////////////////////////////////////////////

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
/////////////////////////////////////////////////////////////////////////
void lcdcmd(unsigned char value)
{
	lcdready();
	lcd=value;
	rs=0;
	rw=0;
	en=1;
	delay(50);
	en=0;
	return;
}
/////////////////////////////////////////////////////////////////////////
void lcddata(unsigned char value)
{
	lcdready();	 
	lcd=value;
	rs=1;
	rw=0;
	en=1;
	delay(50);
	en=0;
	return;
}
/////////////////////////////////////////////////////////////////////////
void lcdready(void)
{
	lcdbusy=1;
	rs=0;
	rw=1;
	while(lcdbusy==1)
	{
		en=0;
		delay(50);
		en=1;
	}	
	return;
}
/////////////////////////////////////////////////////////////////////////
void delay(unsigned int z)
{	
	for(b=1;b<z;b++)
	{
		TMOD=0X01;
		TH0=0XFC;
		TL0=0X66;
		TR0=1;
		while(TF0==0);
		TR0=0;
		TF0=0;			
	}	
	return;
}

