/*
 * Servo_prog.c
 *
 *  Created on: Aug 13, 2024
 *      Author: aya
 */

#include "../../LIB/STD_Types.h"
#include "../../LIB/errorState.h"


#include "../../MCAL/DIO/DIO_interface.h"


#include "../../MCAL/TIMER/TIMER1/TIMER1_int.h"


#include "Servo_config.h"
#include "Servo_priv.h"



ES_t SERVO_enudInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	Local_enuErrorState= DIO_enuInit();
	Local_enuErrorState= TIMER1_enuInit();


#if SERVO_CHANNEL==TIMER1_Channel_A
	Local_enuErrorState= DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN5,DIO_u8OUTPUT);
	Local_enuErrorState= DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN5,DIO_u8LOW);

#elif SERVO_CHANNEL==TIMER1_Channel_B
	Local_enuErrorState= DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN4,DIO_u8OUTPUT);
	Local_enuErrorState= DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8LOW);

#else
#error "Attention!!, your PWM_CHANNEL Selection is Wrong...."

#endif

	Local_enuErrorState= TIMER1_enuSetICR(SERVO_PERIOD);

	return Local_enuErrorState;
}

ES_t SERVO_enuSetAngle(s8 Copy_s8Angle)
{
	ES_t Local_enuErrorState=ES_NOK;

	Copy_s8Angle+=90;
	u32 Local_u32TON=1000+((u32)Copy_s8Angle*1000/180);

#if SERVO_CHANNEL==TIMER1_Channel_A
	Local_enuErrorState= TIMER1_enuSetChannelACTC(Local_u32TON);

#elif SERVO_CHANNEL==TIMER1_Channel_B
	Local_enuErrorState= TIMER1_enuSetChannelBCTC(Local_u32TON);

#else
#error "Attention!!, your PWM_CHANNEL Selection is Wrong...."

#endif



	return Local_enuErrorState;
}

