/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 23/10/2021
 *
 */

/* Files Inclusion */

/* 1. User Defined Libraries */
#include "../../Library/STD_TYPE.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/Interrupts.h"

/* 3. MCAL Files */
#include "Timer_registers.h"
#include "Timer_private.h"
#include "Timer_configuration.h"
#include "Timer_interface.h"

/********************* Array of 8 pointers to functions for callback for all Timers interrupts *******************/
static void (*pvTimer_CallbackFunction[8]) (void) = {NULL};

/****************************************Timer initialize**************************************************/
/*Initialize Timer0 with configuration you choose
 * Input: void
 * return: void
 */
void vTimer0_Initprebuild (void)
{
	/* Timer/Counter Waveform Generation Mode of Operation */
#if Timer0Waveform_Mode == Normal
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
#elif Timer0Waveform_Mode == PWM_Phase_Correct
	SET_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
#elif Timer0Waveform_Mode == CTC
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
#elif Timer0Waveform_Mode == Fast_PWM
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*choose compare output mode*/
#if Timer0CompareOutput_Mode == NormalOperation
	CLR_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif Timer0CompareOutput_Mode == ToggleOC0
	SET_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif Timer0CompareOutput_Mode == ClearOnCompare_SetAtTop
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#elif Timer0CompareOutput_Mode == CLEAR_UpCounting_SET_DownCounting
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#elif Timer0CompareOutput_Mode == SetAtCompare_ClearOnTop
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#elif Timer0CompareOutput_Mode == SET_UpCounting_CLEAR_DownCounting
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Disable or Enable Overflow Interrupt*/
#if Timer0_OverflowInterrupt == Timer0_OVEnableInterrupt
	SET_BIT(TIMSK,TOIE0);
#elif Timer0_OverflowInterrupt == Timer0_OVDisableInterrupt
	CLR_BIT(TIMSK,TOIE0);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Disable or Enable CTC Interrupt*/
#if Timer0_CTCInterrupt == Timer0_CTCEnableInterrupt
	SET_BIT(TIMSK,OCIE0);
#elif Timer0_CTCInterrupt == Timer0_CTCDisableInterrupt
	CLR_BIT(TIMSK,OCIE0);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Set Preload Value on TCNT0*/
	TCNT0 = Timer0_PreloadValue;

	/*Set Compare Value on OCR0*/
	OCR0 = Timer0_CompareValue;

	/* Clock Select Bit Description ---> Prescaler */
	TCCR0 &= TimerPrescaler_Mask;
	TCCR0 |= Timer0Prescaler_Select;
}

uint8_t vTimer0_Initpostbuild (EN_TimerMode_t ENcopy_mode, EN_TimerPrescaler_t ENcopy_prescaler)
{
	uint8_t u8Local_Error = OK;

	if(ENcopy_mode <= Fast_PWMmode && ENcopy_prescaler <= Timer_prescaler1024)
	{
		switch(ENcopy_mode)
		{
		case NormalTimermode: CLR_BIT(TCCR0,WGM00);   CLR_BIT(TCCR0,WGM01);  break;
		case PWM_phasecorrectmode: SET_BIT(TCCR0,WGM00);    CLR_BIT(TCCR0,WGM01);  break;
		case CTCmode: CLR_BIT(TCCR0,WGM00);     SET_BIT(TCCR0,WGM01);  break;
		case Fast_PWMmode: SET_BIT(TCCR0,WGM00);      SET_BIT(TCCR0,WGM01);  break;
		default:    break;
		}

		/* Clock Select Bit Description ---> Prescaler */
		TCCR0 &= TimerPrescaler_Mask;
		switch(ENcopy_prescaler)
		{
		case Timer_Stop: TCCR0 |= Timer_StopClock;  break;
		case Timer_Noprescaler: TCCR0 |= TimerNo_Prescalig;  break;
		case Timer_prescaler8: TCCR0 |= TimerDiv_By_8;  break;
		case Timer_prescaler64: TCCR0 |= TimerDiv_By_64;  break;
		case Timer_prescaler256: TCCR0 |= TimerDiv_By_256; break;
		case Timer_prescaler1024: TCCR0 |= TimerDiv_By_1024;  break;
		default:    break;
		}

		/* Clear Registers  */
		TCNT0 = 0;
		OCR0  = 0;
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

/*CallBack initialize Timer1 with configuration you choose
 * Input: void
 * return: void
 */
void vTimer1_Initprebuild (void)
{
	/* Timer/Counter Waveform Generation mode */
#if Timer1Waveform_Mode == Normal
	CLR_BIT(TCCR1B,WGM13);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1A,WGM10);
#elif Timer1Waveform_Mode == CTC_OCR1A_TOP
	CLR_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1A,WGM10);
#elif Timer1Waveform_Mode == CTC_ICR1_TOP
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1A,WGM10);
#elif Timer1Waveform_Mode == Fast_PWM_ICR1
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1A,WGM10);
#elif Timer1Waveform_Mode == Fast_PWM_OCR1A
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1A,WGM10);
#else
#error "Wrong Choice, Please choose correctly"
#endif

	/*choose compare output mode for Channel A*/
