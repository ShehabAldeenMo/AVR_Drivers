/*
 * PING_PONG_1_private.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */

#ifndef PING_PONG_1_PRIVATE_H_
#define PING_PONG_1_PRIVATE_H_

#define row_0 0
#define row_1 1

#define HIGH 1
#define LOW 0

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

#define PIN_OUT 2             //define pin express that ball go to LCD 1
#define PIN_IN 3              //define pin express that ball go to LCD 2
#define PIN_SAVED_1 4         //define pin that express that the ball saved in LCD 1
#define PIN_SAVED_2 5         //define pin that express that the ball saved in LCD 2

#define PORT_COMMUN PORTB

#define ping_paddle_right_ball 0
#define ping_paddle_right 1
#define ball_down_right 2
#define ball_down_left 3
#define ball_up_left 4
#define ball_up_right 5

#define last_col 15

#define INTER_PORT PORTD
#define INTER_PIN 2

#endif /* PING_PONG_1_PRIVATE_H_ */
