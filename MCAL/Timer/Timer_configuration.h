/*
 * Name: Muhammad Hussein Muhammad Salem
 * Layer: MCAL
 * Version: V1.0 - 08/11/2021
 *
 */


#ifndef _TIMER_CONFIGURATION_H
#define _TIMER_CONFIGURATION_H

/************************************************* TIMER0 *******************************************/
/* Waveform Generation Mode Bit Description
   Options: 
		1: Normal   -  OverFlow
		2: PWM_Phase_Correct
		3: CTC    -    Clear Timer on Compare Match
		4: Fast_PWM
 */

#define Timer0Waveform_Mode     Fast_PWM

/* compare output mode Description
   Options:
		1: NormalOperation   -  , OC0 disconnected
		2: ToggleOC0		- Non PWM mode
		3: ClearOnCompare_SetAtTop    -    Clear OC0 on compare match, set OC0 at TOP (Non-Inverted mode)
		4: SetAtCompare_ClearOnTop			- Set OC0 on compare match, clear OC0 at TOP (Inverted mode)
		5: SET_UpCounting_CLEAR_DownCounting         - Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting
		6: CLEAR_UpCounting_SET_DownCounting         - Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting
 */

#define Timer0CompareOutput_Mode     NormalOperation

/* Clock Select - Prescaler
   Options: 
		1: Timer_StopClock
		2: TimerNo_Prescalig       -   Clock Source
		3: TimerDiv_By_8           -   Division by 8
		4: TimerDiv_By_64          -   Division by 64
		5: TimerDiv_By_256         -   Division by 256
		6: TimerDiv_By_1024        -   Division by 1024
 */

#define Timer0Prescaler_Select    TimerDiv_By_8

/* Disable or Enable Overflow Interrupt
   Options:
		1: Timer0_OVEnableInterrupt
		2: Timer0_OVDisableInterrupt
 */
#define Timer0_OverflowInterrupt         Timer0_OVDisableInterrupt

/* Disable or Enable CTC Interrupt
   Options:
		1: Timer0_CTCEnableInterrupt
		2: Timer0_CTCDisableInterrupt
 */
#define Timer0_CTCInterrupt         Timer0_CTCDisableInterrupt

/*Set Preload Value on TCNT0*/
#define Timer0_PreloadValue                   0

/*Set Compare Value on OCR0*/
#define Timer0_CompareValue                    0

/****************************************************************************************************/
/************************************************* Timer1 *******************************************/
/* Waveform Generation Mode Bit Description
   Options:
		Mode 0: Normal  						 -  OverFlow
		Mode 1: CTC_OCR1A_TOP    				 -    Clear Timer on Compare Match  - OCR1A --> TOP
		Mode 2: CTC_ICR1_TOP   					 -    Clear Timer on Compare Match  - ICR1 --> TOP
		Mode 3: Fast_PWM_ICR1   			     	 - ICR1  --> TOP
		Mode 4: Fast_PWM_OCR1A  				      - OCR1A --> TOP
 */

#define Timer1Waveform_Mode     Normal

/* compare output mode for Channel A Description
   Options:
		1: NormalOperation   -  , OC1A/OC1B disconnected
		2: ToggleOC1A_OC1B		-
		3: ClearOnCompare_SetAtTop    -    Clear OC1A/OC1B on compare match, set OC1A/OC1B at TOP
		4: SetAtCompare_ClearOnTop			- Set OC1A/OC1B on compare match, clear OC1A/OC1B at TOP
		5: SET_UpCounting_CLEAR_DownCounting         - Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting
		6: CLEAR_UpCounting_SET_DownCounting         - Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting
 */

#define Timer1CompareOutput_ModeChannelA     NormalOperation

#define Timer1CompareOutput_ModeChannelB     NormalOperation

/* Clock Select - Prescaler
   Options:
		1: Timer_StopClock
		2: TimerNo_Prescalig       -   Clock Source
		3: TimerDiv_By_8           -   Division by 8
		4: TimerDiv_By_64          -   Division by 64
		5: TimerDiv_By_256         -   Division by 256
		6: TimerDiv_By_1024        -   Division by 1024
 */

