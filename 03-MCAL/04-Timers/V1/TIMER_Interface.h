/*
 * TIMER_Interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void TIMER0_VidInitialize (void) ;                                    //use to initialize TIMER
void TIMER_VidSetCallBack (u8 Copy_NumOfINT , void (*ptr)(void));     //use to point on excuted function in ISR
void Set_Time_S (u8 Copy_U8Time);                                     //to set wanted time
void Set_Time_mS (u16 Copy_U8Time);                                   //to set wanted time
void Set_Time_uS (u16 Copy_U8Time);                                   //to set wanted time
void TIMER0_PWM_INTI (void) ;                                         //to initialize PWM MODE
void Timer0_VidSETDUTY (u8 duty ) ;                                   //to select specific duty


#endif /* TIMER_INTERFACE_H_ */
