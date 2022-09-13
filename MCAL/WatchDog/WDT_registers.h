/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 06/11/2021
 *
 */

 
#ifndef _WDT_REGISTERS_H
#define _WDT_REGISTERS_H

#define WDTCR  *((volatile uint8_t *)0x41)

#define WDTOE     4
#define WDE       3
#define WDP2      2
#define WDP1      1
#define WDP0      0
 

#endif
