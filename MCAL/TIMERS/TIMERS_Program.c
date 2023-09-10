/*
 * TIMERS_Program.c
 *
 *  Created on: Aug 5, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#include "TIMERS_Interface.h"

static void TIMERS_voidConfigurePWMPins(st_TIM_RegDef_t* TIMx, EN_Timers_channel_t channel);

void TIMERS_voidInit(st_TIM_RegDef_t* TIMx)
{

}

void TIMERS_voidStopTimer(st_TIM_RegDef_t* TIMx)
{
	TIMx->CR1 &= ~(1<<TIMERS_BIT_CEN);
}

void TIMERS_voidDelaySec(u32 s)
{
	// Enable UEV (Update event)
	TIMERS_DELAY_TIMER->CR1 &= ~(1<<TIMERS_BIT_UDIS);

	// Set counting as up
	TIMERS_DELAY_TIMER->CR1 &= ~(1<<TIMERS_BIT_DIR);

	// Set PreScaler
	TIMERS_DELAY_TIMER->PSC = ((TIMERS_FREQ*1000000)/1000) - 1;	// Periodic Time = 1 ms (because CK_CNT = 1000)

	// Auto-Reload Register
	TIMERS_DELAY_TIMER->ARR = 1000;

	// Start Timer
	TIMERS_DELAY_TIMER->CR1 |= (1<<TIMERS_BIT_CEN);

	for(u32 i=0; i<s; i++){
		while(!(TIMERS_DELAY_TIMER->SR & (1<<0)));
		// Clear The Update Flag
		TIMERS_DELAY_TIMER->SR &= ~(1<<0);
	}

	// Stop The Timer
	TIMERS_DELAY_TIMER->CR1 &= ~(1<<TIMERS_BIT_CEN);
}

void TIMERS_voidDelayMilliSec(u32 ms)
{
	// Enable UEV (Update event)
	TIMERS_DELAY_TIMER->CR1 &= ~(1<<TIMERS_BIT_UDIS);

	// Set counting as up
	TIMERS_DELAY_TIMER->CR1 &= (1<<TIMERS_BIT_DIR);

	// Set PreScaler
	TIMERS_DELAY_TIMER->PSC = ((TIMERS_FREQ*1000000)/1000000) - 1;	// Periodic Time = 1 us (because CK_CNT = 1000000)

	// Auto-Reload Register
	TIMERS_DELAY_TIMER->ARR = 1000;

	// Start The Timer
	TIMERS_DELAY_TIMER->CR1 |= (1<<TIMERS_BIT_CEN);

	for(u32 i=0; i<ms; i++){
		while(!(TIMERS_DELAY_TIMER->SR & (1<<0)));
		// Clear The Update Flag
		TIMERS_DELAY_TIMER->SR &= ~(1<<0);
	}

	// Stop The Timer
	TIMERS_DELAY_TIMER->CR1 &= ~(1<<TIMERS_BIT_CEN);
}

static void (*TIMERS_CallBackFunctionTIM2)(void) = NULL;
static void (*TIMERS_CallBackFunctionTIM3)(void) = NULL;
static void (*TIMERS_CallBackFunctionTIM4)(void) = NULL;
static void (*TIMERS_CallBackFunctionTIM5)(void) = NULL;

void TIMERS_voidSetInterrupt(st_TIM_RegDef_t* TIMx, void (*ptr)(void), u32 ms)
{
	/* Set CallBack Function */
	if(TIMx == TIM2)
		TIMERS_CallBackFunctionTIM2 = ptr;
	else if(TIMx == TIM3)
		TIMERS_CallBackFunctionTIM3 = ptr;
	else if(TIMx == TIM4)
		TIMERS_CallBackFunctionTIM4 = ptr;
	else if(TIMx == TIM5)
		TIMERS_CallBackFunctionTIM5 = ptr;

	/* Enable Interrupt */
	TIMx->DIER |= (1<<0);

	/* Configure The Timer */
	// Enable UEV (Update event)
	TIMx->CR1 &= ~(1<<TIMERS_BIT_UDIS);

	// Set counting as up
	TIMx->CR1 &= (1<<TIMERS_BIT_DIR);

	// Set PreScaler
	TIMx->PSC = ((TIMERS_FREQ*1000000)/10000) - 1;	// Periodic Time = 100 us (because CK_CNT = 10000)

	// Set Auto-Reload Register
	TIMx->ARR = 10*ms;

	// Start Timer
	TIMx->CR1 |= (1<<TIMERS_BIT_CEN);
}

