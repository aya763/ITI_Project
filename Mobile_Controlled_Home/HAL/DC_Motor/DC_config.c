/*
 * DC_config.c
 *
 *  Created on: Aug 13, 2024
 *      Author: aya
 */

#include "../../LIB/STD_Types.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "DC_config.h"


DC_MOTOR_t  DC_MOTOR_AStrConfig[DC_MOTOR_NUM] =
{
		{DIO_u8PORTA,DIO_u8PIN0,DIO_u8PORTA,DIO_u8PIN1} ,
		{DIO_u8PORTB,DIO_u8PIN0,DIO_u8PORTB,DIO_u8PIN1}
};


