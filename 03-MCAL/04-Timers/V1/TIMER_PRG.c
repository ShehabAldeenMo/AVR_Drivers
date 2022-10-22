/*
 * TIMER_PRG.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */

#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include "DIO_interface.h"
#include "TIMER_Interface.h"
#include "TIMER_Private.h"
#include "TIMER_CFG.h"
#include "LCD_Interface.h"

static void (*TIMER0_PFUNC)(void) = 0 ;
static void (*TIMER1_PFUNC)(void) = 0 ;
static void (*TIMER2_PFUNC)(void) = 0 ;

static u64 DESIRED_TIME ;
static u16 PRE_SCALAR ;
static f32 T_OV  ;
static f32 NUM_OV ;
static f32 PRE_LOAD ;

/*  to define timer 0 in main
    TIMER0_VidInitialize();
	GIE_VidEnable();                         //to clear interrupt flag after every call ISR
	TIMER_VidSetCallBack(0,TOGGLE_LED);
	Set_Time_mS(500);*/

void TIMER_VidSetCallBack (u8 Copy_NumOfINT , void (*ptr)(void)){
	switch (Copy_NumOfINT){
	case 0 :TIMER0_PFUNC = ptr ;             break ;
	case 1 :TIMER1_PFUNC = ptr ;             break ;
	case 2 :TIMER2_PFUNC = ptr ;             break ;
	}
}

/*******************To initialize OV or COMPARE mode***************************************/
//to check that you don't use OV or COMPARE mode
#if TIMER0_MODE != FAST_PWM

void TIMER0_VidInitialize (void) {
#if TIMER0_MODE == OV
	/*   overflow mode , to clear FOC0 and register
	     to enable interrupt , when rising flag jump to ISR     */
	TCCR0 = 0 ;
	SET_BIT(TIMSK,TOIE0);
#endif

#if TIMER0_MODE == COMPARE
	/*  CTC MODE , SET(WGM01)   CLEAR(WGM00)
	    to enable interrupt , when rising flag jump to ISR
	*/
	SET_BIT(TCCR0,WGM01);
	CLR_BIT(TCCR0,WGM00);

	SET_BIT(TIMSK,OCIE0);
#endif

	/*   CS02 CS01 CS00
	     0     0    1   no_prescalar   "NO_PRE"
	     0     1    0   clkI/O/8       "PRE_8"
	     0     1    1   clkI/O/64      "PRE_64"
	     1     0    0   clkI/O/256     "PRE_256"
	     1     0    1   clkI/O/1024    "PRE_1024"
	*/

    /*   to initialize timer pre_scalar      */
#if PRE_SCALAR_TYPE == NO_PRE
	CLR_BIT(TCCR0,CS02);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS00);
#elif PRE_SCALAR_TYPE == PRE_8
	CLR_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS00);
	PRE_SCALAR = 8 ;
#elif PRE_SCALAR_TYPE == PRE_64
	CLR_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS00);
	PRE_SCALAR = 64 ;
#elif PRE_SCALAR_TYPE == PRE_256
	SET_BIT(TCCR0,CS02);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS00);
	PRE_SCALAR = 256 ;
#elif PRE_SCALAR_TYPE == PRE_1024
	SET_BIT(TCCR0,CS02);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS00);
	PRE_SCALAR = 1024 ;
#endif

}//end FUNC TIMER_VidInitialize
#endif
/****************************************************************************/

void __vector_11(void){
	static u32 tick = 0 ;
	tick++ ;

	if (tick == (u32)NUM_OV ){
		TIMER0_PFUNC();                                     //to toggle led
		TCNT0 = 256-(256*PRE_LOAD);                         //to begin from specific value
		tick = 0 ;                                          //to start count from beginning again
	}//end if

}//end ISR FUNC

void __vector_10(void){
	TIMER0_PFUNC();                                     //to toggle led
}//end ISR FUNC

