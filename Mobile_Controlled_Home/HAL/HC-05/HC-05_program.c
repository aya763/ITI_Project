/*
 * HC-05_program.c
 *
 *  Created on: Aug 14, 2024
 *      Author: Dubai
 */


#include "../../LIB/STD_Types.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/USART/USART_int.h"

#include "HC-05_config.h"
#include "HC-05_private.h"
#include "HC-05_interface.h"

ES_t HC_05_enuInit(void){
	ES_t Local_enuErrorState=ES_NOK;
	/*Set USART pins directions*/
	DIO_enuSetPinDirection(DIO_u8PORTD , DIO_u8PIN0 , DIO_u8INPUT);
	DIO_enuSetPinDirection(DIO_u8PORTD , DIO_u8PIN1 , DIO_u8OUTPUT);
	/*USART Initialization */
	Local_enuErrorState = USART_enuInit();
	Local_enuErrorState =USART_enuEnableReceiver();
	Local_enuErrorState =USART_enuEnableTransmitter();
   return Local_enuErrorState;
}

ES_t HC_05_enuRecieveString(char *Copy_pcData){
	ES_t Local_enuErrorState=ES_NOK;

	Local_enuErrorState = USART_enuRecieveString(Copy_pcData);

	return Local_enuErrorState;

}
ES_t HC_05_enuSendString(const char *Copy_pcData){
	ES_t Local_enuErrorState=ES_NOK;

	Local_enuErrorState = USART_enuSendString(Copy_pcData);

	return Local_enuErrorState;
}

ES_t HC_05_enuSendChar(u8 Copy_u8data){
	ES_t Local_enuErrorState=ES_NOK;

	Local_enuErrorState = USART_enuSendChar(Copy_u8data);

	return Local_enuErrorState;

}
ES_t HC_05_enuRecieveChar(u8 *Copy_pu8data){
	ES_t Local_enuErrorState=ES_NOK;

	Local_enuErrorState = USART_enuRecieveChar(Copy_pu8data);

	return Local_enuErrorState;

}
