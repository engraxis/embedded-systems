#ifndef LCD
#define LCD

#include<P18F452.h>
#include "setup.h" 

void setupLCD(void);
void lcdData(unsigned char);
void lcdCmd(unsigned char);
void lcdReady(void);

#endif