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
#include "ADC_cfg.h"

void ADC_VidInit (void){
/* to choose which Voltage reference we need */
#if VREF_USED == AVCC_5V
	ADMUX = 0x40 ;
#elif VREF_USED ==  INTERNAL_AVREF_2.5
	ADMUX = 0xC0 ;
#elif VREF_USED ==  EX_REF
	ADMUX = 0x00 ;
#endif

/*  to choose which pre_scalar we need in conversion  */
#if PRE_SCALAR == PRE_SCALAR_2
	ADCSRA = (1<<ADEN) | (1<<ADPS0) ;
#elif PRE_SCALAR == PRE_SCALAR_4
	ADCSRA = (1<<ADEN)  | (1<<ADPS1)  ;
#elif PRE_SCALAR ==  PRE_SCALAR_8
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0) ;
#elif PRE_SCALAR ==  PRE_SCALAR_16
	ADCSRA = (1<<ADEN) | (1<<ADPS2) ;
#elif PRE_SCALAR ==   PRE_SCALAR_32
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0) ;
#elif PRE_SCALAR ==  PRE_SCALAR_64
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) ;
#elif PRE_SCALAR == PRE_SCALAR_128
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) ;
#endif

/*  to choose which adjusted we need to read from ADC DATA REGISTER   */
#if ADJUSTED_USED == RIGHT_ADJEUSTED
	CLR_BIT(ADMUX,ADLAR);                             //CLEAR ADLAR , RIGHT_ADJEUSTED
#elif ADJUSTED_USED == LEFT_ADJUSTED
	SET_BIT(ADMUX,ADLAR);                             //SET ADLAR , LEFT_ADJUSTED
#endif

}

u16 ADC_VidReadChannel (u8 Copy_U8Channel){
	ADMUX &= 0xE0 ;                                   //to clear ADMUX
	ADMUX |= ( 0x1F & Copy_U8Channel ) ;              //to check that the channel out of 8 pins
	SET_BIT(ADCSRA,ADSC) ;                            //to start conversion
	CLR_BIT(ADCSRA,ADATE) ;                           //to disable  Auto Trigger
	while ( GET_BIT(ADCSRA,ADIF) == 0 ) ;             //to stac while conversion
    SET_BIT(ADCSRA,ADIF);                             //to clear flag

#if ADJUSTED_USED == RIGHT_ADJEUSTED
    return ( (u64)ADC_REG*VREF*1000)/MAX_DIGITAL ;        //to return Analog value in mv value
#elif ADJUSTED_USED == LEFT_ADJUSTED
    ADCH = (ADCH<<2) ;
    return ( (u64)ADCH*VREF*1000)/MAX_DIGITAL ;        //to return Analog value in mv value
#endif
}

void ADC_VidDeinit (void){
	CLR_BIT(ADCSRA,ADEN);                             //to disable ADC perpherial
    ADMUX = 0x00 ;                                    //to clear ADMUX
}


