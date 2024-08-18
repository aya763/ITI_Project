/*
 * TIMER2_prog.c
 *
 *  Created on: Aug 2, 2024
 *      Author: aya
 */

#include "../../../LIB/errorState.h"
#include "../../../LIB/STD_Types.h"

#include "../../EINT/Interrupt.h"
#include "../TIMER_register.h"

#include "TIMER2_priv.h"
#include "TIMER2_config.h"



static void (*TIMER2_APfunCallBack [TIMER2_CALL_BACK])(void*)= {NULL,NULL,NULL};
static void  *TIMER2_APvidParameter[TIMER2_CALL_BACK]        = {NULL,NULL,NULL};

static u32 Timer2_NumOVF=0;
static u32 Timer2_Preload=0;




ES_t TIMER2_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

#if TIMER2_PRESCALER == TIMER2_NO_CLOCK_SOURCE
	TCCR2 &=~(1<<TCCR2_CS22);
	TCCR2 &=~(1<<TCCR2_CS21);
	TCCR2 &=~(1<<TCCR2_CS20);
	Local_enuErrorState =ES_OK;
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_1
	TCCR2 &=~(1<<TCCR0_CS22);
	TCCR2 &=~(1<<TCCR0_CS21);
	TCCR2 |= (1<<TCCR0_CS20);
	Local_enuErrorState =ES_OK;
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_8
	TCCR2 &=~(1<<TCCR2_CS22);
	TCCR2 |= (1<<TCCR2_CS21);
	TCCR2 &=~(1<<TCCR2_CS20);
	Local_enuErrorState =ES_OK;
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_64
	TCCR2 &=~(1<<TCCR2_CS22);
	TCCR2 |= (1<<TCCR2_CS21);
	TCCR2 |= (1<<TCCR2_CS20);
	Local_enuErrorState =ES_OK;
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_256
	TCCR2 |= (1<<TCCR2_CS22);
	TCCR2 &=~(1<<TCCR2_CS21);
	TCCR2 &=~(1<<TCCR2_CS20);
	Local_enuErrorState =ES_OK;
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_1024
	TCCR2 |= (1<<TCCR2_CS22);
	TCCR2 &=~(1<<TCCR2_CS21);
	TCCR2 |= (1<<TCCR2_CS20);
	Local_enuErrorState =ES_OK;
#elif TIMER2_PRESCALER == TIMER2_EXT_CLOCK_FALLING_EDGE
	TCCR2 |= (1<<TCCR2_CS22);
	TCCR2 |= (1<<TCCR2_CS21);
	TCCR2 &=~(1<<TCCR2_CS20);
	Local_enuErrorState =ES_OK;
#elif TIMER2_PRESCALER == TIMER2_EXT_CLOCK_RISING_EDGE
	TCCR2 |=(1<<TCCR2_CS22);
	TCCR2 |=(1<<TCCR2_CS21);
	TCCR2 |=(1<<TCCR2_CS20);
	Local_enuErrorState =ES_OK;
#else
#error "Attention!!, your TIMER2_PRESCALER Selection is Wrong...."

#endif


	  // MODE
#if TIMER2_MODE == TIMER2_OVER_FLOW
	TCCR2 &=~(1<<TCCR2_WGM21);
	TCCR2 &=~(1<<TCCR2_WGM20);
	#if TIMER2_OC2_PIN_STATE == TIMER2_OVF_DISCONNECT_OC2
		TCCR2 &=~(1<<TCCR2_COM20);
		TCCR2 &=~(1<<TCCR2_COM21);
		Local_enuErrorState =ES_OK;
	#else
	#error"Attention!!, you must disable OC2_PIN at overflow MODE...."
	#endif

#elif TIMER2_MODE == TIMER2_COMPARE_MATCH
		TCCR2 |= (1<<TCCR2_WGM21);
		TCCR2 &=~(1<<TCCR2_WGM20);
		#if TIMER2_OC2_PIN_STATE == TIMER2_CTC_DISCONNECT_OC2
			TCCR2 &=~(1<<TCCR2_COM20);
			TCCR2 &=~(1<<TCCR2_COM21);
			Local_enuErrorState =ES_OK;
		#elif TIMER2_OC2_PIN_STATE == TIMER2_CTC_TOGGLE_OC2
			TCCR2 |= (1<<TCCR2_COM20);
			TCCR2 &=~(1<<TCCR2_COM21);
			Local_enuErrorState =ES_OK;
		#elif TIMER2_OC2_PIN_STATE == TIMER2_CTC_CLEAR_OC2
			TCCR2 &=~(1<<TCCR2_COM20);
			TCCR2 |= (1<<TCCR2_COM21);
			Local_enuErrorState =ES_OK;
		#elif TIMER2_OC2_PIN_STATE == TIMER2_CTC_SET_OC2
			TCCR2 |=(1<<TCCR2_COM20);
			TCCR2 |=(1<<TCCR2_COM21);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC2_PIN state is wrong or the mode is not CTC...."
		#endif

