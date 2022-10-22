/*
 * INT_prg.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */

#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include "DIO_interface.h"
#include "INT_Interface.h"
#include "LCD_Interface.h"
#include"INT_cfg.h"
#include "INT_private.h"

#define last_col 15
#define ping_paddle_right 1

u8 Global_row = 1 ;

/**********************************************************/
void INT_VidINIT(void){

#ifdef INT0       //to define edge of interrupt 0
    if (INT0_LOW) {
        //INT0 sense control = low level
    	CLR_BIT(MCUCR,ISC00);
    	CLR_BIT(MCUCR,ISC01);
    }
	else if (INT0_CHANG) {
		//INT0 sense control = change edge
    	SET_BIT(MCUCR,ISC00);
    	CLR_BIT(MCUCR,ISC01);
    }
    else if (INT0_FALLING){
		//INT0 sense control = falling edge
        DIO_VidSetPinDirection(PORTD,PD2,LOW);     //to define bit interrupt 0 as input
        DIO_VidSetPinValue(PORTD,PD2,HIGH);        // pull up resistor on interrupt 0
		CLR_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);
    }
    else if (INT0_RASING) {
        //INT0 sense control = raising edge
    	SET_BIT(MCUCR,ISC00);
        SET_BIT(MCUCR,ISC01);
    }
#endif

#ifdef INT1      //to define edge of interrupt 1
    if (INT1_LOW) {
        //INT1 sense control = low level
    	CLR_BIT(MCUCR,ISC10);
    	CLR_BIT(MCUCR,ISC11);
    }
	else if (INT1_CHANG) {
		//INT1 sense control = change edge
    	SET_BIT(MCUCR,ISC10);
    	CLR_BIT(MCUCR,ISC11);
    }
    else if (INT1_FALLING){
		//INT1 sense control = falling edge
        DIO_VidSetPinDirection(PORTD,PD3,LOW);     //to define bit interrupt 1 as input
        DIO_VidSetPinValue(PORTD,PD3,HIGH);        // pull up resistor on interrupt 1
		CLR_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);
    }
    else if (INT1_RASING) {
        //INT1 sense control = raising edge
    	SET_BIT(MCUCR,ISC10);
        SET_BIT(MCUCR,ISC11);
    }
#endif

#ifdef INT2      //to define edge of interrupt 2
    if (INT2_FALLING){
        DIO_VidSetPinDirection(PORTB,PB2,LOW);     //to define bit interrupt 2 as input
        DIO_VidSetPinValue(PORTB,PB2,HIGH);        // pull up resistor on interrupt 2
		CLR_BIT(MCUCSR,ISC2);		//INT2 sense control = falling edge
    }
    else if (INT2_RASING) {
    	SET_BIT(MCUCSR,ISC2);        //INT2 sense control = raising edge
    }
#endif

}

/**********************************************************/
void GIE_VidEnable (void){
	//to enable general interrupt
	SET_BIT(SREG,I_BIT);
}

void GIE_VidDisable (void){
	//to disable general interrupt
	CLR_BIT(SREG,I_BIT);
}

/**********************************************************/
void PIE_VidEnable(u8 COPY_U8INT_NUM){
	switch(COPY_U8INT_NUM) {
	case 0 : SET_BIT(GICR,INT0);  break ;   //INT0 Enable
	case 1 : SET_BIT(GICR,INT1);  break ;   //INT1 Enable
	case 2 : SET_BIT(GICR,INT2);  break ;   //INT2 Enable
	}
}

void PIE_VidDisable(u8 COPY_U8INT_NUM){
	switch(COPY_U8INT_NUM) {
	case 0 : CLR_BIT(GICR,INT0);  break ;   //INT0 Enable
	case 1 : CLR_BIT(GICR,INT1);  break ;   //INT1 Enable
	case 2 : CLR_BIT(GICR,INT2);  break ;   //INT2 Enable
	}
}

/**********************************************************/
void __vector_1(void){
	//to show right ping paddle in beginning
	LCD_VidPosCur(Global_row%2,last_col);
	LCD_VidSendChar(ping_paddle_right);

	Global_row++;

	//to clear cell
	LCD_VidPosCur(Global_row%2 ,last_col);
	LCD_VidSendChar(' ');
}

void __vector_2(void){

}

void __vector_3(void){

}




