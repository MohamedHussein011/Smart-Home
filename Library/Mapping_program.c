/*
 * Mapping_program.c
 *
 *  	Name: Mohamed Hussein
 * 		Version: V1.0 - 01/10/2021
 */

#include "STD_TYPE.h"
#include "Mapping_interface.h"

int32_t s32Map (int32_t InputMin, int32_t InputMax, int32_t OutputMin, int32_t OutputMax, int32_t InputValue)
{
	/*y is output, x is input
	 * (y-y1)/(x-x1) = (y2-y1)/(x2-x1)
	 * */
	int32_t s32Local_OutputDiference = OutputMax - OutputMin;
	int32_t s32Local_InputDiference = InputMax - InputMin;
	int32_t s32Local_InputCalculation = InputValue - InputMin;

	int32_t s32Local_Output = (int32_t) ((s32Local_OutputDiference * s32Local_InputCalculation) / s32Local_InputDiference);
	s32Local_Output += OutputMin;

	if(s32Local_Output <= OutputMin)
		return OutputMin;
	else if(s32Local_Output >= OutputMax)
		return OutputMax;
	else
		return s32Local_Output;

}
