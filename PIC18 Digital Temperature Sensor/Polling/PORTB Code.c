//	DIGITAL TEMPERATURE SENSOR
//					(interrupt based programming)

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
void delay(unsigned double);
void lcdready(void);
void bin_2_ascii(void);

unsigned char i,j,k;
unsigned char d1,d2,d3,dec;

void main(void)
{
	unsigned char st[]=" DIGITAL THERMOMETER";
	unsigned char tem[]="Temperature =    'C";
	unsigned char nam[]="Abdullah Tahir";
	TRISD=TRISB=0X00;
	PIR1bits.ADIF=0;
	PORTA=0xFF;
	ADCON0=0x49;
	ADCON1=0x01;	
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x0C);
	lcdcmd(0x38);
	lcdcmd(0x80);
	for(i-0;i<=strlen(st);i++)
		lcddata(st[i]);
	lcdcmd(0xC3);
	for(i=0;i<=strlen(tem);i++)
		lcddata(nam[i]);
	lcdcmd(0xD4);
	for(i=0;i<=strlen(tem);i++)
		lcddata(tem[i]);
	while(1)
	{	
		delay(15);
		ADCON0bits.GO=1;
		delay(20);
		while(ADCON0bits.DONE==1);
		bin_2_ascii();
	}
}
void lcddata(unsigned char value)
{
	lcdready();	 
	ldata=value;
	rs=1;
	rw=0;
	en=1;
	delay(10);
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
		delay(10);
		en=0;
	}	
	while(busy==1);
	TRISD=0x00;
	return;
}
void lcdcmd(unsigned char value)
{
	lcdready();
	ldata=value;
	rs=0;
	rw=0;
	en=1;
	delay(10);
	en=0;
	return;
}	
void bin_2_ascii(void)
{
	dec=ADRESH/10;
	d1=ADRESH%10;
	d2=dec%10;
	d3=dec/10;
	d1=d1|0x30;
	d2=d2|0x30;
	d3=d3|0x30;
	lcdcmd(0xE2);
	lcddata(d3);
	lcddata(d2);
	lcddata(d1);
	PIR1bits.ADIF=0;
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
