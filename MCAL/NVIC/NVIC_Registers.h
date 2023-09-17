/*
 * NVIC_Registers.h
 *
 *  Created on: Feb 22, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef NVIC_NVIC_REGISTERS_H_
#define NVIC_NVIC_REGISTERS_H_

#define NVIC_BASE_ADDR					0xE000E000

typedef volatile struct{
	u32 r1[64];
	u32 ISER[8];
	u32 r2[24];
	u32 ICER[8];
	u32 r3[24];
	u32 ISPR[8];
	u32 r4[24];
	u32 ICPR[8];
	u32 r5[24];
	u32 IABR[8];
	u32 r6[56];
	u8 IPR[240];
	u32 r7[580];
	u32 STIR;
}st_NVIC_RegDef_t;

#define NVIC	((st_NVIC_RegDef_t *)NVIC_BASE_ADDR)

#endif /* NVIC_NVIC_REGISTERS_H_ */
