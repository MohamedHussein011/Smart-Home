/*
 * Name: Muhammad Hussein Muhammad Salem
 * Layer: MCAL
 * Version: V1.0 - 08/11/2021
 *
 */


#ifndef _TIMER_PRIVATE_H
#define _TIMER_PRIVATE_H

/************************************************* TIMER0 *******************************************/
/* Waveform Generation Mode Bit Description
   Options: 
		1: Normal   -  OverFlow
		2: PWM_Phase_Correct
		3: CTC - Clear Timer on Compare Match
		4: Fast_PWM
 */

#define Normal                1
#define PWM_Phase_Correct     2
#define CTC                   3
#define Fast_PWM              4

/* compare output mode Description
   Options:
		1: NormalOperation   -  , OC0 disconnected
		2: ToggleOC0		- Non PWM mode
		3: ClearOnCompare_SetAtTop    -    Clear OC0 on compare match, set OC0 at TOP (Non-Inverted mode)
		4: SetAtCompare_ClearOnTop			- Set OC0 on compare match, clear OC0 at TOP (Inverted mode)
		5: CLEAR_DownCounting_SET_UpCounting         - Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting
		6: SET_DownCounting_CLEAR_UpCounting         - Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting
 */

#define NormalOperation                           0
#define ToggleOC0                                 1
#define ClearOnCompare_SetAtTop                   2
#define SetAtCompare_ClearOnTop                   3
#define ToggleOC1A_OC1B                           4
#define ToggleOC2                                 5
#define SET_UpCounting_CLEAR_DownCounting         6
#define CLEAR_UpCounting_SET_DownCounting         7

/* Clock Select - Prescaler
   Options: 
		1: Timer_StopClock
		2: TimerNo_Prescalig       -   Clock Source
		3: TimerDiv_By_8           -   Division by 8
		4: TimerDiv_By_64          -   Division by 64
		5: TimerDiv_By_256         -   Division by 256
		6: TimerDiv_By_1024        -   Division by 1024
 */
#define TimerPrescaler_Mask    0xF8

#define Timer_StopClock        0
#define TimerNo_Prescalig      1
#define TimerDiv_By_8          2
#define TimerDiv_By_64         3
#define TimerDiv_By_256        4
#define TimerDiv_By_1024       5

/* Disable or Enable Overflow Interrupt
   Options:
		1: Timer0_EnableInterrupt
		2: Timer0_DisableInterrupt
 */
#define Timer0_OVEnableInterrupt         0
#define Timer0_OVDisableInterrupt		 1

/* Disable or Enable CTC Interrupt
   Options:
		1: Timer0_CTCEnableInterrupt
		2: Timer0_CTCDisableInterrupt
 */
#define Timer0_CTCEnableInterrupt         0
#define Timer0_CTCDisableInterrupt        1
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

#define    CTC_OCR1A_TOP    				          2
#define    CTC_ICR1_TOP   					          3
#define    Fast_PWM_ICR1   				              4
#define    Fast_PWM_OCR1A  				              5

/* Disable or Enable Overflow Interrupt
   Options:
		1: Timer1_EnableInterrupt
		2: Timer1_DisableInterrupt
 */
#define Timer1_OVEnableInterrupt         0
#define Timer1_OVDisableInterrupt		 1

/* Disable or Enable CTC Channel A Interrupt
   Options:
		1: Timer1_ChannelACTCEnableInterrupt
		2: Timer1_ChannelACTCDisableInterrupt
 */
#define Timer1_ChannelACTCEnableInterrupt         0
#define Timer1_ChannelACTCDisableInterrupt	      1

/* Disable or Enable CTC Channel B Interrupt
   Options:
		1: Timer1_ChannelBCTCEnableInterrupt
		2: Timer1_ChannelBCTCDisableInterrupt
 */
#define Timer1_ChannelBCTCEnableInterrupt         0
#define Timer1_ChannelBCTCDisableInterrupt	      1

/* Disable or Enable Input Capture Unit Interrupt
   Options:
		1: Timer1_ICUEnableInterrupt
		2: Timer1_ICUDisableInterrupt
 */
#define Timer1_ICUEnableInterrupt 			0
#define Timer1_ICUDisableInterrupt 			1

/* Edge Select for Input Capture Unit - ICU
   Options:
		1: Rising_Edge
		2: Falling_Edge
 */

#define Rising_Edge           1
#define Falling_Edge          2

/************************************************* TIMER2 *******************************************/
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
#define Timer2Prescaler_Mask    0xF8

#define Timer2_StopClock            0
#define Timer2No_Prescalig          1
#define Timer2Div_By_8              2
#define Timer2Div_By_32             3
#define Timer2Div_By_64             4
#define Timer2Div_By_128            5
#define Timer2Div_By_256            6
#define Timer2Div_By_1024           7

/* Disable or Enable Overflow Interrupt
   Options:
		1: Timer2_EnableInterrupt
		2: Timer2_DisableInterrupt
 */
#define Timer2_OVEnableInterrupt         0
#define Timer2_OVDisableInterrupt		 1

/* Disable or Enable CTC Interrupt
   Options:
		1: Timer2_CTCEnableInterrupt
		2: Timer2_CTCDisableInterrupt
 */
#define Timer2_CTCEnableInterrupt         0
#define Timer2_CTCDisableInterrupt        1

#endif