#elif TIMER2_MODE == TIMER2_PHASE_CORRECT_PWM
		TCCR2 &=~(1<<TCCR2_WGM21);
		TCCR2 |= (1<<TCCR2_WGM20);
		#if TIMER2_OC2_PIN_STATE == TIMER2_PHASE_CLEAR_CTC_SET_TOP
			TCCR2 &=~(1<<TCCR2_COM20);
			TCCR2 |= (1<<TCCR2_COM21);
			Local_enuErrorState =ES_OK;
		#elif TIMER2_OC2_PIN_STATE == TIMER2_PHASE_SET_CTC_CLEAR_TOP
			TCCR2 |=(1<<TCCR2_COM20);
			TCCR2 |=(1<<TCCR2_COM21);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC2_PIN state is wrong or the mode is not Phase Correct PWM...."
		#endif

#elif TIMER2_MODE == TIMER2_FAST_PWM
		TCCR2 |=(1<<TCCR2_WGM21);
		TCCR2 |=(1<<TCCR2_WGM20);
		#if TIMER2_OC2_PIN_STATE == TIMER2_FAST_PMW_CLEAR_CTC_SET_TOP
			TCCR2 &=~(1<<TCCR2_COM20);
			TCCR2 |= (1<<TCCR2_COM21);
			Local_enuErrorState =ES_OK;
		#elif TIMER2_OC2_PIN_STATE == TIMER2_FAST_PMW_SET_CTC_CLEAR_TOP
			TCCR2 |=(1<<TCCR2_COM20);
			TCCR2 |=(1<<TCCR2_COM21);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC2_PIN state is wrong or the mode is not Fast PWM...."
		#endif
#else
#error "Attention!!, your TIMER2_MODE Selection is Wrong...."
#endif


	return Local_enuErrorState;
}

ES_t TIMER2_enuCallBackOVF(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_PfunCallBack!=NULL)
	{
		TIMER2_APfunCallBack [TIMER2_OVF_CALLBACK] = Copy_PfunCallBack;
		TIMER2_APvidParameter[TIMER2_OVF_CALLBACK] = Copy_PvidParameter;
		Local_enuErrorState =ES_OK;
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t TIMER2_enuCallBackCTC(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_PfunCallBack!=NULL)
	{

		TIMER2_APfunCallBack [TIMER2_CTC_CALLBACK] = Copy_PfunCallBack;
		TIMER2_APvidParameter[TIMER2_CTC_CALLBACK] = Copy_PvidParameter;
		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t TIMER2_enuSetPreload(u8 Copy_u8Preload)
{
	ES_t Local_enuErrorState=ES_NOK;

	TCNT2 =Copy_u8Preload;
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t TIMER2_enuSetCTC(u8 Copy_u8OCR2Value)
{
	ES_t Local_enuErrorState=ES_NOK;

	OCR2 =Copy_u8OCR2Value;
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t TIMER2_enuEnableOVFINTERRUPT(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMSK |=(1<<TIMSK_TOIE2);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t TIMER2_enuEnableCTCINTERRUPT(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMSK |=(1<<TIMSK_OCIE2);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t TIMER2_enuSetAsychDelay(u32 Copy_u8Time ,void(*Copy_pfunApp)(void*),void* Parameter)
{
	ES_t Local_enuErrorState=ES_NOK;

	f32 Local_f32OVFTime=TIMER2_OVF_COUNTS *((f32)TIMER2_PRESCALER/TIMER2_F_CPU);

	f32 Local_f32NumOVF = (Copy_u8Time)/(Local_f32OVFTime);

	if((Local_f32NumOVF-(u32)Local_f32NumOVF) != 0.0)
	{
		u32 Local_u32NumOVF =(u32)Local_f32NumOVF +1;
		Local_f32NumOVF = Local_f32NumOVF-(u32)Local_f32NumOVF;
		u8 Local_u8Preload =256 - (Local_f32NumOVF * 256);
		Timer2_NumOVF =Local_u32NumOVF;
		Timer2_Preload =Local_u8Preload;
		TCNT2 =Local_u8Preload;
	}
	else
	{
		Timer2_NumOVF =(u32)Local_f32NumOVF;
	}

	if(Copy_pfunApp!=NULL)
	{
		TIMER2_APfunCallBack[TIMER2_OVF_CALLBACK]=Copy_pfunApp;
		TIMER2_APvidParameter[TIMER2_OVF_CALLBACK]=Parameter;
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	TIMSK |=(1<<TIMSK_TOIE2);


	return Local_enuErrorState;
}










ISR(VECT_TIMER2_OVF)
{
	if (TIMER2_APfunCallBack[TIMER2_OVF_CALLBACK] != NULL)
	{
		TIMER2_APfunCallBack[TIMER2_OVF_CALLBACK](TIMER2_APvidParameter[TIMER2_OVF_CALLBACK]);
	}

}

ISR(VECT_TIMER2_CTC)
{

	if (TIMER2_APfunCallBack[TIMER2_CTC_CALLBACK] != NULL)
	{
		TIMER2_APfunCallBack[TIMER2_CTC_CALLBACK](TIMER2_APvidParameter[TIMER2_CTC_CALLBACK]);
	}
}





