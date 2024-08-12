/*
 * SPI_prog.c
 *
 *  Created on: Apr 23, 2024
 *      Author: aya
 */

#include "../../LIB/errorState.h"
#include "../../LIB/STD_Types.h"

#include "../EINT/Interrupt.h"

#include "SPI_config.h"
#include "SPI_priv.h"

void (* SPI_pFunc)(void *)=NULL;
void * SPI_pParameter=NULL;

ES_t SPI_enuMaster_Init(void)
{
	ES_t Local_enuErrorState=ES_NOK;
	//Select SPI Speed Mode
#if  SPI_SPEED_MODE  == NORMAL_SPEED_MODE

	SPSR &=~(1<<SPSR_SPI2X);
	Local_enuErrorState = ES_OK;

#elif  SPI_SPEED_MODE  == DOUBLE_SPEED_MODE

	SPSR |=(1<<SPSR_SPI2X);
	Local_enuErrorState = ES_OK;

#else
#error  "Speed Mode Selection is Wrong"
#endif

	//Select Data Order
#if  SPI_DATA_ORDER  == LSB_FIRST
	SPCR |=(1<<SPCR_DORD);
	Local_enuErrorState = ES_OK;

#elif  SPI_DATA_ORDER  == MSB_FIRST

	SPCR &=~(1<<SPCR_DORD);
	Local_enuErrorState = ES_OK;

#else
#error "Data Order Selection is Wrong"
#endif

	//Select Clock Polarity
#if  SPI_CLOCK_POLARITY  == LEADING_RISING_EDGE

	SPCR &=~(1<<SPCR_CPOL);
	Local_enuErrorState = ES_OK;

#elif  SPI_CLOCK_POLARITY  == LEADING_FALLING_EDGE

	SPCR |=(1<<SPCR_CPOL);
	Local_enuErrorState = ES_OK;

#else
#error  "Clock Polarity Selection is Wrong"
#endif

	//Select Clock Phase
#if  SPI_CLOCK_PHASE  == LEADING_SAMPLE

	SPCR &=~(1<<SPCR_CPHA);
	Local_enuErrorState = ES_OK;

#elif  SPI_CLOCK_PHASE  == LEADING_SETUP

	SPCR |=(1<<SPCR_CPHA);
	Local_enuErrorState = ES_OK;

#else
#error  "Clock Phase Selection is Wrong"
#endif

	//Select SPI Clock Rate
#if  SPI_CLOCK_RATE  == NORMAL_PRES_4  || SPI_CLOCK_RATE  == DOUBLE_PRES_2

	SPCR &=~(1<<SPCR_SPR0);
	SPCR &=~(1<<SPCR_SPR1);
	Local_enuErrorState  = ES_OK;

#elif  SPI_CLOCK_RATE  == NORMAL_PRES_16  || SPI_CLOCK_RATE  == DOUBLE_PRES_8

	SPCR |=(1<<SPCR_SPR0);
	SPCR &=~(1<<SPCR_SPR1);
	Local_enuErrorState  = ES_OK;

#elif  SPI_CLOCK_RATE  == NORMAL_PRES_64  || SPI_CLOCK_RATE  == DOUBLE_PRES_32

	SPCR &=~(1<<SPCR_SPR0);
	SPCR |=(1<<SPCR_SPR1);
	Local_enuErrorState  = ES_OK;

#elif  SPI_CLOCK_RATE  == NORMAL_PRES_128  || SPI_CLOCK_RATE  == DOUBLE_PRES_64

	SPCR |=(1<<SPCR_SPR0);
	SPCR |=(1<<SPCR_SPR1);
	Local_enuErrorState  = ES_OK;

#else
#error "Clock Rate Selection is Wrong"
#endif

	//SET Master
	SPCR |=(1<<SPCR_MSTR);


	return Local_enuErrorState;
}

ES_t SPI_enuSlaveInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	//Select SPI Speed Mode
#if  SPI_SPEED_MODE  == NORMAL_SPEED_MODE

	SPSR &=~(1<<SPSR_SPI2X);
	Local_enuErrorState = ES_OK;

#elif  SPI_SPEED_MODE  == DOUBLE_SPEED_MODE

	SPSR |=(1<<SPSR_SPI2X);
	Local_enuErrorState = ES_OK;

#else
#error  "Speed Mode Selection is Wrong"
#endif

	//Select Data Order
#if  SPI_DATA_ORDER  == LSB_FIRST
	SPCR |=(1<<SPCR_DORD);
	Local_enuErrorState = ES_OK;

#elif  SPI_DATA_ORDER  == MSB_FIRST

	SPCR &=~(1<<SPCR_DORD);
	Local_enuErrorState = ES_OK;

#else
#error "Data Order Selection is Wrong"
#endif

	//Select Clock Polarity
#if  SPI_CLOCK_POLARITY  == LEADING_RISING_EDGE

	SPCR &=~(1<<SPCR_CPOL);
	Local_enuErrorState = ES_OK;

#elif  SPI_CLOCK_POLARITY  == LEADING_FALLING_EDGE

	SPCR |=(1<<SPCR_CPOL);
	Local_enuErrorState = ES_OK;

#else
#error  "Clock Polarity Selection is Wrong"
#endif

	//Select Clock Phase
#if  SPI_CLOCK_PHASE  == LEADING_SAMPLE

	SPCR &=~(1<<SPCR_CPHA);
	Local_enuErrorState = ES_OK;

#elif  SPI_CLOCK_PHASE  == LEADING_SETUP

	SPCR |=(1<<SPCR_CPHA);
	Local_enuErrorState = ES_OK;

#else
#error  "Clock Phase Selection is Wrong"
#endif

	//SET Slave
	SPCR &=~(1<<SPCR_MSTR);


	return Local_enuErrorState;
}

ES_t SPI_enuTranceive(u8 Copy_u8TransmitData , u8* Copy_pu8ReceiveData)
{
	ES_t Local_enuErrorState=ES_NOK;

	SPDR = Copy_u8TransmitData;

	while(!(SPSR &(1<< SPSR_SPIF)));

	if(Copy_pu8ReceiveData != NULL)
	{
		*Copy_pu8ReceiveData = SPDR;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t SPI_enuSPIEnable(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	SPCR |=(1<<SPCR_SPE);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t SPI_enuSPIDisable(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	SPCR &=~(1<<SPCR_SPE);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t SPI_enuEnableInterrupt(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	SPCR |=(1<<SPCR_SPIE);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t SPI_enuDisableInterrupt(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	SPCR &=~(1<<SPCR_SPIE);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t SPI_enuCallback(void *(Copy_pfun)(void *), void *Copy_pvParameter)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_pfun!=NULL)
	{
		SPI_pFunc=Copy_pfun;
		SPI_pParameter=Copy_pvParameter;
		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


ISR(VECT_SPI)
{
	if(SPI_pFunc!=NULL)
	{
		SPI_pFunc(SPI_pParameter);
	}

}



