/*
 * TempSensor_program.c
 *
 * 		Name: Mohamed Hussein
 * 		Layer: HAL
 * 		Version: V1.0 - 01/10/2021
 * 		Device: LM35
 */
#include "../../Library/STD_TYPE.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/ADC/ADC_interface.h"

#include "TempSensor_configuration.h"
#include "TempSensor_interface.h"

void vTempSensor_Init(void)
{
	u8DIO_PinDir(TempSensor_Port,TempSensor_Pin,DIO_INPUT);
	u8DIO_PinVal(TempSensor_Port,TempSensor_Pin,DIO_HIGH);
}
uint8_t u8TempSensor_GetValue(uint16_t u16Copy_Value)
{
	uint16_t u16Local_Analog = u16ADC_ConvertDigitalToAnalog(u16Copy_Value);

	uint8_t u8Local_TempValue = (uint8_t)(u16Local_Analog / 10);
	return u8Local_TempValue;
}
