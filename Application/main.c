/*
 * main.c
 *
 *  	Created on: 11/09/2022
 *      Author: Mohamed Hussein
 *      Layer: Application
 *      Smart Home
 */

//Library
#include "../Library/User_Functions.h"
#include "../Library/STD_TYPE.h"
#include "../Library/BIT_MATH.h"
#include "../Library/Mapping_interface.h"

//MCAL Drivers
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/Timer/Timer_interface.h"
#include "../MCAL/USART/USART_interface.h"
#include "../MCAL/Global_Interrupt/GIE_interface.h"
#include "../MCAL/WatchDog/WDT_interface.h"

//HAL Drivers
#include "../HAL/ServoMotor/ServoMotor_interface.h"
#include "../HAL/LED/LED_interface.h"
#include "../HAL/TempSensor/TempSensor_interface.h"
#include "../HAL/Buzzer/Buzzer_interface.h"


#define FALSE             0
#define TRUE              1
#define NUM_USERS         4
#define CLOSED            0
#define OPEN              1
#define NUM_TRIALS        3


uint8_t u8Option = 0;
uint8_t u8LightingOption = 0;
uint8_t u8LightingFlag = FALSE;
uint16_t u16ADC_Result = 0;
uint8_t u8LDR_Value = 0;
uint8_t u8Temperature_Value = 0;
uint8_t u8Temp_Value = 0;
uint8_t u8DoorFlag = CLOSED;
uint8_t u8u8FanFlag = CLOSED;
uint8_t u8Adjustu8FanFlag = CLOSED;
uint8_t u8MusicFlag = TRUE;
uint8_t u8MainRoom = CLOSED;
uint8_t u8Room1 = CLOSED;
uint8_t u8Room2 = CLOSED;

char Option[10];

void TheDoor(void);
void TheLighting(void);
void TheLightingFlag(void);
void TheFan (void);
void TheMusic(void);
void Theu8MusicFlag(void);

