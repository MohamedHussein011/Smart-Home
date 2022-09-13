/*
 * Name: Mohamed Hussein
 * Layer: HAL
 * Version: V1.0 - 07/10/2021
 *
 */

/* Files Inclusion */

/* 1. User Defined Libraries */
#include "../../Library/STD_TYPE.h"
#include "../../Library/BIT_MATH.h"

/* 3. MCAL Files */
#include "../../MCAL/DIO/DIO_interface.h"

/* 4. HAL Files */
#include "LED_interface.h"

/*
 * Public Function Definition
 */

uint8_t u8LED_Init (EN_PORT_t PortId, EN_PIN_t PinId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && PinId <= DIO_PIN7)
	{
		u8DIO_PinDir(PortId,PinId,DIO_OUTPUT);
	}else
		u8Local_Error = NOK;

	return u8Local_Error;

}
/*Turn ON LED
 * Input: takes Port name & Pin number
 * return: Error State
 */
uint8_t u8LED_ON  (EN_PORT_t PortId, EN_PIN_t PinId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && PinId <= DIO_PIN7)
	{
		u8DIO_PinVal(PortId,PinId,DIO_HIGH);
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}
/*Turn OFF LED
 * Input: takes Port name & Pin number
 * return: Error State
 */
uint8_t u8LED_OFF (EN_PORT_t PortId, EN_PIN_t PinId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && PinId <= DIO_PIN7)
	{
		u8DIO_PinVal(PortId,PinId,DIO_LOW);
	}else
		u8Local_Error = NOK;

	return u8Local_Error;

}
/*Toggle LED
 * Input: takes Port name & Pin number
 * return: Error State
 */
uint8_t u8LED_Toggle (EN_PORT_t PortId, EN_PIN_t PinId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && PinId <= DIO_PIN7)
	{
		u8DIO_TogglePin (PortId,PinId);
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

uint8_t u8LED_PORTInit  (EN_PORT_t PortId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD)
	{
		u8DIO_PortDir(PortId, DIO_OUTPUT);
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

uint8_t u8LED_PORT  (EN_PORT_t PortId, EN_Value_t ValId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD || ValId >= DIO_LOW)
	{
		u8DIO_PortVal(PortId, ValId);

	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}
