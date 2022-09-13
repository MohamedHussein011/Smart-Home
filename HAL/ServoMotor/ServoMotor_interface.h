/*
 * ServoMotor_interface.h
 *
 *  	Name: Mohamed Hussein
 * 		Layer: HAL
 * 		Version: V1.0 - 15/10/2021
 */

#ifndef _SERVOMOTOR_INTERFACE_H
#define _SERVOMOTOR_INTERFACE_H

/*Minimum & Maximum on time for Servo Motor     750us --> 0 degree, 2500us --> 180 degree*/
#define MAX_ON       2000
#define MIN_ON       1000

/*Channel Options:
 * 		1: A_CHANNEL
 * 		2: B_CHANNEL
 * */
#define A_CHANNEL           0
#define B_CHANNEL           1

uint8_t u8ServoMotor_SetAngle(uint8_t u8Copy_Channel, uint8_t u8Copy_Degree);
void vServoMotor_Stop(void);

#endif /* HAL_SERVOMOTOR_SERVOMOTOR_INTERFACE_H_ */