void main (void)
{
	//Users & Passwords
	char* UserNames[NUM_USERS] = {"ammar","mhmd","omar","osama"};
	char* Passwords[NUM_USERS] = {"1903","9324","7544","8754"};
	char pchLocal_UserName[10];
	char pchLocal_Password[10];
	uint8_t u8Local_MenuOption = 0;
	uint8_t u8Local_Flag = TRUE;
	uint8_t u8Local_NumberOfUsers = 0;
	uint8_t u8Local_Trial = 0;
	uint8_t u8Local_PermitFlag = FALSE;
	uint8_t u8Local_MainMenuFlag = TRUE;

	vPORT_Init();
	vUSART_Init();
	vADC_Init();
	vTimer0_Initprebuild();
	vTimer2_Initprebuild();
	vGlobalInterrupt_Enable();

	while(u8Local_Flag == TRUE && u8Local_Trial <= NUM_TRIALS)
	{
		//get the user & password
		u8USART_SendStringSynchronous("Welcome to your Smart Home! \n");
		u8USART_SendStringSynchronous("Please enter User name: ");
		u8USART_ReceiveStringSynchronous(pchLocal_UserName);
		u8USART_SendStringSynchronous(pchLocal_UserName);
		u8USART_SendStringSynchronous(" Password: ");
		u8USART_ReceiveStringSynchronous(pchLocal_Password);
		u8USART_SendStringSynchronous(pchLocal_Password);

		while(u8Local_NumberOfUsers < NUM_USERS)
		{
			//check if it's registered or not
			if(!StringCompare(pchLocal_UserName, *(UserNames + u8Local_NumberOfUsers)))
			{
				if(!StringCompare(pchLocal_Password, *(Passwords + u8Local_NumberOfUsers)))
				{
					u8USART_SendStringSynchronous("\n Welcome Back, ");
					u8USART_SendStringSynchronous(pchLocal_UserName);
					vUSART_SendByte('\n');
					u8Local_Flag = FALSE;
					break;
				}
			}
			u8Local_NumberOfUsers++;


		}
		if(u8Local_Flag)
		{
			u8USART_SendStringSynchronous("\n Please, Try Again.");
			u8USART_SendStringSynchronous("\n You got ");
			vUSART_SendNumberSynchronous(NUM_TRIALS - u8Local_Trial);
			u8USART_SendStringSynchronous(" left. \n");
			u8Local_Trial++;
			u8Local_NumberOfUsers = 0;
		}

	}

	if(u8Local_Trial < NUM_TRIALS)  //if user found it will continue with no problem
		u8Local_PermitFlag = TRUE;
	else
	{
		u8Local_PermitFlag = FALSE;          //if user not registered, buzzer will start & will restart the system after 2 seconds
		u8USART_SendStringSynchronous("\n Thief.");
		vBuzzer_ON();
		vWDT_Enable();
		vWDT_Sleep(TIMEOUT_2100ms);
	}

	while(1)
	{
		if(u8Local_MainMenuFlag && u8Local_PermitFlag)      //Main Menu
		{
			u8USART_SendStringSynchronous("\n How can i help you? \n");
			u8USART_SendStringSynchronous("\n 1: the Door \n");
			u8USART_SendStringSynchronous("\n 2: the Lighting \n");
			u8USART_SendStringSynchronous("\n 3: the Fan \n");
			u8USART_SendStringSynchronous("\n 4: Play Music \n");

			vUSART_RecieveByte(&u8Local_MenuOption);
		}

		switch(u8Local_MenuOption)
		{
		case '1': u8Local_MainMenuFlag = FALSE;
		u8Option = 0;
		u8USART_SendStringSynchronous("\n 1: Open Door \n");
		u8USART_SendStringSynchronous("\n 2: Close Door \n");
		u8USART_SendStringSynchronous("\n 3: Main Menu \n");
		vUSART_RecieveByte(&u8Option);
		if(u8Option > '0' && u8Option < '3') /*check if you want main menu or continue with the Door options*/
		{
			TheDoor();
		}else if (u8Option == '3')
		{
			u8Local_MainMenuFlag = TRUE;
		}
		break;

		case '2': u8Local_MainMenuFlag = FALSE;
		u8Option = 0;
		u8USART_SendStringSynchronous("\n 1: Open Lighting \n");
		u8USART_SendStringSynchronous("\n 2: Close Lighting \n");
		u8USART_SendStringSynchronous("\n 3: Adjust Lighting Auto \n");
		u8USART_SendStringSynchronous("\n 4: Main Menu \n");

		vUSART_RecieveByte(&u8Option);
		if(u8Option > '0' && u8Option < '4')    /*check if you want main menu or continue with the Lighting options*/
		{
			u8LightingFlag = TRUE;
			TheLighting();
		}else if (u8Option == '4')
		{
			u8Local_MainMenuFlag = TRUE;
		}
		break;

		case '3': u8Local_MainMenuFlag = FALSE;
		u8Option = 0;
		u8USART_SendStringSynchronous("\n 1: Open Fan \n");
		u8USART_SendStringSynchronous("\n 2: Close Fan \n");
		u8USART_SendStringSynchronous("\n 3: Adjust Fan Auto \n");
		u8USART_SendStringSynchronous("\n 4: Main Menu \n");
		vUSART_RecieveByte(&u8Option);
		if(u8Option > '0' && u8Option < '4')   /*check if you want main menu or continue with the Fan options*/
		{
			TheFan();
		}else if (u8Option == '4')
		{
			u8Local_MainMenuFlag = TRUE;
		}
		break;

		//play music case
		case '4': u8Local_MainMenuFlag = FALSE;
		u8Option = 0;
		u8USART_SendStringSynchronous("\n 1: Play Track 1 \n");
		u8USART_SendStringSynchronous("\n 2: Play Track 2 \n");
		u8USART_SendStringSynchronous("\n 3: Main Menu \n");
		vUSART_RecieveByte(&u8Option);
		if(u8Option > '0' && u8Option < '3')      /*check if you want main menu or continue with the Music options*/
		{
			TheMusic();
		}else if (u8Option == '3')
		{
			u8Local_MainMenuFlag = TRUE;
		}

		break;
		}

	}
}

void TheDoor(void)
{
	switch(u8Option)
	{
	//open door case
	case '1': if(u8DoorFlag == CLOSED)
	{
		u8ServoMotor_SetAngle(A_CHANNEL, 90);
		u8USART_SendStringSynchronous("\n The Door is now Open \n");
		u8DoorFlag = OPEN;
	}
	else if(u8DoorFlag == OPEN)
	{
		u8USART_SendStringSynchronous("\n The Door is already Open \n");
	}
	break;
	//close door case
	case '2': if(u8DoorFlag == OPEN)
	{
		u8ServoMotor_SetAngle(A_CHANNEL, 0);
		u8USART_SendStringSynchronous("\n The Door is now Closed \n");
		vServoMotor_Stop();
		u8DoorFlag = CLOSED;
	}
	else if(u8DoorFlag == CLOSED)
	{
		u8USART_SendStringSynchronous("\n The Door is already Closed \n");
	}
	break;
	}

}

