#line 1 "C:/Users/abx/Desktop/PIC18 GPS Tracking/GPS_Robot.c"
#line 17 "C:/Users/abx/Desktop/PIC18 GPS Tracking/GPS_Robot.c"
unsigned long north;
unsigned long east;
unsigned long north1;
unsigned long east1;
unsigned long north2;
unsigned long east2;
unsigned long north3;
unsigned long east3;

unsigned char raw_data[37];
unsigned char loop;
unsigned char x;
unsigned char gps_status;

void GPS (void)
{

 if(Usart_Data_Ready() ); { if ( Usart_Read() == '$'){
 while(!Usart_Data_Ready() ); if ( Usart_Read() == 'G'){
 while(!Usart_Data_Ready() ); if ( Usart_Read() == 'P'){
 while(!Usart_Data_Ready() ); if ( Usart_Read() == 'R'){
 while(!Usart_Data_Ready() ); if ( Usart_Read() == 'M'){
 while(!Usart_Data_Ready() ); if ( Usart_Read() == 'C'){


 for(loop=0; loop<=37; loop++)
 {
 while(!Usart_Data_Ready() );
 raw_data[loop] = Usart_Read();
 }
 Lcd_Cmd(LCD_CLEAR);

 Lcd_Cmd(LCD_FIRST_ROW);
 for(loop=14; loop<=24; loop++)
 {
 Lcd_Chr_Cp( raw_data[loop] );
 }

 Lcd_Cmd(LCD_SECOND_ROW);
 for(loop=26; loop<=37; loop++)
 {
 Lcd_Chr_Cp( raw_data[loop] );
 }

 gps_status=1; }}}}}}}
}

void extraction(void)
{
 if(! PORTD.F1 )
 {
 unsigned long cons;

 north = 0;
 cons = 10000000;
 for(loop=14; loop<=(24-2); loop++)
 {
 if(raw_data[loop]!='.')
 {
 raw_data[loop] = raw_data[loop] & 0x0F;
 raw_data[loop] = raw_data[loop] * cons;
 north = north + raw_data[loop];
 cons /= 10;
 }
 else
 cons /= 10;
 }

 east = 0;
 cons = 100000000;
 for(loop=26; loop<=(37-2); loop++)
 {
 if(raw_data[loop]!='.')
 {
 raw_data[loop] = raw_data[loop] & 0x0F;
 raw_data[loop] = raw_data[loop] * cons;
 east = east + raw_data[loop];
 cons /= 10;
 }
 else
 cons /= 10;
 }

 if(! PORTD.F1  && x==0)
 {
 x++;
 north1 = north;
 east1 = north;
 while(! PORTD.F1 );
 }
 if(! PORTD.F1  && x==1)
 {
 x++;
 north2 = north;
 east2 = east;
 while(! PORTD.F1 );
 }
 if(! PORTD.F1  && x==2)
 {
 x++;
 north3 = north;
 east3 = east;
 while(! PORTD.F1 );
 }
 }

}

void main(void)
{
 unsigned long error_north;
 unsigned long error_east;
 TRISB=0X00;
 TRISC=0X80;
 TRISD=0xFF;
  PORTC.F0  =  PORTC.F1  =  PORTC.F3  =  PORTC.F2  = 1;
 x=0;
 gps=0;
 Usart_Init(4800);
 Lcd_Init(&PORTB);
 Lcd_Cmd(LCD_CURSOR_OFF);
 Lcd_Out(1,4,"GPS  ROBOT");
 Lcd_Out(2,3,"UET LHR, FSD");
 Delay_1sec();Delay_1sec();Delay_1sec();
 Lcd_Cmd(LCD_CLEAR);
 while(1)
 {
 while(1)
 {
 while(gps_status==0)
 {
 GPS();
 }
 gps_status=0;
 extraction();
 if (x==3)
 {
 break;
 }
 }
 x=0;
 while( PORTD.F2 );
 Lcd_Cmd(LCD_CLEAR);
 while(1)
 {
 Lcd_Out(1,1,"STARTED MOVING");

 while(gps_status==0)
 {
 GPS();
 }
 gps_status=0;
 extraction();
 error_north = north1 - north;
 error_east = east1 - east;
  PORTC.F2 =0;
  PORTC.F1 =0;
 if (error_north <= 20 || error_east <= 20)
 {
  PORTC.F2 = PORTC.F1 =1;
 break;
 }
 }

 while(1);
 }
}
