/*
 * PySerial_test.c
 *
 *  Created on: Sep 5, 2023
 *      Author: Mahmoud Ahmed
 */

#include "../ECUAL/BT_Module/BT_Interface.h"
#include "../ECUAL/LED/LED_Interface.h"

#include "../MCAL/RCC/RCC_Interface.h"
#include "../MCAL/TIMERS/TIMERS_Interface.h"
#include "../MCAL/FMI/FMI_Interface.h"

#include "../Services/PARSER.h"

u8 true[5] = "True\n";
u8 false[6] = "False\n";
u8 record[5][50] = {":020000040801F2",
                        ":1000000000800120590A0008A90A0008A90A00086E",
                        ":10001000A90A0008A90A0008A90A000800000000AF",
                        ":10002000000000000000000000000000A90A000815",
                        ":080B0400F8BC08BC9E467047D6"};
u8 hexFile[200][50];
int main()
{
	LED_t red = {PORTA, 0};
	LED_t green = {PORTA, 1};
	BT_t serial = {USART1, 9600};
	BT_t debug = {USART2, 9600};

	RCC_voidInit();
	RCC_voidPeripheralEnable(GPIOA_EN);
	RCC_voidPeripheralEnable(GPIOB_EN);
	RCC_voidPeripheralEnable(USART1_EN);
	RCC_voidPeripheralEnable(USART2_EN);
	RCC_voidPeripheralEnable(TIM1_EN);
	RCC_voidPeripheralEnable(TIM2_EN);

	LED_voidInit(&red);
	LED_voidInit(&green);
	BT_voidInit(&serial);
	BT_voidInit(&debug);

	LED_voidTurnON(&red);

	u8 lines [4][10];
	u8 Ack = 'z';
	//u8 endOfLine = '\n';

	for(u8 i = 0; i < 3; i++)
	{
			//do{

				BT_voidReceiveData(&serial, lines[i], 5);
			//}while(lines[i][0] == 0xFF);



			/*if(lines[i][j] == 'F'){
				BT_voidSendData(&debug, &endOfLine, 1);
				break;
			}*/
			//for(u32 d=0; d<1080*10; d++);
			//BT_voidSendData(&serial, &Ack, 1);

	}
	for(u8 i = 0; i < 3; i++)
	{
		for(u8 j=0; j<10; j++)
				lines[i][j] &= ~(1<<7);

		BT_voidSendData(&debug, lines[i], 5);
	}
	LED_voidTurnOFF(&red);

	while(1)
	{
		LED_voidToggle(&green);
		TIMERS_voidDelayMilliSec(500);
	}
}
/*

void Bootloader_run(void)
{
	u8 rec = 0, index;


	TIMERS_voidSetInterrupt(TIM1, Application, 10000); // Will be replaced by set interval
	while(1 & rec != 0) // Will be replaced by wait for timer flag (timeout)
	{
		BT_voidReceiveDataTimeOut(&serial, &rec, 1);
	}
	if(rec == 0){
		// jump to application
	}
	else{
		// stop timer and complete bootloader sequence
	}

	// receive the file and flash it
	while(1 File not finished )
	{
		index = 0;
		while(rec != '\n'){
			BT_voidReceiveData(&serial, &rec, 1);
			recordBuffer[index++] = rec;
		}
		RecordParser(recordBuffer);
	}
}
*/
