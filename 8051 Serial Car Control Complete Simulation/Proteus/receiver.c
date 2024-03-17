#include <REGX51.H>
sbit forward=P1^0;
sbit backward=P1^1;
sbit left=P1^2;
sbit right=P1^3;
void rec(void);
unsigned char a;
void main(void)
{
	P0=0X00;
	P1=0X00;
	P2=0X00;
	TMOD=0X20;
	TH1=0XFD;
	SCON=0X50;
	TR1=1;
	forward=backward=left=right=0;
	rec();
}
void rec(void)
{
	while(1)
	{
		while(RI==0);
		RI=0;
		a=SBUF;
		if(a==1)
		{
			forward=1;
			backward=0;
		}		
		if(a==2)	 
		{
			forward=0;
			backward=1; 
		}
		if(a==3)
		{
			left=1;
			right=0;
		}
		if(a==4)
		{
			left=0;
			right=1;
		}
		if(a==0)	
		{
			P1=0x00;
		}
	}
}