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
#include"INT_Interface.h"
#include "avr/delay.h"
#include "PING_PONG_1_private.h"

extern Global_row ;

void main ( void )
{
	//define pin to check that the ball isn't saved
	DIO_VidSetPinDirection(PORT_COMMUN,PIN_SAVED_1,1);
	DIO_VidSetPinValue(PORT_COMMUN,PIN_SAVED_1,0);

	//define pin_out to check the code begin from beginning or after that
	u8 pin_out = 0 ;

	//to initialize interrupt 0
    GIE_VidEnable();        //to open global interrupt

    /* 0 :  enable perpherial interrupt 0
       1 : enable perpherial interrupt 1
       2 : enable perpherial interrupt 2
     */
    PIE_VidEnable(0);       //to enable perpherial interrupt
    INT_VidINIT();          //to initialize interrupt

	//to initialize LCD
	LCD_VidInit();

	//define two pins to communicate between two lcds
	DIO_VidSetPinDirection(PORT_COMMUN,PIN_OUT,HIGH);    // O/P
	DIO_VidSetPinDirection(PORT_COMMUN,PIN_IN,LOW);     //  I/P

	//out zero voltage
	DIO_VidSetPinValue(PORT_COMMUN,PIN_OUT,LOW);

    static s8 local_col = 14 ;

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

    //to show right ping paddle with ball in beginning
		LCD_VidPosCur(row_1,last_col);
		LCD_VidSendChar(ping_paddle_right_ball);
		_delay_ms(100);

		//to show right ping paddle in beginning
		LCD_VidPosCur(row_1,last_col);
		LCD_VidSendChar(ping_paddle_right);

		//declare result
		u8 result = 0 ;

	while(1)
	{
		//to check that ball saved in LCD 2 or not
		if (DIO_U8GetPinValue(PORT_COMMUN,PIN_SAVED_2)){
			PIE_VidDisable(1);
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
			LCD_VidPosCur((Global_row+1)%2,last_col);
			LCD_VidSendChar(ping_paddle_right);
			PIE_VidEnable(1);
		}//end if

		if (pin_out == LOW ){

		//to show fly down
		for(u8 i = 0 ; i < 3 ; i++){
			//to show  ball up
			LCD_VidPosCur(row_1,local_col);
			LCD_VidSendChar(ball_up_left);
			_delay_ms(100);

			//to clear cell
			LCD_VidPosCur(row_1,local_col);
			LCD_VidSendChar(' ');

			local_col--;
		}

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
        while (local_col <= 12 && local_col >= 0){

			//to show  ball up
			LCD_VidPosCur(row_0,local_col);
			LCD_VidSendChar(ball_up_left);
			_delay_ms(100);

			//to clear cell
			LCD_VidPosCur(row_0,local_col);
			LCD_VidSendChar(' ');
            if (local_col == 0){
            	break ;
            }//end if
            else {
            	local_col--;
            }//end else

        }

			//out high voltage
			DIO_VidSetPinValue(PORT_COMMUN,PIN_OUT,HIGH);
			pin_out = HIGH ;
		}//end if pin out

		//to show ball in opposite direction

		//to be sure that u get high voltage
		if ( DIO_U8GetPinValue(PORT_COMMUN,PIN_IN) ){

			//out zero voltage
			DIO_VidSetPinValue(PORT_COMMUN,PIN_OUT,0);
			pin_out = 0 ;

			//to make ball fly up in opposite direction
			while (local_col <= 11 && local_col >= 0){

			//to show  ball up
			LCD_VidPosCur(row_0,local_col);
			LCD_VidSendChar(ball_up_left);
			_delay_ms(100);

			//to clear cell
			LCD_VidPosCur(row_0,local_col);
			LCD_VidSendChar(' ');
			if (local_col == 11){
			      break ;
			}//end if
			else {
			      local_col++ ;
			   }//end else
		    }//end while

			 //to make ball drop from up to down

			 //to show  ball down right
			  LCD_VidPosCur(row_0,local_col);
		      LCD_VidSendChar(ball_down_right);
			 _delay_ms(100);

			 //to clear cell
			  LCD_VidPosCur(row_0,local_col);
			  LCD_VidSendChar(' ');

			  local_col++ ;

			  //to make ball drop up to down in specific cell and the next to it
			  for (s8 i = 1 ; i >= 0 ; i--){

			   //to show  ball down left
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
			    }

			   //to make ball fly up
			    while (local_col < 15){
				//to show  ball up
				LCD_VidPosCur(row_0,local_col);
				LCD_VidSendChar(ball_up_right);
				_delay_ms(100);

				//to clear cell
				LCD_VidPosCur(row_0,local_col);
				LCD_VidSendChar(' ');
				local_col++ ;
			    }//end while (local_col < 15)

			  //to check that the paddle save ball LCD 1
			  if ( (Global_row+1)%2 != 0 ){
				  PIE_VidDisable(1);
					LCD_VidClear();
					DIO_VidSetPinValue(PORT_COMMUN,PIN_SAVED_1,HIGH);
					//to show state wining
					for (u8 i = 0 ; i < 3 ; i++){
						LCD_VidPosCur( row_0 , 4 ) ;
						LCD_VidPrintVar(result);
						_delay_ms(500);
						LCD_VidClear();
						_delay_ms(500);
			          }//end for loop

					//to out low to prevent LCD 2 from display result
					DIO_VidSetPinValue(PORT_COMMUN,PIN_SAVED_1,LOW);

					//to show right ping paddle in beginning
					LCD_VidPosCur((Global_row+1)%2,last_col);
					LCD_VidSendChar(ping_paddle_right);
					PIE_VidEnable(1);

			  }//end if "check"

			local_col = 14 ;
		}//end if
	}//end while (1)
}//end main
