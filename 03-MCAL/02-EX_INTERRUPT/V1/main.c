/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"DIO_interface.h"
#include "EX_INT_Interface.h"

#define LED_PORT 2
#define LED_PIN_0 0
#define LED_PIN_1 1
#define LED_PIN_2 2

#define HIGH 1
#define LOW 0


void TOGGLE_LED_0(void){
    DIO_VidTogglePinValue(LED_PORT,LED_PIN_0);
}
void TOGGLE_LED_1(void){
DIO_VidTogglePinValue(LED_PORT,LED_PIN_1);
}
void TOGGLE_LED_2(void){
DIO_VidTogglePinValue(LED_PORT,LED_PIN_2);
}
void main (void){
    DIO_VidSetPinDirection(LED_PORT,LED_PIN_0,HIGH);	   //to define led pin as out
    DIO_VidSetPinDirection(LED_PORT,LED_PIN_1,HIGH);	   //to define led pin as out
    DIO_VidSetPinDirection(LED_PORT,LED_PIN_2,HIGH);	   //to define led pin as out

    DIO_VidSetPinValue(LED_PORT,LED_PIN_0,LOW);	   //to define led pin as out
    DIO_VidSetPinValue(LED_PORT,LED_PIN_1,LOW);	   //to define led pin as out
    DIO_VidSetPinValue(LED_PORT,LED_PIN_2,LOW);	   //to define led pin as out

    GIE_VidEnable();                                   //to open global interrupt
	EX_INT_VidINIT();
    EX_PIE_VidEnable(0);                                  //to enable interrupt
    EX_PIE_VidEnable(1);                                  //to enable interrupt
    EX_PIE_VidEnable(2);                                  //to enable interrupt

	EX_INT_VidSetCallBack(0,TOGGLE_LED_0);
	EX_INT_VidSetCallBack(1,TOGGLE_LED_1);
	EX_INT_VidSetCallBack(2,TOGGLE_LED_2);

	while(1){

	}
}