#if Timer1CompareOutput_ModeChannelA == NormalOperation
	CLR_BIT(TCCR1A,COM1A0);
	CLR_BIT(TCCR1A,COM1A1);
#elif Timer1CompareOutput_ModeChannelA == ToggleOC1A_OC1B
	SET_BIT(TCCR1A,COM1A0);
	CLR_BIT(TCCR1A,COM1A1);
#elif Timer1CompareOutput_ModeChannelA == ClearOnCompare_SetAtTop
	CLR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#elif Timer1CompareOutput_ModeChannelA == CLEAR_UpCounting_SET_DownCounting
	CLR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#elif Timer1CompareOutput_ModeChannelA == SetAtCompare_ClearOnTop
	SET_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#elif Timer1CompareOutput_ModeChannelA == SET_UpCounting_CLEAR_DownCounting
	SET_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*choose compare output mode for Channel B*/
#if Timer1CompareOutput_ModeChannelB == NormalOperation
	CLR_BIT(TCCR1A,COM1B0);
	CLR_BIT(TCCR1A,COM1B1);
#elif Timer1CompareOutput_ModeChannelB == ToggleOC1A_OC1B
	SET_BIT(TCCR1A,COM1B0);
	CLR_BIT(TCCR1A,COM1B1);
#elif Timer1CompareOutput_ModeChannelB == ClearOnCompare_SetAtTop
	CLR_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
#elif Timer1CompareOutput_ModeChannelB == SetAtCompare_ClearOnTop
	SET_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Disable or Enable Overflow Interrupt*/
#if Timer1_OverflowInterrupt == Timer1_OVEnableInterrupt
	SET_BIT(TIMSK,TOIE1);
#elif Timer1_OverflowInterrupt == Timer1_OVDisableInterrupt
	CLR_BIT(TIMSK,TOIE1);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Disable or Enable CTC Channel A Interrupt*/
#if Timer1_ChannelACTCInterrupt == Timer1_ChannelACTCEnableInterrupt
	SET_BIT(TIMSK,OCIE1A);
#elif Timer1_ChannelACTCInterrupt == Timer1_ChannelACTCDisableInterrupt
	CLR_BIT(TIMSK,OCIE1A);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Disable or Enable CTC Channel B Interrupt*/
#if Timer1_ChannelBCTCInterrupt == Timer1_ChannelBCTCEnableInterrupt
	SET_BIT(TIMSK,OCIE1B);
#elif Timer1_ChannelBCTCInterrupt == Timer1_ChannelBCTCDisableInterrupt
	CLR_BIT(TIMSK,OCIE1B);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Disable or Enable Input Capture Unit Interrupt*/
#if Timer1_ICUInterrupt == Timer1_ICUEnableInterrupt
	SET_BIT(TIMSK,TICIE1);
#elif Timer1_ICUInterrupt == Timer1_ICUDisableInterrupt
	CLR_BIT(TIMSK,TICIE1);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Set Preload Value on TCNT1*/
	TCNT1 = Timer1_PreloadValue;

	/*Set Compare Value on OCR1A/OCR1B*/
	OCR1A = Timer1_CompareAValue;
	OCR1B = Timer1_CompareBValue;

	/*Set Value on ICR1*/
	ICR1 = Timer1_ICR1Value;

	/* Clock Select Bit Description ---> Prescaler */
	TCCR1B &= TimerPrescaler_Mask;
	TCCR1B |= Timer1Prescaler_Select;


}

