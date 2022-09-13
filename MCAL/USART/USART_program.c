/*
 * USART_program.c
 *
 * 		Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: USART
 */
#include "../../Library/STD_TYPE.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/Interrupts.h"
#include "../../Library/User_Functions.h"
#include "USART_private.h"
#include "USART_configuration.h"
#include "USART_registers.h"
#include "USART_interface.h"

//Global pointer to character to hold the transmitted string
static char* pu8USART_TransmitString = NULL;
//Global pointer to character to hold the received string
static char* pu8USART_ReceiveString = NULL;
//Global pointer to function to hold the notification function for transmission completed
static void (*pvNotificationFunction)(void) = NULL;
/*global counter*/
static uint16_t u16USART_Counter = 0;
/*global buffer size*/
static uint8_t u8USART_BufferSize = 0;


void vUSART_Init(void)
{
	//Local variable to hold the UCSRC register value
	uint8_t u8Local_UCSRCvalue = 0;

	//Local variable to hold the UBBR register value
	uint16_t u16Local_UBBRvalue = 0;

	//Local variable to hold the UBBRH register value
	uint8_t u8Local_UBBRHvalue = 0;

	//Select the UCSRC register
	SET_BIT(u8Local_UCSRCvalue,URSEL);

	//Mode Selection
#if   MODE_SELECT == SYNCHRONOUS
	SET_BIT(u8Local_UCSRCvalue,UMSEL);

#elif MODE_SELECT == ASYNCHRONOUS
	CLR_BIT(u8Local_UCSRCvalue,UMSEL);

#else
#error "Wrong Mode Select Configuration"

#endif

	//Parity Mode Selection
#if   PARITY_MODE == DISABLED
	CLR_BIT(u8Local_UCSRCvalue, UPM0);
	CLR_BIT(u8Local_UCSRCvalue, UPM1);

#elif PARITY_MODE == EVEN_PARITY
	CLR_BIT(u8Local_UCSRCvalue, UPM0);
	SET_BIT(u8Local_UCSRCvalue, UPM1);

#elif PARITY_MODE == ODD_PARITY
	SET_BIT(u8Local_UCSRCvalue,UPM0);
	SET_BIT(u8Local_UCSRCvalue,UPM1);

#else
#error "Wrong Parity Mode Configuration"

#endif

	//Stop Bits Selection
#if   STOP_BITS == ONE_BIT
	CLR_BIT(u8Local_UCSRCvalue,USBS);

#elif STOP_BITS == TWO_BITS
	SET_BIT(u8Local_UCSRCvalue,USBS);

#else
#error "Wrong Stop Bits Configuration"

#endif

	//Character size : 8 bits
#if   CHARACTER_SIZE == FIVE_BITS
	CLR_BIT(u8Local_UCSRCvalue,UCSZ0);
	CLR_BIT(u8Local_UCSRCvalue,UCSZ1);
	CLR_BIT(UCSRB,UCSZ2);

#elif CHARACTER_SIZE == SIX_BITS
	SET_BIT(u8Local_UCSRCvalue,UCSZ0);
	CLR_BIT(u8Local_UCSRCvalue,UCSZ1);
	CLR_BIT(UCSRB,UCSZ2);

#elif CHARACTER_SIZE == SEVEN_BITS
	CLR_BIT(u8Local_UCSRCvalue,UCSZ0);
	SET_BIT(u8Local_UCSRCvalue,UCSZ1);
	CLR_BIT(UCSRB,UCSZ2);

#elif CHARACTER_SIZE == EIGHT_BITS
	SET_BIT(u8Local_UCSRCvalue,UCSZ0);
	SET_BIT(u8Local_UCSRCvalue,UCSZ1);
	CLR_BIT(UCSRB,UCSZ2);

#elif CHARACTER_SIZE == NINE_BITS
	SET_BIT(u8Local_UCSRCvalue,UCSZ0);
	SET_BIT(u8Local_UCSRCvalue,UCSZ1);
	SET_BIT(UCSRB,UCSZ2);

#else
#error "Wrong Bit Size Configuration"

#endif

	//Clock Polarity Selection (Synchronous mode only)
#if MODE_SELECT == SYNCHRONOUS

#if   CLOCK_POLARITY == RISING_EDGE
	CLR_BIT(u8Local_UCSRCvalue,UCPOL);

#elif CLOCK_POLARITY == FALLING_EDGE
	SET_BIT(u8Local_UCSRCvalue,UCPOL);

#else
#error "Wrong Clock Polarity Configuration"

#endif

#endif

	//Assigning the UCSRC value in one operation
	UCSRC = u8Local_UCSRCvalue;

#if MODE_SELECT == ASYNCHRONOUS

#if DOUBLE_TRANSMISSION_SPEED == ENABLED
	SET_BIT(UCSRA,U2X);
	u16Local_UBBRvalue = (uint16_t) ( (MC_Frequency / (uint32_t) (8UL * BAUD_RATE)) - 1);

#elif DOUBLE_TRANSMISSION_SPEED == DISABLED
	CLR_BIT(UCSRA,U2X);
	u16Local_UBBRvalue = (uint16_t) ( (MC_Frequency / (uint32_t) (16UL * BAUD_RATE)) - 1);

#else
#error "Wrong double transmission speed configuration"

#endif

#elif MODE_SELECT == SYNCHRONOUS
	u16Local_UBBRvalue = (uint16_t) ( (MC_Frequency / (uint32_t) (2UL * BAUD_RATE)) - 1);

#endif

	//Selecting the UBRRH Register
	CLR_BIT(u8Local_UBBRHvalue,URSEL);

	u8Local_UBBRHvalue = u16Local_UBBRvalue >> 8;

	//Assigning the UBRRH value in one operation
	UBRRH = u8Local_UBBRHvalue;
	UBRRL = (uint8_t) u16Local_UBBRvalue;

	//baud rate setting to 9600 bps
	//UBRRL = 63;

	//Receiver Enable
#if RECEIVER_STATE == ENABLED
	SET_BIT(UCSRB,RXEN);

#elif RECEIVER_STATE == DISABLED
	CLR_BIT(UCSRB,RXEN);

#else
#error "Wrong Receiver State Configuration"

#endif

	//Transmitter enable
#if TRANSMITTER_STATE == ENABLED
	SET_BIT(UCSRB,TXEN);

#elif TRANSMITTER_STATE == DISABLED
	CLR_BIT(UCSRB,TXEN);

#else
#error "Wrong Transmitter State Configuration"

#endif

}