void TheLighting(void)
{
	switch(u8Option)
	{
	//open lighting case
	case '1':
		while(u8LightingFlag)
		{
			u8USART_SendStringSynchronous("\n 1: Room 1 \n");
			u8USART_SendStringSynchronous("\n 2: Room 2 \n");
			u8USART_SendStringSynchronous("\n 3: Main Room \n");
			u8USART_SendStringSynchronous("\n 4: Return \n");
			vUSART_RecieveByte(&u8LightingOption);


			if(u8LightingOption == '1')
			{
				if(u8Room1 == OPEN)
					u8USART_SendStringSynchronous("\n Room 1 is already on \n");
				else if (u8Room1 == CLOSED)
				{
					u8LED_ON(DIO_PORTC,DIO_PIN5);
					u8USART_SendStringSynchronous("\n Room 1 is on \n");
					u8Room1 = OPEN;
				}
			}
			else if(u8LightingOption == '2')
			{
				if(u8Room2 == OPEN)
					u8USART_SendStringSynchronous("\n Room 2 is already on \n");
				else if (u8Room2 == CLOSED)
				{
					u8LED_ON(DIO_PORTC,DIO_PIN6);
					u8USART_SendStringSynchronous("\n Room 2 is on \n");
					u8Room2 = OPEN;
				}
			}
			else if(u8LightingOption == '3')
			{
				if(u8MainRoom == OPEN)
					u8USART_SendStringSynchronous("\n Main Room is already on \n");
				else if(u8MainRoom == CLOSED)
				{
					u8Timer2_SetCompareMatchMode(SET_AT_TOP_CLEAR_AT_COMPARE);
					vTimer2_SetCompMatchValue(255);
					u8USART_SendStringSynchronous("\n Main Room is on \n");
					u8MainRoom = OPEN;
				}
			}
			else if(u8LightingOption == '4')
			{
				u8LightingFlag = FALSE;
			}
		}
		break;
		//close lighting case
	case '2': while(u8LightingFlag)
	{
		u8USART_SendStringSynchronous("\n 1: Room 1 \n");
		u8USART_SendStringSynchronous("\n 2: Room 2 \n");
		u8USART_SendStringSynchronous("\n 3: Main Room \n");
		u8USART_SendStringSynchronous("\n 4: Return \n");
		vUSART_RecieveByte(&u8LightingOption);


		if(u8LightingOption == '1')
		{
			if(u8Room1 == CLOSED)
				u8USART_SendStringSynchronous("\n Room 1 is already off \n");
			else if (u8Room1 == OPEN)
			{
				u8LED_OFF(DIO_PORTC,DIO_PIN5);
				u8USART_SendStringSynchronous("\n Room 1 is off \n");
				u8Room1 = CLOSED;
			}
		}
		else if(u8LightingOption == '2')
		{
			if(u8Room2 == CLOSED)
				u8USART_SendStringSynchronous("\n Room 2 is already off \n");
			else if (u8Room2 == OPEN)
			{
				u8LED_OFF(DIO_PORTC,DIO_PIN6);
				u8USART_SendStringSynchronous("\n Room 2 is off \n");
				u8Room2 = CLOSED;
			}
		}
		else if(u8LightingOption == '3')
		{
			if(u8MainRoom == OPEN)
			{
				u8Timer2_SetCompareMatchMode(NORMAL_OPERATION);
				vTimer2_SetCompMatchValue(0);
				u8USART_SendStringSynchronous("\n Main Room is now on \n");
				u8MainRoom = CLOSED;
			}
			else if(u8MainRoom == CLOSED)
			{
				u8USART_SendStringSynchronous("\n Main Room is already off \n");
			}
		}
		else if(u8LightingOption == '4')
		{
			u8LightingFlag = FALSE;
		}
	}
	break;

	//adjust lighting case
	case '3': u8Timer2_SetCompareMatchMode(SET_AT_TOP_CLEAR_AT_COMPARE);
	u8USART_SendStringSynchronous("\n Main room lighting is now being adjusted. ");
	u8USART_SendStringSynchronous("\n press return to get back to lighting menu\n");
	u8USART_ReceiveBufferAsynchronous(Option,6,TheLightingFlag);
	while (u8LightingFlag)
	{
		u8ADC_StartSingleConversionSynch(ADC_SingleEndedChannel0,&u16ADC_Result);
		u8LDR_Value = (uint8_t)s32Map(0,1023,0,255,u16ADC_Result);
		vTimer2_SetCompMatchValue(u8LDR_Value);
	}
	u8MainRoom = OPEN;
	break;
	}
}

void TheLightingFlag(void)
{
	if(!StringCompare(Option, "return"))
	{
		u8LightingFlag = FALSE;
	}
	StringReset(Option);
}

