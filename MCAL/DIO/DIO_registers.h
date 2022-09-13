/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 01/10/2021
 * Driver: DIO - Digital Input Output
 */
 
#ifndef _DIO_REGISTERS_H
#define _DIO_REGISTERS_H

/* PORT A Related Register*/
#define PORTA *((volatile uint8_t*) 0x3B )
#define DDRA  *((volatile uint8_t*) 0x3A )
#define PINA  *((volatile uint8_t*) 0x39 )

/* PORT B Related Register*/
#define PORTB *((volatile uint8_t*) 0x38 )
#define DDRB  *((volatile uint8_t*) 0x37 )
#define PINB  *((volatile uint8_t*) 0x36 )

/* PORT C Related Register*/
#define PORTC *((volatile uint8_t*) 0x35 )
#define DDRC  *((volatile uint8_t*) 0x34 )
#define PINC  *((volatile uint8_t*) 0x33 )

/* PORT D Related Register*/
#define PORTD *((volatile uint8_t*) 0x32 )
#define DDRD  *((volatile uint8_t*) 0x31 )
#define PIND  *((volatile uint8_t*) 0x30 )
 
#endif
