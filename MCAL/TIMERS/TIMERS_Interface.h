/*
 * TIMERS_Interface.h
 *
 *  Created on: Aug 5, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef TIMERS_TIMERS_INTERFACE_H_
#define TIMERS_TIMERS_INTERFACE_H_

#include "../../Utilities/STD_TYPES.h"
#include "../GPIO/GPIO_Interface.h"
#include "TIMERS_Registers.h"
#include "TIMERS_Config.h"

typedef enum{
	TIMERS_CHANNEL1,
	TIMERS_CHANNEL2,
	TIMERS_CHANNEL3,
	TIMERS_CHANNEL4
}EN_Timers_channel_t;

void TIMERS_voidInit(st_TIM_RegDef_t* TIMx);

void TIMERS_voidSetInterrupt(st_TIM_RegDef_t* TIMx, void (*ptr)(void), u32 ms);
void TIMERS_voidStopTimer(st_TIM_RegDef_t* TIMx);

void TIMERS_voidDelaySec(u32 s);
void TIMERS_voidDelayMilliSec(u32 ms);

void TIMERS_voidInitPWM(st_TIM_RegDef_t* TIMx, EN_Timers_channel_t channel, f32 dutyCycle, u32 period);
void TIMERS_voidUpdateDutyCycle(st_TIM_RegDef_t* TIMx, EN_Timers_channel_t channel, f32 dutyCycle);

#endif /* TIMERS_TIMERS_INTERFACE_H_ */
