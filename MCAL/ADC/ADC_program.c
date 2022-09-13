/*
 * ADC_program.c
 *
 * 		Name: Mohamed Hussein
 * 		Layer: MCAL
 * 		Version: V1.0 - 09/12/2021
 * 		Driver: ADC - Analog to Digital Converter
 */
#include "../../Library/BIT_MATH.h"
#include "../../Library/STD_TYPE.h"
#include "../../Library/Interrupts.h"

#include "ADC_private.h"
#include "ADC_configuration.h"
#include "ADC_registers.h"
#include "ADC_interface.h"

/*Global flag to indicate for the ADC busy state*/
static uint8_t u8ADC_State = IDLE;
/*Global pointer to carry the conversion result in the asynchronous execution*/
static uint16_t* pu16ADC_ConversionResult = NULL;
/*Global pointer to function to carry the notification function called by ISR*/
static void (*pvADC_NotificationFunction)(void) = NULL;
/*Global variable to carry the how many conversions needed in chain conversion*/
static uint8_t u8ADC_NumberOfChainConversions = 0;
/*Global pointer to carry the number of channels in chain conversion*/
static uint8_t* pu8ADC_ChainNeededChannels = NULL;
/*Global flag to indicate for the chain conversion is working*/
static uint8_t u8ADC_ChainConversionFlag = NOT_WORKING;
/*Global counter for chain conversion*/
static uint8_t u8ADC_ChainCounter = 0;

void vADC_Init(void)
{
	/*Reference Voltage*/
#if ADC_RefVolt == AREF
	CLR_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
#elif ADC_RefVolt == AVCC
	SET_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
#elif ADC_RefVolt == Internal_2560mv
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
#else
#error "Wrong Choice, Choose Correctly"
#endif

	/*ADC Adjustment*/
#if ADC_Adjust == ADC_RightAdjust
	CLR_BIT(ADMUX,ADLAR);
#elif ADC_Adjust == ADC_LeftAdjust
	SET_BIT(ADMUX,ADLAR);
#else
#error "Wrong Choice, Choose Correctly"
#endif

	/*Enable or Disable ADC Auto Trigger*/
#if ADC_AutoTrigger == ADC_AutoTriggerDisable
	CLR_BIT(ADCSRA,ADATE);
#elif ADC_AutoTrigger == ADC_AutoTriggerEnable
	SET_BIT(ADCSRA,ADATE);
#else
#error "Wrong Choice, Choose Correctly"
#endif

	/*Enable or Disable ADC Interrupt*/
#if ADC_Interrupt == ADC_InterruptDisable
	CLR_BIT(ADCSRA,ADIE);
#elif ADC_Interrupt == ADC_InterruptEnable
	SET_BIT(ADCSRA,ADIE);
#else
#error "Wrong Choice, Choose Correctly"
#endif

	/* ADC Prescaler set, First clear the 3 LSBs & keep the 5 MSBs the same*/
	ADCSRA &= ADC_Prescaler_Mask;
	ADCSRA |= ADC_Prescaler;

	/* ADC Enable Peripheral */
	SET_BIT(ADCSRA,ADEN);

}

uint8_t u8ADC_StartSingleConversionSynch(uint8_t u8Copy_Channel, uint16_t* u16Copy_Reading)
{
	uint8_t u8Local_ErrorState = OK;
	uint32_t u32local_Counter = 0;

	if(u16Copy_Reading != NULL)
	{
		if(u8ADC_State == IDLE)
		{
			/*ADC busy now*/
			u8ADC_State = BUSY;

			/* clear MUX bits in the ADMUX register */
			ADMUX &= 0xE0;

			/* Set required channel into the MUX bits in ADMUX register */
			ADMUX |= u8Copy_Channel;

			/* ADC Start Conversion */
			SET_BIT(ADCSRA,ADSC);

			/* Busy wait polling till conversion complete
			 * using also Timeout to make sure ADC conversion time not take too long or exit
			 * */
			while((GET_BIT(ADCSRA,ADIF) == 0) && (u32local_Counter != ADC_u32TIMEOUT)) {
				u32local_Counter++;
			}

			if(u32local_Counter == ADC_u32TIMEOUT) /*Loop is broken because of Timeout*/
				u8Local_ErrorState = TIMEOUT_STATE;
			else
			{
				/* Clear the ADC complete conversion Flag */
				SET_BIT(ADCSRA,ADIF);

				/* Read the value of the ADC Registers */
				/*ADC Adjustment*/
#if ADC_Adjust == ADC_RightAdjust
#if ADC_Result == EightBits
				*u16Copy_Reading = ADC_DATA>>2;
#elif ADC_Result == TenBits
				*u16Copy_Reading = ADC_DATA;
#else
#error "Wrong Choice, Choose Correctly"
#endif  /*ADC Result*/
#elif ADC_Adjust == ADC_LeftAdjust
#if ADC_Result == EightBits
				*u16Copy_Reading = ADCH;
#elif ADC_Result == TenBits
				*u16Copy_Reading = ADC_DATA>>6;
#else
#error "Wrong Choice, Choose Correctly"
#endif  /*ADC Result*/
#else
#error "Wrong Choice, Choose Correctly"
#endif

				/*ADC is now IDLE*/
				u8ADC_State = IDLE;
			}
		}else
			u8Local_ErrorState = BUSY;
	}
	else
		u8Local_ErrorState = NULLPOINTER;

	return u8Local_ErrorState;
}

