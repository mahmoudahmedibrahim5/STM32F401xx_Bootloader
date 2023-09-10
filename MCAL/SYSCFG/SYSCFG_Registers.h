/*
 * SYSCFG_Registers.h
 *
 *  Created on: Feb 23, 2023
 *      Author: ADMIN
 */

#ifndef SYSCFG_SYSCFG_REGISTERS_H_
#define SYSCFG_SYSCFG_REGISTERS_H_

#define SYSCFG_BASE_ADDR				0x40013800U

typedef volatile struct{
	u32 MEMRMP;
	u32 PMC;
	u32 EXTICR1;
	u32 EXTICR2;
	u32 EXTICR3;
	u32 EXTICR4;
	u32 CMPCR;
}st_SYSCFG_RegDef_t;

#define SYSCFG	((st_SYSCFG_RegDef_t *) SYSCFG_BASE_ADDR)

#endif /* SYSCFG_SYSCFG_REGISTERS_H_ */
