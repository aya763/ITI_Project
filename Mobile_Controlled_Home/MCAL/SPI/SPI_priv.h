/*
 * SPI_priv.h
 *
 *  Created on: Apr 23, 2024
 *      Author: aya
 */

#ifndef MCAL_SPI_SPI_PRIV_H_
#define MCAL_SPI_SPI_PRIV_H_


#define   NORMAL_SPEED_MODE                     0
#define   DOUBLE_SPEED_MODE                     1

#define   LSB_FIRST                             1
#define   MSB_FIRST                             0

#define   MASTER                                1
#define   SLAVE                                 0

#define   LEADING_RISING_EDGE                   0
#define   LEADING_FALLING_EDGE                  1

#define   LEADING_SAMPLE                        0  //Sample = receive
#define   LEADING_SETUP                         1  //Setup = send


#define   NORMAL_PRES_4                         0
#define   NORMAL_PRES_16                        1
#define   NORMAL_PRES_64                        2
#define   NORMAL_PRES_128                       3
#define   DOUBLE_PRES_2                         4
#define   DOUBLE_PRES_8                         5
#define   DOUBLE_PRES_32                        6
#define   DOUBLE_PRES_64                        7




#define SPCR              *((volatile u8 *)0x2D)     //SPI Control Register
#define SPCR_SPIE         7           //SPI Interrupt Enable
#define SPCR_SPE          6           // SPI Enable
#define SPCR_DORD         5           // Data Order
#define SPCR_MSTR         4           //Master/Slave Select
#define SPCR_CPOL         3           // Clock Polarity
#define SPCR_CPHA         2           // Clock Phase
#define SPCR_SPR1         1           //SPI Clock Rate Select 1 and 0
#define SPCR_SPR0         0


#define SPSR              *((volatile u8 *)0x2E)     //SPI Status Register
#define SPSR_SPIF         7            // SPI Interrupt Flag
#define SPSR_WCOL         6            // Write COLlision Flag
#define SPSR_SPI2X        0            // Double SPI Speed Bit


#define SPDR              *((volatile u8 *)0x2F)     //SPI Data Register


#endif /* MCAL_SPI_SPI_PRIV_H_ */
