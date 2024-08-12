/*
 * PWM_int.h
 *
 *  Created on: Aug 7, 2024
 *      Author: aya
 */

#ifndef HAL_PWM_PWM_INT_H_
#define HAL_PWM_PWM_INT_H_

ES_t PWM_enuInit(void);

ES_t PWM_enuSetPeriod(u16 Copy_u8Period);

ES_t PWM_enuSetDutyCyle(u16 Copy_u8Duty);

#endif /* HAL_PWM_PWM_INT_H_ */
