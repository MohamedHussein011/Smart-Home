/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 15/10/2021
 * Driver: Global Interrput
 */
 
/* Files Inclusion */

/* 1. User Defined Libraries */
#include "../../Library/STD_TYPE.h"
#include "../../Library/BIT_MATH.h"

/* 3. MCAL Files */
#include "../Global_Interrupt/GIE_interface.h"
#include "../Global_Interrupt/GIE_registers.h"

/* Functions Definitions */
/*Enable Global Interrupt
 * Input: void
 * return: void
 */
void vGlobalInterrupt_Enable(void)
{
	SET_BIT(SREG,7);
}
void vGlobalInterrupt_Disable(void)
{
	CLR_BIT(SREG,7);
}
