/*
 *  File : main.c
 *  DATE: 10/9/2022
 *  Author: Shehab aldeen
 *  Version : V1
 *  Describtion : Calculator
 */
#include"avr/delay.h"
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_Interface.h"
#include "KeyPad_Interface.h"

#define RESULOTION 1000      //the number of digits after dot '.'
#define NO_NUM 50            //to express about no number returned from KEY_PAD
#define CLR_KEY 12           //to express about clear LCD
#define DEFAULT_VAL 0             //to express about state of numbers that entered or not

u8 global_First_sign = 0 ;//to check if it the first sign
u8 sign_1 = 0 ;           //to store signs of num_1 in it
u8 sign_2 = 0 ;           //to store signs of num_2 in it

void Calculate_VidResult(u32 Copy_U8num1 , u32 Copy_U8num2 , u8 Copy_U8Sign);//to calculate the operations
void Error_VidStatment ();                                                   //to show the error statement
u32 Reverse_value (u32 Copy_U8Num , u8  iter);                               //to get the true value of numbers

void main (void){
	u8 flag_1_visit = 0 ;                       //express that u entered num1
	u8 flag_2_visit = 0 ;                       //express that u entered sign
	u8 flag_3_visit = 0 ;                       //express that u entered num2
	u8 flag_first_time = 1 ;                    //to clear LCD after u entered operation
	u8 local_draft = 0 ;                        //draft of entered KEY_PAD
	u64 local_num1 = DEFAULT_VAL ;              //to store num1
	u64 local_num2 = DEFAULT_VAL ;              //to store num2
	u8 local_sign =  DEFAULT_VAL ;              //to store sign
    u8 cycle_1 = 0 ;                            //to get the right value of num1 reversed
    u8 cycle_2 = 0 ;                            //to get the right value of num2 reversed

	LCD_VidInit();	                            //to initialize LCD
	KeyPad_VidInit();	                        //to initialize KEYPAD

	 while (1)
	    {
		 local_draft = KeyPad_U8GetNUM () ;

		 // if entered num != empty key or CLR_KEY or / or * or + or - or = , so it's num
		 if ( !( local_draft == NO_NUM || local_draft == CLR_KEY ||  local_draft == '/' ||  local_draft == '*'
				 ||  local_draft == '+' ||  local_draft == '-' ||  local_draft == '=')  )
		 {
			 // if we entered num1 , we can't enter it again
			 if (global_First_sign == 0){
				 if (flag_first_time){
	                 LCD_VidClear();                     //to clear LCD after every operation
	                 flag_first_time = 0 ;
				 }
				 LCD_VidPrintVar(local_draft ) ;     //to print the values
     			 local_num1 += local_draft*LCD_U32Pow(10,cycle_1) ;          //to send the values
			     cycle_1++;
			 	 flag_1_visit = 1 ;
			 }//end if

			 // if we entered num1 , we will enter num2
			 else if (global_First_sign >= 1 ){
				 local_num2 += local_draft*LCD_U32Pow(10,cycle_2) ;       //to send the values
				 LCD_VidPrintVar(local_draft ) ;     //to print the values
				 flag_2_visit = 1 ;
				 cycle_2++;
			 }//end else if

		 }//end if

		 // to enter sign
		 else if (local_draft != NO_NUM && local_draft != '=' && local_draft != CLR_KEY ){
		     LCD_VidSendChar(local_draft);          //to print the values
		     if (local_draft == '-'&& sign_1 == 0 && flag_1_visit == 0){
		    	 LCD_VidClear();
			     LCD_VidSendChar(local_draft);               //to print the values
		    	 sign_1 = 1 ;
		    	 flag_first_time = 0 ;                       //to prevent clear sign in num_1
		     }//end if
		     else{
	             // to enter sign number 2
		    	 if (flag_3_visit && local_draft == '-' && sign_2 == 0 && flag_2_visit == 0){
		    		 sign_2 = 1 ;
		    	 }//end if
		    	 else {                                      //to enter sign operation
				     local_sign = local_draft ;              //to send the values
				     global_First_sign++ ;                   //to check that the sign isn't entered twice
				     flag_3_visit = 1 ;
		    	 }//end else
		     }//end else
		 }

		 //to clear all arithimitic operation and begin again
		 else if (local_draft == CLR_KEY){
			 local_num1 = DEFAULT_VAL ;
			 local_num2 = DEFAULT_VAL ;
			 local_sign = DEFAULT_VAL ;
			 global_First_sign = 0 ;
			 flag_first_time = 1 ;
		     cycle_1 = 0 ;
		     cycle_2 = 0 ;
		     flag_1_visit = 0 ;
		     flag_2_visit = 0 ;
		     flag_3_visit = 0 ;
		     sign_1 = 0 ;
		     sign_2 = 0 ;
		 }

		 //to display the result and begin new arithimitic operation
		 else if (local_draft != NO_NUM && local_draft != CLR_KEY ){
		     LCD_VidSendChar(local_draft);

		     //to check that 2/  give error on LCD
		     if (!(flag_1_visit && flag_2_visit && flag_3_visit) ){
		    	 Error_VidStatment();
		    	 break ;
		     }

			Calculate_VidResult(Reverse_value(local_num1,cycle_1) ,Reverse_value(local_num2,cycle_2) ,
					 local_sign ) ;
				 local_num1 = DEFAULT_VAL ;
				 local_num2 = DEFAULT_VAL ;
				 local_sign = DEFAULT_VAL ;
				 flag_first_time = 1 ;
			     cycle_1 = 0 ;
			     cycle_2 = 0 ;
			     flag_1_visit = 0 ;
			     flag_2_visit = 0 ;
			     flag_3_visit = 0 ;
			     sign_1 = 0 ;
			     sign_2 = 0 ;
		 }

	   }//end while loop
}//end main