uint8_t u8ADC_StartSingleConversionAsynch(uint8_t u8Copy_Channel, uint16_t* pu16Copy_Value, void (*pvCopy_NotificationFunction) (void))
{
	uint8_t u8Local_ErrorState = OK;

	if(pu16Copy_Value == NULL || pvCopy_NotificationFunction == NULL)
	{
		u8Local_ErrorState = NULLPOINTER;
	}
	else
	{
		if(u8ADC_State == IDLE)
		{
			/*ADC busy now*/
			u8ADC_State = BUSY;
			/*Initialize the global result pointer*/
			pu16ADC_ConversionResult = pu16Copy_Value;
			/*Initialize the global notification function pointer*/
			pvADC_NotificationFunction = pvCopy_NotificationFunction;

			/* clear MUX bits in the ADMUX register */
			ADMUX &= 0xE0;

			/* Set required channel into the MUX bits in ADMUX register */
			ADMUX |= u8Copy_Channel;
			/* ADC Start Conversion */
			SET_BIT(ADCSRA,ADSC);
			/*Enable ADC Interrupt*/
			SET_BIT(ADCSRA,ADIE);
		}
		else
		{
			u8Local_ErrorState = BUSY;
		}
	}

	return u8Local_ErrorState;
}

uint8_t u8ADC_StartChainConversionSynch(ST_ChainSynch_t *stCopy_Element)
{
	uint8_t u8Local_ErrorState = OK;
	uint32_t u32local_Counter = 0;

	if(stCopy_Element == NULL || stCopy_Element->ADC_Channels == NULL || stCopy_Element->ADC_Results == NULL)
		u8Local_ErrorState = NULLPOINTER;
	else
	{
		if(u8ADC_State == IDLE)
		{
			/*zero the counter*/
			u8ADC_ChainCounter = 0;
			/*ADC busy now*/
			u8ADC_State = BUSY;

			/*loop to get the conversion for all channels needed*/
			while(u8ADC_ChainCounter <= (stCopy_Element->ADC_NumberOfConversions))
			{
				/* clear MUX bits in the ADMUX register */
				ADMUX &= 0xE0;

				/* Set required channel into the MUX bits in ADMUX register */
				ADMUX |= stCopy_Element->ADC_Channels[u8ADC_ChainCounter];

				/* ADC Start Conversion */
				SET_BIT(ADCSRA,ADSC);

				/* Busy wait polling till conversion complete
				 * using also Timeout to make sure ADC conversion time not take too long or exit
				 * */
				while((GET_BIT(ADCSRA,ADIF) == 0) && (u32local_Counter != ADC_u32TIMEOUT)) {
					u32local_Counter++;
				}

				if(u32local_Counter == ADC_u32TIMEOUT) /*Loop is broken because of Timeout*/
					u8Local_ErrorState = TIMEOUT_STATE;
				else
				{
					/* Clear the ADC complete conversion Flag */
					SET_BIT(ADCSRA,ADIF);

					/* Read the value of the ADC Registers */
					/*ADC Adjustment*/
#if ADC_Adjust == ADC_RightAdjust
#if ADC_Result == EightBits
					stCopy_Element->ADC_Results[u8ADC_ChainCounter] = ADC_DATA>>2;
#elif ADC_Result == TenBits
					stCopy_Element->ADC_Results[u8ADC_ChainCounter] = ADC_DATA;
#else
#error "Wrong Choice, Choose Correctly"
#endif  /*ADC Result*/
#elif ADC_Adjust == ADC_LeftAdjust
#if ADC_Result == EightBits
					stCopy_Element->ADC_Results[u8ADC_ChainCounter] = ADCH;
#elif ADC_Result == TenBits
					stCopy_Element->ADC_Results[u8ADC_ChainCounter] = ADC_DATA>>6;
#else
#error "Wrong Choice, Choose Correctly"
#endif  /*ADC Result*/
#else
#error "Wrong Choice, Choose Correctly"
#endif

				}
				/*increment the counter */
				u8ADC_ChainCounter++;
			}

			/*ADC is now IDLE*/
			u8ADC_State = IDLE;
		}
		else
			u8Local_ErrorState = BUSY;
	}
	return u8Local_ErrorState;
}
uint8_t u8ADC_StartChainConversionAsynch(ST_ChainAsynch_t *stCopy_Element)
{
	uint8_t u8Local_ErrorState = OK;


	if(stCopy_Element == NULL || stCopy_Element->ADC_Channels == NULL || stCopy_Element->ADC_Results == NULL || stCopy_Element->pvNotificationFunc == NULL)
		u8Local_ErrorState = NULLPOINTER;
	else
	{
		if(u8ADC_State == IDLE)
		{
			/*Chain conversion now starts*/
			u8ADC_ChainConversionFlag = WORKING;
			/*ADC busy now*/
			u8ADC_State = BUSY;
			/*Initialize the global Number Of Chain Conversions variable*/
			u8ADC_NumberOfChainConversions = stCopy_Element->ADC_NumberOfConversions;
			/*Initialize the global result pointer*/
			pu16ADC_ConversionResult = stCopy_Element->ADC_Results;
			/*Initialize the global Chain Needed Channels pointer*/
			pu8ADC_ChainNeededChannels = stCopy_Element->ADC_Channels;
			/*Initialize the global notification function pointer*/
			pvADC_NotificationFunction = stCopy_Element->pvNotificationFunc;
			/* clear MUX bits in the ADMUX register */
			ADMUX &= 0xE0;

			/* Set required channel into the MUX bits in ADMUX register */
			ADMUX |= stCopy_Element->ADC_Channels[u8ADC_ChainCounter];
			/* ADC Start Conversion */
			SET_BIT(ADCSRA,ADSC);
			/*Enable ADC Interrupt*/
			SET_BIT(ADCSRA,ADIE);
		}
		else
			u8Local_ErrorState = BUSY;
	}

	return u8Local_ErrorState;
}

