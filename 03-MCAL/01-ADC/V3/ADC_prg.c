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

#ifdef AVCC_5V
	ADMUX = 0x40 ;
#endif

#ifdef AVREF_2.5
	ADMUX = 0xC0 ;
#endif

#ifdef EX_REF
	ADMUX = 0x00 ;
#endif

	/*to enable interrupt of ADC :
	 1) open global interrupt
	 2) set ADIE
	  */
	GIE_VidEnable();
	SET_BIT(ADCSRA,ADIE);

#ifdef PRE_SCALAR_2
	ADCSRA = (1<<ADEN) | (1<<ADPS0) ;
#endif

#ifdef PRE_SCALAR_4
	ADCSRA = (1<<ADEN)  | (1<<ADPS1)  ;
#endif

#ifdef PRE_SCALAR_8
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0) ;
#endif

#ifdef PRE_SCALAR_16
	ADCSRA = (1<<ADEN) | (1<<ADPS2) ;
#endif

#ifdef PRE_SCALAR_32
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0) ;
#endif

#ifdef PRE_SCALAR_64
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) ;
#endif

#ifdef PRE_SCALAR_128
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) ;
#endif

}

u16 ADC_VidReadChannel (u8 Copy_U8Channel){
	CLR_BIT(ADMUX,ADLAR);                             //clear ADLAR , register data

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
	CLR_BIT(ADCSRA,ADEN);                             //to disable ADC perpherial

	/*to disable interrupt of ADC :
	 1) close global interrupt
	 2) clear ADIE
	  */
	GIE_VidDisable();
	CLR_BIT(ADCSRA,ADIE);
}


