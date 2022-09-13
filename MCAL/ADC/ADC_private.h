/*
 * ADC_private.h
 *
 *  	Name: Mohamed Hussein
 * 		Layer: MCAL
 * 		Version: V1.0 - 09/12/2021
 * 		Driver: ADC - Analog to Digital Converter
 */

#ifndef _ADC_PRIVATE_H
#define _ADC_PRIVATE_H

/* Choose ADC Reference voltage
   Options:
		1: AREF
		2: AVCC
		3: Internal_2560mv
*/
#define AREF                     1
#define AVCC                     2
#define Internal_2560mv          3

/* Choose how to present ADC Conversion result in ADC Data Register
   Options:
		1: ADC_LeftAdjust
		2: ADC_RightAdjust
*/
#define ADC_LeftAdjust     1
#define ADC_RightAdjust    2

/* Choose if you want to enable auto trigger or not
   Options:
		1: ADC_AutoTriggerDisable
		2: ADC_AutoTriggerEnable
*/
#define ADC_AutoTriggerDisable       1
#define ADC_AutoTriggerEnable        2

/* Choose if you want to enable ADC Interrupt or not
   Options:
		1: ADC_InterruptDisable
		2: ADC_InterruptEnable
*/
#define ADC_InterruptDisable     1
#define ADC_InterruptEnable      2

/* ADC Prescaler Selections
   Options:
		1: Div_By_2
		2: Div_By_4
		3: Div_By_8
		4: Div_By_16
		5: Div_By_32
		6: Div_By_64
		7: Div_By_128
*/
#define ADC_Prescaler_Mask   0xF8

#define Div_By_2         1
#define Div_By_4         2
#define Div_By_8         3
#define Div_By_16        4
#define Div_By_32        5
#define Div_By_64        6
#define Div_By_128       7

/* ADC conversion result
   Options:
		1: EightBits
		2: TenBits
*/
#define EightBits              1
#define TenBits                2

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
