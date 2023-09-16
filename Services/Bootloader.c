/*
 * Bootloader.c
 *
 *  Created on: Sep 16, 2023
 *      Author: Mahmoud Ahmed
 */

#include "Bootloader.h"

#if SERIAL_DEBUG
BT_t debug = {USART1, 9600};  // PA9, PA10
#else
BT_t serial = {USART6, 9600}; // PA11, PA12
#endif
char DataBuffer[200];

void SerialTest(void)
{
	char msg[] = "Hello Bootloader\n";
#if SERIAL_DEBUG
	BT_voidInit(&debug);
#else
	BT_voidInit(&serial);
#endif

#if SERIAL_DEBUG
	BT_voidSendData(&debug, (u8 *)msg, strlen(msg));
#else
	BT_voidSendData(&serial, (u8 *)msg, strlen(msg));
#endif
}

void BL_getCommand(void)
{
	u8 command;
	while(1)
	{
		command = 0xFF;
		while(command == 0xFF)
			BT_voidReceiveDataTimeout(&serial, &command, 1);
		command &= ~(1<<7);
		command -= '0';

		if(command == 0)
			break;

		switch(command)
		{
		case 1:
			BL_cmdGetVersion();
			break;
		case 2:
			BL_cmdGetHelp();
			break;
		case 3:
			BL_cmdMassErase();
			break;
		case 4:
			BL_cmdSectorErase();
			break;
		case 5:
			BL_cmdFlashWrite();
			break;
		}
	}
}

void BL_cmdGetVersion(void)
{
	char version[] = "Part No. : stm32f401cdu6\nFlash : 384kB\nSRAM : 96kB\n";
	BT_voidSendData(&serial, (u8 *)version, strlen(version));
}

void BL_cmdGetHelp(void)
{
	char help[] = "No\n";
	BT_voidSendData(&serial, (u8 *)help, strlen(help));
}

void BL_cmdMassErase(void)
{

}

void BL_cmdSectorErase(void)
{

}

void BL_cmdFlashWrite(void)
{

}
