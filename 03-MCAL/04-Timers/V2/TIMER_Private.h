/*
 * TIMER_Private.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define NO_PRE   1
#define PRE_8    2
#define PRE_64   3
#define PRE_256  4
#define PRE_1024 5

#define OV       1
#define COMPARE  2
#define FAST_PWM 3

void __vector_11(void)    __attribute__((signal));                           //overflow mode in timer 0
void __vector_10(void)    __attribute__((signal));                           //compare mode in timer 0

void __vector_5(void)    __attribute__((signal));                           //overflow mode in timer 2
void __vector_4(void)    __attribute__((signal));                           //compare mode in timer 2

#define TCCR0 *((volatile u8*)(0x53))
#define FOC0  7
#define WGM00 6
#define COM01 5
#define COM00 4
#define WGM01 3
#define CS02  2
#define CS01  1
#define CS00  0

#define TCNT0 *((volatile u8*)(0x52))
#define TIMSK *((volatile u8*)(0x59))
#define OCIE0 1
#define TOIE0 0

#define OCR0 *((volatile u8*)(0x5C))

/*************************************************************/

#define TCCR2 *((volatile u8*)(0x45))
#define FOC2  7
#define WGM20 6
#define COM21 5
#define COM20 4
#define WGM21 3
#define CS22  2
#define CS21  1
#define CS20  0

#define TCNT2 *((volatile u8*)(0x44))

#define OCIE2 7
#define TOIE2 6

#define OCR2 *((volatile u8*)(0x43))

#endif /* TIMER_PRIVATE_H_ */
