/*
 * TIMER_Interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#include "TIMER_Private.h"
#include "TIMER_CFG.h"

#if TIMER0_MODE != FAST_PWM

void TIMER0_VidInitialize (void) ;                                    //use to initialize TIMER0
void TIMER0_Set_Time_S (u8 Copy_U8Time);                                     //to set wanted time
void TIMER0_Set_Time_mS (u16 Copy_U8Time);                                   //to set wanted time
void TIMER_VidSetCallBack (u8 Copy_NumOfINT , void (*ptr)(void));     //use to point on excuted function in ISR

#elif TIMER0_MODE == FAST_PWM

void TIMER0_PWM_INTI (void) ;                                         //to initialize PWM MODE in timer0
void Timer0_VidSETDUTY (u8 duty ) ;                                   //to select specific duty in timer0

#endif

#if TIMER2_MODE != FAST_PWM

void TIMER2_VidInitialize (void) ;                                    //use to initialize TIMER0
void TIMER2_Set_Time_S (u8 Copy_U8Time);                                     //to set wanted time
void TIMER2_Set_Time_mS (u16 Copy_U8Time);                                   //to set wanted time

#elif TIMER2_MODE == FAST_PWM

void TIMER2_PWM_INTI (void) ;                                         //to initialize PWM MODE in timer0
void Timer2_VidSETDUTY (u8 duty ) ;                                   //to select specific duty in timer0

#endif

#endif /* TIMER_INTERFACE_H_ */
