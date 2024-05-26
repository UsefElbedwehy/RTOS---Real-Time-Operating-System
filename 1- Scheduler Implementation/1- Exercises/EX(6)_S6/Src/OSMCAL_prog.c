
#include <stdint.h>

#include "Stm32F446xx.h"
#include "ErrType.h"

#include "OSMCAL_cfg.h"
#include "OSMCAL_interface.h"

#include "main.h"

void IdleTaskHandler(void);

typedef enum{

	ReadyState,
	BlockState

}TaskState_t;

typedef struct{

	uint32_t 	PSPValue;
	uint32_t 	BLockCount;
	TaskState_t CurrentState;
	void(*TaskHandler)(void);

}TCP_t;

TCP_t UserTasks[MAX_TASK_NUM];


uint32_t CurrentTask = 1u; /*Starting at 1 to ignore Idle task*/

uint32_t GlobalTickCounts=0u;

void InitTaskStack(void)
{

	uint32_t* Local_pu32TaskPSP;
	uint8_t Local_u8LoopIdx1 ,Local_u8LoopIdx2;

	/*Tasks PSP Initialization*/
	UserTasks[0].PSPValue = IDLE_TASK_STACK_START;
	UserTasks[1].PSPValue = T1_STACK_START;
	UserTasks[2].PSPValue = T2_STACK_START;
	UserTasks[3].PSPValue = T3_STACK_START;
	UserTasks[4].PSPValue = T4_STACK_START;

	/*Tasks Handler Initialization*/
	UserTasks[0].TaskHandler = &IdleTaskHandler;
	UserTasks[1].TaskHandler = &Task1_Handler;
	UserTasks[2].TaskHandler = &Task2_Handler;
	UserTasks[3].TaskHandler = &Task3_Handler;
	UserTasks[4].TaskHandler = &Task4_Handler;

	for(Local_u8LoopIdx1=0 ; Local_u8LoopIdx1 < MAX_TASK_NUM ; Local_u8LoopIdx1++)
	{
		/*Initialize Task as ready*/
		UserTasks[Local_u8LoopIdx1].CurrentState = ReadyState;

		Local_pu32TaskPSP = (uint32_t*)UserTasks[Local_u8LoopIdx1].PSPValue;

		/*xPSR register*/
		Local_pu32TaskPSP--;
		*Local_pu32TaskPSP = DUMMY_XPSR;
		/*PC register*/
		Local_pu32TaskPSP--;
		*Local_pu32TaskPSP = (uint32_t)(UserTasks[Local_u8LoopIdx1].TaskHandler);
		/*LR register*/
		Local_pu32TaskPSP--;
		*Local_pu32TaskPSP = DUMMY_LR;

		for(Local_u8LoopIdx2=0 ; Local_u8LoopIdx2 < 13 ; Local_u8LoopIdx2++)
		{
			/*R0, R1, R2, R3, R12 initialze with zero*/
			/*R4, R5, R6, R7, R8, R9, R10, R11*/
			Local_pu32TaskPSP--;
			*Local_pu32TaskPSP = 0;
		}

		/*update PSP value in PSP array*/
		UserTasks[Local_u8LoopIdx1].PSPValue = (uint32_t)Local_pu32TaskPSP;

	}


}

__attribute__((naked)) void SysTick_Handler(void)
{
	/*Save context of current task*/
	/*1- Get current running task's PSP value*/
	__asm volatile("MRS R0,PSP");
	/*2- using that PSP value,Store SF2 (R4 -> R11)*/
	__asm volatile("STMDB R0!,{R4-R11}");

	/*We will push LR value in current sp which is MSP, cuz we are going to use LR register*/
	__asm volatile("PUSH {LR}");

	/*3- save current value of PSP*/
	__asm volatile("BL SavePSPValue");

	/*Retrieve context of next task*/
	/*1- decide next task to run*/
	__asm volatile("BL UpdateNextTask");
	/*2- Get its PSP value*/
	__asm volatile("BL GetCurrentPSPValue");

	/*we will get the LR register value back */
	__asm volatile("POP {LR}");

	/*3- Using that PSP value, retrieve SF2(R4->R11)*/
	__asm volatile("LDM R0!,{R4-R11}");
	/*4- Update PSP value*/
	__asm volatile("MSR PSP,R0");

	/*Exit*/
	__asm volatile("BX LR");

}

uint32_t GetCurrentPSPValue(void)
{
	return UserTasks[CurrentTask].PSPValue;
}

void SavePSPValue(uint32_t Copy_u32CurrentPSPValue)
{
	UserTasks[CurrentTask].PSPValue = Copy_u32CurrentPSPValue;
}

void UpdateNextTask(void)
{
	uint8_t Local_u8TaskCount;
	for(Local_u8TaskCount=0;Local_u8TaskCount<MAX_TASK_NUM;Local_u8TaskCount++)
	{
		CurrentTask++;
		CurrentTask %= MAX_TASK_NUM;

		if((UserTasks[CurrentTask].CurrentState == ReadyState) && (Local_u8TaskCount !=0) )
		{
		/*check if any other task is ready ,excluding the idle task*/
			break;
		}

	}
	if((UserTasks[CurrentTask].CurrentState != ReadyState))	/*All tasks re blocked*/
	{
		CurrentTask = 0;
	}

}

__attribute__((naked)) void ChangeToPSP(void)
{
	__asm volatile("PUSH {LR}");

	/*Initialize PSP with Task stack address start*/
	__asm volatile("BL GetCurrentPSPValue");

	__asm volatile("MSR PSP, R0");

	__asm volatile("POP {LR}");

	/*2- Change SP to PSP using CONTROL register*/
	__asm volatile("MOV R0, #0x02");
	__asm volatile("MSR CONTROL, R0");

	__asm volatile("BX LR");
}

void EnableSystemFaults(void)
{
	SCB->SCB_SHCRS |= (1<<16);	/*Mem Manage fault enable*/
	SCB->SCB_SHCRS |= (1<<17);	/*Bus fault enable*/
	SCB->SCB_SHCRS |= (1<<18);	/*Usage fault enable*/
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

void TaskDelay(uint32_t Copy_u32BLockCount)
{
	/*Update Task blocking period*/
	UserTasks[CurrentTask].BLockCount = Copy_u32BLockCount + GlobalTickCounts ;

	/*Update Task state*/
	UserTasks[CurrentTask].CurrentState = BlockState;
}

void IdleTaskHandler(void)
{
	while(1);
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
