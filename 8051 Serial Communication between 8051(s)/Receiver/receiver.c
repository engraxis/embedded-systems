#include <REGX51.H>
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void delay(unsigned int);
void lcdready (void); 
unsigned char abz;
sfr ldata=0x90;
sbit rs=P2^0;
sbit rw=P2^1;
sbit en=P2^2;
sbit busy=P1^7;

void main(void)
{
	unsigned char i;
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x86);
	lcdcmd(0x06);
	lcdcmd(0x0E);
	TMOD=0x20;
	TH1=0XFD;
	SCON=0X50;
	TR1=1;
	for(i=0;i<=2;i++)
	{
		while(RI==0);
		delay(1);
		abz=SBUF;
		RI=0;
		lcddata(abz);
	}
	lcdcmd(0xC2);
	for(i=3;i<=14;i++)
	{
		while(RI==0);
		delay(1);
		abz=SBUF;
		RI=0;
		lcddata(abz);
	}
	lcdcmd(0x91);
	for(i=14;i<=27;i++)
	{
		while(RI==0);
		delay(1);
		abz=SBUF;
		RI=0;
		lcddata(abz);
	}
	lcdcmd(0xD0);
	for(i=27;i<=46;i++)
	{
		while(RI==0);
		delay(1);
		abz=SBUF;
		RI=0;
		lcddata(abz);
	}
	while(1);
}
void lcdcmd(unsigned char value)
{
	lcdready ();
	ldata=value;
	rs=0;
	rw=0;
	en=1;
	delay(1);
	en=0;
	return;
}
void lcddata(unsigned char value)
{
	ldata=value;
	rs=1;
	rw=0;
	en=1;
	delay(1);
	en=0;
	return;
}
void delay(unsigned int itime)
{
	unsigned int i,j;
	for(i=0;i<itime;i++)
		for (j=0;j<1275;j++);
}
void lcdready (void)
{
	busy=1;
	rs=0;
	rw=1;
	while (busy==1)
	{
		en=0;
		delay(1);
		en=1;
	}
	return;
}