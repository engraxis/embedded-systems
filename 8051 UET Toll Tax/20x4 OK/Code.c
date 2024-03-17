///////////////////////////////////////////////////////////////////////////
#include <REGX51.H>
#include <string.h>
#define lcd P0
sbit rs=P1^5;
sbit rw=P1^6;
sbit en=P1^7;
sbit lcdbusy=P0^7;
sbit lv=P3^4;
sbit hv=P3^5;
////////////////////////// LCD DISPLAY FUNCTIONS //////////////////////////
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcdready(void);
void lcd_pre(void);
void fun_lv(void);
void fun_hv(void);
///////////////////////////////// DELAY //////////////////////////////////
void delay(unsigned int);
//////////////////////////////// VARIABLES ///////////////////////////////
unsigned char a;						// Looping
unsigned int b;							// Looping
/////////////////////////////////////////////////////
void payment_barrier_up(void) interrupt 0  //Cash OK Barrier Open
{	
	code unsigned char pre_data[]="   Payment OK   ";	
	lcdcmd(0xC0);
	for (a=0;a<=strlen(pre_data);a++)
	{
		lcddata(pre_data[a]);					
	}
	P2=0x0C;
	delay(1);
	P2=0x0A;
}
/////////////////////////////////////////////////////
void barrier_down(void) interrupt 2 	 //Barrier Close
{						  
	P2=0X04;
	delay(1);
	P2=0x05;
	lcd_pre();
}
///////////////////////////// MAIN FUNCTION /////////////////////////////
void main(void)
{
	P1=0x00;
	P2=0x00;
	IE=0x85;
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcd_pre();
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
	}
}
/////////////////////////////////////////////////////////////////////////
void lcd_pre(void)					//Data, that should be displayed on the LCD
{
	code unsigned char pre_data[]="UET TOOL TAX";
	code unsigned char pre_data1[]="Drive Safely";
	lcdcmd(0x01);
	lcdcmd(0x82);
	for (a=0;a<=strlen(pre_data);a++)
	{
		lcddata(pre_data[a]);					
	}	
	lcdcmd(0x92);								
	for (a=0;a<=strlen(pre_data1);a++)
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
	lcdcmd(0xC0);
	for (a=0;a<=strlen(pre_data);a++)
	{
		lcddata(pre_data[a]);					
	}	
	return;
}
/////////////////////////////////////////////////////////////////////////
void fun_hv(void)					  //Cash display for Heavy Vehicle
{
	code unsigned char pre_data[]="Pay cash = Rs.50";	
	lcdcmd(0xC0);
	for (a=0;a<=strlen(pre_data);a++)
	{
		lcddata(pre_data[a]);					
	}	
	return;
}
/////////////////////////////////////////////////////////////////////////