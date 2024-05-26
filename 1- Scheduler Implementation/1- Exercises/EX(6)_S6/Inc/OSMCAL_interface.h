#ifndef OSMCAL_INTERFACE_H_
#define OSMCAL_INTERFACE_H_

#define DUMMY_XPSR 0x01000000
#define DUMMY_LR   0xFFFFFFFD

void InitTaskStack(void);
uint32_t GetCurrentPSPValue(void);
void SavePSPValue(uint32_t Copy_u32CurrentPSPValue);
void UpdateNextTask(void);
__attribute__((naked)) void ChangeToPSP(void);
void EnableSystemFaults(void);
__attribute__ ((naked)) void Stack_voidSchedulerStackInit(uint32_t Copy_u32SchedTOS);
void STK_voidInit(uint32_t Copy_u32TickHz);
__attribute__((naked)) void SysTick_Handler(void);

void TaskDelay(uint32_t Copy_u32BLockCount);



#endif
