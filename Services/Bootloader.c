/*
 * Bootloader.c
 *
 *  Created on: Sep 16, 2023
 *      Author: Mahmoud Ahmed
 */

#include "Bootloader.h"

BT_t serial = {USART6, 9600}; // PA11, PA12
u8 bootloaderOn = 2;
static void StopBootloader(void);

void HelloBootloader(void)
{
	char msg[] = "Hello Bootloader\n";
	BT_voidSendData(&serial, (u8 *)msg, strlen(msg));
}

void BL_start(void)
{
	BT_voidInit(&serial);
	TIMERS_voidSetInterrupt(TIM5, &StopBootloader, 4000);
	u8 ack = 0xFF;
	while(ack == 0xFF && bootloaderOn)
		BT_voidReceiveDataTimeout(&serial, &ack, 1);
	if(bootloaderOn)
		BL_getCommand();
}

static void StopBootloader(void)
{
	bootloaderOn--;
}

void BL_getCommand(void)
{
	u8 command;
	HelloBootloader();
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
	char ack[] = "1\n";
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
	char ack[] = "1\n";
	u8 record[100];
	u8 lengthOfNumber = 0xFF;
	u32 numberOfLines = 0;

	// Ack of entering flash write
	BT_voidSendData(&serial, (u8 *)ack, strlen(ack));

	while(lengthOfNumber == 0xFF)
		BT_voidReceiveDataTimeout(&serial, &lengthOfNumber, 1);
	lengthOfNumber &= ~(1<<7);
	lengthOfNumber -= '0';

	// Ack of receiving length of the number
	BT_voidSendData(&serial, (u8 *)ack, strlen(ack));


	BT_voidReceiveData(&serial, record, lengthOfNumber);
	for(u8 i=0; i<lengthOfNumber; i++){
		record[i] &= ~(1<<7);
		record[i] -= '0';
		numberOfLines *= 10;
		numberOfLines += record[i];
	}

	// Ack of receiving number of lines
	BT_voidSendData(&serial, (u8 *)ack, strlen(ack));

	u8 lengthOfRecord;
	for(u32 i=0; i<numberOfLines; i++)
	{
		BT_voidReceiveData(&serial, record, 2);
		record[0] &= ~(1<<7);
		record[1] &= ~(1<<7);
		lengthOfRecord = ((record[0]-'0')*10) + (record[1]-'0');

		// Ack of receiving length of record
		BT_voidSendData(&serial, (u8 *)ack, strlen(ack));

		BT_voidReceiveData(&serial, record, lengthOfRecord);
		PARSER_u8RecordParser(record);

		// Ack of receiving record
		BT_voidSendData(&serial, (u8 *)ack, strlen(ack));
	}

}
