/*
 * DC_int.h
 *
 *  Created on: Aug 13, 2024
 *      Author: aya
 */

#ifndef HAL_DC_MOTOR_DC_INT_H_
#define HAL_DC_MOTOR_DC_INT_H_

#define DC_MOTOR_CW		    0
#define DC_MOTOR_CCW		1

ES_t DC_Motor_enuInit(DC_MOTOR_t *Copy_PStrMotorConfig);
ES_t DC_Motor_enuRotate(DC_MOTOR_t *Copy_PStrMotor_ID,u8 Copy_u8Direction);
ES_t DC_Motor_enuStop(DC_MOTOR_t *Copy_PStrMotor_ID);

#endif /* HAL_DC_MOTOR_DC_INT_H_ */
