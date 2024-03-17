#include <REGX51.H>
sbit check=P3^2;
unsigned int i;
void on_ex0() interrupt 0
{
	while(check!=1);
}
void main(void)
{
	IE=0x81;
	P2=0x00;
	while(1)
	{
		P2++;
		for(i=1;i<=1000;i++);
		if(P2==6)
		{
			P2=0;
		}
	}
}
