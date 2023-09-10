/*
 * TIMERS_Registers.h
 *
 *  Created on: Aug 5, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef TIMERS_TIMERS_REGISTERS_H_
#define TIMERS_TIMERS_REGISTERS_H_

#define TIM2_BASE_ADDR					0x40000000U
#define TIM3_BASE_ADDR					0x40000400U
#define TIM4_BASE_ADDR					0x40000800U
#define TIM5_BASE_ADDR					0x40000C00U

typedef struct{
	u32 CR1;
	u32 CR2;
	u32 SMCR;
	u32 DIER;
	u32 SR;
	u32 EGR;
	u32 CCMR1;
	u32 CCMR2;
	u32 CCER;
	u32 CNT; 	// Counter Register
	u32 PSC; 	// PreScaler Register
	u32 ARR; 	// Auto-Reload Register
	u32 r0;
	u32 CCR1;
	u32 CCR2;
	u32 CCR3;
	u32 CCR4;
	u32 r1;
	u32 DCR;
	u32 DMAR;
	u32 OR; 	// present only in TIM2 and TIM5
}st_TIM_RegDef_t;

#define TIM2	((st_TIM_RegDef_t *)TIM2_BASE_ADDR)
#define TIM3	((st_TIM_RegDef_t *)TIM3_BASE_ADDR)
#define TIM4	((st_TIM_RegDef_t *)TIM4_BASE_ADDR)
#define TIM5	((st_TIM_RegDef_t *)TIM5_BASE_ADDR)

/* CR1 Register Bits */
#define TIMERS_BIT_CEN		0
#define TIMERS_BIT_UDIS		1
#define TIMERS_BIT_URS		2
#define TIMERS_BIT_OPM		3
#define TIMERS_BIT_DIR		4
#define TIMERS_BIT_CMS		5
#define TIMERS_BIT_ARBE		7
#define TIMERS_BIT_CKD		8

#endif /* TIMERS_TIMERS_REGISTERS_H_ */
