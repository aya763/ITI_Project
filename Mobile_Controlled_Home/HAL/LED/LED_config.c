/*
 * LED_config.c
 *
 *  Created on: Jul 25, 2024
 *      Author: aya
 */

#include "../../LIB/STD_Types.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "LED_config.h"
#include "LED_private.h"

LED_t LED_AstrLedConfig[LED_NUM]={
		{DIO_u8PORTC,DIO_u8PIN0,LED_SOURCE,LED_OFF},
		{DIO_u8PORTC,DIO_u8PIN1,LED_SOURCE,LED_OFF},
		{DIO_u8PORTC,DIO_u8PIN2,LED_SOURCE,LED_OFF},
		{DIO_u8PORTC,DIO_u8PIN3,LED_SOURCE,LED_OFF},
		{DIO_u8PORTC,DIO_u8PIN4,LED_SOURCE,LED_OFF}
};

