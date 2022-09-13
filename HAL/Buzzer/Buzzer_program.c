/*
 * Buzzer_program.c
 *
 *  	Name: Mohamed Hussein
 * 		Layer: HAL
 * 		Version: V1.0 - 15/10/2021
 */
#include "util/delay.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "Buzzer_configuration.h"
#include "Buzzer_interface.h"

void vBuzzer_Init(void)
{
	u8DIO_PinDir(BUZZER_PORT,BUZZER_PIN,DIO_OUTPUT);
}

void vBuzzer_ON(void)
{
	u8DIO_PinVal(BUZZER_PORT,BUZZER_PIN,DIO_HIGH);
}

void vBuzzer_PlayTone(uint16_t u16Copy_Duration, uint16_t u16Copy_Frequency)
{
	uint32_t u32Local_Wavelength, u32Local_HalfPeriod, u32Local_Cycles, u32Local_Counter, u32Local_RequiredTime;

	u32Local_RequiredTime = (uint32_t) ( (uint32_t) u16Copy_Duration * 1000);
	u32Local_Wavelength = (uint32_t)(1000000UL / (uint32_t)u16Copy_Frequency);
	/*the number of cycles*/
	u32Local_Cycles = (uint32_t) (u32Local_RequiredTime / u32Local_Wavelength);
	/*the time between each toggle*/
	u32Local_HalfPeriod = u32Local_Wavelength / 2UL;

	if(u16Copy_Frequency == PAUSE)
		_delay_us(u32Local_RequiredTime);
	else
	{
		for(u32Local_Counter = 0; u32Local_Counter<u32Local_Cycles; u32Local_Counter++)
		{
			u8DIO_PinVal(BUZZER_PORT,BUZZER_PIN,DIO_HIGH);
			_delay_us(u32Local_HalfPeriod);
			u8DIO_PinVal(BUZZER_PORT,BUZZER_PIN,DIO_LOW);
			_delay_us(u32Local_HalfPeriod);
		}
	}
}

void vBuzzer_Stop(void)
{
	u8DIO_PinVal(BUZZER_PORT,BUZZER_PIN,DIO_LOW);
}
