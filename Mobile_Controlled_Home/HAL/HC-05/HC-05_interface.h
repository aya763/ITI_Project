/*
 * HC-05_interface.h
 *
 *  Created on: Aug 14, 2024
 *      Author: Dubai
 */

#ifndef HAL_HC_05_HC_05_INTERFACE_H_
#define HAL_HC_05_HC_05_INTERFACE_H_

ES_t HC_05_enuInit(void);
ES_t HC_05_enuRecieveString(u8 *Copy_pcData);
ES_t HC_05_enuSendString(const u8 *Copy_pcData);
ES_t HC_05_enuSendChar(u8 Copy_u8data);
ES_t HC_05_enuRecieveChar(u8 *Copy_pu8data);

#endif /* HAL_HC_05_HC_05_INTERFACE_H_ */
