/*
 * Name: Mohamed Hussein
 * Layer: HAL
 * Version: V1.0 - 07/10/2021
 *
 */
 
#ifndef _LED_INTERFACE_H
#define _LED_INTERFACE_H

/*
 * Public Function Prototype
 */

uint8_t u8LED_Init (EN_PORT_t PortId, EN_PIN_t PinId);

uint8_t u8LED_ON  (EN_PORT_t PortId, EN_PIN_t PinId);
uint8_t u8LED_OFF (EN_PORT_t PortId, EN_PIN_t PinId);
uint8_t u8LED_Toggle (EN_PORT_t PortId, EN_PIN_t PinId);

uint8_t u8LED_PORTInit  (EN_PORT_t PortId);
uint8_t u8LED_PORT  (EN_PORT_t PortId, EN_Value_t ValId);

#endif