void TheFan (void)
{
	switch(u8Option)
	{
	//open fan case
	case '1': if(u8u8FanFlag == CLOSED)
	{
		u8Timer0_SetCompareMatchMode(SET_AT_TOP_CLEAR_AT_COMPARE);
		vTimer0_SetCompMatchValue(255);
		u8USART_SendStringSynchronous("\n The Fan is now on \n");
		u8u8FanFlag = OPEN;
	}
	else if(u8u8FanFlag == OPEN)
	{
		u8USART_SendStringSynchronous("\n The Fan is already on \n");
	}
	break;

	//close fan case
	case '2': if(u8u8FanFlag == CLOSED)
	{
		u8USART_SendStringSynchronous("\n The Fan is already off \n");
	}
	else if(u8u8FanFlag == OPEN || u8Adjustu8FanFlag == OPEN)
	{
		vTimer0_SetCompMatchValue(0);
		u8Timer0_SetCompareMatchMode(NORMAL_OPERATION);
		u8USART_SendStringSynchronous("\n The Fan is now off \n");
		u8u8FanFlag = CLOSED;
		u8Adjustu8FanFlag = CLOSED;
	}
	break;

	//adjust fan case
	case '3':
		if(u8Adjustu8FanFlag == OPEN)
			u8USART_SendStringSynchronous("\n The Fan is already being adjusted \n");
		else
		{
			u8Timer0_SetCompareMatchMode(SET_AT_TOP_CLEAR_AT_COMPARE);
			u8USART_SendStringSynchronous("\n The Fan is now being adjusted. ");

			u8ADC_StartSingleConversionSynch(ADC_SingleEndedChannel1,&u16ADC_Result);
			u8Temperature_Value = u8TempSensor_GetValue(u16ADC_Result);
			u8Temp_Value = (uint8_t)s32Map(20,40,0,255,u8Temperature_Value);
			vTimer0_SetCompMatchValue(u8Temp_Value);

			u8Adjustu8FanFlag = OPEN;
			u8u8FanFlag = OPEN;
		}
		break;
	}
}

void TheMusic(void)
{
	/*Melodies to be played*/
	uint16_t u16Local_Melody[] = { F, A, B, PAUSE, F, A, B, PAUSE, F, A, B, PAUSE, PAUSE, B, PAUSE, B, G, E, PAUSE, PAUSE, D, E, G, E, PAUSE, F, A, B, PAUSE, F, A, B, F, A, B, PAUSE, B, PAUSE, B, G, PAUSE, B, G, D, E, PAUSE, D, E, F, PAUSE, G, A, B, PAUSE, B, E, PAUSE, F, G, A, PAUSE, B, A, B, PAUSE, D, E, F, PAUSE, G, END };
	uint16_t u16Local_Twinkle[] = { G, G, D, D, E, E, D, PAUSE, C, C, B, B, A, A, G, PAUSE, D, D, C, C, B, B, A, PAUSE, D, D, C, C, B, B, A, PAUSE, G, G, D, D, E, E, D, PAUSE, C, C, B, B, A, A, G, END };
	/***********************/

	uint8_t u8Local_BuzzerCounter = 0;
	switch(u8Option)
	{
	//case Track 1
	case '1':
		u8MusicFlag = TRUE;
		u8USART_SendStringSynchronous("\n Track 1 is now playing. ");
		u8USART_SendStringSynchronous("\n Press stop to stop music. ");
		u8USART_ReceiveBufferAsynchronous(Option,4,Theu8MusicFlag);
		while(u8MusicFlag)
		{
			vBuzzer_PlayTone(200,u16Local_Melody[u8Local_BuzzerCounter]);
			u8Local_BuzzerCounter++;
			if(u16Local_Melody[u8Local_BuzzerCounter] == END)
				u8Local_BuzzerCounter = 0;
		}
		vBuzzer_Stop();
		break;
		//case Track 2
	case '2':
		u8MusicFlag = TRUE;
		u8USART_SendStringSynchronous("\n Track 2 is now playing. ");
		u8USART_SendStringSynchronous("\n Press stop to stop music. ");
		u8USART_ReceiveBufferAsynchronous(Option,4,Theu8MusicFlag);
		while(u8MusicFlag)
		{
			vBuzzer_PlayTone(500,u16Local_Twinkle[u8Local_BuzzerCounter]);
			u8Local_BuzzerCounter++;
			if(u16Local_Twinkle[u8Local_BuzzerCounter] == END)
				u8Local_BuzzerCounter = 0;
		}
		vBuzzer_Stop();
		break;
	}
}
void Theu8MusicFlag(void)
{
	if(!StringCompare(Option, "stop"))
	{
		u8MusicFlag = FALSE;
	}
	StringReset(Option);

}
