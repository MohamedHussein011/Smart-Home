/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 06/11/2021
 *
 */

/* Files Inclusion */

/* 1. User Defined Libraries */
#include "../../Library/STD_TYPE.h"
#include "../../Library/BIT_MATH.h"

/* 3. MCAL Files */
#include "WDT_registers.h"
#include "WDT_interface.h"

void vWDT_Enable(void)
{	
	SET_BIT(WDTCR,WDE);
}

void vWDT_Disable(void)
{
	WDTCR = (1 << WDE) | (1 << WDTOE);
	WDTCR = 0;
}

void vWDT_Sleep(uint8_t u8Copy_Timeout)
{
	WDTCR = ((WDTCR & 0xF8) | u8Copy_Timeout);
}