void TIM2_IRQHandler(void)
{
	TIMERS_CallBackFunctionTIM2();

	// Clear The Flag
	TIM2->SR &= ~(1<<0);
}
void TIM3_IRQHandler(void)
{
	TIMERS_CallBackFunctionTIM3();

	// Clear The Flag
	TIM3->SR &= ~(1<<0);
}
void TIM4_IRQHandler(void)
{
	TIMERS_CallBackFunctionTIM4();

	// Clear The Flag
	TIM4->SR &= ~(1<<0);
}
void TIM5_IRQHandler(void)
{
	TIMERS_CallBackFunctionTIM5();

	// Clear The Flag
	TIM5->SR &= ~(1<<0);
}

void TIMERS_voidInitPWM(st_TIM_RegDef_t* TIMx, EN_Timers_channel_t channel, f32 dutyCycle, u32 period)
{
	/* Configure PWM Pin */
	TIMERS_voidConfigurePWMPins(TIMx, channel);

	// Set counting PreScaler
	TIMx->PSC = ((TIMERS_FREQ*1000000)/1000000) - 1;	// Periodic Time = 1 us (because CK_CNT = 1000000)

	// Set Frequency
	TIMx->ARR = period;

	// Set PreLoad Enable
	TIMx->CR1 |= (1<<7);
	switch(channel)
	{
	case TIMERS_CHANNEL1:
		// Set Duty Cycle
		TIMx->CCR1 = (dutyCycle * period)/100;
		// Set PWM Mode
		TIMx->CCMR1 |= (0b110 << 4);
		// Set Output compare PreLoad Enable
		TIMx->CCMR1 |= (1<<3);
		// Turn on Channel 1
		TIMx->CCER |= (1<<0);
		break;
	case TIMERS_CHANNEL2:
		// Set Duty Cycle
		TIMx->CCR2 = (dutyCycle * period)/100;
		// Set PWM Mode
		TIMx->CCMR1 |= (0b110 << 12);
		// Set Output compare PreLoad Enable
		TIMx->CCMR1 |= (1<<11);
		// Turn on Channel 2
		TIMx->CCER |= (1<<4);
		break;
	case TIMERS_CHANNEL3:
		// Set Duty Cycle
		TIMx->CCR3 = (dutyCycle * period)/100;
		// Set PWM Mode
		TIMx->CCMR2 |= (0b110 << 4);
		// Set Output compare PreLoad Enable
		TIMx->CCMR2 |= (1<<3);
		// Turn on Channel 1
		TIMx->CCER |= (1<<8);
		break;
	case TIMERS_CHANNEL4:
		// Set Duty Cycle
		TIMx->CCR4 = (dutyCycle * period)/100;
		// Set PWM Mode
		TIMx->CCMR2 |= (0b110 << 12);
		// Set Output compare PreLoad Enable
		TIMx->CCMR2 |= (1<<11);
		// Turn on Channel 1
		TIMx->CCER |= (1<<12);
		break;
	}

	// Initialize the registers
	TIMx->EGR |= (1<<0);

	// Enable Counter
	TIMx->CR1 |= (1<<0);
}

void TIMERS_voidUpdateDutyCycle(st_TIM_RegDef_t* TIMx, EN_Timers_channel_t channel, f32 dutyCycle)
{
	switch(channel)
	{
	case TIMERS_CHANNEL1:
		TIMx->CCR1 = (dutyCycle * TIMx->ARR)/100;
		break;
	case TIMERS_CHANNEL2:
		TIMx->CCR2 = (dutyCycle * TIMx->ARR)/100;
		break;
	case TIMERS_CHANNEL3:
		TIMx->CCR3 = (dutyCycle * TIMx->ARR)/100;
		break;
	case TIMERS_CHANNEL4:
		TIMx->CCR4 = (dutyCycle * TIMx->ARR)/100;
		break;
	}
}

