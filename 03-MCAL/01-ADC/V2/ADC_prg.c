/*
 * ADC_prg.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include "INTERRUPT_Interface.h"
#include "ADC_interface.h"
#include "ADC_private.h"

void ADC_VidInit (void){
	/*to select :  REFS1   REFS0
	  External V    0        0          on Aref
	  Vref = 5 V    0        1          on Avcc
	  Vref = 2.5 V  1        1          internal
	 */
	ADMUX = 0x40 ;

	/*to enable interrupt of ADC :
	 1) open global interrupt
	 2) set ADIE
	  */
	GIE_VidEnable();
	SET_BIT(ADCSRA,ADIE);

	/*
	 - to enable ADC perpherial
	 - to select specific :
	 1) pre_scalar  /2    0 0 0 or 0 0 1
	 2) pre_scalar  /4    0 1 0
	 3) pre_scalar  /8    0 1 1
	 4) pre_scalar  /16   1 0 0
	 5) pre_scalar  /32   1 0 1
	 6) pre_scalar  /64   1 1 0
	 7) pre_scalar  /128  1 1 1
	  */
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) ;

}

u16 ADC_VidReadChannel (u8 Copy_U8Channel){
	//clear ADLAR , register data
	CLR_BIT(ADMUX,ADLAR);

	//to determine which channel that we need
	switch (Copy_U8Channel){
	case 0 : ADMUX &= 0xE0 ;                break ;
	case 1 : ADMUX &= 0xE1 ;                break ;
	case 2 : ADMUX &= 0xE2 ;                break ;
	case 3 : ADMUX &= 0xE3 ;                break ;
	case 4 : ADMUX &= 0xE4 ;                break ;
	case 5 : ADMUX &= 0xE5 ;                break ;
	case 6 : ADMUX &= 0xE6 ;                break ;
	case 7 : ADMUX &= 0xE7 ;                break ;
	}
	SET_BIT(ADCSRA,ADSC) ;                            //to start conversion
	CLR_BIT(ADCSRA,ADATE) ;                           //to disable  Auto Trigger
	while ( GET_BIT(ADCSRA,ADIF) == 0 ) ;             //to stac while conversion
    return ( (u64)ADC*VREF*1000)/MAX_DIGITAL ;        //to return Analog value in mv value
}

void ADC_VidDeinit (void){
	//to disable ADC perpherial
	CLR_BIT(ADCSRA,ADEN);

	/*to disable interrupt of ADC :
	 1) close global interrupt
	 2) clear ADIE
	  */
	GIE_VidDisable();
	CLR_BIT(ADCSRA,ADIE);
}


