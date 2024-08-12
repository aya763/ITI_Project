/*
 * PWM_prog.c
 *
 *  Created on: Aug 7, 2024
 *      Author: aya
 */

#include "../../LIB/STD_Types.h"
#include "../../LIB/errorState.h"


#include "../../MCAL/TIMER/TIMER1/TIMER1_int.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "PWM_config.h"
#include "PWM_priv.h"

static volatile u16 PWM_u16Period=0;

ES_t PWM_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	Local_enuErrorState= DIO_enuInit();
	Local_enuErrorState= TIMER1_enuInit();


#if PWM_CHANNEL==TIMER1_Channel_A
	Local_enuErrorState= DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN5,DIO_u8OUTPUT);
	Local_enuErrorState= DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN5,DIO_u8LOW);

#elif PWM_CHANNEL==TIMER1_Channel_B
	Local_enuErrorState= DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN4,DIO_u8OUTPUT);
	Local_enuErrorState= DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8LOW);

#else
#error "Attention!!, your PWM_CHANNEL Selection is Wrong...."

#endif


	return Local_enuErrorState;
}

ES_t PWM_enuSetPeriod(u16 Copy_u8Period)
{
	ES_t Local_enuErrorState=ES_NOK;

	PWM_u16Period=Copy_u8Period;
	Local_enuErrorState= TIMER1_enuSetICR(Copy_u8Period);

	return Local_enuErrorState;
}

ES_t PWM_enuSetDutyCyle(u16 Copy_u8Duty)
{
	ES_t Local_enuErrorState=ES_NOK;

	u32 Local_u16TON=(u32)Copy_u8Duty*PWM_u16Period/100;

#if PWM_CHANNEL==TIMER1_Channel_A
	Local_enuErrorState= TIMER1_enuSetChannelACTC(Local_u16TON);

#elif PWM_CHANNEL==TIMER1_Channel_B
	Local_enuErrorState= TIMER1_enuSetChannelBCTC(Local_u16TON);

#else
#error "Attention!!, your PWM_CHANNEL Selection is Wrong...."

#endif


	return Local_enuErrorState;
}






