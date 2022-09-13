/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 06/11/2021
 *
 */

 
#ifndef _WDT_INTERFACE_H
#define _WDT_INTERFACE_H

#define TIMEOUT_16ms             0
#define TIMEOUT_32ms             1
#define TIMEOUT_65ms             2
#define TIMEOUT_130ms            3
#define TIMEOUT_260ms            4
#define TIMEOUT_520ms            5
#define TIMEOUT_1000ms           6
#define TIMEOUT_2100ms           7


void vWDT_Enable(void);
void vWDT_Disable(void);
void vWDT_Sleep(uint8_t u8Copy_Timeout);


#endif
