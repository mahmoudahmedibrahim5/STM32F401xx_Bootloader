/*
 * NVIC_Program.c
 *
 *  Created on: Feb 22, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#include "NVIC_Interface.h"

void NVIC_voidEnableIRQ(u8 IRQn)
{
	// To know which register we will use, ex: ISER0, ISER1, ...
	u8 index = IRQn/32;
	NVIC->ISER[index] |= (u32)(1<<(IRQn%32));
}

void NVIC_voidDisableIRQ(u8 IRQn)
{
	// To know which register we will use, ex: ICER0, ICER1, ...
	u8 index = IRQn/32;
	NVIC->ICER[index] |= (u32)(1<<(IRQn%32));
}


void NVIC_voidSetPendingIRQ(u8 IRQn)
{
	// To know which register we will use, ex: ISPR0, ISPR1, ...
	u8 index = IRQn/32;
	NVIC->ISPR[index] |= (u32)(1<<(IRQn%32));
}

void NVIC_voidClearPendingIRQ(u8 IRQn)
{
	// To know which register we will use, ex: ICPR0, ICPR1, ...
	u8 index = IRQn/32;
	NVIC->ICPR[index] |= (u32)(1<<(IRQn%32));
}


void NVIC_voidSetPriority(u8 IRQn, u8 priority)
{
	NVIC->IPR[IRQn] = (priority<<4);
}

u8 NVIC_u8GetPriority(u8 IRQn)
{
	return (NVIC->IPR[IRQn]>>4);
}
