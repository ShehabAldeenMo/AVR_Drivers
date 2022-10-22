/*
 * TIMER_CFG.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */

#include "TIMER_Private.h"

#ifndef TIMER_CFG_H_
#define TIMER_CFG_H_

/*
	no_prescalar   "NO_PRE"
	clkI/O/8       "PRE_8"
	clkI/O/64      "PRE_64"
	clkI/O/256     "PRE_256"
	clkI/O/1024    "PRE_1024"
*/

//be aware to make pre_scalar in PRE_8 to make time by ms
#define PRE_SCALAR_TYPE PRE_8

//define the mode will be used to count the time
/*
"OV"       1
"COMPARE"  2
"FAST_PWM" 3
*/
#define TIMER0_MODE OV

#endif /* TIMER_CFG_H_ */