static void TIMERS_voidConfigurePWMPins(st_TIM_RegDef_t* TIMx, EN_Timers_channel_t channel)
{
	GPIO_Config_t pwm;
	pwm.mode = GPIO_ALT_FN;
	pwm.outType = GPIO_PUSH_PULL;
	pwm.pupdState = GPIO_NO_PUPD;
	pwm.speed = GPIO_LOW_SPEED;

	if(TIMx == TIM2)
	{
		pwm.AltFuncMode = GPIO_AF1;
		switch(channel)
		{
		case TIMERS_CHANNEL1:
			GPIO_voidInitPin(PORTA, TIMERS_TIM2_CH1_PIN, &pwm);
			break;
		case TIMERS_CHANNEL2:
			#if (TIMERS_TIM2_CH2_PIN == 1)
				GPIO_voidInitPin(PORTA, TIMERS_TIM2_CH2_PIN, &pwm);
			#elif(TIMERS_TIM2_CH2_PIN == 3)
				GPIO_voidInitPin(PORTB, TIMERS_TIM2_CH2_PIN, &pwm);
			#endif
			break;
		case TIMERS_CHANNEL3:
			#if (TIMERS_TIM2_CH3_PIN == 2)
				GPIO_voidInitPin(PORTA, TIMERS_TIM2_CH3_PIN, &pwm);
			#elif(TIMERS_TIM2_CH3_PIN == 10)
				GPIO_voidInitPin(PORTB, TIMERS_TIM2_CH3_PIN, &pwm);
			#endif
			break;
		case TIMERS_CHANNEL4:
			GPIO_voidInitPin(PORTA, TIMERS_TIM2_CH4_PIN, &pwm);
			break;
		}
	}
	else if(TIMx == TIM3)
	{
		pwm.AltFuncMode = GPIO_AF2;
		switch(channel)
		{
		case TIMERS_CHANNEL1:
			#if (TIMERS_TIM3_CH1_PIN == 6)
				GPIO_voidInitPin(PORTA, TIMERS_TIM3_CH1_PIN, &pwm);
			#elif(TIMERS_TIM3_CH1_PIN == 4)
				GPIO_voidInitPin(PORTB, TIMERS_TIM3_CH1_PIN, &pwm);
			#endif

			break;
		case TIMERS_CHANNEL2:
			#if (TIMERS_TIM3_CH2_PIN == 7)
				GPIO_voidInitPin(PORTA, TIMERS_TIM3_CH2_PIN, &pwm);
			#elif(TIMERS_TIM3_CH2_PIN == 5)
				GPIO_voidInitPin(PORTB, TIMERS_TIM3_CH2_PIN, &pwm);
			#endif
			break;
		case TIMERS_CHANNEL3:
			GPIO_voidInitPin(PORTB, TIMERS_TIM3_CH3_PIN, &pwm);
			break;
		case TIMERS_CHANNEL4:
			GPIO_voidInitPin(PORTB, TIMERS_TIM3_CH4_PIN, &pwm);
			break;
		}
	}
	else if(TIMx == TIM4)
	{
		pwm.AltFuncMode = GPIO_AF2;
		switch(channel)
		{
		case TIMERS_CHANNEL1:
			GPIO_voidInitPin(PORTB, TIMERS_TIM4_CH3_PIN, &pwm);
			break;
		case TIMERS_CHANNEL2:
			GPIO_voidInitPin(PORTB, TIMERS_TIM4_CH2_PIN, &pwm);
			break;
		case TIMERS_CHANNEL3:
			GPIO_voidInitPin(PORTB, TIMERS_TIM4_CH3_PIN, &pwm);
			break;
		case TIMERS_CHANNEL4:
			GPIO_voidInitPin(PORTB, TIMERS_TIM4_CH4_PIN, &pwm);
			break;
		}
	}
	else if(TIMx == TIM5)
	{
		pwm.AltFuncMode = GPIO_AF2;
		switch(channel)
		{
		case TIMERS_CHANNEL1:
			GPIO_voidInitPin(PORTA, TIMERS_TIM5_CH3_PIN, &pwm);
			break;
		case TIMERS_CHANNEL2:
			GPIO_voidInitPin(PORTA, TIMERS_TIM5_CH2_PIN, &pwm);
			break;
		case TIMERS_CHANNEL3:
			GPIO_voidInitPin(PORTA, TIMERS_TIM5_CH3_PIN, &pwm);
			break;
		case TIMERS_CHANNEL4:
			GPIO_voidInitPin(PORTA, TIMERS_TIM5_CH4_PIN, &pwm);
			break;
		}
	}
}
