//-- LCD
//PORTD
//RC0
//RC1
//RC2

#include <P18F452.h>
#include "setup.h"
#include "lcd.h"
#include<string.h>

/*#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF*/
#pragma config WDT=OFF
unsigned int i = 0;
unsigned char info2[] = "Jalebi Machine";

void main(void)
{		
	setupLCD();
	
	lcdCmd(0x80);
	for(i=0; i < strlen(info2); i++)
		lcdData(info2[i]);

	while(1)
	{
		PORTB = 0x55;
		msDelay(1000);
		PORTB = 0xAA;
		msDelay(1000);
	}
}