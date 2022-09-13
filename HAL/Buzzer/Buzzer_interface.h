/*
 * Buzzer_interface.h
 *
 *  	Name: Mohamed Hussein
 * 		Layer: HAL
 * 		Version: V1.0 - 15/10/2021
 */

#ifndef _BUZZER_INTERFACE_H
#define _BUZZER_INTERFACE_H

#define PAUSE	1
#define END		0



#define A		1500//880
#define B		1700//988
#define C		1900//1047
#define D		2100//1175
#define E		2300//1319
#define F		2500//1397
#define G		2700//1568

void vBuzzer_Init(void);
void vBuzzer_ON(void);
void vBuzzer_PlayTone(uint16_t u16Copy_Duration, uint16_t u16Copy_Frequency);
void vBuzzer_Stop(void);

#endif /* HAL_BUZZER_BUZZER_INTERFACE_H_ */
