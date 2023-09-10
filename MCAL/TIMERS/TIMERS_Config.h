/*
 * TIMERS_Config.h
 *
 *  Created on: Aug 5, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef TIMERS_TIMERS_CONFIG_H_
#define TIMERS_TIMERS_CONFIG_H_

/* Write timers clock input in MHz*/
#define TIMERS_FREQ		16

/* ************* Delay Timer **************
 * Choose the timer that will be used in delay functions
 * (TIM2, TIM3, TIM4, TIM5)
 * */
#define TIMERS_DELAY_TIMER		TIM2


/* PWM Channels Configurations */
#define TIMERS_TIM2_CH1_PIN		0  		// Could be 0 (PORTA) or 5 (PORTA) or 15 (PORTA)
#define TIMERS_TIM2_CH2_PIN		1		// Could be 1 (PORTA) or 3 (PORTB)
#define TIMERS_TIM2_CH3_PIN		2		// Could be 2 (PORTA) or 10 (PORTB)
#define TIMERS_TIM2_CH4_PIN		3		// Only 3 (PORTA)

#define TIMERS_TIM3_CH1_PIN		6  		// Could be 6 (PORTA) or 4 (PORTB)
#define TIMERS_TIM3_CH2_PIN		7		// Could be 7 (PORTA) or 5 (PORTB)
#define TIMERS_TIM3_CH3_PIN		0		// Only 0 (PORTB)
#define TIMERS_TIM3_CH4_PIN		1		// Only 1 (PORTB)

#define TIMERS_TIM4_CH1_PIN		6  		// Only 6 (PORTB)
#define TIMERS_TIM4_CH2_PIN		7		// Only 7 (PORTB)
#define TIMERS_TIM4_CH3_PIN		8		// Only 8 (PORTB)
#define TIMERS_TIM4_CH4_PIN		9		// Only 9 (PORTB)

#define TIMERS_TIM5_CH1_PIN		0  		// Only 0 (PORTA)
#define TIMERS_TIM5_CH2_PIN		1		// Only 1 (PORTA)
#define TIMERS_TIM5_CH3_PIN		2		// Only 2 (PORTA)
#define TIMERS_TIM5_CH4_PIN		3		// Only 3 (PORTA)

#endif /* TIMERS_TIMERS_CONFIG_H_ */
