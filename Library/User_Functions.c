/*
 * User_Functions.c
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: Library
 */
#include "STD_TYPE.h"
#include "User_Functions.h"

void ConvertToString(char* Copy_String, int32_t s32Copy_Number)
{
	int32_t s32Local_Temp1 = 0, s32Local_Length = 0, s32Local_Remainder = 0, s32Local_Temp2 = 0;

	if(s32Copy_Number == 0)
	{
		Copy_String[0] = '0';
		s32Local_Length++;
		Copy_String[s32Local_Length] = '\0';
	}
	else
	{
		s32Local_Temp2 = s32Copy_Number;
		if(s32Local_Temp2<0)
		{
			s32Local_Length++;
			s32Copy_Number *= -1;
		}

		s32Local_Temp1 = s32Copy_Number;
		while(s32Local_Temp1 > 0)
		{
			s32Local_Temp1 /= 10;
			s32Local_Length++;
		}

		for(uint8_t i = 0; i<s32Local_Length; i++)
		{
			s32Local_Remainder = s32Copy_Number % 10;
			s32Copy_Number = s32Copy_Number / 10;
			Copy_String[s32Local_Length - (i+1)] = s32Local_Remainder + '0';
		}

		if(s32Local_Temp2 < 0)
			Copy_String[0] = '-';

		Copy_String[s32Local_Length] = '\0';
	}
}
int32_t ConvertToint(const char* Copy_String)
{
	int32_t s32Local_Number = 0;
	int8_t u8Local_sign = 1, u8Local_Iterator = 0;
	if(Copy_String[0] == '-')
	{
		u8Local_sign = -1;
		u8Local_Iterator = 1;
	}

	while(Copy_String[u8Local_Iterator] != '\0')
	{
		if((Copy_String[u8Local_Iterator] - '0' < 0) || (Copy_String[u8Local_Iterator] - '0' > 9))
			break;
		s32Local_Number = (s32Local_Number*10) + (Copy_String[u8Local_Iterator] - '0');
		u8Local_Iterator++;
	}

	s32Local_Number *= u8Local_sign;
	return s32Local_Number;
}

char StringCompare(const char* pu8Copy_String1, const char* pu8Copy_String2)
{
	uint8_t u8Local_Flag = 0;

	while(*pu8Copy_String1 != '\0' || *pu8Copy_String2 != '\0')
	{
		if(*pu8Copy_String1 == *pu8Copy_String2)
		{
			pu8Copy_String1++;
			pu8Copy_String2++;
		}
		else if((*pu8Copy_String1 == '\0' && *pu8Copy_String2 != '\0') || (*pu8Copy_String1 != '\0' && *pu8Copy_String2 == '\0') || (*pu8Copy_String1 != *pu8Copy_String2))
		{
			u8Local_Flag=1;
			break;
		}

	}
	if(u8Local_Flag == 0)
		return 0;
	else
		return 1;
}

char StringLength(const char* pu8Copy_String)
{
	uint16_t u16LocalCounter = 0;
	while (*pu8Copy_String != 0 || *pu8Copy_String != '\0')
	{
		u16LocalCounter++;
		pu8Copy_String++;
	}

	return u16LocalCounter;
}

void StringReset(char* pu8Copy_String)
{
	uint16_t u16LocalCounter = 0;
	uint16_t u16LocalLength = 0;
	u16LocalLength = StringLength(pu8Copy_String);
	while(u16LocalCounter < u16LocalLength)
	{
		*(pu8Copy_String + u16LocalCounter) = 0;
		u16LocalCounter++;
	}
}