uint8_t vTimer1_Initpostbuild (EN_Timer1Mode_t ENcopy_mode, EN_TimerPrescaler_t ENcopy_prescaler)
{
	uint8_t u8Local_Error = OK;

	if(ENcopy_mode <= Fast_PWM_OCR1Amode && ENcopy_prescaler <= Timer_prescaler1024)
	{
		switch(ENcopy_mode)
		{
		case NormalTimer1mode: CLR_BIT(TCCR1B,WGM13);   CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1A,WGM11);   CLR_BIT(TCCR1A,WGM10);  break;
		case CTC_OCR1A_TOPmode: CLR_BIT(TCCR1B,WGM13);  SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1A,WGM11);  CLR_BIT(TCCR1A,WGM10);  break;
		case CTC_ICR1_TOPmode: SET_BIT(TCCR1B,WGM13);   SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1A,WGM11);   CLR_BIT(TCCR1A,WGM10);  break;
		case Fast_PWM_ICR1mode: SET_BIT(TCCR1B,WGM13);  SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1A,WGM11);  CLR_BIT(TCCR1A,WGM10);  break;
		case Fast_PWM_OCR1Amode: SET_BIT(TCCR1B,WGM13);   SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1A,WGM11);   SET_BIT(TCCR1A,WGM10);  break;
		default:    break;
		}

		/* Clock Select Bit Description ---> Prescaler */
		TCCR1B &= TimerPrescaler_Mask;
		switch(ENcopy_prescaler)
		{
		case Timer_Stop:        TCCR1B |= Timer_StopClock;  break;
		case Timer_Noprescaler: TCCR1B |= TimerNo_Prescalig;  break;
		case Timer_prescaler8: TCCR1B |= TimerDiv_By_8;  break;
		case Timer_prescaler64: TCCR1B |= TimerDiv_By_64;  break;
		case Timer_prescaler256: TCCR1B |= TimerDiv_By_256; break;
		case Timer_prescaler1024: TCCR1B |= TimerDiv_By_1024;  break;
		default:    break;
		}
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

void vTimer2_Initprebuild (void)
{
	/* Timer/Counter Waveform Generation Mode of Operation */
#if Timer2Waveform_Mode == Normal
	CLR_BIT(TCCR2,WGM00);
	CLR_BIT(TCCR2,WGM01);
#elif Timer2Waveform_Mode == PWM_Phase_Correct
	SET_BIT(TCCR2,WGM00);
	CLR_BIT(TCCR2,WGM01);
#elif Timer2Waveform_Mode == CTC
	CLR_BIT(TCCR2,WGM00);
	SET_BIT(TCCR2,WGM01);
#elif Timer2Waveform_Mode == Fast_PWM
	SET_BIT(TCCR2,WGM00);
	SET_BIT(TCCR2,WGM01);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*choose compare output mode*/
#if Timer2CompareOutput_Mode == NormalOperation
	CLR_BIT(TCCR2,COM20);
	CLR_BIT(TCCR2,COM21);
#elif Timer2CompareOutput_Mode == ToggleOC2
	SET_BIT(TCCR2,COM20);
	CLR_BIT(TCCR2,COM21);
#elif Timer2CompareOutput_Mode == ClearOnCompare_SetAtTop
	CLR_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
#elif Timer2CompareOutput_Mode == CLEAR_UpCounting_SET_DownCounting
	CLR_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
#elif Timer2CompareOutput_Mode == SetAtCompare_ClearOnTop
	SET_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
#elif Timer2CompareOutput_Mode == SET_UpCounting_CLEAR_DownCounting
	SET_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
#else
#error "Wrong choice, please choose correctly"
#endif


	/*Disable or Enable Overflow Interrupt*/
#if Timer2_OverflowInterrupt == Timer2_OVEnableInterrupt
	SET_BIT(TIMSK,TOIE2);
#elif Timer2_OverflowInterrupt == Timer2_OVDisableInterrupt
	CLR_BIT(TIMSK,TOIE2);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Disable or Enable CTC Interrupt*/
#if Timer2_CTCInterrupt == Timer2_CTCEnableInterrupt
	SET_BIT(TIMSK,OCIE2);
#elif Timer2_CTCInterrupt == Timer2_CTCDisableInterrupt
	CLR_BIT(TIMSK,OCIE2);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Set Preload Value on TCNT2*/
	TCNT2 = Timer2_PreloadValue;

	/*Set Compare Value on OCR2*/
	OCR2 = Timer2_CompareValue;

	/* Clock Select Bit Description ---> Prescaler */
	TCCR2 &= Timer2Prescaler_Mask;
	TCCR2 |= Timer2Prescaler_Select;
}
void vTimer2_Initpostbuild (EN_TimerMode_t ENcopy_mode, EN_Timer2Prescaler_t ENcopy_prescaler)
{
	switch(ENcopy_mode)
	{
	case NormalTimermode: CLR_BIT(TCCR2,WGM20);   CLR_BIT(TCCR2,WGM21);  break;
	case PWM_phasecorrectmode: SET_BIT(TCCR2,WGM20);    CLR_BIT(TCCR2,WGM21);  break;
	case CTCmode: CLR_BIT(TCCR2,WGM20);     SET_BIT(TCCR2,WGM21);  break;
	case Fast_PWMmode: SET_BIT(TCCR2,WGM20);      SET_BIT(TCCR2,WGM21);  break;
	default:    break;
	}

	/* Clock Select Bit Description ---> Prescaler */
	TCCR2 &= Timer2Prescaler_Mask;
	switch(ENcopy_prescaler)
	{
	case Timer2_Stop: TCCR2 |= Timer2_StopClock;  break;
	case Timer2_Noprescaler: TCCR2 |= Timer2No_Prescalig;  break;
	case Timer2_prescaler8: TCCR2 |= Timer2Div_By_8;  break;
	case Timer2_prescaler32: TCCR2 |= Timer2Div_By_32;  break;
	case Timer2_prescaler64: TCCR2 |= Timer2Div_By_64; break;
	case Timer2_prescaler128: TCCR2 |= Timer2Div_By_128;  break;
	case Timer2_prescaler256: TCCR2 |= Timer2Div_By_256;  break;
	case Timer2_prescaler1024: TCCR2 |= Timer2Div_By_1024;  break;
	default:    break;
	}

	/* Clear Registers  */
	TCNT2 = 0;
	OCR2  = 0;
}

