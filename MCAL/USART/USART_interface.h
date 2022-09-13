/*
 * USART_interface.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: USART
 */

#ifndef _USART_INTERFACE_H
#define _USART_INTERFACE_H

void vUSART_Init(void);

uint8_t vUSART_SendByte(uint8_t u8Copy_Byte);
uint8_t vUSART_RecieveByte(uint8_t* pu8Copy_Byte);

uint8_t u8USART_SendStringSynchronous(const char * pu8Copy_string);
uint8_t u8USART_SendStringAsynchronous(const char * pu8Copy_string, void(*Copy_pvNotificationFunction)(void));

uint8_t u8USART_ReceiveBufferSynchronous(char * pu8Copy_Data, uint8_t u8Copy_BufferSize);
uint8_t u8USART_ReceiveBufferAsynchronous(char * pu8Copy_Data, uint8_t u8Copy_BufferSize, void(*Copy_pvNotificationFunction)(void));

/*enter horizontal tab to exit the function*/
uint8_t u8USART_ReceiveStringSynchronous(char * pu8Copy_string);

void vUSART_SendNumberSynchronous(int32_t s32Copy_Number);

#endif /* MCAL_USART_USART_INTERFACE_H_ */
