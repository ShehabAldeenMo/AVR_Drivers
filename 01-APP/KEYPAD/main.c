/*
 *  File : main.c
 *  DATE: 10/9/2022
 *  Author: Shehab aldeen
 *  Version : V1
 *  Describtion :KEYPAD_DRIVER
 */
#include"avr/delay.h"
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_Interface.h"
#include "KeyPad_Interface.h"

/*main*/

void main (void){
	s8 num ;
	LCD_VidInit();
	KeyPad_VidInit();
	 while (1)
	    {
		 num = KeyPad_U8GetNUM () ;
		 if ( !( num == 50 ||  num == '/' ||  num == '*' ||  num == '+' ||  num == '-' ||  num == '=')  )
		 {
			 LCD_VidPrintVar(num ) ;
		 }//end if
		 else if (num != 50){
		     LCD_VidSendChar(num);
		 }

	   }//end while loop
}//end main

