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

#define ADDITION		6
#define SUBTRACTION		7
#define MULTIPLICATION	8
#define DIVISION		9

#define STACK_FRAME_R0_INDEX    0
#define STACK_FRAME_R1_INDEX	1
#define	STACK_FRAME_PC_INDEX	6

void SVC_Addition(uint8_t x,uint8_t y);
void SVC_Subtraction(uint8_t x,uint8_t y);
void SVC_Multiplication(uint8_t x,uint8_t y);
void SVC_Division(uint8_t x,uint8_t y);

int main(void)
{
	uint8_t Local_u8NewResult;

	SVC_Addition(3,2);

	__asm volatile ("MOV %0, R0":"=r"(Local_u8NewResult));

    /* Loop forever */
	for(;;);
}

__attribute__((naked)) void SVC_Handler(void)
{

	__asm volatile ("MRS R0, MSP");

	__asm volatile ("B SVC_Handler_C");

}
void SVC_Handler_C(uint32_t* Copy_pu32StackFrameBase)
{

	uint8_t  Local_u8Result;
	uint8_t* Local_pu8SVC = (uint8_t*)Copy_pu32StackFrameBase[STACK_FRAME_PC_INDEX];

	Local_pu8SVC -= 2;

	switch(*Local_pu8SVC)
	{
	case ADDITION:
		Local_u8Result = (uint8_t)(Copy_pu32StackFrameBase[STACK_FRAME_R0_INDEX] + Copy_pu32StackFrameBase[STACK_FRAME_R1_INDEX]);
		Copy_pu32StackFrameBase[STACK_FRAME_R0_INDEX] = Local_u8Result;
		break;
	case SUBTRACTION:
		Local_u8Result = (uint8_t)(Copy_pu32StackFrameBase[STACK_FRAME_R0_INDEX] - Copy_pu32StackFrameBase[STACK_FRAME_R1_INDEX]);
		Copy_pu32StackFrameBase[STACK_FRAME_R0_INDEX] = Local_u8Result;
			break;
	case MULTIPLICATION:
		Local_u8Result = (uint8_t)(Copy_pu32StackFrameBase[STACK_FRAME_R0_INDEX] * Copy_pu32StackFrameBase[STACK_FRAME_R1_INDEX]);
		Copy_pu32StackFrameBase[STACK_FRAME_R0_INDEX] = Local_u8Result;
			break;
	case DIVISION:
		Local_u8Result = (uint8_t)(Copy_pu32StackFrameBase[STACK_FRAME_R0_INDEX] / Copy_pu32StackFrameBase[STACK_FRAME_R1_INDEX]);
		Copy_pu32StackFrameBase[STACK_FRAME_R0_INDEX] = Local_u8Result;
			break;
	default:
		Local_u8Result = 0;

		break;


	}

}
void SVC_Addition(uint8_t x,uint8_t y)
{
	__asm ("SVC #6");
}
void SVC_Subtraction(uint8_t x,uint8_t y)
{
	__asm ("SVC #7");
}
void SVC_Multiplication(uint8_t x,uint8_t y)
{
	__asm ("SVC #8");
}
void SVC_Division(uint8_t x,uint8_t y)
{
	__asm ("SVC #9");
}
