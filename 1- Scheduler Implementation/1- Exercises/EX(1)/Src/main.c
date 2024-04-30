/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

int main(void)
{

	__asm ("SVC #5");

	//register uint32_t local_u32Data __asm("r0");

	uint32_t Local_u32Data;

	__asm volatile("MOV %0, R0" : "=r"(Local_u32Data));

    /* Loop forever */
	for(;;);
}

__attribute__ ((naked)) void SVC_Handler(void)
{
	/*1- Getting the MSP value(Stack frame base) */
	__asm volatile("MRS R0, MSP");

	__asm volatile("B SVCHandler_C");


	/*Note that R0 will be considered as an argument to the called function*/
}

void SVCHandler_C(uint32_t* Copy_pu32StackFrameBase)
{
	uint8_t Local_u8SVCNumber;
	/*2- Getting the PC value*/
	uint8_t*  Local_pu8ReturnAddress = (uint8_t*)Copy_pu32StackFrameBase[6];

	/*3- Getting the SVC Instruction address*/
	Local_pu8ReturnAddress -=2;

	/*4- Now derefersnce this address, get the 1st byte*/
	Local_u8SVCNumber = *Local_pu8ReturnAddress;

	/*5- Increment the value by 4*/
	Local_u8SVCNumber += 4;
	/*Put the result in R0 of the interrupted code stack frame*/
	Copy_pu32StackFrameBase[0] = Local_u8SVCNumber;
}


