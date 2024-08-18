/*
 * DC_config.h
 *
 *  Created on: Aug 13, 2024
 *      Author: aya
 */

#ifndef HAL_DC_MOTOR_DC_CONFIG_H_
#define HAL_DC_MOTOR_DC_CONFIG_H_

#define DC_MOTOR_NUM        2




typedef  struct{

	u8 DC_MOTOR_CW_PORT;
	u8 DC_MOTOR_CW_PIN;
	u8 DC_MOTOR_CCW_PORT;
	u8 DC_MOTOR_CCW_PIN;

}DC_MOTOR_t;

#endif /* HAL_DC_MOTOR_DC_CONFIG_H_ */
