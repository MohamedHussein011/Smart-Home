/*
 * ADC_configuration.h
 *
 * 		Name: Mohamed Hussein
 * 		Layer: MCAL
 * 		Version: V1.0 - 09/12/2021
 * 		Driver: ADC - Analog to Digital Converter
 */

#ifndef _ADC_CONFIGURATION_H
#define _ADC_CONFIGURATION_H

/* Choose ADC Reference voltage
   Options:
		1: AREF
		2: AVCC
		3: Internal_2560mv
*/
#define   ADC_RefVolt          AVCC

/* Choose how to present ADC Conversion result in ADC Data Register
   Options:
		1: ADC_LeftAdjust      - the 8 MSBs are in the ADCH
		2: ADC_RightAdjust     - the 8 LSBs are in the ADCL
*/
#define ADC_Adjust     ADC_LeftAdjust

/* Choose if you want to enable auto trigger or not
   Options:
		1: ADC_AutoTriggerDisable
		2: ADC_AutoTriggerEnable
*/
#define ADC_AutoTrigger     ADC_AutoTriggerDisable

/* Choose if you want to enable ADC Interrupt or not
   Options:
		1: ADC_InterruptDisable
		2: ADC_InterruptEnable
*/
#define ADC_Interrupt     ADC_InterruptDisable

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
#define ADC_Prescaler       Div_By_128


/* TIMEOUT to make sure ADC conversion time not take too long or exit*/
#define ADC_u32TIMEOUT          50000

/* ADC conversion result
   Options:
		1: EightBits
		2: TenBits
*/
#define ADC_Result              TenBits

/*reference voltage (in mV) & resolution bits (10bits max in decimal) used to calculate the analog value with respect to digital value*/
#define ADC_Reference        5000UL
#define ADC_ResolutionBit        1024UL

#endif /* MCAL_ADC_ADC_CONFIGURATION_H_ */
