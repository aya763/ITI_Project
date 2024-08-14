/*
 * LED_interface.h
 *
 *  Created on: Jul 25, 2024
 *      Author: aya
 */

#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_

#include "LED_private.h"
#include "LED_config.h"

ES_t LED_enuInit(LED_t * copy_pstrLedConfig);

ES_t LED_enuTurnON(LED_t * copy_pstrLedID);

ES_t LED_enuTurnOFF(LED_t * copy_pstrLedID);


#endif /* HAL_LED_LED_INTERFACE_H_ */
