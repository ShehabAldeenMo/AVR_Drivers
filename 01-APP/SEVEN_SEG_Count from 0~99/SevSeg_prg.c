/*
 *  File : SevSeg_prg.c
 *  DATE: 6/9/2022
 *  Author: Shehab aldeen
 *  Version : V1
 *  Describtion : --------------
 */
 
#include"../LIB/STD_TYPES.h"
#include"../LIB/Bit_math.h"
#include"DIO_interface.h"
#include"SevSeg_interface.h"
#include"SevSeg_Private.h"
#include"SevSeg_cfg.h"


//to define used SevSeg_prg_num
#if SEG_TYPE == COM_KA
  u8 SevSeg_prg_num[10] = { ZERO , ONE , TWO , THREE , FOUR , FIVE , SEX , SEVEN , EIGHT,NINE };
#elif SEG_TYPE == COM_ANA
   u8 SevSeg_prg_num[10] = { ~(ZERO) , ~(ONE) , ~(TWO) , ~(THREE) , ~(FOUR) , ~(FIVE)
		            , ~(SEX) , ~(SEVEN) , ~(EIGHT) , ~(NINE) } ;
#endif

//to display num on SEV_SEG PORT
void SevSeg_VidDisplayNum(u8 Copy_U8Num ) {
	DIO_VidSetPortValue( SEG_PORT , SevSeg_prg_num[Copy_U8Num] );
}