#define Timer1Prescaler_Select       TimerDiv_By_8

/* Disable or Enable Overflow Interrupt
   Options:
		1: Timer1_OVEnableInterrupt
		2: Timer1_OVDisableInterrupt
 */
#define Timer1_OverflowInterrupt         Timer1_OVDisableInterrupt

/* Disable or Enable CTC Channel A Interrupt
   Options:
		1: Timer1_ChannelACTCEnableInterrupt
		2: Timer1_ChannelACTCDisableInterrupt
 */
#define Timer1_ChannelACTCInterrupt         Timer1_ChannelACTCDisableInterrupt

/* Disable or Enable CTC Channel B Interrupt
   Options:
		1: Timer1_ChannelBCTCEnableInterrupt
		2: Timer1_ChannelBCTCDisableInterrupt
 */
#define Timer1_ChannelBCTCInterrupt         Timer1_ChannelBCTCDisableInterrupt

/* Disable or Enable Input Capture Unit Interrupt
   Options:
		1: Timer1_ICUEnableInterrupt
		2: Timer1_ICUDisableInterrupt
 */
#define Timer1_ICUInterrupt         Timer1_ICUDisableInterrupt


/*Set Preload Value on TCNT1*/
#define Timer1_PreloadValue                   0

/*Set Compare Value on OCR1A*/
#define Timer1_CompareAValue                    0

/*Set Compare Value on OCR1B*/
#define Timer1_CompareBValue                    0

/*Set Compare Value on ICR1*/
#define Timer1_ICR1Value                    0

/* Edge Select for Input Capture Unit - ICU
   Options:
		1: Rising_Edge
		2: Falling_Edge
 */
#define ICU_SelectEdge       Rising_Edge

/************************************************* TIMER2 *******************************************/
/* Waveform Generation Mode Bit Description
   Options:
		1: Normal   -  OverFlow
		2: PWM_Phase_Correct
		3: CTC    -    Clear Timer on Compare Match
		4: Fast_PWM
 */

#define Timer2Waveform_Mode     Fast_PWM

/* compare output mode Description
   Options:
		1: NormalOperation   -  , OC2 disconnected
		2: ToggleOC2		- Non PWM mode
		3: ClearOnCompare_SetAtTop    -    Clear OC2 on compare match, set OC2 at TOP
		4: SetAtCompare_ClearOnTop			- Set OC2 on compare match, clear OC2 at TOP
		5: SET_UpCounting_CLEAR_DownCounting         - Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting
		6: CLEAR_UpCounting_SET_DownCounting         - Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting
 */

#define Timer2CompareOutput_Mode     NormalOperation

/* Clock Select - Prescaler
   Options:
		1: Timer2_StopClock
		2: Timer2No_Prescalig       -   Clock Source
		3: Timer2Div_By_8           -   Division by 8
		4: Timer2Div_By_32          -   Division by 32
		5: Timer2Div_By_64         -   Division by 64
		6: Timer2Div_By_128        -   Dvision by 128
		7: Timer2Div_By_256        -   Dvision by 256
		8: Timer2Div_By_1024        -   Dvision by 1024
 */

#define Timer2Prescaler_Select    Timer2Div_By_8

/* Disable or Enable Overflow Interrupt
   Options:
		1: Timer2_OVEnableInterrupt
		2: Timer2_OVDisableInterrupt
 */
#define Timer2_OverflowInterrupt         Timer2_OVDisableInterrupt

/* Disable or Enable CTC Interrupt
   Options:
		1: Timer2_CTCEnableInterrupt
		2: Timer2_CTCDisableInterrupt
 */
#define Timer2_CTCInterrupt         Timer2_CTCDisableInterrupt

/*Set Preload Value on TCNT2*/
#define Timer2_PreloadValue                   0

/*Set Compare Value on OCR2*/
#define Timer2_CompareValue                    0

#endif
