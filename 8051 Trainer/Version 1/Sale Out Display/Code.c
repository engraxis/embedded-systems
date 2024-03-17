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
///////////////////////////////// DELAY //////////////////////////////////
void delay(unsigned int);
//////////////////////////////// VARIABLES ///////////////////////////////
unsigned char a,b,i;						// Looping
///////////////////////////// MAIN FUNCTION //////////////////////////////
void main(void)
{		
	unsigned char abz[]= "ABDULLAH TAHIR";
	unsigned char disp[]="8051 TRAINER";
	P0=P1=P2=P3=0x00;
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x82);
	for(i=0;i<=(strlen(disp)-1);i++)
	{	
		lcddata(disp[i]);
	}
	lcdcmd(0xC1);
	for(i=0;i<=(strlen(abz)-1);i++)
	{
		lcddata(abz[i]);
	}	
	while(1)
	{
		
		P2=0x11;
		P1=0x55;
		delay(200);

		P2=0x22;
		P1=0x2A;
		delay(200);

		P2=0x44;
		P1=0x55;
		delay(200);

		P2=0x88;
		P1=0x2A;
		delay(200);


	}
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

