/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 01/10/2021
 * Driver: DIO - Digital Input Output
 */

#ifndef _DIO_INTERFACE_H
#define _DIO_INTERFACE_H

/* PORT */
typedef enum
{
	DIO_PORTA,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD,
}EN_PORT_t;

/* PIN */
typedef enum
{
	DIO_PIN0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7,
}EN_PIN_t;

/* DIRECTION */
typedef enum
{
	DIO_INPUT,
	DIO_OUTPUT,
}EN_Direction_t;

/* VALUE */
typedef enum
{
	DIO_LOW,
	DIO_HIGH,
}EN_Value_t;


/*
 * Public Function Prototype
 */

void vPORT_Init(void);

uint8_t u8DIO_PinDir(EN_PORT_t PortId, EN_PIN_t PinId, EN_Direction_t DirId);
uint8_t u8DIO_PinVal(EN_PORT_t PortId, EN_PIN_t PinId, EN_Value_t ValId);

uint8_t  u8DIO_ReadPinVal(EN_PORT_t PortId, EN_PIN_t PinId, uint8_t *u8Copy_Value);
uint8_t  u8DIO_ReadPortVal(EN_PORT_t PortId, uint8_t *u8Copy_Value);

uint8_t u8DIO_PortDir(EN_PORT_t PortId, EN_Direction_t DirId);
uint8_t u8DIO_PortVal(EN_PORT_t PortId, EN_Value_t ValId);

uint8_t u8DIO_TogglePin (EN_PORT_t PortId, EN_PIN_t PinId);

#endif
