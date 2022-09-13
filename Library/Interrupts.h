/*
 * Interrupts.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mhmd
 */

#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H


#define RESET          __vector_0                 /*External Pin, Power-on Reset, Brown-out Reset, Watchdog Reset,
												   *and JTAG AVR Reset
												   */
#define EXT_INT0       __vector_1                 /*External Interrupt 0*/
#define EXT_INT1       __vector_2 				  /*External Interrupt 1*/
#define EXT_INT2       __vector_3                 /*External Interrupt 2*/
#define TIMER2_COMP    __vector_4                 /*Timer/Counter2 Compare Match*/
#define TIMER2_OVF     __vector_5                 /*Timer/Counter2 Overflow*/
#define TIMER1_CAPT    __vector_6                 /*Timer/Counter1 Capture Event*/
#define TIMER1_COMPA   __vector_7                 /*Timer/Counter1 Compare Match A*/
#define TIMER1_COMPB   __vector_8                 /*Timer/Counter1 Compare Match B*/
#define TIMER1_OVF     __vector_9                 /*Timer/Counter1 Overflow*/
#define TIMER0_COMP    __vector_10                 /*Timer/Counter0 Compare Match*/
#define TIMER0_OVF     __vector_11                 /*Timer/Counter0 Overflow*/
#define SPI_STC        __vector_12                /**Serial Transfer Complete*/
#define USART_RXC      __vector_13                /*USART, Rx Complete*/
#define USART_UDRE     __vector_14                /*USART Data Register Empty*/
#define USART_TXC      __vector_15                /*USART, Tx Complete*/
#define ADC            __vector_16                /*ADC Conversion Complete*/
#define EE_RDY         __vector_17                /*EEPROM Ready*/
#define ANA_COMP       __vector_18                /*Analog Comparator*/
#define TWI            __vector_19                /*Two-wire Serial Interface*/



/*Interrupt Service Routine*/
#define ISR(INT_VECTOR)      void INT_VECTOR (void) __attribute__((signal));\
	void INT_VECTOR (void)

/*Enable Global interrupt*/
#define sei()     __asm__ __volatile__("sei" ::: "memory")


/*Disable Global interrupt*/
#define cli()     __asm__ __volatile__("cli" ::: "memory")

#endif /* INTERRUPTS_H_ */