uint8_t vUSART_SendByte(uint8_t u8Copy_Byte)
{
	uint8_t u8Local_ErrorState = OK;
	uint32_t u32Local_TimeoutCounter = 0;

	//wait until the transmitter buffer is empty
	while(GET_BIT(UCSRA,UDRE) == 0 && u32Local_TimeoutCounter != USART_u32TIMEOUT)
	{
		u32Local_TimeoutCounter++;
	}

	if(u32Local_TimeoutCounter == USART_u32TIMEOUT)   /*check if the loop is broken because of timeout or not*/
	{
		u8Local_ErrorState = TIMEOUT_STATE;
	}
	else
	{
		UDR = u8Copy_Byte;      /*write data into UDR register to send it*/
	}

	return u8Local_ErrorState;
}
uint8_t vUSART_RecieveByte(uint8_t* pu8Copy_Byte)
{
	uint8_t u8Local_ErrorState = OK;
	uint32_t u32Local_TimeoutCounter = 0;

	if(pu8Copy_Byte == NULL)
		u8Local_ErrorState = NULLPOINTER;
	else
	{
		//wait until the receive complete event happens
		while(GET_BIT(UCSRA,RXC) == 0 && u32Local_TimeoutCounter != USART_u32TIMEOUT)
		{
			u32Local_TimeoutCounter++;
		}

		if(u32Local_TimeoutCounter == USART_u32TIMEOUT)   /*check if the loop is broken because of timeout or not*/
		{
			u8Local_ErrorState = TIMEOUT_STATE;
		}
		else
		{
			*pu8Copy_Byte = UDR;       /*read data from UDR register*/
		}
	}

	return u8Local_ErrorState;
}

uint8_t u8USART_SendStringSynchronous(const char * pu8Copy_string)
{
	uint8_t u8Local_ErrorState = OK;
	uint32_t u32Local_TimeoutCounter = 0;
	uint16_t u16Local_StringCounter = 0;

	if(pu8Copy_string == NULL)
		u8Local_ErrorState = NULLPOINTER;
	else
	{
		while(pu8Copy_string[u16Local_StringCounter] != '\0')
		{
			//Polling until UDRE (data register empty) flag is Set or timeout is reached
			while(GET_BIT(UCSRA,UDRE) == 0 && u32Local_TimeoutCounter != USART_u32TIMEOUT)
			{
				u32Local_TimeoutCounter++;
			}

			if(u32Local_TimeoutCounter == USART_u32TIMEOUT)  /*check if the loop is broken because of timeout or not*/
			{
				u8Local_ErrorState = TIMEOUT_STATE;
			}
			else
			{
				UDR = pu8Copy_string[u16Local_StringCounter];     /*write data into UDR register to send it*/
				u16Local_StringCounter++;
				u32Local_TimeoutCounter = 0;
			}
		}
	}

	return u8Local_ErrorState;
}

uint8_t u8USART_SendStringAsynchronous(const char * pu8Copy_string, void(*Copy_pvNotificationFunction)(void))
{
	uint8_t u8Local_ErrorState = OK;

	if(pu8Copy_string == NULL || Copy_pvNotificationFunction == NULL)
		u8Local_ErrorState = NULLPOINTER;
	else
	{
		/*set global pointer to string that we want to send*/
		pu8USART_TransmitString = pu8Copy_string;
		/*set notification for the transmission completion*/
		pvNotificationFunction = Copy_pvNotificationFunction;
		/*enable the data register empty interrupt*/
		SET_BIT(UCSRB,UDRIE);
	}

	return u8Local_ErrorState;
}

