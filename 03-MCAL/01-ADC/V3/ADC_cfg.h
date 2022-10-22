/*
 * ADC_cfg.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/*to select :  REFS1   REFS0
   External V    0        0         EX_REF
   AVCC = 5 V    0        1         AVREF_5V
   VREF = 2.5 V  1        1         AVREF_2.5
*/

#define AVCC_5V                              //to define V REFERENCE

	/*
	 - to enable ADC perpherial
	 - to select specific :
	 1) pre_scalar  /2    0 0 0 or 0 0 1      PRE_SCALAR_2
	 2) pre_scalar  /4    0 1 0               PRE_SCALAR_4
	 3) pre_scalar  /8    0 1 1               PRE_SCALAR_8
	 4) pre_scalar  /16   1 0 0               PRE_SCALAR_16
	 5) pre_scalar  /32   1 0 1               PRE_SCALAR_32
	 6) pre_scalar  /64   1 1 0               PRE_SCALAR_64
	 7) pre_scalar  /128  1 1 1               PRE_SCALAR_128
	  */
#define PRE_SCALAR_128

#endif /* ADC_CFG_H_ */