/*
    "NOT_PREFEREED because time is not accurate with high F every 1ms take in real 3ms"
    1) NO_PRE   every 1msec need t_ov = 32us , num_ov = 31.250 , pre_load = 0.25
    *****************************************************
    "USED in scale 1 mS"
    2) PRE_8   every 1msec need t_ov = 256us , num_ov = 3.90625 , pre_load = 0.90625
     *****************************************************
    "USED in scale 1S "
    3) PRE_64   every 1sec need t_ov = 2.048ms  , num_ov = 488.28125   , pre_load = 0.28125
    4) PRE_256  every 1sec need t_ov = 8.192ms  , num_ov = 122.0703125 , pre_load = 0.0703125
    5) PRE_1024 every 1sec need t_ov = 32.768ms , num_ov = 30.51757813 , pre_load = 0.51757813
*/

/******************** The part that use to count time  *************************/
//to check that you don't use OV or COMPARE mode
#if TIMER0_MODE != FAST_PWM

void Set_Time_S (u8 Copy_U8Time){
#warning "BE SURE THAT YOU USE OV MODE TO COUNT TIME ACCURATE IN S"

	DESIRED_TIME = (u64)Copy_U8Time*1000 ;               //time in ms
    T_OV = (256*(f32)PRE_SCALAR)/8000 ;                  //time in ms
	NUM_OV = DESIRED_TIME / T_OV ;                       //number of overflow wanted in entered if
	PRE_LOAD  = NUM_OV -( (u32)(DESIRED_TIME /T_OV) );   //the value which should be in TCNT to make time more accurate
	if ( NUM_OV > (u32)NUM_OV )
		NUM_OV++;

	//to begin from specific value
	TCNT0 = 256-(256*PRE_LOAD );
}

void Set_Time_mS (u16 Copy_U8Time){
#warning "BE SURE THAT YOU USE OV MODE TO COUNT TIME ACCURATE IN mS"

	DESIRED_TIME = Copy_U8Time ;                         //time in ms
    T_OV = (256*(f32)PRE_SCALAR)/8000 ;                  //time in us
	NUM_OV = DESIRED_TIME / T_OV ;                       //number of overflow wanted in entered if
	PRE_LOAD  = NUM_OV -( (u32)(DESIRED_TIME /T_OV) );   //the value which should be in TCNT to make time more accurate
	if ( NUM_OV > (u32)NUM_OV )
		NUM_OV++;

#if PRE_SCALAR_TYPE != PRE_8
#error "YOU SELECTED PRE_SCALAR MAKE MORE THAN 1 ms"
#endif

	//to begin from specific value
	TCNT0 = 256-(256*PRE_LOAD );
}


void Set_Time_uS (u16 Copy_U8Time){
#warning "BE SURE THAT YOU USE COMPARE MODE TO COUNT TIME ACCURATE IN uS"

#if PRE_SCALAR_TYPE == NO_PRE
	Copy_U8Time *= 8 ;                 //to make 1us need 8 counts
#warning "YOU ARE USED CORRECT PRE_SCALAR FOR US"
#endif

#if PRE_SCALAR_TYPE == PRE_8
#warning "YOU ARE USED CORRECT PRE_SCALAR FOR US"
#endif

#warning "BE SURE THAT YOU DON't USE ( Copy_U8Time > 255 ) "
	OCR0 = Copy_U8Time ;

}

#endif
/*********************************************************************************/

//to check that you use FAST_PWM mode
#if TIMER0_MODE == FAST_PWM

void TIMER0_PWM_INTI (void) {
	// to initialize timer0 on 0 , FOCO = 0
	TCCR0 = 0 ;

	// 1 1 Fast PWM
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);

	//1 0 Clear OC0 on compare match, set OC0 at TOP ,  NON_INVERED MODE PWM
	SET_BIT(TCCR0,COM01);
	CLR_BIT(TCCR0,COM00);

    /*   to initialize timer pre_scalar      */
	#if PRE_SCALAR_TYPE == NO_PRE
		CLR_BIT(TCCR0,CS02);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS00);
	#elif PRE_SCALAR_TYPE == PRE_8
		CLR_BIT(TCCR0,CS02);
		SET_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS00);
	#elif PRE_SCALAR_TYPE == PRE_64
		CLR_BIT(TCCR0,CS02);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS00);
	#elif PRE_SCALAR_TYPE == PRE_256
		SET_BIT(TCCR0,CS02);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS00);
	#elif PRE_SCALAR_TYPE == PRE_1024
		SET_BIT(TCCR0,CS02);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS00);
	#endif
}

void Timer0_VidSETDUTY (u8 duty ) {
	OCR0 = duty ;
}

#endif
