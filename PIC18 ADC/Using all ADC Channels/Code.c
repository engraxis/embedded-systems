//		ANALOGUE TO DIGITAL CONVERSION

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18F452.h>
#include<string.h>

#define ldata PORTD
#define rs PORTBbits.RB0
#define rw PORTBbits.RB1
#define en PORTBbits.RB2
#define busy PORTDbits.RD7

void lcdcmd(unsigned char);
void lcddata(unsigned char);
void delay(unsigned double);			// 1 us
void lcdready(void);
void welcome(void);
void start(void);
void start_bin_2_ascii(void);

unsigned char dec,d1,d2,d3,l;
unsigned double j,a;

far rom const char an0[]="A0=";
far rom const char an1[]="A1=";
far rom const char an2[]="A2=";
far rom const char an3[]="A3=";
far rom const char an4[]="A4=";
far rom const char an5[]="A5=";
far rom const char an6[]="A6=";
far rom const char an7[]="A7=";
far rom const char st[]="WELCOME";
far rom const char nd[]="UET - MECHATRONICS";
far rom const char rd[]="ADC Initializing";
far rom const char na[]="   Abdullah Tahir   ";

void main (void)
{	
	ADCON0=0X41;
	ADCON1=0X4E;	

	TRISB=TRISD=0X00;	
	TRISA=0XFF;
	
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	
	welcome();
	start();

	while(1)
	{
		lcdcmd(0x83);
		ADCON0=ADCON0&0XC7;
		ADCON0=ADCON0|0X00;
		start_bin_2_ascii();

		lcdcmd(0x8A);
		ADCON0=ADCON0&0XC7;
		ADCON0=ADCON0|0X08;
		start_bin_2_ascii();	
		
		lcdcmd(0x91);
		ADCON0=ADCON0&0XC7;
		ADCON0=ADCON0|0X10;
		start_bin_2_ascii();

		lcdcmd(0xC3);
		ADCON0=ADCON0&0XC7;
		ADCON0=ADCON0|0X18;
		start_bin_2_ascii();

		lcdcmd(0xCA);
		ADCON0=ADCON0&0XC7;
		ADCON0=ADCON0|0X20;
		start_bin_2_ascii();

		lcdcmd(0xD1);
		ADCON0=ADCON0&0XC7;
		ADCON0=ADCON0|0X28;
		start_bin_2_ascii();

		lcdcmd(0x97);
		ADCON0=ADCON0&0XC7;
		ADCON0=ADCON0|0X30;
		start_bin_2_ascii();

		lcdcmd(0x9E);
		ADCON0=ADCON0&0XC7;
		ADCON0=ADCON0|0X38;
		start_bin_2_ascii();
		delay(1000);

	}
}
void welcome(void)
{
	lcdcmd(0x86);	
	for(l=0;l<=6;l++)
		lcddata(st[l]);		
	lcdcmd(0xC1);	
	for(l=0;l<=17;l++)
		lcddata(nd[l]);
	lcdcmd(0x96);	
	for(l=0;l<=15;l++)
		lcddata(rd[l]);
	delay(12000);

	lcdcmd(0x01);
	return;
}
void start(void)
{
	lcdcmd(0x80);	
	for(l=0;l<=2;l++)
		lcddata(an0[l]);
	lcdcmd(0x87);	
	for(l=0;l<=2;l++)
		lcddata(an1[l]);
	lcdcmd(0x8E);	
	for(l=0;l<=2;l++)
		lcddata(an2[l]);
	lcdcmd(0xC0);	
	for(l=0;l<=2;l++)
		lcddata(an3[l]);
	lcdcmd(0xC7);	
	for(l=0;l<=2;l++)
		lcddata(an4[l]);
	lcdcmd(0xCE);	
	for(l=0;l<=2;l++)
		lcddata(an5[l]);
	lcdcmd(0x94);	
	for(l=0;l<=2;l++)
		lcddata(an6[l]);
	lcdcmd(0x9B);	
	for(l=0;l<=2;l++)
		lcddata(an7[l]);
	lcdcmd(0xD4);	
	for(l=0;l<=19;l++)
		lcddata(na[l]);
	return;
}
void start_bin_2_ascii(void)
{
	for(a=1;a<=200;a++);
	ADCON0bits.GO=1;
	while(ADCON0bits.DONE==1);
	for(a=1;a<=400;a++);
	
	dec=ADRESH/10;
	d1=ADRESH%10;
	d2=dec%10;
	d3=dec/10;
	d1=d1|0x30;
	d2=d2|0x30;
	d3=d3|0x30;
	lcddata(d3);
	lcddata(d2);
	lcddata(d1);
	return;	
}
void lcddata(unsigned char value)
{
	lcdready();	 
	ldata=value;
	rs=1;
	rw=0;
	en=1;
	delay(100);
	en=0;
	return;
}
void lcdcmd(unsigned char value)
{
	lcdready();
	ldata=value;
	rs=0;
	rw=0;
	en=1;
	delay(100);
	en=0;
	return;
}	
void lcdready(void)
{
	TRISD=0xFF;
	rs=0;
	rw=1;
	do
	{
		en=1;
		delay(100);
		en=0;
	}	
	while(busy==1);
	TRISD=0x00;
	return;
}
void delay(unsigned double y)		// 1 us
{
	for(j=1;j<=y;j++)
	{
		T0CON=0X08;
		INTCON=0X00;
		TMR0H=0xFF;
		TMR0L=0xFC;
		T0CONbits.TMR0ON=1;
		while(INTCONbits.TMR0IF==0);
		T0CONbits.TMR0ON=0;
		INTCONbits.TMR0IF=0;
	}
	return;
}

