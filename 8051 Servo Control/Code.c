///////////////////////////////////////////////////////////
// Servo Motor Control using AT89C51 (8051) Microcontroller
///////////////////////////////////////////////////////////

#include <REGX51.H>

sbit sm1=P2^0;
sbit sm2=P2^1;

void move_sm1(unsigned int);		// passing required value of theta as argument
void move_sm2(unsigned int);		
void sm_delay(unsigned int);		// creating basic delay of 40us(including over head)
void delay(unsigned int);			// basic delay of 1s approx

unsigned int preset,x;				// preset value that will essentially create delay of 1us

void main (void)
{
	P0=P1=P2=P3=0;
	preset=26;

	TMOD=0X02;
	TH0=-1;
//	while(1)
	{
	move_sm1(25);
	for(x=1;x<=55000;x++);
	move_sm1(0);
	for(x=1;x<=55000;x++);
	move_sm1(30);
	}
	while(1);
}
void move_sm1(unsigned int angle)
{
																//	des_td=(.001/180)*angle;
																//	des_td=des_td/.00004;
																//	sm_delay(des_td);
	sm1=1;
	sm_delay(angle);
	sm1=0;	
	sm_delay(100);
}
void move_sm2(unsigned int angle)
{
																//	des_td=(.001/180)*angle;
																//	des_td=des_td/.00004;																//	sm_delay(des_td);
	sm2=1;
	sm_delay(angle);
	sm2=0;	
	sm_delay(100);
}
void sm_delay(unsigned int des_td_angle)
{
	
	for(x=0;x<preset+des_td_angle;x++)
	{
		TR0=1;
		while(TF0==0);
		TR0=0;
		TF0=0;
	}
	return;
}
