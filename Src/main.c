/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "string.h"

#include "../MCAL/RCC/RCC_Interface.h"
#include "../MCAL/TIMERS/TIMERS_Interface.h"
#include "../MCAL/NVIC/NVIC_Interface.h"

#include "../ECUAL/LED/LED_Interface.h"
#include "../Services/Bootloader.h"


LED_t green = {PORTA, 1};

void SystemInitialize(void);
void Blink(void);
void SerialTest(void);
void WriteSector(void);

//void (*app)(void);


int main(void)
{
	SystemInitialize();

	//app = (void *)0x08010000;

	BL_start();

	//app();

	while(1)
	{
		Blink();
	}
}

void SystemInitialize(void)
{
	RCC_voidInit();

	RCC_voidPeripheralEnable(GPIOA_EN);
	RCC_voidPeripheralEnable(GPIOB_EN);
	RCC_voidPeripheralEnable(TIM2_EN);
	RCC_voidPeripheralEnable(TIM5_EN);
	RCC_voidPeripheralEnable(USART1_EN);
	RCC_voidPeripheralEnable(USART6_EN);

	NVIC_voidEnableIRQ(NVIC_IRQ_TIM5);

	LED_voidInit(&green);
}

void Blink(void)
{
	LED_voidToggle(&green);
	TIMERS_voidDelayMilliSec(500);
}

void WriteSector(void)
{
	u32 flashAddress = 0x08010000;
	u32 data[] = {0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007};
	FMI_voidFlashWrite(flashAddress, data, 8);
}
