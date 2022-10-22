/*
 *  File : main.c
 *  DATE: 11/9/2022
 *  Author: Shehab aldeen
 *  Version : V1
 *  Describtion :LCD_animation_3 "PING PONG"
 */
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_Interface.h"
#include "avr/delay.h"

#define row_0 0
#define row_1 1

#define ping_paddle_right_ball 0
#define ping_paddle_right 1
#define ping_paddle_left 2
#define ball_down_right 3
#define ball_down_left 4
#define ball_up_left 5
#define NET_PART_1 6
#define NET_PART_2 7
#define NET_BALL 0

#define last_col 15
#define first_col 0
#define middle_col 7
#define col_4 4

void main ( void )
{
	//to initialize LCD
	LCD_VidInit();

	while(1)
	{
		//to open CGRAM location
		LCD_VidSendCommend(0b01000000);

		//to make ping paddle right address 0 with ball
		LCD_VidSendChar(0b00000100);
		LCD_VidSendChar(0b00001110);
		LCD_VidSendChar(0b00000100);
		LCD_VidSendChar(0b00001111);
		LCD_VidSendChar(0b00001111);
		LCD_VidSendChar(0b00000111);
		LCD_VidSendChar(0b00001011);
		LCD_VidSendChar(0b00010000);


		//to make ping paddle right address 1
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00001111);
		LCD_VidSendChar(0b00001111);
		LCD_VidSendChar(0b00000111);
		LCD_VidSendChar(0b00001011);
		LCD_VidSendChar(0b00010000);

		//to make ping paddle left address 2
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00011110);
		LCD_VidSendChar(0b00011110);
		LCD_VidSendChar(0b00011100);
		LCD_VidSendChar(0b00011010);
		LCD_VidSendChar(0b00000001);

	    //to make ball down right address 3
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000010);
		LCD_VidSendChar(0b00000111);
		LCD_VidSendChar(0b00000111);
		LCD_VidSendChar(0b00000010);


	    //to make ball down left address 4
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00001000);
		LCD_VidSendChar(0b00011100);
		LCD_VidSendChar(0b00011100);
		LCD_VidSendChar(0b00001000);

	    //to make ball up left address 5
		LCD_VidSendChar(0b00001000);
		LCD_VidSendChar(0b00011100);
		LCD_VidSendChar(0b00011100);
		LCD_VidSendChar(0b00001000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);

		//to make net part 1 address 6
		LCD_VidSendChar(0b00000001);
		LCD_VidSendChar(0b00000010);
		LCD_VidSendChar(0b00000100);
		LCD_VidSendChar(0b00001000);
		LCD_VidSendChar(0b00010000);
		LCD_VidSendChar(0b00001000);
		LCD_VidSendChar(0b00000100);
		LCD_VidSendChar(0b00000010);

		//to make net part 2 address 7
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000000);
		LCD_VidSendChar(0b00000100);
		LCD_VidSendChar(0b00001010);
		LCD_VidSendChar(0b00010001);

	    static s8 local_col = 14 ;

	    //to show right ping paddle with ball in beginning
		if (local_col == 14 ){
			LCD_VidPosCur(row_1,last_col);
			LCD_VidSendChar(ping_paddle_right_ball);
			_delay_ms(100);
		}

		//to show right ping paddle in beginning
		LCD_VidPosCur(row_1,last_col);
		LCD_VidSendChar(ping_paddle_right);

		//to show left ping paddle in beginning
		LCD_VidPosCur(row_1,first_col);
		LCD_VidSendChar(ping_paddle_left);

		//to show net in the middle of LCD
		LCD_VidPosCur(row_1,middle_col);
		LCD_VidSendChar(NET_PART_1);
		LCD_VidPosCur(row_0,middle_col+1);
		LCD_VidSendChar(NET_PART_2);

		//to make ball drop down to up in specific cell and the next to it
		for (s8 i = 1 ; i >= 0 ; i--){
			//to show  ball down right
			LCD_VidPosCur(i,local_col);
			LCD_VidSendChar(ball_down_right);
			_delay_ms(100);

			//to show ball up left
			LCD_VidPosCur(i,local_col);
			LCD_VidSendChar(ball_up_left);
			_delay_ms(100);

			//to clear cell
			LCD_VidPosCur(i,local_col);
			LCD_VidSendChar(' ');

			local_col-- ;
		}//end for loop

		//to make ball fly up
        while (local_col <= 12 && local_col >= 5){

        	if (local_col == 8 ){
        		//to open CGRAM location
        		LCD_VidSendCommend(0b01000000);

        		//to make net with ball address 7
        		LCD_VidSendChar(0b00000100);
        		LCD_VidSendChar(0b00001110);
        		LCD_VidSendChar(0b00001110);
        		LCD_VidSendChar(0b00000100);
        		LCD_VidSendChar(0b00000000);
        		LCD_VidSendChar(0b00000100);
        		LCD_VidSendChar(0b00001010);
        		LCD_VidSendChar(0b00010001);

        		LCD_VidPosCur(row_0,middle_col+1);
        		LCD_VidSendChar(NET_BALL);
    			_delay_ms(100);
    			LCD_VidPosCur(row_0,middle_col+1);
    			LCD_VidSendChar(NET_PART_2);
    			local_col--;

        	}
			//to show  ball up
			LCD_VidPosCur(row_0,local_col);
			LCD_VidSendChar(ball_up_left);
			_delay_ms(100);

			//to clear cell
			LCD_VidPosCur(row_0,local_col);
			LCD_VidSendChar(' ');

			local_col--;
        }

		//to make ball drop from up to down

		//to show  ball down left
		LCD_VidPosCur(row_0,local_col);
		LCD_VidSendChar(ball_down_left);
		_delay_ms(100);

		//to clear cell
		LCD_VidPosCur(row_0,local_col);
		LCD_VidSendChar(' ');

		local_col-- ;

		//to make ball drop up to down in specific cell and the next to it
		for (s8 i = 1 ; i >= 0 ; i--){

			//to show  ball down right
			LCD_VidPosCur(i,local_col);
			LCD_VidSendChar(ball_down_right);
			_delay_ms(100);

			//to show ball up left
			LCD_VidPosCur(i,local_col);
			LCD_VidSendChar(ball_up_left);
			_delay_ms(100);

			//to clear cell
			LCD_VidPosCur(i,local_col);
			LCD_VidSendChar(' ');

			local_col-- ;
		}//end for loop

		//to make ball fly up
        while (local_col >= 0){

			//to show  ball up
			LCD_VidPosCur(row_0,local_col);
			LCD_VidSendChar(ball_up_left);
			_delay_ms(100);

			//to clear cell
			LCD_VidPosCur(row_0,local_col);
			LCD_VidSendChar(' ');

			local_col--;
        }

		if(0 >= local_col){
			local_col = 14 ;
			LCD_VidClear();
			//to show state wining
			for (u8 i = 0 ; i < 3 ; i++){
				LCD_VidPosCur( row_0 , col_4 ) ;
				LCD_VidSendString(" G O A L ");
				LCD_VidPosCur( row_1 , col_4 ) ;
				LCD_VidSendString(" G O A L ");
				_delay_ms(500);
				LCD_VidClear();
				_delay_ms(500);
			}
		}//end if

	}//end while
}//end main
