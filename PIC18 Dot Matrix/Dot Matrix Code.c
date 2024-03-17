//	Dot Matrix Display

// Data is the bit that will be available at the output parallel
// 		pins of S-in-P-out IC. Every time high to low transition
//		of Clock, bit available at DATA is shifted as LSB 

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18F452.h>

#define clock PORTBbits.RB6
#define data PORTBbits.RB7

unsigned char i,j,index1,n,
addr[11]={0xEA,0xEA,0x2A,0x2A,0x2A,0x2A,0xAA,0x82,0xFF,0xFF,0xFF},
cont[11];

void main(void)
{
	TRISB=0x00;
    TRISD=0X00;
	PORTB=PORTD=0X00;
    while(1)
    {
        for(n=0;n<=99;n++)
       {
            data=1;    
            for(i=0;i<=7;i++)
            {    
                clock=1;   
                PORTD=addr[i];
                clock=0;
                data=0; 
            }
        }
  
        for(j=0;j<=10;j++)  
        {
            cont[j]=addr[j];
        }
 
        for(j=0;j<=9;j++)   
        {
            addr[j]=cont[j+1];  
        }
        addr[10]=cont[0];
  
/*
	data=1;
	 for(j=0;j<=1;j++)   
        {
            clock=1;
			clock=0;  
        }
	data=0;
	 for(j=0;j<=1;j++)   
        {
            clock=1;
			clock=0;  
        }
*/	
    }
}