uint8_t u8USART_ReceiveBufferSynchronous(char * pu8Copy_Data, uint8_t u8Copy_BufferSize)
{
	uint8_t u8Local_ErrorState = OK;
	uint32_t u32Local_TimeoutCounter = 0;
	uint8_t u8Local_BufferCounter = 0;

	if(pu8Copy_Data == NULL)
		u8Local_ErrorState = NULLPOINTER;
	else
	{
		while(u8Local_BufferCounter < u8Copy_BufferSize)
		{
			//wait until the receive complete event happens
			while(GET_BIT(UCSRA,RXC) == 0 && u32Local_TimeoutCounter != USART_u32TIMEOUT)
			{
				u32Local_TimeoutCounter++;
			}

			if(u32Local_TimeoutCounter == USART_u32TIMEOUT)   /*check if the loop is broken because of timeout or not*/
			{
				u8Local_ErrorState = TIMEOUT_STATE;
				break;
			}
			else
			{
				pu8Copy_Data[u8Local_BufferCounter] = UDR;   /*read data from UDR register*/
				u8Local_BufferCounter++;
				u32Local_TimeoutCounter = 0;
			}
		}
	}

	return u8Local_ErrorState;
}

uint8_t u8USART_ReceiveBufferAsynchronous(char * pu8Copy_Data, uint8_t u8Copy_BufferSize, void(*Copy_pvNotificationFunction)(void))
{
	uint8_t u8Local_ErrorState = OK;

	if(pu8Copy_Data == NULL || Copy_pvNotificationFunction == NULL)
		u8Local_ErrorState = NULLPOINTER;
	else
	{
		/*set global pointer to string that we want to receive*/
		pu8USART_ReceiveString = pu8Copy_Data;
		/*set notification for the transmission completion*/
		pvNotificationFunction = Copy_pvNotificationFunction;
		/*set the buffer size*/
		u8USART_BufferSize = u8Copy_BufferSize;
		//Enable the Receive Complete interrupt
		SET_BIT(UCSRB,RXCIE);
	}

	return u8Local_ErrorState;
}

uint8_t u8USART_ReceiveStringSynchronous(char * pu8Copy_string)
{
	uint8_t u8Local_ErrorState = OK;
	uint32_t u32Local_TimeoutCounter = 0;
	uint8_t u8Local_StringCounter = 0;
	uint16_t u16Local_StringSize = 1000;

	if(pu8Copy_string == NULL)
		u8Local_ErrorState = NULLPOINTER;
	else
	{
		while(u8Local_StringCounter < u16Local_StringSize)
		{
			//wait until the receive complete event happens
			while(GET_BIT(UCSRA,RXC) == 0 && u32Local_TimeoutCounter != USART_u32TIMEOUT)
			{
				u32Local_TimeoutCounter++;
			}

			if(u32Local_TimeoutCounter == USART_u32TIMEOUT)   /*check if the loop is broken because of timeout or not*/
			{
				u8Local_ErrorState = TIMEOUT_STATE;
				break;
			}
			else
			{
				pu8Copy_string[u8Local_StringCounter] = UDR;   /*read data from UDR register*/
				if(pu8Copy_string[u8Local_StringCounter] == 9) //check if entered character is horizontal tab or not to exit the function
				{
					pu8Copy_string[u8Local_StringCounter] = '\0';
					break;
				}
				else
				{
					u8Local_StringCounter++;
					u32Local_TimeoutCounter = 0;
				}
			}
		}
	}

	return u8Local_ErrorState;
}
void vUSART_SendNumberSynchronous(int32_t s32Copy_Number)
{
	/* array to hold the converted number to string*/
	char pu8Local_Number[11];
	ConvertToString(pu8Local_Number,s32Copy_Number);
	u8USART_SendStringSynchronous(pu8Local_Number);
}

/******************************************************************************
 * !comment  :  ISR Function EXI.  							 			      *
 ******************************************************************************/
//USART, Receive Complete
ISR(USART_RXC)
{
	/*receive the current byte*/
	pu8USART_ReceiveString[u16USART_Counter] = UDR;
	//Increment the counter
	u16USART_Counter++;
	/*check if it reached the last element in the string array*/
	if(u16USART_Counter >= u8USART_BufferSize)
	{
		/*Reset the counter*/
		u16USART_Counter = 0;
		/*disable the interrupt*/
		CLR_BIT(UCSRB,RXCIE);
		/*call the notification function*/
		pvNotificationFunction();
	}
}

//USART Data Register Empty
ISR(USART_UDRE)
{
	/*send the current byte*/
	UDR = pu8USART_TransmitString[u16USART_Counter];
	//Increment the counter
	u16USART_Counter++;

	/*check if it reached the last element in the string array*/
	if(pu8USART_TransmitString[u16USART_Counter] == '\0')
	{
		/*Reset the counter*/
		u16USART_Counter = 0;
		/*disable the interrupt*/
		CLR_BIT(UCSRB,UDRIE);
		/*call the notification function*/
		pvNotificationFunction();
	}
}

//USART, Transmit Complete
ISR(USART_TXC)
{

}
