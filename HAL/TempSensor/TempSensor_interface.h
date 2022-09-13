/*
 * TempSensor_interface.h
 *
 *  	Name: Mohamed Hussein
 * 		Layer: HAL
 * 		Version: V1.0 - 01/10/2021
 * 		Device: LM35
 */

#ifndef _TEMPSENSOR_INTERFACE_H
#define _TEMPSENSOR_INTERFACE_H

void vTempSensor_Init(void);
uint8_t u8TempSensor_GetValue(uint16_t u16Copy_Value);

#endif /* HAL_TEMPSENSOR_TEMPSENSOR_INTERFACE_H_ */
