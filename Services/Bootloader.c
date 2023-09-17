/*
 * Bootloader.c
 *
 *  Created on: Sep 16, 2023
 *      Author: Mahmoud Ahmed
 */

#include "Bootloader.h"

BT_t serial = {USART6, 9600}; // PA11, PA12

void HelloBootloader(void)
{
	char msg[] = "Hello Bootloader\n";
	BT_voidInit(&serial);
	BT_voidSendData(&serial, (u8 *)msg, strlen(msg));
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
	FMI_voidMassErase();
}

void BL_cmdSectorErase(void)
{
	u8 sector = 0;
	char ack[] = "\n";
	BT_voidSendData(&serial, (u8 *)ack, strlen(ack));
	sector = 0xFF;
	while(sector == 0xFF)
		BT_voidReceiveDataTimeout(&serial, &sector, 1);
	sector &= ~(1<<7);
	sector -= '0';
	FMI_voidSectorErase(sector);
}

void BL_cmdFlashWrite(void)
{
	u8 record[44];
	BT_voidReceiveData(&serial, record, 44);
	PARSER_u8RecordParser(record);
}
