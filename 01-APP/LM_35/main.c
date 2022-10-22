/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include "LCD_Interface.h"
#include "DIO_interface.h"
#include "INTERRUPT_Interface.h"
#include "ADC_interface.h"
#include "avr/delay.h"

void main (void){
	//to initailize LCD
	LCD_VidInit();

	//initialize ADC
	ADC_VidInit();

	u16 DIGITAL ;

	while(1){
   	    LCD_VidPosCur(0,0);
     	LCD_VidSendString("ANA:");
		LCD_VidPrintVar(ADC_VidReadChannel(0));
		LCD_VidSendString("mV");
		LCD_VidSendString(" D:");
		DIGITAL = ( ((u64)ADC_VidReadChannel(0)*1023)/5000)  ;
		LCD_VidPrintVar(DIGITAL);
		LCD_VidPosCur(1,0);
		LCD_VidSendString("TEMP:");
		LCD_VidPrintVar(ADC_VidReadChannel(0)/10);
		LCD_VidSendChar('C');
	}//end while
}//end main
