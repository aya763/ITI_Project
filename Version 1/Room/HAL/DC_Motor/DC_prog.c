/*
 * DC_prog.c
 *
 *  Created on: Aug 13, 2024
 *      Author: aya
 */

#include <util/delay.h>

#include "../../LIB/STD_Types.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "DC_config.h"
#include "DC_priv.h"



ES_t DC_Motor_enuInit(DC_MOTOR_t *Copy_PStrMotorConfig)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_PStrMotorConfig != NULL)
	{
		u8  Local_u8Iterator;

		for(Local_u8Iterator = 0 ; Local_u8Iterator < DC_MOTOR_NUM ; Local_u8Iterator++)
		{

			Local_enuErrorState = DIO_enuSetPinDirection(Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_CW_PORT , Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_CW_PIN , DIO_u8OUTPUT);
			Local_enuErrorState = DIO_enuSetPinDirection(Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_CCW_PORT , Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_CCW_PIN , DIO_u8OUTPUT);
			Local_enuErrorState = DIO_enuSetPinValue(Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_CW_PORT , Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_CW_PIN , DIO_u8LOW);
			Local_enuErrorState = DIO_enuSetPinValue(Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_CCW_PORT , Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_CCW_PIN , DIO_u8LOW);
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}
ES_t DC_Motor_enuRotate(DC_MOTOR_t *Copy_PStrMotor_ID,u8 Copy_u8Direction)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_PStrMotor_ID != NULL)
	{
		switch(Copy_u8Direction)
		{
		case MOTOR_CW:
			Local_enuErrorState  = DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_CCW_PORT , Copy_PStrMotor_ID->DC_MOTOR_CCW_PIN , DIO_u8LOW);
			_delay_ms(1);
			Local_enuErrorState  = DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_CW_PORT , Copy_PStrMotor_ID->DC_MOTOR_CW_PIN , DIO_u8HIGH);
			break;
		case MOTOR_CCW:
			Local_enuErrorState  = DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_CW_PORT , Copy_PStrMotor_ID->DC_MOTOR_CW_PIN , DIO_u8LOW);
			_delay_ms(1);
			Local_enuErrorState  = DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_CCW_PORT , Copy_PStrMotor_ID->DC_MOTOR_CCW_PIN , DIO_u8HIGH);
			break;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}



	return Local_enuErrorState;
}
ES_t DC_Motor_enuStop(DC_MOTOR_t *Copy_PStrMotor_ID)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_PStrMotor_ID != NULL)
	{
		Local_enuErrorState  = DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_CCW_PORT , Copy_PStrMotor_ID->DC_MOTOR_CCW_PIN , DIO_u8LOW);
		Local_enuErrorState  = DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_CW_PORT , Copy_PStrMotor_ID->DC_MOTOR_CW_PIN , DIO_u8LOW);
		_delay_ms(1000);
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}















