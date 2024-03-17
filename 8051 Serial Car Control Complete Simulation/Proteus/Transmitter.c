#include <REGX51.H>
sbit stop=P2^0;
unsigned int a;
void trans(unsigned char);
void main(void)
{		
	TMOD=0X20;
	TH1=0XFD;
	SCON=0X50;
	TR1=1;
	for(a=1;a<=10000;a++);
	while(1)
	{
		if(stop==1)
			trans(0);

		if(P1==0xF1)	//forward
			trans(1);	
		while(P1==0xF1);

		if(P1==0xF2)	//backward
			trans(2);
		while(P1==0xF2);

		if(P1==0xF4) //left
			trans(3);
		while(P1==0xF4);
		
		if(P1==0xF8) //right
			trans(4);
		while(P1==0xF8);		

			trans(0);
		
	}	
}
void trans(unsigned char op)
{	
	SBUF=op;
	while(TI==0);
	TI=0;
	return;
}  