
#include <stdint.h>

#include "Stm32F446xx.h"
#include "ErrType.h"

#include "OSMCAL_cfg.h"
#include "OSMCAL_interface.h"


__attribute__ ((naked)) void Stack_voidSchedulerStackInit(uint32_t Copy_u32SchedTOS)
{
	__asm volatile("MSR MSP,R0");

	//__asm volatile("MSR MSP,%0"::"r"(Copy_u32SchedTOS));

	__asm volatile("BX LR");

}


void STK_voidInit(uint32_t Copy_u32TickHz)
{
	/*Calculate the required number of ticks*/
	uint32_t Local_u32ReloadValue = (SYSTICK_TIM_CLK / Copy_u32TickHz);

	/*Decrement by one to consider the multi-shot timer*/
	Local_u32ReloadValue--;

	SYSTICK->SYSTICK_RVR = Local_u32ReloadValue;

	/*Enable SYSTICK exception*/
	SYSTICK->SYSTICK_CSR |= ( 1 << 1 );

	/*Set clock source*/
	SYSTICK->SYSTICK_CSR |= (1 << 2);

	/*Enable SYSTICK timer peripheral*/
	SYSTICK->SYSTICK_CSR |= (1 << 0);

}

void SysTick_Handler(void)
{

}

