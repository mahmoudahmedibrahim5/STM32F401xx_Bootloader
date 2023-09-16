/*
 * Bootloader.h
 *
 *  Created on: Sep 16, 2023
 *      Author: Mahmoud Ahmed
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#include "../ECUAL/BT_Module/BT_Interface.h"
#include <string.h>

#define SERIAL_DEBUG	0

void SerialTest(void);
void BL_getCommand(void);

void BL_cmdGetVersion(void);
void BL_cmdGetHelp(void);
void BL_cmdMassErase(void);
void BL_cmdSectorErase(void);
void BL_cmdFlashWrite(void);

#endif /* BOOTLOADER_H_ */
