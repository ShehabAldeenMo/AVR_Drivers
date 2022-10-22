/*
 *  File : SEVEN_SEG_TASK2.c
 *  DATE: 6/9/2022
 *  Author: Shehab aldeen
 *  Describtion : diplay 0:99  on 2 seven_segment by 9 PINS
 */
#include"DIO_interface.h"
#include"SevSeg_Interface.h"
#include"avr/delay.h"
/* TASK : count from 0 : 99 on two 7-seg */

void main (void) {
	DIO_VidSetPortDirection(0,0xff) ;
	DIO_VidSetPinDirection(2,7,1);
	while (1){
		u8 i=0 ;//the digit which displayed
		u8 tick = 0 ;//after every 1 second the digit is incremented
	while( i<100 ){
		/*we make lines 19:25 by this way to force compilar to display 2 digit in fast way  */
    	SevSeg_VidDisplayNum(i/10);
		DIO_VidSetPinValue(0,6,0);
		DIO_VidSetPinValue(2,7,1);
    	_delay_ms(5);//exert 5 ms
	   	SevSeg_VidDisplayNum(i%10);
    	DIO_VidSetPinValue(0,6,1);
    	DIO_VidSetPinValue(2,7,0);
		_delay_ms(5);//exert 5 ms
		/*now while hinged in display 2 digits quickly than ur eye and in runtime tick is incremented
		 * to increnebt i after 1 second to hing in while by the same way */
		tick++ ;//total time exert is 10 ms so we need 100 tick to make 1 second
		if (tick == 100){
            tick = 0 ;
			i++ ;
		}//end if
	   }//end for loop
	}//end while loop
}//end FUNC main
