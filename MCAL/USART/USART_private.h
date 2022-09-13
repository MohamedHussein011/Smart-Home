/*
 * USART_private.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: USART
 */

#ifndef _USART_PRIVATE_H
#define _USART_PRIVATE_H

/*Receiver or Transmitter state Selection:
 * Options: 1-DISABLED
 * 			2-ENABLED
 **/
#define ENABLED			1
#define DISABLED		2

/*Stop Bit Selection:
 * Options: 1-ONE_BIT
 * 			2-TWO_BITS
 **/
#define ONE_BIT			1
#define TWO_BITS		2

/*Character Size Selection:
 * Options: 1-FIVE_BITS
 * 			2-SIX_BITS
 * 			3-SEVEN_BITS
 * 			4-EIGHT_BITS
 * 			5-NINE_BITS
 **/
#define FIVE_BITS		1
#define SIX_BITS		2
#define SEVEN_BITS		3
#define EIGHT_BITS		4
#define NINE_BITS		5

/*USART Mode Selection:
 * Options: 1-SYNCHRONOUS
 * 			2-ASYNCHRONOUS
 **/
#define SYNCHRONOUS		1
#define ASYNCHRONOUS	2

/*Parity Mode Selection:
 * Options: 1-DISABLED
 * 			2-EVEN_PARITY
 * 			3-ODD_PARITY
 **/
#define EVEN_PARITY		3
#define ODD_PARITY		4

/*Clock Polarity Selection: (Synchronous mode only)
 * Options: 1-FALLING_EDGE
 * 			Transmit data at falling edge and receive data at rising edge.
 * 			2-RISING_EDGE
 * 			Transmit data at rising  edge and receive data at falling edge.
 **/
#define FALLING_EDGE	1
#define RISING_EDGE		2

#endif /* MCAL_USART_USART_PRIVATE_H_ */
