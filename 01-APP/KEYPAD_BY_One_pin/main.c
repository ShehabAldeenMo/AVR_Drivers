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

	while(1){
   	    LCD_VidPosCur(0,0);
     	LCD_VidSendString("ANALOG : ");
		LCD_VidPrintVar(ADC_VidReadChannel(0));
		LCD_VidSendString(" mV");
		LCD_VidPosCur(1,0);
		LCD_VidSendString("BUTTON : ");
        switch (ADC_VidReadChannel(0)){
        case 4002 : LCD_VidSendChar('7') ; _delay_ms(1000); LCD_VidClear(); break ;
        case 3504 : LCD_VidSendChar('4') ; _delay_ms(1000); LCD_VidClear(); break ;
        case 1500 : LCD_VidSendChar('1') ; _delay_ms(1000); LCD_VidClear(); break ;
        case 1603 : LCD_VidSendChar('8') ; _delay_ms(1000); LCD_VidClear(); break ;
        case 801  : LCD_VidSendChar('9') ; _delay_ms(1000); LCD_VidClear(); break ;
        case 1402 : LCD_VidSendChar('5') ; _delay_ms(1000); LCD_VidClear(); break ;
        case 698  : LCD_VidSendChar('6') ; _delay_ms(1000); LCD_VidClear(); break ;
        case 601  : LCD_VidSendChar('2') ; _delay_ms(1000); LCD_VidClear(); break ;
        case 298  : LCD_VidSendChar('3') ; _delay_ms(1000); LCD_VidClear(); break ;
        }
	}//end while
}//end main
