/*
 * SPI_int.h
 *
 *  Created on: Apr 23, 2024
 *      Author: aya
 */

#ifndef MCAL_SPI_SPI_INT_H_
#define MCAL_SPI_SPI_INT_H_

ES_t SPI_enuMaster_Init(void);

ES_t SPI_enuSlaveInit(void);

ES_t SPI_enuTranceive(u8 Copy_u8TransmitData , u8* Copy_pu8ReceiveData);

ES_t SPI_enuSPIEnable(void);

ES_t SPI_enuSPIDisable(void);

ES_t SPI_enuEnableInterrupt(void);

ES_t SPI_enuDisableInterrupt(void);

ES_t SPI_enuCallback(void *(Copy_pfun)(void *), void *Copy_pvParameter);

#endif /* MCAL_SPI_SPI_INT_H_ */
