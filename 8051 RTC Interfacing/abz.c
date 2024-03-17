///////////////////////////////////////////////////////////////////////////
#include <REGX51.H>
#include <absacc.h>
#define lcd P1
sbit rs=P3^4;
sbit rw=P3^3;
sbit en=P3^2;
sbit lcdbusy=P1^7;
////////////////////////////// LCD COMMANDS //////////////////////////////
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcdready(void);
void lcd_pre(void);
void time(void);
void bcdconv(unsigned char);
///////////////////////////////// DELAY /////////////////////////////////
void delay(unsigned int);
/////////////////////////////// VARIABLES ///////////////////////////////
unsigned char a;						// Looping
unsigned int b;							// Looping
unsigned char x;						// Storing Character
///////////////////////////// MAIN FUNCTION /////////////////////////////
/////////////////////////////////////////////////////////////////////////
void main(void)
{
	////////////////////////////////
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x82);
 	//lcd_pre();
	lcdcmd(0x01);
	time();
	while(1);
}
/////////////////////////////////////////////////////////////////////////
void lcd_pre(void)
{
	code unsigned char pre_data[]="-- Welcome --UET FSD ELEC--09M AbdullahBilawalIrshad UllahJunaid";
	for (a=0;a<=12;a++)
	{
		lcddata(pre_data[a]);					// --Welcome --
	}	
	delay(400);	
	lcdcmd(0xC0);								
	for (a=13;a<=28;a++)
	{
		lcddata(pre_data[a]);					// UET FSD ELEC--09
	}

	delay(1500);		   					//////////////////////////////////////
	lcdcmd(0x01);
	lcdcmd(0x80);
	for (a=29;a<=38;a++)
	{
		lcddata(pre_data[a]);	  				// M Abdullah
	}
	lcdcmd(0xC0);
	for (a=39;a<=45;a++)
	{
		lcddata(pre_data[a]);			 		// Bilawal
	}
	delay(1500); 							//////////////////////////////////////
	lcdcmd(0x01);

	for (a=46;a<=57;a++)
	{
		lcddata(pre_data[a]);			 		// Irshad Ullah
	}
	lcdcmd(0xC0);
	for (a=58;a<=63;a++)
	{
		lcddata(pre_data[a]);			 		// Junaid
	}
	delay(1500); 							//////////////////////////////////////
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
void time(void)
{
	unsigned char hr,min,sec,yr,mo,day;
	XBYTE[10]=0X20;
	XBYTE[11]=0X83;
	XBYTE[4]=0X23;
	XBYTE[2]=0X59;
	XBYTE[0]=0X55;
	XBYTE[7]=0X09;
	XBYTE[8]=0X02;
	XBYTE[9]=0X12;
	
	lcdcmd(0xc3);
	day=XBYTE[7];
	yr=XBYTE[9];
	bcdconv(day);
	lcddata(0x20);
	lcddata('F');
	lcddata('E');
	lcddata('B');
	lcddata(0x20);
	lcddata('2');
	lcddata('0');
	bcdconv(yr);

	XBYTE[11]=0X03;

	while(1)
	{
		lcdcmd(0x84);
		XBYTE[10]=0X20;
		delay(0x300);
		hr=XBYTE[4];
		delay(20);
		min=XBYTE[2];
		delay(20);						
		sec=XBYTE[0];
		delay(20);
		bcdconv(hr);
	//	bcdconv(0x33);
		lcddata(':');
		bcdconv(min);
	//	bcdconv(0x56);
		lcddata(':');
		bcdconv(sec);
	//	bcdconv(0x49);
	}		
}
/////////////////////////////////////////////////////////////////////////
void bcdconv(unsigned char abz)
{
	unsigned char Ax,Ay;

	Ax=0;
	Ay=0;	

	Ax=abz&0x0F;
	Ax=Ax|0x30;

	Ay=abz&0xF0;
	Ay=Ay>>4;
	Ay=Ay|0x30;

	lcddata(Ay);
	lcddata(Ax);

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