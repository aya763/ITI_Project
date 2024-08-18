/*
 * LED_program.c
 *
 *  Created on: Jul 25, 2024
 *      Author: aya
 */

#include "../../LIB/STD_Types.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "LED_private.h"
#include "LED_config.h"




ES_t LED_enuInit(LED_t * copy_pstrLedConfig)
{
	ES_t Local_enuErrorState=ES_NOK;
	if(copy_pstrLedConfig !=NULL)
	{
		u8 Local_enuIterator=0;
		for(Local_enuIterator=0;Local_enuIterator<LED_NUM;Local_enuIterator++)
		{
			Local_enuErrorState=DIO_enuSetPinDirection(copy_pstrLedConfig[Local_enuIterator].LED_u8PortID,copy_pstrLedConfig[Local_enuIterator].LED_u8PinID,DIO_u8OUTPUT);
			if(copy_pstrLedConfig[Local_enuIterator].LED_u8Connection==LED_SINK)
			{
				if(copy_pstrLedConfig[Local_enuIterator].LED_u8InitState==LED_ON)
				{
					Local_enuErrorState=DIO_enuSetPinValue(copy_pstrLedConfig[Local_enuIterator].LED_u8PortID,copy_pstrLedConfig[Local_enuIterator].LED_u8PinID,DIO_u8LOW);
				}
				else if(copy_pstrLedConfig[Local_enuIterator].LED_u8InitState==LED_OFF)
				{
					Local_enuErrorState=DIO_enuSetPinValue(copy_pstrLedConfig[Local_enuIterator].LED_u8PortID,copy_pstrLedConfig[Local_enuIterator].LED_u8PinID,DIO_u8HIGH);
				}
				else
				{
					return ES_OUT_OF_RANGE;
				}
			}
			else if(copy_pstrLedConfig[Local_enuIterator].LED_u8Connection==LED_SOURCE)
			{
				if(copy_pstrLedConfig[Local_enuIterator].LED_u8InitState==LED_ON)
				{
					Local_enuErrorState=DIO_enuSetPinValue(copy_pstrLedConfig[Local_enuIterator].LED_u8PortID,copy_pstrLedConfig[Local_enuIterator].LED_u8PinID,DIO_u8HIGH);
				}
				else if(copy_pstrLedConfig[Local_enuIterator].LED_u8InitState==LED_OFF)
				{
					Local_enuErrorState=DIO_enuSetPinValue(copy_pstrLedConfig[Local_enuIterator].LED_u8PortID,copy_pstrLedConfig[Local_enuIterator].LED_u8PinID,DIO_u8LOW);
				}
				else
				{
					return ES_OUT_OF_RANGE;
				}
			}
			else
			{
				return ES_OUT_OF_RANGE;
			}
		}
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t LED_enuTurnON(LED_t * copy_pstrLedID)
{
	ES_t Local_enuErrorState=ES_NOK;
	if(copy_pstrLedID!=NULL)
	{
		if(copy_pstrLedID->LED_u8Connection==LED_SINK)
		{
			Local_enuErrorState=DIO_enuSetPinValue(copy_pstrLedID->LED_u8PortID,copy_pstrLedID->LED_u8PinID,DIO_u8LOW);
		}
		else if(copy_pstrLedID->LED_u8Connection==LED_SOURCE)
		{
			Local_enuErrorState=DIO_enuSetPinValue(copy_pstrLedID->LED_u8PortID,copy_pstrLedID->LED_u8PinID,DIO_u8HIGH);
		}
		else
		{
			Local_enuErrorState= ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t LED_enuTurnOFF(LED_t * copy_pstrLedID)
{
	ES_t Local_enuErrorState=ES_NOK;
	if(copy_pstrLedID!=NULL)
	{
		if(copy_pstrLedID->LED_u8Connection==LED_SINK)
		{
			Local_enuErrorState=DIO_enuSetPinValue(copy_pstrLedID->LED_u8PortID,copy_pstrLedID->LED_u8PinID,DIO_u8HIGH);
		}
		else if(copy_pstrLedID->LED_u8Connection==LED_SOURCE)
		{
			Local_enuErrorState=DIO_enuSetPinValue(copy_pstrLedID->LED_u8PortID,copy_pstrLedID->LED_u8PinID,DIO_u8LOW);
		}
		else
		{
			Local_enuErrorState= ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}
