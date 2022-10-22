/*
 *  File : main.c
 *  DATE: 6/9/2022
 *  Author: Shehab aldeen
 *  Version : V1
 *  Describtion : PING_PONG_1
*/

#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_Interface.h"
#include "INT_Interface.h"
#include "avr/delay.h"
#include "PING_PONG_2_private.h"

extern Global_row ;

void main ( void )
{
	//define pin to check that the ball isn't saved in LCD 1
	DIO_VidSetPinDirection(PORT_COMMUN,PIN_SAVED_1,LOW);

	//define pin to check that the ball isn't saved in LCD 2
	DIO_VidSetPinDirection(PORT_COMMUN,PIN_SAVED_2,HIGH);
	DIO_VidSetPinValue(PORT_COMMUN,PIN_SAVED_2,LOW);

     /***********************/
	//to initialize interrupt 2
    GIE_VidEnable();        //to open global interrupt

    /* 0 :  enable perpherial interrupt 0
       1 : enable perpherial interrupt 1
       2 : enable perpherial interrupt 2
     */
    PIE_VidEnable(2);       //to enable perpherial interrupt
    INT_VidINIT();          //to initialize interrupt

	//to initialize LCD
	LCD_VidInit();

	//define two pins to communicate between two lcds
	DIO_VidSetPinDirection(PORT_COMMUN,PIN_OUT,HIGH);    // O/P
	DIO_VidSetPinDirection(PORT_COMMUN,PIN_IN,LOW);     //  I/P

	//out zero voltage
	DIO_VidSetPinValue(PORT_COMMUN,PIN_OUT,LOW);

	//to open CGRAM location
	LCD_VidSendCommend(0b01000000);

	//to make ping paddle left with ball address 0
	LCD_VidSendChar(0b00000100);
	LCD_VidSendChar(0b00001110);
	LCD_VidSendChar(0b00000100);
	LCD_VidSendChar(0b00011110);
	LCD_VidSendChar(0b00011110);
	LCD_VidSendChar(0b00011100);
	LCD_VidSendChar(0b00011010);
	LCD_VidSendChar(0b00000001);


	//to make ping paddle left address 1
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00011110);
	LCD_VidSendChar(0b00011110);
	LCD_VidSendChar(0b00011100);
	LCD_VidSendChar(0b00011010);
	LCD_VidSendChar(0b00000001);

    //to make ball down right address 2
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000010);
	LCD_VidSendChar(0b00000111);
	LCD_VidSendChar(0b00000111);
	LCD_VidSendChar(0b00000010);


    //to make ball down left address 3
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00001000);
	LCD_VidSendChar(0b00011100);
	LCD_VidSendChar(0b00011100);
	LCD_VidSendChar(0b00001000);

    //to make ball up left address 4
	LCD_VidSendChar(0b00001000);
	LCD_VidSendChar(0b00011100);
	LCD_VidSendChar(0b00011100);
	LCD_VidSendChar(0b00001000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);

    //to make ball up right address 5
	LCD_VidSendChar(0b00000010);
	LCD_VidSendChar(0b00000111);
	LCD_VidSendChar(0b00000111);
	LCD_VidSendChar(0b00000010);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);
	LCD_VidSendChar(0b00000000);

    static s8 local_col = 15 ;

	//to show left ping paddle in beginning
	LCD_VidPosCur(row_1,first_col);
	LCD_VidSendChar(ping_paddle_left);

	//declare result
	u8 result = 0 ;

	while(1)
	{
		//to check that ball saved in LCD 1 or not
		if (DIO_U8GetPinValue(PORT_COMMUN,PIN_SAVED_1)){
			PIE_VidDisable(3);
			result++;
			LCD_VidClear();
			//to show state wining
			for (u8 i = 0 ; i < 3 ; i++){
				LCD_VidPosCur( row_0 , 4 ) ;
				LCD_VidPrintVar(result);
                _delay_ms(500);
				LCD_VidClear();
				_delay_ms(500);
	          }//end for loop
			//to show right ping paddle in beginning
			LCD_VidPosCur((Global_row+1)%2,first_col);
			LCD_VidSendChar(ping_paddle_left);
			PIE_VidEnable(3);
		}//end if

		//to display on second LCD
		if (DIO_U8GetPinValue(PORT_COMMUN,PIN_IN)){

			//to make ball fly up
			while (local_col <= 15 && local_col >= 5){

			//to show  ball up
			LCD_VidPosCur(row_0,local_col);
			LCD_VidSendChar(ball_up_left);
			_delay_ms(100);

			//to clear cell
			LCD_VidPosCur(row_0,local_col);
			LCD_VidSendChar(' ');
			if (local_col == 5){
			      break ;
			}//end if
			else {
			      local_col-- ;
			   }//end else
		    }//end while

			 //to make ball drop from up to down

			 //to show  ball down right
			  LCD_VidPosCur(row_0,local_col);
		      LCD_VidSendChar(ball_down_left);
			 _delay_ms(100);

			 //to clear cell
			  LCD_VidPosCur(row_0,local_col);
			  LCD_VidSendChar(' ');

			  local_col-- ;

			  //to make simulation of dropping

			   //to show  ball down left
			   LCD_VidPosCur(row_1,local_col);
			   LCD_VidSendChar(ball_down_right);
			   _delay_ms(100);

			   //to clear cell
			   LCD_VidPosCur(row_1,local_col);
			   LCD_VidSendChar(' ');

			    local_col-- ;

			   //to show ball up left
			   LCD_VidPosCur(row_1,local_col);
			   LCD_VidSendChar(ball_up_left);
			   _delay_ms(100);

			   //to clear cell
			   LCD_VidPosCur(row_1,local_col);
			   LCD_VidSendChar(' ');

			    local_col-- ;

		//to show fly down
		for(u8 i = 0 ; i < 1 ; i++){
		    //to show  ball up
			LCD_VidPosCur(row_1,local_col);
			LCD_VidSendChar(ball_up_left);
			_delay_ms(100);

			//to clear cell
			LCD_VidPosCur(row_1,local_col);
			LCD_VidSendChar(' ');

			local_col--;
			}//end for

		 //to check that the paddle save ball in LCD 2
		  if ( (Global_row+1)%2 != 1 ){
			  PIE_VidEnable(3);
				LCD_VidClear();
				DIO_VidSetPinValue(PORT_COMMUN,PIN_SAVED_2,HIGH);
				//to show state wining
				for (u8 i = 0 ; i < 3 ; i++){
					LCD_VidPosCur( row_0 , 4 ) ;
					LCD_VidPrintVar(result);
					_delay_ms(500);
					LCD_VidClear();
					_delay_ms(500);
		          }//end for loop

				//to out low to prevent LCD 2 from display goal
				DIO_VidSetPinValue(PORT_COMMUN,PIN_SAVED_2,LOW);

				//to show right ping paddle in beginning
				LCD_VidPosCur((Global_row+1)%2,first_col);
				LCD_VidSendChar(ping_paddle_left);
				PIE_VidEnable(3);

		  }//end if "check"
		local_col = 1 ;

		//to show fly down
		for(u8 i = 0 ; i < 3 ; i++){
			//to show  ball up
			LCD_VidPosCur(row_1,local_col);
			LCD_VidSendChar(ball_up_left);
			_delay_ms(100);

			//to clear cell
			LCD_VidPosCur(row_1,local_col);
			LCD_VidSendChar(' ');

			local_col++;
		}

		//to make ball drop down to up in specific cell and the next to it
		for (s8 i = 1 ; i >= 0 ; i--){
			//to show  ball down right
			LCD_VidPosCur(i,local_col);
			LCD_VidSendChar(ball_down_left);
			_delay_ms(100);

			//to show ball up left
			LCD_VidPosCur(i,local_col);
			LCD_VidSendChar(ball_up_right);
			_delay_ms(100);

			//to clear cell
			LCD_VidPosCur(i,local_col);
			LCD_VidSendChar(' ');

			local_col++ ;
		}//end for loop

		//to make ball fly up in opposite direction
		while (local_col <= 15){

		//to show  ball up
		LCD_VidPosCur(row_0,local_col);
		LCD_VidSendChar(ball_up_right);
		_delay_ms(100);

		//to clear cell
		LCD_VidPosCur(row_0,local_col);
		LCD_VidSendChar(' ');

		local_col++ ;
	   }//end while

		local_col = 15 ;

		//out high voltage
		DIO_VidSetPinValue(PORT_COMMUN,PIN_OUT,HIGH);
		//to stac with high voltage to permit LCD 1 to display to achieve if condition
		_delay_ms(50);
		//to prevent LCD 1 from display again in reverse direction
		DIO_VidSetPinValue(PORT_COMMUN,PIN_OUT,LOW);

		   }//end if
	}//end while
}//end main