/****************************************Timer0 Post Configurations****************************************/
/*set preload value for Timer0 to start count from it
 * Input: takes preload value for Timer0 to start count from it
 * return: Error State
 */
uint8_t u8Timer0_SetOverFlowPreload(uint8_t u8copy_tValue)
{
	uint8_t u8Local_Error = OK;

	if(u8copy_tValue >= 0)
	{
		TCNT0 = u8copy_tValue;
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}
void vTimer0_SetCompMatchValue(uint8_t u8copy_tValue)
{
	OCR0 = u8copy_tValue;
}

/*Disable Timer0 OverFlow Interrupt
 * Input: void
 * return: void
 */
void vTimer0_DisableOverFlowInterrupt(void)
{
	CLR_BIT(TIMSK,TOIE0);
}

/*Enable Timer0 OverFlow Interrupt
 * Input: void
 * return: void
 */
void vTimer0_EnableCOverFlowInterrupt(void)
{
	SET_BIT(TIMSK,TOIE0);
}

void vTimer0_DisableCompareMatchInterrupt(void)
{
	CLR_BIT(TIMSK,OCIE0);
}
void vTimer0_EnableCompareMatchInterrupt(void)
{
	SET_BIT(TIMSK,OCIE0);
}

uint8_t  u8Timer0_SetCompareMatchMode(uint8_t u8copy_tValue)
{
	uint8_t u8Local_ErrorState = OK;
	switch(u8copy_tValue)
	{
	case SET_AT_TOP_CLEAR_AT_COMPARE: CLR_BIT(TCCR0,COM00); SET_BIT(TCCR0,COM01);   break;
	case SET_DownCounting_CLEAR_UpCounting: CLR_BIT(TCCR0,COM00); SET_BIT(TCCR0,COM01);   break;
	case CLEAR_AT_TOP_SET_AT_COMPARE: SET_BIT(TCCR0,COM00); SET_BIT(TCCR0,COM01);   break;
	case CLEAR_DownCounting_SET_UpCounting: SET_BIT(TCCR0,COM00); SET_BIT(TCCR0,COM01);   break;
	case NORMAL_OPERATION: CLR_BIT(TCCR0,COM00);   CLR_BIT(TCCR0,COM01);   break;
	case TOGGLE: SET_BIT(TCCR0,COM00);   CLR_BIT(TCCR0,COM01);   break;
	default: u8Local_ErrorState = NOK;
	}

	return u8Local_ErrorState;
}

void vTimer0_Stop(void)
{
	/* Clock Select Bit Description ---> Prescaler */
	TCCR0 &= TimerPrescaler_Mask;
	TCCR0 |= Timer_StopClock;
}
uint8_t  u8Timer0_GetTimerValue(uint8_t *u8Copy_Value)
{
	uint8_t u8Local_ErrorState = OK;

	if(u8Copy_Value != NULL)
		*u8Copy_Value = TCNT0;
	else
		u8Local_ErrorState = NULLPOINTER;
	return u8Local_ErrorState;
}
void vTimer0_ResetTimer(void)
{
	TCNT0 = 0;
}

/*******************************************************************************************************************/
/****************************************Timer1 Post Configurations****************************************/

void vTimer1_DisableCompareMatchInterrupt(uint8_t u8copy_ChannelID)
{
	switch(u8copy_ChannelID)
	{
	case CHANNEL_A: CLR_BIT(TIMSK,OCIE1A);   break;
	case CHANNEL_B: CLR_BIT(TIMSK,OCIE1B);   break;
	default:  break;
	}
}
void vTimer1_EnableCompareMatchInterrupt(uint8_t u8copy_ChannelID)
{
	switch(u8copy_ChannelID)
	{
	case CHANNEL_A: SET_BIT(TIMSK,OCIE1A);   break;
	case CHANNEL_B: SET_BIT(TIMSK,OCIE1B);   break;
	default:  break;
	}
}
/*Set compare value in channel A or B form compare match
 * Input: takes channel & value
 * return: Error State
 */
uint8_t u8Timer1_SetCompValue(uint8_t u8Copy_Channel, uint16_t u16Copy_Value)
{
	uint8_t u8Local_Error = OK;

	if(u8Copy_Channel <= 1 && u16Copy_Value >= 0)
	{
		switch (u8Copy_Channel)
		{
		case CHANNEL_A: OCR1A = u16Copy_Value;      break;
		case CHANNEL_B: OCR1B = u16Copy_Value;      break;
		default:        break;
		}
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

/*set preload value for Timer1 to start count from it
 * Input: takes preload value for Timer1 to start count from it
 * return: Error State
 */
uint8_t u8Timer1_SetOverFlowPreload(uint16_t u16Copy_TCNT1)
{
	uint8_t u8Local_Error = OK;

	if(u16Copy_TCNT1 >= 0)
	{
		TCNT1 = u16Copy_TCNT1;
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

void vTimer1_DisableOverFlowInterrupt(void)
{
	CLR_BIT(TIMSK,TOIE1);
}
void vTimer1_EnableOverFlowInterrupt(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void vTimer1_SetICRValue(uint16_t u16Copy_ICR)
{
	ICR1 = u16Copy_ICR;
}
void vTimer1_ICUInit(void)
{
	/* Edge Select */
#if ICU_SelectEdge == Rising_Edge
	SET_BIT(TCCR1B,ICES1);
#elif ICU_SelectEdge == Falling_Edge
	CLR_BIT(TCCR1B,ICES1);
#else
#error "Wrong Choice, Please choose correctly"
#endif
}
void vTimer1_DisableICUInterrupt(void)
{
	CLR_BIT(TIMSK,TICIE1);
}
void vTimer1_EnableICUInterrupt(void)
{
	SET_BIT(TIMSK,TICIE1);
}

uint16_t  u16Timer1_ICUGetTimerRead(void)
{
	return ICR1;
}
void vTimer1_ICUSetEdge(uint8_t copy_uint8_tEdgeId)
{
	switch(copy_uint8_tEdgeId)
	{
	case ICU_RISING_EDGE : SET_BIT(TCCR1B,ICES1);				break;

	case ICU_FALLING_EDGE: CLR_BIT(TCCR1B,ICES1);    			break;
	}
}
void vTimer1_ICUDeInit(void)
{
	/* Stop & Reset all module functionality */
	TCNT1 = 0;
	ICR1  = 0;

	CLR_BIT(TIMSK,TICIE1);
}

uint8_t  u8Timer1_SetCompareMatchMode(uint8_t u8copy_ChannelID, uint8_t u8Copy_Mode)
{
	uint8_t u8Local_ErrorState = OK;

	switch(u8copy_ChannelID)
	{
	case CHANNEL_A:
		switch(u8Copy_Mode)
		{
		case SET_AT_TOP_CLEAR_AT_COMPARE: CLR_BIT(TCCR1A,COM1A0);   SET_BIT(TCCR1A,COM1A1);   break;
		case SET_DownCounting_CLEAR_UpCounting: CLR_BIT(TCCR1A,COM1A0);   SET_BIT(TCCR1A,COM1A1);   break;
		case CLEAR_AT_TOP_SET_AT_COMPARE: SET_BIT(TCCR1A,COM1A0);   SET_BIT(TCCR1A,COM1A1);	   break;
		case CLEAR_DownCounting_SET_UpCounting: SET_BIT(TCCR1A,COM1A0);   SET_BIT(TCCR1A,COM1A1);	   break;
		case NORMAL_OPERATION: CLR_BIT(TCCR1A,COM1A0);   CLR_BIT(TCCR1A,COM1A1);   break;
		case TOGGLE: SET_BIT(TCCR1A,COM1A0);     CLR_BIT(TCCR1A,COM1A1);   break;
		default: u8Local_ErrorState = NOK;           break;
		}      break;

		case CHANNEL_B:
			switch(u8Copy_Mode)
			{
			case SET_AT_TOP_CLEAR_AT_COMPARE: CLR_BIT(TCCR1A,COM1B0);   SET_BIT(TCCR1A,COM1B1);   break;
			case SET_DownCounting_CLEAR_UpCounting: CLR_BIT(TCCR1A,COM1B0);   SET_BIT(TCCR1A,COM1B1);   break;
			case CLEAR_AT_TOP_SET_AT_COMPARE: SET_BIT(TCCR1A,COM1B0);   SET_BIT(TCCR1A,COM1B1);	   break;
			case CLEAR_DownCounting_SET_UpCounting: SET_BIT(TCCR1A,COM1B0);   SET_BIT(TCCR1A,COM1B1);	   break;
			case NORMAL_OPERATION: CLR_BIT(TCCR1A,COM1B0);   CLR_BIT(TCCR1A,COM1B1);   break;
			case TOGGLE: SET_BIT(TCCR1A,COM1B0);     CLR_BIT(TCCR1A,COM1B1);   break;
			default: u8Local_ErrorState = NOK;	           break;
			}           break;
			default: u8Local_ErrorState = NOK;            break;
	}

	return u8Local_ErrorState;
}

void vTimer1_Stop(void)
{
	/* Clock Select Bit Description ---> Prescaler */
	TCCR1B &= TimerPrescaler_Mask;
	TCCR1B |= Timer_StopClock;
}
uint8_t  u8Timer1_GetTimerValue(uint16_t *u16Copy_Value)
{
	uint8_t u8Local_ErrorState = OK;

	if(u16Copy_Value != NULL)
		*u16Copy_Value = TCNT1;
	else
		u8Local_ErrorState = NULLPOINTER;
	return u8Local_ErrorState;
}
void vTimer1_ResetTimer(void)
{
	TCNT1 = 0;
}

/****************************************Timer2 Post Configurations****************************************/

void vTimer2_SetOverFlowPreload(uint8_t u8copy_tValue)
{
	TCNT2 = u8copy_tValue;
}
void vTimer2_SetCompMatchValue(uint8_t u8copy_tValue)
{
	OCR2 = u8copy_tValue;
}
void vTimer2_DisableOverFlowInterrupt(void)
{
	CLR_BIT(TIMSK,TOIE2);
}

void vTimer2_EnableOverFlowInterrupt(void)
{
	SET_BIT(TIMSK,TOIE2);
}

void vTimer2_DisableCompareMatchInterrupt(void)
{
	CLR_BIT(TIMSK,OCIE2);
}
void vTimer2_EnableCompareMatchInterrupt(void)
{
	SET_BIT(TIMSK,OCIE2);
}

uint8_t  u8Timer2_SetCompareMatchMode(uint8_t u8copy_tValue)
{
	uint8_t u8Local_ErrorState = OK;
	switch(u8copy_tValue)
	{
	case SET_AT_TOP_CLEAR_AT_COMPARE: CLR_BIT(TCCR2,COM20); SET_BIT(TCCR2,COM21);   break;
	case SET_DownCounting_CLEAR_UpCounting: CLR_BIT(TCCR2,COM20); SET_BIT(TCCR2,COM21);   break;
	case CLEAR_AT_TOP_SET_AT_COMPARE: SET_BIT(TCCR2,COM20); SET_BIT(TCCR2,COM21);   break;
	case CLEAR_DownCounting_SET_UpCounting: SET_BIT(TCCR2,COM20); SET_BIT(TCCR2,COM21);   break;
	case NORMAL_OPERATION: CLR_BIT(TCCR2,COM20);   CLR_BIT(TCCR2,COM21);   break;
	case TOGGLE: SET_BIT(TCCR2,COM20);   CLR_BIT(TCCR2,COM21);   break;
	default: u8Local_ErrorState = NOK;
	}

	return u8Local_ErrorState;
}

void vTimer2_Stop(void)
{
	/* Clock Select Bit Description ---> Prescaler */
	TCCR2 &= Timer2Prescaler_Mask;
	TCCR2 |= Timer2_StopClock;
}
uint8_t  u8Timer2_GetTimerValue(uint8_t *u8Copy_Value)
{
	uint8_t u8Local_ErrorState = OK;

	if(u8Copy_Value != NULL)
		*u8Copy_Value = TCNT2;
	else
		u8Local_ErrorState = NULLPOINTER;
	return u8Local_ErrorState;
}
void vTimer2_ResetTimer(void)
{
	TCNT2 = 0;
}

/******************************* Set callback function for all Timers interrupts source *****************************/
uint8_t u8Timer_SetCallbackFunction (void (*pvCopy_CallbackFunction) (void), uint8_t u8Copy_InterruptSource)
{
	uint8_t u8Local_ErrorState = OK;

	if(pvCopy_CallbackFunction != NULL)
	{
		pvTimer_CallbackFunction[u8Copy_InterruptSource] = pvCopy_CallbackFunction;
	}else{
		u8Local_ErrorState = NULLPOINTER;
	}

	return u8Local_ErrorState;
}
/*******************************************************************************************************************/

/********************************************** ISR Body Definition ************************************************/
/************************************************* Timer0 *******************************************/

ISR(TIMER0_OVF)
{
	if (pvTimer_CallbackFunction[Timer0_Overflow] != NULL)
	{
		pvTimer_CallbackFunction[Timer0_Overflow]();
	}else{
		/*Do Nothing*/
	}
}

ISR(TIMER0_COMP)
{
	if (pvTimer_CallbackFunction[Timer0_CompareMatch] != NULL)
	{
		pvTimer_CallbackFunction[Timer0_CompareMatch]();
	}else{
		/*Do Nothing*/
	}
}

/************************************************* TIMER1 *******************************************/
ISR(TIMER1_OVF)
{
	if (pvTimer_CallbackFunction[Timer1_Overflow] != NULL)
	{
		pvTimer_CallbackFunction[Timer1_Overflow]();
	}else{
		/*Do Nothing*/
	}
}

ISR(TIMER1_COMPB)
{
	if (pvTimer_CallbackFunction[Timer1_CompareMatchB] != NULL)
	{
		pvTimer_CallbackFunction[Timer1_CompareMatchB]();
	}else{
		/*Do Nothing*/
	}
}

ISR(TIMER1_COMPA)
{
	if (pvTimer_CallbackFunction[Timer1_CompareMatchA] != NULL)
	{
		pvTimer_CallbackFunction[Timer1_CompareMatchA]();
	}else{
		/*Do Nothing*/
	}
}

ISR(TIMER1_CAPT)
{
	if (pvTimer_CallbackFunction[Timer1_CaptureEvent] != NULL)
	{
		pvTimer_CallbackFunction[Timer1_CaptureEvent]();
	}else{
		/*Do Nothing*/
	}
}

/************************************************* Timer2 *******************************************/

ISR(TIMER2_OVF)
{
	if (pvTimer_CallbackFunction[Timer2_Overflow] != NULL)
	{
		pvTimer_CallbackFunction[Timer2_Overflow]();
	}else{
		/*Do Nothing*/
	}
}

ISR(TIMER2_COMP)
{
	if (pvTimer_CallbackFunction[Timer2_CompareMatch] != NULL)
	{
		pvTimer_CallbackFunction[Timer2_CompareMatch]();
	}else{
		/*Do Nothing*/
	}
}
