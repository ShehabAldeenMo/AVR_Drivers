/*
 *  File : main.c
 *  DATE: 11/9/2022
 *  Author: Shehab aldeen
 *  Version : V1
 *  Describtion :LCD_animation_2
 */
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_Interface.h"
#include "avr/delay.h"

void main ( void )
{
    //to initialize LCD
	LCD_VidInit();

	//to display my name ‘Â«» from address 0:3

	//to open CGRAM location 0 = ‘
	LCD_VidSendCommend(0b01000000);

	LCD_VidSendChar(0b00000100);
	LCD_VidSendChar(0b00010001);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00010101);
	LCD_VidSendChar(0b00010101);
	LCD_VidSendChar(0b00011010);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);

	//to open CGRAM location 1 = Â
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000100);
	LCD_VidSendChar(0b00001010);
	LCD_VidSendChar(0b00011111);
	LCD_VidSendChar(0b00001010);
	LCD_VidSendChar(0b00000100);


	//to open CGRAM location 2 = «
	LCD_VidSendChar(0b00000100);
	LCD_VidSendChar(0b00000100);
	LCD_VidSendChar(0b00000100);
	LCD_VidSendChar(0b00000100);
	LCD_VidSendChar(0b00000100);
	LCD_VidSendChar(0b00000111);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);

	//to open CGRAM location 3 = »
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00010001);
	LCD_VidSendChar(0b00010001);
	LCD_VidSendChar(0b00011111);
	LCD_VidSendChar(0b00000100);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);

	 u8 local_i = 0 ;
	 u8 local_row = 0 ;
     while(1){
      	if (local_i == 13){
				local_i = 0 ;
				local_row++ ;
			}
			LCD_VidPosCur(local_row%2,15-local_i) ;
		    LCD_VidSendChar(0);
		    LCD_VidPosCur(local_row%2,14-local_i);
		    LCD_VidSendChar(1);
		    LCD_VidPosCur(local_row%2,13-local_i);
		    LCD_VidSendChar(2);
		    LCD_VidPosCur(local_row%2,12-local_i);
		    LCD_VidSendChar(3);
		    local_i++ ;
		    _delay_ms(250);
		    LCD_VidClear();
         }
}
