/*
 * LED_config.h
 *
 *  Created on: Jul 25, 2024
 *      Author: aya
 */

#ifndef HAL_LED_LED_CONFIG_H_
#define HAL_LED_LED_CONFIG_H_

#define LED_NUM  5

typedef struct
{
	u8 LED_u8PortID;
	u8 LED_u8PinID;
	u8 LED_u8Connection;
	u8 LED_u8InitState;
}LED_t;

#endif /* HAL_LED_LED_CONFIG_H_ */
