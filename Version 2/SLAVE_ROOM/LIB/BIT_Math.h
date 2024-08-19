/*
 * BIT_Math.h
 *
 *  Created on: Jul 25, 2024
 *      Author: aya
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define SET_BIT(X,BIT_NO) X|=(1<<BIT_NO)
#define CLEAR_BIT(X,BIT_NO) X&=~(1<<BIT_NO)
#define READ_BIT(X,BIT_NO) ((X&(1<<BIT_NO))>>BIT_NO)
#define TOGGLE_BIT(X,BIT_NO) X^=(1<<BIT_NO)
#define GET_BIT(BYTE,BIT_N)     (1&(BYTE>>BIT_N))

#endif /* LIB_BIT_MATH_H_ */
