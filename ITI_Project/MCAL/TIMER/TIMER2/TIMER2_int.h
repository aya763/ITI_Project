/*
 * TIMER2_interface.h
 *
 *  Created on: Aug 2, 2024
 *      Author: aya
 */

#ifndef MCAL_TIMER_TIMER2_TIMER2_INT_H_
#define MCAL_TIMER_TIMER2_TIMER2_INT_H_

ES_t TIMER2_enuInit(void);

ES_t TIMER2_enuCallBackOVF(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter);

ES_t TIMER2_enuCallBackCTC(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter);

ES_t TIMER2_enuSetPreload(u8 Copy_u8Preload);

ES_t TIMER2_enuSetCTC(u8 Copy_u8OCR2Value);

ES_t TIMER2_enuEnableOVFINTERRUPT(void);

ES_t TIMER2_enuEnableCTCINTERRUPT(void);

ES_t TIMER2_enuSetAsychDelay(u32 Copy_u8Time ,void(*Copy_pfunApp)(void*),void* Parameter);//Time in mS

#endif /* MCAL_TIMER_TIMER2_TIMER2_INT_H_ */
