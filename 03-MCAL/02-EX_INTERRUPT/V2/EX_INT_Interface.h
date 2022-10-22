/*
 * INT_Interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */

#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"

#ifndef INT_INTERFACE_H_
#define INT_INTERFACE_H_

void EX_INT_VidINIT(void);                                            //to define type of edge
/*void GIE_VidEnable (void);                                            //to open global interrupt
void GIE_VidDisable (void);                                           //to close global interrupt*/
void EX_PIE_VidEnable(u8 COPY_U8INT_NUM);                             //to enable specific interrupt
void EX_PIE_VidDisable(u8 COPY_U8INT_NUM);                            //to disable specific interrupt
void EX_INT_VidSetCallBack (u8 Copy_NumOfINT , void (*ptr)(void));    //use to point on excuted function in ISR


#endif /* INT_INTERFACE_H_ */
