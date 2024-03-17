///////////////////////////////////////////////////////////////////////////
#include <REGX51.H>
#include <string.h>
#define lcd P0
sbit rs=P1^5;
sbit rw=P1^6;
sbit en=P1^7;
sbit lcdbusy=P0^7;
sbit pc=P3^2;
sbit co=P3^3;
sbit lv=P3^4;
sbit hv=P3^5;
////////////////////////// LCD DISPLAY FUNCTIONS //////////////////////////
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcdready(void);
void lcd_pre(void);
void fun_lv(void);
void fun_hv(void);
void payment_barrier_up(void);
void barrier_down(void);
///////////////////////////////// DELAY //////////////////////////////////
void delay(unsigned int);
//////////////////////////////// VARIABLES ///////////////////////////////
unsigned char a;						// Looping
unsigned char b;						// Looping
unsigned char i;						// Looping for Stepper motor
unsigned char ok;						// Variable used to call "lcd_pre()"
unsigned char x,y;						// Current status of P3
/////////////////////////////////////////////////////
//void payment_barrier_up(void) interrupt 0  //Cash OK Barrier Open
void payment_barrier_up(void) 
{	
	code unsigned char pre_data[]="   Payment OK   ";	

	lcdcmd(0xC2);
	for(i=1;i<=24;i++)
	{
		P2=0x80;
		delay(80);
		P2=0x40;
		delay(80);
		P2=0x20;
		delay(80);
		P2=0x10;
		delay(80);
	}
	for (a=0;a<=(strlen(pre_data)-1);a++)
	{
		lcddata(pre_data[a]);					
	}
	return;
}
/////////////////////////////////////////////////////
//void barrier_down(void) interrupt 2 	 //Barrier Close
void barrier_down(void) 
{						  
	for(i=1;i<=24;i++)
	{
		P2=0x10;
		delay(80);
		P2=0x20;
		delay(80);
		P2=0x40;
		delay(80);
		P2=0x80;
		delay(80);
	}
	ok=1;
}
///////////////////////////// MAIN FUNCTION /////////////////////////////
void main(void)
{
	ok=2;
	P1=P2=0x00;
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcd_pre();

	y=P3;
	while(y==P3);

	while(1)
	{
		if(lv==0 && hv==0)
		{
			fun_hv();	
		}
		if(lv==0 && hv==1)
		{
			fun_lv();	
		}
		if(co==1)
		{
			barrier_down();
		}
		if(pc==0)
		{
			payment_barrier_up();
		}
		if(ok==1)
		{
			lcdcmd(0xC0);
			for(x=0;x<=15;x++)
			{
				lcddata(' ');
			}
			ok=2;
		}
	}
}
/////////////////////////////////////////////////////////////////////////
void lcd_pre(void)					//Data, that should be displayed on the LCD
{
	code unsigned char pre_data[]="UET TOLL TAX";
	code unsigned char pre_data1[]="Drive Safely";
	lcdcmd(0x01);
	lcdcmd(0x84);
	for (a=0;a<=(strlen(pre_data)-1);a++)
	{
		lcddata(pre_data[a]);					
	}	
	lcdcmd(0x98);								
	for (a=0;a<=(strlen(pre_data1)-1);a++)
	{
		lcddata(pre_data1[a]);					
	}
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
/////////////////////////////////////////////////////////////////////////
void fun_lv(void)					  //Cash display for Light Vehicle
{
	code unsigned char pre_data[]="Pay cash = Rs.25";	
	lcdcmd(0xC2);
	for (a=0;a<=(strlen(pre_data)-1);a++)
	{
		lcddata(pre_data[a]);					
	}	
	return;
}
/////////////////////////////////////////////////////////////////////////
void fun_hv(void)					  //Cash display for Heavy Vehicle
{
	code unsigned char pre_data[]="Pay cash = Rs.50";	
	lcdcmd(0xC2);
	for (a=0;a<=(strlen(pre_data)-1);a++)
	{
		lcddata(pre_data[a]);					
	}	
	return;
}
/////////////////////////////////////////////////////////////////////////
