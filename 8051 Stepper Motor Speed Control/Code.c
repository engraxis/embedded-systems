///////////////////////////////////////////
#include <REGX51.H>
///////////////////////////////////////////
sbit cw=P1^0; 
sbit ccw=P1^1;
sbit inc=P1^2;
sbit dec=P1^3;
sbit cwled=P2^6;
sbit ccwled=P2^7;
unsigned char speed;
///////////////////////////////////////////
void delay(void);
void cwfun(void);
void ccwfun(void);
///////////////////////////////////////////
void main (void)
{
	P0=P1=P2=P3=0X00;
	speed=3;
	cwled=ccwled=0;
	while(1)
	{
		if(cw==1 && ccw==1 || cw==0 && ccw==0)
		{
			P0=0x00;
			cwled=ccwled=1;
		}
		if (cw==1 && ccw!=1)
			cwfun();
		if(ccw==1 && cw!=1)	
			ccwfun();
	}
}           
///////////////////////////////////////////
void delay(void)
{
	TMOD=0X01;

	if (speed>4)
		speed=4;
	if (speed <0)
		speed=0;
	
	if (speed==1)
	{	
		TH0=0X00;
		TL0=0X00;
	}
	if (speed==2)
	{
		TH0=0X00;
		TL0=0X00;
	}
	if (speed==3)
	{
		TH0=0XFF;
		TL0=0XFF;
	}
	if (speed==4)
	{
		TH0=0X00;
		TL0=0X00;
	}
	if (speed==5)
	{
		TH0=0X00;
		TL0=0X00;	
	}


	TR0=1;
	while(TF0==0);
	TR0=0;
	TF0=0;
	return;	
}
///////////////////////////////////////////
void cwfun(void)
{
	P0=0x10;
	while(ccw==0)
	{
		delay();
		P0=P0>>1;
		if(P0==0x80)
		{
			delay();
			P0=0x10;
		}
	}
	return;
}
///////////////////////////////////////////
/*void cwfun(void)
{
	cwled=0;
	ccwled=1;
	while(ccw==0)
	{
		P0=0x10;
		delay();
		P0=0x20;
		delay();
		P0=0x40;
		delay();
		P0=0x80;
		delay();

		if(inc==1)
		{
			delay();
			speed++;
		}
		if(dec==1)
		{
			delay();
			speed--;
		}
	}
	return;
}*/
///////////////////////////////////////////
void ccwfun(void)
{
	ccwled=0;
	cwled=1;
	while(cw==0)
	{
		P0=0x80;
		delay();
		P0=0x40;
		delay();
		P0=0x20;
		delay();
		P0=0x10;
		delay();

		if(inc==1)
		{
			delay();
			speed++;
		}
		if(dec==1)
		{
			delay();
			speed--;
		}
	}
	return;
}