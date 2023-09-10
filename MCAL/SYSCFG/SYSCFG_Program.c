/*
 * SYSCFG_Program.c
 *
 *  Created on: Feb 23, 2023
 *      Author: ADMIN
 */

#include "SYSCFG_Interface.h"

void SYSCFG_voidEXTIcontrol(u8 port, u8 lineNum)
{
	if(lineNum < 4){
		SYSCFG->EXTICR1 |= (port<<(lineNum*4));
	}
	else if(lineNum < 8){
		SYSCFG->EXTICR2 |= ((port<<(lineNum-4)*4));
	}
	else if(lineNum < 12){
		SYSCFG->EXTICR3 |= ((port<<(lineNum-8)*4));
	}
	else if(lineNum < 16){
		SYSCFG->EXTICR4 |= ((port<<(lineNum-12)*4));
	}

}