/*function takes digital value as input & convert it to analog value represented in mV in range 0 - 5V*/
uint16_t u16ADC_ConvertDigitalToAnalog (uint16_t u16Copy_Value)
{
	/*return mV */
	uint16_t u16Local_Value = 0;

	/*type casting u16Copy_Value to calculate precisely the mV*/
	u16Local_Value = (uint16_t)(((uint32_t)u16Copy_Value * ADC_Reference) / ADC_ResolutionBit);
	return u16Local_Value;
}

/******************************************************************************
 * !comment  :  ISR Function ADC.        					                  *
 ******************************************************************************/
ISR(ADC)
{
	/*for single Asynch conversion*/
	if(u8ADC_ChainConversionFlag == NOT_WORKING)
	{
		/* Read the value of the ADC Registers */
		/*ADC Adjustment*/
#if ADC_Adjust == ADC_RightAdjust
#if ADC_Result == EightBits
		*pu16ADC_ConversionResult = ADC_DATA>>2;
#elif ADC_Result == TenBits
		*pu16ADC_ConversionResult = ADC_DATA;
#else
#error "Wrong Choice, Choose Correctly"
#endif  /*ADC Result*/
#elif ADC_Adjust == ADC_LeftAdjust
#if ADC_Result == EightBits
		*pu16ADC_ConversionResult = ADCH;
#elif ADC_Result == TenBits
		*pu16ADC_ConversionResult = ADC_DATA>>6;
#else
#error "Wrong Choice, Choose Correctly"
#endif  /*ADC Result*/
#else
#error "Wrong Choice, Choose Correctly"
#endif

		/*ADC is now IDLE to be used*/
		u8ADC_State = IDLE;
		/*Invoke the callback notification function*/
		pvADC_NotificationFunction();

		/*Disable the ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA,ADIE);
	}
	else if(u8ADC_ChainConversionFlag == WORKING) /*for chain conversion*/
	{

		/* Read the value of the ADC Registers */
		/*ADC Adjustment*/
#if ADC_Adjust == ADC_RightAdjust
#if ADC_Result == EightBits
		pu16ADC_ConversionResult[u8ADC_ChainCounter] = ADC_DATA>>2;
#elif ADC_Result == TenBits
		pu16ADC_ConversionResult[u8ADC_ChainCounter] = ADC_DATA;
#else
#error "Wrong Choice, Choose Correctly"
#endif  /*ADC Result*/
#elif ADC_Adjust == ADC_LeftAdjust
#if ADC_Result == EightBits
		pu16ADC_ConversionResult[u8ADC_ChainCounter] = ADCH;
#elif ADC_Result == TenBits
		pu16ADC_ConversionResult[u8ADC_ChainCounter] = ADC_DATA>>6;
#else
#error "Wrong Choice, Choose Correctly"
#endif  /*ADC Result*/
#else
#error "Wrong Choice, Choose Correctly"
#endif

		/*increment the counter for next chain conversion member*/
		u8ADC_ChainCounter++;

		if(u8ADC_ChainCounter == u8ADC_NumberOfChainConversions)
		{
			/*ADC is now IDLE to be used*/
			u8ADC_State = IDLE;
			/*Chain conversion is now not working*/
			u8ADC_ChainConversionFlag = NOT_WORKING;
			/*Invoke the callback notification function*/
			pvADC_NotificationFunction();
			/*Disable the ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA,ADIE);
			/*reset the counter*/
			u8ADC_ChainCounter = 0;
		}
		else
		{
			/* clear MUX bits in the ADMUX register */
			ADMUX &= 0xE0;

			/* Set required channel into the MUX bits in ADMUX register */
			ADMUX |= pu8ADC_ChainNeededChannels[u8ADC_ChainCounter];
			/* ADC Start Conversion */
			SET_BIT(ADCSRA,ADSC);
		}
	}

}
