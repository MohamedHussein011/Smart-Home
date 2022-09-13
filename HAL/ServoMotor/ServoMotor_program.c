/*
 * ServoMotor_program.c
 *
 *  	Name: Mohamed Hussein
 * 		Layer: HAL
 * 		Version: V1.0 - 15/10/2021
 */

#include "../../Library/STD_TYPE.h"
#include "../../Library/Mapping_interface.h"

#include "../../MCAL/Timer/Timer_interface.h"

#include "ServoMotor_interface.h"

uint8_t u8ServoMotor_SetAngle(uint8_t u8Copy_Channel, uint8_t u8Copy_Degree)
{
	uint8_t u8Local_ErrorState = OK;

	if(u8Copy_Degree >= 0 && u8Copy_Degree <= 180)
	{
		/*mapping to get the on time required for servo to rotate*/
		uint16_t u8Local_AngleOnTime = (uint16_t) s32Map(0,180,MIN_ON,MAX_ON,u8Copy_Degree);
		/*Servo motor needs period time of 20ms -> 50Hz.*/
		vTimer1_SetICRValue(20000);
		if(u8Copy_Channel == A_CHANNEL)
		{
			/*set compare match mode*/
			u8Timer1_SetCompareMatchMode(CHANNEL_A,SET_AT_TOP_CLEAR_AT_COMPARE);
			/*set compare match value*/
			u8Timer1_SetCompValue(CHANNEL_A,u8Local_AngleOnTime);
		}
		else if(u8Copy_Channel == B_CHANNEL)
		{
			/*set compare match mode*/
			u8Timer1_SetCompareMatchMode(CHANNEL_B,SET_AT_TOP_CLEAR_AT_COMPARE);
			/*set compare match value*/
			u8Timer1_SetCompValue(CHANNEL_B,u8Local_AngleOnTime);
		}
		/*start Timer1*/
		vTimer1_Initpostbuild(Fast_PWM_ICR1mode,Timer_prescaler8);
	}
	else
		u8Local_ErrorState = OUT_RANGE;

	return u8Local_ErrorState;
}
void vServoMotor_Stop(void)
{
	vTimer1_Initpostbuild(NormalTimer1mode,Timer_Stop);
	vTimer1_Stop();
}
