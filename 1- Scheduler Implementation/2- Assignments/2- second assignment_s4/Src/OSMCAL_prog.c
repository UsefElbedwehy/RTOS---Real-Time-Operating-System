
#include <stdint.h>

#include "Stm32F446xx.h"
#include "ErrType.h"

#include "OSMCAL_cfg.h"
#include "OSMCAL_interface.h"

uint32_t u32PSPValue[4]={0};

__attribute__ ((naked)) void Stack_TaskStackInit(uint32_t Copy_u32TaskTOS ,uint8_t Copy_u8TaskNumber)
{
	uint32_t* Local_pu32PSP = (uint32_t*)Copy_u32TaskTOS;

	/*switch to PSP*/
	//__asm volatile("MSR CONTROL, 0b0010");
	/*Set PSP value*/
	//__asm volatile("MSR SP,R0");

	/*xPSR*/
	*(--Local_pu32PSP) = 0x01000000;
	/*PC*/
	*(--Local_pu32PSP) = (uint32_t)(Stack_TaskStackInit);
	/*LR*/
	*(--Local_pu32PSP) = 0xFFFFFFFD;
	/*R0, R1, R2, R3, R12 initialze with zero*/
	*(--Local_pu32PSP) = 0;
	*(--Local_pu32PSP) = 0;
	*(--Local_pu32PSP) = 0;
	*(--Local_pu32PSP) = 0;
	*(--Local_pu32PSP) = 0;

	/*R4, R5, R6, R7, R8, R9, R10, R11*/
	*(--Local_pu32PSP) = 0;
	*(--Local_pu32PSP) = 0;
	*(--Local_pu32PSP) = 0;
	*(--Local_pu32PSP) = 0;
	*(--Local_pu32PSP) = 0;
	*(--Local_pu32PSP) = 0;
	*(--Local_pu32PSP) = 0;
	*(--Local_pu32PSP) = 0;


	/*update PSP value in PSP array*/
	__asm volatile("MRS %0, PSP":"=r"(u32PSPValue[Copy_u8TaskNumber]));

	__asm volatile("BX LR");
}

void Stack_voidChangeToPSPValue(uint32_t Copy_u32TaskTOS)
{
	//__asm volatile("MSR SP,R0");
}

void Stack_voidEnableSystemFaults(void)
{
	SCB->SCB_SHCRS |= ((1<<3) | (1<<1) | (1<<0));
}

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
void HardFault_Handler(void)
{
	while(1);
}
void MemManage_Handler(void)
{
	while(1);
}
void BusFault_Handler(void)
{
	while(1);
}
void UsageFault_Handler(void)
{
	while(1);
}
