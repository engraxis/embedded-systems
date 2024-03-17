#include<P18F452.h>
void msdelay(unsigned int);
void main (void)
{
	TRISB=TRISC=TRISD=TRISA=TRISE=0X00;	

	while(1)
	{	
		PORTA=PORTB=PORTC=PORTD=0X11;
		msdelay(70);
		PORTA=PORTB=PORTC=PORTD=0X22;
		msdelay(70); 
		PORTE = 2;
		PORTA=PORTB=PORTC=PORTD=0X44;
		msdelay(70); 
		PORTA=PORTB=PORTC=PORTD=0X88;
		msdelay(70); 
		PORTE = 1;
	}
}

void msdelay(unsigned int delay)
{
	unsigned int i,j=0;
	for(i=0;i<delay;i++)
	{
		for(j=0;j<100;j++);
	}	
	
}