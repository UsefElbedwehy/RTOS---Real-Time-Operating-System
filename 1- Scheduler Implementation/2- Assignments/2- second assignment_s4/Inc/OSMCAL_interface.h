#ifndef OSMCAL_INTERFACE_H_
#define OSMCAL_INTERFACE_H_



void Stack_voidSchedulerStackInit(uint32_t Copy_u32SchedTOS);
void STK_voidInit(uint32_t Copy_u32TickHz);


__attribute__ ((naked)) void Stack_TaskStackInit(uint32_t Copy_u32TaskTOS ,uint8_t Copy_u8TaskNumber);


void Stack_voidEnableSystemFaults(void);
void Stack_voidChangeToPSPValue(uint32_t Copy_u32TaskTOS);









#endif
