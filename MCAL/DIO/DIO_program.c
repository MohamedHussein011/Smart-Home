/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 01/10/2021
 * Driver: DIO - Digital Input Output
 */

/* Files Inclusion */
#include "../../Library/STD_TYPE.h"
#include "../../Library/BIT_MATH.h"

#include "DIO_registers.h"
#include "DIO_private.h"
#include "DIO_configuration.h"
#include "DIO_interface.h"

/*
 * Public Function Prototype
 */

/*Initialize every pin state
 * Input: void
 * Return: void
 */
void vPORT_Init(void)
{
	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;

	PORTA = PORTA_INITIAL_VALUE;
	PORTB = PORTB_INITIAL_VALUE;
	PORTC = PORTC_INITIAL_VALUE;
	PORTD = PORTD_INITIAL_VALUE;
}

uint8_t u8DIO_PinDir(EN_PORT_t PortId, EN_PIN_t PinId, EN_Direction_t DirId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && PinId <= DIO_PIN7 && DirId <= DIO_OUTPUT)
	{
		switch(PortId)
		{
		case DIO_PORTA: WRT_BIT(DDRA, PinId, DirId); break;
		case DIO_PORTB: WRT_BIT(DDRB, PinId, DirId); break;
		case DIO_PORTC: WRT_BIT(DDRC, PinId, DirId); break;
		case DIO_PORTD: WRT_BIT(DDRD, PinId, DirId); break;
		default: /* ERROR */ break;

		}
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

uint8_t u8DIO_PinVal(EN_PORT_t PortId, EN_PIN_t PinId, EN_Value_t ValId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && PinId <= DIO_PIN7 && ValId <= DIO_HIGH)
	{
		switch(PortId)
		{
		case DIO_PORTA: WRT_BIT(PORTA, PinId, ValId); break;
		case DIO_PORTB: WRT_BIT(PORTB, PinId, ValId); break;
		case DIO_PORTC: WRT_BIT(PORTC, PinId, ValId); break;
		case DIO_PORTD: WRT_BIT(PORTD, PinId, ValId); break;
		default: /* ERROR */ break;

		}
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

/*Read Pin current state
 * Input: takes Port name & Pin number & pointer that points to a variable you want to save value in it
 * return: Error State
 */
uint8_t  u8DIO_ReadPinVal(EN_PORT_t PortId, EN_PIN_t PinId, uint8_t *u8Copy_Value)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && PinId <= DIO_PIN7 && u8Copy_Value != NULL)
	{
		switch(PortId)
		{
		case DIO_PORTA: *u8Copy_Value = GET_BIT(PINA, PinId); break;
		case DIO_PORTB: *u8Copy_Value = GET_BIT(PINB, PinId); break;
		case DIO_PORTC: *u8Copy_Value = GET_BIT(PINC, PinId); break;
		case DIO_PORTD: *u8Copy_Value = GET_BIT(PIND, PinId); break;
		default: /* ERROR */ break;

		}
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

uint8_t u8DIO_PortDir(EN_PORT_t PortId, EN_Direction_t DirId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && DirId <= DIO_OUTPUT)
	{
		if(DirId == DIO_OUTPUT)
		{
			switch(PortId)
			{
			case DIO_PORTA: DDRA = 0xff;          break;
			case DIO_PORTB: DDRB = 0xff;          break;
			case DIO_PORTC: DDRC = 0xff;          break;
			case DIO_PORTD: DDRD = 0xff;          break;
			}
		}else{
			switch(PortId)
			{
			case DIO_PORTA: DDRA = 0;             break;
			case DIO_PORTB: DDRB = 0;             break;
			case DIO_PORTC: DDRC = 0;             break;
			case DIO_PORTD: DDRD = 0;             break;
			}

		}
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

uint8_t u8DIO_PortVal(EN_PORT_t PortId, EN_Value_t ValId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && ValId >= DIO_LOW)
	{
		if(ValId == DIO_HIGH)
		{
			switch(PortId)
			{
			case DIO_PORTA: PORTA = 0xff;             break;
			case DIO_PORTB: PORTB = 0xff;             break;
			case DIO_PORTC: PORTC = 0xff;             break;
			case DIO_PORTD: PORTD = 0xff;             break;
			}
		}else if(ValId == DIO_LOW)
		{
			switch(PortId)
			{
			case DIO_PORTA: PORTA = 0;             break;
			case DIO_PORTB: PORTB = 0;             break;
			case DIO_PORTC: PORTC = 0;             break;
			case DIO_PORTD: PORTD = 0;             break;
			}
		}else{
			switch(PortId)
			{
			case DIO_PORTA: PORTA = ValId;             break;
			case DIO_PORTB: PORTB = ValId;             break;
			case DIO_PORTC: PORTC = ValId;             break;
			case DIO_PORTD: PORTD = ValId;             break;
			}

		}
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

uint8_t  u8DIO_ReadPortVal(EN_PORT_t PortId, uint8_t *u8Copy_Value)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && u8Copy_Value != NULL)
	{
		switch(PortId)
		{
		case DIO_PORTA: *u8Copy_Value = PINA;                 break;
		case DIO_PORTB: *u8Copy_Value = PINB;                 break;
		case DIO_PORTC: *u8Copy_Value = PINC;                 break;
		case DIO_PORTD: *u8Copy_Value = PIND;                 break;
		default: /* ERROR */ break;

		}
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

uint8_t u8DIO_TogglePin (EN_PORT_t PortId, EN_PIN_t PinId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && PinId <= DIO_PIN7)
	{
		switch (PortId)
		{
		case DIO_PORTA: TOG_BIT(PORTA,PinId);        break;
		case DIO_PORTB: TOG_BIT(PORTB,PinId);        break;
		case DIO_PORTC: TOG_BIT(PORTC,PinId);        break;
		case DIO_PORTD: TOG_BIT(PORTD,PinId);        break;

		default: /* Error */      break;
		}
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}