void Calculate_VidResult(u32 Copy_U8num1 , u32 Copy_U8num2 , u8 Copy_U8Sign){
	// to search about wanted sign and do arthimitic operations
	switch (Copy_U8Sign){
       case '/' :

    	   // to check that the division won't be on 0
    	   if (Copy_U8num2 == 0 || global_First_sign != 1){
    		   global_First_sign = 0 ;
    		   Error_VidStatment() ;
    		   return ;
    	   }

    	   //to display integer numbers
    	   if ((sign_1&&!sign_2) || (!sign_1&&sign_2)) {
    		   LCD_VidSendChar('-');
       		   LCD_VidPrintVar(Copy_U8num1/Copy_U8num2);
    	   }
    	   else {
       		   LCD_VidPrintVar(Copy_U8num1/Copy_U8num2);
    	   }

    		LCD_VidSendChar('.');

    		//to display float numbers
    		if (Copy_U8num1 >= Copy_U8num2){
        		LCD_VidPrintVar( (  ( (Copy_U8num1%Copy_U8num2) *RESULOTION ) /Copy_U8num2)  );
    		}
    		//to check about zeros after '.'
    		else if ( (Copy_U8num1*100 /Copy_U8num2) < 10 ) {
    			u32 mirror_num1= Copy_U8num1 ;
    			u32 mirror_num2= Copy_U8num2 ;
    			u8 num1_zero = 0 ;
    			u8 num2_zero = 0 ;
    			u8 flag_1 = 0 , flag_2 = 0 ;
    			while (1){
    				if(flag_1&&flag_2){
    					break ;
    				}//end if
    				Copy_U8num1/= 10 ;
    				Copy_U8num2/= 10 ;
    				if (Copy_U8num1%10>0){
    					num1_zero++;
    				}
    				else
    					flag_1 = 1 ;

    				if (Copy_U8num2% 10 ){
    					num2_zero++;
    				}
    				else
    				    flag_2 = 1 ;
    			}//end while
    			for (u8 i = 0 ; i <num2_zero-num1_zero ; i++){
    				LCD_VidPrintVar(0);
    			}//end for
        		LCD_VidPrintVar( (  ( mirror_num1*RESULOTION ) /mirror_num2)  );
    		}//end else if

    		else {
        		LCD_VidPrintVar( (  ( (u64)Copy_U8num1*RESULOTION ) /Copy_U8num2)  );
    		}//end else
    		global_First_sign = 0 ;
    	   return ;

       case '*' :

    	   // to  be sure that the sign is not repeated
    	   if (global_First_sign != 1){
    		   global_First_sign = 0 ;
    		   Error_VidStatment() ;
    		   return ;
    	   }
    	   if ((sign_1&&!sign_2) || (!sign_1&&sign_2)){
    		   LCD_VidSendChar('-');
       		   LCD_VidPrintVar(Copy_U8num1*Copy_U8num2);
    	   }
    	   else {
       		   LCD_VidPrintVar(Copy_U8num1*Copy_U8num2);
    	   }
    	   global_First_sign = 0 ;
    	   return ;

       case '-' :
    	   // to  be sure that the sign is not repeated
    	   if (global_First_sign != 1){
    		   global_First_sign = 0 ;
    		   Error_VidStatment() ;
    		   return ;
    	   }
    	   //to operate subtraction between first number '-' and second number '+'
    	   //like -3-4    -4-3
    	   if (sign_1&&!sign_2){
    		   LCD_VidSendChar('-');
       		   LCD_VidPrintVar(Copy_U8num1+Copy_U8num2);
    	   }
    	   //like 3--4   4--3
    	   else if (!sign_1&&sign_2){
       		   LCD_VidPrintVar(Copy_U8num1+Copy_U8num2);
    	   }
    	   else if (sign_1&&sign_2){
    		   //like -3--4
    		   if (Copy_U8num1<=Copy_U8num2)
           		   LCD_VidPrintVar(Copy_U8num2-Copy_U8num1);
    		   //-4--3
    		   else {
        		   LCD_VidSendChar('-');
           		   LCD_VidPrintVar(Copy_U8num1-Copy_U8num2);
    		   }
    	   }
    	   //to make '-' in result if num_1 < num_2
    	   //like 3-4  4-3
    	   else {
    		   if ( (Copy_U8num1<Copy_U8num2) ){
        		   LCD_VidSendChar('-');
        		   LCD_VidPrintVar(Copy_U8num2-Copy_U8num1);
    		   }
    		   else
    			   LCD_VidPrintVar(Copy_U8num1-Copy_U8num2);
    	   }
    	   global_First_sign = 0 ;
    	   return ;

       case '+' :
    	   // to  be sure that the sign is not repeated
    	   if (global_First_sign != 1){
    		   global_First_sign = 0 ;
    		   Error_VidStatment() ;
    		   return ;
    	   }
    	   if (sign_1&&!sign_2){
    		   if (Copy_U8num1>Copy_U8num2){
        		   LCD_VidSendChar('-');
        		   LCD_VidPrintVar(Copy_U8num1-Copy_U8num2);
    		   }
    		   else
        		   LCD_VidPrintVar(Copy_U8num2-Copy_U8num1);
    	   }
    	   else if (!sign_1&&sign_2){
    		   if (Copy_U8num1>=Copy_U8num2){
        		   LCD_VidPrintVar(Copy_U8num1-Copy_U8num2);
    		   }
    		   else {
        		   LCD_VidSendChar('-');
        		   LCD_VidPrintVar(Copy_U8num2-Copy_U8num1);
    		   }
    	   }
    	   else if (sign_1&&sign_2){
    		   LCD_VidSendChar('-');
    		   LCD_VidPrintVar(Copy_U8num2+Copy_U8num1);
    	   }
    	   else
    		   LCD_VidPrintVar(Copy_U8num2+Copy_U8num1);
    	   global_First_sign = 0 ;
    	   return ;

     default : Error_VidStatment() ;  return ;
  }//end switch
}//end FUNC Calculate_VidResult

void Error_VidStatment(){
	   LCD_VidClear();
	   LCD_VidSendString("    false        operation     ");
	   global_First_sign = 0 ;
       _delay_ms(2000);
       //to clear all global flags
       global_First_sign = 0 ;
       sign_1 = 0 ;
       sign_2 = 0 ;
       main() ;
}//end FUNC Error_VidStatment


u32 Reverse_value (u32 Copy_U8Num , u8 iter){
	u32 new_value = 0 ;
    for (u8 i=iter ; i > 0 ; i--)  {
    	new_value += (Copy_U8Num % 10)*LCD_U32Pow(10,i-1) ;
    	Copy_U8Num/=10;
    }
    return new_value;
}
